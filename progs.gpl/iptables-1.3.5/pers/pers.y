/*
 * IP Personality
 *   pers.y - Parser for config file
 *
 * Copyright (C) 2000, Gaël Roualland <gael.roualland@iname.com>
 * Copyright (C) 2000, Jean-Marc Saffroy <saffroy@mail.com>   
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Id: pers.y,v 1.15 2001/07/22 01:10:22 g_roualland Exp $
 *
 */

%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "pers.h"
  
#ifndef YYDEBUG
int yydebug;
#endif

/* global vars used by the parser */
struct symbol * yycode[2] = { NULL, NULL };
struct ip_pers * yypers;
char * yyfile;

int yyerror(char *);
struct symbol * newsym(int type, int option, int operand);
struct test * newtest(int type, int operand);
u_int32_t urandom();

#define linksym(sym, nxt)            { sym->next = nxt; }
#define linkcond(sym, tst, ctrue, cfalse) { sym->test = tst; sym->cond[0] = ctrue; sym->cond[1] = cfalse; }
#define linktest(tst, tst1, tst2)    { tst->test[0] = tst1; tst->test[1] = tst2; };

%}

%union {
  struct symbol * sym;
  struct test * test;
  int val;
  char * str;
}; 

%token SECT_ISN SECT_TCPOPT SECT_TCP SECT_IPID ID SECT_TCPDECOY SECT_UDP
%token SECT_IPTTL SECT_HTTP   /* Ella ++ */
%token ISN_TYPE ISN_IVALUE TSTAMP_SCALE
%token KEEP_UNKNOWN KEEP_UNUSED CODE MANGLEORIG RLEN RIPLEN
%token RANDOM TOK_NULL TCP_MAX_WINDOW ISOLATED_PACKETS
%token <val> NUMBER YESNO TCP_WAY ISN_TYPE_0 ISN_TYPE_N MANGLE ZERO SAME
%token <str> STRING

/* TCP Options */
%token <val> EOL NOP MSS WSCALE SACKOK SACK ECHO ECHOREPLY TIMESTAMP POCOK POCSP CC
%token <val> CCNEW CCECHO ACREQ ACDATA

/* TCP flags */
%token <val> SYN ACK FIN RST URG PUSH ECE CWR BOG1 BOG2 BOG3 BOG4

/* instructions */
%token IF ELSE ACCEPT DROP REPLY FLAGS OPTION COPY INSERT THIS SET LISTEN

/* misc */
%token <val> DF UDP_OPT TOS MAXLEN WIN

/* http Options, Ella ++ */
%token <val> HTTP_COOKIEFRAG

%left OR AND '!'

%type <sym> instruction_list instruction prog set_val
%type <test> test tcp_flag_list
%type <val> tcp_opt tcp_flag set_arg ins_opt ret udp_act

%expect 1 /* if/then/else conflict */

%start file

%%

/* grammar for config file */

file		  : ID STRING ';' { strncpy((char *) yypers->id, $2, sizeof(yypers->id) - 1);
                                    free($2); }
                    options ;

options           : SECT_TCP '{' section_tcp '}' options
                  | SECT_ISN '{' section_isn '}' options
                  | SECT_TCPOPT '{' section_tcpopt '}' options
                  | SECT_TCPDECOY '{' section_tcpdecoy '}' options
		  | SECT_IPTTL '{' section_ipttl '}' options
                  | SECT_UDP '{' section_udp '}' options { yypers->udp_unreach = 1; }
		  | SECT_IPID '{' section_ipid '}' options
		  | SECT_HTTP '{' section_http '}' options
                  |
                  ;

section_tcp	  : conf_tcp section_tcp
                  |
                  ;

conf_tcp          : TCP_WAY YESNO ';'
                    { if ($2) yypers->tcp_way |= $1; else yypers->tcp_way &= ~$1; }
                  | TCP_MAX_WINDOW NUMBER ';' { yypers->tcp_maxwin = $2; }
                  ;

section_isn       : conf_isn section_isn
                  |
                  ;

conf_isn          : ISN_TYPE ISN_TYPE_0 ';'
                    { yypers->isn_type = $2 ; }
                  | ISN_TYPE ISN_TYPE_N NUMBER ';'
                    { yypers->isn_type = $2 ; yypers->isn_param = $3 ; }
                  | ISN_IVALUE NUMBER ';'
                    { yypers->current_isn = $2 ; }
                  | ISN_IVALUE RANDOM ';'
                    { yypers->current_isn = urandom(); }
                  ;                  

section_ipid	  : conf_ipid section_ipid
                  |
                  ;

conf_ipid         : ISN_TYPE ISN_TYPE_0 ';'
                    { yypers->ipid_type = $2 ; }
                  | ISN_TYPE ISN_TYPE_N NUMBER ';'
                    { yypers->ipid_type = $2 ; yypers->ipid_param = $3 ; }
                  | ISN_IVALUE NUMBER ';'
                    { yypers->current_ipid = $2 ; }
                  | ISN_IVALUE RANDOM ';'
                    { yypers->current_ipid = urandom(); }

section_ipttl	  : conf_ipttl section_ipttl
                  |
                  ;

conf_ipttl        : ISN_IVALUE NUMBER ';'
                    { yypers->current_ipttl = $2 ; }
                  | ISN_IVALUE RANDOM ';'
                    { yypers->current_ipttl = urandom(); }

section_http	  : conf_http section_http
		  |
		  ;

conf_http	  : HTTP_COOKIEFRAG YESNO ';'
                    { if ($2) yypers->http_cookiefrag |= $1; else yypers->http_cookiefrag &= ~$1; }
		  ;

section_tcpopt    : conf_tcpopt section_tcpopt
                  |
                  ;

conf_tcpopt       : KEEP_UNKNOWN YESNO ';'
                    { yypers->opt_keep_unknown = $2; }
                  | KEEP_UNUSED YESNO ';'
                    { yypers->opt_keep_unused = $2; }
                  | ISOLATED_PACKETS YESNO ';'
                    { yypers->opt_isolated = $2; }
                  | TSTAMP_SCALE NUMBER ';'
                    { yypers->timestamp_scale = $2; }
                  | CODE '{' instruction_list '}' { yycode[0] = $3; }
                  ;

section_tcpdecoy  : conf_tcpdecoy section_tcpdecoy
                  |
                  ;

conf_tcpdecoy     : CODE '{' instruction_list '}' { yycode[1] = $3; }
                  ;

section_udp       : conf_udp section_udp
                  |
                  ;

conf_udp          : MANGLEORIG '{' mangle_udp_list '}'
                  | REPLY YESNO ';' { yypers->udp_info[IP_PERS_UDP_REPLY] = $2; }
                  | MAXLEN NUMBER ';' { yypers->udp_info[IP_PERS_UDP_MAXLEN] = $2; }
                  | DF YESNO ';' { yypers->udp_info[IP_PERS_UDP_DF] = $2; }
                  | TOS NUMBER ';' { yypers->udp_info[IP_PERS_UDP_TOS] = $2; }
                  ;

mangle_udp_list   : mangle_udp mangle_udp_list
                  |
                  ;

mangle_udp        : UDP_OPT udp_act ';' { yypers->udp_info[$1] = $2; }
                  | RIPLEN NUMBER ';' { yypers->udp_info[IP_PERS_UDP_RIPLEN] = $2;
		                        yypers->udp_info[IP_PERS_UDP_RIPLEN_SAME] = 0; }
                  | RIPLEN SAME ';' { yypers->udp_info[IP_PERS_UDP_RIPLEN_SAME] = 1; }
                  | RLEN NUMBER ';' { yypers->udp_info[IP_PERS_UDP_RLEN] = $2;
                 		      yypers->udp_info[IP_PERS_UDP_RLEN_SAME] = 0;}
                  | RLEN SAME ';' { yypers->udp_info[IP_PERS_UDP_RLEN_SAME] = 1; }
                  ;

udp_act           : SAME | ZERO | MANGLE;

/* grammar for code */

prog              : '{' instruction_list '}' { $$ = $2; }
                  | '{' '}' { $$ = NULL; }
                  | instruction { $$ = $1; }
                  ;

instruction_list  : instruction instruction_list { linksym($1, $2); $$ = $1; }
                  | instruction { $$ = $1; }
                  ;

instruction       : IF '(' test ')' prog
                    { $$ = newsym(INS_TYPE_TEST, 0, 0); linkcond($$, $3, $5, NULL); }
                  | IF '(' test ')' prog ELSE prog
                    { $$ = newsym(INS_TYPE_TEST, 0, 0); linkcond($$, $3, $5, $7); }
                  | COPY '(' tcp_opt ')' ';' { $$ = newsym(INS_TYPE_COPY, 0, $3); }
                  | INSERT '(' tcp_opt ')' ';'
                    { $$ = newsym(INS_TYPE_INS, INS_OPT_FROM_THIS + $3, 0); }
                  | INSERT '(' ins_opt ',' set_val ')' ';'
                    { $$ = $5 ; $5->option += $3 ; $5->type = INS_TYPE_INS; }
                  | SET '(' FLAGS ',' tcp_flag_list ')' ';'
                    { $$ = newsym(INS_TYPE_SET, INS_OPT_SET_FLAGS, $5->operand); }
                  | SET '(' set_arg ',' set_val ')' ';'
                    { $$ = $5 ; $5->option += $3 ; $5->type = INS_TYPE_SET; }
                  | ret ';' { $$ = newsym(INS_TYPE_RET, $1, 0); }
		  | ';' { $$ = newsym(INS_TYPE_NOP, 0, 0); }
                  ;

test              : test OR test
                    { $$ = newtest(TEST_OR, 0); linktest($$, $1, $3); }
                  | test AND test
                    { $$ = newtest(TEST_AND, 0); linktest($$, $1, $3); }
                  | '(' test ')' { $$ = $2; }
                  | '!' test { $2->not = !$2->not; $$ = $2; }
                  | OPTION '(' tcp_opt ')' { $$ = newtest(TEST_TCPOPT, $3); }
                  | FLAGS '(' tcp_flag_list ')' { $$ = $3; }
                  | FLAGS '(' TOK_NULL ')' { $$ = newtest(TEST_TCPFLAG, 0); }
                  | ACK '(' NUMBER ')' { $$ = newtest(TEST_ACK, $3); }
                  | LISTEN { $$ = newtest(TEST_LISTEN, 0); }
                  ;

tcp_flag_list     : tcp_flag '&' tcp_flag_list
                  { if ($3->type != TEST_TCPFLAG && $3->type != TEST_TCPFLAG_ALL)
   		       { yyerror("incompatible flags grouping"); return 1; }
    		    $3->type = TEST_TCPFLAG_ALL;
		    $3->operand = $3->operand | $1; $$ = $3; }
                  | tcp_flag '|' tcp_flag_list
                  { if ($3->type != TEST_TCPFLAG && $3->type != TEST_TCPFLAG_ANY)
   		      { yyerror("incompatible flags grouping"); return 1; }
    		    $3->type = TEST_TCPFLAG_ANY;
		    $3->operand = $3->operand | $1; $$ = $3; }
                  | tcp_flag { $$ = newtest(TEST_TCPFLAG, $1); }
                  ;

tcp_flag          : SYN | ACK | FIN | RST | URG | PUSH | ECE | CWR | BOG1 | BOG2 | BOG3
                  | BOG4 ;

tcp_opt           : EOL | NOP | MSS | WSCALE | SACKOK | SACK | ECHO | ECHOREPLY | TIMESTAMP
                  | POCOK | POCSP | CC | CCNEW | CCECHO | ACREQ | ACDATA ;

ins_opt           : MSS | WSCALE | TIMESTAMP;
 
ret               : REPLY { $$ = INS_OPT_RET_REPLY; }
                  | ACCEPT { $$ = INS_OPT_RET_ACCEPT; }
                  | DROP { $$ = INS_OPT_RET_DROP; }
                  ;

set_arg           : ACK { $$ = INS_OPT_SET_ACK; }
                  | DF { $$ = INS_OPT_SET_DF; }
                  | WIN { $$ = INS_OPT_SET_WIN; }
                  ;

set_val           : NUMBER { $$ = newsym(0, 0, $1); }
                  | THIS { $$ = newsym(0, INS_OPT_FROM_THIS, 0); }
                  | THIS '+' NUMBER { $$ = newsym(0, INS_OPT_FROM_THIS, $3); }
                  ;

%%

int yyerror(char * s) {
  fprintf(stderr,"%s:%d: %s before '%s'.\n", yyfile,
          yylineno, s, yytext);
  return 0;
}

struct symbol * newsym(int type, int option, int operand) {
  struct symbol * sym;

  sym = (struct symbol *) calloc(1, sizeof(struct symbol));
  if (!sym) {
    fprintf(stderr, "%s:%d: not enough memory.\n", yyfile, yylineno);
    exit(EXIT_FAILURE);
  }
  sym->type = type;
  sym->option = option;
  sym->operand = operand;
  return sym;
}

struct test * newtest(int type, int operand) {
  struct test * test;

  test = (struct test *) calloc(1, sizeof(struct test));
  if (!test) {
    fprintf(stderr, "%s:%d: not enough memory.\n", yyfile, yylineno);
    exit(EXIT_FAILURE);
  }
  test->type = type;
  test->operand = operand;
  return test;
}

u_int32_t urandom() {
  u_int32_t res;
  int fd;

  if ((fd = open("/dev/urandom", O_RDONLY)) >= 0) {
    if (read(fd, &res, sizeof(u_int32_t)) == sizeof(u_int32_t)) {
      close(fd);
      return res;
    } else
      close(fd);
  }

  fprintf(stderr, "No /dev/urandom available. Reverting to regular pseudo-random.\n");
  srand((unsigned int) time(NULL));
  return (u_int32_t) rand();
}

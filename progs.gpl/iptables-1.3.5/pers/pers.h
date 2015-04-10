/*
 * IP Personality
 *   pers.h - IPTables PERS extension defines/prototypes
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
 * $Id: pers.h,v 1.10 2001/07/22 01:10:22 g_roualland Exp $
 *
 */

#ifndef PERS_H
#define PERS_H

#include <linux/netfilter_ipv4/ip_personality.h>

#define YYDEBUG 1

/* TCP Options from RFC1700:

   The Transmission Control Protocol (TCP) has provision for optional
   header fields identified by an option kind field.  Options 0 and 1 are
   exactly one octet which is their kind field.  All other options have
   their one octet kind field, followed by a one octet length field,
   followed by length-2 octets of option data.

   Kind   Length   Meaning                           Reference
   ----   ------   -------------------------------   ---------
   0        -    End of Option List                 [RFC793]
   1        -    No-Operation                       [RFC793]
   2        4    Maximum Segment Lifetime           [RFC793]
   3        3    WSOPT - Window Scale              [RFC1323]
   4        2    SACK Permitted                    [RFC1072]
   5        N    SACK                              [RFC1072]
   6        6    Echo (obsoleted by option 8)      [RFC1072]
   7        6    Echo Reply (obsoleted by option 8)[RFC1072]
   8       10    TSOPT - Time Stamp Option         [RFC1323]
   9        2    Partial Order Connection Permitted[RFC1693]
   10       5    Partial Order Service Profile     [RFC1693]
   11            CC                                 [Braden]
   12            CC.NEW                             [Braden]
   13            CC.ECHO                            [Braden]
   14       3    TCP Alternate Checksum Request    [RFC1146]
   15       N    TCP Alternate Checksum Data       [RFC1146]
   16            Skeeter                           [Knowles]
   17            Bubba                             [Knowles]
   18       3    Trailer Checksum Option    [Subbu & Monroe]

   URL = ftp://ftp.isi.edu/in-notes/iana/assignments/tcp-parameters
*/
#ifndef TCPOPT_EOL
#define TCPOPT_EOL         0
#endif
#ifndef TCPOPT_NOP
#define TCPOPT_NOP         1
#endif
#ifndef TCPOPT_MSS
#define TCPOPT_MSS         2
#endif
#ifndef TCPOPT_WSCALE
#define TCPOPT_WSCALE      3
#endif
#ifndef TCPOPT_SACKOK
#define TCPOPT_SACKOK      4
#endif
#ifndef TCPOPT_SACK
#define TCPOPT_SACK        5
#endif
#ifndef TCPOPT_ECHO
#define TCPOPT_ECHO        6
#endif
#ifndef TCPOPT_ECHOREPLY
#define TCPOPT_ECHOREPLY   7
#endif
#ifndef TCPOPT_TIMESTAMP
#define TCPOPT_TIMESTAMP   8
#endif
#ifndef TCPOPT_POCOK
#define TCPOPT_POCOK       9
#endif
#ifndef TCPOPT_POCSP
#define TCPOPT_POCSP      10
#endif
#ifndef TCPOPT_CC
#define TCPOPT_CC         11
#endif
#ifndef TCPOPT_CCNEW
#define TCPOPT_CCNEW      12
#endif
#ifndef TCPOPT_CCECHO
#define TCPOPT_CCECHO     13
#endif
#ifndef TCPOPT_ACREQ
#define TCPOPT_ACREQ      14
#endif
#ifndef TCPOPT_ACDATA
#define TCPOPT_ACDATA     15
#endif

/* TCP flags */
#ifndef TH_FIN
#define TH_FIN  0x01
#endif
#ifndef TH_SYN
#define TH_SYN  0x02
#endif
#ifndef TH_RST
#define TH_RST  0x04
#endif
#ifndef TH_PUSH
#define TH_PUSH 0x08
#endif
#ifndef TH_ACK
#define TH_ACK  0x10
#endif
#ifndef TH_URG
#define TH_URG  0x20
#endif
#ifndef TH_ECE
#define TH_ECE  0x40
#endif
#ifndef TH_CWR
#define TH_CWR  0x80
#endif
/* Bogus TCP Flags used by scanners */
#ifndef TH_BOG1
#define TH_BOG1 0x100
#endif
#ifndef TH_BOG2
#define TH_BOG2 0x200
#endif
#ifndef TH_BOG3
#define TH_BOG3 0x400
#endif
#ifndef TH_BOG4
#define TH_BOG4 0x800
#endif

/* symbol tree */
#define INS_TYPE_NOP  1
#define INS_TYPE_TEST 2
#define INS_TYPE_COPY 3
#define INS_TYPE_INS  4
#define INS_TYPE_SET  5
#define INS_TYPE_RET  6

/* options */
#define INS_OPT_SET_FLAGS     0
#define INS_OPT_SET_ACK       1
#define INS_OPT_SET_DF        2
#define INS_OPT_SET_WIN       3

#define INS_OPT_FROM_THIS     0x100

#define INS_OPT_RET_ACCEPT    0
#define INS_OPT_RET_REPLY     1
#define INS_OPT_RET_DROP      2

/* default size for asm output buffer */
#define CODE_BASESIZE  256

struct symbol {
  int type;
  int option;
  int operand;
  struct symbol * next;
  struct test * test;
  struct symbol * cond[2];
};

#define TEST_TCPOPT      0
#define TEST_TCPFLAG     1
#define TEST_TCPFLAG_ANY 2
#define TEST_TCPFLAG_ALL 3
#define TEST_OR          4
#define TEST_AND         5
#define TEST_ACK         6
#define TEST_LISTEN      7

struct test {
  int type;
  int operand;
  int not;
  struct test * test[2];
};

/* flex globals */
extern int yylineno;
extern FILE * yyin;
extern char * yytext;

/* parser globals */
extern struct ip_pers * yypers;
extern char * yyfile;
extern struct symbol * yycode[2];

#ifdef YYDEBUG
extern int yydebug;
#endif

/* in the lexer and parser */
int yylex();
int yyparse();

/* in pers_asm.c */
struct asmbuf {
  u_int32_t * code;
  int size;
};

void free_symtree(struct symbol * sym);
int asm_gen(struct asmbuf * abuf, struct symbol * sym);
void asm_optimize(u_int32_t * code, int len);

#endif

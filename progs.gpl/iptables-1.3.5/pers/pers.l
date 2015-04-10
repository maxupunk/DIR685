/*
 * IP Personality
 *   pers.l - Lexer for config file
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
 * $Id: pers.l,v 1.14 2001/07/19 23:43:25 g_roualland Exp $
 *
 */

/* -*-c-*- */

%pointer
%option noyywrap
%option 8bit
%option yylineno

%{
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include "pers.h"
#include "pers_tab.h"

#define LEXRET(a, b) { yylval.val = b ; return a ; }
%}

number          [0-9]+
hexnumber       0x[0-9A-Fa-f]+
symbol          [a-zA-Z][a-zA-Z0-9_]*
blanks          [ \t]*
string		\"[a-zA-Z0-9_\-.]+\"
cr              "\n"

%x ccomment cscomment

%%

 /* C like comments */
"/*"                    BEGIN(ccomment); 
<ccomment>[^*]*       
<ccomment>"*"+[^/]   
<ccomment>"*"+"/"       BEGIN(INITIAL);

 /* C++ ans shell like comments */
"//"|"#"                BEGIN(cscomment); 
<cscomment>[^\n]*
<cscomment>\n           BEGIN(INITIAL);

 /* sections */
tcp			return SECT_TCP;
tcp_isn			return SECT_ISN;
tcp_options		return SECT_TCPOPT;
tcp_decoy               return SECT_TCPDECOY;
ip_id			return SECT_IPID;
udp_unreach             return SECT_UDP;
ip_ttl			return SECT_IPTTL;  /* Ella ++ */
http			return SECT_HTTP;   /* Ella ++ */

 /* keywords for tcp section */
max-window		return TCP_MAX_WINDOW;
incoming		LEXRET(TCP_WAY, IP_PERS_TCP_IN);
outgoing		LEXRET(TCP_WAY, IP_PERS_TCP_OUT);

 /* keywords for isn section */
type			return ISN_TYPE;
initial-value		return ISN_IVALUE;

 /* isn types */
asis		        LEXRET(ISN_TYPE_0, IP_PERS_ASIS);
fixed-inc		LEXRET(ISN_TYPE_N, IP_PERS_FIXED_INC);
random-inc		LEXRET(ISN_TYPE_N, IP_PERS_RAND_INC);
time-inc		LEXRET(ISN_TYPE_N, IP_PERS_TIME_INC);
true-random		LEXRET(ISN_TYPE_0, IP_PERS_RANDOM);
builtin			LEXRET(ISN_TYPE_0, IP_PERS_BUILTIN);
broken-inc		LEXRET(ISN_TYPE_N, IP_PERS_BROKEN_INC);

 /* keywords for tcp options section */
code                    return CODE;
keep-unknown		return KEEP_UNKNOWN;
keep-unused		return KEEP_UNUSED;
isolated-packets	return ISOLATED_PACKETS;
timestamp-scale		return TSTAMP_SCALE;

 /* tcp options */
eol			LEXRET(EOL, TCPOPT_EOL);
nop			LEXRET(NOP, TCPOPT_NOP);
mss			LEXRET(MSS, TCPOPT_MSS);
wscale			LEXRET(WSCALE, TCPOPT_WSCALE);
sackOK			LEXRET(SACKOK, TCPOPT_SACKOK);
sack			LEXRET(SACK, TCPOPT_SACK);
echo			LEXRET(ECHO, TCPOPT_ECHO);
echoreply		LEXRET(ECHOREPLY, TCPOPT_ECHOREPLY);
timestamp		LEXRET(TIMESTAMP, TCPOPT_TIMESTAMP);
pocOK			LEXRET(POCOK, TCPOPT_POCOK);
pocSP			LEXRET(POCSP, TCPOPT_POCSP);
CC			LEXRET(CC, TCPOPT_CC);
CC\.NEW			LEXRET(CCNEW, TCPOPT_CCNEW);
CC\.ECHO		LEXRET(CCECHO, TCPOPT_CCECHO);
acreq			LEXRET(ACREQ, TCPOPT_ACREQ);
acdata			LEXRET(ACDATA, TCPOPT_ACDATA);

 /* tcp flags */
syn			LEXRET(SYN, TH_SYN);
ack			LEXRET(ACK, TH_ACK);
fin			LEXRET(FIN, TH_FIN);
rst			LEXRET(RST, TH_RST);
urg			LEXRET(URG, TH_URG);
push			LEXRET(PUSH, TH_PUSH);
ece			LEXRET(ECE, TH_ECE);
cwr 			LEXRET(CWR, TH_CWR);
bog1			LEXRET(BOG1, TH_BOG1);
bog2			LEXRET(BOG2, TH_BOG2);
bog3			LEXRET(BOG3, TH_BOG3);
bog4			LEXRET(BOG4, TH_BOG4);

 /* special case */
null                    return TOK_NULL;

 /* instructions */
flags                   return FLAGS;
option                  return OPTION;
copy                    return COPY;
insert                  return INSERT;
accept                  return ACCEPT;
reply                   return REPLY;
drop                    return DROP;
this                    return THIS;
set                     return SET;
listen                  return LISTEN;

 /* UDP options */
mangle-original         return MANGLEORIG;
ip-len                  return RIPLEN;
udp-len                 return RLEN;
ip-id                   LEXRET(UDP_OPT, IP_PERS_UDP_RIPID);
ip-csum                 LEXRET(UDP_OPT, IP_PERS_UDP_RIPCSUM);
udp-csum                LEXRET(UDP_OPT, IP_PERS_UDP_RCSUM);
udp-data                LEXRET(UDP_OPT, IP_PERS_UDP_RDATA);
same                    LEXRET(SAME, IP_PERS_UDP_SAME);
mangle                  LEXRET(MANGLE, IP_PERS_UDP_MANGLE);
zero                    LEXRET(ZERO, IP_PERS_UDP_ZERO);

 /* HTTP options, Ella ++ */
cookiefrag		LEXRET(HTTP_COOKIEFRAG, 1);	

 /* generic tokens */
if			return IF;
else                    return ELSE;
df                      return DF;
tos                     return TOS;
win                     return WIN;
max-len                 return MAXLEN;
yes                     LEXRET(YESNO, 1);
no                      LEXRET(YESNO, 0);
random			return RANDOM;
id			return ID;
{hexnumber}             { sscanf(yytext, "%x", &(yylval.val));
                          return NUMBER; }
{number} 		{ yylval.val = atoi(yytext);
                          return NUMBER; } 
{string}                { yytext[yyleng-1]='\0';
                          yylval.str = strdup(yytext+1);
                          return STRING; } 
"||"			return OR;
"&&"			return AND;

{blanks}               
{cr}
.                       return yytext[0];
%%

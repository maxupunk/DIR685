/*
 * IP Personality
 *   perscc.c - An external config file interpreter/compiler.
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
 * $Id: perscc.c,v 1.16 2001/07/22 01:10:22 g_roualland Exp $
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pers.h"

char * tcpopts[] = {
  "eol",
  "nop",
  "mss",
  "wscale",
  "sackOK",
  "sack",
  "echo",
  "echoreply",
  "timestamp",
  "pocOK",
  "pocSP",
  "CC",
  "CC.NEW",
  "CC.ECHO",
  "acreq",
  "acdata"
};

char * tcpopt(int n) {
  static char buf[20];
  
  if (n>=0 && n<sizeof(tcpopts))
    return tcpopts[n];
  else
    snprintf(buf, sizeof(buf), "tcpopt(%d)", n);
  return buf;
}

char * setarg(int n) {
  static char buf[20];

  switch(n) {
  case INS_OPT_SET_ACK:
    return "ack";
  case INS_OPT_SET_DF:
    return "df";
  case INS_OPT_SET_WIN:
    return "win";
  default:
    snprintf(buf, sizeof(buf), "tcpopt(%d)", n);
    return buf;
  }
}

char * tcpflags(int flags, char s) {
  static char buf[100];
  char sep[2];
  int i = 0;
  struct {
    char * txt;
    int bit;
  } flagnames[] = {
    { "fin", TH_FIN },
    { "syn", TH_SYN },
    { "ack", TH_ACK },
    { "urg", TH_URG },
    { "push", TH_PUSH },
    { "rst", TH_RST },
    { "ece", TH_ECE },
    { "cwr", TH_CWR },
    { "bog1", TH_BOG1 },
    { "bog2", TH_BOG2 },
    { "bog3", TH_BOG3 },
    { "bog4", TH_BOG4 },
    { NULL, 0 }
  };
  
  if (!flags)
    return "null";

  buf[0]='\0';
  sep[0] = s; sep[1] = '\0';
  
  while(flagnames[i].txt) {
    if (flags & flagnames[i].bit) {
      strcat(buf, sep);
      strcat(buf, flagnames[i].txt);
    }
    i++;
  }
  return buf+1;
}

int dump_testtree(struct test * test) {
  int nb = 1;
  
  if (test->not)
    printf("!");
  
  switch(test->type) {
  case TEST_OR:
  case TEST_AND:
    if (test->test[0]) {
      if (test->test[0]->type == TEST_OR || test->test[0]->type == TEST_AND)
	printf("(");      
      nb += dump_testtree(test->test[0]);
      if (test->test[0]->type == TEST_OR || test->test[0]->type == TEST_AND)
	printf(")");
    }
    printf(test->type == TEST_OR ? " || " : " && ");
    if (test->test[1]) {
      if (test->test[1]->type == TEST_OR || test->test[1]->type == TEST_AND)
	printf("(");      
      nb += dump_testtree(test->test[1]);
      if (test->test[1]->type == TEST_OR || test->test[1]->type == TEST_AND)
	printf(")");
    }
    break;
  case TEST_TCPFLAG:
  case TEST_TCPFLAG_ANY:
    printf("flags(%s)", tcpflags(test->operand, '|'));
    break;
  case TEST_TCPFLAG_ALL:
    printf("flags(%s)", tcpflags(test->operand, '&'));
    break;
  case TEST_TCPOPT:
    printf("option(%s)", tcpopt(test->operand & 0xFF));
    break;
  case TEST_ACK:
    printf("ack(%u)", test->operand);
    break;
  case TEST_LISTEN:
    printf("listen");
    break;
  default:
    printf("test[%d](%d)", test->type, test->operand);
    break;
  }
  return nb;
}

/* dumps the symbol tree built by the parser */
int dump_symtree(struct symbol * sym, int level) {
  int i = level;
  int j = 1;

  for (i=level; i; i--)
    printf("  ");

  switch(sym->type) {
  case INS_TYPE_COPY:
    printf("copy(%s);\n", tcpopt(sym->operand));
    break;
  case INS_TYPE_INS:
    printf("insert(%s, %s%u);\n", tcpopt(sym->option & ~(INS_OPT_FROM_THIS)),
	   (sym->option & INS_OPT_FROM_THIS) ? "this + " : "",
	   sym->operand);
    break;
  case INS_TYPE_SET:
    if ((sym->option & ~(INS_OPT_FROM_THIS)) == INS_OPT_SET_FLAGS)
      printf("set(flags, %s);\n", tcpflags(sym->operand, '|'));
    else
      printf("set(%s, %s%u);\n", setarg(sym->option & ~(INS_OPT_FROM_THIS)),
	     (sym->option & INS_OPT_FROM_THIS) ? "this + " : "",
	     sym->operand);
    break;
  case INS_TYPE_NOP:
    printf(";\n");
    break;
  case INS_TYPE_TEST:
    printf("if (");
    j += dump_testtree(sym->test);
    printf(") {\n");
    if (sym->cond[0])
      j += dump_symtree(sym->cond[0], level+1);
    for (i=level; i; i--)
      printf("  ");
    printf("} ");
    if (sym->cond[1]) {
      printf("else {\n");
      j += dump_symtree(sym->cond[1], level+1);
      for (i=level; i; i--)
	printf("  ");
      printf("}\n");
    } else {
      printf("\n");
    }
    break;
  case INS_TYPE_RET:
    switch (sym->option) {
    case INS_OPT_RET_ACCEPT:
      printf("accept;\n");
      break;
    case INS_OPT_RET_DROP:
      printf("drop;\n");
      break;
    case INS_OPT_RET_REPLY:
      printf("reply;\n");
      break;
    default:
      printf("ret(%d);\n", sym->option);
    }
    break;
  default:
    printf("ins[%d.%d](%d);\n", sym->type, sym->option, sym->operand);
    break;
  }
  if (sym->next)
    j += dump_symtree(sym->next, level);
  return j;
}

void asm_dump(u_int32_t * code, int len) {
  int i;

  for (i=0; i<len; i++) {
    printf("%04X:  [%08X]  ", i, code[i]);
    switch(code[i] & IP_PERS_INST) {
    case IP_PERS_PUT:
      printf("PUT     %s%s\n", tcpopt(code[i] & IP_PERS_DATA),
	     ((code[i] & IP_PERS_IOPT) == IP_PERS_PUT_INS) ? " (insert)" : " (copy)");
      break;
    case IP_PERS_JMP:
      printf("JMP     %04X\n", code[i] & IP_PERS_DATA);
      break;
    case IP_PERS_TEST:
      printf("TEST    ");
      switch (code[i] & IP_PERS_IOPT) {
      case IP_PERS_TEST_OPTION:
	printf("tcp_option, %s\n", tcpopt(code[i] & IP_PERS_DATA));
	break;
      case IP_PERS_TEST_FLAG_ANY:
	printf("tcp_flags, %s\n", tcpflags(code[i] & IP_PERS_DATA, '|'));
	break;
      case IP_PERS_TEST_FLAG_ALL:
	printf("tcp_flags, %s\n", tcpflags(code[i] & IP_PERS_DATA, '&'));
	break;
      case IP_PERS_TEST_LISTEN:
	printf("listen\n");
	break;
      case IP_PERS_TEST_ACK:
	printf("ack, %u\n", code[i] & IP_PERS_DATA);
	break;
      default:
	printf("%06X\n", code[i] & ~IP_PERS_INST);
      }
      break;
    case IP_PERS_SET:
      printf("SET     ");
      switch ((code[i] & IP_PERS_IOPT) & ~IP_PERS_SET_FROM_THIS) {
      case IP_PERS_SET_FLAGS:
	printf("flags, %s\n", tcpflags(code[i] & IP_PERS_DATA, '|'));
	break;
      case IP_PERS_SET_ACK:
	printf("ack, %s%u\n",
	       ((code[i] & IP_PERS_IOPT) & IP_PERS_SET_FROM_THIS) ? "this + " : "",
	       code[i] & IP_PERS_DATA);
	break;
      case IP_PERS_SET_DF:
	printf("df, %s%u\n",
	       ((code[i] & IP_PERS_IOPT) & IP_PERS_SET_FROM_THIS) ? "this + " : "",
	       code[i] & IP_PERS_DATA);
	break;
      case IP_PERS_SET_WIN:
	printf("win, %s%u\n",
	       ((code[i] & IP_PERS_IOPT) & IP_PERS_SET_FROM_THIS) ? "this + " : "",
	       code[i] & IP_PERS_DATA);
	break;
      case IP_PERS_SET_MSS:
	printf("mss, %s%u\n",
	       ((code[i] & IP_PERS_IOPT) & IP_PERS_SET_FROM_THIS) ? "this + " : "",
	       code[i] & IP_PERS_DATA);
	break;
      case IP_PERS_SET_WSCALE:
	printf("wscale, %s%u\n",
	       ((code[i] & IP_PERS_IOPT) & IP_PERS_SET_FROM_THIS) ? "this + " : "",
	       code[i] & IP_PERS_DATA);
      case IP_PERS_SET_TIMESTAMP:
	printf("timestamp, %s%u\n",
	       ((code[i] & IP_PERS_IOPT) & IP_PERS_SET_FROM_THIS) ? "this + " : "",
	       code[i] & IP_PERS_DATA);
	break;
      default:
	printf("%06X\n", code[i] & ~IP_PERS_INST);
      }
      break;
    case IP_PERS_RET:
      printf("RET     ");
      switch(code[i] & IP_PERS_DATA) {
      case IP_PERS_ACCEPT:
	printf("accept\n");
	break;
      case IP_PERS_DROP:
	printf("drop\n");
	break;
      case IP_PERS_REPLY:
	printf("reply\n");
	break;
      default:
	printf("%06X\n", code[i] & IP_PERS_DATA);
      }
      break;
    default:
      printf("%02X      %06X\n", (code[i] & IP_PERS_INST) >> 24, code[i] & ~IP_PERS_INST);
    }
  }
}

char * udp_text(int i) {
  switch (i) {
  case IP_PERS_UDP_ZERO:
    return "zero";
  case IP_PERS_UDP_SAME:
    return "same";
  case IP_PERS_UDP_MANGLE:
    return "mangle";
  }
  return "??";
}

void print_gen(u_int32_t type, u_int32_t param, u_int32_t current) {
  switch(type) {
  case IP_PERS_FIXED_INC:
    printf("fixed-increments (value=%u, base=%u)\n", param, current);
    break;
  case IP_PERS_BROKEN_INC:
    printf("broken-increments (value=%u, base=%u)\n", param, current);
    break;
  case IP_PERS_RAND_INC:
    printf("random-increments (value=%u, base=%u)\n", param, current);
    break;
  case IP_PERS_TIME_INC:
    printf("time-increments, (freq=%u Hz, base=%u)\n", param, current);
    break;
  case IP_PERS_RANDOM:
    printf("true-random\n");
    break;
  case IP_PERS_BUILTIN:
    printf("builtin\n");
    break;
  case IP_PERS_ASIS:
  default:
    printf("asis\n");
    break;
  }
}

void dump_config(struct ip_pers * pers) {
  if (pers->id[0]) 
    printf("id: %s\n", pers->id);

  printf("ipid type: ");
  print_gen(pers->ipid_type, pers->ipid_param, pers->current_ipid);
  printf("isn type: ");
  print_gen(pers->isn_type, pers->isn_param, pers->current_isn);
  printf("rewrite way: %s %s\n"
	 "keep unknown options: %s\n"
	 "keep unused options: %s\n"
	 "max window: %u\n"
	 "change options for isolated packets: %s\n",
	 pers->tcp_way & IP_PERS_TCP_IN ? "ingoing" : "",
	 pers->tcp_way & IP_PERS_TCP_OUT ? "outgoing" : "",
	 pers->opt_keep_unknown ? "yes" : "no",
	 pers->opt_keep_unused ? "yes" : "no",
	 pers->tcp_maxwin,
	 pers->opt_isolated ? "yes" : "no" );

  
  if (pers->udp_unreach) 
    printf("udp-unreach:\n"
	   "  reply: %s\n"
	   "  df: %s\n"
	   "  max-len: %d\n"
	   "  tos: %d\n"
	   "  ip-len: %u %s\n"
	   "  ip-id: %s\n"
	   "  ip-csum: %s\n"
	   "  udp-len: %u %s\n"
	   "  udp-csum: %s\n"
	   "  udp-data: %s\n",
	   pers->udp_info[IP_PERS_UDP_REPLY] ? "yes" : "no",
	   pers->udp_info[IP_PERS_UDP_DF] ? "yes" : "no",
	   pers->udp_info[IP_PERS_UDP_MAXLEN],
	   pers->udp_info[IP_PERS_UDP_TOS],
	   pers->udp_info[IP_PERS_UDP_RIPLEN],
	   pers->udp_info[IP_PERS_UDP_RIPLEN_SAME]  ? "(same)" : "",
	   udp_text(pers->udp_info[IP_PERS_UDP_RIPID]),
	   udp_text(pers->udp_info[IP_PERS_UDP_RIPCSUM]),
	   pers->udp_info[IP_PERS_UDP_RLEN],
	   pers->udp_info[IP_PERS_UDP_RLEN_SAME]  ? "(same)" : "",
	   udp_text(pers->udp_info[IP_PERS_UDP_RCSUM]),
	   udp_text(pers->udp_info[IP_PERS_UDP_RDATA]));

  printf("decoy timestamp-scale: ");
  if (pers->timestamp_scale)
    printf("%u\n", pers->timestamp_scale);
  else
    printf("disabled\n");
}

int main(int argc, char ** argv) {
  struct ip_pers pers;
  struct asmbuf abuf;
  int alen;
  int i;
  
  if (argc != 2) {
    fprintf(stderr, "usage: %s file\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  yyin = fopen(argv[1], "r");
  if (!yyin) {
    fprintf(stderr, "%s: can't open %s for reading.\n", argv[0], argv[1]);
    exit(EXIT_FAILURE);
  }
  yyfile = argv[1];
  
  memset(&pers, 0, sizeof(pers));
  yypers = &pers;
#ifdef YYDEBUG
  yydebug = 0;
#endif  
  if (yyparse())
    exit(EXIT_FAILURE);

  printf("=== config ===\n");
  dump_config(yypers);

  for (i=0;i<2; i++) {
    printf("\n=== interpreted code #%d ===\n", i);
    if (yycode[i])
      printf("code: %d instructions.\n", dump_symtree(yycode[i], 0));
    printf("\n=== compiled code #%d ===\n", i);
    if (yycode[i]) {
      alen = asm_gen(&abuf, yycode[i]);
      free_symtree(yycode[i]);
      asm_optimize(abuf.code, alen);
      asm_dump(abuf.code, alen);
      printf("asm: %d instructions.\n", alen);
    }
  } 
  fclose(yyin);
  
  return EXIT_SUCCESS;
}

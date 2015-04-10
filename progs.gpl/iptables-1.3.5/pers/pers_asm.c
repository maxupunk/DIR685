/*
 * IP Personality
 *   pers_asm.c - Code generation routines
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
 * $Id: pers_asm.c,v 1.7 2001/07/22 01:10:22 g_roualland Exp $
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pers.h"

static void free_testtree(struct test * test) {
  if (test->test[0])
    free_testtree(test->test[0]);
  if (test->test[1])
    free_testtree(test->test[1]);

  free(test);
}

void free_symtree(struct symbol * sym) {
  struct symbol * sym2;
  
  while(sym) {
    if (sym->cond[0])
      free_symtree(sym->cond[0]);
    if (sym->cond[1])
      free_symtree(sym->cond[1]);
    if (sym->type == INS_TYPE_TEST)
      free_testtree(sym->test);

    sym2 = sym->next;
    free(sym);
    sym = sym2;
  }
}

static void asm_addins(struct asmbuf * abuf, int pos, int ins) {
  if (pos >= abuf->size) {
    u_int32_t * newbuf =
      (u_int32_t *) realloc((void *) abuf->code, (abuf->size << 1) * sizeof(u_int32_t));
    if (newbuf) {
      memset((void *) newbuf + abuf->size * sizeof(u_int32_t), 0,
	     abuf->size * sizeof(u_int32_t));
      abuf->code = newbuf;
      abuf->size <<= 1;
    } else {
      fprintf(stderr, "not enough memory assembling code.\n");
      exit(EXIT_FAILURE);
    }
  }
  abuf->code[pos] = ins;
}

static int asm_testtree(struct asmbuf * abuf, struct test * test, int pos) {
  int cur = 0, jmp = 0;
  
  switch (test->type) {
  case TEST_OR:
    cur += asm_testtree(abuf, test->test[0], pos);
    asm_addins(abuf, pos + cur, IP_PERS_JMP |
	       ((pos + cur + 2) & IP_PERS_DATA)); /* jump to second part of or */
    jmp = cur + 1; /* reserve room for jump at end of test (true case) */
    cur += 2;
    cur += asm_testtree(abuf, test->test[1], pos + cur);
    asm_addins(abuf, pos + jmp, IP_PERS_JMP |
	       ((pos + cur + 1) & IP_PERS_DATA)); /* jump to true part */
    break;
  case TEST_AND:
    cur += asm_testtree(abuf, test->test[0], pos);
    jmp = cur++; /* reserve room for false case */
    cur += asm_testtree(abuf, test->test[1], pos + cur);
    asm_addins(abuf, pos + jmp, IP_PERS_JMP |
	       ((pos + cur) & IP_PERS_DATA)); /* jump to false part */
    break;
  case TEST_TCPOPT:
    asm_addins(abuf, pos, IP_PERS_TEST | IP_PERS_TEST_OPTION |
	       (test->operand & IP_PERS_DATA));
    cur++;
    break;
  case TEST_TCPFLAG:
  case TEST_TCPFLAG_ANY:
    asm_addins(abuf, pos, IP_PERS_TEST | IP_PERS_TEST_FLAG_ANY |
	       (test->operand & IP_PERS_DATA));
    cur++;
    break;
  case TEST_TCPFLAG_ALL:
    asm_addins(abuf, pos, IP_PERS_TEST | IP_PERS_TEST_FLAG_ALL |
	       (test->operand & IP_PERS_DATA));
    cur++;
    break;
  case TEST_LISTEN:
    asm_addins(abuf, pos, IP_PERS_TEST | IP_PERS_TEST_LISTEN);
    cur++;
    break;
  case TEST_ACK:
    asm_addins(abuf, pos, IP_PERS_TEST | IP_PERS_TEST_ACK |
	       (test->operand & IP_PERS_DATA));
    cur++;
    break;
  default:
    fprintf(stderr, "instruction %d: invalid test %d -- test always true\n",
	    pos, test->type);
    asm_addins(abuf, pos, IP_PERS_JMP | ((pos + 2) & IP_PERS_DATA)); /* skip else case */	
    return 1;
  }

  if (test->not) { // inverse test
    asm_addins(abuf, pos + cur, IP_PERS_JMP | ((pos + cur +2) & IP_PERS_DATA));
    return cur+1;
  } else
    return cur;
}

static int asm_symtree(struct asmbuf * abuf, struct symbol * sym, int base) {
  int cur = 0, pos = base, jmp[2] = { 0, 0 };
  int tmp;
  
  while(sym) {
    switch(sym->type) {
    case INS_TYPE_RET:
      tmp = -1;
      switch(sym->option) {
      case INS_OPT_RET_ACCEPT:
	tmp = IP_PERS_ACCEPT;
	break;
      case INS_OPT_RET_REPLY:
	tmp = IP_PERS_REPLY;
	break;
      case INS_OPT_RET_DROP:
	tmp = IP_PERS_DROP;
	break;
      default:
	fprintf(stderr, "invalid option %d for RET, ignored.\n", sym->option);
      }
      if (tmp>=0) {
	asm_addins(abuf, pos, IP_PERS_RET | tmp);
	cur = 1;
      }
      break;
    case INS_TYPE_SET:
      tmp = -1;
      switch(sym->option & ~(INS_OPT_FROM_THIS)) {
      case INS_OPT_SET_FLAGS:
	tmp = IP_PERS_SET_FLAGS;
	break;
      case INS_OPT_SET_DF:
	tmp = IP_PERS_SET_DF;
	break;
      case INS_OPT_SET_ACK:
	tmp = IP_PERS_SET_ACK;
	break;
      case INS_OPT_SET_WIN:
	tmp = IP_PERS_SET_WIN;
	break;
      default:
	fprintf(stderr, "invalid option %d for SET, ignored.\n", sym->option);
      }
      if (tmp>=0) {
	if (sym->option & INS_OPT_FROM_THIS)
	  tmp |= IP_PERS_SET_FROM_THIS;
	asm_addins(abuf, pos, IP_PERS_SET | tmp | (sym->operand & IP_PERS_DATA));
	cur = 1;
      }
      break;
    case INS_TYPE_INS:
      tmp = -1;
      switch (sym->option & ~(INS_OPT_FROM_THIS)) {
      case TCPOPT_WSCALE:
	tmp = IP_PERS_SET_WSCALE;
	break;
      case TCPOPT_MSS:
	tmp = IP_PERS_SET_MSS;
	break;
      case TCPOPT_TIMESTAMP:
	tmp = IP_PERS_SET_TIMESTAMP;
	break;
      default:
	fprintf(stderr, "invalid option %d for INS, ignored.\n", sym->option);
      }
      if (tmp>=0) {
	if (sym->option & INS_OPT_FROM_THIS)
	  tmp |= IP_PERS_SET_FROM_THIS;
	asm_addins(abuf, pos, IP_PERS_SET | tmp | (sym->operand & IP_PERS_DATA));
	asm_addins(abuf, pos + 1, IP_PERS_PUT | IP_PERS_PUT_INS |
		   ((sym->option & ~(INS_OPT_FROM_THIS)) & IP_PERS_DATA));
	cur = 2;
      }
      break;
    case INS_TYPE_COPY:
      asm_addins(abuf, pos, IP_PERS_PUT | IP_PERS_PUT_COPY |
		 (sym->operand & IP_PERS_DATA));
      cur = 1;
      break;
    case INS_TYPE_NOP:
      break;
    case INS_TYPE_TEST:
      cur += asm_testtree(abuf, sym->test, pos);
      jmp[0] = cur++; /* reserve room for "else" jump on pos+cur */
      if (sym->cond[0])
	cur += asm_symtree(abuf, sym->cond[0], pos + cur);
      if (sym->cond[1]) {
	jmp[1] = cur++; /* reserve room for jmp at end of true case */
	asm_addins(abuf, pos + jmp[0],
		   IP_PERS_JMP | ((pos + cur) & IP_PERS_DATA)); /* else case starts here */
	cur += asm_symtree(abuf, sym->cond[1], pos + cur);
	asm_addins(abuf, pos + jmp[1],
		   IP_PERS_JMP | ((pos + cur) & IP_PERS_DATA)); /* end of test here */
      } else
	asm_addins(abuf, pos + jmp[0],
		   IP_PERS_JMP | ((pos + cur) & IP_PERS_DATA)); /* end of test and else case */
      break;
    default:
      fprintf(stderr, "invalid instruction %d, ignored.\n", sym->type);
      break;
    }
    sym = sym->next;
    pos += cur;
    cur = 0;
  }
  return (pos - base);
}

int asm_gen(struct asmbuf * abuf, struct symbol * sym) {
  abuf->size = CODE_BASESIZE;
  abuf->code = (u_int32_t *) calloc(abuf->size, sizeof(u_int32_t));

  if (abuf->code) {
    return asm_symtree(abuf, sym, 0);
  } else {
    fprintf(stderr, "cannot allocate asm memory\n");
    exit(EXIT_FAILURE);
  }
}

void asm_optimize(u_int32_t * code, int len) {
  int i = len;
  int ojmp, njmp;

  /* simple optimization: short cut consecutive jumps */
  while(--i>=0)
    if ((code[i] & IP_PERS_INST) == IP_PERS_JMP) {
      ojmp = njmp = code[i] & IP_PERS_DATA;
      while((njmp >= 0) && (njmp < len) && ((code[njmp] & IP_PERS_INST) == IP_PERS_JMP))
	njmp = code[njmp] & IP_PERS_DATA;
      if (njmp != ojmp)
	code[i] = IP_PERS_JMP | (njmp & IP_PERS_DATA);
    }
}

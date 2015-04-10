/*
 * IP Personality
 *   libipt_PERS.c - Shared library extension of iptables for PERS
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
 * $Id: libipt_PERS.c,v 1.15 2001/07/19 23:43:25 g_roualland Exp $
 *
 */

#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>
#include <iptables.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ip_personality.h>
#include "pers.h"

/* Function which prints out usage message. */
static void
help(void)
{
	printf(
"PERS (personality) v%s options:\n"
" --conf file			reads configuration from file.\n"
" --tweak {src|dst}		sets which part of the rule to tweak.\n"
" --local			destination is local, enables decoy for it.\n",
IPTABLES_VERSION);
}

static struct option opts[] = {
  { "conf", 1, 0, '1' },
  { "tweak", 1, 0, '2' },
  { "local", 0, 0, '3' },
  { 0 }
};

struct optnames {
  char * text;
  u_int32_t code;
};

static struct optnames tweak_opts[] = {
  { "src", IP_PERS_TWEAK_SRC },
  { "dst", IP_PERS_TWEAK_DST },
  { NULL, 0 }
};

/* Initialize the target. */
static void
init(struct ipt_entry_target *t, unsigned int *nfcache)
{
	struct ip_pers *pers = (struct ip_pers *)t->data;

	memset(pers, 0, sizeof(struct ip_pers));
	pers->isn_type = IP_PERS_ASIS;
	pers->ipid_type = IP_PERS_ASIS;

	/* Can't cache this ?? */
	*nfcache |= NFC_UNKNOWN;
}

/* Function which parses command options; returns true if it
   ate an option */
static int
parse(int c, char **argv, int invert, unsigned int *flags,
      const struct ipt_entry *entry,
      struct ipt_entry_target **target)
{
	int i, alen;
	struct ip_pers *pers
		= (struct ip_pers *)(*target)->data;
	struct asmbuf abuf;

	switch (c) {
	case '1':
	  if (pers->id[0])
	    exit_error(PARAMETER_PROBLEM,
		       "Only one configuration file allowed.");

	  yyfile = optarg;
	  yypers = pers;
	  yyin = fopen(yyfile, "r");

	  if (!yyin)
	    exit_error(PARAMETER_PROBLEM,
		       "Cannot read %s.", yyfile);
	  
	  yyparse();
	  fclose(yyin);
	  
	  if (!pers->id[0])
	    exit_error(PARAMETER_PROBLEM,
		       "Bad configuration file.");
	    
	  if (yycode[0] && ((alen = asm_gen(&abuf, yycode[0]))>0)) {
	    free_symtree(yycode[0]);
	    yycode[0] = NULL;
	    
	    if (alen <= IP_PERS_MAX_CODE) { 
	      asm_optimize(abuf.code, alen);
	      pers->opt_prog.prog_len = alen;
	      memcpy(pers->opt_prog.instr, abuf.code, alen * sizeof(u_int32_t));
	    } else {
	      exit_error(PARAMETER_PROBLEM,
			 "Compiled code is too big. Increase IP_PERS_MAX_CODE.");
	    }
	  } else
	    pers->opt_prog.prog_len = 0;

	  if (yycode[1] && ((alen = asm_gen(&abuf, yycode[1]))>0)) {
	    free_symtree(yycode[1]);
	    yycode[1] = NULL;
	    
	    if (alen <= IP_PERS_MAX_CODE) { 
	      asm_optimize(abuf.code, alen);
	      pers->decoy_prog.prog_len = alen;
	      memcpy(pers->decoy_prog.instr, abuf.code, alen * sizeof(u_int32_t));
	    } else {
	      exit_error(PARAMETER_PROBLEM,
			 "Compiled code is too big. Increase IP_PERS_MAX_CODE.");
	    }
	  } else
	    pers->decoy_prog.prog_len = 0;
	  
	  return 1;
	case '2':
	  i = 0;
	  while (tweak_opts[i].text) {
	    if (!strcasecmp(tweak_opts[i].text, optarg)) {
	      pers->tweak_type = tweak_opts[i].code;
	      break;
	    }
	    i++;
	  }
	  if (!tweak_opts[i].text)
	    exit_error(PARAMETER_PROBLEM,
		       "Unknown TWEAK mode.\n");
	  return 1;
	case '3':
	  pers->local = 1;
	  return 1;
	}
	return 0;
}

/* Final check; don't care. */
static void final_check(unsigned int flags)
{
}

/* Prints out the targinfo. */
static void
print(const struct ipt_ip *ip,
      const struct ipt_entry_target *target,
      int numeric)
{
	struct ip_pers *pers
		= (struct ip_pers *)target->data;

	switch(pers->tweak_type) {
	case IP_PERS_TWEAK_SRC:
	  printf("tweak:src ");
	  break;
	case IP_PERS_TWEAK_DST:
	  printf("tweak:dst ");
	  break;
	}
	if (pers->local)
	  printf("local ");
	if (pers->id[0])
	  printf("id:%s ", pers->id);
}

/* Saves the union ipt_targinfo in parsable form to stdout. */
static void
save(const struct ipt_ip *ip, const struct ipt_entry_target *target)
{
	struct ip_pers *pers
		= (struct ip_pers *)target->data;

	switch(pers->tweak_type) {
	case IP_PERS_TWEAK_SRC:
	  printf("--tweak src ");
	  break;
	case IP_PERS_TWEAK_DST:
	  printf("--tweak dst ");
	  break;
	}
	if (pers->local)
	  printf("--local ");
	if (pers->id[0])
	  printf("--conf %s.conf ", pers->id);
}

struct iptables_target pers_target = { NULL,
    .name		= "PERS",
    .version		= IPTABLES_VERSION,
    .size		= IPT_ALIGN(sizeof(struct ip_pers)),
    .userspacesize	= IPT_ALIGN(sizeof(struct ip_pers)),
    .help		= &help,
    .init		= &init,
    .parse		= &parse,
    .final_check	= &final_check,
    .print		= &print,
    .save		= &save,
    .extra_opts		= opts
};

void _init(void)
{
	register_target(&pers_target);
}

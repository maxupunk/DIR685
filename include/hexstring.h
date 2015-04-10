/* vi: set sw=4 ts=4: */
/*
 *	hexstring.c
 *
 *	This file contains some useful function to manupulate HEX-string.
 *
 *	Created by David Hsieh <david_hsieh@alphanetworks.com>
 */

#ifndef __HEXSTRING_HEADER__
#define __HEXSTRING_HEADER__

size_t			read_hexstring(unsigned char * buf, size_t size, const char * string);
const char *	print_macaddr(const unsigned char * macaddr);
const char *	print_uuid(const unsigned char * uuid);

void dump_hex(FILE * out, const char * start, const char * end, char delimiter,
			 const unsigned char * bin, size_t size);

#endif	/* endif ifdef __HEXSTRING_HEADER__ */

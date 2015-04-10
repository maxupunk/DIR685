/* ------------------------------------------------------------------------- */
/* tftp.c                                                                    */
/*                                                                           */
/* A simple tftp client for busybox.                                         */
/* Tries to follow RFC1350.                                                  */
/* Only "octet" mode supported.                                              */
/* Optional blocksize negotiation (RFC2347 + RFC2348)                        */
/*                                                                           */
/* Copyright (C) 2001 Magnus Damm <damm@opensource.se>                       */
/*                                                                           */
/* Parts of the code based on:                                               */
/*                                                                           */
/* atftp:  Copyright (C) 2000 Jean-Pierre Lefebvre <helix@step.polymtl.ca>   */
/*                        and Remi Lefebvre <remi@debian.org>                */
/*                                                                           */
/* utftp:  Copyright (C) 1999 Uwe Ohse <uwe@ohse.de>                         */
/*                                                                           */
/* This program is free software; you can redistribute it and/or modify      */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU          */
/* General Public License for more details.                                  */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with this program; if not, write to the Free Software               */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA   */
/*                                                                           */
/* ------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
/*------------------------------*/
/*FW_log_20070412, start {, Added by Erick*/
/*ELBOX_PROGS_GPL_SYSLOGD*/
#include <syslog.h>
#include "../../../include/asyslog.h"
/*FW_log_20070412, End }, Added by Erick*/
/* ********************************* */
#include "busybox.h"
#include "../../../include/elbox_config.h"/*ftp_tftp_FW_CG_20070125 Erick*/
/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
#include "imghdr.h"/*ftp_tftp_FW_CG_200609028 Erick*/
#include "md5.h"/*ftp_tftp_FW_CG_200609028 Erick*/

#include "lrgbin.h"/*ftp_tftp_FW_CG_20070112 Erick*/
#include "rgdb.h"/*ftp_tftp_FW_CG_20070112 Erick*/

char g_signature[50];/*ftp_tftp_FW_CG_20070112 Erick*/
#define RGDBGET(x, y, args...) _cli_rgdb_get_(x, y, ##args)/*ftp_tftp_FW_CG_20070112 Erick*/
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/
//#define CONFIG_FEATURE_TFTP_DEBUG

#define TFTP_BLOCKSIZE_DEFAULT 512 /* according to RFC 1350, don't change */
#define TFTP_TIMEOUT 5             /* seconds */

/* opcodes we support */

#define TFTP_RRQ   1
#define TFTP_WRQ   2
#define TFTP_DATA  3
#define TFTP_ACK   4
#define TFTP_ERROR 5
#define TFTP_OACK  6

static const char *tftp_bb_error_msg[] = {
	"Undefined error",
	"File not found",
	"Access violation",
	"Disk full or allocation error",
	"Illegal TFTP operation",
	"Unknown transfer ID",
	"File already exists",
	"No such user"
};

const int tftp_cmd_get = 1;
const int tftp_cmd_put = 2;
/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
const int tftp_cmd_get_fw = 4;
const int tftp_cmd_get_config = 8;
const int tftp_cmd_put_config = 0x10;

char *download_buffer=NULL;
char *download_buffer_ptr=NULL;
int  download_len=0;
#define MAX_FW_BUFFER_SIZE 16*1024*1024 /*FW_log_20070412, Added by Erick*/ 
#define MAX_CFG_BUFFER_SIZE 1*1024*1024
#define Config_Path "/var/config.bin"

/*		The rgdb tool function		*/
int _cli_rgdb_get_(char *buf, int size, const char *format, ...)
{
	int fd;
	char node[BUFSIZ];
	va_list marker;
	va_start(marker, format);
	vsnprintf(node, BUFSIZ, format, marker);
	va_end(marker);
	if((fd = lrgdb_open(NULL)) == -1)
	{
		perror("Cannot open database.");
		return -1;
	}
	if(lrgdb_get(fd, 0, node, NULL) == -1)
	{
		perror("Get ERROR!");
		lrgdb_close(fd);
		return -1;
	}
	if(read(fd, buf, size) == -1)
	{
		perror("Read database failed.");
		lrgdb_close(fd);
		return -1;
	}
	lrgdb_close(fd);
	return 0;
}

static unsigned long _cpu_to_le(unsigned long value)
{
	static int swap = -1;
	static unsigned long patt = 0x01020304;
	static unsigned char * p = (unsigned char *)&patt;
	
	if (swap == -1)
	{
		if (p[0] == 0x04 && p[1] == 0x03 && p[2] == 0x02 && p[3] == 0x01) swap=0;
		else swap = 1;
	}
	if (swap)
	{
		return (((value & 0x000000ff) << 24) |
				((value & 0x0000ff00) << 8) |
				((value & 0x00ff0000) >> 8) |
				((value & 0xff000000) >> 24));
	}
	return value;
}
extern int v2_check_image_block(const char * image, int size)
{
	int offset = sizeof(imghdr2_t);
	imgblock_t * block = NULL;
	MD5_CTX ctx;
	unsigned char digest[16];

	while (offset < size)
	{
		block = (imgblock_t *)&image[offset];

		//printf("Image header (0x%08x):\n", offset);
		//printf("  magic  : 0x%08x\n", block->magic);
		//printf("  size   : %d (0x%x)\n", block->size, block->size);
		//printf("  offset : 0x%08x\n", block->offset);
		//printf("  devname: \'%s\'\n", block->devname);
		//printf("  digest : "); DBYTES(block->digest, 16);
		
		if (block->magic != _cpu_to_le(IMG_V2_MAGIC_NO))
		{
			//printf("Wrong Magic in header !\n");
			break;
		}
		if (offset + sizeof(imgblock_t) + block->size > size)
		{
			//printf("Size out of boundary !\n");
			break;
		}

		/* check MD5 digest */
		MD5Init(&ctx);
		MD5Update(&ctx, (unsigned char *)&block->offset, sizeof(block->offset));
		MD5Update(&ctx, (unsigned char *)block->devname, sizeof(block->devname));
		MD5Update(&ctx, (unsigned char *)&block[1], block->size);
		MD5Final(digest, &ctx);

		if (memcmp(digest, block->digest, 16)!=0)
		{
			//printf("MD5 digest mismatch !\n");
//			printf("digest caculated : "); DBYTES(digest, 16);
//			printf("digest in header : "); DBYTES(block->digest, 16);
			break;
		}


		/* move to next block */
		offset += sizeof(imgblock_t);
		offset += block->size;

		//printf("Advance to next block : offset=%d(0x%x), size=%d(0x%x)\n", offset, offset, size, size);
	}
	if (offset == size) return 0;


//	printf("illegal block found at offset %d (0x%x)!\n", offset, offset);
//	printf("  offset (%d) : \n", offset); DBYTES((unsigned char *)block, 16);
/*FW_log_20070412, start {, Added by Erick*/                        
   bb_error_msg("Image file is not acceptable. Please check download file is right.");
#if ELBOX_PROGS_GPL_SYSLOGD 
   syslog(ALOG_AP_SYSACT|LOG_WARNING,"[SYSACT]Image file is not acceptable. Please check download file is right.");
#endif 
/*FW_log_20070412, End }, Added by Erick*/
	return -1;
}

extern int v3_check_image_block(const char * image, int size)
{
	int offset = sizeof(imghdr2_t);
	imgblock_tv3 * block = NULL;
	MD5_CTX ctx;
	unsigned char digest[16];
#ifdef ELBOX_FIRMWARE_FLASH_SP_MX
	unsigned char xmldb_buff[10];
	int           bcflag0, imgflag0;
#endif /*ELBOX_FIRMWARE_FLASH_SP_MX*/

	while (offset < size)
	{
		block = (imgblock_tv3 *)&image[offset];

		//printf("Image header (0x%08x):\n", offset);
		//printf("  magic  : 0x%08x\n", block->magic);
		//printf("  size   : %d (0x%x)\n", block->size, block->size);
		//printf("  offset : 0x%08x\n", block->offset);
		//printf("  devname: \'%s\'\n", block->devname);
		//printf("  digest : "); DBYTES(block->digest, 16);

		if (block->magic != _cpu_to_le(IMG_V3_MAGIC_NO))
		{
			//printf("Wrong Magic in header !\n");
			break;
		}

#ifdef ELBOX_FIRMWARE_FLASH_SP_MX
		memset(xmldb_buff, 0x0, sizeof(xmldb_buff));
		RGDBGET(xmldb_buff, sizeof(xmldb_buff)-1, "/runtime/nvram/flash");
		if(strlen(xmldb_buff)!=0)
		{
			bcflag0 = atoi(xmldb_buff);
#ifdef B_ENDIAN
		imgflag0 = ((block->flag[0]&0xff000000)>>24)|
		           ((block->flag[0]&0x00ff0000)>>8)|
		           ((block->flag[0]&0x0000ff00)<<8)|
		           ((block->flag[0]&0x000000ff)<<24);
#else
		imgflag0 = block->flag[0];
#endif /*B_ENDIAN*/
			if(bcflag0 > imgflag0)
			{
				printf("New board can't support old firmware\n");
				break;
			}
		}
#endif /*ELBOX_FIRMWARE_FLASH_SP_MX*/

		if (offset + sizeof(imgblock_tv3) + block->size > size)
		{
			//printf("Size out of boundary !\n");
			break;
		}

		/* check MD5 digest */
		MD5Init(&ctx);
		MD5Update(&ctx, (unsigned char *)&block->offset, sizeof(block->offset));
		MD5Update(&ctx, (unsigned char *)block->devname, sizeof(block->devname));
		MD5Update(&ctx, (unsigned char *)&block[1], block->size);
		MD5Final(digest, &ctx);

		if (memcmp(digest, block->digest, 16)!=0)
		{
			//printf("MD5 digest mismatch !\n");
			//printf("digest caculated : "); DBYTES(digest, 16);
			//printf("digest in header : "); DBYTES(block->digest, 16);
			break;
		}


		/* move to next block */
		offset += sizeof(imgblock_tv3);
		offset += block->size;

		//printf("Advance to next block : offset=%d(0x%x), size=%d(0x%x)\n", offset, offset, size, size);
	}
	if (offset == size) return 0;


	//printf("illegal block found at offset %d (0x%x)!\n", offset, offset);
	//printf("  offset (%d) : \n", offset); DBYTES((unsigned char *)block, 16);

	return -1;
}

extern int v2_image_check(const char * image, int size)
{
	imghdr2_t * v2hdr = (imghdr2_t *)image;
	unsigned char signature[MAX_SIGNATURE];
	
	int i;
	if (v2hdr && size > sizeof(imghdr2_t) && v2hdr->magic == _cpu_to_le(IMG_V2_MAGIC_NO))
	{
		/* check if the signature match */
		//printf("check image signature !\n");
		memset(g_signature,0,50);/*ftp_tftp_FW_CG_20070112 Erick*/
        RGDBGET(g_signature, 50, "/runtime/layout/image_sign");/*ftp_tftp_FW_CG_20070112 Erick*/
		
		memset(signature, 0, sizeof(signature));
		strncpy(signature, g_signature, sizeof(signature));
	

		//printf("  expected signature : [%s]\n", signature);
		//printf("  image signature    : [%s]\n", v2hdr->signature);

		if (strncmp(signature, v2hdr->signature, MAX_SIGNATURE)==0)
			return v2_check_image_block(image, size);
		/* check if the signature is {boardtype}_aLpHa (ex: wrgg02_aLpHa, wrgg03_aLpHa */
		for (i=0; signature[i]!='_' && i<MAX_SIGNATURE; i++);
		if (signature[i] == '_')
		{
			signature[i+1] = 'a';
			signature[i+2] = 'L';
			signature[i+3] = 'p';
			signature[i+4] = 'H';
			signature[i+5] = 'a';
			signature[i+6] = '\0';

			//printf("  try this signature : [%s]\n", signature);

			if (strcmp(signature, v2hdr->signature) == 0)
				return v2_check_image_block(image, size);
		}
	}
/*FW_log_20070412, start {, Added by Erick*/                        
                        bb_error_msg("Image file is not acceptable. Please check download file is right.");
#if ELBOX_PROGS_GPL_SYSLOGD 
                      	syslog(ALOG_AP_SYSACT|LOG_WARNING,"[SYSACT]Image file is not acceptable. Please check download file is right.");
#endif 
/*FW_log_20070412, End }, Added by Erick*/	
	
	return -1;
}

extern int v3_image_check(const char * image, int size)
{
	imghdr2_t * v2hdr = (imghdr2_t *)image;
	unsigned char signature[MAX_SIGNATURE];
	int i;
	if (v2hdr && size > sizeof(imghdr2_t) && v2hdr->magic == _cpu_to_le(IMG_V3_MAGIC_NO))
	{
		/* check if the signature match */
		//printf("check image signature !\n");
		
		memset(g_signature,0,50);/*ftp_tftp_FW_CG_20070112 Erick*/
        RGDBGET(g_signature, 50, "/runtime/layout/image_sign");/*ftp_tftp_FW_CG_20070112 Erick*/

		memset(signature, 0, sizeof(signature));
		strncpy(signature, g_signature, sizeof(signature));

		//printf("  expected signature : [%s]\n", signature);
		//printf("  image signature    : [%s]\n", v2hdr->signature);

		if (strncmp(signature, v2hdr->signature, MAX_SIGNATURE)==0)
			return v3_check_image_block(image, size);

		/* check if the signature is {boardtype}_aLpHa (ex: wrgg02_aLpHa, wrgg03_aLpHa */
		for (i=0; signature[i]!='_' && i<MAX_SIGNATURE; i++);
		if (signature[i] == '_')
		{
			signature[i+1] = 'a';
			signature[i+2] = 'L';
			signature[i+3] = 'p';
			signature[i+4] = 'H';
			signature[i+5] = 'a';
			signature[i+6] = '\0';

			//printf("  try this signature : [%s]\n", signature);

			if (strcmp(signature, v2hdr->signature) == 0)
				return v3_check_image_block(image, size);
		}
	}
	return -1;
}

extern int v2_burn_image(const char * image, int size)
{
	int offset = sizeof(imghdr2_t);
	imgblock_t * block;
	imghdr2_t headcheck;
	FILE * fh;
/*FW_log_20070412, start {, Added by Erick*/ 
        bb_error_msg("Download and check new F/W OK.");
	bb_error_msg("Device is writing new F/W to Flash.");
	bb_error_msg("Don't power off .");
/*FW_log_20070412, End }, Added by Erick*/ 


	while (offset < size)
	{
		block = (imgblock_t *)&image[offset];

		//bb_error_msg("burning image block.\n");
		//bb_error_msg("  size    : %d (0x%x)\n", (unsigned int)block->size, (unsigned int)block->size);
		//bb_error_msg("  devname : %s\n", block->devname);
		//bb_error_msg("  offset  : %d (0x%x)\n", (unsigned int)block->offset, (unsigned int)block->offset);

#if 1
		fh = fopen(block->devname, "w+");
		if (fh == NULL)
		{
/*FW_log_20070412, start {, Added by Erick*/			
			bb_error_msg("Fail to write file!");
#if ELBOX_PROGS_GPL_SYSLOGD 
			syslog(ALOG_AP_SYSACT|LOG_WARNING,"[SYSACT]Fail to write file!");
#endif		
/*FW_log_20070412, End }, Added by Erick*/	
			return -1;
		}
#if 1//joel auto check the header in flash,we can not handle the offset non zero....
		if(fread(&headcheck,sizeof(imghdr2_t),1,fh) && headcheck.magic == _cpu_to_le(IMG_V2_MAGIC_NO) && block->offset==0)
		{
		fseek(fh, block->offset, SEEK_SET);
			printf("head in flash\n");
			//write header 1
			fwrite((const void *)image, 1, sizeof(imghdr2_t), fh);
			//write header 2
			fwrite((const void *)&block[0], 1, sizeof(imgblock_t), fh);
		}
		else
#endif
		{
		   printf("No header in images\n");
		   fseek(fh, block->offset, SEEK_SET);
		}
		fwrite((const void *)&block[1], 1, block->size, fh);
		fsync(fh);
		fclose(fh);
#endif
/*FW_log_20070412, start {, Added by Erick*/
     bb_error_msg("Firmware update success");
#if ELBOX_PROGS_GPL_SYSLOGD 
		syslog(ALOG_AP_SYSACT|LOG_NOTICE,"[SYSACT]Firmware update success");	
#endif 
/*FW_log_20070412, End }, Added by Erick*/

		/* move to next block */
		offset += sizeof(imgblock_t);
		offset += block->size;
	}
	//upload_file.flag = 0;

	return 0;
}

extern int v3_burn_image(const char * image, int size)
{
	int offset = sizeof(imghdr2_t);
	imgblock_tv3 * block;
	FILE * fh;

	//printf("v3_burn_image >>>>\n");

	while (offset < size)
	{
		block = (imgblock_tv3 *)&image[offset];

		//printf("burning image block.\n");
		//printf("  size    : %d (0x%x)\n", (unsigned int)block->size, (unsigned int)block->size);
		//printf("  devname : %s\n", block->devname);
		//printf("  offset  : %d (0x%x)\n", (unsigned int)block->offset, (unsigned int)block->offset);

#if 1
		fh = fopen(block->devname, "w+");
		if (fh == NULL)
		{
 /* papa add start for syslog 2007/03/30 */
#if ELBOX_PROGS_GPL_SYSLOGD_AP
			syslog(ALOG_AP_SYSACT|LOG_WARNING,"[SYSACT]Fail to write file!");
#endif
 /* papa add end for syslog 2007/03/30 */
			printf("Failed to open device %s\n", block->devname);
			return -1;
		}
        fseek(fh, block->offset, SEEK_SET);
		printf("head in flash\n");
		//write header 1
		fwrite((const void *)image, 1, sizeof(imghdr2_t), fh);
		//write header 2
		fwrite((const void *)&block[0], 1, sizeof(imgblock_tv3), fh);
		fwrite((const void *)&block[1], 1, block->size, fh);
		fclose(fh);
#endif
 /* papa add start for syslog 2007/03/30 */
#if ELBOX_PROGS_GPL_SYSLOGD_AP
		syslog(ALOG_AP_SYSACT|LOG_NOTICE,"[SYSACT]Firmware update success");
#endif
 /* papa add end for syslog 2007/03/30 */
		printf("burning done!\n");

		/* move to next block */
		offset += sizeof(imgblock_tv3);
		offset += block->size;
	}
	//upload_file.flag = 0;

	return 0;
}

extern int burn_image(const char * image, int size)
{
	FILE * fh;

	//printf("burn_image >>>>\n");
	fh = fopen("/dev/mtdblock/1", "w+");
	if (fh == NULL)
	{
 /* papa add start for syslog 2007/03/30 */
#if ELBOX_PROGS_GPL_SYSLOGD_AP
			syslog(ALOG_AP_SYSACT|LOG_WARNING,"[SYSACT]Fail to write file!");
#endif
 /* papa add end for syslog 2007/03/30 */
		//printf("Failed to open device %s\n", "/dev/mtdblock/1");
		return -1;
	}
	fwrite((const void *)image, 1, size, fh);
	fclose(fh);
 /* papa add start for syslog 2007/03/30 */
#if ELBOX_PROGS_GPL_SYSLOGD_AP
	syslog(ALOG_AP_SYSACT|LOG_NOTICE,"[SYSACT]Firmware update success");
#endif
 /* papa add end for syslog 2007/03/30 */
	//printf("burning done!\n");

	//upload_file.flag = 0;

	return 0;
}
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/
#ifdef CONFIG_FEATURE_TFTP_BLOCKSIZE

static int tftp_blocksize_check(int blocksize, int bufsize)
{
        /* Check if the blocksize is valid:
	 * RFC2348 says between 8 and 65464,
	 * but our implementation makes it impossible
	 * to use blocksizes smaller than 22 octets.
	 */

        if ((bufsize && (blocksize > bufsize)) ||
	    (blocksize < 8) || (blocksize > 65464)) {
	        bb_error_msg("bad blocksize");
	        return 0;
	}

	return blocksize;
}

static char *tftp_option_get(char *buf, int len, char *option)
{
        int opt_val = 0;
	int opt_found = 0;
	int k;

	while (len > 0) {

	        /* Make sure the options are terminated correctly */

	        for (k = 0; k < len; k++) {
		        if (buf[k] == '\0') {
			        break;
			}
		}

		if (k >= len) {
		        break;
		}

		if (opt_val == 0) {
			if (strcasecmp(buf, option) == 0) {
			        opt_found = 1;
			}
		}
		else {
		        if (opt_found) {
				return buf;
			}
		}

		k++;

		buf += k;
		len -= k;

		opt_val ^= 1;
	}

	return NULL;
}

#endif

static inline int tftp(const int cmd, const struct hostent *host,
	const char *remotefile, int localfd, const unsigned short port, int tftp_bufsize)
{
	const int cmd_get = cmd & tftp_cmd_get;
	const int cmd_put = cmd & tftp_cmd_put;
/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
	const int cmd_get_fw = cmd & tftp_cmd_get_fw;/*ftp_tftp_FW_CG_200609028 Erick*/
	const int cmd_get_config = cmd & tftp_cmd_get_config;/*ftp_tftp_FW_CG_200609028 Erick*/
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*end }*/
	const int bb_tftp_num_retries = 5;

	struct sockaddr_in sa;
	struct sockaddr_in from;
	struct timeval tv;
	socklen_t fromlen;
	fd_set rfds;
	char *cp;
	unsigned short tmp;
	int socketfd;
	int len;
	int opcode = 0;
	int finished = 0;
	int timeout = bb_tftp_num_retries;
	unsigned short block_nr = 1;

#ifdef CONFIG_FEATURE_TFTP_BLOCKSIZE
	int want_option_ack = 0;
#endif

	/* Can't use RESERVE_CONFIG_BUFFER here since the allocation
	 * size varies meaning BUFFERS_GO_ON_STACK would fail */
	char *buf=xmalloc(tftp_bufsize + 4);

	tftp_bufsize += 4;

	if ((socketfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		bb_perror_msg("socket");
		return EXIT_FAILURE;
	}

	len = sizeof(sa);

	memset(&sa, 0, len);
	bind(socketfd, (struct sockaddr *)&sa, len);

	sa.sin_family = host->h_addrtype;
	sa.sin_port = port;
	memcpy(&sa.sin_addr, (struct in_addr *) host->h_addr,
		   sizeof(sa.sin_addr));

	/* build opcode */

	if (cmd_get) {
		opcode = TFTP_RRQ;
	}

	if (cmd_put) {
		opcode = TFTP_WRQ;
	}

	while (1) {

		cp = buf;

		/* first create the opcode part */

		*((unsigned short *) cp) = htons(opcode);

		cp += 2;

		/* add filename and mode */

		if ((cmd_get && (opcode == TFTP_RRQ)) ||
			(cmd_put && (opcode == TFTP_WRQ))) {
                        int too_long = 0;

			/* see if the filename fits into buf */
			/* and fill in packet                */

			len = strlen(remotefile) + 1;

			if ((cp + len) >= &buf[tftp_bufsize - 1]) {
			        too_long = 1;
			}
			else {
			        safe_strncpy(cp, remotefile, len);
				cp += len;
			}

			if (too_long || ((&buf[tftp_bufsize - 1] - cp) < 6)) {
				bb_error_msg("too long remote-filename");
				break;
			}

			/* add "mode" part of the package */

			memcpy(cp, "octet", 6);
			cp += 6;

#ifdef CONFIG_FEATURE_TFTP_BLOCKSIZE

			len = tftp_bufsize - 4; /* data block size */

			if (len != TFTP_BLOCKSIZE_DEFAULT) {

			        if ((&buf[tftp_bufsize - 1] - cp) < 15) {
				        bb_error_msg("too long remote-filename");
					break;
				}

				/* add "blksize" + number of blocks  */

				memcpy(cp, "blksize", 8);
				cp += 8;

				cp += snprintf(cp, 6, "%d", len) + 1;

				want_option_ack = 1;
			}
#endif
		}

		/* add ack and data */

		if ((cmd_get && (opcode == TFTP_ACK)) ||
			(cmd_put && (opcode == TFTP_DATA))) {

			*((unsigned short *) cp) = htons(block_nr);

			cp += 2;

			block_nr++;

			if (cmd_put && (opcode == TFTP_DATA)) {
				len = bb_full_read(localfd, cp, tftp_bufsize - 4);

				if (len < 0) {
					bb_perror_msg("read");
					break;
				}

				if (len != (tftp_bufsize - 4)) {
					finished++;
				}

				cp += len;
			}
		}


		/* send packet */


		timeout = bb_tftp_num_retries;  /* re-initialize */
		do {

			len = cp - buf;

#ifdef CONFIG_FEATURE_TFTP_DEBUG
			fprintf(stderr, "sending %u bytes\n", len);
			for (cp = buf; cp < &buf[len]; cp++)
				fprintf(stderr, "%02x ", (unsigned char)*cp);
			fprintf(stderr, "\n");
#endif
			if (sendto(socketfd, buf, len, 0,
					(struct sockaddr *) &sa, sizeof(sa)) < 0) {
				bb_perror_msg("send");
				len = -1;
				break;
			}


			if (finished && (opcode == TFTP_ACK)) {
				break;
			}

			/* receive packet */

			memset(&from, 0, sizeof(from));
			fromlen = sizeof(from);

			tv.tv_sec = TFTP_TIMEOUT;
			tv.tv_usec = 0;

			FD_ZERO(&rfds);
			FD_SET(socketfd, &rfds);

			switch (select(FD_SETSIZE, &rfds, NULL, NULL, &tv)) {
			case 1:
				len = recvfrom(socketfd, buf, tftp_bufsize, 0,
						(struct sockaddr *) &from, &fromlen);

				if (len < 0) {
					bb_perror_msg("recvfrom");
					break;
				}

				timeout = 0;

				if (sa.sin_port == port) {
					sa.sin_port = from.sin_port;
				}
				if (sa.sin_port == from.sin_port) {
					break;
				}

				/* fall-through for bad packets! */
				/* discard the packet - treat as timeout */
				timeout = bb_tftp_num_retries;

			case 0:
				bb_error_msg("timeout");

				timeout--;
				if (timeout == 0) {
					len = -1;
					bb_error_msg("last timeout");
				}
				break;

			default:
				bb_perror_msg("select");
				len = -1;
			}

		} while (timeout && (len >= 0));

		if ((finished) || (len < 0)) {
			break;
		}

		/* process received packet */


		opcode = ntohs(*((unsigned short *) buf));
		tmp = ntohs(*((unsigned short *) &buf[2]));

#ifdef CONFIG_FEATURE_TFTP_DEBUG
		fprintf(stderr, "received %d bytes: %04x %04x\n", len, opcode, tmp);
#endif

		if (opcode == TFTP_ERROR) {
			char *msg = NULL;

			if (buf[4] != '\0') {
				msg = &buf[4];
				buf[tftp_bufsize - 1] = '\0';
			} else if (tmp < (sizeof(tftp_bb_error_msg)
					  / sizeof(char *))) {

				msg = (char *) tftp_bb_error_msg[tmp];
			}

			if (msg) {
				bb_error_msg("server says: %s", msg);
			}

			break;
		}

#ifdef CONFIG_FEATURE_TFTP_BLOCKSIZE
		if (want_option_ack) {

			 want_option_ack = 0;

		         if (opcode == TFTP_OACK) {

			         /* server seems to support options */

			         char *res;

				 res = tftp_option_get(&buf[2], len-2,
						       "blksize");

				 if (res) {
				         int blksize = atoi(res);
			
					 if (tftp_blocksize_check(blksize,
							   tftp_bufsize - 4)) {

					         if (cmd_put) {
				                         opcode = TFTP_DATA;
						 }
						 else {
				                         opcode = TFTP_ACK;
						 }
#ifdef CONFIG_FEATURE_TFTP_DEBUG
						 fprintf(stderr, "using blksize %u\n", blksize);
#endif
					         tftp_bufsize = blksize + 4;
						 block_nr = 0;
						 continue;
					 }
				 }
				 /* FIXME:
				  * we should send ERROR 8 */
				 bb_error_msg("bad server option");
				 break;
			 }

			 bb_error_msg("warning: blksize not supported by server"
				   " - reverting to 512");

			 tftp_bufsize = TFTP_BLOCKSIZE_DEFAULT + 4;
		}
#endif

		if (cmd_get && (opcode == TFTP_DATA)) {

			if (tmp == block_nr) {
/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG			
			    if (cmd_get_fw || cmd_get_config)
			    {
			        len=len-4;
			        memcpy(download_buffer_ptr,&buf[4],len);
			        download_buffer_ptr += len;
			        download_len += len;
			        //printf("\r ..(%d)..",download_len);
			
			    }
			    else
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*end }*/
				len = bb_full_write(localfd, &buf[4], len - 4);

				if (len < 0) {
					bb_perror_msg("write");
					break;
				}

				if (len != (tftp_bufsize - 4)) {
					finished++;
				}

				opcode = TFTP_ACK;
				continue;
			}
		}

		if (cmd_put && (opcode == TFTP_ACK)) {

			if (tmp == (unsigned short)(block_nr - 1)) {
				if (finished) {
					break;
				}

				opcode = TFTP_DATA;
				continue;
			}
		}
	}

#ifdef CONFIG_FEATURE_CLEAN_UP
	close(socketfd);

        free(buf);
#endif

	return finished ? EXIT_SUCCESS : EXIT_FAILURE;
}

int tftp_main(int argc, char **argv)
{
	struct hostent *host = NULL;
	const char *localfile = NULL;
	const char *remotefile = NULL;
	int port;
	int cmd = 0;
	int fd = -1;
	int flags = 0;
	int opt;
	int result;
	int blocksize = TFTP_BLOCKSIZE_DEFAULT;
/*ftp_tftp_FW_CG_20070125 Erick*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
	char buf[50];
#endif

	

	/* figure out what to pass to getopt */

#ifdef CONFIG_FEATURE_TFTP_BLOCKSIZE
#define BS "b:"
#else
#define BS
#endif

#ifdef CONFIG_FEATURE_TFTP_GET
#define GET "g"
#else
#define GET
#endif

#ifdef CONFIG_FEATURE_TFTP_PUT
#define PUT "p"
#else
#define PUT
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
#define FW "f"  
#define GCG "t" /*get configuration file from PC*/
#define PCG "d" /*put configuration file to PC*/
	while ((opt = getopt(argc, argv, BS GET PUT FW GCG PCG "l:r:")) != -1) {
#else /*ftp_tftp_FW_CG_20070125 Erick*//*end }*/
	while ((opt = getopt(argc, argv, BS GET PUT "l:r:")) != -1) {
#endif
		switch (opt) {
#ifdef CONFIG_FEATURE_TFTP_BLOCKSIZE
		case 'b':
			blocksize = atoi(optarg);
			if (!tftp_blocksize_check(blocksize, 0)) {
                                return EXIT_FAILURE;
			}
			break;
#endif
#ifdef CONFIG_FEATURE_TFTP_GET
		case 'g':
			cmd = tftp_cmd_get;
			flags = O_WRONLY | O_CREAT | O_TRUNC;
			break;
#endif
#ifdef CONFIG_FEATURE_TFTP_PUT
		case 'p':
			cmd = tftp_cmd_put;
			flags = O_RDONLY;
			break;
#endif
		case 'l':
			localfile = optarg;
			break;
		case 'r':
			remotefile = optarg;
			break;
/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
		case 'f':
			cmd = tftp_cmd_get_fw | tftp_cmd_get;
			//get_fw=1;
			flags = O_RDWR | O_CREAT | O_TRUNC;
			break;
        case 't':
			cmd = tftp_cmd_put_config | tftp_cmd_put;
			flags = O_RDONLY;
			break;		
			
        case 'd':
			cmd = tftp_cmd_get_config | tftp_cmd_get;
			flags = O_RDWR | O_CREAT | O_TRUNC;
			break;
		/*case 'S':
			g_signature = optarg;*/
			break;	
#endif			
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/							
		}
	}

	if ((cmd == 0) || (optind == argc)) {
		bb_show_usage();
	}
	if(localfile && strcmp(localfile, "-") == 0) {
	    fd = fileno(((cmd==tftp_cmd_get))? stdout : stdin);
	}
/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
	
	if((cmd&tftp_cmd_get_fw)||(cmd&tftp_cmd_get_config))
	{
	    if(cmd&tftp_cmd_get_fw)
	        download_buffer=malloc(MAX_FW_BUFFER_SIZE);
	    else
	        download_buffer=malloc(MAX_CFG_BUFFER_SIZE);
	    
	    
        if(download_buffer)
        {
            download_buffer_ptr=download_buffer;
            download_len=0;
            //printf("allocate download_buffer->OK!\n");
            system("cp /usr/sbin/reboot /var/run/reboot");
            system("rgdb -i -s /runtime/update/fwimage/status 1");
	}
        else
        {
            //printf("allocate download_buffer->Fail!\n");
            return EXIT_FAILURE;
        } 

	}
	
	if(localfile == NULL && !(cmd&tftp_cmd_get_fw))
	{
	    localfile = remotefile;
	}
	
	if((cmd&tftp_cmd_get_config))
	{
	        /*The configuration file will be saved to /var/config.bin, 
	        and we will parse it after we get it by using tftp.*/
	        sprintf(buf,Config_Path);
	        localfile = buf;
	        //printf("%s\n", buf);
	}

	if((cmd&tftp_cmd_put_config))
	{
	        /*To generate the configuration file to put to PC*/
	        //printf("get config from flash\n");
	        system("/usr/sbin/sys -s configsave");
	        /*The file will be /var/config.bin*/
	        //printf("set local file to /var/config.bin\n");
	        sprintf(buf,Config_Path);
	        localfile = buf;
	}		
/*ftp_tftp_FW_CG_20070125 Erick*//*end }*/	
#else

	if(localfile == NULL)
	    localfile = remotefile;
#endif
	if(remotefile == NULL)
	    remotefile = localfile;
/*ftp_tftp_FW_CG_20070125 Erick*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
	if (fd==-1&& !(cmd&tftp_cmd_get_fw)) {
#else
	if (fd==-1) {
#endif
	    fd = open(localfile, flags, 0644);
	}
/*ftp_tftp_FW_CG_20070125 Erick*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
	if (fd < 0&& !(cmd&tftp_cmd_get_fw)) {
#else
	if (fd < 0) {
#endif
		bb_perror_msg_and_die("local file");
	}

	host = xgethostbyname(argv[optind]);
	port = bb_lookup_port(argv[optind + 1], "udp", 69);

#ifdef CONFIG_FEATURE_TFTP_DEBUG
	fprintf(stderr, "using server \"%s\", remotefile \"%s\", "
		"localfile \"%s\".\n",
		inet_ntoa(*((struct in_addr *) host->h_addr)),
		remotefile, localfile);
#endif

	result = tftp(cmd, host, remotefile, fd, port, blocksize);

#ifdef CONFIG_FEATURE_CLEAN_UP
	if (!(fd == STDOUT_FILENO || fd == STDIN_FILENO)) {
	    close(fd);
	}
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
    if((cmd&tftp_cmd_get_fw)&&result==EXIT_SUCCESS)
    {
//        printf("tftp get F/W success and start to check F/W ..\n");
            //img_buffer=malloc(5*1024*1024/2);
            //if(img_buffer) 
            {
                //lseek(fd,0,SEEK_SET);
                /*img_len=fread(img_buffer, 1, (5*1024*1024/2), pFile);*/
                //img_len=read(fd, img_buffer,(5*1024*1024/2));
                //if(img_len<=0)                   
                //    printf("Read File Error!!\n");
                //else
                {
                   // printf("image size=%d\n",download_len);
#ifdef ELBOX_PROGS_PRIV_CLI_SUPER
                    {
                        char xmldb_buff[10];
                        
                        memset(xmldb_buff, 0x0, sizeof(xmldb_buff));
                        RGDBGET(xmldb_buff, 10, "/runtime/sys/super");
                        //xmldbc_get_wb(NULL, 0, "/runtime/sys/super", xmldb_buff, sizeof(xmldb_buff)-1);
                        if(atoi(xmldb_buff)==1){
#ifdef ELBOX_FIRMWARE_HEADER_VERSION
                            if(ELBOX_FIRMWARE_HEADER_VERSION == 3){
                                burn_image(download_buffer, download_len);
                                return(result);
                            }else if(ELBOX_FIRMWARE_HEADER_VERSION == 2){
                                v2_burn_image(download_buffer, download_len);
                                return(result);
                            }
#else
                            v2_burn_image(download_buffer, download_len);
                            return(result);
#endif /*ELBOX_FIRMWARE_HEADER_VERSION*/
                        }
                    }
#endif /*ELBOX_PROGS_PRIV_CLI_SUPER*/
#ifdef ELBOX_FIRMWARE_HEADER_VERSION
                    if(ELBOX_FIRMWARE_HEADER_VERSION == 3){
                        if (v3_image_check(download_buffer, download_len)==0)
                        {
                            v3_burn_image(download_buffer, download_len);
                        }
                    }else if(ELBOX_FIRMWARE_HEADER_VERSION == 2){
                        if (v2_image_check(download_buffer, download_len)==0)
                        {
                            v2_burn_image(download_buffer, download_len);
                        }                        
                    }
#else
                    if (v2_image_check(download_buffer, download_len)==0)
                    {
                        //printf("F/W image_check->OK!!\n");
                        v2_burn_image(download_buffer, download_len);
                        //printf("close(fd)..");
                        //close(fd);
                        //printf("kill local file..");
                        //unlink(localfile);
                        //printf("OK\n");
                        
                    }
                    else
                    {
                       // printf("F/W image_check->fail!!\n");
                    }
#endif /*ELBOX_FIRMWARE_HEADER_VERSION*/
                 }  
                
            }
  
      
        
    }
/*FW_log_20070412, start {, Added by Erick*/ 
    if(result!=EXIT_SUCCESS&&((cmd&tftp_cmd_get_config)||(cmd&tftp_cmd_get_fw)||(cmd&tftp_cmd_put_config)))
    {     
        if(cmd&tftp_cmd_put_config)
        {
            /*Remove local file /var/config.bin*/
	        unlink(localfile);
	        bb_error_msg("Put configuraion file fail!");
        } 
        else
        { 
            bb_error_msg("Fail to get the file, please check the IP address and check the file name.");   
            if(cmd&tftp_cmd_get_config)
            {
                unlink(localfile);
            }
#if ELBOX_PROGS_GPL_SYSLOGD  
			else
                /*ftp_tftp_log_20070427*/
                syslog(ALOG_AP_SYSACT|LOG_WARNING,"[SYSACT]Fail to get the file, please check the IP address and check the file name.");
#endif
        }
    } 
/*FW_log_20070412, End }, Added by Erick*/    
    
    if(result==EXIT_SUCCESS&&((cmd&tftp_cmd_get_config)||(cmd&tftp_cmd_put_config)))
	{
	    if (cmd&tftp_cmd_get_config)
	    {
	        memset(g_signature,0,50);
            RGDBGET(g_signature, 50, "/runtime/layout/image_sign");
	        
	        download_buffer_ptr=download_buffer;
	        download_buffer_ptr+=strlen(g_signature)+1;
	        download_len-=strlen(g_signature)+1;
	        //printf("Signature len =%d Bytes\n",strlen(g_signature));
	        //printf("config file len =%d Bytes\n",download_len);
	        
	        if(write(fd,download_buffer_ptr,download_len)<=0)
	        {
	            bb_error_msg("Write config to dev->fail");
	        }
	        else
	        {
	            //printf("write config to dev->OK/n");
	            system("/etc/scripts/misc/profile.sh reset /var/config.bin");
	            system("/etc/scripts/misc/profile.sh put");/*Save_config_20070426 Erick*/
                //printf("/etc/scripts/misc/profile.sh reset /var/config.bin \n");	            
/*FW_log_20070412, Added by Erick*/                 	
                bb_error_msg("Update configuraion file successfully!");    
	        }
	        
	    }
	    else  /*FW_log_20070412, Added by Erick*/ 
	           bb_error_msg("Put configuraion file successfully!");
	         close(fd);
	        /*Remove local file /var/config.bin*/
	         unlink(localfile);
	}		
    
    if(download_buffer)
    {
        free(download_buffer);
        download_buffer=NULL;
      //  printf("Free download_buffer\n");
    }
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/
	return(result);
}

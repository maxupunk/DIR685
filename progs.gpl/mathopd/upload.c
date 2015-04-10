/* vi: set sw=4 ts=4: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "md5.h"
#include "mathopd.h"
#include "imghdr.h"
#include <elbox_config.h>


#include "xmldb.h"
#include "libxmldbc.h"
#include <libgen.h>

/*------------------------------*/
/* papa add start for syslog 2007/03/30 */
#include <syslog.h>
#include "asyslog.h"
/* ********************************* */
#undef DEBUG_MSG
//#define DEBUG_MSG

#ifdef DEBUG_MSG
#include <stdarg.h>
#define DEBUG_MSG_FILE		"/var/dbgmsg.txt"
static void _dbgprintf(const char * format, ...)
{
	va_list marker;
	FILE * fd;

	fd = fopen(DEBUG_MSG_FILE, "a+");
	if (fd)
	{
		va_start(marker, format);
		vfprintf(fd, format, marker);
		va_end(marker);
		fclose(fd);
	}
}
static void _dump_nbytes(const unsigned char * data, int size)
{
	int i;
	FILE * fd;

	fd = fopen(DEBUG_MSG_FILE, "a+");
	if (fd)
	{
		for (i=0; i<size; i++) fprintf(fd, "%02X ", data[i]);
		fprintf(fd, "\n");
		fclose(fd);
	}
}

#define DPRINTF(x, args...)	_dbgprintf(x, ##args)
#define DBYTES(data, size)	_dump_nbytes(data, size)
#else
#define DPRINTF(x, args...)
#define DBYTES(data, size)
#endif

extern char *g_signature;

upload upload_file={0, 0, 0, 0, 0, -1, 0};
void rlt_page(struct pool *p, char *pFName)
{
	char buf[512];
	FILE *pFile;
	size_t n;
	int r;

	if ((pFile=fopen(pFName, "r")))
	{
		while ((r=fread(buf, 1, 512, pFile)))
		{
			if (p->ceiling <= p->end) break;

			n = p->ceiling - p->end;
			if(r>n)
			{
				memcpy(p->end, buf ,n);
				p->end+=n;
				break;
			}
			memcpy(p->end, buf, r);
			p->end+=r;
		}
		fclose(pFile);
	}
}

#ifdef ELBOX_PROGS_GPL_MATHOPD_EXTERNAL_BT_FILE
void rlt_recvbuf(struct pool *p, char *pStr, size_t size)
{
	size_t n;
	
	if (p->ceiling <= p->end) return (void)0;
	
		n = p->ceiling - p->end;
		if(size<n)	n=size;
		memcpy(p->end, pStr ,n);
		p->end+=n;
		
	return (void)0;
}
#endif

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

static int v2_check_image_block(const char * image, int size)
{
	int offset = sizeof(imghdr2_t);
	imgblock_t * block = NULL;
	MD5_CTX ctx;
	unsigned char digest[16];

	while (offset < size)
	{
		block = (imgblock_t *)&image[offset];

		DPRINTF("Image header (0x%08x):\n", offset);
		DPRINTF("  magic  : 0x%08x\n", block->magic);
		DPRINTF("  size   : %d (0x%x)\n", block->size, block->size);
		DPRINTF("  offset : 0x%08x\n", block->offset);
		DPRINTF("  devname: \'%s\'\n", block->devname);
		DPRINTF("  digest : "); DBYTES(block->digest, 16);

		if (block->magic != _cpu_to_le(IMG_V2_MAGIC_NO))
		{
			DPRINTF("Wrong Magic in header !\n");
			break;
		}
		if (offset + sizeof(imgblock_t) + block->size > size)
		{
			DPRINTF("Size out of boundary !\n");
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
			DPRINTF("MD5 digest mismatch !\n");
			DPRINTF("digest caculated : "); DBYTES(digest, 16);
			DPRINTF("digest in header : "); DBYTES(block->digest, 16);
			break;
		}


		/* move to next block */
		offset += sizeof(imgblock_t);
		offset += block->size;

		DPRINTF("Advance to next block : offset=%d(0x%x), size=%d(0x%x)\n", offset, offset, size, size);
	}
	if (offset == size) return 0;


	DPRINTF("illegal block found at offset %d (0x%x)!\n", offset, offset);
	DPRINTF("  offset (%d) : \n", offset); DBYTES((unsigned char *)block, 16);

	return -1;
}

#ifdef ELBOX_FIRMWARE_HEADER_VERSION_CONTROL
static int v3_check_image_block(const char * image, int size)
{
	int offset = sizeof(imghdr2_t);
	imgblock_tv3 * block = NULL;
	MD5_CTX ctx;
	unsigned char digest[16];
#ifdef ELBOX_FIRMWARE_FLASH_SP_MX
	unsigned char xmldb_buff[10];
	int           bdflag0, imgflag0;
#endif /*ELBOX_FIRMWARE_FLASH_SP_MX*/

	while (offset < size)
	{
		block = (imgblock_tv3 *)&image[offset];

		DPRINTF("Image header (0x%08x):\n", offset);
		DPRINTF("  magic  : 0x%08x\n", block->magic);
		DPRINTF("  modle  : %s\n", block->modle);
		DPRINTF("  flag[0]: 0x%.8x\n", block->flag[0]);
		DPRINTF("  flag[1]: 0x%.8x\n", block->flag[1]);
		DPRINTF("  reserve[0]: %d\n", block->reserve[0]);
		DPRINTF("  reserve[1]: %d\n", block->reserve[1]);
		DPRINTF("  size   : %d (0x%x)\n", block->size, block->size);
		DPRINTF("  offset : 0x%08x\n", block->offset);
		DPRINTF("  devname: \'%s\'\n", block->devname);
		DPRINTF("  digest : "); DBYTES(block->digest, 16);

		if (block->magic != _cpu_to_le(IMG_V3_MAGIC_NO))
		{
			DPRINTF("Wrong Magic in header !\n");
			break;
		}

#ifdef ELBOX_FIRMWARE_FLASH_SP_MX
		memset(xmldb_buff, 0x0, sizeof(xmldb_buff));
		xmldbc_get_wb(NULL, 0, "/runtime/nvram/flash", xmldb_buff, sizeof(xmldb_buff)-1);
		bdflag0=atoi(xmldb_buff);

#ifdef B_ENDIAN
		imgflag0 = ((block->flag[0]&0xff000000)>>24)|
		           ((block->flag[0]&0x00ff0000)>>8)|
		           ((block->flag[0]&0x0000ff00)<<8)|
		           ((block->flag[0]&0x000000ff)<<24);
#else
		imgflag0 = block->flag[0];
#endif /*B_ENDIAN*/

		DPRINTF("imgflag0: %x\n", imgflag0);
		
		if(bdflag0 > imgflag0)
		{
			DPRINTF("New board can't support old firmware\n");
			break;
		}
#endif /*ELBOX_FIRMWARE_FLASH_SP_MX*/

		if (offset + sizeof(imgblock_tv3) + block->size > size)
		{
			DPRINTF("Size out of boundary !\n");
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
			DPRINTF("MD5 digest mismatch !\n");
			DPRINTF("digest caculated : "); DBYTES(digest, 16);
			DPRINTF("digest in header : "); DBYTES(block->digest, 16);
			break;
		}


		/* move to next block */
		offset += sizeof(imgblock_tv3);
		offset += block->size;

		DPRINTF("Advance to next block : offset=%d(0x%x), size=%d(0x%x)\n", offset, offset, size, size);
	}
	if (offset == size) return 0;


	DPRINTF("illegal block found at offset %d (0x%x)!\n", offset, offset);
	DPRINTF("  offset (%d) : \n", offset); DBYTES((unsigned char *)block, 16);

	return -1;
}
#endif /*ELBOX_FIRMWARE_HEADER_VERSION_CONTROL*/

static int v2_image_check(const char * image, int size)
{
	imghdr2_t * v2hdr = (imghdr2_t *)image;
	unsigned char signature[MAX_SIGNATURE];
	int i;
	if (v2hdr && size > sizeof(imghdr2_t) && v2hdr->magic == _cpu_to_le(IMG_V2_MAGIC_NO))
	{
		/* check if the signature match */
		DPRINTF("check image signature !\n");

		memset(signature, 0, sizeof(signature));
		strncpy(signature, g_signature, sizeof(signature));

		DPRINTF("  expected signature : [%s]\n", signature);
		DPRINTF("  image signature    : [%s]\n", v2hdr->signature);

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

			DPRINTF("  try this signature : [%s]\n", signature);

			if (strcmp(signature, v2hdr->signature) == 0)
				return v2_check_image_block(image, size);
		}
	}
	return -1;
}

#ifdef ELBOX_FIRMWARE_HEADER_VERSION_CONTROL
static int v3_image_check(const char * image, int size)
{
	imghdr2_t * v2hdr = (imghdr2_t *)image;
	unsigned char signature[MAX_SIGNATURE];
	int i;
	if (v2hdr && size > sizeof(imghdr2_t) && v2hdr->magic == _cpu_to_le(IMG_V3_MAGIC_NO))
	{
		/* check if the signature match */
		DPRINTF("check image signature !\n");

		memset(signature, 0, sizeof(signature));
		strncpy(signature, g_signature, sizeof(signature));

		DPRINTF("  expected signature : [%s]\n", signature);
		DPRINTF("  image signature    : [%s]\n", v2hdr->signature);

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

			DPRINTF("  try this signature : [%s]\n", signature);

			if (strcmp(signature, v2hdr->signature) == 0)
				return v3_check_image_block(image, size);
		}
	}
	return -1;
}
#endif ELBOX_FIRMWARE_HEADER_VERSION_CONTROL

static int v2_burn_image(const char * image, int size)
{
	int offset = sizeof(imghdr2_t);
	imgblock_t * block;
	imghdr2_t headcheck;
	FILE * fh;

	DPRINTF("v2_burn_image >>>>\n");

	while (offset < size)
	{
		block = (imgblock_t *)&image[offset];

		DPRINTF("burning image block.\n");
		DPRINTF("  size    : %d (0x%x)\n", (unsigned int)block->size, (unsigned int)block->size);
		DPRINTF("  devname : %s\n", block->devname);
		DPRINTF("  offset  : %d (0x%x)\n", (unsigned int)block->offset, (unsigned int)block->offset);
	    
	    //joel add ,before we write the mtd block ,umout first,some kernel can not write when device busy
		{
			char umount_buff[256];
			sprintf(umount_buff,"umount %s",block->devname);
			system(umount_buff);
		}
#if 1
		fh = fopen(block->devname, "w+");
		if (fh == NULL)
		{
 /* papa add start for syslog 2007/03/30 */
#if ELBOX_PROGS_GPL_SYSLOGD_AP
			syslog(ALOG_AP_SYSACT|LOG_WARNING,"[SYSACT]Fail to write file!");
#endif
 /* papa add end for syslog 2007/03/30 */
			DPRINTF("Failed to open device %s\n", block->devname);
			return -1;
		}
#if 1//joel auto check the header in flash,we can not handle the offset non zero....
		if(fread(&headcheck,sizeof(imghdr2_t),1,fh) && headcheck.magic == _cpu_to_le(IMG_V2_MAGIC_NO) && block->offset==0)
		{
            fseek(fh, block->offset, SEEK_SET);
			DPRINTF("head in flash\n");
			//write header 1
			fwrite((const void *)image, 1, sizeof(imghdr2_t), fh);
			//write header 2
			fwrite((const void *)&block[0], 1, sizeof(imgblock_t), fh);
		}
		else
#endif
		{
		   DPRINTF("No header in images\n");
		   fseek(fh, block->offset, SEEK_SET);
		}
		fwrite((const void *)&block[1], 1, block->size, fh);
		fclose(fh);
#endif
 /* papa add start for syslog 2007/03/30 */
#if ELBOX_PROGS_GPL_SYSLOGD_AP
		syslog(ALOG_AP_SYSACT|LOG_NOTICE,"[SYSACT]Firmware update success");
#endif
 /* papa add end for syslog 2007/03/30 */
#ifdef ELBOX_PROGS_GPL_NET_SNMP
//sendtrap("[SNMP-TRAP][Specific=12]");
#endif
		DPRINTF("burning done!\n");

		/* move to next block */
		offset += sizeof(imgblock_t);
		offset += block->size;
	}
	upload_file.flag = 0;

	return 0;
}

#ifdef ELBOX_FIRMWARE_HEADER_VERSION_CONTROL
static int v3_burn_image(const char * image, int size)
{
	int offset = sizeof(imghdr2_t);
	imgblock_tv3 * block;
	imghdr2_t headcheck;
	FILE * fh;

	DPRINTF("v3_burn_image >>>>\n");

	while (offset < size)
	{
		block = (imgblock_tv3 *)&image[offset];

		DPRINTF("burning image block.\n");
		DPRINTF("  size    : %d (0x%x)\n", (unsigned int)block->size, (unsigned int)block->size);
		DPRINTF("  devname : %s\n", block->devname);
		DPRINTF("  offset  : %d (0x%x)\n", (unsigned int)block->offset, (unsigned int)block->offset);

		//joel add ,before we write the mtd block ,umout first,some kernel can not write when device busy
		{
			char umount_buff[256];
			sprintf(umount_buff,"umount %s",block->devname);
			system(umount_buff);
		}
#if 1
		fh = fopen(block->devname, "w+");
		if (fh == NULL)
		{
 /* papa add start for syslog 2007/03/30 */
#if ELBOX_PROGS_GPL_SYSLOGD_AP
			syslog(ALOG_AP_SYSACT|LOG_WARNING,"[SYSACT]Fail to write file!");
#endif
 /* papa add end for syslog 2007/03/30 */
			DPRINTF("Failed to open device %s\n", block->devname);
			return -1;
		}
#if 1//joel auto check the header in flash,we can not handle the offset non zero....
		if(fread(&headcheck,sizeof(imghdr2_t),1,fh) && headcheck.magic == _cpu_to_le(IMG_V3_MAGIC_NO) && block->offset==0)
		{
        	fseek(fh, block->offset, SEEK_SET);
			DPRINTF("head in flash\n");
			//write header 1
			fwrite((const void *)image, 1, sizeof(imghdr2_t), fh);
			//write header 2
			fwrite((const void *)&block[0], 1, sizeof(imgblock_tv3), fh);
		}
		else
#endif
		{
			DPRINTF("No header in images\n");
			fseek(fh, block->offset, SEEK_SET);
		}
		fwrite((const void *)&block[1], 1, block->size, fh);
		fclose(fh);
#endif
 /* papa add start for syslog 2007/03/30 */
#if ELBOX_PROGS_GPL_SYSLOGD_AP
		syslog(ALOG_AP_SYSACT|LOG_NOTICE,"[SYSACT]Firmware update success");
#endif
 /* papa add end for syslog 2007/03/30 */
#ifdef ELBOX_PROGS_GPL_NET_SNMP
//sendtrap("[SNMP-TRAP][Specific=12]");
#endif
		DPRINTF("burning done!\n");

		/* move to next block */
		offset += sizeof(imgblock_tv3);
		offset += block->size;
	}
	upload_file.flag = 0;

	return 0;
}
#endif /*ELBOX_FIRMWARE_HEADER_VERSION_CONTROL*/

static int burn_image(const char * image, int size)
{
	FILE * fh;

	DPRINTF("burn_image >>>>\n");
	fh = fopen("/dev/mtdblock/1", "w+");
	if (fh == NULL)
	{
 /* papa add start for syslog 2007/03/30 */
#if ELBOX_PROGS_GPL_SYSLOGD_AP
			syslog(ALOG_AP_SYSACT|LOG_WARNING,"[SYSACT]Fail to write file!");
#endif
 /* papa add end for syslog 2007/03/30 */
		DPRINTF("Failed to open device %s\n", "/dev/mtdblock/1");
		return -1;
	}
	fwrite((const void *)image, 1, size, fh);
	fclose(fh);
 /* papa add start for syslog 2007/03/30 */
#if ELBOX_PROGS_GPL_SYSLOGD_AP
	syslog(ALOG_AP_SYSACT|LOG_NOTICE,"[SYSACT]Firmware update success");
#endif
 /* papa add end for syslog 2007/03/30 */
#ifdef ELBOX_PROGS_GPL_NET_SNMP
//sendtrap("[SNMP-TRAP][Specific=12]");
#endif
	DPRINTF("burning done!\n");

	upload_file.flag = 0;

	return 0;
}

#include "xmldb.h"
#include "libxmldbc.h"
#include <libgen.h>

int upload_image(struct request *r, struct pool *p)
{
#ifdef ELBOX_PROGS_PRIV_CLI_SUPER
    char xmldb_buff[10];
#endif /*ELBOX_PROGS_PRIV_CLI_SUPER*/
	DPRINTF("formUpload\n");
/* papa add start for syslog 2007/03/30 */
#if ELBOX_PROGS_GPL_SYSLOGD_AP
	if((upload_file.file_ptr == NULL)||(upload_file.file_length == 0))
	{
		syslog(ALOG_AP_SYSACT|LOG_WARNING,"[SYSACT]Fail to get the file, please check the IP address and check the file name.");
	}
#endif
 /* papa add end for syslog 2007/03/30 */
	/* check v2 image first. */
#ifdef ELBOX_PROGS_PRIV_CLI_SUPER
    memset(xmldb_buff, 0x0, sizeof(xmldb_buff));
    xmldbc_get_wb(NULL, 0, "/runtime/sys/super", xmldb_buff, sizeof(xmldb_buff)-1);
    if(atoi(xmldb_buff)==1){
        int		len=upload_file.file_length/1024;
		char	cmd[256];

		DPRINTF("Without checking image, sending message!\n");
		DPRINTF("Prepare burning image!\n");
		sprintf(cmd, "rgdb -i -s /runtime/sys/fw_size '%d'", len);
		system(cmd);

		rlt_page(p, r->c->info_fwrestart_file);
		sync_time();
		upload_file.flag=1;
		upload_file.uptime=current_uptime;
		return 0;
    }
#endif /*ELBOX_PROGS_PRIV_CLI_SUPER*/
#ifdef ELBOX_FIRMWARE_HEADER_VERSION_CONTROL
    if(ELBOX_FIRMWARE_HEADER_VERSION == 3){
    	if (v3_image_check(upload_file.file_ptr, upload_file.file_length)==0)
	    {
		    int		len=upload_file.file_length/1024;
		    char	cmd[256];

    		DPRINTF("V3 image checked, sending message!\n");
	    	DPRINTF("Prepare burning V3 image!\n");
		    sprintf(cmd, "rgdb -i -s /runtime/sys/fw_size '%d'", len);
    		system(cmd);

            rlt_page(p, r->c->info_fwrestart_file);
            sync_time();
    		upload_file.flag=1;
	    	upload_file.uptime=current_uptime;
		    return 0;
	    }
    }else{
    	if (v2_image_check(upload_file.file_ptr, upload_file.file_length)==0)
	    {
		    int		len=upload_file.file_length/1024;
		    char	cmd[256];

    		DPRINTF("V2 image checked, sending message!\n");
	    	DPRINTF("Prepare burning V2 image!\n");
		    sprintf(cmd, "rgdb -i -s /runtime/sys/fw_size '%d'", len);
    		system(cmd);

            rlt_page(p, r->c->info_fwrestart_file);
            sync_time();
    		upload_file.flag=1;
	    	upload_file.uptime=current_uptime;
		    return 0;
	    }
    }
#else
	if (v2_image_check(upload_file.file_ptr, upload_file.file_length)==0)
	{
		int		len=upload_file.file_length/1024;
		char	cmd[256];

		DPRINTF("V2 image checked, sending message!\n");
		DPRINTF("Prepare burning V2 image!\n");
		sprintf(cmd, "rgdb -i -s /runtime/sys/fw_size '%d'", len);
		system(cmd);

        rlt_page(p, r->c->info_fwrestart_file);
        sync_time();
		upload_file.flag=1;
		upload_file.uptime=current_uptime;
		return 0;
	}
#endif /*ELBOX_FIRMWARE_HEADER_VERSION_CONTROL*/
/* papa add start for syslog 2007/03/30 */
#if ELBOX_PROGS_GPL_SYSLOGD_AP
	syslog(ALOG_AP_SYSACT|LOG_WARNING,"[SYSACT]Image file is not acceptable. Please check download file is right.");
#endif
 /* papa add end for syslog 2007/03/30 */
	rlt_page(p, r->c->error_fwup_file);

	DPRINTF("formUpload done!\n");

	return -1;
}

int upload_config(struct request *r, struct pool *p)
{
	char *pInput=upload_file.file_ptr;
	FILE *pFile;
	int  filelen=0;
	if (!strncasecmp(pInput, g_signature, strlen(g_signature)))
	{
		filelen=strlen(g_signature)+1;
		pInput+=filelen;
		filelen=upload_file.file_length-filelen;
		if((pFile=fopen("/var/config.bin","w")))
		{
			fwrite(pInput, 1, filelen, pFile);
			fclose(pFile);
			system("/etc/scripts/misc/profile.sh reset /var/config.bin");
			rlt_page(p, r->c->info_cfgrestart_file);
			sync_time();
			upload_file.flag=2;
			upload_file.uptime=current_uptime;
			return 0;
		}
	}
	rlt_page(p, r->c->error_cfgup_file);
	return -1;
}

void check_upgrad()
{
	FILE *pFile=NULL;
	int   reboot_inRam=0;
#ifdef ELBOX_PROGS_PRIV_CLI_SUPER
        char xmldb_buff[1024];
#endif /*ELBOX_PROGS_PRIV_CLI_SUPER*/
	if (current_uptime - upload_file.uptime<4) return;
	system("/etc/scripts/misc/haltdemand.sh");
//+++joel add for the Image upgrade the flash is changed,the file system is wrap ,so the reboot need copy to ram first.
	if(access("/usr/sbin/reboot",X_OK)==0)
	{
		system("cp /usr/sbin/reboot /var/reboot");
		reboot_inRam = 1;
	}
	else if(access("/bin/reboot",X_OK)==0)
	{
		system("cp /bin/reboot /var/reboot");
		reboot_inRam = 1;
	}
	else if(access("/sbin/reboot",X_OK)==0)
	{
		system("cp /sbin/reboot /var/reboot");
		reboot_inRam = 1;
	}
	else
		reboot_inRam = 0;
//---	

	switch (upload_file.flag)
	{
	case 1:	//-----Upload Image
#ifdef ELBOX_PROGS_PRIV_CLI_SUPER
        memset(xmldb_buff, 0x0, sizeof(xmldb_buff));
        xmldbc_get_wb(NULL, 0, "/runtime/sys/super", xmldb_buff, sizeof(xmldb_buff)-1);
        if(atoi(xmldb_buff)==1){
            burn_image(upload_file.file_ptr, upload_file.file_length);
        }else{
#endif /*ELBOX_PROGS_PRIV_CLI_SUPER*/
#ifdef ELBOX_FIRMWARE_HEADER_VERSION_CONTROL
        if (ELBOX_FIRMWARE_HEADER_VERSION == 3){
            v3_burn_image(upload_file.file_ptr, upload_file.file_length);
        }else{
            v2_burn_image(upload_file.file_ptr, upload_file.file_length);
        }
#else
		v2_burn_image(upload_file.file_ptr, upload_file.file_length);
#endif /*ELBOX_FIRMWARE_HEADER_VERSION_CONTROL*/
#ifdef ELBOX_PROGS_PRIV_CLI_SUPER
        }
#endif /*ELBOX_PROGS_PRIV_CLI_SUPER*/
		break;
	case 2:	//-----Upload Config
		system("/etc/scripts/misc/profile.sh put");
		upload_file.flag = 0;//yes we have done
		break;
	}
	if((pFile=fopen("/proc/driver/system_reset", "r+")))
	{
		fprintf(pFile, "1\n");
		fclose(pFile);
	}
	else if(reboot_inRam)
		system("/var/reboot");
	else
		system("reboot");
}
#ifdef ELBOX_PROGS_GPL_MATHOPD_EXTERNAL_FILE
int upload_certificate(struct request *r, struct pool *p, int iflag)
{
	FILE *pFile;
	char *pInput=upload_file.file_ptr;
	char *pName=upload_file.file_name;
	char *filename=NULL,str[100];
	int filelen = upload_file.file_length;

	if(filename = strrchr(pName,'\\'))
	{
		if(filename)	filename++;
	}
	else if(filename = strrchr(pName,'/'))
	{
		if(filename)	filename++;
	}
	else
	{
		filename = pName;
	}

	mkdir("/var/certificate",0755);
	sprintf(str,"/var/certificate/%s",filename);
	if((pFile=fopen(str,"w")))
	{
		fwrite(pInput, 1, filelen, pFile);
		fclose(pFile);

		rlt_page(p, "/www/sys/redir_8021x.htm");
		sync_time();
		upload_file.flag=0;
		upload_file.uptime=current_uptime;

		FILE *fd;
		char cmd[256],ori_path[64], alt_path[64];
		if (iflag==TYPE_CERTIFICATE)
		{
			if ((fd=popen("rgdb -g /w8021x/certificate", "r")))
			{
				memset( ori_path, 0, sizeof(ori_path) );
				fscanf(fd,"%s",ori_path);
				fclose(fd);
			}
			if ((fd=popen("rgdb -g /w8021x/pri_key", "r")))
			{
				memset( alt_path, 0, sizeof(alt_path) );
				fscanf(fd,"%s",alt_path);
				fclose(fd);
			}
			sprintf(cmd, "rgdb -s /w8021x/certificate '%s'", filename);
		}
		else if (iflag==TYPE_PRIVATE_KEY)
		{
			if ((fd=popen("rgdb -g /w8021x/pri_key", "r")))
			{
				memset( ori_path, 0, sizeof(ori_path) );
				fscanf(fd,"%s",ori_path);
				fclose(fd);
			}
			if ((fd=popen("rgdb -g /w8021x/certificate", "r")))
			{
				memset( alt_path, 0, sizeof(alt_path) );
				fscanf(fd,"%s",alt_path);
				fclose(fd);
			}
			sprintf(cmd, "rgdb -s /w8021x/pri_key '%s'", filename);
		}
		else // (iflag==TYPE_CA)
		{
			if ((fd=popen("rgdb -g /w8021x/ca", "r")))
			{
				memset( ori_path, 0, sizeof(ori_path) );
				fscanf(fd,"%s",ori_path);
				fclose(fd);
			}
			sprintf(cmd, "rgdb -s /w8021x/ca '%s'", filename);
		}
		//to set filename on rgdb and save
		strcat(cmd,";submit COMMIT");
		system(cmd);
		//to remove old file from /var/certificate/ path
		if(ori_path[0]!='\0' && strcmp(filename,ori_path)!= 0 && strcmp(ori_path,alt_path)!= 0)
		{
			sprintf(cmd, "rm -f '/var/certificate/%s'", ori_path);
			system(cmd);
		}
		//to save /var/certificate/ to mtd block
		sprintf(cmd, "sh /etc/scripts/misc/profile_ca.sh put %s", filename);
		system(cmd);
	}

	return -1;
}
#endif

#ifdef ELBOX_PROGS_GPL_MATHOPD_EXTERNAL_FILE
#ifndef BUFSIZ
#define BUFSIZ 1024
#endif

//ssize_t xmldbc_ephp_wb(sock_t sn, flag_t f, const char * file, char * buff, size_t size)
void redirect_page(struct pool *p, char *page)
{
	char *buf = NULL;
	size_t n = 0;
	int r = 0;

	if((buf=calloc(1,BUFSIZ)) == NULL) goto red_err;

	xmldbc_ephp_wb(NULL, XMLDB_EPHP, page, buf, BUFSIZ);

	if(p->ceiling <= p->end) return (void)0;

	n = p->ceiling - p->end;
	if((r=strlen(buf))>n)
	{
		memcpy(p->end, buf ,n);
		p->end+=n;
		goto red_err;
	}
	memcpy(p->end, buf, r);
	p->end+=r;

	return (void)0;
red_err:
	DPRINTF("%s: %s\n", __FUNCTION__, strerror(errno));
	if(buf) free(buf);
	exit(-1);
}

struct _ext_file_ {
	char *service;
	char *path;
	char *filename;
	char *process_page;
	char *error_page;
} ext_file[] = {
	{"none", "/var/mnt", "ca.pem", NULL, NULL},
	{"none", "/var/mnt", "cert.pem", NULL, NULL},
	{"none", "/var/mnt", "asdf.pem",  NULL, NULL},
#ifdef ELBOX_PROGS_GPL_STUNNEL_EXTERNAL_CERTIFICATE
	{"stunnel_cert", ELBOX_PROGS_GPL_STUNNEL_CPATH, ELBOX_PROGS_GPL_STUNNEL_CERTNAME, "sys_stunnel_process.php", "sys_stunnel_error.php"},
	{"stunnel_key",  ELBOX_PROGS_GPL_STUNNEL_CPATH, ELBOX_PROGS_GPL_STUNNEL_KEYNAME, "sys_stunnel_process.php?reboot=1","sys_stunnel_error.php"},
#else
	{"none", NULL, "none", NULL, NULL},
	{"none", NULL, "none", NULL, NULL},
#endif
	{"none", NULL, "none", NULL, NULL}
};

int upload_ext_file(struct request *r, struct pool *p, int iflag)
{
	char *buf = NULL;
	FILE *file = NULL;

	if((buf=calloc(1,BUFSIZ)) == NULL) goto up_err;
	DPRINTF("[%s]: calloc(1,%d)\n", __FUNCTION__, BUFSIZ);

	/* we maybe need to redirect to a warning page in this situation */
	if(ext_file[iflag].path == NULL) goto up_end;
	sprintf(buf, "mkdir -p %s", ext_file[iflag].path);
	system(buf);

	memset(buf, 0, BUFSIZ);
	if(strcmp(ext_file[iflag].filename,"none") == 0)
		sprintf(buf, "%s/%s", ext_file[iflag].path, strrchr(upload_file.file_name,'\\') + 1);
	else
		sprintf(buf, "%s/%s", ext_file[iflag].path, ext_file[iflag].filename);

	if((file=fopen(buf, "r")))
	{
		fclose(file);
		unlink(buf);
	}

	DPRINTF("write to file:\n\t%s ", buf);

	if((file=fopen(buf, "wb")) != NULL)
	{
		char *tmp = (char *)calloc(1,BUFSIZ);
		if(tmp == NULL) goto up_err;
		sprintf(tmp, "rgdb -i -s /runtime/web/upload_filename %s", basename(buf));
		system(tmp);
		free(tmp);

		memset(buf, 0, BUFSIZ);
		sprintf(buf, "rgdb -i -s /runtime/web/redirect_next_page %s", ext_file[iflag].process_page);
		system(buf);
		redirect_page(p, "/www/sys/redirectlink.php");

		DPRINTF(" with length %d.\n", upload_file.file_length);
		fwrite(upload_file.file_ptr, upload_file.file_length, 1, file);
		fclose(file);

		memset(buf, 0, BUFSIZ);
		sprintf(buf, "rgdb -i -s /runtime/web/upload_service %s", ext_file[iflag].service);
		system(buf);

		system("/etc/templates/upload.sh");
		DPRINTF("[%s#%d]: %s(code %d)\n", __FUNCTION__, __LINE__, strerror(errno), errno);

		//sync_time();
		upload_file.flag = 0;
		upload_file.uptime = current_uptime;

		if(buf) free(buf);
		return 0;
	}
	else
	{
		DPRINTF("[%s#%d]: %s(code %d)\n", __FUNCTION__, __LINE__, strerror(errno), errno);
		;
	}

up_err:
	memset(buf, 0, BUFSIZ);
	sprintf(buf, "rgdb -i -s /runtime/web/redirect_next_page %s", ext_file[iflag].error_page);
	system(buf);
	redirect_page(p, "/www/sys/redirectlink.php");
	DPRINTF("[%s#%d]: %s(code %d)\n", __FUNCTION__, __LINE__, strerror(errno), errno);
	if(file) fclose(file);
up_end:
	if(buf) free(buf);
	return -1;
}
#endif

#ifdef ELBOX_PROGS_GPL_MATHOPD_EXTERNAL_BT_FILE
/*  This function must depend on bittorrent-sdk-dir685-v2_0/bin/bt,
 *  and upload torrent file to the bt server, the bt server process automation,
 *  host use 'localhost' and port use 63521.
 *  other function (e.g. torrents-get...) has called btcgi(alpha_bt).
 */
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>

#define HOST            "127.0.0.1"
#define PORT            63521
#define MAX_BUFFER_SIZE	2048
#define MAX_WAIT_TIME	3

static char *	o_host = HOST;
static int		o_port = PORT;
static int	 	o_time = MAX_WAIT_TIME;

static int connect_host(void)
{
 	fd_set write_fd;
	socklen_t optlen = sizeof(int);
	struct timeval tv;
	int fd, option, flags;
	struct sockaddr_in sa;
	struct hostent *he;
	
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(fd < 0)
	{
		return -1;
	}
	if((he=gethostbyname(o_host))==NULL)
	{
		return -1;
	}
	memset(&sa, 0, sizeof(sa));
    sa.sin_family       = AF_INET;
    sa.sin_port         = htons(o_port);
    sa.sin_addr.s_addr  = *((unsigned long *)he->h_addr);
	flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	if (connect(fd, (struct sockaddr *)&sa, sizeof(struct sockaddr)) == -1)
    {
		if (errno == EINPROGRESS)
        {
			FD_ZERO(&write_fd);
            FD_SET(fd, &write_fd);
            tv.tv_sec = o_time;
            tv.tv_usec = 0;
            if (select(fd+1, NULL, &write_fd, NULL, &tv) > 0)
            {
            	if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &option, &optlen)==0)
                {
                	if (option == 0)
                    {
                    	flags = fcntl(fd, F_GETFL);
                        fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);
                        return fd;
                    }
                }
            }
			close(fd);
			fd =0;
			//d_info("%s: Can not connect to %s:%d\n",__FUNCTION__,o_host, o_port);
			return -1;
		}
	}
	
   return 0;
}

int upload_bt_torrent(struct request *r)
{
	char *pData=upload_file.data;
	char *pBoundary=r->multi_boundary;
	int data_length=upload_file.length;
	char buf[1024];
	int s[2],status,cmd_len=0;
	pid_t pid;
	struct pool *p=&r->cn->output;

	log_d("r->url:%s,r->multi_boundary=%s\n",r->url,r->multi_boundary);
	log_d("upload_file.length:%d\n",upload_file.length);
	log_d("upload_file.data:%s\n",upload_file.data);
	
	if (r->args)
		cmd_len=sprintf(buf, "POST %s?%s HTTP/1.1\r\n", r->url,r->args);
	else
		cmd_len=sprintf(buf, "POST %s HTTP/1.1\r\n", r->url);
	cmd_len+=sprintf(buf+cmd_len, "Accept: */*\r\nHost: %s\r\nKeep-Alive: 300\r\nConnection: keep-alive\r\n", o_host);
	cmd_len+=sprintf(buf+cmd_len, "Content-Type: multipart/form-data; boundary=%s\r\nContent-Length: %d\r\n\r\n", pBoundary, data_length);
	log_d("buf=%s=\n",buf);

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, s) == -1)
		return -1;
	if((pid=fork())==-1)
	{
		//failed
		log_d("fork error:%s\n",strerror(errno));
		return -1;
	}
	else if(pid==0)
	{
		int fd,client_size;
		char c_readbuf[DEFAULT_INPUT_BUF_SIZE];
		fd_set read_fd;
		struct timeval tv;
		
		close(s[0]);//server uses s[1],so there is no usage.
		
		if ((fd=connect_host()) < 0) return -1;
		
		client_size = send(fd, buf, cmd_len, 0);
		client_size = send(fd, pData, data_length, 0);
		
		FD_ZERO(&read_fd);
	    FD_SET(fd, &read_fd);
	    tv.tv_sec = o_time;
	    tv.tv_usec = 0;
	    if (select(fd+1, &read_fd, NULL, NULL, &tv) > 0)
	    {
			if(FD_ISSET(fd, &read_fd))
			{
				if((client_size = read( fd, c_readbuf, sizeof(c_readbuf)))>1)
				{
					client_size = write( s[1], c_readbuf, client_size);
				}
			}
		}
		
		if(shutdown(s[1],SHUT_WR)==-1)
		{
			log_d("shutdown ShUT_WR error:%s\n",strerror(errno));
			return -1;
		}
		close(fd);
		close(s[1]);
		_exit(0);
	}
	else
	{
		char p_readbuf[DEFAULT_INPUT_BUF_SIZE];
		int parent_size,pfd;
		fd_set read_fd;
		struct timeval tv;
		
		close(s[1]);
		
		pfd=s[0];
		FD_ZERO(&read_fd);
	    FD_SET(pfd, &read_fd);
	    tv.tv_sec = o_time*2;
	    tv.tv_usec = 0;
		if (select(pfd+1, &read_fd, NULL, NULL, &tv) > 0)
	    {
			if(FD_ISSET(pfd, &read_fd))
			{
				if((parent_size=read(pfd,p_readbuf,sizeof(p_readbuf)))>0)
				{
					rlt_recvbuf(p,p_readbuf,parent_size);
				}
			}
		}
		close(s[0]);
		wait(&status);
	}
	return -1;
}
#endif

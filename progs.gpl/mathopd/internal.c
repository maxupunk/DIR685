/*------------------------------*/
/* vi: set sw=4 ts=4: */
/* Added by Paul Liu 20040326 */
/* Process Internal Call */
/*------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mathopd.h"

extern upload upload_file;

extern int  pool_print(struct pool *p, const char *fmt, ...);
extern int  upload_image(struct request *r, struct pool *p);
extern int  upload_config(struct request *r, struct pool *p);
#ifdef ELBOX_PROGS_GPL_MATHOPD_EXTERNAL_FILE
extern int  upload_certificate(struct request *r, struct pool *p, int iflag);
extern int upload_ext_file(struct request *r, struct pool *p, int iflag);
#endif
#ifdef ELBOX_PROGS_GPL_MATHOPD_EXTERNAL_BT_FILE
extern int  upload_bt_torrent(struct request *r);
extern void rlt_recvbuf(struct pool *p, char *pStr, size_t size);
#endif
extern void rlt_page(struct pool *p, char *pFName);

int process_internal(struct request *r)
{
	int  rlt=-1;
	char Name[128]={0};
	char *pArgs=r->path_translated+strlen(r->path_translated);
	char *pEnd=NULL;
	struct pool *p=NULL;

	while(--pArgs>r->path_translated && *(pArgs-1)!='/');

	if ((pEnd=strchr(pArgs, '.'))) *pEnd=0;

#ifdef ELBOX_PROGS_GPL_MATHOPD_EXTERNAL_BT_FILE
	/* +++ Teresa Ke, for bt add torrent file. */
	if (0==Name[0] || !strncmp(r->user, Name, strlen(r->user)))
	{
		if(!strncasecmp(pArgs, "torrent-add", 11))
		{
			rlt=upload_bt_torrent(r);
			if(upload_file.data) free(upload_file.data);
			memset(&upload_file, 0, sizeof(upload_file));
			//-----Restore service
			system("/etc/scripts/misc/preupgrade.sh restore");
			return 0;
		}
	}
#endif

	p=&r->cn->output;
	pool_print(p, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n");
	r->forked=1;
	r->cn->keepalive=0;

	if (0==Name[0] || !strncmp(r->user, Name, strlen(r->user)))
	{
		if(!strncasecmp(pArgs, "upload_image", 12))
			rlt=upload_image(r, p);
		else if(!strncasecmp(pArgs, "upload_config", 13))
			rlt=upload_config(r, p);
#ifdef ELBOX_PROGS_GPL_MATHOPD_EXTERNAL_FILE
		else if(!strncasecmp(pArgs, "upload_ca", 9))
			rlt=upload_certificate(r, p, TYPE_CA);
		else if(!strncasecmp(pArgs, "upload_certificate", 18))
			rlt=upload_certificate(r, p, TYPE_CERTIFICATE);
		else if(!strncasecmp(pArgs, "upload_privatekey", 17))
			rlt=upload_certificate(r, p, TYPE_PRIVATE_KEY);
		else if(!strncasecmp(pArgs, "upload_stunnel_cert", 19))
			rlt=upload_ext_file(r, p, TYPE_STUNNEL_CERT);
		else if(!strncasecmp(pArgs, "upload_stunnel_key", 18))
			rlt=upload_ext_file(r, p, TYPE_STUNNEL_KEY);
#endif
		else
			rlt_page(p, r->c->error_fwup_file);
	}

	//-----CleanUp Memory
	if(rlt<0)
	{
		if(upload_file.data) free(upload_file.data);
		memset(&upload_file, 0, sizeof(upload_file));
		//-----Restore service
		system("/etc/scripts/misc/preupgrade.sh restore");
	}

	return 0;
}

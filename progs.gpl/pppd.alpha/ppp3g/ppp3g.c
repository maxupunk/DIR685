/* vi: set sw=4 ts=4: */

/***********************************************************************
*
* ppp3g.c
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/wait.h>

#include "ppp3g.h"
#include "ppp_fcs.h"
#include "eloop.h"
#include "dtrace.h"
#include "pppd.h"

#include "pathnames.h"

static int chat_script(char *, int, int );


static int conn_running;				/* we have a [dis]connector running */

/* function located in chat.c for porcessing the script */
extern int do_file(char *, int );

extern void modem_hungup(void);
extern int hungup;
extern uid_t uid;
extern mode_t tty_mode;
//extern int fd_devnull;

int *real_ttyfd;				/* fd for actual serial port (not pty) */
extern int pty_pid;

static int chat_script(char * program, int ttyfd, int dont_wait)
{
	int pid;
	int status = -1;
	int errfd;

	++conn_running;
#ifdef EMBED
	pid = vfork();
#else
	pid = safe_fork();
#endif
	printf("After the fork Pid = %d\n", pid);
	if (pid < 0)
	{
		--conn_running;
		error("Failed to create child process: %m");
		return -1;
    }

	if (pid != 0)
	{
		if (dont_wait)
		{
//#ifndef EMBED
			record_child(pid, program, NULL, NULL);
//#endif
			fprintf(stderr, "pppd: %s %d\n", program, pid);
			pty_pid = pid; //what is this for?
			status = 0;
		}
		else
		{
			while (waitpid(pid, &status, 0) < 0)
			{
				if (errno == EINTR) continue;
				fatal("error waiting for (dis)connection process: %m");
			}
			--conn_running;
		}
		printf("before exiting\n");
		return (status == 0 ? 0 : -1);
	}

    /* here we are executing in the child */
    
    /* dup log_to_fd to 2 for debug printing */
	printf( "log_to_fd = %d\n", log_to_fd );
	errfd = dup(log_to_fd);
	close( log_to_fd );
	close(2);
	dup2(errfd, 2);
	close(errfd);

	setuid(uid);
	if (getuid() != uid)
	{
		error("setuid failed");
		exit(1);
	}
	setgid(getgid());

	fprintf(stderr,"program equals to: %s\n", program );
	if( do_file( program, ttyfd ) == 0 )
    	return 0;
    else
    {	
    	fprintf(stderr,"chat.c failed \n");
    	return 1;
    }	

}

int ppp3g_module_connect(int *tty_fd, char *connector)
{
	real_ttyfd = tty_fd;
	int fdflags;
	struct stat statbuf;
	int ttyfd;				/* Serial port file descriptor */
	
	if (devnam[0] != 0) {
		for (;;) {
			/* Become the user before opening the Device. */
			int err;
			
			//seteuid(uid);
			ttyfd = open(devnam, O_NONBLOCK | O_RDWR, 0);
			err = errno;
			//seteuid(0);
			if (ttyfd >= 0)
				break;
			errno = err;
			if (err != EINTR) {
				error("Failed to open %s: %m", devnam);
				status = EXIT_OPEN_FAILED;
			}
			if (!persist || err != EINTR)
				return -1;
		}
		*real_ttyfd = ttyfd;
		printf("real ttyfd becomes %d\n", *real_ttyfd );
		if ((fdflags = fcntl(ttyfd, F_GETFL)) == -1 || fcntl(ttyfd, F_SETFL, fdflags & ~O_NONBLOCK) < 0)
			warn("Couldn't reset non-blocking mode on device: %m");

		/*
		 * Do the equivalent of `mesg n' to stop broadcast messages.
		 */
		if (fstat(ttyfd, &statbuf) < 0 || fchmod(ttyfd, statbuf.st_mode & ~(S_IWGRP | S_IWOTH)) < 0) 
			warn("Couldn't restrict write permissions to %s: %m", devnam);
		else
			tty_mode = statbuf.st_mode;

		/*
		 * Set line speed, flow control, etc.
		 * If we have a non-null connection or initializer script,
		 * on most systems we set CLOCAL for now so that we can talk
		 * to the modem before carrier comes up.  But this has the
		 * side effect that we might miss it if CD drops before we
		 * get to clear CLOCAL below.  On systems where we can talk
		 * successfully to the modem with CLOCAL clear and CD down,
		 * we could clear CLOCAL at this point.
		 */
		printf("set up tty!!\n");
		set_up_tty(ttyfd, (ppp3g_chat_file != NULL && ppp3g_chat_file[0] != 0));
		printf("finish tty set up!!\n");
	}
	
		/* run connection script */
	printf("connection script!!\n");
	if (pty_module == 3 && (ppp3g_chat_file != NULL && ppp3g_chat_file[0] != 0))
	{
		if (*real_ttyfd != -1) 
		{
			/* XXX do this if doing_callback == CALLBACK_DIALIN? */
			if (!default_device && modem) 
			{
				setdtr(*real_ttyfd, 0);	/* in case modem is off hook */
				sleep(1);
				setdtr(*real_ttyfd, 1);
				printf("modem = %d\n", modem );
				printf("default_device = %d", default_device );
			}
		}
		if (ppp3g_chat_file && ppp3g_chat_file[0]) 
		{
			fflush(stdout);
			if (chat_script(ppp3g_chat_file, ttyfd, 0) < 0) 
			{
				error("Connect script failed");
				status = EXIT_CONNECT_FAILED;
				return -1;
			}
			info("Serial connection established.");
		}

		/* set line speed, flow control, etc.;
		   clear CLOCAL if modem option */
		/* Mark: these two lines are likely for call back and can be erased, but not sure */
/*		if (*real_ttyfd != -1)
			set_up_tty(*real_ttyfd, 0);
		connector = ppp3g_chat_file; */
	}
	
	return 0;
}

void ppp3g_module_disconnect(void)
{
	if (ppp3g_dc_chat_file == NULL || hungup)
		return;
	if (*real_ttyfd >= 0)
		set_up_tty(*real_ttyfd, 1);
	if (chat_script(ppp3g_dc_chat_file, *real_ttyfd, 0) < 0) 
		warn("disconnect script failed");
	else 
		info("Serial link disconnected.");
}


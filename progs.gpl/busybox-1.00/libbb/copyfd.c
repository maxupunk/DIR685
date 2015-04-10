/* vi: set sw=4 ts=4: */
/*
 * Utility routines.
 *
 * Copyright (C) 1999-2004 by Erik Andersen <andersen@codepoet.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "busybox.h"
#include "../../../include/elbox_config.h"/*ftp_tftp_FW_CG_20070125*//*Added by Erick*/

#if BUFSIZ < 4096
#undef BUFSIZ
#define BUFSIZ 4096
#endif


/* If size is 0 copy until EOF */
static size_t bb_full_fd_action(int src_fd, int dst_fd, const size_t size)
{
	size_t read_total = 0;
	RESERVE_CONFIG_BUFFER(buffer,BUFSIZ);

	while ((size == 0) || (read_total < size)) {
		size_t read_try;
		ssize_t read_actual;

 		if ((size == 0) || (size - read_total > BUFSIZ)) {
			read_try = BUFSIZ;
		} else {
			read_try = size - read_total;
		}

		read_actual = safe_read(src_fd, buffer, read_try);
		if (read_actual > 0) {
			if ((dst_fd >= 0) && (bb_full_write(dst_fd, buffer, (size_t) read_actual) != read_actual)) {
				bb_perror_msg(bb_msg_write_error);	/* match Read error below */
				break;
			}
		}
		else if (read_actual == 0) {
			if (size) {
				bb_error_msg("Unable to read all data");
			}
			break;
		} else {
			/* read_actual < 0 */
			bb_perror_msg("Read error");
			break;
		}

		read_total += read_actual;
	}

	RELEASE_CONFIG_BUFFER(buffer);

	return(read_total);
}

/*ftp_tftp_FW_CG_20070125 Erick*//*start {*/
#if ELBOX_PROGS_GPL_TFTP_FTP_GET_PUT_FW_CONFIG
extern int bb_copyfd2buff_eof(int src_fd, char *buffer_ptr, const size_t Max_buffer_len)
{
	size_t read_total = 0;
	RESERVE_CONFIG_BUFFER(buffer,BUFSIZ);

	while ((read_total < Max_buffer_len)) {
		size_t read_try;
		ssize_t read_actual;

		read_try = BUFSIZ;


		read_actual = safe_read(src_fd, buffer, read_try);
		if (read_actual > 0) {
			//if ((dst_fd >= 0) && (bb_full_write(dst_fd, buffer, (size_t) read_actual) != read_actual)) {
			//	bb_perror_msg(bb_msg_write_error);	/* match Read error below */
			//	break;
			//}
			memcpy(buffer_ptr, buffer,(size_t) read_actual);
			buffer_ptr += (int) read_actual;
		}
		else if (read_actual == 0) {
			//if (size) {
			//	bb_error_msg("Unable to read all data");
			//}
			break;
		} else {
			/* read_actual < 0 */
			bb_perror_msg("Read error");
			break;
		}

		read_total += read_actual;
	}

	RELEASE_CONFIG_BUFFER(buffer);

	return (int)(read_total);
}
#endif
/*ftp_tftp_FW_CG_20070125 Erick*//*End }*/

extern int bb_copyfd_size(int fd1, int fd2, const off_t size)
{
	if (size) {
		return(bb_full_fd_action(fd1, fd2, size));
	}
	return(0);
}

extern int bb_copyfd_eof(int fd1, int fd2)
{
	return(bb_full_fd_action(fd1, fd2, 0));
}

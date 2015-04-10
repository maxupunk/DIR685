#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>

#include "lrgbin.h"
#include "rgdb_getset.h"

/* ========================================================================== */
int _rgdb_get_(char *buf, int size, const char *format, ...)
{
	int fd;
	char node[BUFSIZ];
	va_list marker;
	va_start(marker, format);
	vsnprintf(node, BUFSIZ, format, marker);
	va_end(marker);
	if((fd = lrgdb_open(NULL)) == RGDB_GETSET_ERROR)
	{
		perror("Cannot open database.");
		return RGDB_GETSET_ERROR;
	}
	if(lrgdb_get(fd, 0, node, NULL) == RGDB_GETSET_ERROR)
	{
		perror("Get ERROR!");
		lrgdb_close(fd);
		return RGDB_GETSET_ERROR;
	}
	if(read(fd, buf, size) == RGDB_GETSET_ERROR)
	{
		perror("Read database failed.");
		lrgdb_close(fd);
		return RGDB_GETSET_ERROR;
	}
	lrgdb_close(fd);
	return RGDB_GETSET_OK;
}

int _rgdb_set_(const char *node, const char *value)
{
	int fd;
	if((fd = lrgdb_open(NULL)) == RGDB_GETSET_ERROR)
	{
		perror("Cannot open database.");
		return RGDB_GETSET_ERROR;
	}
	if(lrgdb_set(fd, 0, node, value) == RGDB_GETSET_ERROR)
	{
		lrgdb_close(fd);
		perror("Set ERROR!");
		return RGDB_GETSET_ERROR;
	}
	lrgdb_close(fd);
	return RGDB_GETSET_OK;
}

int cli_get_val(char *pVal, int sizeVal, const char * format, ...)
{
	char    path[256];
	int     fd, size = -1;
	va_list marker;

	if(pVal)
	{
		va_start(marker, format);
		vsnprintf(path, sizeof(path), format, marker);
		va_end(marker);

		memset(pVal, 0, sizeVal);
		if((fd = open(path, O_RDONLY)) > 0)
		{
			size = read(fd, pVal, sizeVal);
			close(fd);
		}
	}

	return size;
}

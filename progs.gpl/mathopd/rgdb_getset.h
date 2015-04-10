#ifndef _RGDB_GETSET_H_
#define _RGDB_GETSET_H_

#define RGDB_GETSET_OK 0
#define RGDB_GETSET_ERROR -1

#define RGDBGET(x, y, args...) _rgdb_get_(x, y, ##args)
#define RGDBSET(x, y) _rgdb_set_(x, y)

int _rgdb_get_(char *buf, int size, const char *format, ...);
int _rgdb_set_(const char *node, const char *value);
int cli_get_val(char *pVal, int sizeVal, const char * format, ...);


#endif

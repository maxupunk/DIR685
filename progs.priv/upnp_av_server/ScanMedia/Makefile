-include ../../arch.mk
-include ../../../path.mk
-include ../../../.config

OBJS = 	libxmldbc.o\
	mp3-scanner.o \
	iconv_string.o \
	err.o \
	prescan.o \
	getImgsize.o\
	video_info.o 


MEDIA_TYPE= ../media_type/media_type.o
INCLUDE = ../libid3tag-0.15.0b/ -I../libiconv-1.9.1/include -I../sqlite-3.5.8 -I$(TOPDIR)/include
LIBS = -L../libid3tag-0.15.0b/.libs -lid3tag -L../libiconv-1.9.1/lib/.libs -liconv 
LIBS+=-L../sqlite-3.5.8/.libs -lsqlite3 -L../zlib-1.2.1/ -lz 

ifeq ($(strip $(ELBOX_MODEL_DIR685)),y)
INCLUDE+=-DDIR685NAS=1
endif

DEBUG_FLAG = 
#-DDBG

LARGE_DEFINE = -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64

#-DAUTOPRESCAN
AUTOPRESCAN = -DAUTOPRESCAN

.SUFFIXES= .o .c

ScanMedia: ${OBJS}
	${CC} ${DEBUG_FLAG} ${LARGE_DEFINE} ${AUTOPRESCAN} -I$(INCLUDE) -lpthread -Os -Wall -o $@ -s ${OBJS} $(LIBS)
	${STRIP} ScanMedia

.c.o:
	${CC} -I$(INCLUDE) ${DEBUG_FLAG} ${LARGE_DEFINE} ${AUTOPRESCAN} -c $<

clean:
	/bin/rm -f core *.o ScanMedia

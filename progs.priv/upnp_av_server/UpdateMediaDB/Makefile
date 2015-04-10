-include ../../arch.mk
-include ../../../path.mk
-include ../../../.config
OBJS = 	libxmldbc.o iconv_string.o video_info.o \
		getImgsize.o DBSemaphore.o\
		db-gdbm.o err.o \
		mp3-scanner.o EmbeddedMediaServer_iTune_Sync.o \
		ScanDisk_iTune_Sync.o

INCLUDE = ../libid3tag-0.15.0b/ -I../libiconv-1.9.1/include -I../sqlite-3.5.8 -I$(TOPDIR)/include -I../gdbm-1.8.3
LIBS = -L../libid3tag-0.15.0b/.libs -lid3tag -L../libiconv-1.9.1/lib/.libs -liconv 
LIBS+=-L../sqlite-3.5.8/.libs -lsqlite3 -lgdbm -lpthread -L../gdbm-1.8.3/.libs -lgdbm -L../zlib-1.2.1/ -lz
LDFLAG = -s 
##DEBUG_FLAG = -DDBG
DEFINE = -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D_POSIX

ifeq ($(strip $(ELBOX_MODEL_DIR685)),y)
INCLUDE+=-DDIR685NAS=1
endif

.SUFFIXES= .o .c

UpdateMediaDB: ${OBJS}
	${CC} ${DEBUG_FLAG} ${DEFINE} -I$(INCLUDE) -Os -Wall -o $@ -s ${OBJS} $(LDFLAG) $(LIBS)

.c.o:
	${CC} -I$(INCLUDE) ${DEBUG_FLAG} ${DEFINE} -c $<

clean:
	/bin/rm -f core *.o UpdateMediaDB

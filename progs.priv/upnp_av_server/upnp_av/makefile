
#
# Intel's UPnP MicroStack/1.0, Sample MakeFile */
# Intel Device Builder - Build#1.0.1725.27554
#

-include ../../arch.mk
-include ../../../path.mk
-include ../../../.config
# List all object files here
OFILES = libxmldbc.o\
	Main.o \
	ILibParsers.o\
	ILibAsyncSocket.o\
	ILibAsyncServerSocket.o\
	ILibWebClient.o\
	ILibWebServer.o\
	UPnPMicroStack.o\
	UPnPProcess.o \
	mp3_id3.o \
	getImgsize.o \
	video_info.o

# Compiler command name
#CC = $(CROSS_COMPILE)gcc
#STRIP = $(CROSS_COMPILE)strip

# Compiler flags applied to all files 

# ************** Define **************
# ----product define----
# -DSAMWISE , -DARWEN , -DFRODO 
#PRODUCT = -DFRODO
PRODUCT = -DSAMWISE

# ----Byte order define----
# -D_LITTLE_EDIAN , -D_BIG_EDIAN 
EDIAN = -D_LITTLE_EDIAN
#EDIAN = -D_BIG_EDIAN 

# ----Image convert define----
# -DIMGCONV , -DNOINGCONV
IMGCONV = -DIMGCONV
#IMGCONV = -DNOINGCONV

# ----SQL define----
# -DSQL
SQL = -DSQL

# ----customer define----
# -DDLINK -DCONCEPTRONIC
#CUSTOMER = -DCONCEPTRONIC
CUSTOMER = -DDLINK

# ----customer define----
# -DPNPX
#PNPX = -DPNPX
PNPX =
# ************** Define End **************

# ----For dlink 346----
#INCLUDE = /home/ben/iSCSI/AIS-400/arm-marvell-linux-gnu/arm-marvell-linux-gnu/include

# ----For Samwise----
#INCLUDE = /opt/uclibc-toolchain-src-20040609/gcc-2.95/toolchain_powerpc/include
INCLUDE =../sqlite-3.5.8/ -I../libiconv-1.9.1/include -I../libid3tag-0.15.0b/
#-DGB2312 -DBIG5
CFLAGS = -I$(INCLUDE) -Os -Wall -DUPNP_1_1 -D_POSIX -D_REENTRANT -D_DEBUG -D_VERBOSE $(SQL) $(PNPX) $(CUSTOMER) $(PRODUCT) $(EDIAN) $(IMGCONV) -s -Wno-unused -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -I$(TOPDIR)/include
#CFLAGS = -I$(INCLUDE) -Os -Wall -DUPNP_1_1 -D_POSIX -D_REENTRANT -D_DEBUG -D_VERBOSE $(SQL) $(CUSTOMER) $(PRODUCT) $(EDIAN) $(IMGCONV) -s -Wno-unused -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
#CFLAGS = -O0 -g -Wall -DUPNP_1_1 -D_POSIX -D_DEBUG -D_VERBOSE -D_BIG_EDIAN -DIMGCONV -s -Wno-unused -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
#CFLAGS = -Os -Wall   -D_POSIX -D_DEBUG -D_VERBOSE -D_BIG_EDIAN -s -Wno-unused 
 
#LIBS = -lpthread -lm -liconv -lid3tag -lsqlite3
#LIBS = -lpthread -lm -lsqlite3 -lxmldbc
LIBS = -lpthread -lm -L../libiconv-1.9.1/lib/.libs/ -liconv \
-L../libid3tag-0.15.0b/.libs/ -lid3tag -L../sqlite-3.5.8/.libs/ -lsqlite3
# Name of the executable
EXENAME = upnp

ifeq ($(strip $(ELBOX_MODEL_DIR685)),y)
INCLUDE+=-DDIR685NAS=1
endif

LDFLAG = -s -L../lib

#LD = powerpc-linux-uclibc-ld

# Builds all object files and executable
${EXENAME} : $(OFILES)
#	$(CC) $(CFLAGS) -o ${EXENAME} $(OFILES) $(LD) $(LDFLAG) $(LIBS)
	$(CC) $(CFLAGS) -o ${EXENAME} $(OFILES) $(LDFLAG) $(LIBS) 

# Macro rule for all object files.
$(OFILES) : \
	UPnPMicroStack.h

# Clean up
clean :
	rm -f $(OFILES) ${EXENAME} ${EXENAME}.exe

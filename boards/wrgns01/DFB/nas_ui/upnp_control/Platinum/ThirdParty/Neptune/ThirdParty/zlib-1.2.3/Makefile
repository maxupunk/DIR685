OBJFile = adler32.o compress.o crc32.o deflate.o infback.o inffast.o inflate.o inftrees.o trees.o zutil.o
CC=/opt/storlink_arm_920t_le_uclibc/bin/arm-linux-gcc
RANLIB=ranlib
CFLAGS= -pedantic -g -Werror -Werror -Wall -W -Wundef -Wno-long-long -D_REENTRANT -DNPT_DEBUG -DNPT_CONFIG_ENABLE_LOGGING

ZLIB = libZlib.a
all: $(ZLIB)

$(ZLIB): $(OBJFile)
#	$(AR) $(LDFLAGS) -o $@ $(OBJS1) $(LIBCRYPT) $(LDLIBS$(LDLIBS-$(@)))
	$(AR) rc libZlib.a $(OBJFile)
#	$(RANLIB) libZlib.a
%.o: %.c
	echo $(CC)$(INC_PATH) $(CFLAGS) -c -o $@ $<
	$(CC)$(INC_PATH) $(CFLAGS) -c -o $@ $<
clean:
	rm -rf *.o *.a

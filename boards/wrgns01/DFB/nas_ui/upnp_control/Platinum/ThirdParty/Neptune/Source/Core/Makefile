OBJFile = Neptune.o NptHttp.o NptStreams.o NptBase64.o NptList.o NptStrings.o \
          NptBufferedStreams.o  NptLogging.o  NptSystem.o NptCommon.o NptMessaging.o \
          NptThreads.o NptConsole.o NptNetwork.o  NptTime.o NptDataBuffer.o  NptQueue.o \
          NptUri.o NptDebug.o NptRingBuffer.o NptUtils.o NptDirectory.o NptSimpleMessageQueue.o \
          NptXml.o NptFile.o NptSockets.o NptZip.o

OBJFile += ../System/StdC/NptStdcFile.o ../System/StdC/NptStdcEnvironment.o ../System/StdC/NptStdcDebug.o \
		   ../System/StdC/NptStdcConsole.o ../System/Posix/NptPosixQueue.o ../System/Posix/NptPosixSystem.o \
		   ../System/Posix/NptPosixThreads.o ../System/Posix/NptPosixDirectory.o ../System/Posix/NptPosixNetwork.o \
		   ../System/Posix/NptSelectableMessageQueue.o ../System/Bsd/NptBsdNetwork.o ../System/Bsd/NptBsdSockets.o

CXX=/opt/storlink_arm_920t_le_uclibc/bin/arm-linux-g++
RANLIB=ranlib
CFLAGS= -c -pedantic -g -Werror -Werror -Wall -W -Wundef -Wno-long-long -pedantic -g -Werror -Werror -Wall -W -Wundef -Wno-long-long -D_REENTRANT -DNPT_DEBUG -DNPT_CONFIG_ENABLE_LOGGING -DNPT_CONFIG_ENABLE_ZIP
CFLAGS += -I../../ThirdParty/zlib-1.2.3
CFLAGS += -I.

LIB = libNeptune.a
all: $(LIB)

$(LIB): $(OBJFile)
	$(AR) rc $(LIB) $(OBJFile)
#	$(RANLIB) $(LIB)
%.o: %.cpp
	$(CXX) $(INC_PATH) $(CFLAGS) -c -o $@ $<
clean:
	rm -rf *.o *.a

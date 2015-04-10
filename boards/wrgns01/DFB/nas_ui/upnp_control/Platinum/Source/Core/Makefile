OBJFile = Platinum.o           PltEvent.o             PltService.o \
			PltAction.o          PltHttpClientTask.o    PltSsdp.o \
			PltArgument.o        PltHttp.o              PltStateVariable.o \
			PltCtrlPoint.o       PltHttpServer.o        PltStreamPump.o \
			PltCtrlPointTask.o   PltHttpServerTask.o    PltTaskManager.o \
			PltDatagramStream.o  PltLeaks.o             PltThreadTask.o \
			PltDeviceData.o      PltLog.o               PltUPnP.o \
			PltDeviceHost.o      PltMetadataHandler.o \
			PltDownloader.o      PltRingBufferStream.o \

ROOTPATH=../..
CXX=/opt/storlink_arm_920t_le_uclibc/bin/arm-linux-g++
RANLIB=ranlib
CFLAGS= -c -pedantic -g -Werror -Werror -Wall -W -Wundef -Wno-long-long -pedantic -g -Werror -Werror -Wall -W -Wundef -Wno-long-long -D_REENTRANT -DNPT_DEBUG -DNPT_CONFIG_ENABLE_LOGGING -DNPT_CONFIG_ENABLE_ZIP
CFLAGS += -I$(ROOTPATH)/ThirdParty/Neptune/Source/Core -I$(ROOTPATH)/Source/Core -I$(ROOTPATH)/Source/Devices/MediaServer -I$(ROOTPATH)/Source/Devices/MediaRenderer -I$(ROOTPATH)/Source/Devices/MediaConnect

LIB = libPlatinum.a
all: $(LIB)

$(LIB): $(OBJFile)
	$(AR) rc $(LIB) $(OBJFile)
#	$(RANLIB) $(LIB)
%.o: %.cpp
	$(CXX) $(INC_PATH) $(CFLAGS) -c -o $@ $<
clean:
	rm -rf *.o *.a

OBJFile = PltDidl.o             PltMediaCache.o     PltMediaServer.o \
PltFileMediaServer.o  PltMediaItem.o      PltMediaServerSCPDs.o \
PltMediaBrowser.o     PltMediaPlaylist.o  PltSyncMediaBrowser.o \


ROOTPATH=../../..
CXX=/opt/storlink_arm_920t_le_uclibc/bin/arm-linux-g++
RANLIB=ranlib
CFLAGS= -c -pedantic -g -Werror -Werror -Wall -W -Wundef -Wno-long-long -pedantic -g -Werror -Werror -Wall -W -Wundef -Wno-long-long -D_REENTRANT -DNPT_DEBUG -DNPT_CONFIG_ENABLE_LOGGING -DNPT_CONFIG_ENABLE_ZIP
CFLAGS += -I$(ROOTPATH)/ThirdParty/Neptune/Source/Core -I$(ROOTPATH)/Source/Core -I$(ROOTPATH)/Source/Devices/MediaServer -I$(ROOTPATH)/Source/Devices/MediaRenderer -I$(ROOTPATH)/Source/Devices/MediaConnect

LIB = libPltMediaServer.a
all: $(LIB)

$(LIB): $(OBJFile)
	$(AR) rc $(LIB) $(OBJFile)
#	$(RANLIB) $(LIB)
%.o: %.cpp
	$(CXX) $(INC_PATH) $(CFLAGS) -c -o $@ $<
clean:
	rm -rf *.o *.a

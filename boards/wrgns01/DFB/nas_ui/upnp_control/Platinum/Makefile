-include ../../../../../../path.mk
CP_OBJFile = Alpha_MediaController/main.o Alpha_MediaController/PltMicroMediaController.o Alpha_MediaController/PltMicroMediaController_Extend.o Alpha_MediaController/packet_serialize.o \
			Alpha_MediaController/str_tool.o			
#CP_OBJFile = Source/Apps/MicroMediaController/main.o Source/Apps/MicroMediaController/PltMicroMediaController.o

CXX=/opt/storlink_arm_920t_le_uclibc/bin/arm-linux-g++
RANLIB=ranlib
CFLAGS= -c -pedantic -g -Wall -W -Wundef -Wno-long-long -pedantic -g  -Wall -W -Wundef -Wno-long-long -D_REENTRANT -DNPT_DEBUG -DNPT_CONFIG_ENABLE_LOGGING -DNPT_CONFIG_ENABLE_ZIP
CFLAGS += -IThirdParty/Neptune/Source/Core -ISource/Core -ISource/Devices/MediaServer -ISource/Devices/MediaRenderer -ISource/Devices/MediaConnect -IAlpha_MediaController/include
NP_LIB = ThirdParty/Neptune/Source/Core/libNeptune.a 
Z_LIB = ThirdParty/Neptune/ThirdParty/zlib-1.2.3/libZlib.a
PT_LIB = Source/Core/libPlatinum.a
MS_LIB =  Source/Devices/MediaServer/libPltMediaServer.a
RD_LIB = Source/Devices/MediaRenderer/libPltMediaRenderer.a
EXEC = MicroMediaController
all: $(EXEC)

$(EXEC): $(NP_LIB) $(Z_LIB) $(CP_OBJFile) $(PT_LIB) $(MS_LIB) $(RD_LIB)
	$(CXX) -static $(CP_OBJFile) $(NP_LIB) $(Z_LIB) $(PT_LIB)  $(MS_LIB) $(RD_LIB) -lpthread -o $@ $<

$(Z_LIB):
	make -C ThirdParty/Neptune/ThirdParty/zlib-1.2.3
	
$(NP_LIB):
	make -C ThirdParty/Neptune/Source/Core

$(PT_LIB):
	make -C Source/Core

$(MS_LIB):
	make -C Source/Devices/MediaServer

$(RD_LIB):
	make -C Source/Devices/MediaRenderer

install:
	 $(Q)cp MicroMediaController $(TARGET)/directfb
clean:
	rm -rf $(CP_OBJFile)
	make -C ThirdParty/Neptune/ThirdParty/zlib-1.2.3 clean
	make -C ThirdParty/Neptune/Source/Core clean
	make -C Source/Core clean
	make -C Source/Devices/MediaServer clean
	make -C Source/Devices/MediaRenderer clean

%.o: %.cpp
	$(CXX) $(INC_PATH) $(CFLAGS) -c -o $@ $<

.PHONY:$(NP_LIB) $(Z_LIB)

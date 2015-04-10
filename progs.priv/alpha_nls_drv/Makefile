
-include ../../arch.mk
-include ../../path.mk
-include ../../model_config.sh
-include $(TOPDIR)/.config

# Mark added two additional flags
LINUX_VERSION_2_6=y
STAND_ALONE=y

LED_HOME=$(shell pwd)
KCFLAGS += -DLINUX -DENABLE_TRACE

ifeq ($(ELBOX_BOARD_DHA130),y)
KCFLAGS += -DBOARD_DHA130=1
else
ifeq  ($(ELBOX_BOARD_AVA3422),y)
KCFLAGS += -DBOARD_AVA3422=1
else
#error	 "Undefined BOARD type"
endif
endif

NLS_TEST = alpha_nls_test
NLS_FUNC_ONLY =  alpha_nls_conv.o
NLS_TEST_SRC = alpha_nls_test.c
SA_MACRO_FLAG = -D__NLS_STAND_ALONE=1

# Building module
ifeq ($(LINUX_VERSION_2_6),y)

OBJS := alpha_nls_conv_drv.ko
obj-m += alpha_nls_conv_drv.o

all: $(NLS_TEST)
	@echo -e "\033[32mBuilding ALPHA NLS CONV module...\033[0m"
	$(Q)make -C $(KERNELDIR) M=`pwd` modules V=1
	$(STRIP) -g alpha_nls_conv_drv.ko

clean:
#	@echo -e "\033[32mCleaning ALPHA NLS CONV module...\033[0m"
#	$(Q)make -C $(KERNELDIR) M=`pwd` clean
#	$(Q)rm -f *~
#	$(Q)rm -rf alpha_nls_test *.o

install:
	@echo -e "\033[32mInstalling Alpha NLS Conv driver ...\033[0m"
	$(Q)[ -d $(TARGET)/lib/modules ] || mkdir -p $(TARGET)/lib/modules
	$(Q)cp -a ./$(OBJS) $(TARGET)/lib/modules/$(OBJS)
	
.PHONY: alpha_nls_test
	
else # For Linux version 2.4

INC_DIR = -I$(KERNELDIR)/include -I ./h 
OBJS = alpha_nls_conv_drv.o

all:	$(OBJS) $(NLS_TEST)
	@echo -e "\033[32mBuilding ALPHA NLS CONV module...\033[0m"
	$(LD) -o nls_conv_drv.o -r $(OBJS)

clean:
	@echo -e "\033[32mCleaning ALPHA NLS CONV module...\033[0m"
	rm -rf nls_conv_drv.o *.o

install:
	@echo -e "\033[32mInstalling Alpha NLS Conv driver ...\033[0m"
	cp -f ./nls_conv_drv.o $(TARGET)/lib/modules
	
.c.o:
	$(CC) $(KCFLAGS) $(INC_DIR) -c  $<

endif


ifeq ($(STAND_ALONE),y)
# Building testing application file
IFLAGS += -D__NLS_STAND_ALONE=1

$(NLS_TEST): $(NLS_TEST_SRC)
	@echo -e "${FG_GREEN}Compile $(NLS_TEST) ...${C_RESET}"
	$(CC) $(CFLAGS) $(IFLAGS) $(NLS_TEST_SRC) -o $(NLS_TEST) 
	$(STRIP) -s $(NLS_TEST)

else # For function only build

$(NLS_TEST): $(NLS_TEST_SRC)
	@echo -e "${FG_GREEN}Compile $(NLS_FUNC_ONLY) ...${C_RESET}"
	$(CC) $(CFLAGS) $(IFLAGS) -c $(NLS_TEST_SRC) -o $(NLS_FUNC_ONLY) 
#	$(STRIP) -s $(NLS_TEST)

endif
	
.PHONY: all install clean

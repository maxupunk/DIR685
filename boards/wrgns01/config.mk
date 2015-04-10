#
# Makefile for WRG-N15 (linux kernel 2.6)
#
MYNAME:=WRG-N15
Q?=@

#############################################################################
# build root file system image

build_tools:
	$(Q)[ -d images ] || mkdir -p images
	$(Q)make -C ./tools/squashfs-tools
	$(Q)make -C ./tools/buildimg

squashfs: build_tools clean_CVS remove_fsimg
	@echo -e "\033[32m$(MYNAME): building squashfs !\033[0m"
	$(Q)./tools/squashfs-tools/mksquashfs_mknode rootfs $(ROOTFS_IMG) -le -noappend -no-fragments -noI -all-root -D progs.board/device_table.txt

squashfs_lzma: build_tools clean_CVS remove_fsimg strip_all_progs strip_all_libs
	@echo -e "\033[32m$(MYNAME): building squashfs (LZMA) mknode!\033[0m"
	./tools/squashfs-tools/mksquashfs_mknod-lzma rootfs $(ROOTFS_IMG) -le -noappend -no-fragments -noI -all-root -D progs.board/device_table.txt

.PHONY: build_tools squashfs squashfs_lzma strip_all_progs strip_all_libs

#############################################################################
#
# build kernel image
#
kernel_image:
	@echo -e "\033[32m$(MYNAME) Building kernel image file ...\033[0m"
	$(Q)rm -f $(KERNEL_IMG)
	$(Q)cp $(KERNELDIR)/arch/arm/boot/zImage $(KERNEL_IMG)
#	$(Q)cp $(KERNELDIR)/arch/arm/boot/Image vmlinux.bin
#	$(Q)gzip vmlinux.bin
#	$(Q)mv vmlinux.bin.gz $(KERNEL_IMG)
	

kernel_image_lzma:
	@echo -e "\033[32m$(MYNAME) Building kernel image file (LZMA)...\033[0m"
	$(Q)rm -f $(KERNEL_IMG).lzma
	$(Q)make -C ./tools/squashfs-tools
	$(Q)cp $(KERNELDIR)/arch/arm/boot/zImage $(KERNEL_IMG)
#	$(Q)./tools/squashfs-tools/lzma/lzma e $(KERNELDIR)/arch/arm/boot/Image $(KERNEL_IMG)

#kernel_image_u-boot: kernel_image_lzma
#	@echo -e "\033[32m$(MYNAME) Prefix kernel image with u-boot header...\033[0m"
#	$(Q)rm -f $(KERNEL_IMG)
#	$(Q)./tools/mkimage.5vt/mkimage -A arm -O linux -T kernel -C bzip2 -a 0x40008000 -e 0x40008000 \
#	-n $(ELBOX_BSP_NAME) -d $(KERNEL_IMG).lzma $(KERNEL_IMG)

debugk_image: kernel_image_lzma
	cat $(KERNELDIR)/arch/arm/boot/zImage >> $(KERNEL_IMG)
	make squashfs_lzma
	@echo -e "\033[32m$(MYNAME) make F/W image (release image)!\033[0m"
	$(Q)./tools/buildimg/packimgs -v -o raw.img -i $(KERNEL_IMG) -i $(ROOTFS_IMG)
	$(Q)./tools/buildimg/v2image -v -i raw.img -o web.img -d /dev/mtdblock/1 -s $(ELBOX_SIGNATURE) -c
	$(Q)./tools/release.sh web.img debugimage.bin
debug_kernel: mykernel kernel_image_lzma
	./tools/buildimg/v2image -v -i kernel.img -o images/debugkernel.bin -d /dev/mtdblock/1 -s $(ELBOX_SIGNATURE) -c 
	
.PHONY: kernel_image kernel_image_lzma debug_kernel debugk_image

##########################################################################
#
# Common target
#

kernel_clean:
	@echo -e "\033[32m$(MYNAME): cleaning kernel ...\033[0m"
	$(Q)make -C kernel mrproper

kernel: kernel_clean mykernel

mykernel:
	@echo -e "\033[32m$(MYNAME) make linux 2.6 kernel!\033[0m"
	if [ ! -f  kernel/.config ]; then \
		cp progs.board/kernel.config kernel/.config; \
	fi
	echo $(CC)
	$(Q)make -C ./tools/7zip-0.1
	$(Q)make -C kernel zImage 
	
#hendry add to strip all programs bfore making image
PGRMS_STRIP := /opt/storlink_arm_920t_le_uclibc/bin/arm-linux-strip -s
ALL_PGRMS := $(shell find "$(TARGET)/usr/sbin" -type f  | grep -v "font")
ALL_PGRMS += $(shell find "$(TARGET)/usr/bin" -type f)
ALL_PGRMS += $(shell find "$(TARGET)/bin" -type f)
ALL_PGRMS += $(shell find "$(TARGET)/sbin" -type f)
ALL_PGRMS += $(TARGET)/directfb/alpha_nas $(TARGET)/directfb/fcrss_server

LIB_STRIP := /opt/storlink_arm_920t_le_uclibc/bin/arm-linux-strip --strip-unneeded
ALL_LIB := $(shell find "$(TARGET)/lib" -type f)
ALL_LIB += $(shell find "$(TARGET)/lib64" -type f)

test :
	for i in $$ALL_PGRMS; do \
	file $$i; \
	done	
test2 :
	for i in $$ALL_LIB; do \
	file $$i ;\
	done

strip_all_progs :
	for i in $$ALL_PGRMS; do \
	$(PGRMS_STRIP) $$i; \
	done
strip_all_libs :
	for i in $$ALL_LIB; do \
	$(LIB_STRIP) $$i; \
	done

#####################################################################
# Image signature	re-alloc the signature //joel
# in this file we will re-work some env v
include progs.board/customer.mk
#

ifeq (buildno, $(wildcard buildno))
BUILDNO:=$(shell cat buildno)
ifdef CHIP_RTL8366SR
RELIMAGE:=$(shell echo $(ELBOX_MODEL_NAME)_v$(ELBOX_FIRMWARE_VERSION)_$(BUILDNO))
else
RELIMAGE:=$(shell echo $(ELBOX_MODEL_NAME)_v$(ELBOX_FIRMWARE_VERSION)_RB$(BUILDNO))
endif

#sonnia
.PHONY: lang_pack
lang_pack:
ifeq ($(strip $(ELBOX_CREATE_LANGUAGE_PACK)),y)
	$(Q)[ -d images/$(RELIMAGE) ] || mkdir -p images/$(RELIMAGE)
	$(Q)for i in $(LANGUAGE); do \
		./tools/squashfs-tools/mksquashfs-lzma language/$$i langpack.bin -le ; \
		chmod 664 langpack.bin ; \
		./tools/buildimg/v2image -v -i langpack.bin -o images/$(RELIMAGE)/$(RELIMAGE)_langpack_$$i.bin \
			-d /dev/mtdblock/5 -s $(ELBOX_SIGNATURE) -c ; \
		rm -f langpack.bin ; \
		done
endif

magic_release: kernel_image_lzma squashfs
	@echo -e "\033[32m$(MYNAME) make F/W image (magic release image)!\033[0m"
	$(Q)./tools/buildimg/packimgs -v -o raw.img -i $(KERNEL_IMG) -i $(ROOTFS_IMG)
	$(Q)./tools/buildimg/v2image -v -i raw.img -o web.img -d /dev/mtdblock/1 -s $(ELBOX_BOARD_NAME)_aLpHa -c
#	$(Q)rm -f raw.img
	$(Q)./tools/release.sh web.img $(RELIMAGE)/$(RELIMAGE).magic.bin

release: kernel_image_lzma squashfs_lzma lang_pack
	@echo -e "\033[32m$(MYNAME) make F/W image (release image)!\033[0m"
	$(Q)[ -d images/$(RELIMAGE) ] || mkdir -p images/$(RELIMAGE)
	$(Q)./tools/buildimg/packimgs -v -o raw.img -i $(KERNEL_IMG) -i $(ROOTFS_IMG)
	$(Q)./tools/buildimg/v2image -v -i raw.img -o web.img -d /dev/mtdblock/1 -s $(ELBOX_SIGNATURE) -c
#	$(Q)rm -f raw.img
	$(Q)./tools/release.sh web.img $(RELIMAGE)/$(RELIMAGE).bin
		
tftpimage: kernel_image_lzma squashfs_lzma
	@echo -e "\033[32m$(MYNAME) make F/W image (tftp image)!\033[0m"
	$(Q)rm -f $(TFTPIMG)
	$(Q)./tools/buildimg/packimgs -v -o raw.img -i $(KERNEL_IMG) -i $(ROOTFS_IMG)
	$(Q)./tools/tftpimage.sh $(TFTPIMG)

else
release tftpimage:
	@echo -e "\033[32m$(MYNAME): Can not build image, ROOTFS is not created yet !\033[0m"
endif

.PHONY: kernel release tftpimage

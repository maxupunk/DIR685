#
# Makefile for the linux squashfs routines.
#
ifdef CONFIG_CC_OPTIMIZE_FOR_SIZE
	CFLAGS += -O2
endif

obj-$(CONFIG_SQUASHFS) += squashfs.o
squashfs-y += inode.o
squashfs-y += squashfs2_0.o
squashfs-y += LzmaDecode.o

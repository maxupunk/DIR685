cmd_/home/jana/20090522/boards/wrgns01/apps/rtl8366/rtl8366rb/smi.o := arm-linux-gcc -Wp,-MD,/home/jana/20090522/boards/wrgns01/apps/rtl8366/rtl8366rb/.smi.o.d  -nostdinc -isystem /spaces/opt/storlink_arm_920t_le_uclibc.20080713/bin/../lib/gcc/arm-linux-uclibc/3.4.6/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -ffreestanding -O2     -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mapcs-32 -mno-thumb-interwork -D__LINUX_ARM_ARCH__=4 -march=armv4  -malignment-traps -msoft-float -Uarm -Wdeclaration-after-statement    -DMODULE -DKBUILD_BASENAME=smi -DKBUILD_MODNAME=switch -c -o /home/jana/20090522/boards/wrgns01/apps/rtl8366/rtl8366rb/smi.o /home/jana/20090522/boards/wrgns01/apps/rtl8366/rtl8366rb/smi.c

deps_/home/jana/20090522/boards/wrgns01/apps/rtl8366/rtl8366rb/smi.o := \
  /home/jana/20090522/boards/wrgns01/apps/rtl8366/rtl8366rb/smi.c \
  include/linux/spinlock.h \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/preempt.h) \
  include/linux/config.h \
    $(wildcard include/config/h.h) \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
  include/linux/thread_info.h \
  include/linux/bitops.h \
  include/asm/types.h \
    $(wildcard include/config/lbd.h) \
  include/asm/bitops.h \
  include/linux/compiler.h \
  include/linux/compiler-gcc3.h \
  include/linux/compiler-gcc.h \
  include/asm/system.h \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
  include/linux/linkage.h \
  include/asm/linkage.h \
  include/asm/thread_info.h \
  include/asm/fpstate.h \
    $(wildcard include/config/iwmmxt.h) \
  include/asm/ptrace.h \
    $(wildcard include/config/arm/thumb.h) \
  include/asm/domain.h \
  include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/sysctl.h) \
  /spaces/opt/storlink_arm_920t_le_uclibc.20080713/bin/../lib/gcc/arm-linux-uclibc/3.4.6/include/stdarg.h \
  include/linux/stddef.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
  include/linux/posix_types.h \
  include/asm/posix_types.h \
  include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/byteorder/swab.h \
  include/linux/byteorder/generic.h \
  include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
  include/linux/stringify.h \
  include/linux/spinlock_types.h \
  include/linux/spinlock_types_up.h \
  include/linux/spinlock_up.h \
  include/linux/spinlock_api_up.h \
  include/asm/atomic.h \
  /home/jana/20090522/boards/wrgns01/apps/rtl8366/rtl8366rb/rtl8368s_types.h \
  include/linux/string.h \
  include/asm/string.h \
  /home/jana/20090522/boards/wrgns01/apps/rtl8366/rtl8366rb/gpio.h \
  /home/jana/20090522/boards/wrgns01/apps/rtl8366/rtl8366rb/smi.h \

/home/jana/20090522/boards/wrgns01/apps/rtl8366/rtl8366rb/smi.o: $(deps_/home/jana/20090522/boards/wrgns01/apps/rtl8366/rtl8366rb/smi.o)

$(deps_/home/jana/20090522/boards/wrgns01/apps/rtl8366/rtl8366rb/smi.o):

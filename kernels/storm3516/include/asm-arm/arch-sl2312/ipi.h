/*
 *  linux/include/asm-arm/arch-sl2312/system.h
 *
 *  Copyright (C) 1999 ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd
 *  Copyright (C) 2001 Altera Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef __ASM_ARCH_IPI_H
#define __ASM_ARCH_IPI_H
#include <asm/io.h>
#include <asm/sizes.h>
#include <linux/pci.h>

//#define spin_lock(x)	spin_lock_dt(x)
//#define spin_unlock(x)	spin_unlock_dt(x)

#define SWAP_OFFSET							0x400000
#define SWAP_SIZE							0x400000

// CPU1 reset release
#define GLOBAL_BASE		IO_ADDRESS(0x40000000)
#define GLOBAL_SOFTRESET	(GLOBAL_BASE + 0x0C)
#define CPU1_RESET_BIT_MASK     0x40000000

// IPI , need to redefine the folliwing,  bug
#define CPU0_STATUS			(GLOBAL_BASE + 0x0038)
#define CPU1_STATUS			(GLOBAL_BASE + 0x003C)
#define CPU_IPI_BIT_MASK    0x80000000

#define	CPU1_BASE_OFFSET	0x04000000

/* Your basic SMP spinlocks, allowing only a single CPU anywhere
*/
typedef struct {
       volatile unsigned int lock;
} spinlock_dt;


#define         MASTER_BIT      0x01
#define         SLAVE_BIT       0x02
#define         HEART_BIT       0x04
#define         IPI0_IRQ_BIT    0x08
#define         IPI0_FIQ_BIT    0x10
#define         IPI1_IRQ_BIT    0x20
#define         IPI1_FIQ_BIT    0x40

#define IRQ     0
#define FIQ     1
#define DONE    0xff

#define         CPU0            0x0
#define         CPU1            0x1

#define         MAXCHAR         128*1024

/*-----------------------------------------------------------------------------
 * We have four types of IPI messages so far:
 * 1. GMAC1 configuration command, from CPU0: init, reset, close, etc.
 * 2. Transfer network buffers (SKBs) to the other system. CPU0 <-> CPU1
 * 3. Release crosee bound network buffers (SKBs).
 * 4. Update CPU1 bridging/NAT tables. (CPU0 maintains the master tables).
 *---------------------------------------------------------------------------*/
#define IPI_MSG_GMAC1_CONFIG		0x01
#define	IPI_MSG_TRANSFER_BUF		0x02
#define	IPI_MSG_RELEASE_BUF			0x03
#define	IPI_MSG_UPDATE_TABLE		0x04

#define	IPI_MSG_USER_WRITE			0x05		// test purpose

/*-----------------------------------------------------------------------------
 * IPI queue descriptor definitions
 *---------------------------------------------------------------------------*/
typedef struct {
	u16		type;				// message type
	u16		param;				// message parameters.
} IPC_MSG_HDR_T;

typedef struct{
	IPC_MSG_HDR_T	hdr;
	u32				buf_addr;	// data buffer's bus address
	u32				buf_size;	// data buffer length.
	u32				reserved;
} IPI_DESC_T;

/*-----------------------------------------------------------------------------
 * Linked software queue.
 *---------------------------------------------------------------------------*/
// a simple chain structure
struct IPI_QUEUE;

struct IPI_QUEUE {
	struct IPI_QUEUE	*next;
	unsigned int	cmd;
	unsigned int	size;
	unsigned int	data;
};

#define IPC_REQ_MSG			0	// request from CPU-0 to CPU-1
#define IPC_RSP_MSG			1	// response from CPU-1 to CPU-0
#define IPC_REQ_DATA		2	// request data, CPU-0 to CPU-1 
#define IPC_RSP_DATA		3	// response data, CPU-1 to CPU-0

/*-----------------------------------------------------------------------------
 * IPI Queue Header Definitions
 *---------------------------------------------------------------------------*/
#define IPIQ_DESC_POWER		8
#define IPIQ_DESC_NUM		(1<<IPIQ_DESC_POWER)
#define	IPIQ_DESC_MASK		(IPIQ_DESC_NUM-1)
#define	IPIQ_BUF_SIZE		PAGE_CACHE_SIZE

#define	IPI_QHDR_OFFSET			0x0400
#define	CPU0_IPI_Q_HDR_BASE		(IO_ADDRESS(SL2312_SRAM_BASE))
#define CPU1_IPI_Q_HDR_BASE		(IO_ADDRESS((SL2312_SRAM_BASE)+(IPI_QHDR_OFFSET)))

#define	CPU0_IPIQ_DESC_BASE		(IO_ADDRESS((SL2312_SRAM_BASE)+(IPI_QHDR_OFFSET)*2))
#define	IPIQ_DESC_SIZE			(IPIQ_DESC_NUM * sizeof(IPI_DESC_T))

#define	CPU0_IPI_Q0_BASE		(CPU0_IPIQ_DESC_BASE)
#define	CPU1_IPI_Q0_BASE		((CPU0_IPIQ_DESC_BASE)+(IPIQ_DESC_SIZE))

#define	IPI_SHARE_MEM_SIZE		(3<<20)
#define	IPI_SHARE_BASE			(SZ_64M - IPI_SHARE_MEM_SIZE)
/*
#define IPI_SHARE_MEM_SIZE		(3<<20)
#define CPU0_IPI_Q0_BASE		(CPU_1_MEM_BASE+CPU_1_DATA_OFFSET)
#define CPU1_IPI_Q0_BASE		(CPU_1_MEM_BASE+CPU_1_DATA_OFFSET+(IPI_SHARE_MEM_SIZE>>1))
*/

typedef union {
	unsigned int bits32;
	unsigned int base_size;
} IPI_QHDR0_T;

typedef struct {
	unsigned int wptr;
	unsigned int rptr;
} IPI_QHDR1_T;

typedef struct {
	IPI_QHDR0_T		word0;
	IPI_QHDR1_T		word1;
//	unsigned int	tx_clean_ptr;
} IPI_QHDR_T;

typedef struct ipi_dev {
	// virtual addresses of cpu queue descriptors, at shared memory.
	unsigned int	txq_desc_ptr;
	unsigned int	rxq_desc_ptr;

	unsigned int	tx_clean_ptr;
	// cpu queue header, in SRAM.
	IPI_QHDR_T		*ipi_tx_qhdr;
	IPI_QHDR_T		*ipi_rx_qhdr;

	unsigned int	irq;
} IPI_DEV_T;

#define			TX_TESTBIT	0
#define			RX_TESTBIT	1

typedef struct ipi_private {
	IPI_DEV_T		dev;
	struct IPI_QUEUE	*txq, *txq_tail;
	struct IPI_QUEUE	*rxq, *rxq_tail;
	///struct semaphore	tx_sem, rx_sem;
	spinlock_t	tx_lock, rx_lock;

	unsigned int		tasklet_testbit;	// bit 0 for tx, bit 1 for rx.
	struct tasklet_struct	tx_tasklet;
	struct tasklet_struct	rx_tasklet;
} IPI_INFO_T;

static IPI_INFO_T	ipi_dev;
EXPORT_SYMBOL(ipi_dev);

#define GEMINI_IPI_IOCTL_BASE	'Z'
#define GEMINI_IPI_JSCALE_REQ		_IOW (GEMINI_IPI_IOCTL_BASE,0,JSCALE_REQ_T)
#define GEMINI_IPI_JSCALE_STAT		_IOR (GEMINI_IPI_IOCTL_BASE,1,JSCALE_RSP_T)


/*-----------------------------------------------------------------------------
 * Shared Memory for NetEngine Queues
 *---------------------------------------------------------------------------*/

#define	GEMINI_GMAC_SHARE_BASE		IPI_SHARE_BASE
#define	GEMINI_GMAC_SHARE_SIZE		0x200000	// 2MB total size

/*
* Simple spin lock operations.
*
*/

#define spin_is_locked_dt(x)((x)->lock != 0)

static inline int test_and_set_dt(spinlock_dt *lock)
{
unsigned long tmp;
__asm__ __volatile__(
"swp     %0, %2, [%1]\n"
: "=&r" (tmp)
: "r" (&lock->lock), "r" (1)
: "cc", "memory");

return tmp;
}

static inline void spin_lock_dt(spinlock_dt *lock)
{
/*
unsigned long tmp;
__asm__ __volatile__(
"1:     ldr   %0, [%1]\n"
"teq     %0, #0\n"
"swpeq   %0, %2, [%1]\n"
"       teqeq   %0, #0\n"
"       bne     1b"
       : "=&r" (tmp)
       : "r" (&lock->lock), "r" (1)
       : "cc", "memory");
*/
}

static inline void spin_unlock_dt(spinlock_dt *lock)
{
/*
       __asm__ __volatile__(
"       str     %1, [%0]"
       :
       : "r" (&lock->lock), "r" (0)
       : "cc", "memory");
*/
}

static int getcpuid(void)
{
       int cpuid;

      __asm__(
"mrc p8, 0, r0, c0, c0, 0\n"
"mov %0, r0"
       :"=r"(cpuid)
       :
       :"r0");
       return (cpuid & 0x07);
}



#endif

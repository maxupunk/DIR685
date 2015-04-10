#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <linux/kernel.h>
//#define FFBDBG_LV 100 marco
#define FFBDBG_LV 0
#ifdef FFBDBG_LV
#include <linux/spinlock.h>

#define MAX_DBG_INDENT_LEVEL	3
#define DBG_INDENT_SIZE		3
#define MAX_DBG_MESSAGES	0

static int dbg_indent;
static int dbg_cnt;
static spinlock_t dbg_spinlock = SPIN_LOCK_UNLOCKED;

#define dbg_print(level, format, arg...)                           \
       if (level <= FFBDBG_LV) {                                   \
           if (!MAX_DBG_MESSAGES || dbg_cnt < MAX_DBG_MESSAGES) {  \
               int ind = dbg_indent;                               \
               unsigned long flags;                                \
               spin_lock_irqsave(&dbg_spinlock, flags);            \
               dbg_cnt++;                                          \
               if (ind > MAX_DBG_INDENT_LEVEL)                     \
                  ind = MAX_DBG_INDENT_LEVEL;                      \
	       printk("%*s", ind * DBG_INDENT_SIZE, "");           \
               printk(format, ## arg);                             \
               spin_unlock_irqrestore(&dbg_spinlock, flags);       \
           }                                                       \
       }


#define DBGPRINT	dbg_print

#define DBGENTER(level)	do { \
		dbg_print(level, "%s: Enter\n", __FUNCTION__); \
		dbg_indent++; \
	} while (0)

#define DBGLEAVE(level)	do { \
		dbg_indent--; \
		dbg_print(level, "%s: Leave\n", __FUNCTION__); \
	} while (0)

#else				/* FFBDBG_LV */

#define DBGPRINT(level, format, ...)
#define DBGENTER(level)
#define DBGLEAVE(level)

#endif				/* FFBDBG_LV */

#define err(format, arg...)    printk(KERN_ERR PFX "(%s): " format "\n" , __FUNCTION__, ## arg)
#define warn(format, arg...)   printk(KERN_WARNING PFX "(%s): " format "\n" , __FUNCTION__, ## arg)
#define info(format, arg...)   printk(KERN_INFO PFX ": " format "\n" , ## arg)
#define infos(format, arg...)  printk(KERN_INFO PFX ": " format , ## arg)
#define infom(format, arg...)  printk(format , ## arg)
#define infoe(format, arg...)  printk(format "\n" , ## arg)
#define notice(format, arg...) printk(KERN_NOTICE PFX ": " format "\n" , ## arg)

#endif				/* __DEBUG_H__ */

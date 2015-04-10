#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

//debug_Aaron
//#include <asm/arch/fmem.h>
#include <asm/memory.h>
#include <linux/mm.h>
#include <linux/gfp.h>
void __iomem *__ioremap(unsigned long phys_addr, size_t size, unsigned long flags);
void __iounmap(void __iomem *addr);

#define PFX		       "GM"

#define err(format, arg...)    printk(KERN_ERR PFX "(%s): " format "\n" , __FUNCTION__, ## arg)
#define warn(format, arg...)   printk(KERN_WARNING PFX "(%s): " format "\n" , __FUNCTION__, ## arg)
#define info(format, arg...)   printk(KERN_INFO PFX ": " format "\n" , ## arg)
#define notice(format, arg...) printk(KERN_NOTICE PFX ": " format "\n" , ## arg)


#define FMEM_PROCESS_SINGLE_PAGE
//#define FMEM_DEBUG_MODE

/* to prevent the coherent total size >2MB issue */
void *fmem_alloc(size_t size, dma_addr_t *dma_handle, unsigned long flags)
{
    struct page *page;
    void *cpu_addr = NULL;
    struct page *end;
    
    size = PAGE_ALIGN(size);
#ifdef CONFIG_ISOLATE_HIGHMEM
    page = alloc_pages(GFP_HIGHUSER, get_order(size));
#else
    page = alloc_pages(GFP_KERNEL, get_order(size));
#endif
    if(!page) {
	err("alloc_pages fail! (requested %#x)", size);
	goto no_page;
    }
#ifdef FMEM_DEBUG_MODE
    printk("fmem_alloc 0x%x size 0x%x\n",page_to_phys(page),size);
#endif

    *dma_handle =  page_to_phys(page);

//debug_Aaron
    //cpu_addr = __ioremap(*dma_handle, size, flags, 1);
    cpu_addr = __ioremap(*dma_handle, size, flags);
  
    if(cpu_addr) {
#ifdef FMEM_PROCESS_SINGLE_PAGE
        end = page + (1 << get_order(size));
	    do {
//debug_Aaron
//printk("%s: page=0x%x\r\n", __func__, page);
	        set_page_count(page, 1);
	        SetPageReserved(page);
	        page++;
	    } while (size -= PAGE_SIZE);

		/*
		 * Free the otherwise unused pages.
		 */
		while (page < end) {
			set_page_count(page, 1);
	        if (!PageReserved(page) && put_page_testzero(page))
	            free_cold_page(page);
			page++;
		}
#else
        set_page_count(page, 1);
        SetPageReserved(page);
#endif
    }
    else {
	__free_pages(page, get_order(size));
	err("__ioremap fail! (phy %#x)", *dma_handle);
    }
 no_page:
    return cpu_addr;
}
EXPORT_SYMBOL(fmem_alloc);

void fmem_free(size_t size, void *cpu_addr, dma_addr_t handle)
{
    struct page *page = pfn_to_page(handle >> PAGE_SHIFT);
    struct page *pg;
    unsigned int sz;
    
    pg=page;
    sz=size;

//debug_Aaron
//printk("%s: size=0x%x, cpu_addr=0x%x, handle=0x%x\r\n", __func__, size, cpu_addr, handle);
// printk("fmem_free 0x%x size 0x%x\n",page_to_phys(pg),size);
    __iounmap(cpu_addr);

    size = PAGE_ALIGN(size);

//debug_Aaron
//printk("%s: size=0x%x, cpu_addr=0x%x\r\n", __func__, size, cpu_addr);

#ifdef FMEM_PROCESS_SINGLE_PAGE
    do {
//debug_Aaron
//printk("%s: page=0x%x\r\n", __func__, page);
	    ClearPageReserved(page);
	    if (!PageReserved(page) && put_page_testzero(page))
		{
//printk("%s: free_cold_page(page=0x%x)\r\n", __func__, page);

	        	free_cold_page(page);
		}
	    page++;
    } while (size -= PAGE_SIZE);

#else
    ClearPageReserved(page);
    if (!PageReserved(page) && set_page_count(page, 0))
        __free_pages_ok(page,get_order(size));
#endif

#ifdef FMEM_DEBUG_MODE
    printk("fmem_free 0x%x size 0x%x\n",page_to_phys(pg),size);
#endif

}

EXPORT_SYMBOL(fmem_free);

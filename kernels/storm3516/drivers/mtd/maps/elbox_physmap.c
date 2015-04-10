/* vi: set sw=4 ts=4: */
/* elbox mappings of chips in physical memory */

#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/map.h>
#include <linux/config.h>
#include <linux/mtd/partitions.h>
#include <linux/squashfs_fs.h>
#include <asm/arch/sl2312.h>
#include <linux/mtd/kvctl.h>

#define CONFIG_MTD_PHYSMAP_LEN  0x400000*4*2/*32M*/
#define FLASH_SIZE   CONFIG_MTD_PHYSMAP_LEN
//#define  CONFIG_MTD_PHYSMAP_LEN FLASH_SIZE
#define  CONFIG_MTD_PHYSMAP_BANKWIDTH 2
#define CONFIG_ELBOX_KERNEL_SKIP 0x80000

static struct mtd_info *mymtd;

#define MAX_SIGNATURE	    32
#define IMG_MAX_DEVNAME		32
#define IMG_V2_MAGIC_NO		0x20040220	/* version 2 magic number */
#define IMG_V3_MAGIC_NO		0x20080321	/* version 3 magic number */

typedef struct _imgblock imgblock_t;
struct _imgblock
{
	uint32_t	magic;		/* image magic number (should be IMG_V2_MAGIC_NO in little endian). */
	uint32_t	size;		/* size of the image. */
	uint32_t	offset;		/* offset from the beginning of the storage device. */
	char			devname[IMG_MAX_DEVNAME];	/* null termiated string of the storage device name. ex. "/dev/mtd6" */
	unsigned char	digest[16];	/* MD5 digest of the image */
} __attribute__ ((packed));

typedef struct _imgblockv3 imgblock_tv3;
struct _imgblockv3
{
	uint32_t	magic;		/* image magic number (should be IMG_V2_MAGIC_NO in little endian). */
	char        version[16];/* firmware version ex: v1.00 */
	char        modle[16];  /* Modle name ex:DAP-2553 */
	uint32_t	flag[2];	/* control flag */
	uint32_t	reserve[2];	/* control flag */
	char    	buildno[16];/* build number */
	uint32_t	size;		/* size of the image. */
	uint32_t	offset;		/* offset from the beginning of the storage device. */
	char			devname[IMG_MAX_DEVNAME];	/* null termiated string of the storage device name. ex. "/dev/mtd6" */
	unsigned char	digest[16];	/* MD5 digest of the image */
} __attribute__ ((packed));

typedef struct _imghdr2 imghdr2_t;
struct _imghdr2
{
	char			signature[MAX_SIGNATURE];
	uint32_t	magic;	/* should be IMG_V2_MAGIC_NO in little endian. */
} __attribute__ ((packed));

struct map_info physmap_map =
{
	.name		= "ELBOX physically mapped flash",
	.phys		= SL2312_FLASH_BASE,
	.size		= CONFIG_MTD_PHYSMAP_LEN,
	.bankwidth	= CONFIG_MTD_PHYSMAP_BANKWIDTH,
};

#ifdef CONFIG_MTD_PARTITIONS

static int mtd_parts_nb = 0;

#if 1
static struct mtd_partition physmap_partitions[] =
{
	{
		.name           = "rootfs",
		.offset         = 0x000000,
		.size           = 0x000000,
		.mask_flags     = MTD_WRITEABLE
	},
	{
		.name           = "upgrade",
		.offset         = 0x040000,
		.size           = FLASH_SIZE - 0x20000 - 0x20000 - 0x40000 - 0x40000
	},
	{
		.name			= "rgdb",
		.offset			= FLASH_SIZE - 0x20000-0x20000 - 0x40000,
		.size			= 0x40000
	},
	{
		.name           = "nvram",
		.offset         = FLASH_SIZE - 0x20000 - 0x20000,
		.size           = 0x020000
	},
	{
		.name           = "RedBoot",
		.offset         = 0x000000,
		.size           = 0x040000,			//128K -> 256K
		.mask_flags     = MTD_WRITEABLE
	},
	{
		.name           = "LangPack",	//sonnia
		.offset         = FLASH_SIZE - 0x020000,
		.size           = 0x020000,
//		.mask_flags     = MTD_WRITEABLE	//sonnia
	},
	{
		.name           = "flash",
		.offset         = 0x000000,
		.size           = FLASH_SIZE,
		.mask_flags     = MTD_WRITEABLE
	},
	{
		.name           = NULL
	}
};
#else
static struct mtd_partition physmap_partitions[] =
{
	{
		.name           = "rootfs",
		.offset         = 0x000000,
		.size           = 0x000000,
		.mask_flags     = MTD_WRITEABLE
	},
	{
		.name           = "upgrade",
		.offset         = 0x020000,
		.size           = FLASH_SIZE - 0x20000 - 0x20000 - 0x20000
	},
	{
		.name			= "rgdb",
		.offset			= FLASH_SIZE - 0x20000-0x20000,
		.size			= 0x20000
	},
	{
		.name           = "nvram",
		.offset         = FLASH_SIZE - 0x20000,
		.size           = 0x020000
	},
	{
		.name           = "RedBoot",
		.offset         = 0x000000,
		.size           = 0x020000,
		.mask_flags     = MTD_WRITEABLE
	},
	{
		.name           = "Boot Config",
		.offset         = FLASH_SIZE - 0x020000,
		.size           = 0x020000,
	},
	{
		.name           = "flash",
		.offset         = 0x000000,
		.size           = FLASH_SIZE,
		.mask_flags     = MTD_WRITEABLE
	},
	{
		.name           = NULL
	}
};
#endif

/* the tag is 32 bytes octet,
 * first part is the tag string,
 * and the second half is reserved for future used. */
#define PACKIMG_TAG "--PaCkImGs--"
struct packtag
{
	char tag[16];
	unsigned long size;
	char reserved[12];
};

static struct mtd_partition * __init init_mtd_partitions(struct mtd_info * mtd, size_t size)
{
	struct squashfs_super_block *squashfsb;
	struct packtag *ptag = NULL;
	unsigned char buf[512];
	int off = physmap_partitions[1].offset;
    int shift_hdr = 0;  /* Jack add 18/12/07 */
	size_t len;
	squashfsb = (struct squashfs_super_block *) &(buf[32]);

	/* Skip kernel image, and look at every 64KB boundary */
	for (off /*+= CONFIG_MTD_KERNEL_SKIP*/; off < size; off += (64*1024))
	{
		memset(buf, 0xe5, sizeof(buf));

#if ELBOX_DEBUG
		printk("look for offset : 0x%x\n", off);
#endif
		/* Read block 0 to test for fs superblock */
		if (MTD_READ(mtd, off, sizeof(buf), &len, buf) || len != sizeof(buf))
		{
			continue;
		}

#ifdef ELBOX_DEBUG
		printk("%c%c%c%c%c%c%c%c ...\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
		printk("%02x %02x %02x %02x %02x %02x %02x %02x  ...\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
#endif

		/* Try to find the tag of packimgs, the tag is always at 64K boundary. */
		if (memcmp(buf, PACKIMG_TAG, 12))
		{
		    /* Jack modify 18/12/07 +++ */
		    // if image header in flash, we should shift (sizeof(imghdr2_t) + sizeof(imgblock_tv3) ) to find PACKIMG_TAG
		    if (memcmp(buf+(sizeof(imghdr2_t) + sizeof(imgblock_tv3) ), PACKIMG_TAG, 12))
		    {		        
				continue;
			}
		    else
		    {   
		        printk("shift_hdr:%d exist\n", shift_hdr); 
		        shift_hdr = (sizeof(imghdr2_t) + sizeof(imgblock_tv3) ) ;
		        squashfsb = (struct squashfs_super_block *) &(buf[32+(sizeof(imghdr2_t) + sizeof(imgblock_tv3))]);
		        
		    }
		    //continue;
		    /* Jack modify 18/12/07 --- */
		}

		/* yes, we found it, check for supported file system */

		/* squashfs is at block zero */
		if (squashfsb->s_magic == SQUASHFS_MAGIC)
		{
			printk("OK OK OK \n"); 
			
			printk(KERN_NOTICE
				"%s: squashfs filesystem found at offset %d\n",
				mtd->name, off);
			ptag = (struct packtag *)buf;
			goto done;
		}
	}

	printk(KERN_NOTICE "%s: Couldn't find valid rootfs image!\n", mtd->name);

done:
	if (ptag)
	{
		physmap_partitions[0].offset = off + 32;
		physmap_partitions[0].offset += shift_hdr;  /* Jack add 18/12/07 */
		physmap_partitions[0].size = ntohl(ptag->size);
	}
	else
	{
		physmap_partitions[0].offset = 0;
		physmap_partitions[0].size = 0;
	}

	return physmap_partitions;
}
#endif /* CONFIG_MTD_PARTITIONS */

static int __init init_physmap(void)
{
#ifdef CONFIG_MTD_PARTITIONS
	struct mtd_partition * parts = 0;
#endif

	printk(KERN_NOTICE "ELBOX physmap flash device: %lx at %lx\n", physmap_map.size, physmap_map.phys);
	physmap_map.virt = ioremap(physmap_map.phys, physmap_map.size);

	if (!physmap_map.virt)
	{
		printk("Failed to ioremap\n");
		return -EIO;
	}

	simple_map_init(&physmap_map);
	mymtd = do_map_probe("cfi_probe", &physmap_map);
	if (mymtd)
	{
		mymtd->owner = THIS_MODULE;

#ifdef CONFIG_MTD_PARTITIONS
		parts = init_mtd_partitions(mymtd, physmap_map.size);
		for (mtd_parts_nb=0; parts[mtd_parts_nb].name; mtd_parts_nb++);
		if (mtd_parts_nb > 0)
		{
			add_mtd_partitions(mymtd, parts, mtd_parts_nb);
			return 0;
		}
#endif
		add_mtd_device(mymtd);

		return 0;
	}

	iounmap(physmap_map.virt);
	return -ENXIO;
}
								
static void __exit cleanup_physmap(void)
{
#ifdef CONFIG_MTD_PARTITIONS
	if (mtd_parts_nb)       del_mtd_partitions(mymtd);
	else                    del_mtd_device(mymtd);
#else
	del_mtd_device(mymtd);
#endif
	map_destroy(mymtd);

	iounmap(physmap_map.virt);
	physmap_map.virt = NULL;
}

char chrtohex(char c)
{
  char val;
  if ((c >= '0') && (c <= '9'))
  {
    val = c - '0';
    return val;
  }
  else if ((c >= 'a') && (c <= 'f'))
  {
    val = 10 + (c - 'a');
    return val;
  }
  else if ((c >= 'A') && (c <= 'F'))
  {
    val = 10 + (c - 'A');
    return val;
  }
  printk("<1>Error number\n");
  return 0;
}
int get_vlaninfo(vlaninfo* vlan)
{
	vctl_mheader head;
	vctl_entry entry;
	struct mtd_info *mymtd=NULL;
	int i, j, loc = 0;
	char *payload=0, *tmp1, *tmp2, tmp3[9];
	size_t retlen;

	#ifdef CONFIG_SL2312_SHARE_PIN
	sl2312flash_enable_parallel_flash();
	#endif
	for(i=0;i<MAX_MTD_DEVICES;i++)
	{
		mymtd=get_mtd_device(NULL,i);
		//    printk("mymtd->name: %s\n", mymtd->name);
		if(mymtd && !strcmp(mymtd->name,"VCTL"))
		{
			//      printk("%s\n", mymtd->name);
			break;
		}
	}
	if( i >= MAX_MTD_DEVICES)
	{
		printk("Can't find version control\n");
		#ifdef CONFIG_SL2312_SHARE_PIN
		sl2312flash_disable_parallel_flash();
		#endif
		return 0;
	}

	if (!mymtd | !mymtd->read)
	{
		printk("<1>Can't read Version Configuration\n");
		#ifdef CONFIG_SL2312_SHARE_PIN
		sl2312flash_disable_parallel_flash();
		#endif
		return 0;
	}

	mymtd->read(mymtd, 0, VCTL_HEAD_SIZE, &retlen, (u_char*)&head);
	//  printk("entry header: %c%c%c%c\n", head.header[0], head.header[1], head.header[2], head.header[3]);
	//  printk("entry number: %x\n", head.entry_num);
	if ( strncmp(head.header, "FLFM", 4) )
	{
		printk("VCTL is a erase block\n");
		#ifdef CONFIG_SL2312_SHARE_PIN
		sl2312flash_disable_parallel_flash();
		#endif
		return 0;
	}
	loc += retlen;
	for (i = 0; i < head.entry_num; i++)
	{
		mymtd->read(mymtd, loc, VCTL_ENTRY_LEN, &retlen, (u_char*)&entry);
		//    printk("type: %x\n", entry.type);
		//    printk("size: %x\n", entry.size);
		strncpy(tmp3, entry.header, 4);
		if (entry.type == VCT_VLAN)
		{
			for (j = 0; j < 6 ; j++)
			{
				vlan[0].mac[j] = 0;
				vlan[1].mac[j] = 0;
			}
			vlan[0].vlanid = 1;
			vlan[1].vlanid = 2;
			vlan[0].vlanmap = 0x7F;
			vlan[1].vlanmap = 0x80;

			payload = (char *)kmalloc(entry.size - VCTL_ENTRY_LEN, GFP_KERNEL);
			loc += VCTL_ENTRY_LEN;
			mymtd->read(mymtd, loc, entry.size - VCTL_ENTRY_LEN, &retlen, payload);
			//      printk("%s\n", payload);
			tmp1 = strstr(payload, "MAC1:");
			tmp2 = strstr(payload, "MAC2:");
			if(!tmp1||!tmp2){
				kfree(payload);
				#ifdef CONFIG_SL2312_SHARE_PIN
				sl2312flash_disable_parallel_flash();
				#endif
				printk("Error VCTL format!!\n");
				return;
			}
			tmp1 += 7;
			tmp2 += 7;


			for (j = 0; j < 6; j++)
			{
				vlan[0].mac[j] = chrtohex(tmp1[2*j])*16 + chrtohex(tmp1[(2*j)+1]);
				vlan[1].mac[j] = chrtohex(tmp2[2*j])*16 + chrtohex(tmp2[(2*j)+1]);
			}
			tmp1 = strstr(payload, "ID1:");
			tmp2 = strstr(payload, "ID2:");
			tmp1 += 4;
			tmp2 += 4;
			vlan[0].vlanid = tmp1[0] - '0';
			vlan[1].vlanid = tmp2[0] - '0';
			tmp1 = strstr(payload, "MAP1:");
			tmp2 = strstr(payload, "MAP2:");
			tmp1 += 7;
			tmp2 += 7;
			vlan[0].vlanmap = chrtohex(tmp1[0]) * 16 + chrtohex(tmp1[1]);
			vlan[1].vlanmap = chrtohex(tmp2[0]) * 16 + chrtohex(tmp2[1]);
			//  printk("Vlan1 id:%x map:%02x mac:%x%x%x%x%x%x\n", vlan[0].vlanid, vlan[0].vlanmap, vlan[0].mac[0], vlan[0].mac[1], vlan[0].mac[2], vlan[0].mac[3], vlan[0].mac[4], vlan[0].mac[5]);
			//  printk("Vlan2 id:%x map:%02x mac:%x%x%x%x%x%x\n", vlan[1].vlanid, vlan[1].vlanmap, vlan[1].mac[0], vlan[1].mac[1], vlan[1].mac[2], vlan[1].mac[3], vlan[1].mac[4], vlan[1].mac[5]);
			break;
		}
		loc += entry.size;
	}
	if ( entry.type == VCT_VLAN )
	{
		#ifdef CONFIG_SL2312_SHARE_PIN
		sl2312flash_disable_parallel_flash();
		#endif
		kfree(payload);
		return 1;
	}
	if (i >= head.entry_num)
	printk("Can't find vlan information\n");
	#ifdef CONFIG_SL2312_SHARE_PIN
	sl2312flash_disable_parallel_flash();
	#endif
	return 0;
}

EXPORT_SYMBOL(get_vlaninfo);



module_init(init_physmap);
module_exit(cleanup_physmap);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Hsieh <david_hsieh@alphanetworks.com>");
MODULE_DESCRIPTION("ELBOX MTD map driver");

#include <linux/module.h>  
#include <linux/autoconf.h>  
#include <linux/types.h>  
#include <linux/fs.h>  
#include <linux/init.h>  
#include <asm/uaccess.h>  
#include <linux/proc_fs.h>  
#include <linux/kernel.h>  
#include <linux/mm.h>  
#include <linux/cdev.h>  
#include <linux/list.h>  
#include <asm/io.h>  
#include <linux/input.h>  

#define PFX "PKBD: "  
  
  static int ascii_to_key[] ={      
      0, KEY_LEFT,KEY_RIGHT,KEY_DOWN,KEY_UP, 0,     
  };  

  static struct input_dev *pkbd_dev = NULL;  
  
  static int pkbd_write_proc(struct file *file, const char __user *buffer, unsigned long count, void *data)  
  { 
	int key_num, i;		    

	sscanf(buffer, "%d", key_num); 	
        for(i=0; i<6;i++){	
	 	if (key_num == ascii_to_key[i]) input_report_key(pkbd_dev, ascii_to_key[i], key_num);
	}

	return count;  
  }  
  
  static int __init pkbddev_init(void)  
  {     
    struct proc_dir_entry * pkbd_proc = NULL;   
    int i;      
    pkbd_proc = create_proc_entry("pkbd", 0, NULL);     
    
    if(pkbd_proc) {         
      pkbd_proc->write_proc = pkbd_write_proc;   
    }  
    else {  
      printk (KERN_ERR PFX "Can't create proc entry for pkbd driver.\n");       
      return -EBUSY;    
    }
       
    pkbd_dev = input_allocate_device();     
    
    if (pkbd_dev == NULL) {         
      return -ENODEV;   
    }      
    
  //  init_input_dev(pkbd_dev);   
    pkbd_dev->name = "pkbd";     
    set_bit(EV_KEY, pkbd_dev->evbit);    
    
    for(i = 1; ; i++) {         
      if(ascii_to_key[i] == 0) break;       
      set_bit(ascii_to_key[i], pkbd_dev->keybit);    
    }   
    
    input_register_device(pkbd_dev);    
    return 0;  
  } 
 
  static void __exit pkbddev_exit(void)  
  {     
    if (pkbd_dev) input_unregister_device(pkbd_dev);    
    remove_proc_entry("pkbd", NULL);  
  }
  
  module_init(pkbddev_init);  
  module_exit(pkbddev_exit);  
  MODULE_AUTHOR("Ricky Zheng, <ricky_gz_zheng@yahoo.co.nz>");  
  MODULE_DESCRIPTION("Pseudo Keyboard Driver");  
  MODULE_LICENSE("GPL");  

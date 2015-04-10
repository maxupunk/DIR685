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
/*
  static int dbg = 0;  
  MODULE_PARM(dbg, "i");  
  MODULE_PARM_DESC(dbg, "set dbg=1 enable debug message output to stdout, dbg=0 disable it");  
     
  #define DEBUG_PKBD
     
  #ifdef DEBUG_PKBD  
  
  #define DBG(x...) \  
  	do { \  
           if(dbg) \  
               printk(KERN_INFO PFX x ); \  
       } while(0)  
  #else  
  #define DBG(x...)  
  #endif  
*/     
  #define PFX "PKBD: "  
  
  static unsigned char m_mapedMin = 1;  
  static unsigned char m_mapedMax = 0;  
  static int ascii_to_key[] ={      
     /* 00: ^@ */ 0,  
     /* 01: ^A */ (KEY_LEFTCTRL << 16) | KEY_A,  
     /* 02: ^B */ (KEY_LEFTCTRL << 16) | KEY_B,  
     /* 03: ^C */ (KEY_LEFTCTRL << 16) | KEY_C,  
     /* 04: ^D */ (KEY_LEFTCTRL << 16) | KEY_D,  
     /* 05: ^E */ (KEY_LEFTCTRL << 16) | KEY_E,  
     /* 06: ^F */ (KEY_LEFTCTRL << 16) | KEY_F,  
     /* 07: ^G */ (KEY_LEFTCTRL << 16) | KEY_G,  
     /* 08: ^H */ (KEY_LEFTCTRL << 16) | KEY_H,  
     /* 09: ^I */ (KEY_LEFTCTRL << 16) | KEY_I,  
     /* 0a: ^J */ (KEY_LEFTCTRL << 16) | KEY_J,  
     /* 0b: ^K */ (KEY_LEFTCTRL << 16) | KEY_K,  
     /* 0c: ^L */ (KEY_LEFTCTRL << 16) | KEY_L,  
     /* 0d: ^M */ (KEY_LEFTCTRL << 16) | KEY_M,  
     /* 0e: ^N */ (KEY_LEFTCTRL << 16) | KEY_N,  
     /* 0f: ^O */ (KEY_LEFTCTRL << 16) | KEY_O,  
     /* 10: ^P */ (KEY_LEFTCTRL << 16) | KEY_P,  
     /* 11: ^Q */ (KEY_LEFTCTRL << 16) | KEY_Q,  
     /* 12: ^R */ (KEY_LEFTCTRL << 16) | KEY_R,  
     /* 13: ^S */ (KEY_LEFTCTRL << 16) | KEY_S,  
     /* 14: ^T */ (KEY_LEFTCTRL << 16) | KEY_T,  
     /* 15: ^U */ (KEY_LEFTCTRL << 16) | KEY_U,  
     /* 16: ^V */ (KEY_LEFTCTRL << 16) | KEY_V,  
     /* 17: ^W */ (KEY_LEFTCTRL << 16) | KEY_W,  
     /* 18: ^X */ (KEY_LEFTCTRL << 16) | KEY_X,  
     /* 19: ^Y */ (KEY_LEFTCTRL << 16) | KEY_Y,  
     /* 1a: ^Z */ (KEY_LEFTCTRL << 16) | KEY_Z,  
     /* 1b: ^[ */ (KEY_LEFTCTRL << 16) | KEY_LEFTBRACE,  
     /* 1c: ^\ */ (KEY_LEFTCTRL << 16) | KEY_BACKSLASH,  
     /* 1d: ^] */ (KEY_LEFTCTRL << 16) | KEY_RIGHTBRACE,  
     /* 1e: ^^ */ (KEY_LEFTCTRL << 16) | KEY_6,  
     /* 1f: ^_ */ (KEY_LEFTCTRL << 16) | KEY_MINUS,  
     /* 20: SP */ KEY_SPACE,  
     /* 21: ! */ (KEY_LEFTSHIFT << 16) | KEY_1,  
     /* 22: " */ (KEY_LEFTSHIFT << 16) | KEY_APOSTROPHE,  
     /* 23: # */ (KEY_LEFTSHIFT << 16) | KEY_3,  
     /* 24: $ */ (KEY_LEFTSHIFT << 16) | KEY_4,  
     /* 25: % */ (KEY_LEFTSHIFT << 16) | KEY_5,  
     /* 26: & */ (KEY_LEFTSHIFT << 16) | KEY_7,  
     /* 27: ' */ KEY_APOSTROPHE,  
     /* 28: ( */ (KEY_LEFTSHIFT << 16) | KEY_9,  
     /* 29: ) */ (KEY_LEFTSHIFT << 16) | KEY_0,  
     /* 2a: * */ (KEY_LEFTSHIFT << 16) | KEY_8,  
     /* 2b: + */ (KEY_LEFTSHIFT << 16) | KEY_EQUAL,  
     /* 2c: , */ KEY_COMMA,  
     /* 2d: - */ KEY_MINUS,  
     /* 2e: . */ KEY_DOT,  
     /* 2f: / */ KEY_SLASH,  
     /* 30: 0 */ KEY_0,  
     /* 31: 1 */ KEY_1,  
     /* 32: 2 */ KEY_2,  
    /* 33: 3 */ KEY_3,  
    /* 34: 4 */ KEY_4,  
    /* 35: 5 */ KEY_5,  
    /* 36: 6 */ KEY_6,  
    /* 37: 7 */ KEY_7,  
    /* 38: 8 */ KEY_8,  
    /* 39: 9 */ KEY_9,  
    /* 3a: : */ (KEY_LEFTSHIFT << 16) | KEY_SEMICOLON,  
    /* 3b: ; */ KEY_SEMICOLON,  
    /* 3c: < */ (KEY_LEFTSHIFT << 16) | KEY_COMMA,  
    /* 3d: = */ KEY_EQUAL,  
    /* 3e: > */ (KEY_LEFTSHIFT << 16) | KEY_DOT,  
    /* 3f: ? */ (KEY_LEFTSHIFT << 16) | KEY_SLASH,  
    /* 40: @ */ (KEY_LEFTSHIFT << 16) | KEY_2,  
    /* 41: A */ (KEY_LEFTSHIFT << 16) | KEY_A,  
    /* 42: B */ (KEY_LEFTSHIFT << 16) | KEY_B,  
    /* 43: C */ (KEY_LEFTSHIFT << 16) | KEY_C,  
    /* 44: D */ (KEY_LEFTSHIFT << 16) | KEY_D,  
    /* 45: E */ (KEY_LEFTSHIFT << 16) | KEY_E,  
    /* 46: F */ (KEY_LEFTSHIFT << 16) | KEY_F,  
    /* 47: G */ (KEY_LEFTSHIFT << 16) | KEY_G,  
    /* 48: H */ (KEY_LEFTSHIFT << 16) | KEY_H,  
    /* 49: I */ (KEY_LEFTSHIFT << 16) | KEY_I,  
    /* 4a: J */ (KEY_LEFTSHIFT << 16) | KEY_J,  
    /* 4b: K */ (KEY_LEFTSHIFT << 16) | KEY_K,  
    /* 4c: L */ (KEY_LEFTSHIFT << 16) | KEY_L,  
    /* 4d: M */ (KEY_LEFTSHIFT << 16) | KEY_M,  
    /* 4e: N */ (KEY_LEFTSHIFT << 16) | KEY_N,  
    /* 4f: O */ (KEY_LEFTSHIFT << 16) | KEY_O,  
    /* 50: P */ (KEY_LEFTSHIFT << 16) | KEY_P,  
    /* 51: Q */ (KEY_LEFTSHIFT << 16) | KEY_Q,  
    /* 52: R */ (KEY_LEFTSHIFT << 16) | KEY_R,  
    /* 53: S */ (KEY_LEFTSHIFT << 16) | KEY_S,  
    /* 54: T */ (KEY_LEFTSHIFT << 16) | KEY_T,  
    /* 55: U */ (KEY_LEFTSHIFT << 16) | KEY_U,  
    /* 56: V */ (KEY_LEFTSHIFT << 16) | KEY_V,  
    /* 57: W */ (KEY_LEFTSHIFT << 16) | KEY_W,  
    /* 58: X */ (KEY_LEFTSHIFT << 16) | KEY_X,  
    /* 59: Y */ (KEY_LEFTSHIFT << 16) | KEY_Y,  
    /* 5a: Z */ (KEY_LEFTSHIFT << 16) | KEY_Z,  
    /* 5b: [ */ KEY_LEFTBRACE,  
    /* 5c: \ */ KEY_BACKSLASH,  
    /* 5d: ] */ KEY_RIGHTBRACE,  
    /* 5e: ^ */ (KEY_LEFTSHIFT << 16) | KEY_6,  
    /* 5f: _ */ (KEY_LEFTSHIFT << 16) | KEY_MINUS,  
    /* 60: '  */ KEY_APOSTROPHE,  
    /* 61: a */ KEY_A,  
    /* 62: b */ KEY_B,  
    /* 63: c */ KEY_C,  
    /* 64: d */ KEY_D,  
    /* 65: e */ KEY_E,  
    /* 66: f */ KEY_F,  
    /* 67: g */ KEY_G,  
    /* 68: h */ KEY_H,  
    /* 69: i */ KEY_I,  
    /* 6a: j */ KEY_J,  
    /* 6b: k */ KEY_K,  
    /* 6c: l */ KEY_L,  
    /* 6d: m */ KEY_M,  
    /* 6e: n */ KEY_N,  
    /* 6f: o */ KEY_O,  
    /* 70: p */ KEY_P,  
    /* 71: q */ KEY_Q,  
    /* 72: r */ KEY_R,  
    /* 73: s */ KEY_S,  
    /* 74: t */ KEY_T,  
    /* 75: u */ KEY_U,  
    /* 76: v */ KEY_V,  
    /* 77: w */ KEY_W,  
    /* 78: x */ KEY_X,  
    /* 79: y */ KEY_Y,  
    /* 7a: z */ KEY_Z,  
    /* 7b: { */ (KEY_LEFTSHIFT << 16) | KEY_LEFTBRACE,  
    /* 7c: | */ (KEY_LEFTSHIFT << 16) | KEY_BACKSLASH,  
    /* 7d: } */ (KEY_LEFTSHIFT << 16) | KEY_RIGHTBRACE,  
    /* 7e: ~ */ 0,  
    
    /* TODO: add more keymap here ... */  
    /* 7f: ?? */ 0,  
    /* 80: ?? */ 0,  
    0,    /* end with 0 */  
  };  
  static struct input_dev *pkbd_dev = NULL;  
  
  static int pkbd_write_proc(struct file *file, const char __user *buffer, unsigned long count, void *data)  
  {  
    #define MAX_INPUT_LEN 64  
    unsigned char buf[MAX_INPUT_LEN];  
    int i;  
    if (pkbd_dev) {  
      memset(buf, 0, MAX_INPUT_LEN);  
      if(count > 0 && count < MAX_INPUT_LEN) {  
        copy_from_user(buf, buffer, count);  
        for (i = 0; i < count; i++) {  
          if (buf[i] >= m_mapedMin &&  buf[i] <= m_mapedMax) {  

		int key_code = ascii_to_key[buf[i]];
		switch(key_code){
			case KEY_W:	
					key_code = KEY_0;
					break;			
			case KEY_A:
					key_code = KEY_1;	
					break;
			case KEY_D:
					key_code = KEY_2;
					break;
			case KEY_X:
					key_code = KEY_3;
					break;
			default:
					break;		
		}			
            input_report_key(pkbd_dev, key_code, 1);  
            input_report_key(pkbd_dev, key_code, 0);  
          }  
          }  
      }  
    }  
    return count;  
  }  
  
  static int __init pkbddev_init(void)  
  {     
    struct proc_dir_entry * pkbd_proc = NULL;   
    int i;      
//    dbg = dbg;      
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
    
//    init_input_dev(pkbd_dev);   
    pkbd_dev->name = "pkbd";     
    set_bit(EV_KEY, pkbd_dev->evbit);    
    
    for(i = 1; ; i++) {         
      if(ascii_to_key[i] == 0) break;       
      set_bit(ascii_to_key[i], pkbd_dev->keybit);    
    }   
    
    m_mapedMax = i - 1;     
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

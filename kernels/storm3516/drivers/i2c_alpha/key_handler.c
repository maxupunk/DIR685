#include <linux/input.h> 
#include <asm/uaccess.h> 
#include <linux/proc_fs.h>  
#include <asm/io.h>
#include <asm/hardware.h>
#include <linux/module.h>
int pkbd_dev_init(void);
void key_handler(unsigned int key);
struct input_dev *g_pkbd_dev=NULL;
int i2c_write_proc(struct file *file, const char __user *buffer, unsigned long count, void *data);
int lcd_write_proc(struct file *file, const char __user *buffer, unsigned long count, void *read_data) ;
#define GPIO_BACKLIGHT 16
#if 1
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
    			 KEY_LEFT,
    			 KEY_RIGHT,
    			 KEY_UP,
    			 KEY_DOWN, 
    			 KEY_ENTER,
    /* 7e: ~ */ 0,  
    
    /* TODO: add more keymap here ... */  
    /* 7f: ?? */ 0,  
    /* 80: ?? */ 0,  
    0,    /* end with 0 */  
  };  
#endif
int lcd_write_proc(struct file *file, const char __user *buffer, unsigned long count, void *read_data)  
{  
    #define MAX_INPUT_LEN 32  
    unsigned char buf[MAX_INPUT_LEN];  
    unsigned int addr,value;
    int err=0;  
    memset(buf, 0, MAX_INPUT_LEN);  
#define GPIO_BASE_ADDR      (IO_ADDRESS(SL2312_GPIO_BASE))
enum GPIO_REG
{
    GPIO_DATA_OUT   = 0x00,
    GPIO_DATA_IN    = 0x04,
    GPIO_PIN_DIR    = 0x08,
    GPIO_BY_PASS    = 0x0c,
    GPIO_DATA_SET   = 0x10,
    GPIO_DATA_CLEAR = 0x14,
};
    if(count > 0 && count < MAX_INPUT_LEN) 
    {  

    	copy_from_user(buf, buffer, count);  
    	////////////////////////////////////////
    	if( buf[0]=='0')
		{
			addr = (GPIO_BASE_ADDR + GPIO_PIN_DIR);
			value = readl(addr) | (1<<GPIO_BACKLIGHT);
			writel(value,addr);
			addr = (GPIO_BASE_ADDR + GPIO_DATA_OUT);
			value = readl(addr) & ~((unsigned int)(1<<GPIO_BACKLIGHT));
			
			writel(value,addr);
			
		}
		else if( buf[0]=='1')
		{
			addr = (GPIO_BASE_ADDR + GPIO_PIN_DIR);
			value = readl(addr) | (1<<GPIO_BACKLIGHT);
			writel(value,addr);
			addr = (GPIO_BASE_ADDR + GPIO_DATA_OUT);
			value = readl(addr) | (1<<GPIO_BACKLIGHT);
			
			writel(value,addr);		
		}
    	///////////////////////////////////////
    	
    }
    return count;
}
int i2c_write_proc(struct file *file, const char __user *buffer, unsigned long count, void *read_data)  
{  
    #define MAX_INPUT_LEN 32  
    unsigned char buf[MAX_INPUT_LEN];  
    unsigned char data[]={0xA7,0x40};
    int value;
    int err=0;  
//joel check if the touchpad is not plugin ,do not write data to i2c that cause watchdog reboot,block in I2C_Write
    static int check_touchpad_exist=0;
    if(check_touchpad_exist==0)//check now
    {
    	if(I2C_Device_Detect(0x4d)<0)//not found
    		check_touchpad_exist = -1;
    	else
    		check_touchpad_exist = 1;
    }

    if(check_touchpad_exist != 1)
    {
    	printk("No touchpad found\n");
    	return count;
    }
//---    			

    memset(buf, 0, MAX_INPUT_LEN);  
    if(count > 0 && count < MAX_INPUT_LEN) 
    {  
    	copy_from_user(buf, buffer, count);  
		
		value=simple_strtol(buf,NULL,10);
		data[1]=value;
		 
		//disable interrupt to prevent dead lock with interrupt. siyou 2009/1/8 04:06pm
		local_irq_disable();	
		err=I2C_Write(0x4C, 0x00, &data, 2);
		//enable interrupt.
		local_irq_enable();
	}  
    return count;  
 }  
int pkbd_dev_init(void)
{
	int error;
	
	g_pkbd_dev = input_allocate_device();   
	if (g_pkbd_dev == NULL) 
	{         
      return -ENODEV;   
    } 
    g_pkbd_dev->name = "pkbd";     
    g_pkbd_dev->id.bustype = BUS_HOST;
    set_bit(EV_KEY, g_pkbd_dev->evbit);  
 //   set_bit(BTN_0, g_pkbd_dev->keybit);
  
    int i=0;
    for(i = 1; ; i++) {         
      if(ascii_to_key[i] == 0) break;       
      set_bit(ascii_to_key[i], g_pkbd_dev->keybit);    
    }   
    
	//set_bit(KEY_5, g_pkbd_dev->keybit);
       
    error=input_register_device(g_pkbd_dev);
    if (error) 
    {
		printk(KERN_ERR "button.c:} Failed kbd driver.\n");       
      return -EBUSY; 
 
    }
	return 1;
}
void key_handler(unsigned int key)
{
#if 1//some version
	if(key==0x01)//up
	{
		key = KEY_UP;
		input_report_key(g_pkbd_dev, key, 1);  
        input_report_key(g_pkbd_dev, key, 0);  
	}
	else if(key==0x02)//down
	{
		key = KEY_DOWN;
		input_report_key(g_pkbd_dev, key, 1);  
        input_report_key(g_pkbd_dev, key, 0);  
	}
	else if(key==0x04)//left
	{
		key = KEY_LEFT;
		input_report_key(g_pkbd_dev, key, 1);  
        input_report_key(g_pkbd_dev, key, 0);  
	}
	else if(key==0x08)//right
	{
		key = KEY_RIGHT;
		input_report_key(g_pkbd_dev, key, 1);  
        input_report_key(g_pkbd_dev, key, 0);  
	}
	else if(key==0x10)//enter
	{
		key = KEY_ENTER;
		input_report_key(g_pkbd_dev, key, 1);  
        input_report_key(g_pkbd_dev, key, 0);  
	}
	else if(key==0x20)//WPS
	{
		key = KEY_W;
		input_report_key(g_pkbd_dev, key, 1);  
        input_report_key(g_pkbd_dev, key, 0);  
	}
	else if(key==0x30)//switch port	by sam_pan	
	{	
		key = KEY_O;
		input_report_key(g_pkbd_dev, key, 1);  
        input_report_key(g_pkbd_dev, key, 0);  
	}
#else
	if(key==0x10)//up
	{
		key = KEY_UP;
		input_report_key(g_pkbd_dev, key, 1);  
        input_report_key(g_pkbd_dev, key, 0);  
	}
	else if(key==0x04)//down
	{
		key = KEY_DOWN;
		input_report_key(g_pkbd_dev, key, 1);  
        input_report_key(g_pkbd_dev, key, 0);  
	}
	else if(key==0x08)//left
	{
		key = KEY_LEFT;
		input_report_key(g_pkbd_dev, key, 1);  
        input_report_key(g_pkbd_dev, key, 0);  
	}
	else if(key==0x20)//right
	{
		key = KEY_RIGHT;
		input_report_key(g_pkbd_dev, key, 1);  
        input_report_key(g_pkbd_dev, key, 0);  
	}
	else if(key==0x02)//enter
	{
		key = KEY_ENTER;
		input_report_key(g_pkbd_dev, key, 1);  
        input_report_key(g_pkbd_dev, key, 0);  
	}
	else if(key==0x01)//WPS
	{
		key = KEY_W;
		input_report_key(g_pkbd_dev, key, 1);  
        input_report_key(g_pkbd_dev, key, 0);  
	}
#endif
}
EXPORT_SYMBOL(key_handler);
//EXPORTED_SYMBOL(pkbd_dev_init);

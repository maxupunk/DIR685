/* lcd.c
 *
 * $Id: lcd_sl2312.c,v 1.2 2007/05/11 09:12:58 stone Exp $
 *
 * LCD driver for HD44780 compatible displays connected to the parallel port,
 * because real men use device files.
 *
 * Copyright (C) by Michael McLellan (mikey@mclellan.org.nz)
 * Released under the terms of the GNU GPL, see file COPYING for more details.
 */

#define KBUILD_MODNAME lcd


#include <linux/config.h>
#include <linux/version.h>
#ifndef KERNEL_VERSION
#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#endif
#ifndef LINUX_VERSION_CODE
#define LINUX_VERSION_CODE KERNEL_VERSION(2,2,0)
#endif
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,2,0)
#include <asm/segment.h>
#include <linux/sched.h>
#else
#include <asm/uaccess.h>
#endif
/*#if CONFIG_PARPORT
#include <linux/parport.h>
#elif CONFIG_PARPORT_MODULE
#include <linux/parport.h> 
#warning - Your kernel has parallel-port support compiled as a
#warning - module, you must ensure that the parport module is
#warning - inserted before lcdmod. This should happen automatically
#warning - whenever you send data to /dev/lcd if you "make install"
#else
#warning - Your kernel is not configured with parport support,
#warning - compiling with failsafe outb() functions instead.
#endif */ // PARPORT_CONFIG 
#include <linux/proc_fs.h>
#include <linux/ioport.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <linux/slab.h>
#include <linux/config.h>
#include <linux/kernel.h>
#include "config.h"
#include "charmap.h"
#include "wiring.h"
#include "lcd.h"
#include <asm/arch/sl2312.h>
#include <asm/arch/irqs.h>
#include <asm/system.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <asm-arm/arch-sl2312/hardware.h>

#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,0)
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/config.h>
#include <linux/init.h>
MODULE_LICENSE("GPL");
#endif

#if LINUX_VERSION_CODE > KERNEL_VERSION(2,4,0)
/* does MODULE_LICENSE exist in older kernel trees? */
#include <linux/module.h>
#include <linux/config.h>
#include <linux/init.h>
MODULE_LICENSE("GPL");
#endif

#ifdef CGRAM_DEFAULT
#include "default.h"
#endif
#ifdef CGRAM_SWEDISH
#include "swedish.h"
#endif

#define MAX_DISP_ROWS	4		// The HD44780 supports up to 4 rows
#define MAX_DISP_COLS	40		// The HD44780 supports up to 40 columns

/* input_state states */
#define NORMAL			0
#define ESC				1   	// Escape sequence start
#define DCA_Y			2   	// Direct cursor access, the next input will be the row
#define DCA_X			3   	// Direct cursor access, the next input will be the column
#define CGRAM_SELECT	4		// Selecting which slot to enter new character
#define CGRAM_ENTRY		5		// Adding a new character to the CGRAM
#define CGRAM_GENERATE	6		// Waiting fot the 8 bytes which define a character
#define CHAR_MAP_OLD	7		// Waiting for the original char to map to another
#define CHAR_MAP_NEW	8		// Waiting for the new char to replace the old one with
#define ESC_			10		// Waiting for the [ in escape sequence


/* globals */
/*
#if CONFIG_PARPORT || CONFIG_PARPORT_MODULE
static struct pardevice *pd;
#endif  */
u32 io = IO_ADDRESS(DFLT_BASE);
static int disp_rows = DFLT_DISP_ROWS;
static int disp_cols = DFLT_DISP_COLS;
static unsigned char state[ MAX_DISP_ROWS ][ MAX_DISP_COLS ];	// The current state of the display
static int disp_row = 0, disp_column = 0; 						// Current actual cursor position
static int row = 0, column = 0; 								// Current virtual cursor position
static int wrap = 0;											// Linewrap on/off
static char backlight = BL_ON;		
static unsigned int pLCD_Access= 0xc0013000;	
						// Backlight on-off

#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,0)
static struct cdev *my_cdev; // character device
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,1,0)
MODULE_DESCRIPTION( "LCD parallel port driver for HD44780 compatable controllers" );
MODULE_AUTHOR( "Michael McLellan <mikey@mclellan.org.nz>" );
MODULE_PARM( io, "i" );
MODULE_PARM( disp_rows, "i" );
MODULE_PARM( disp_cols, "i" );
MODULE_PARM_DESC( io, "Parallel port i/o base address (default: DEFAULT_BASE)" );
MODULE_PARM_DESC( disp_rows, "LCD rows (default: DFLT_DISP_ROWS, max: MAX_DISP_ROWS)" );
MODULE_PARM_DESC( disp_cols, "LCD columns (default: DFLT_DISP_COLS, max: MAX_DISP_COLS)" );
#endif


/* Send an instruction to the display, e.g. move cursor */
static void writeCommand( char command, int display )
{
	/* The E cycle time for a write should be at least 500 ns,
	 * and the minimum E pulse width should be 230 ns.
	 */
//#if !CONFIG_PARPORT && !CONFIG_PARPORT_MODULE
//	outb( (display==1?E1_ON:E2_ON) | RS_INST | RW_WRITE | backlight, io + 2 );
//    udelay( 250 );
    outb( command, io );
//    outb( (display==1?E1_OFF:E2_OFF) | RS_INST | RW_WRITE | backlight , io + 2 );
/*#else
	parport_write_control( pd->port, ((display==1?E1_ON:E2_ON) | RS_INST| RW_WRITE) | backlight );
	udelay( 250 );
	parport_write_data( pd->port, command );
	parport_write_control( pd->port, ((display==1?E1_OFF:E2_OFF) | RS_INST | RW_WRITE) | backlight );
	udelay( 250 );
#endif // CONFIG_PARPORT */

#ifdef LOW_VOLTAGE
	/* LOW_VOLTAGE displays operate much slower */
	switch (command)
	{
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x38:
			mdelay( 20 );
			break;
		default:
			udelay( 160 );
			break;
	}
#else
	/* Minimum time to wait after most commands is 39ns except Clear Display
	 * and Return Home which is 1.53ms, we never use Return Home.
	 */
	if( command <= 0x03 )
		mdelay( 1.6 );
	else
		udelay( 40 );
#endif // LOW_VOLTAGE
}




/* LCD Controller register offset 0x18 LCD_Data_Reg */
static void write_Data_register( unsigned int data1 )
{
	writel( data1, io+0x18 );
}

/* LCD Controller register offset 0x10 LCD_Access_Reg */
static void write_Access_register( unsigned int data2 )
{
	writel( data2, io+0x10 );
}

static unsigned int read_Access_register( void )
{
	unsigned int uValue1;
	uValue1=readl(io+0x10);
	return uValue1;
}

static void Polling( void )
{
 unsigned int uValue;
 int i;
 i=0;
	do 
          {
           i++;
           uValue = read_Access_register();
           }while (i<5);
         if ((uValue & 0x80000000) != 0x0)
         printk("LCD Polling fail \n");
}

static void write_Instruct_register( unsigned int data3 )
{
	write_Data_register(data3);
	write_Access_register(pLCD_Access);
	Polling();
}	

static void write_LCD_Data_register( unsigned int data4 )
{
	write_Data_register(data4);
	write_Access_register(pLCD_Access|0x4000);
	Polling();
}



/* Send character data to the display, i.e. writing to DDRAM */
static void writeData( unsigned char data )
{
	/* check and see if we really need to write anything */
	if( state[ row ][ column ] != data )
	{
		state[ row ][ column ] = data;
		/* set the cursor position if need be.
		 * Special case for 16x1 displays, They are treated as two
		 * 8 charcter lines side by side, and dont scroll along to
		 * the second line automaticly.
		 */
		if( disp_row != row || disp_column != column ||
				( disp_rows == 1 && disp_cols == 16 && column == 8 ) )
		{
			if( NUM_CONTROLLERS == 1 )
			{
				/* Some transation done here so 4 line displays work */
				writeCommand( ( row>=2?(row-2)*0x40:row*0x40 ) |
						( row>=2?column+disp_cols:column ) |
						0x80, 1 );
			} else {
				writeCommand( row * 0x40 | column | 0x80, row<2?1:2 );
			}
			disp_row = row;
			disp_column = column;
		}

		/* The E cycle time for a write should be at least 500 ns,
		 * and the minimum E pulse width should be 230 ns.
		 */
//#if !CONFIG_PARPORT && !CONFIG_PARPORT_MODULE
		outb(  (row<2||NUM_CONTROLLERS==1?E1_ON:E2_ON) | RS_DATA | RW_WRITE | backlight, io + 2 );
		udelay( 250 );
		outb( ( unsigned char ) data, io );
		outb(  (row<2||NUM_CONTROLLERS==1?E1_OFF:E2_OFF) | RS_DATA | RW_WRITE | backlight, io + 2 );
/*#else
		parport_write_control( pd->port,(row<2||NUM_CONTROLLERS==1?E1_ON:E2_ON) | RS_DATA | RW_WRITE | backlight );
		udelay( 250 );
		parport_write_data( pd->port, ( unsigned char ) data );
		parport_write_control( pd->port,(row<2||NUM_CONTROLLERS==1?E1_OFF:E2_OFF) | RS_DATA | RW_WRITE | backlight );
#endif */ // CONFIG_PARPORT 
		udelay( 250 );
		/* Time to wait after write to RAM is 43ns */
		udelay( 43 );
		disp_column++;
	}
	if ( column < disp_cols - 1 )
		column++;
	else if ( wrap && column == disp_cols - 1 && row < disp_rows - 1 )
	{
		column = 0;
		row++;
	}
}

/* Write an entire (5x8) character to the CGRAM,
 * takes the CGRAM index, and a char[ 8 ] binary bitmap.
 */
static void writeCGRAM( int index, unsigned char pixels[] )
{
	int i;

	/* Move address pointer to index in CGRAM */
	writeCommand( 0x40 + ( 8 * index ), 1 );
	if( NUM_CONTROLLERS == 2 )
		writeCommand( 0x40 + ( 8 * index ), 2 );
	for( i = 0; i < 8; i++ )
	{
		/* Write a line of a character. The E cycle time for
		 * a write should be at least 500 ns, and the minimum
		 * E pulse width should be 230 ns.
		 */
//#if !CONFIG_PARPORT && !CONFIG_PARPORT_MODULE
		outb (E1_ON | RS_DATA | RW_WRITE | backlight, io + 2);
		udelay( 250 );
		outb( ( unsigned char ) pixels[ i ], io );
		outb( E1_OFF | RS_DATA | RW_WRITE | backlight, io + 2 );

		if( NUM_CONTROLLERS == 2 )
		{
			/* Write to controller 2 */
			outb( E2_ON | RS_DATA | RW_WRITE | backlight, io + 2 );
			udelay( 250 );
			outb( ( unsigned char ) pixels[ i ], io );
			outb( E2_OFF | RS_DATA | RW_WRITE | backlight, io + 2 );
		}
/*#else
		parport_write_control( pd->port, E1_ON | RS_DATA | RW_WRITE | backlight );
		udelay( 250 );
		parport_write_data( pd->port, ( unsigned char ) pixels[ i ] );
		parport_write_control( pd->port, E1_OFF | RS_DATA | RW_WRITE | backlight );
		if( NUM_CONTROLLERS == 2 )
		{ */
			/* Write to controller 2 */
/*			parport_write_control( pd->port, E2_ON | RS_DATA | RW_WRITE | backlight );
			udelay( 250 );
			parport_write_data( pd->port, ( unsigned char ) pixels[ i ] );
			parport_write_control( pd->port, E2_OFF | RS_DATA | RW_WRITE | backlight );
		}
#endif */// CONFIG_PARPORT 
		udelay( 250 );
		/* Time to wait after write to RAM is 43 ns */
		udelay( 45 );
	}
	row = column = -1;
}

static void initDisplay(void)
{
unsigned int    reg_val;   //stone set global reg 0x30 to VBUS on
      reg_val = readl(IO_ADDRESS(0x40000000) + 0x30);
      reg_val = reg_val | 0x00000087; //0x00000087
      writel(reg_val,IO_ADDRESS(0x40000000) + 0x30);
      reg_val = readl(IO_ADDRESS(0x40000000) + 0x30);
      printk("reg_val %x \n",reg_val );

	/* initialize state array */
	memset( state, ' ', sizeof( state ) );
#ifndef CONFIG_SL2312_LCD
	/* initialize controller 1 */
	writeCommand( 0x30, 1 );
	writeCommand( 0x30, 1 );
	writeCommand( 0x38, 1 );    // Function set
	writeCommand( 0x0c, 1 );    // Display on
	writeCommand( 0x01, 1 );    // Clear display
	writeCommand( 0x06, 1 );    // Entry mode set
	writeCommand( 0x02, 1 );	// Cursor home
#else

       printk("pLCD_Access %x\n",pLCD_Access); 
       write_Instruct_register(0x0000002C);

       write_Instruct_register(0x00000008);
       
       write_Instruct_register(0x00000001);
       
       write_Instruct_register(0x00000006);
       
       write_Instruct_register(0x0000000C);
       
#endif
//	if( NUM_CONTROLLERS == 2 )
//	{
		/* initialize controller 2 */
//		writeCommand( 0x30, 2 );
//		writeCommand( 0x30, 2 );
//		writeCommand( 0x38, 2 );    // Function set
//		writeCommand( 0x0c, 2 );    // Display on
//		writeCommand( 0x01, 2 );    // Clear display
//		writeCommand( 0x06, 2 );    // Entry mode set
//		writeCommand( 0x02, 2 );	// Cursor home
//	}
#ifndef CONFIG_SL2312_LCD
	/* Set the CGRAM to default values */
	writeCGRAM( 0, cg0 );
	writeCGRAM( 1, cg1 );
	writeCGRAM( 2, cg2 );
	writeCGRAM( 3, cg3 );
	writeCGRAM( 4, cg4 );
	writeCGRAM( 5, cg5 );
	writeCGRAM( 6, cg6 );
	writeCGRAM( 7, cg7 );
	init_charmap();
#endif
}

static void handleInput( unsigned char input )
{
	static int cgram_index = 0;
	static int cgram_row_count;
	static unsigned char cgram_pixels[ 8 ];
	static unsigned char char_map_old;
	static int input_state = NORMAL; 			// the current state of the input handler
	int i;
	int j;
	int temp;
        
        printk("handleInput\n");
	if ( input_state == NORMAL )
	{
		switch ( input )
		{
			case 0x08: 	// Backspace
				if ( column > 0 )
				{
					column--;
					writeData( ' ' );
					column--;
				}
				break;
			case 0x09: 	// Tabstop
				column = ( ( ( column + 1 ) / TABSTOP ) * TABSTOP ) + TABSTOP - 1;
				break;
			case 0x0a: 	// Newline
				if ( row < disp_rows - 1 )
					row++;
				else
				{
					/* scroll up */
					temp = column;
					for ( i = 0; i < disp_rows - 1; i++ )
					{
						row = i;
						for( j = 0; j < disp_cols; j++ )
						{
							column = j;
							writeData( state[ i + 1 ][ j ] );
						}
					}
					row = disp_rows - 1;
					column = 0;
					for ( i = 0; i < disp_cols; i++ )
					{
						writeData( ' ' );
					}
					column = temp;
				}
				/* Since many have trouble grasping the \r\n concept... */
				column = 0;
				break;
			case 0x0d: 	// Carrage return
				column = 0;
				break;
			case 0x1b: 	// esc ie. start of escape sequence
				input_state = ESC_;
				break;
			default:
				/* The character is looked up in the */
				writeData( charmap[ input ] );
		}
	}
	else if ( input_state == ESC_ )
	{
		input_state = ESC;
	}
	else if ( input_state == ESC )
	{
		if( input <= '7' && input >= '0' )
		{
			/* Chararacter from CGRAM */
			writeData( input - 0x30 );
		} else {
			switch ( input )
			{
				case 'A': 		// Cursor up
					if ( row > 0 )
						row--;
					break;
				case 'B': 		// Cursor down
					if ( row < disp_rows - 1 )
						row++;
					break;
				case 'C': 		// Cursor Right
					if ( column < disp_cols - 1 )
						column++;
					break;
				case 'D': 		// Cursor Left
					if ( column > 0 )
						column--;
					break;
				case 'H': 		// Cursor home
					row = 0;
					column = 0;
					break;
				case 'J': 		// Clear screen, cursor doesn't move
					memset( state, ' ', sizeof( state ) );
					writeCommand( 0x01, 1 );
					if( NUM_CONTROLLERS == 2 )
						writeCommand( 0x01, 2 );
					break;
				case 'K': 		// Erase to end of line, cursor doesn't move
					temp = column;
					for ( i = column; i < disp_cols; i++ )
						writeData( ' ' );
					column = temp;
					break;
				case 'M':		// Charater mapping
					input_state = CHAR_MAP_OLD;
					break;
				case 'Y': 		// Direct cursor access
					input_state = DCA_Y;
					break;
				case 'R':		// CGRAM select
					input_state = CGRAM_SELECT;
					break;
				case 'V':		// Linewrap on
					wrap = 1;
					break;
				case 'W':		// Linewrap off
					wrap = 0;
					break;
               case 'b':       // Toggle backlight
                   backlight = ( backlight == BL_OFF ? BL_ON : BL_OFF );
                   break;
				default:
					printk( "LCD: unrecognized escape sequence: %#x ('%c')\n", input, input );
			}
		}
		if ( input_state != DCA_Y &&
				input_state != CGRAM_SELECT &&
				input_state != CHAR_MAP_OLD )
		{
			input_state = NORMAL;
		}
	}
	else if ( input_state == DCA_Y )
	{
		if ( input - 0x1f < disp_rows )
			row = input - 0x1f;
		else
		{
			printk( "LCD: tried to set cursor to off screen location\n" );
			row = disp_rows - 1;
		}
		input_state = DCA_X;
	}
	else if ( input_state == DCA_X )
	{
		if ( input - 0x1f < disp_cols )
			column = input - 0x1f;
		else
		{
			printk( "LCD: tried to set cursor to off screen location\n" );
			column = disp_cols - 1;
		}
		input_state = NORMAL;
	}
	else if ( input_state == CGRAM_SELECT )
	{
		if( input > '7' || input < '0' )
		{
			printk( "LCD: Bad CGRAM index %c\n", input );
			input_state = NORMAL;
		} else {
			cgram_index = input - 0x30;
			cgram_row_count = 0;
			input_state = CGRAM_GENERATE;
		}
	}
	else if( input_state == CGRAM_GENERATE )
	{
		cgram_pixels[ cgram_row_count++ ] = input;
		if( cgram_row_count == 8 )
		{
			writeCGRAM( cgram_index, cgram_pixels );
			input_state = NORMAL;
		}
	}
	else if( input_state == CHAR_MAP_OLD )
	{
		char_map_old = input;
		input_state = CHAR_MAP_NEW;
	}
	else if( input_state == CHAR_MAP_NEW )
	{
		charmap[ char_map_old ] = input;
		input_state = NORMAL;
	}
}

/* Handle device open */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,2,0)
static int lcd_open( struct inode *minode, struct file *file )
#else
int lcd_open( struct inode *minode, struct file *mfile )
#endif
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
	if ( MOD_IN_USE )
		return -EBUSY;

	MOD_INC_USE_COUNT;
#else
// FIXME : 2.6.x inc use count
#endif
	return ( 0 );
}

/* Handle device file close */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,2,0)
static void lcd_release( struct inode *minode, struct file *mfile )
#else
int lcd_release( struct inode *minode, struct file *mfile )
#endif
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
	MOD_DEC_USE_COUNT;
#else
// FIXME : 2.6.x dec use count
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,2,0)
	return 0;
#endif
}

/* Handle write to device file */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,2,0)
int lcd_write_byte( struct inode *minode, struct file *mfile, const char *gdata, int length )
#else
ssize_t lcd_write_byte( struct file *inode, const char *gdata, size_t length, loff_t *off_what )
#endif
{
	printk("lcd_write_byte\n");
	int i;
	for ( i = 0; i < length; i++ )
		handleInput( gdata[ i ] );
	return ( length );
}

/* Handle read from device file */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,2,0)
int lcd_read_byte( struct inode *inode, struct file *mfile, char *data, int length )
#else
ssize_t lcd_read_byte( struct file *inode, char *udata, size_t length, loff_t *loff_what )
#endif
{
	printk("lcd_read_byte\n");
	return ( EACCES );
}

/* Handle read from proc file */
int readProcFile( char *buffer, char **start, off_t offset, int size, int *eof, void *data )

{
	char *temp = buffer;
	int i, j;

	/* Print module configuration */
	temp += sprintf( temp, "I/O base:        %#x\n"
			"Display rows:    %d\n"
			"Display columns: %d\n"
			"Linewrap:        %s\n\n",
			io, disp_rows, disp_cols,
			wrap?"On":"Off" );

	/* Print display state */
	temp += sprintf( temp, "+" );
	for( i = 0; i < disp_cols; i++ )
		temp += sprintf( temp, "-" );
	temp += sprintf( temp, "+\n" );

	for( i = 0; i < disp_rows; i++ )
	{
		temp += sprintf( temp, "|" );
		for( j = 0; j < disp_cols ; j++ )
			temp += sprintf( temp, "%c", (state[ i ][ j ] < 10)?'·':state[ i ][ j ] );
		temp += sprintf( temp, "|\n" );
	}
	
	temp += sprintf( temp, "+" );
	for( i = 0; i < disp_cols; i++ )
		temp += sprintf( temp, "-" );
	temp += sprintf( temp, "+\n" );
	return temp - buffer;
}

/* Module cleanup */
static void __exit exit_module(void)
{
	writeCommand( 0x01, 1 );
	if( NUM_CONTROLLERS == 2 )
		writeCommand( 0x01, 2 );
//#if !CONFIG_PARPORT && !CONFIG_PARPORT_MODULE
	release_region( io, 3 );
/*#else
 	parport_release( pd );
	parport_unregister_device( pd );
#endif*/ // CONFIG_PARPORT 
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0)
	remove_proc_entry( "lcd", 0 );
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)

	if ( unregister_chrdev( LCD_MAJOR, "LCD panel" ) )
		printk( "LCD: module cleanup failed\n" );
	else
		printk( "LCD: module cleanup OK\n" );
#else
  dev_t dev = MKDEV(LCD_MAJOR,0);
  printk ("LCD: deleting char device %d\n", dev);
  // these functions return void so no error checking possible
  unregister_chrdev_region (dev, 1);
  cdev_del (my_cdev );
#endif
}


static int lcd_ioctl(struct inode *inode, struct file *file,
		     unsigned int cmd, unsigned long arg)
{
	struct lcd_display button_display;
	unsigned long address, a;
	int index;

	switch (cmd) {

        //Clear Display
	case LCD_Clear:
		udelay(150);
                write_Instruct_register(0x00000001);
		break;

        //Return Home
	case LCD_Home:
		udelay(150);
                write_Instruct_register(0x00000002);
		break;
        //Display On Cursor On Blink On
	case LCD_Display_On_Cursor_On_Blink_On:
		udelay(150);
                write_Instruct_register(0x0000000B);
		break;
        //Display Off Cursor On Blink On
	case LCD_Display_Off_Cursor_On_Blink_On:
		udelay(150);
                write_Instruct_register(0x00000008);
		break;
/*
        //Display On Cursor Off Blink On
	case LCD_Display_On_Cursor_Off_Blink_On:
		udelay(150);
                write_Instruct_register(0x0000000D);
		break;

        //Display On Cursor On Blink Off
	case LCD_Display_On_Cursor_On_Blink_Off:
		udelay(150);
                write_Instruct_register(0x0000000E);
		break;

        //Display On Cursor Off Blink Off
	case LCD_Display_On_Cursor_Off_Blink_Off:
		udelay(150);
                write_Instruct_register(0x0000000C);
		break;

        //Display Off Cursor Off Blink On
	case LCD_Display_Off_Cursor_Off_Blink_On:
		udelay(150);
                write_Instruct_register(0x00000009);
		break;

        //Display Off Cursor On Blink Off
	case LCD_Display_Off_Cursor_On_Blink_Off:
		udelay(150);
                write_Instruct_register(0x0000000A);
		break;

        //Display Off Curson Off Blink Off
	case LCD_Display_Off_Cursor_Off_Blink_Off:
		udelay(150);
                write_Instruct_register(0x00000008);
		break;
*/
        //Function set
	case LCD_Reset:
		udelay(150);
                write_Instruct_register(0x00000001);  //Display clear
                write_Instruct_register(0x00000006); //Entry mode set,increase by 1,shift of entire display
		break;
        //Shift all the display to the left ,cursor moves accroding to display
	case LCD_Cursor_Left:
		udelay(150);
                write_Instruct_register(0x00000018);
		break;
        //Shift all the display to the right,cursor moves accroding to the display
	case LCD_Cursor_Right:
		udelay(150);
                write_Instruct_register(0x0000001C);
		break;
/****not modify for lepus LCD controller ***/
	case LCD_Get_Cursor_Pos:{
			struct lcd_display display;

			udelay(150);
			display.cursor_address = (LCDReadInst);
			display.cursor_address =
			    (display.cursor_address & 0x07F);
			if (copy_to_user
			    ((struct lcd_display *) arg, &display,
			     sizeof(struct lcd_display)))
				return -EFAULT;

			break;
		}


	case LCD_Set_Cursor_Pos:{
			struct lcd_display display;

			if (copy_from_user
			    (&display, (struct lcd_display *) arg,
			     sizeof(struct lcd_display)))
				return -EFAULT;

			a = (display.cursor_address | kLCD_Addr);

			udelay(150);
			BusyCheck();
			LCDWriteInst(a);

			break;
		}

	case LCD_Disp_Left:
		udelay(150);
                write_Instruct_register(0x18);
		break;

	case LCD_Disp_Right:
		udelay(150);
                write_Instruct_register(0x1C);
		break;
/*

        case LCD_Dram_Increase_Shift_Right:
                udelay(150);
                write_Instruct_register(0x00000006);
                break;

        case LCD_Dram_Increase_Shift_Left:
                udelay(150);
                write_Instruct_register(0x00000007);
                break;

        case LCD_Dram_Decrease_Shift_Right:
                udelay(150);
                write_Instruct_register(0x00000004);
                break;

        case LCD_Dram_Decrease_Shift_Left:
                udelay(150);
                write_Instruct_register(0x00000005);
                break;
*/
        case LCD_Set_Line1_Dram_Address:
                udelay(150);
                //first addrest of line 1
                write_Instruct_register(0x80);
                //last addrest of line 1
                //write_Instruct_register(0x93);
                break;

        case LCD_Set_Line2_Dram_Address:
                udelay(150);
                //first address of line 2
                //write_Instruct_register(0xC0);
                //last address of line 2
                write_Instruct_register(0xD3);
                break;

	case LCD_Write:{
			struct lcd_ioctl_data display;
                        int string_num,pos;
                           

			if (copy_from_user
			    (&display, (struct lcd_display *) arg,
			     sizeof(struct lcd_display)))
				return -EFAULT;

			udelay(150);
                       
			//write_Instruct_register(0x00000001);
			udelay(150);
                        printk("String is %s\n",display.data);
                        string_num=strlen(display.data); 
                        //printk("Size is %d\n",string_num);
                        //printk("Line is %d\n",display.line);
                        //pos=display.pos;
                        //printk("Posistion is %d\n",pos);
                         
                        if(display.line = 1)
                          {  
                            //write_Instruct_register(0x80);
		 	    for (index = 0; index < string_num; index++) {
				udelay(150);
				write_LCD_Data_register(display.data[index]);
			        }
                           }
                        
                        /*if(display.line = 2)
                          {
                            write_Instruct_register(0xC0);
		 	    for (index = 0; index < string_num; index++) {
				udelay(150);
				write_LCD_Data_register(display.data[index]);
			        }
                          } 
			break;*/
		}
	}
}



/*#if CONFIG_PARPORT || CONFIG_PARPORT_MODULE
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,0) */
/* parport_find_base is missing in 2.2.x kernels
 * Thanks Nick Metcalfe (krane@alphalink.com.au)
 */
/*struct parport *parport_find_base( int io )
{
	struct parport *list;
	list = parport_enumerate();
	while( list != NULL && list->base != io )
		list = list->next;
	return list;
}
#endif
#endif
*/

static test_lcd_0_9(void)
{
	printk("Test 0 to 9  ..... \n");
	printk("pLCD_Access %x\n",pLCD_Access);
       //write_Instruct_register(0x1);
       //add by andy
       write_Instruct_register(0x83);
       
       write_LCD_Data_register(0x30);
       
       write_LCD_Data_register(0x31);
       
       write_LCD_Data_register(0x32);
       
       write_LCD_Data_register(0x33);
       
       write_LCD_Data_register(0x34);	
       
       write_LCD_Data_register(0x35);
       
       write_LCD_Data_register(0x36);
       
       write_LCD_Data_register(0x37);
       
       write_LCD_Data_register(0x38);
       
       write_LCD_Data_register(0x39);
	
}

static test_lcd_A_P(void)
{
	printk("Test A to p  ..... \n");
//write_Instruct_register(0x01);
       write_Instruct_register(0xC3);

       write_LCD_Data_register(0x41);
       
       write_LCD_Data_register(0x42);
       
       write_LCD_Data_register(0x43);
       
       write_LCD_Data_register(0x44);
       
       write_LCD_Data_register(0x45);	
       
       write_LCD_Data_register(0x46);
       
       write_LCD_Data_register(0x47);
       
       write_LCD_Data_register(0x48);
       
       write_LCD_Data_register(0x49);
       
       write_LCD_Data_register(0x4a);
       
//       write_LCD_Data_register(0x4b);
       
//       write_LCD_Data_register(0x4c);
       
//       write_LCD_Data_register(0x4d);
       
//       write_LCD_Data_register(0x4e);
       
//       write_LCD_Data_register(0x4f);	
       
//       write_LCD_Data_register(0x50);
       
//       write_LCD_Data_register(0x51);
       
//       write_LCD_Data_register(0x52);
       
//       write_LCD_Data_register(0x53);
	
}

/* Module initilisation */
static int __init start_module(void)
{

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,2,0)
	static struct file_operations lcd_fops =
	    { NULL, lcd_read_byte, lcd_write_byte, NULL, NULL, NULL, NULL, lcd_open, lcd_release, };
#elif LINUX_VERSION_CODE < KERNEL_VERSION(2,4,0)
	static struct file_operations lcd_fops =
	    { NULL, lcd_read_byte, lcd_write_byte, NULL, NULL, NULL, NULL, lcd_open, NULL, lcd_release, };
#elif  LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
	static struct file_operations lcd_fops =
	    { NULL, NULL, lcd_read_byte, lcd_write_byte, NULL, NULL, NULL, NULL, lcd_open, NULL, lcd_release, };
#else 
        static struct file_operations lcd_fops =
            { NULL, NULL, lcd_read_byte, NULL, lcd_write_byte, NULL, NULL, NULL, lcd_ioctl, NULL, lcd_open, NULL, lcd_release, };
#endif

//#if !CONFIG_PARPORT && !CONFIG_PARPORT_MODULE
	if( check_region( io, 3 ) )
	{
		printk( "LCD: check_region failed, io = %#x\n", io );
		return -EACCES;
//	}
//	else if( request_region( io, 3, "LCD panel" ) )
//	{
//		printk( "LCD: request_region failed, io = %#x\n", io );
//		return -EACCES;
	} else {
/*#else
	static struct parport *pp;

	pp = parport_find_base( io );
	if( !pp )
	{
		printk( "LCD: no parport found at %#x\n", io );
		return -EACCES;
	}

	if( ( pd = parport_register_device( pp, "lcdmod", NULL, NULL,
				NULL, PARPORT_DEV_EXCL, NULL ) ) == NULL )
	{
		printk( "LCD: parport busy\n" );
		return -EBUSY;
	}
	if( parport_claim_or_block( pd ) < 0 )
	{
		printk( "LCD: couldn't claim port\n" );
		parport_release( pd );
		parport_unregister_device( pd );
		return -EAGAIN;
	} else {
#endif	*/ // CONFIG_PARPORT 
		/* Make sure user didn't pass silly numbers, MAX_DISP_???? are just
		 * arbitary numbers and can be increased if need be.
		 */
		disp_rows = disp_rows<=MAX_DISP_ROWS?disp_rows:MAX_DISP_ROWS;
		disp_cols = disp_cols<=MAX_DISP_COLS?disp_cols:MAX_DISP_COLS;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
        if ( register_chrdev( LCD_MAJOR, "LCD panel", &lcd_fops ) )
                {
                        printk( "LCD: Error! Unable to bind to major %d\n", LCD_MAJOR );
//#if !CONFIG_PARPORT && !CONFIG_PARPORT_MODULE
                        release_region( io, 3 );
/*#else
                        parport_release( pd );
                        parport_unregister_device( pd );
#endif */ // CONFIG_PARPORT  
                        return -1;
                }
#else 
		// device number
		dev_t dev = MKDEV(LCD_MAJOR, 0);
		if ( register_chrdev_region(dev, 1, "LCD panel") ) 
		{
		  printk ("LCD: char device register failed\n"); 
		  return -1; 
		} 
		else 
		{
		  printk ("LCD: char device registered\n"); 
		}
		// fill cdev structure
		my_cdev = cdev_alloc();
		my_cdev->owner = THIS_MODULE;
		my_cdev->ops = &lcd_fops;
		kobject_set_name(&my_cdev->kobj, "LCD panel");

		// register it
		if ( cdev_add(my_cdev, dev, 1) ) 
		{ 
		  printk ("LCD char device add failed\n");
//#if !CONFIG_PARPORT && !CONFIG_PARPORT_MODULE
		    release_region( io, 3 );
/*#else
		    parport_release( pd );
		    parport_unregister_device( pd );
#endif */ // CONFIG_PARPORT 
		  return -1; 
		} 
		else 
		  printk ("LCD: char device added\n"); 
		
#endif // LINUX_VERSION_CODE

		initDisplay();
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,4,0)
		if( !create_proc_read_entry( "lcd", 0, 0, readProcFile, NULL ) )
		{
			printk( KERN_ERR "LCD: Error! Can't create /proc/lcd\n" );
			return -ENOMEM;
		}
#endif
		printk( "LCD: init OK, iobase: %#x, rows: %d, columns: %d\n", io, disp_rows, disp_cols );
		
		test_lcd_0_9();
		test_lcd_A_P();
	}
	return 0;
}

module_init(start_module);
module_exit(exit_module);

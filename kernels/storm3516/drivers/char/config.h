/* $Id: config.h,v 1.1 2007/05/07 05:36:21 stone Exp $ */

#define LCDMOD_VERSION "1.0.1"

// Setup the keymap
#define CGRAM_DEFAULT
//#define CGRAM_SWEDISH

#define WIRING_LCDMOD
//#define WIRING_LCDPROC_8_BIT
//#define WIRING_RANDY_RASA
//#define WIRING_WIRING_STUART

#define DFLT_BASE		0x44000000	// Default I/O base address of the parallel port
#define DFLT_DISP_ROWS	2		// Default number of rows the display has
#define DFLT_DISP_COLS	20		// Default number of columns the display has
#define LCD_MAJOR		120		// Major for device file
#define TABSTOP			3		// Length of tabs

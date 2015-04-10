/* wiring.h
 *
 * $Id: wiring.h,v 1.1 2007/05/07 05:38:13 stone Exp $
 *
 * This file defines various wiring schemes.
 *
 * Copyright (C) by Michael McLellan (mikey@cs.auckland.ac.nz)
 * Released under the terms of the GNU GPL, see file COPYING for more details.
 */

/* These defines are for the only availble pins on a parallel port
 * which we can use for output besides pins 2 throuh 9 which are used
 * for data. The address for the below pins is IO + 2 eg. 0x378 + 0x02.
 * Some pins on the parallel port are logicaly reversed which is why
 * some which are ON are 0x00.
 */
#define PIN_1_ON		0x00
#define PIN_1_OFF		0x01
#define PIN_14_ON		0x00
#define PIN_14_OFF		0x02
#define PIN_16_ON		0x04
#define PIN_16_OFF		0x00
#define PIN_17_ON		0x00
#define PIN_17_OFF		0x08

#define E2_ON			0x00
#define E2_OFF			0x00

#ifdef WIRING_LCDMOD
/* My own wiring.
 *
 * parallel 14		RS (LCD 4)
 * grounded			RW (LCD 5)
 * parallel 1		EN (LCD 6)
 */
#define RW_WRITE		0x00	// Not needing in my wiring.
#define E1_ON			PIN_1_ON
#define E1_OFF			PIN_1_OFF
#define RS_DATA			PIN_14_ON
#define RS_INST			PIN_14_OFF
#define BL_ON			PIN_17_OFF
#define BL_OFF			PIN_17_ON
#define NUM_CONTROLLERS	1
#endif

#ifdef WIRING_STUART
/* 4x40 wiring, supplied by Alan Grainger <alan@obvi.us>
 * Originally by Nathan Stuart <nathan.stuart@maine.edu>
 * Info: http://home.iae.nl/users/pouweha/lcd/lcd.shtml
 * Schematic: http://www.eio.com/lcd4034.htm
 *
 * parallel 16          RS (LCD 11)
 * parallel 14          RW (LCD 10)
 * parallel 1           E1 (LCD 9)
 * parallel 17          E2 (LCD 15)
 */
#define RS_DATA			PIN_16_ON
#define RS_INST			PIN_16_OFF
#define RW_READ			PIN_14_ON
#define RW_WRITE		PIN_14_OFF
#define E1_ON			PIN_1_ON
#define E1_OFF			PIN_1_OFF
#undef E2_ON
#undef E2_OFF
#define E2_ON			PIN_17_ON
#define E2_OFF			PIN_17_OFF
#define BL_ON			0x00
#define BL_OFF			0x00
#define NUM_CONTROLLERS 2

#endif

#ifdef WIRING_LCDPROC_8_BIT
/* http://lcdproc.omnipotent.net/
 * wiring from lcdtime aswell?
 *
 * parallel 1		RS (LCD 4)
 * parallel 14		RW (LCD 5)
 * parallel 16		EN (LCD 6)
 */
#define RW_WRITE		PIN_14_OFF
#define RS_DATA			PIN_1_ON
#define RS_INST			PIN_1_OFF
#define E1_ON			PIN_16_ON
#define E1_OFF			PIN_16_OFF
#define BL_ON			PIN_17_OFF
#define BL_OFF			PIN_17_ON
#define NUM_CONTROLLERS	1
#endif

#ifdef WIRING_RANDY_RASA
/* This scheme used by lots of other software, including LCDProc.
 * http://www.geocities.com/ResearchTriangle/1495/ee_lcd.html
 * http://www.eio.com/lcd2014.htm
 * http://www.rendo.dekooi.nl/~fjbgp/smartie/
 * http://lcdproc.omnipotent.net/
 *
 * parallel 16		RS (LCD 4)
 * parallel 14		RW (LCD 5)
 * parallel 1		EN (LCD 6)
 */
#define RW_WRITE		PIN_14_OFF
#define RS_DATA			PIN_16_ON
#define RS_INST			PIN_16_OFF
#define E1_ON			PIN_1_ON
#define E1_OFF			PIN_1_OFF
/* Backlight (BL) not used by all the other sotware */
#define BL_ON			PIN_17_OFF
#define BL_OFF			PIN_17_ON
#define NUM_CONTROLLERS	1
#endif

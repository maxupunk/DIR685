/******************************************************************************
 *    proslic.h
 *
 *
 *****************************************************************************/
#include <linux/types.h>

#define BITFIELD_MASK( FIELD ) ((1<<(FIELD##_LEN))-1) << (FIELD##_POS)
/* Direct registers */
#define PROSLIC_SPI_MODE_SEL_REG				0
#define PROSLIC_PCM_MODE_SEL_REG				1
#define PROSLIC_LOOPBACK_REG					8
#define PROSLIC_IMPEDANCE_REG					10
#define PROSLIC_HYBRID_CTRL_REG					11
#define PROSLIC_POWER_DOWN1_CTRL_REG	        14
#define PROSLIC_INT1_STATUS_REG					18
#define PROSLIC_INT2_STATUS_REG					19
#define PROSLIC_INT3_STATUS_REG					20
#define PROSLIC_INT1_MASK_REG					21
#define PROSLIC_INT2_MASK_REG					22
#define PROSLIC_INT3_MASK_REG					23
#define PROSLIC_DTMF_REG						24
#define PROSLIC_IND_DATA_LOW_REG				28
#define PROSLIC_IND_DATA_HIGH_REG				29
#define PROSLIC_IND_ADDR_REG					30
#define PROSLIC_IND_STATUS_REG					31
#define PROSLIC_OSC1_CTRL_REG					32
#define PROSLIC_OSC2_CTRL_REG					33
#define PROSLIC_RING_OSC_CTRL_REG				34

#define PROSLIC_OSC1_ACTTIME_LOW_REG			36
#define PROSLIC_OSC1_ACTTIME_HIGH_REG			37
#define PROSLIC_OSC1_INACTTIME_LOW_REG			38
#define PROSLIC_OSC1_INACTTIME_HIGH_REG			39
#define PROSLIC_OSC2_ACTTIME_LOW_REG			40
#define PROSLIC_OSC2_ACTTIME_HIGH_REG			41
#define PROSLIC_OSC2_INACTTIME_LOW_REG			42
#define PROSLIC_OSC2_INACTTIME_HIGH_REG			43

#define PROSLIC_RING_OSC_ACTIVE_TIMERL			48
#define PROSLIC_RING_OSC_ACTIVE_TIMERH			49
#define PROSLIC_RING_OSC_INACTIVE_TIMERL		50
#define PROSLIC_RING_OSC_INACTIVE_TIMERH		51
#define PROSLIC_FSK_DATA						52
#define PROSLIC_LINEFEED_CTRL_REG				64
#define PROSLIC_BATT_FEED_CTRL_REG				66
#define PROSLIC_AUTO_MANUAL_CTRL_REG			67
#define PROSLIC_OFF_HOOK_STATUS_REG				68
#define PROSLIC_LOOP_CLOSURE_DEBOUNCE_REG		69
#define PROSLIC_RING_TRIP_DEBOUNCE_REG			70
#define PROSLIC_LOOP_CUR_LIMIT_REG				71
#define PROSLIC_ONHOOK_VOLTAGE_REG				72
#define PROSLIC_ACTIVE_VOLTAGE_REG				73
#define PROSLIC_VBAT_HIGH_REG					74
#define PROSLIC_VBAT_LOW_REG					75
#define PROSLIC_LOOP_VOLTAGE_SENSE_REG			78
#define PROSLIC_LOOP_CUR_SENSE_REG				79
#define PROSLIC_TIP_VOLTAGE_SENSE_REG			80
#define PROSLIC_RING_VOLTAGE_SENSE_REG			81
#define PROSLIC_VBAT_HIGH_SENSE_REG				82
#define PROSLIC_VBAT_LOW_SENSE_REG				83
#define	PROSLIC_IQ1_REG							84
#define	PROSLIC_IQ2_REG							85
#define	PROSLIC_IQ3_REG							86
#define	PROSLIC_IQ4_REG							87
#define	PROSLIC_IQ5_REG							88
#define	PROSLIC_IQ6_REG							89
#define PROSLIC_DC_TO_DC_PERIOD_REG				92
#define PROSLIC_DC_TO_DC_SWITCH_REG				93
#define PROSLIC_DC_TO_DC_PWM_REG				94
#define PROSLIC_CALIBRATION1_REG				96
#define PROSLIC_CALIBRATION2_REG				97
#define PROSLIC_RING_GAIN_MIS_CALIB_REG			98
#define PROSLIC_TIP_GAIN_MIS_CALIB_REG			99
#define PROSLIC_REV_C_ENH_REG					108

/* Indirect registers */
#define PROSLIC_IND_DTMF_ROW0_THRESH_REG		        0
#define PROSLIC_IND_DTMF_ROW1_THRESH_REG		        1
#define PROSLIC_IND_DTMF_ROW2_THRESH_REG		        2
#define PROSLIC_IND_DTMF_ROW3_THRESH_REG		        3
#define PROSLIC_IND_DTMF_COL_THRESH_REG			        4
#define PROSLIC_IND_DTMF_FOR_TWIST_THRESH_REG	        5
#define PROSLIC_IND_DTMF_REV_TWIST_THRESH_REG	        6
#define PROSLIC_IND_DTMF_ROW_RATIO_THRESH_REG	        7
#define PROSLIC_IND_DTMF_COL_RATIO_THRESH_REG	        8
#define PROSLIC_IND_DTMF_ROW_2ND_THRESH_REG		        9
#define PROSLIC_IND_DTMF_COL_2ND_THRESH_REG		        10
#define PROSLIC_IND_DTMF_POW_MIN_THRESH_REG		        11
#define PROSLIC_IND_DTMF_HOT_LIM_THRESH_REG		        12
#define PROSLIC_IND_OSC1_FREQ_COEFF_REG			        13
#define PROSLIC_IND_OSC1_INIT1_REG						14
#define PROSLIC_IND_OSC1_INIT2_REG						15
#define PROSLIC_IND_OSC2_FREQ_COEFF_REG			        16
#define PROSLIC_IND_OSC2_INIT1_REG						17
#define PROSLIC_IND_OSC2_INIT2_REG						18
#define PROSLIC_IND_RING_OSC_DC_OFFSET_REG		        19
#define PROSLIC_IND_RING_OSC_FREQ_COEFF_REG		        20
#define PROSLIC_IND_RING_OSC_INIT1_REG			        21
#define PROSLIC_IND_RING_OSC_INIT2_REG			        22
#define PROSLIC_IND_PM_OSC_RATE_REG						23
#define PROSLIC_IND_PM_OSC_INIT_REG						24
#define PROSLIC_IND_PM_OSC_FREQ_COEFF_REG		        25
#define PROSLIC_IND_DAC_GAIN_REG						26
#define PROSLIC_IND_ADC_GAIN_REG						27
#define PROSLIC_IND_LOOP_CLOSURE_THRESH_REG		        28
#define PROSLIC_IND_RING_TRIP_THRESH_REG		        29
#define PROSLIC_IND_ACTIVE_MIN_THRESH_REG		        30
#define PROSLIC_IND_ACTIVE_MAX_THRESH_REG		        31
#define PROSLIC_IND_PWR_ALARM_Q12_THRESH_REG	        32
#define PROSLIC_IND_PWR_ALARM_Q34_THRESH_REG	        33
#define PROSLIC_IND_PWR_ALARM_Q56_THRESH_REG	        34
#define PROSLIC_IND_LOOP_CLOSURE_FILT_COEFF_REG	        35
#define PROSLIC_IND_RING_TRIP_FILT_COEFF_REG	        36
#define PROSLIC_IND_LPFP_Q12_REG						37
#define PROSLIC_IND_LPFP_Q34_REG						38
#define PROSLIC_IND_LPFP_Q56_REG						39
#define PROSLIC_IND_ACTIVE_BIAS_ADJ_RING_REG	        40
#define PROSLIC_IND_DC_TO_DC_MIN_VOLTAGE_REG	        41
#define PROSLIC_IND_DC_TO_DC_EXTRA_VOLTAGE_REG	        42
#define	PROSLIC_IND_FSK_X_0		99	/*	x	sign				fsk_x_0[15:0]												*/
#define	PROSLIC_IND_FSK_COEFF_0	100	/*	x	sign				fsk_coeff_0[15:0]												*/
#define	PROSLIC_IND_FSK_X_1		101	/*	x	sign				fsk_x_1[15:0]												*/
#define	PROSLIC_IND_FSK_COEFF_1	102	/*	x	sign				fsk_coeff_1[15:0]												*/
#define	PROSLIC_IND_FSK_X_01	103	/*	x	sign				fsk_x_01[15:0]												*/
#define	PROSLIC_IND_FSK_X_10	104	/*	x	sign				fsk_x_10[15:0]												*/

#define ERRORCODE_LONGBALCAL -2;


/* Register field bit positions */

/* Register 1 */
#define PROSLIC_PCM_XFER_SIZE_POS				2
#define PROSLIC_PCM_FORMAT_POS					3
#define PROSLIC_PCM_ENABLE_POS					5
/* Register 10 */
#define PROSLIC_TWO_WIRE_IMP_POS				0
#define PROSLIC_TWO_WIRE_IMP_ENA_POS			        3
#define PROSLIC_LINE_CAP_POS					4
/* Register 11 */
#define PROSLIC_AUD_HYBRID_POS					0
/* Register 19 */
#define PROSLIC_RING_TRIP_INT_POS				0
#define PROSLIC_LOOP_CLOSURE_INT_POS			        1
#define PROSLIC_POWER_ALARM_INT_POS				2
/* Register 20 */
#define PROSLIC_DTMF_INT_POS					0
/* Register 22 */
#define PROSLIC_RING_TRIP_INT_EN_POS			        0
#define PROSLIC_LOOP_CLOSURE_INT_EN_POS			        1
#define PROSLIC_POWER_ALARM_INT_EN_POS			        2
/* Register 23 */
#define PROSLIC_DTMF_INT_EN_POS					0
/* Register 24 */
#define PROSLIC_DTMF_DIGIT_POS					0
#define PROSLIC_DTMF_VALID_POS					4
/* Register 34 */
#define PROSLIC_RING_OSC_EN_POS					2
/* Register 64 */
#define PROSLIC_SLIC_STATE_POS					0
/* Register 68 */
#define PROSLIC_LOOP_CLOSURE_POS				0
#define PROSLIC_RING_TRIP_POS					1
/* Register 96 */
#define PROSLIC_CALIBRATION_STATUS_POS			        6

/* Register field lengths */

/* Register 1 */
#define PROSLIC_PCM_XFER_SIZE_LEN				1
#define PROSLIC_PCM_FORMAT_LEN					2
#define PROSLIC_PCM_ENABLE_LEN					1
/* Register 10 */
#define PROSLIC_TWO_WIRE_IMP_LEN				3
#define PROSLIC_TWO_WIRE_IMP_ENA_LEN			        1
#define PROSLIC_LINE_CAP_LEN					2
/* Register 11 */
#define PROSLIC_AUD_HYBRID_LEN					3
/* Register 19 */
#define PROSLIC_RING_TRIP_INT_LEN				1
#define PROSLIC_LOOP_CLOSURE_INT_LEN			        1
#define PROSLIC_POWER_ALARM_INT_LEN				6
/* Register 20 */
#define PROSLIC_DTMF_INT_LEN					1
/* Register 22 */
#define PROSLIC_RING_TRIP_INT_EN_LEN			        1
#define PROSLIC_LOOP_CLOSURE_INT_EN_LEN			        1
#define PROSLIC_POWER_ALARM_INT_EN_LEN			        6
/* Register 23 */
#define PROSLIC_DTMF_INT_EN_LEN					1
/* Register 24 */
#define PROSLIC_DTMF_DIGIT_LEN					4
#define PROSLIC_DTMF_VALID_LEN					1
/* Register 34 */
#define PROSLIC_RING_OSC_EN_LEN					1
/* Register 64 */
#define PROSLIC_SLIC_STATE_LEN					3
/* Register 68 */
#define PROSLIC_LOOP_CLOSURE_LEN				1
#define PROSLIC_RING_TRIP_LEN					1
/* Register 96 */
#define PROSLIC_CALIBRATION_STATUS_LEN			        1

/* Register fields */
/* Register 1 */
#define PROSLIC_PCM_XFER_SIZE	    BITFIELD_MASK( PROSLIC_PCM_XFER_SIZE )
#define PROSLIC_PCM_FORMAT	    	BITFIELD_MASK( PROSLIC_PCM_FORMAT )
#define PROSLIC_PCM_ENABLE	    	BITFIELD_MASK( PROSLIC_PCM_ENABLE )

#define PROSLIC_PCM_FORMAT_ALAW	    0
#define PROSLIC_PCM_FORMAT_MULAW    (1<<PROSLIC_PCM_FORMAT_POS)
#define PROSLIC_PCM_FORMAT_LINEAR   (3<<PROSLIC_PCM_FORMAT_POS)

#define PROSLIC_PCM_XFER_SIZE_8BIT  0
#define PROSLIC_PCM_XFER_SIZE_16BIT (1<<PROSLIC_PCM_XFER_SIZE_POS)

#define PROSLIC_PCM_ENABLE_OFF	    0
#define PROSLIC_PCM_ENABLE_ON	    (1<<PROSLIC_PCM_ENABLE_POS)

/* Register 10 */
#define PROSLIC_TWO_WIRE_IMP	    BITFIELD_MASK( PROSLIC_TWO_WIRE_IMP )
#define PROSLIC_TWO_WIRE_IMP_ENA    BITFIELD_MASK( PROSLIC_TWO_WIRE_IMP_ENA )
#define PROSLIC_LINE_CAP	    	BITFIELD_MASK( PROSLIC_LINE_CAP )
/* Register 11 */
#define PROSLIC_AUD_HYBRID	    	BITFIELD_MASK( PROSLIC_AUD_HYBRID )
/* Register 19 */
#define PROSLIC_RING_TRIP_INT	    BITFIELD_MASK( PROSLIC_RING_TRIP_INT )
#define PROSLIC_LOOP_CLOSURE_INT    BITFIELD_MASK( PROSLIC_LOOP_CLOSURE_INT )
#define PROSLIC_POWER_ALARM_INT	    BITFIELD_MASK( PROSLIC_POWER_ALARM_INT )
/* Register 20 */
#define PROSLIC_DTMF_INT	   		BITFIELD_MASK( PROSLIC_DTMF_INT )
/* Register 22 */
#define PROSLIC_RING_TRIP_INT_EN    BITFIELD_MASK( PROSLIC_RING_TRIP_INT_EN )
#define PROSLIC_LOOP_CLOSURE_INT_EN BITFIELD_MASK(PROSLIC_LOOP_CLOSURE_INT_EN)
#define PROSLIC_POWER_ALARM_INT_EN  BITFIELD_MASK( PROSLIC_POWER_ALARM_INT_EN)
/* Register 23 */
#define PROSLIC_DTMF_INT_EN	    	BITFIELD_MASK( PROSLIC_DTMF_INT_EN )
/* Register 24 */
#define PROSLIC_DTMF_DIGIT	    	BITFIELD_MASK( PROSLIC_DTMF_DIGIT )
#define PROSLIC_DTMF_VALID	    	BITFIELD_MASK( PROSLIC_DTMF_VALID )
/* Register 34 */
#define PROSLIC_RING_OSC_EN	    	BITFIELD_MASK( PROSLIC_RING_OSC_EN )
/* Register 64 */
#define PROSLIC_SLIC_STATE	    	BITFIELD_MASK( PROSLIC_SLIC_STATE )
/* Register 68 */
#define PROSLIC_LOOP_CLOSURE	    BITFIELD_MASK( PROSLIC_LOOP_CLOSURE )
#define PROSLIC_RING_TRIP	    	BITFIELD_MASK( PROSLIC_RING_TRIP )
/* Register 96 */
#define PROSLIC_CALIBRATION_STATUS  BITFIELD_MASK(PROSLIC_CALIBRATION_STATUS)


#define	DIALTONE_IR13	0x7b30	//tone_struct DialTone = {  /* OSC1= 350 Hz OSC2= 440 Hz .0975 Volts -18 dBm */
#define	DIALTONE_IR14	0x0063	
#define	DIALTONE_IR16	0x7870	
#define	DIALTONE_IR17	0x007d	
#define	DIALTONE_DR32	6	
#define	DIALTONE_DR33	6	
#define	DIALTONE_DR36	0	
#define	DIALTONE_DR37	0	
#define	DIALTONE_DR38	0	
#define	DIALTONE_DR39	0	
#define	DIALTONE_DR40	0	
#define	DIALTONE_DR41	0	
#define	DIALTONE_DR42	0	
#define	DIALTONE_DR43	0	

#define	REORDERTONE_IR13	0x7700	//"//tone_struct ReorderTone = {	/* OSC1= 480 Hz OSC2 = 620 .0975 Volts -18 dBm */"
#define	REORDERTONE_IR14	0x0089	
#define	REORDERTONE_IR16	0x7120	
#define	REORDERTONE_IR17	0x00B2	
#define	REORDERTONE_DR32	0x1E	
#define	REORDERTONE_DR33	0x1E	
#define	REORDERTONE_DR36	0x60	
#define	REORDERTONE_DR37	0x09	
#define	REORDERTONE_DR38	0x40	
#define	REORDERTONE_DR39	0x06	
#define	REORDERTONE_DR40	0x60	
#define	REORDERTONE_DR41	0x09	
#define	REORDERTONE_DR42	0x40	
#define	REORDERTONE_DR43	0x06	


//one_struct BusySignal = { /* OSC1= 480  OSC2 = 620 .0975 Voltz -18 dBm 8*/
//	{0x7700,0x0089,0,0x0f,0xa0,0x0f,0xa0},{0x7120,0x00b2,0,0x0f,0xa0,0x0f,0xa0}
//};
#define	BUSYTONE_IR13	0x7700	//tone_struct BusySignal = { /* OSC1= 480  OSC2 = 620 .0975 Voltz -18 dBm 8*/
#define	BUSYTONE_IR14	0x0089	
#define	BUSYTONE_IR16	0x7120	
#define	BUSYTONE_IR17	0x00B2	
#define	BUSYTONE_DR32	0x1E	
#define	BUSYTONE_DR33	0x1E	
#define	BUSYTONE_DR36	0xa0	
#define	BUSYTONE_DR37	0x0f	
#define	BUSYTONE_DR38	0xa0	
#define	BUSYTONE_DR39	0x0f	
#define	BUSYTONE_DR40	0xa0	
#define	BUSYTONE_DR41	0x0f	
#define	BUSYTONE_DR42	0xa0	
#define	BUSYTONE_DR43	0x0f	
			//tone_struct RingbackNormal = { /* OSC1 = 440 Hz OSC2 = 480 .0975 Volts -18 dBm */
#define	RINGBACKTONE_IR13	0x7870	
#define	RINGBACKTONE_IR14	0x007D	
#define	RINGBACKTONE_IR16	0x7700	
#define	RINGBACKTONE_IR17	0x0089	
#define	RINGBACKTONE_DR32	0x1E	
#define	RINGBACKTONE_DR33	0x1E	
#define	RINGBACKTONE_DR36	0x80	
#define	RINGBACKTONE_DR37	0x3E	
#define	RINGBACKTONE_DR38	0x0	
#define	RINGBACKTONE_DR39	0x7d	
#define	RINGBACKTONE_DR40	0x80	
#define	RINGBACKTONE_DR41	0x3E	
#define	RINGBACKTONE_DR42	0x0	
#define	RINGBACKTONE_DR43	0x7d	
			
#define	RINGBACKPBXTONE_IR13	0x7870 //	"//tone_struct RingbackPBX = {	/* OSC1 = 440 Hz OSC2= 480 .0975 Volts -18 dBM */"
#define	RINGBACKPBXTONE_IR14	0x007D	
#define	RINGBACKPBXTONE_IR16	0x7700	
#define	RINGBACKPBXTONE_IR17	0x0089	
#define	RINGBACKPBXTONE_DR32	0x1E	
#define	RINGBACKPBXTONE_DR33	0x1E	
#define	RINGBACKPBXTONE_DR36	0x40	
#define	RINGBACKPBXTONE_DR37	0x1f	
#define	RINGBACKPBXTONE_DR38	0xc0	
#define	RINGBACKPBXTONE_DR39	0x5d	
#define	RINGBACKPBXTONE_DR40	0x40	
#define	RINGBACKPBXTONE_DR41	0x1f	
#define	RINGBACKPBXTONE_DR42	0xc0	
#define	RINGBACKPBXTONE_DR43	0x5d	

#define	CONGESTIONTONE_IR13	0x7700	//tone_struct CongestionTone = { /* OSC1= 480 Hz OSC2 = 620 .0975 Volts -18 dBM */
#define	CONGESTIONTONE_IR14	0x0089	
#define	CONGESTIONTONE_IR16	0x7120	
#define	CONGESTIONTONE_IR17	0x00B2	
#define	CONGESTIONTONE_DR32	0x1E	
#define	CONGESTIONTONE_DR33	0x1E	
#define	CONGESTIONTONE_DR36	0x40	
#define	CONGESTIONTONE_DR37	0x06	
#define	CONGESTIONTONE_DR38	0x60	
#define	CONGESTIONTONE_DR39	0x09	
#define	CONGESTIONTONE_DR40	0x40	
#define	CONGESTIONTONE_DR41	0x06	
#define	CONGESTIONTONE_DR42	0x60	
#define	CONGESTIONTONE_DR43	0x09	

#define	INIT_DR0	0X00	//	Serial Interface
#define	INIT_DR1	0X28	//	PCM Mode
#define	INIT_DR2	0X00	//	PCM TX Clock Slot Low Byte (1 PCLK cycle/LSB)
#define	INIT_DR3	0x00	//	PCM TX Clock Slot High Byte
#define	INIT_DR4	0x00	//	PCM RX Clock Slot Low Byte (1 PCLK cycle/LSB)
#define	INIT_DR5	0x00	//	PCM RX Clock Slot High Byte
#define	INIT_DR6	0x00	//	DIO Control (external battery operation, Si3211/12)
#define	INIT_DR8	0X00	//	Loopbacks (digital loopback default)
#define	INIT_DR9	0x00	//	Transmit and receive path gain and control
#define	INIT_DR9_MUTE	0x30	//	Transmit and receive path gain and control
#define	INIT_DR10	0X28	//	Initialization Two-wire impedance (600  and enabled)
#define	INIT_DR11	0x33	//	Transhybrid Balance/Four-wire Return Loss
#define	INIT_DR14	0X10	//	Powerdown Control 1
#define	INIT_DR15	0x00	//	Initialization Powerdown Control 2
#define	INIT_DR18	0xff	//	Normal Oper. Interrupt Register 1 (clear with 0xFF)
#define	INIT_DR19	0xff	//	Normal Oper. Interrupt Register 2 (clear with 0xFF)
#define	INIT_DR20	0xff	//	Normal Oper. Interrupt Register 3 (clear with 0xFF)
#define	INIT_DR21	0xff	//	Interrupt Mask 1
#define	INIT_DR22	0xff	//	Initialization Interrupt Mask 2
#define	INIT_DR23	0xff	//	 Initialization Interrupt Mask 3
#define	INIT_DR32	0x00	//	Oper. Oscillator 1 Control—tone generation
#define	INIT_DR33	0x00	//	Oper. Oscillator 2 Control—tone generation
#define	INIT_DR34	0X18	//	34 0x22 0x00 Initialization Ringing Oscillator Control
#define	INIT_DR35	0x00	//	Oper. Pulse Metering Oscillator Control
#define	INIT_DR36	0x00	//	36 0x24 0x00 Initialization OSC1 Active Low Byte (125 µs/LSB)
#define	INIT_DR37	0x00	//	37 0x25 0x00 Initialization OSC1 Active High Byte (125 µs/LSB)
#define	INIT_DR38	0x00	//	38 0x26 0x00 Initialization OSC1 Inactive Low Byte (125 µs/LSB)
#define	INIT_DR39	0x00	//	39 0x27 0x00 Initialization OSC1 Inactive High Byte (125 µs/LSB)
#define	INIT_DR40	0x00	//	40 0x28 0x00 Initialization OSC2 Active Low Byte (125 µs/LSB)
#define	INIT_DR41	0x00	//	41 0x29 0x00 Initialization OSC2 Active High Byte (125 µs/LSB)
#define	INIT_DR42	0x00	//	42 0x2A 0x00 Initialization OSC2 Inactive Low Byte (125 µs/LSB)
#define	INIT_DR43	0x00	//	43 0x2B 0x00 Initialization OSC2 Inactive High Byte (125 µs/LSB)
#define	INIT_DR44	0x00	//	44 0x2C 0x00 Initialization Pulse Metering Active Low Byte (125 µs/LSB)
#define	INIT_DR45	0x00	//	45 0x2D 0x00 Initialization Pulse Metering Active High Byte (125 µs/LSB)
#define	INIT_DR46	0x00	//	46 0x2E 0x00 Initialization Pulse Metering Inactive Low Byte (125 µs/LSB)
#define	INIT_DR47	0x00	//	47 0x2F 0x00 Initialization Pulse Metering Inactive High Byte (125 µs/LSB)
#define	INIT_DR48	0X80	//	48 0x30 0x00 0x80 Initialization Ringing Osc. Active Timer Low Byte (2 s,125 µs/LSB)
#define	INIT_DR49	0X3E	//	49 0x31 0x00 0x3E Initialization Ringing Osc. Active Timer High Byte (2 s,125 µs/LSB)
#define	INIT_DR50	0X00	//	50 0x32 0x00 0x00 Initialization Ringing Osc. Inactive Timer Low Byte (4 s, 125 µs/LSB)
#define	INIT_DR51	0X7D	//	51 0x33 0x00 0x7D Initialization Ringing Osc. Inactive Timer High Byte (4 s, 125 µs/LSB)
#define	INIT_DR52	0X00	//	52 0x34 0x00 Normal Oper. FSK Data Bit
#define	INIT_DR63	0X54	//	63 0x3F 0x54 Initialization Ringing Mode Loop Closure Debounce Interval
#define	INIT_DR64	0x00	//	64 0x40 0x00 Normal Oper. Mode Byte—primary control
#define	INIT_DR65	0X61	//	65 0x41 0x61 Initialization External Bipolar Transistor Settings
#define	INIT_DR66	0X03	//	66 0x42 0x03 Initialization Battery Control
#define	INIT_DR67	0X1F	//	67 0x43 0x1F Initialization Automatic/Manual Control
#define	INIT_DR69	0X0C	//	69 0x45 0x0A 0x0C Initialization Loop Closure Debounce Interval (1.25 ms/LSB)
#define	INIT_DR70	0X0A	//	70 0x46 0x0A Initialization Ring Trip Debounce Interval (1.25 ms/LSB)
#define	INIT_DR71	0X01	//	71 0x47 0x00 0x01 Initialization Off-Hook Loop Current Limit (20 mA + 3 mA/LSB)
#define	INIT_DR72	0X20	//	72 0x48 0x20 Initialization On-Hook Voltage (open circuit voltage) = 48 V(1.5 V/LSB)
#define	INIT_DR73	0X02	//	73 0x49 0x02 Initialization Common Mode Voltage—VCM = –3 V(–1.5 V/LSB)
#define	INIT_DR74	0X32	//	74 0x4A 0x32 Initialization VBATH (ringing) = –75 V (–1.5 V/LSB)
#define	INIT_DR75	0X10	//	75 0x4B 0x10 Initialization VBATL (off-hook) = –24 V (TRACK = 0)(–1.5 V/LSB)
#define	INIT_DR92	0x7f	//	92 0x5C  7F Initialization DC–DC Converter PWM Period (61.035 ns/LSB)
#define	INIT_DR93	0x14	//	93 0x5D 0x14 0x19 Initialization DC–DC Converter Min. Off Time (61.035 ns/LSB)
#define	INIT_DR96	0x00	//	96 0x60 0x1F Initialization Calibration Control Register 1(written second and starts calibration)
#define	INIT_DR97	0X1F	//	97 0x61 0x1F Initialization Calibration Control Register 2(written before Register 96)
#define	INIT_DR98	0X10	//	98 0x62 0x10 Informative Calibration result (see data sheet)
#define	INIT_DR99	0X10	//	99 0x63 0x10 Informative Calibration result (see data sheet)
#define	INIT_DR100	0X11	//	100 0x64 0x11 Informative Calibration result (see data sheet)
#define	INIT_DR101	0X11	//	101 0x65 0x11 Informative Calibration result (see data sheet)
#define	INIT_DR102	0x08	//	102 0x66 0x08 Informative Calibration result (see data sheet)
#define	INIT_DR103	0x88	//	103 0x67 0x88 Informative Calibration result (see data sheet)
#define	INIT_DR104	0x00	//	104 0x68 0x00 Informative Calibration result (see data sheet)
#define	INIT_DR105	0x00	//	105 0x69 0x00 Informative Calibration result (see data sheet)
#define	INIT_DR106	0x20	//	106 0x6A 0x20 Informative Calibration result (see data sheet)
#define	INIT_DR107	0x08	//	107 0x6B 0x08 Informative Calibration result (see data sheet)
#define	INIT_DR108	0xEB	//	108 0x63 0x00 0xEB Initialization Feature enhancement register
#define INIT_SI3210M_DR92 0x60  //  92 0x60 Initialization DC–DC Converter PWM Period (61.035 ns/LSB)
#define INIT_SI3210M_DR93 0x38  //  92 0x60 Initialization DC–DC Converter PWM Period (61.035 ns/LSB)

 

typedef struct {
	//unsigned char chip_number;
	enum{ MAKEbUSY, STATEcHANGE,DIALtONE,INITIALIZING,POWERuP,CALIBRATE,PROGRAMMEDrING,
	POWERdOWN,POWERlEAKtEST, MAKErINGbACKjAPAN, MAKEbUSYjAPAN, RINGbACKjAPAN, 
	MAKErINGbACK,RINGbACK,ONlINE,MAKErEORDER,REORDER,MAKEcONGESTION,CONGESTION,PRENEON,
	NEON, CALLBACKpROGRAMMED, BUSY, CALLBACK, CALLING, MAKEoFFHOOK,ONHOOK, OFFHOOK, 
	DIGITDECODING, LOOPtRANSITION, FIRSTrING, DEFEREDcALLBACKpROGRAMMED,CALLERiD,
	RINGING,DTMFtRANISTION,CONVERSATION} state,newState,previousState;
	int digit_count;     //This is the number of digits collected.
	char DTMF_digits[20];  //This is the number of digits collected.
	unsigned long interrupt;  //This is a collection of the bits in the ProSLIC interrupt register.
	unsigned char eventEnable; //This is a flag to allow event processing to occur.
	unsigned char hook_status; //This is a flag for the current state of the loop. It is updated when the loop state transitions.
	unsigned long On_Hook_time; //This is a record of the time the telephone loop goes open circuit.
	unsigned long Off_Hook_time; //This is a record of the time the telephone loop goes closed circuit.
	char	version;
	char    type; //revision & type of the chip.
	int	dtmf_wait, ring_type; //dtmf wait time 10sec
	int	int_init;
	int exce_occ;
	int inrd, inwt, in_release;
	unsigned char osc1_event; //This is a flag to allow event osc1 active timer to occur.
	//This is the link to the next cadences entry in this linked
	//list implemented in an array fro easy programmability.
	struct{ enum { TYPE1, TYPE2, TYPE3 } ringType;
			int nextCadenceEntryIndex;
		}  ringCadenceCordinates;
	unsigned char ringCount;  //This is the counter of the ringing.
	int qLog[6];  //power alarm count.
	unsigned long eventNumber;
	char * phoneNumber ;
} chipStruct;




char SSPID2[] =
 "\x80\x27\x01\x08" "01010101"  "\x02\x0A"  "0123456789"  "\x07\x0f"
 "SSPSLIC" "\x20" "CALLING" ;//"\x2F" ;

struct CID
{
	unsigned char field1[4], field2[8],field3[2],field4[10],field5[2];
	char * field6;
}  example =

{ {0x80,0x27,0x01,0x08}, {'0','1','0','1','0','1','0','1'}, {0x02,0x0A}, 
 {'0','1','2','3','4','5','6','7','8','9'},{0x07,0x0f}, 
"SSPSLIC" "\x20" "CALLING" ,
};

char * exceptionStrings[] = 
{ " ProSLIC not communicating", "Time out durring Power Up", "Time out durring Power Down","Power is Leaking; might be a short",

" Tip or Ring Ground Short",

"Too Many Q1 Power Alarms" ,"Too Many Q2 Power Alarms" ,"Too Many Q3 Power Alarms" 

"Too Many Q4 Power Alarms" ,"Too Many Q5 Power Alarms" ,"Too Many Q6 Power Alarms" };

char *stt[] = {"MAKEbUSY", 
"STATEcHANGE",
"DIALtONE",
"INITIALIZING",
"POWERuP",
"CALIBRATE",
"PROGRAMMEDrING",
"POWERdOWN",
"POWERlEAKtEST",
"MAKErINGbACKjAPAN", 
"MAKEbUSYjAPAN", 
"RINGbACKjAPAN", 
"MAKErINGbACK",
"RINGbACK",
"MAKErEORDER",
"REORDER",
"MAKEcONGESTION",
"CONGESTION",
"PRENEON",
"NEON",
"CALLBACKpROGRAMMED", 
"BUSY", 
"CALLBACK", 
"CALLING", 
"MAKEoFFHOOK",
"ONHOOK", 
"OFFHOOK", 
"DIGITDECODING",
"LOOPtRANSITION", 
"FIRSTrING", 
"DEFEREDcALLBACKpROGRAMMED",
"CALLERiD",
"RINGING",
"DTMFtRANISTION",
"CONVERSATION"
	};

static __u16 SLIC_ind_reg_def[] = {
	0,   0x55C2,  /* Row 0 (1,2,3,A) dtmf detection */ 
	1,   0x51E6,  /* Row 1 (4,5,6,B) dtmf detection */ 
	2,   0x4B85,  /* Row 2 (7.8.9,C) dtmf detection */ 
	3,   0x4937,  /* Row 3 (*,0.#,D) dtmf detection */ 
	4,   0x3333,  /* column peak magnitude threshold */
	5,   0x0202,
	6,   0x0202,
	7,   0x0198,
	8,   0x0198,
	9,   0x0611,
	10,  0x0202,
	11,  0x00E5,  /* dtmf power minimum threshold */
	12,  0x0A1C,  /* Two step AGC, which is in the DTMF path*/
	13,  0x7B30,
	14,  0x0063,
	15,  0x0000,
	16,  0x7870,
	17,  0x007D,
	18,  0x0000,
	19,  0x0000,
	20,  0x7EF0, //7ef0
	/*21, 0x0177, (70V) */
	21,  0x0160,  //0x01C8, /* 85V */ //
	22,  0x0000,
	23,  0x2000,
	24,  0x2000,
	25,  0x0000,
	26,  0x4000,
	27,  0x4000,
	28,  0x1000,
	29,  0x3600,
	30,  0x1000,
	31,  0x0200, //x0080
	32,  0x07C0,
	33,  0x376f, //0x2600
	34,  0x1B80,
	35,  0x8000,
	36,  0x0320,
	37,  0x008C,
	38,  0x0100, //ox8c
	39,  0x0010,
	40,  0x0C00, //0x200
	41,  0x0C00,
	43,  0x00DA,
	99,  0x00DA,
	100, 0x6B60,
	101, 0x0074,
	102, 0x79C0,
	103, 0x1120,
	104, 0x3BE0,
	97,  0x0000,
	0, 0
};
/*
static __u8 SLIC_reg_def[] = {
	0	,0x00,	//	Serial Interface
	//0	,0x05,	//	Serial Interface
	1	,0x28,	//	PCM Mode
	2	,0x00,	//	PCM TX Clock Slot Low Byte (1 PCLK cycle/LSB)
	3	,0x00,	//	PCM TX Clock Slot High Byte
	4	,0x00,	//	PCM RX Clock Slot Low Byte (1 PCLK cycle/LSB)
	5	,0x00,	//	PCM RX Clock Slot High Byte
	6	,0x00,	//	DIO Control (external battery operation, Si3211/12)
	8	,0x00,	//	Loopbacks (digital loopback default)
	9	,0x00,	//	Transmit and receive path gain and control
	10	,0x28,	//	Initialization Two-wire impedance (600  and enabled)
	11	,0x33,	//	Transhybrid Balance/Four-wire Return Loss
	14	,0x10,	//	Powerdown Control 1
	15	,0x00,	//	Initialization Powerdown Control 2
	18	,0xff,	//	Normal Oper. Interrupt Register 1 (clear with 0xFF)
	19	,0xff,	//	Normal Oper. Interrupt Register 2 (clear with 0xFF)
	20	,0xff,	//	Normal Oper. Interrupt Register 3 (clear with 0xFF)
	21	,0xff,	//	Interrupt Mask 1
	22	,0xff,	//	Initialization Interrupt Mask 2
	23	,0xff,	//	 Initialization Interrupt Mask 3
	32	,0x00,	//	Oper. Oscillator 1 Control—tone generation
	33	,0x00,	//	Oper. Oscillator 2 Control—tone generation
	34	,0x18,	//	34 0x22 0x00 Initialization Ringing Oscillator Control
	35	,0x00,	//	Oper. Pulse Metering Oscillator Control
	36	,0x00,	//	36 0x24 0x00 Initialization OSC1 Active Low Byte (125 µs/LSB)
	37	,0x00,	//	37 0x25 0x00 Initialization OSC1 Active High Byte (125 µs/LSB)
	38	,0x00,	//	38 0x26 0x00 Initialization OSC1 Inactive Low Byte (125 µs/LSB)
	39	,0x00,	//	39 0x27 0x00 Initialization OSC1 Inactive High Byte (125 µs/LSB)
	40	,0x00,	//	40 0x28 0x00 Initialization OSC2 Active Low Byte (125 µs/LSB)
	41	,0x00,	//	41 0x29 0x00 Initialization OSC2 Active High Byte (125 µs/LSB)
	42	,0x00,	//	42 0x2A 0x00 Initialization OSC2 Inactive Low Byte (125 µs/LSB)
	43	,0x00,	//	43 0x2B 0x00 Initialization OSC2 Inactive High Byte (125 µs/LSB)
	44	,0x00,	//	44 0x2C 0x00 Initialization Pulse Metering Active Low Byte (125 µs/LSB)
	45	,0x00,	//	45 0x2D 0x00 Initialization Pulse Metering Active High Byte (125 µs/LSB)
	46	,0x00,	//	46 0x2E 0x00 Initialization Pulse Metering Inactive Low Byte (125 µs/LSB)
	47	,0x00,	//	47 0x2F 0x00 Initialization Pulse Metering Inactive High Byte (125 µs/LSB)
	48	,0x80,	//	48 0x30 0x00 0x80 Initialization Ringing Osc. Active Timer Low Byte (2 s,125 µs/LSB)
	49	,0x3E,	//	49 0x31 0x00 0x3E Initialization Ringing Osc. Active Timer High Byte (2 s,125 µs/LSB)
	50	,0x00,	//	50 0x32 0x00 0x00 Initialization Ringing Osc. Inactive Timer Low Byte (4 s, 125 µs/LSB)
	51	,0x7D,	//	51 0x33 0x00 0x7D Initialization Ringing Osc. Inactive Timer High Byte (4 s, 125 µs/LSB)
	52	,0x00,	//	52 0x34 0x00 Normal Oper. FSK Data Bit
	63	,0x54,	//	63 0x3F 0x54 Initialization Ringing Mode Loop Closure Debounce Interval
	64	,0x00,	//	64 0x40 0x00 Normal Oper. Mode Byte—primary control
	65	,0x61,	//	65 0x41 0x61 Initialization External Bipolar Transistor Settings
	66	,0x03,	//	66 0x42 0x03 Initialization Battery Control
	67	,0x1F,	//	67 0x43 0x1F Initialization Automatic/Manual Control
	69	,0x0C,	//	69 0x45 0x0A 0x0C Initialization Loop Closure Debounce Interval (1.25 ms/LSB)
	70	,0x0A,	//	70 0x46 0x0A Initialization Ring Trip Debounce Interval (1.25 ms/LSB)
	71	,0x01,	//	71 0x47 0x00 0x01 Initialization Off-Hook Loop Current Limit (20 mA + 3 mA/LSB)
	72	,0x20,	//	72 0x48 0x20 Initialization On-Hook Voltage (open circuit voltage) = 48 V(1.5 V/LSB)
	73	,0x02,	//	73 0x49 0x02 Initialization Common Mode Voltage—VCM = –3 V(–1.5 V/LSB)
	74	,0x32,	//	74 0x4A 0x32 Initialization VBATH (ringing) = –75 V (–1.5 V/LSB)
	75	,0x10,	//	75 0x4B 0x10 Initialization VBATL (off-hook) = –24 V (TRACK = 0)(–1.5 V/LSB)
	92	,0x7f,	//	92 0x5C  7F Initialization DC–DC Converter PWM Period (61.035 ns/LSB)
	93	,0x14,	//	93 0x5D 0x14 0x19 Initialization DC–DC Converter Min. Off Time (61.035 ns/LSB)
	96	,0x00,	//	96 0x60 0x1F Initialization Calibration Control Register 1(written second and starts calibration)
	97	,0x1F,	//	97 0x61 0x1F Initialization Calibration Control Register 2(written before Register 96)
	98	,0x10,	//	98 0x62 0x10 Informative Calibration result (see data sheet)
	99	,0x10,	//	99 0x63 0x10 Informative Calibration result (see data sheet)
	100	,0x11,	//	100 0x64 0x11 Informative Calibration result (see data sheet)
	101	,0x11,	//	101 0x65 0x11 Informative Calibration result (see data sheet)
	102	,0x08,	//	102 0x66 0x08 Informative Calibration result (see data sheet)
	103	,0x88,	//	103 0x67 0x88 Informative Calibration result (see data sheet)
	104	,0x00,	//	104 0x68 0x00 Informative Calibration result (see data sheet)
	105	,0x00,	//	105 0x69 0x00 Informative Calibration result (see data sheet)
	106	,0x20,	//	106 0x6A 0x20 Informative Calibration result (see data sheet)
	107	,0x08,	//	107 0x6B 0x08 Informative Calibration result (see data sheet)
	108	,0xEB,	//	108 0x63 0x00 0xEB Initialization Feature enhancement register
    0, 0
};
*/



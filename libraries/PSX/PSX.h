// PSX.h
// Header of PSX lib
// (c) 2017 Al'Khana

#ifndef _PSX_h
#define _PSX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define PSX_DELAY		10

// Button Hex Representations:
#define PSB_L2          0x0001
#define PSB_R2          0x0002
#define PSB_L1          0x0004
#define PSB_R1          0x0008
#define PSB_GREEN       0x0010
#define PSB_RED         0x0020
#define PSB_BLUE        0x0040
#define PSB_PINK        0x0080
#define PSB_TRIANGLE    0x0010
#define PSB_CIRCLE      0x0020
#define PSB_CROSS       0x0040
#define PSB_SQUARE      0x0080
#define PSB_SELECT      0x0100
#define PSB_L3          0x0200
#define PSB_R3          0x0400
#define PSB_START       0x0800
#define PSB_UP			    0x1000
#define PSB_RIGHT		    0x2000
#define PSB_DOWN		    0x4000
#define PSB_LEFT		    0x8000

#define PSA_RX			  0
#define PSA_RY			  1
#define PSA_LX			  2
#define PSA_LY			  3
#define PSA_RIGHT		  4
#define PSA_LEFT		  5
#define PSA_UP			  6
#define PSA_DOWN		  7
#define PSA_GREEN		  8
#define PSA_RED			  9
#define PSA_BLUE		  10
#define PSA_PINK		  11
#define PSA_TRIANGLE	  8
#define PSA_CIRCLE		  9
#define PSA_CROSS		  10
#define PSA_SQUARE		  11
#define PSA_L1			  12
#define PSA_R1			  13
#define PSA_L2			  14
#define PSA_R2			  15

class PSXClass
{
 protected:
	byte dataPin;
	byte commandPin;
	byte attPin;
	byte clockPin;
 public:
	byte mode;
	unsigned int buttons;
	byte pressed[16];

	PSXClass(uint8_t data, uint8_t command, uint8_t att, uint8_t clock);
	void begin();
 protected:
	uint8_t write(uint8_t cmd);
	uint16_t read();
};

#endif


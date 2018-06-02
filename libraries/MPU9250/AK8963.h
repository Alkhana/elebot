// AK8963.h
// Header of AK8963 lib
// (c) 2018 Al'Khana

#ifndef _AK8963_h
#define _AK8963_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Wire.h>

#define AK8963_ADDRESS   0x0C

class AK8963Class
{
 protected:
	uint8_t i2c_addr;

	void write(uint8_t addr, uint8_t data);
	void read(uint8_t addr, uint8_t* data, uint8_t size);

public:
	int16_t mx;
	int16_t my;
	int16_t mz;

 public:
	 AK8963Class(uint8_t addr);
	 void begin();
	 void read();
};

extern AK8963Class AK8963;

#endif


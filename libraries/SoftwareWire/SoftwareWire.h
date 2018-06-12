// SoftwareWire.h
// Header of SoftwareWire lib
// (c) 2018 Al'Khana

#ifndef _SoftwareWire_h
#define _SoftwareWire_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Wire.h>

class SoftwareWire
{
public:
	uint8_t i2c_addr;

	void write(uint8_t addr, uint8_t data);
	void read(uint8_t addr, uint8_t* data, uint8_t size);
public:
	SoftwareWire(uint8_t addr);
	void begin();
};

#endif


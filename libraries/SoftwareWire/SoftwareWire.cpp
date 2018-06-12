// SoftwareWire.h
// Code of SoftwareWire lib
// (c) 2018 Al'Khana

#include "SoftwareWire.h"

SoftwareWire::SoftwareWire(uint8_t addr)
{
	i2c_addr = addr;
}

void SoftwareWire::write(uint8_t addr, uint8_t data)
{
	Wire.beginTransmission(i2c_addr);
	Wire.write(addr);
	Wire.write(data);
	Wire.endTransmission();
}

void SoftwareWire::read(uint8_t addr, uint8_t* data, uint8_t size)
{
	int i = 0;
	Wire.beginTransmission(i2c_addr);
	Wire.write(addr);
	Wire.endTransmission();
	Wire.requestFrom(i2c_addr, size);
	while (Wire.available())
	{
		data[i] = Wire.read();
		i++;
	}
}

void SoftwareWire::begin()
{
	Wire.begin();
}


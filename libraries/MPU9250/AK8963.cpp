// AK8963.h
// code of AK8963 lib
// (c) 2018 Al'Khana

#include "AK8963.h"

void AK8963Class::write(uint8_t addr, uint8_t data)
{
	Wire.beginTransmission(i2c_addr);
	Wire.write(addr);
	Wire.write(data);
	Wire.endTransmission();
}

void AK8963Class::read(uint8_t addr, uint8_t* data, uint8_t size)
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

AK8963Class::AK8963Class(uint8_t addr = AK8963_ADDRESS)
{
	i2c_addr = addr;
}

void AK8963Class::begin()
{
	Wire.begin();
	write(0x0A, 0x16);
}

void AK8963Class::read()
{
  uint8_t st;
  read(0x02, &st, 1);
  if(!(st & 0x01))
    return;

  // Read magnetometer data
  uint8_t data[7];
  read(0x03, data, 7);
  if(data[6] & 0x08) // Check if magnetic sensor overflow set, if not then report data
    return;
 
  // Create 16 bits values from 8 bits data
  mx=-(data[3]<<8 | data[2]);
  my=-(data[1]<<8 | data[0]);
  mz=-(data[5]<<8 | data[4]);
}

AK8963Class AK8963;


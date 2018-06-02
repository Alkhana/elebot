// MPU9250.cpp
// Code of BME280 lib
// (c) 2017 Al'Khana

#include "MPU9250.h"

void MPU9250Class::write(uint8_t addr, uint8_t data)
{
	Wire.beginTransmission(i2c_addr);
	Wire.write(addr);
	Wire.write(data);
	Wire.endTransmission();
}

void MPU9250Class::read(uint8_t addr, uint8_t* data, uint8_t size)
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

MPU9250Class::MPU9250Class(uint8_t addr = MPU9250_ADDRESS)
{
	i2c_addr = addr;
}

void MPU9250Class::begin()
{
	Wire.begin();

	// Set accelerometers low pass filter at 5Hz
	write(ACCEL_CONFIG2, 0x06);
	// Set gyroscope low pass filter at 5Hz
	write(CONFIG, 0x06);
	// Configure gyroscope range
	write(GYRO_CONFIG, 0x10);
	// Configure accelerometers range
	write(ACCEL_CONFIG, 0x08);
	// Set pin 2 as int
	write(0x37, 0x02);
}

void MPU9250Class::read()
{
	// Read accelerometer and gyroscope
	uint8_t data[14];
	read(ACCEL_XOUT_H, data, 14);

	// Accelerometer
	ax = -(data[0] << 8 | data[1]);
	ay = -(data[2] << 8 | data[3]);
	az = data[4] << 8 | data[5];

	// Gyroscope
	gx = -(data[8] << 8 | data[9]);
	gy = -(data[10] << 8 | data[11]);
	gz = data[12] << 8 | data[13];
}

MPU9250Class MPU9250;


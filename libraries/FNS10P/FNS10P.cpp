// FNS10P.cpp
// Code of FN_S10P lib
// (c) 2017 Al'Khana

#include "FNS10P.h"

FNS10PClass::FNS10PClass(uint8_t receive, uint8_t transmit, uint8_t busy) :
	SoftwareSerial(receive, transmit)
{
	busyPin = busy;
	pinMode(busyPin, INPUT);
}

void FNS10PClass::begin()
{
	SoftwareSerial::begin(9600);
}

void FNS10PClass::command(uint8_t cmd, uint16_t val)
{
	uint8_t buffer[8];

	buffer[0] = 0X7e;
	buffer[1] = 0xff;
	buffer[2] = 0x06;
	buffer[3] = cmd; // command
	buffer[4] = 0X00; // nofeedback
	buffer[5] = (val >> 8);
	buffer[6] = (val & 0xff);
	buffer[7] = 0xef;

	for (int i = 0; i < 8; i++)
	{
		SoftwareSerial::write(buffer[i]);
	}
}

void FNS10PClass::playtrack(uint16_t track)
{
	command(FNS10P_PLAYTRACK, track);
	//while (digitalRead(busyPin) == LOW);
	delay(1000);
}

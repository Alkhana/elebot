// PSX.cpp
// Code of PSX lib
// (c) 2017 Al'Khana

#include "PSX.h"

uint8_t PSXClass::write(uint8_t cmd)
{
  uint8_t ret = 0;

  for(uint8_t i = 0; i < 8; i++)
  {
    // Writes out the _dataOut bits
    digitalWrite(commandPin, (cmd & (1 << i)) ? HIGH : LOW);

    digitalWrite(clockPin, LOW);
    
    delayMicroseconds(PSX_DELAY);

    if(digitalRead(dataPin))
    {
      ret |= (1 << i);
    }

    digitalWrite(clockPin, HIGH);
    delayMicroseconds(PSX_DELAY);
  }
  return ret;
}

uint16_t PSXClass::read()
{
  //byte cmd[] = { 0x01, 0x42, 0x00, 0x00, 0x00 };
  //byte dat[] = { 0x00, 0x00, 0x00, 0x00, 0x00 };

  digitalWrite(attPin, LOW);

  write(0x01);
  uint8_t mb = write(0x42);
  mode = mb >> 4;
  uint8_t lenth = mb & 0x0F;
  write(0x00);
  uint8_t hb = write(0x00);
  uint8_t lb = write(0x00);

  buttons = ~((hb << 8) | lb);

  if(mode == 0x07)
  for (uint8_t i = 0; i < 16; i++)
    pressed[i] = write(0x00);

  digitalWrite(attPin, HIGH);

  return buttons;
}

PSXClass::PSXClass(uint8_t data, uint8_t command, uint8_t att, uint8_t clock)
{
  dataPin = data;
  commandPin = command;
  attPin = att;
  clockPin = clock;
}

void PSXClass::begin()
{
  pinMode(dataPin, INPUT);
  digitalWrite(dataPin, HIGH); // Turn on internal pull-up

  pinMode(commandPin, OUTPUT);

  pinMode(attPin, OUTPUT);
  digitalWrite(attPin, HIGH);

  pinMode(clockPin, OUTPUT);
  digitalWrite(clockPin, HIGH);
  
  //delay = PSX_DELAY;

  buttons = 0x0000;
  for (uint8_t i = 0; i < 16; i++)
    pressed[i] = 0x00;
}


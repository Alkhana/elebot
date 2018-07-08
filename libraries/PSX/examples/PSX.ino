// PSX.ino
// Sample for PSX lib
// (c) 2017 Al'Khana

#include "PSX.h"

//#define LEDPin 13

PSXClass PSX(8, 9, 11, 10);

uint8_t data = 0;

void setup()
{
  psx.begin();
  //pinMode(LEDPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  uint8_t cdat = PSX.read();
  if(cdat != data)
  {
    data = cdat;
    Serial.print(psx.mode);
    Serial.print(": ");
    Serial.println(PSX.buttons);
    Serial.print("PSA_LY :");
    Serial.println(PSX.pressed[PSA_LY]);
  }
  delay(20);
}

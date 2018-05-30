// BME280.ino
// Sample for BME280 lib
// (c) 2017 Al'Khana
// SCL - A5
// SDA - A4

#include "BME280.h"

// the setup function runs once when you press reset or power the board
void setup() 
{
	Serial.begin(9600);
	BME280.begin();
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	BME280.read();

	Serial.print("TEMP : ");
	Serial.print(BME280.temp_act);
	Serial.print(" DegC PRESS : ");
	Serial.print(BME280.press_act);
	Serial.print(" hPa HUM : ");
	Serial.print(BME280.hum_act);
	Serial.println(" %");

	delay(1000);  
}


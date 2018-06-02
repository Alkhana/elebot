// MPU9250.ino
// Sample for MPU9250 lib
// (c) 2017 Al'Khana

#include "AK8963.h"
#include "MPU9250.h"

// the setup function runs once when you press reset or power the board
void setup() 
{
  Serial.begin(9600);
	MPU9250.begin();
  AK8963.begin();
	delay(100);
}

// the loop function runs over and over again until power down or reset
void loop() 
{
  
	MPU9250.read();

	Serial.print("Accelerometer");
  Serial.print("\t");
	Serial.print(MPU9250.ax, DEC);
  Serial.print("\t");
	Serial.print(MPU9250.ay, DEC);
	Serial.print("\t");
	Serial.print(MPU9250.az, DEC);
	Serial.print("\t");

  Serial.print("Gyroscope");
  Serial.print("\t");
	Serial.print(MPU9250.gx, DEC);
	Serial.print("\t");
	Serial.print(MPU9250.gy, DEC);
	Serial.print("\t");
	Serial.print(MPU9250.gz, DEC);
	Serial.print("\t");

 AK8963.read();

  Serial.print("Magnetometer");
  Serial.print("\t");
  Serial.print(AK8963.mx, DEC);
  Serial.print("\t");
  Serial.print(AK8963.my, DEC);
  Serial.print("\t");
  Serial.print(AK8963.mz, DEC);

	Serial.println("");
 
	delay(200);
}

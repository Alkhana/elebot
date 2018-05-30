// BME280.ino
// Code of BME280 lib
// (c) 2017 Al'Khana

#include "BME280.h"

BME280Class::BME280Class(uint8_t addr = BME280_ADDRESS)
{
	i2c_addr = addr;
}

void BME280Class::write(uint8_t addr, uint8_t data)
{
	Wire.beginTransmission(i2c_addr);
	Wire.write(addr);
	Wire.write(data);
	Wire.endTransmission();
}

void BME280Class::read(uint8_t addr, uint8_t* data, uint8_t size)
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

void BME280Class::begin(uint8_t osrs_t, uint8_t osrs_p, uint8_t osrs_h,
	uint8_t mode, uint8_t t_sb, uint8_t filter)
{
	Wire.begin();
 
	write(BME280_REG_CONTROLHUMID, osrs_h);
	write(BME280_REG_CONTROL, (osrs_t << 5) | (osrs_p << 2) | mode);
	write(BME280_REG_CONFIG, (t_sb << 5) | (filter << 2)/* | spi3w_en*/);

	uint8_t data[32];
 
	read(BME280_REG_DIG_T1, data, 24);
	read(BME280_REG_DIG_H1, data + 24, 1);
	read(BME280_REG_DIG_H2, data + 25, 7);

	dig_T1 = (data[1] << 8) | data[0];
	dig_T2 = (data[3] << 8) | data[2];
	dig_T3 = (data[5] << 8) | data[4];
	dig_P1 = (data[7] << 8) | data[6];
	dig_P2 = (data[9] << 8) | data[8];
	dig_P3 = (data[11] << 8) | data[10];
	dig_P4 = (data[13] << 8) | data[12];
	dig_P5 = (data[15] << 8) | data[14];
	dig_P6 = (data[17] << 8) | data[16];
	dig_P7 = (data[19] << 8) | data[18];
	dig_P8 = (data[21] << 8) | data[20];
	dig_P9 = (data[23] << 8) | data[22];
  
	dig_H1 = data[24];
  
	dig_H2 = (data[26] << 8) | data[25];
	dig_H3 = data[27];
	dig_H4 = (data[28] << 4) | (0x0F & data[29]);
	dig_H5 = (data[30] << 4) | ((data[29] >> 4) & 0x0F);
	dig_H6 = data[31];
}
/*
void BME280Class::read()
{
	uint8_t data[8];
	read(0xF7, data, 8);
  
	temp_act = calibration_T(((uint32_t)data[3] << 12) | ((uint32_t)data[4] << 4) | ((uint32_t)data[5] >> 4));
	press_act = calibration_P(((uint32_t)data[0] << 12) | ((uint32_t)data[1] << 4) | ((uint32_t)data[2] >> 4));
	hum_act = calibration_H(((uint32_t)data[6] << 8) | (uint32_t)data[7]);
}

double BME280Class::calibration_T(signed long int adc_T)
{
	signed long int var1 = ((((adc_T >> 3) - ((signed long int)dig_T1 << 1))) * ((signed long int)dig_T2)) >> 11;
	signed long int var2 = (((((adc_T >> 4) - ((signed long int)dig_T1)) * ((adc_T >> 4) - ((signed long int)dig_T1))) >> 12) * ((signed long int)dig_T3)) >> 14;
	return (double)(((var1 + var2) * 5 + 128) >> 8) / 100.0;
}

double BME280Class::calibration_P(signed long int adc_P)
{
	signed long int var1 = (((signed long int)t_fine) >> 1) - (signed long int)64000;
	signed long int var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * ((signed long int)dig_P6);
	var2 = var2 + ((var1*((signed long int)dig_P5)) << 1);
	var2 = (var2 >> 2) + (((signed long int)dig_P4) << 16);
	var1 = (((dig_P3 * (((var1 >> 2)*(var1 >> 2)) >> 13)) >> 3) + ((((signed long int)dig_P2) * var1) >> 1)) >> 18;
	var1 = ((((32768 + var1))*((signed long int)dig_P1)) >> 15);
	if (var1 == 0)
	{
		return 0;
	}
  unsigned long int P = (((unsigned long int)(((signed long int)1048576) - adc_P) - (var2 >> 12))) * 3125;
	if (P < 0x80000000)
	{
		P = (P << 1) / ((unsigned long int) var1);
	}
	else
	{
		P = (P / (unsigned long int)var1) * 2;
	}
	var1 = (((signed long int)dig_P9) * ((signed long int)(((P >> 3) * (P >> 3)) >> 13))) >> 12;
	var2 = (((signed long int)(P >> 2)) * ((signed long int)dig_P8)) >> 13;
	return (double)((signed long int)P + ((var1 + var2 + dig_P7) >> 4)) / 100.0;
}

double BME280Class::calibration_H(signed long int adc_H)
{
	signed long int var = (t_fine - ((signed long int)76800));
	var = (((((adc_H << 14) - (((signed long int)dig_H4) << 20) - (((signed long int)dig_H5) * var)) +
		((signed long int)16384)) >> 15) * (((((((var * ((signed long int)dig_H6)) >> 10) *
		(((var * ((signed long int)dig_H3)) >> 11) + ((signed long int) 32768))) >> 10) + ((signed long int)2097152)) *
		((signed long int) dig_H2) + 8192) >> 14));
	var = (var - (((((var >> 15) * (var >> 15)) >> 7) * ((signed long int)dig_H1)) >> 4));
	var = (var < 0 ? 0 : var);
	var = (var > 419430400 ? 419430400 : var);
	return (double)(var >> 12) / 1024.0;
}
*/

void BME280Class::read()
{
  uint8_t data[8];
  read(0xF7, data, 8);
  
  signed long int adc_T = ((uint32_t)data[3] << 12) | ((uint32_t)data[4] << 4) | ((uint32_t)data[5] >> 4);
  signed long int var1 = ((((adc_T >> 3) - ((signed long int)dig_T1 << 1))) * ((signed long int)dig_T2)) >> 11;
  signed long int var2 = (((((adc_T >> 4) - ((signed long int)dig_T1)) * ((adc_T >> 4) - ((signed long int)dig_T1))) >> 12) * ((signed long int)dig_T3)) >> 14;
  temp_act = (double)(((var1 + var2) * 5 + 128) >> 8) / 100.0;
  press_act = calibration_P(((uint32_t)data[0] << 12) | ((uint32_t)data[1] << 4) | ((uint32_t)data[2] >> 4));
  hum_act = calibration_H(((uint32_t)data[6] << 8) | (uint32_t)data[7]);
}

double BME280Class::calibration_P(signed long int adc_P)
{
  signed long int var1 = (((signed long int)t_fine) >> 1) - (signed long int)64000;
  signed long int var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * ((signed long int)dig_P6);
  var2 = var2 + ((var1*((signed long int)dig_P5)) << 1);
  var2 = (var2 >> 2) + (((signed long int)dig_P4) << 16);
  var1 = (((dig_P3 * (((var1 >> 2)*(var1 >> 2)) >> 13)) >> 3) + ((((signed long int)dig_P2) * var1) >> 1)) >> 18;
  var1 = ((((32768 + var1))*((signed long int)dig_P1)) >> 15);
  if (var1 == 0)
  {
    return 0;
  }
  unsigned long int P = (((unsigned long int)(((signed long int)1048576) - adc_P) - (var2 >> 12))) * 3125;
  if (P < 0x80000000)
  {
    P = (P << 1) / ((unsigned long int) var1);
  }
  else
  {
    P = (P / (unsigned long int)var1) * 2;
  }
  var1 = (((signed long int)dig_P9) * ((signed long int)(((P >> 3) * (P >> 3)) >> 13))) >> 12;
  var2 = (((signed long int)(P >> 2)) * ((signed long int)dig_P8)) >> 13;
  return (double)((signed long int)P + ((var1 + var2 + dig_P7) >> 4)) / 100.0;
}

double BME280Class::calibration_H(signed long int adc_H)
{
  signed long int var = (t_fine - ((signed long int)76800));
  var = (((((adc_H << 14) - (((signed long int)dig_H4) << 20) - (((signed long int)dig_H5) * var)) +
    ((signed long int)16384)) >> 15) * (((((((var * ((signed long int)dig_H6)) >> 10) *
    (((var * ((signed long int)dig_H3)) >> 11) + ((signed long int) 32768))) >> 10) + ((signed long int)2097152)) *
    ((signed long int) dig_H2) + 8192) >> 14));
  var = (var - (((((var >> 15) * (var >> 15)) >> 7) * ((signed long int)dig_H1)) >> 4));
  var = (var < 0 ? 0 : var);
  var = (var > 419430400 ? 419430400 : var);
  return (double)(var >> 12) / 1024.0;
}

BME280Class BME280;


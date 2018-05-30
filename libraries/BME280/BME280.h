// BME280.h
// Header of BME280 lib
// (c) 2017 Al'Khana

#ifndef _BME280_h
#define _BME280_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Wire.h>

#define BME280_ADDRESS 0x76

#define BME280_REG_DIG_T1    0x88
#define BME280_REG_DIG_T2    0x8A
#define BME280_REG_DIG_T3    0x8C

#define BME280_REG_DIG_P1    0x8E
#define BME280_REG_DIG_P2    0x90
#define BME280_REG_DIG_P3    0x92
#define BME280_REG_DIG_P4    0x94
#define BME280_REG_DIG_P5    0x96
#define BME280_REG_DIG_P6    0x98
#define BME280_REG_DIG_P7    0x9A
#define BME280_REG_DIG_P8    0x9C
#define BME280_REG_DIG_P9    0x9E

#define BME280_REG_DIG_H1    0xA1
#define BME280_REG_DIG_H2    0xE1
#define BME280_REG_DIG_H3    0xE3
#define BME280_REG_DIG_H4    0xE4
#define BME280_REG_DIG_H5    0xE5
#define BME280_REG_DIG_H6    0xE7

#define BME280_REG_CHIPID          0xD0
#define BME280_REG_VERSION         0xD1
#define BME280_REG_SOFTRESET       0xE0

#define BME280_REG_CAL26           0xE1

#define BME280_REG_CONTROLHUMID    0xF2
#define BME280_REG_CONTROL         0xF4
#define BME280_REG_CONFIG          0xF5
#define BME280_REG_PRESSUREDATA    0xF7
#define BME280_REG_TEMPDATA        0xFA
#define BME280_REG_HUMIDITYDATA    0xFD

class BME280Class
{
protected:
	uint8_t i2c_addr;
	signed long int t_fine;

    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;
    int8_t   dig_H1;
    int16_t  dig_H2;
    int8_t   dig_H3;
    int16_t  dig_H4;
    int16_t  dig_H5;
    int8_t   dig_H6;

	void write(uint8_t addr, uint8_t data);
	void read(uint8_t addr, uint8_t* data, uint8_t size);

	//double calibration_T(signed long int adc_T);
	double calibration_P(signed long int adc_P);
	double calibration_H(signed long int adc_H);
public:
    double temp_act;
    double press_act;
    double hum_act;

	BME280Class(uint8_t addr);
	void begin(uint8_t osrs_t = 1, uint8_t osrs_p = 1, uint8_t osrs_h = 1, 
	uint8_t mode = 3, uint8_t t_sb = 5, uint8_t filter = 0);
    void read();
};

extern BME280Class BME280;

#endif


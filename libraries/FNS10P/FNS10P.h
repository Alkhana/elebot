// FNS10P.h
// Header of FN_S10P lib
// (c) 2017 Al'Khana

#ifndef _FNS10P_h
#define _FNS10P_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <SoftwareSerial.h>

#define FNS10P_PLAYNEXT          0x01
#define FNS10P_PLAYPREV          0x02
#define FNS10P_PLAYTRACK         0x03
#define FNS10P_INCVOLUME         0x04
#define FNS10P_DECVOLUME         0x05
#define FNS10P_SETVOLUME         0x06
#define FNS10P_SETREPEATINFOLDER 0x08
#define FNS10P_SETSLEEP          0x0A
#define FNS10P_AWAKE             0x0B
#define FNS10P_RESET             0x0C
#define FNS10P_PLAY              0x0D
#define FNS10P_PAUSE             0x0E
#define FNS10P_SETPLAYINFOLDER   0x0F
#define FNS10P_INTERCUT          0x13
#define FNS10P_STOPINTERCUT      0x15
#define FNS10P_STOP              0x16
#define FNS10P_SETREPEATFOLDER   0x17
#define FNS10P_SETRANDOM         0x18
#define FNS10P_SETREPEATCURRENT  0x19
#define FNS10P_SETDAC            0x1A
#define FNS10P_SETPLAYGROUP      0x21
#define FNS10P_SETPLAYVOLUME     0x22
/*
#define FN_S10P_QUERYERRORDATA        0x40
#define FN_S10P_REPORTSFEEDBACK       0x41
#define FN_S10P_QUERYCURRENTSTATUS    0x42
#define FN_S10P_QUERYCURRENTVOLUME    0x43
#define FN_S10P_QUERYNUMBEROFTRACKS   0x44
#define FN_S10P_QUERYCURRENTTRACK     0x45
#define FN_S10P_QUERYNUMBEROFTARCKSIF 0x46
#define FN_S10P_QUERYNUMBEROFFOLDERS  0x47
*/
class FNS10PClass : private SoftwareSerial
{
protected:
	uint8_t busyPin;
	void command(uint8_t cmd, uint16_t val);
public:
	FNS10PClass(uint8_t receive, uint8_t transmit, uint8_t busy);
	void begin();
	void playtrack(uint16_t track);
};

//extern FNS10PClass FNS10P;

#endif

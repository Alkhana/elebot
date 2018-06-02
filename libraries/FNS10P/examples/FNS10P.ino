// FN_S10P.ino
// Sample for FN_S10P lib
// (c) 2017 Al'Khana

#include "FNS10P.h"

FNS10PClass Sound(7, 8, 9); // RX, TX, Busy

int su[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int sfd[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
int suf[] = { 38, 39 };
int sd[] = { 20, 21, 22, 23, 24, 25, 26, 27 };
int sh[] = { 28, 29, 30, 31, 32, 33, 34, 35, 36 };
int shw[] = { 41, 42, 43 };
int pmw[] = { 46, 47, 47 };
int sn = 37;
int sm = 40;

int sgc[] = { 49, 50, 51 };

void setup()
{
	Serial.begin(9600);
	Sound.begin();
	delay(1000);
	Serial.println("-----------");
	Sound.playtrack(48);
	int tt = saydigit(27.41, false);
	Sound.playtrack(sgc[tt]);
}

void loop()
{
}

int saydigit(double val, bool f)
{
	int ret = 2;

	if (val < 0)
	{
		Sound.playtrack(sm);
		val = -val;
	}
	Serial.print("val :");
	Serial.println(val);
	int ip = (int)val;
	Serial.print("int : ");
	Serial.println(ip);
	if (ip == 0)
	{
		Sound.playtrack(sn);
	}
	else
	{
		int it = ip / 1000;
		if (it > 0)
		{
			int tp = saydigit(it, true);
			Sound.playtrack(shw[tp]); // 1000
									  //      ret = 2;
		}
		ip = ip % 1000;
		int ih = ip / 100;
		if (ih > 0)
		{
			Sound.playtrack(sh[ih - 1]);
			Serial.println(ih * 100);
		}
		int id = ip % 100;
		if (id > 9 && id < 20)
		{
			Serial.print("Say 10-19:");
			Serial.println(id);
			Sound.playtrack(sfd[id - 10]); // play 10-19
		}
		else
		{
			int ic = id / 10;
			if (ic > 0)
			{
				Serial.print("Say decs:");
				Serial.println(ic * 10);
				Sound.playtrack(sd[ic - 2]);
			}
			int iu = id % 10;
			if (iu < 3 && f)
			{
				Serial.print("Say unit:");
				Serial.println(iu);
				Sound.playtrack(suf[iu - 1]); // for 1 & 2
			}
			else
			{
				Serial.print("Say unit:");
				Serial.println(iu);
				Sound.playtrack(su[iu - 1]);
			}
			if (iu < 5)
				ret = 1;
			if (iu == 1)
				ret = 0;
		}
	}
	Serial.print("val :");
	Serial.println(val);
	int im = (int)(val * 100);
	Serial.print("val: ");
	Serial.println(im);
	int ii = im % 100;
	Serial.print("Promilli: ");
	Serial.println(ii);
	if (ii > 0)
	{
		int tm = saydigit(ii, true);
		Sound.playtrack(pmw[tm]);
	}
	return ret;
}

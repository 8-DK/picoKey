#include "utils.h"

UtilsClass *UtilsClass::instance=nullptr;
UtilsClass Utils;

int UtilsClass::isOutOfrange(int inValue, int setPoint,int plusOrMinus)
{
	if(inValue < (setPoint-plusOrMinus))
	{
		return -((setPoint-plusOrMinus) - inValue);
	}
	else if(inValue > (setPoint+plusOrMinus))
	{
		return inValue-(setPoint+plusOrMinus);
	}

	return 0;
}

float UtilsClass::map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint8_t UtilsClass::mapU8(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int UtilsClass::mapInt(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (int)(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int UtilsClass::ascciToDecimal(char a)
{
	if (a >= '0' && a <= '9')
	{
	    int digit = a - '0';
	    return digit;
	}
	if( a >= 'A' && a <= 'F')
	{
		return a-55;
	}

	if( a >= 'a' && a <= 'f')
	{
		return a-87;
	}

	return 0;
}

void UtilsClass::getRandoms(uint8_t* arr,int lower, int upper,int count)
{
    for (int i = 0; i < count; i++) {
    	arr[i] = (uint8_t)((rand() % (upper - lower + 1)) + lower);
    }
}

uint32_t UtilsClass::millis() {
	return to_ms_since_boot(get_absolute_time());
}

uint32_t UtilsClass::micros() {
	return to_us_since_boot(get_absolute_time());
}
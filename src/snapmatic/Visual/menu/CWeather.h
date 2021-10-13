
#ifndef _CWEATHER_H_
#define _CWEAHER_H_


#include "CUIElement.h"


class CWeather : public CUIElement, public CSelectable
{
	CSelectBox weather;
	int *weatherID;
public:
	CWeather(const char*, const Weather[], int);
	bool render();
	int getValue();
};



































#endif

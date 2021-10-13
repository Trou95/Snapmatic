
#ifndef _CTIME_H_
#define _CTIME_H_


#include "CUIElement.h"


class CTime : public CUIElement, public CSelectable
{
	CSlider<int> slider;
public:
	CTime(const char*, int, int);
	bool render();
	int getValue();
};































#endif
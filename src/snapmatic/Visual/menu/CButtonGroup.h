
#ifndef _CBUTTONGROUP_H_
#define _CBUTTONGROUP_H_


#include "CUIElement.h"


class CButtonGroup : public CUIElement
{
	const char* button2;
	bool selectedButton;
public:
	CButtonGroup(const char*, const char*);
	bool render();
	bool getSelectedButtonID();
};
































#endif

#ifndef _CCHECKBOX_H_
#define _CCHECKBOX_H_


#include "CUIElement.h"



class CCheckbox : public CUIElement, public CSelectable
{
public:
	CCheckbox(const char*);
	bool render();
};































#endif

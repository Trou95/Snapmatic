
#include "CUIElement.h"


CSelectBox::CSelectBox(const char* name, const char** items, int size)
{
	this->name = name;
	this->items = items;
	this->itemSize = size;
	this->selectedItem = NULL;
}
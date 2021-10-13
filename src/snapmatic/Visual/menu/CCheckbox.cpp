
#include "CCheckbox.h"


CCheckbox::CCheckbox(const char* name)
{
	this->name = name;
}

bool CCheckbox::render()
{
	return ImGui::Checkbox(name, &bIsSelected);
}
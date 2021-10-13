
#include "CButton.h"


CButton::CButton(const char* name)
{
	this->name = name;
}

bool CButton::render()
{
	return ImGui::Button(name, ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT));
}

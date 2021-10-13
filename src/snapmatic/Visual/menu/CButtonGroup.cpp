
#include "CButtonGroup.h"



CButtonGroup::CButtonGroup(const char* name,const char* name2)
{
	this->name = name;
	button2 = name2;
	selectedButton = false;
}

bool CButtonGroup::render()
{
	bool bIsClick = false;
	ImGui::SetCursorPosX((WINDOW_WIDTH - (BUTTON_WIDTH * 2)) / 2);
	if (ImGui::Button(name, ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
	{
		selectedButton = false;
		bIsClick = true;
	}
	ImGui::SameLine();
	if (ImGui::Button(button2, ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
	{
		selectedButton = true;
		bIsClick = true;
	}
	return bIsClick;
}


bool CButtonGroup::getSelectedButtonID()
{
	return selectedButton;
}
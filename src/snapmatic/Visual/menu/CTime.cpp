

#include "CTime.h"



CTime::CTime(const char* name,int minvalue,int maxvalue)
{
	this->name = name; 
	slider = CSlider<int>(); 
	slider.minValue = minvalue; 
	slider.maxValue = maxvalue;
}


bool CTime::render()
{
	bool bIsClick = ImGui::Checkbox(name, &bIsSelected);
	ImGui::SameLine(0, 24);
	if (ImGui::SliderInt("", &slider.value, slider.minValue, slider.maxValue, "%.2d:00") && bIsSelected) bIsClick = true; // Send Click When Slider Update
	return bIsClick;
}

int CTime::getValue()
{
	return slider.getValue();
}




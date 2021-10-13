
#include "CWeather.h"


CWeather::CWeather(const char* name, const Weather weathers[], int size)
{
	this->name = name;
	const char** items = new const char* [size];
	weatherID = new int[size];
	for (int i = 0; i < size; i++)
	{
		items[i] = new char[strlen(weathers[i].name)];
		items[i] = weathers[i].name;
		weatherID[i] = weathers[i].id - 1;
	}
	char* _name = new char[strlen(name) + strlen("##_select") + 1];
	strcpy(_name, "##");
	strcat(_name, name);
	strcat(_name, "_select");
	weather = CSelectBox(_name, items, size);
}


bool CWeather::render()
{
	bool bIsClick = ImGui::Checkbox(name, &bIsSelected);
	ImGui::SameLine();
	if (ImGui::BeginCombo(weather.name, weather.selectedItem))
	{
		for (int n = 0; n < weather.itemSize; n++)
		{
			bool is_selected = (weather.selectedItem == weather.items[n]);
			if (ImGui::Selectable(weather.items[n], is_selected))
				weather.selectedItem = weather.items[n];
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
		if (bIsSelected) bIsClick = true;
	}
	return bIsClick;
}

int CWeather::getValue()
{
	for (int i = 0; i < weather.itemSize; i++)
		if (weather.selectedItem == weather.items[i])
			return weatherID[i];
	return 0;
}
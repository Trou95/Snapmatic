
#ifndef _CMENU_H_
#define _CMENU_H_




#include "CUIElement.h"
#include "CCheckbox.h"
#include "CButton.h"
#include "CButtonGroup.h"
#include "CTime.h"
#include "CWeather.h"



#include "../VMTHookManager.h"



#include <vector>
#include <memory>




class CMenu
{
	bool bInit;
	bool bIsVisible;

	void InitStyle();

	

public:

	bool bIsSettingsVisible;
	bool bSampTextDraw;
	bool bSampNameTag;
	bool bFreezeTime;
	int time;
	bool bFreezeWeather;
	byte weather;
	PDIRECT3DTEXTURE9 mIcon;

	CMenu();
	bool Init();
	bool IsVisible();
	bool IsSettingsVisible();
	void ShowMenu(bool state);

	int getItemSize();
	void addCheckBox(const char* name);
	void addButton(const char* name);
	void addButtonGroup(const char* name, const char* name2);
	void addTime(const char* name);
	void addWeather(const char* name,Weather weathers[]);

	std::vector<std::unique_ptr<CUIElement>> menuItems;

	void Render();
	void RenderSettings();

	void InitItems();


};











#endif

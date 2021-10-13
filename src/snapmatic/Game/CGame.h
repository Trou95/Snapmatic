
#ifndef _CGAME_H_
#define _CGAME_H_


#include <Windows.h>
#include "string"


struct Weather
{
	int id;
	const char* name;
};



class CGAME
{
	DWORD* ped = nullptr;
	DWORD* camera = nullptr;
	byte origHud = NULL;
	bool bShowHud;

public:
	CGAME();
	void getTime(int& hour, int& min);
	void setTime(int hour);
	byte getWeather();
	void setWeather(int id);
	const char* getWeather(byte id);
	bool IsInMenu();
	void ToggleHud(bool state);
	void HideHud();
	bool IsShowHud();
	DWORD* getPed();
	bool getPedPos(float(&pos)[3]);
	DWORD* getCam();
	DWORD* getActiveCam(byte id);
	float* getCameraPos();
	void setCameraPos(float pos[3]);
	void setCameraLookAt(float pos[3],bool mode = false);
	void getCameraFront(float& x, float& y,float distance);
	void cameraReset();
	void playSound(int id, const float pos[3] = NULL);
	void showText(const char* text, int time, int style);
};




















#endif

#include "CGame.h"


Weather weathers[] =
{
	8,"Blue sky",
	9,"Stormy",
	10,"Cloudy and foggy",
	11,"Clear blue sky",
	12,"Scorching hot (heat waves)",
	13,"Very dull, colorless, hazy",
	17,"Dull, cloudy, rainy",
	18,"Scorching hot",
	20,"Sandstorm",
	21,"Greenish fog",
	22,"Very dark, gradiented skyline, purple",
	23,"Very dark, gradiented skyline, green",
	24,"Variations of pale orange",
	27,"Variations of fresh blue",
	31,"Variations of dark, cloudy, teal",
	34,"Dark, cloudy, brown",
	36,"Blue, purple, regular",
	37,"Dull brown",
	41,"Extremely bright",
	44,"Blue, purple, cloudy",
	45,"Dark toxic clouds",
	46,"Black, white sky",
	47,"Black, purple sky"

};



CGAME::CGAME()
{
	camera = (DWORD*)0xB6F028;
	bShowHud = true;
}


void CGAME::getTime(int& hour, int& min)
{
    if(hour) hour = *(byte*)0xB70153;
	if(min) min = *(byte*)0xB70152;
}

void CGAME::setTime(int hour)
{
	*(byte*)0xB70153 = hour;
}

byte CGAME::getWeather()
{
	return *(byte*)0xC81318;
}

void CGAME::setWeather(int id)
{
	*(short*)0xC81320 = id;
}

const char* CGAME::getWeather(byte id)
{
	for (auto _w : weathers)
		if (id < _w.id)
			return _w.name;
	return weathers[0].name;
}


bool CGAME::IsInMenu()
{
	return *(byte*)(0xBA6748 + 0x5C);
}


void CGAME::ToggleHud(bool state)
{
	if (!state)
	{
		if (!origHud) origHud = *(byte*)(0x589270);
		*(byte*)(0x589270) = 0xC3;
		*(byte*)(0x5890A0) = 0xC3;
		*(byte*)(0x58D7D0) = 0xC3;
		*(byte*)(0x5893B0) = 0xC3;
		*(int*)0xBAA424 = 0;
		bShowHud = false;
	}
	else
	{
		if (origHud)
		{
			*(byte*)(0x589270) = origHud;
			*(byte*)(0x5890A0) = origHud;
			*(byte*)(0x58D7D0) = 0xA1;
			*(byte*)(0x5893B0) = 0x53;
			*(int*)0xBAA424 = 1;
			*(int*)0xBAA428 = 1000;
			origHud = 0;
		}
		bShowHud = true;
	}
}



void CGAME::HideHud()
{
	if (!origHud) ToggleHud(false);
	*(bool*)0xBAA3FB = 1;
	*(int*)0xBAA424 = 0;
	*(int*)0xBAA430 = *(DWORD*)(0xB7CD98 + 0xBC) - 1;
}

bool CGAME::IsShowHud()
{
	return bShowHud;
}



DWORD* CGAME::getPed()
{
	if (ped)
		return ped;
	ped = (DWORD*)0xB6F5F0;
	return ped ? ped : NULL;
}



bool CGAME::getPedPos(float (&pos)[3])
{
	if (!ped)
	{
		if (!getPed())
			return false;
	}
	memcpy(pos, (DWORD*)(*(DWORD*)(*(DWORD*)ped + 0x14) + 0x30), sizeof(float) * 3);
	return true;
}


DWORD* CGAME::getCam()
{
	return camera ? camera : NULL;
}

DWORD* CGAME::getActiveCam(byte id)
{
	//Active Camera Always 0 ?
	return (DWORD*)0xB6F19C;
}

float* CGAME::getCameraPos()
{
	DWORD* currentCam = getActiveCam(0);
	if (!currentCam)
		return NULL;
	if (*(short int*)((char*)currentCam + 0xC) != 15) // Check Camera Mode Is Fixed
		return NULL;
	float* pos = new float[3];
	memcpy(pos, (char*)currentCam + 0x160, sizeof(float) * 3);
	return pos;
}

void CGAME::setCameraPos(float pos[3])
{
	((void(__thiscall*) (DWORD*, float*, float*)) (0x50BEC0))(camera, &pos[0], new float[3]{ 0,0,0 });
}


void CGAME::setCameraLookAt(float pos[3],bool mode)
{
	((void(__thiscall*) (DWORD*,float*,short,int)) (0x50C8B0))(camera,&pos[0],mode ? 2 : 1,1);
}

void CGAME::getCameraFront(float& x, float& y,float distance)
{
	if (distance < 0) distance = 0;
	DWORD* ped = getPed();
	if (!ped)
		return;
	x = *(float*)(*(DWORD*)(*(DWORD*)ped + 0x14) + 16) * distance;
	y = *(float*)(*(DWORD*)(*(DWORD*)ped + 0x14) + 20) * distance;
}

void CGAME::cameraReset()
{
	if (!camera)
		return;
	((void(__thiscall*) (DWORD*)) (0x50BD40))(camera);
	((void(__thiscall*) (DWORD*)) (0x50BAB0))(camera);
}

void CGAME::playSound(int id, const float pos[3])
{
	((int(__thiscall*) (unsigned int* ptr, short _id, const float* _pos)) (0x507340)) ((unsigned int*)0xB6BC90, id, pos == NULL ? new float[3]{ 0,0,0 } : &pos[0]);
}


void CGAME::showText(const char* text, int time, int style)
{
	((void(__cdecl*) (unsigned int ptr)) (0x0069DCD0)) (0);
	((void(__cdecl*) (const char* text, int time, int style)) (0x0069F2B0)) (text, time, style);
}
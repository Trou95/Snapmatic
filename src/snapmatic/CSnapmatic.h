
#ifndef _CSNAPMATIC_H_
#define _CSNAPMATIC_H_


#include "Samp/CSamp.h"
#include "Visual/CVisual.h"
#include "Game/CGame.h"
#include "CKeys.h"
#include "CSettings.h"


#define VERSION "1.00"

#define FILE_PATH "snapmatic\\"


#define KEY_TIME 300
#define KEY_TIME_MOVE 50




class CSnapmatic
{
	bool bIsInit;
	bool bIsInitSamp;
	bool bIsBasicMode;
	bool bIsInitVisual;
	bool bIsCam;
	bool bIsCameraModeSmooth;
	bool bShowFilter;
	CSAMP* pSamp;
	CVisual* pVisual;
	CGAME* pGame;
	CKeys* pKeys;
	CSettings* pSettings;

public:
	bool bFreezeTime;
	bool bFreezeWeather;
	int time;
	int weather;
	float cameraSpeed;
	float filterColor[4];

	CSnapmatic();
	bool Init();
	bool IsInit();
	bool IsFreeCam();
	bool IsShowFilter();
	CSAMP *getSamp();
	CVisual *getVisual();
	CGAME *getGame();
	CKeys* getKeys();
	CSettings* getSettings();
	void ToggleCam(bool);
	void MoveCam(eMoveDirection);
	void ToggleCameraModeSmooth();
	void ToggleFilter(bool);
	void TakeScreenShot();
	void PlayGameSound(int);
	void ShowInfo(const char*);
	~CSnapmatic();
};












#endif
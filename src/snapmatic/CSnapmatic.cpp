
#include "CSnapmatic.h"

#include <future>




WNDPROC pWindowProc = NULL;
HWND gameWindow = NULL;



CSnapmatic::CSnapmatic()
{
	bIsInit =
	bIsInitSamp =
	bIsBasicMode = false;
	bIsInitVisual =
	bFreezeTime =
	bFreezeWeather =
	bShowFilter =
	bIsCam =
	bIsCameraModeSmooth = false;
	filterColor[0] =
	filterColor[1] =
	filterColor[2] = 0;
	filterColor[3] = 0.8;
	cameraSpeed = 1.0f;
	pSamp = new CSAMP();
	pVisual = new CVisual();
	pGame = new CGAME();
	pKeys = new CKeys();
	pSettings = new CSettings();
}


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void OnKeyDown(eKeys);

extern CSnapmatic* snapmatic;

LRESULT WINAPI WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;
	if (msg == WM_KEYDOWN)
	{
		if (!snapmatic->getSamp()->IsSampChatVisible())
		{
			for (int i = __KEY_SIZE__ - 2; i > -1; i--)
			{
				CKeys* keys = snapmatic->getKeys();
				if (!keys->IsKeyMode())
				{
					if (keys->getKey(i) == wParam)
					{
						eKeyGroup key = keys->getKeyGroup((eKeys)i);
						if (snapmatic->getKeys()->keyTick[key] < GetTickCount())
						{
							OnKeyDown((eKeys)i);
							keys->keyTick[key] = GetTickCount() + (key == eKeyGroup::KEY_GROUP_MOVE ? KEY_TIME_MOVE : KEY_TIME);
							break;
						}
					}
				}
				else
				{
					if (keys->IsValidKey(wParam))
					{
						keys->setKey((eKeys)keys->getKeyIndex(), wParam);
						keys->bIsSelect[keys->getKeyIndex()] = false;
						keys->setKeyIndex(-1);
					}
				}
			}
		}
	}


	return CallWindowProc(pWindowProc, hWnd, msg, wParam, lParam);
}


bool CSnapmatic::Init()
{
	if (bIsInit)
		return true;
	if (!gameWindow)
	{
		gameWindow = FindWindowA(NULL, "GTA:SA:MP");
		if (!gameWindow)
			return false;
	}
	if (!pWindowProc)
	{
		pWindowProc = (WNDPROC)SetWindowLongPtr(gameWindow, GWL_WNDPROC, (LONG)(LONG_PTR)WndProcHandler);
		if (!pWindowProc)
			return false;
	}
	if (bIsInitVisual == false)
	{
		if(*(DWORD*)0xC8D4C0 != 9)
		{
			Sleep(100);
			return false;
		}
		pVisual->init();
		bIsInitVisual = true;
	}
	if (bIsInitSamp == false)
	{
		if (!pSamp->init()) bIsBasicMode = true;
	}
	pSettings->LoadSettings();
	bIsInit = true;
	return true;
}

bool CSnapmatic::IsInit()
{
	return bIsInit;
}

bool CSnapmatic::IsFreeCam()
{
	return bIsCam;
}

bool CSnapmatic::IsShowFilter()
{
	return bShowFilter;
}

CSAMP* CSnapmatic::getSamp()
{
	return pSamp;
}

CVisual* CSnapmatic::getVisual()
{
	return pVisual;
}

CGAME* CSnapmatic::getGame()
{
	return pGame;
}

CKeys* CSnapmatic::getKeys()
{
	return pKeys;
}

CSettings* CSnapmatic::getSettings()
{
	return pSettings;
}

void CSnapmatic::ToggleCam(bool state)
{
	if (state)
	{
		float pos[3], fX, fY;
		pGame->getPedPos(pos);
		pGame->getCameraFront(fX, fY, 5);

		float cameraPos[3] = { pos[0] + fX,pos[1] + fY, pos[2] };

		pGame->setCameraLookAt(pos);
		pGame->setCameraPos(cameraPos);

		bIsCam = true;
    }
	else
	{
		pGame->cameraReset();
		
		bIsCam = false;

	}
}


void CSnapmatic::MoveCam(eMoveDirection movedirection)
{
	float* cameraPos = pGame->getCameraPos();
	if (!cameraPos)
		return;
	float pos[3];
	pGame->getPedPos(pos);
	float _cameraSpeed = bIsCameraModeSmooth ? 0.5f : this->cameraSpeed;
	if (movedirection == eMoveDirection::MOVE_FORWARD) cameraPos[0] += _cameraSpeed;
	else if (movedirection == eMoveDirection::MOVE_BACK) cameraPos[0] -= _cameraSpeed;
	else if (movedirection == eMoveDirection::MOVE_LEFT) cameraPos[1] += _cameraSpeed;
	else if (movedirection == eMoveDirection::MOVE_RIGHT) cameraPos[1] -= _cameraSpeed;
	else if (movedirection == eMoveDirection::MOVE_UP) cameraPos[2] += _cameraSpeed;
	else if (movedirection == eMoveDirection::MOVE_DOWN) cameraPos[2] -= _cameraSpeed;
	pGame->setCameraLookAt(pos,true);
	pGame->setCameraPos(cameraPos);
	delete[] cameraPos;
}

void CSnapmatic::ToggleCameraModeSmooth()
{
	bIsCameraModeSmooth = !bIsCameraModeSmooth;
}

void CSnapmatic::ToggleFilter(bool state)
{
	bShowFilter = state;
}

void CSnapmatic::TakeScreenShot()
{
	getVisual()->TakeScreenShot();
}

void CSnapmatic::PlayGameSound(int id)
{
	if (!pSettings->bPlaySounds)
		return;
	pGame->playSound(id);
}

void CSnapmatic::ShowInfo(const char* text)
{
	if (!pSettings->bShowNotifications)
		return;
	char* tmpText = new char;
	strcpy_s(tmpText, strlen(text) + 23, "~y~~h~Snapmatic~n~~w~");
	strcat(tmpText, text);
	pGame->showText(tmpText, 1000, 4);
}


CSnapmatic::~CSnapmatic() 
{
	delete pSamp;
	delete pVisual;
	delete pGame;
	delete pKeys;
	delete pSettings;
}


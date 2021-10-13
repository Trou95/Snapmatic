

#include "main.h"

#include "CKeys.h"



CSnapmatic* snapmatic;


extern HWND gameWindow;



void OnKeyDown(eKeys keyid)
{
    if (keyid == eKeys::KEY_MENU) snapmatic->getVisual()->getMenu()->ShowMenu(!snapmatic->getVisual()->getMenu()->IsVisible());
    else if (keyid == eKeys::KEY_CAMERA) snapmatic->ToggleCam(!snapmatic->IsFreeCam());
    else if (keyid == eKeys::KEY_CAMERASPEED) snapmatic->ToggleCameraModeSmooth();
    else if (snapmatic->IsFreeCam())
    {
        if (keyid == eKeys::KEY_MOVEF) snapmatic->MoveCam(eMoveDirection::MOVE_FORWARD);
        else if (keyid == eKeys::KEY_MOVEB) snapmatic->MoveCam(eMoveDirection::MOVE_BACK);
        else if (keyid == eKeys::KEY_MOVEL) snapmatic->MoveCam(eMoveDirection::MOVE_LEFT);
        else if (keyid == eKeys::KEY_MOVER) snapmatic->MoveCam(eMoveDirection::MOVE_RIGHT);
        else if (keyid == eKeys::KEY_MOVEU) snapmatic->MoveCam(eMoveDirection::MOVE_UP);
        else if (keyid == eKeys::KEY_MOVED) snapmatic->MoveCam(eMoveDirection::MOVE_DOWN);
    }
}


int main()
{
    while (true)
    {
        if (!snapmatic->IsInit())
        {
            snapmatic->Init();
            
        }
        else
        {
            
            if (GetForegroundWindow() == gameWindow)
            {

                if (!snapmatic->getSamp()->IsTextDrawsVisible()) snapmatic->getSamp()->hideTextDraws();
                if (GetAsyncKeyState(snapmatic->getKeys()->getKey(eKeys::KEY_SNAP)) && snapmatic->getKeys()->keyTick[eKeyGroup::KEY_GROUP_SNAP] < GetTickCount())
                {
                    snapmatic->TakeScreenShot();
                    snapmatic->getKeys()->keyTick[eKeyGroup::KEY_GROUP_SNAP] = GetTickCount() + KEY_TIME;
                }
                if (!snapmatic->getGame()->IsShowHud())
                {
                    if (snapmatic->getGame()->IsInMenu()) snapmatic->getGame()->ToggleHud(true);
                    else snapmatic->getGame()->HideHud();
                }
                if (snapmatic->bFreezeTime) snapmatic->getGame()->setTime(snapmatic->time);
                if (snapmatic->bFreezeWeather) snapmatic->getGame()->setWeather(snapmatic->weather);

            }



        }
       
    }
    return 0;
}



BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, NULL, 0, 0);
        snapmatic = new CSnapmatic();
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


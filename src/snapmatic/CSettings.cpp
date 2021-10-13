
#include "CSettings.h"

#include "CSnapmatic.h"

#include <future>


extern CSnapmatic* snapmatic;


CSettings::CSettings()
{
	bPlaySounds =
	bShowNotifications = false;
}

void CSettings::SaveSettings()
{
	std::async([this]
		{
			WritePrivateProfileStringA("Settings", "EnableSound", std::to_string(bPlaySounds).c_str(), FILE_PATH FILE_NAME);
			WritePrivateProfileStringA("Settings", "EnableNotification", std::to_string(bPlaySounds).c_str(), FILE_PATH FILE_NAME);
			WritePrivateProfileStringA("Settings", "FilterColor", std::to_string(ImColor(snapmatic->filterColor[2],snapmatic->filterColor[1],snapmatic->filterColor[0],snapmatic->filterColor[3])).c_str(), FILE_PATH FILE_NAME);
			WritePrivateProfileStringA("Settings", "CameraSpeed", std::to_string(snapmatic->cameraSpeed).c_str(), FILE_PATH FILE_NAME);
			WritePrivateProfileStringA("Keys", "KeyMoveF", std::to_string(snapmatic->getKeys()->getKey(eKeys::KEY_MOVEF)).c_str(), FILE_PATH FILE_NAME);
			WritePrivateProfileStringA("Keys", "KeyMoveB", std::to_string(snapmatic->getKeys()->getKey(eKeys::KEY_MOVEB)).c_str(), FILE_PATH FILE_NAME);
			WritePrivateProfileStringA("Keys", "KeyMoveL", std::to_string(snapmatic->getKeys()->getKey(eKeys::KEY_MOVEL)).c_str(), FILE_PATH FILE_NAME);
			WritePrivateProfileStringA("Keys", "KeyMoveR", std::to_string(snapmatic->getKeys()->getKey(eKeys::KEY_MOVER)).c_str(), FILE_PATH FILE_NAME);
			WritePrivateProfileStringA("Keys", "KeyMoveU", std::to_string(snapmatic->getKeys()->getKey(eKeys::KEY_MOVEU)).c_str(), FILE_PATH FILE_NAME);
			WritePrivateProfileStringA("Keys", "KeyMoveD", std::to_string(snapmatic->getKeys()->getKey(eKeys::KEY_MOVED)).c_str(), FILE_PATH FILE_NAME);
			WritePrivateProfileStringA("Keys", "KeyFreeCam", std::to_string(snapmatic->getKeys()->getKey(eKeys::KEY_CAMERA)).c_str(), FILE_PATH FILE_NAME);
			WritePrivateProfileStringA("Keys", "KeyCamSmooth", std::to_string(snapmatic->getKeys()->getKey(eKeys::KEY_CAMERASPEED)).c_str(), FILE_PATH FILE_NAME);
			WritePrivateProfileStringA("Keys", "KeyMenu", std::to_string(snapmatic->getKeys()->getKey(eKeys::KEY_MENU)).c_str(), FILE_PATH FILE_NAME);
			WritePrivateProfileStringA("Keys", "KeySnap", std::to_string(snapmatic->getKeys()->getKey(eKeys::KEY_SNAP)).c_str(), FILE_PATH FILE_NAME);
			snapmatic->ShowInfo("Changes Saved");
		});
}

void CSettings::LoadSettings()
{
	std::async([this]
		{
			bPlaySounds = GetPrivateProfileIntA("Settings", "EnableSound", 1, FILE_PATH FILE_NAME);
			bShowNotifications = GetPrivateProfileIntA("Settings", "EnableNotification", 1, FILE_PATH FILE_NAME);
			int color = GetPrivateProfileIntA("Settings", "FilterColor", 0, FILE_PATH FILE_NAME);
			snapmatic->cameraSpeed = GetPrivateProfileIntA("Settings", "CameraSpeed", 1, FILE_PATH FILE_NAME);
			snapmatic->getKeys()->setKey(eKeys::KEY_MOVEF, GetPrivateProfileIntA("Keys", "KeyMoveF", 0x68, FILE_PATH FILE_NAME));
			snapmatic->getKeys()->setKey(eKeys::KEY_MOVEB, GetPrivateProfileIntA("Keys", "KeyMoveB", 0x62, FILE_PATH FILE_NAME));
			snapmatic->getKeys()->setKey(eKeys::KEY_MOVEL, GetPrivateProfileIntA("Keys", "KeyMoveL", 0x64, FILE_PATH FILE_NAME));
			snapmatic->getKeys()->setKey(eKeys::KEY_MOVER, GetPrivateProfileIntA("Keys", "KeyMoveR", 0x66, FILE_PATH FILE_NAME));
			snapmatic->getKeys()->setKey(eKeys::KEY_MOVEU, GetPrivateProfileIntA("Keys", "KeyMoveU", 0x26, FILE_PATH FILE_NAME));
			snapmatic->getKeys()->setKey(eKeys::KEY_MOVED, GetPrivateProfileIntA("Keys", "KeyMoveD", 0x28, FILE_PATH FILE_NAME));
			snapmatic->getKeys()->setKey(eKeys::KEY_CAMERA, GetPrivateProfileIntA("Keys", "KeyFreeCam", 0x7A, FILE_PATH FILE_NAME));
			snapmatic->getKeys()->setKey(eKeys::KEY_CAMERASPEED, GetPrivateProfileIntA("Keys", "KeyCamSmooth", 0x60, FILE_PATH FILE_NAME));
			snapmatic->getKeys()->setKey(eKeys::KEY_MENU, GetPrivateProfileIntA("Keys", "KeyMenu", 0x61, FILE_PATH FILE_NAME));
			snapmatic->getKeys()->setKey(eKeys::KEY_SNAP, GetPrivateProfileIntA("Keys", "KeySnap", 0x7B, FILE_PATH FILE_NAME));
			snapmatic->filterColor[0] = ((color) & 0xFF) / 255.0;
			snapmatic->filterColor[1] = ((color >> 8) & 0xFF) / 255.0;
			snapmatic->filterColor[2] = ((color >> 16) & 0xFF) / 255.0;
			snapmatic->filterColor[3] = ((color >> 24) & 0xFF) / 255.0;

		});
}
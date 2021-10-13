
#ifndef _CSETTINGS_H_
#define _CSETTINGS_H_



#define FILE_NAME "settings.ini"




class CSettings
{
public:
	CSettings();
	bool bPlaySounds;
	bool bShowNotifications;

	void SaveSettings();
	void LoadSettings();

};































#endif
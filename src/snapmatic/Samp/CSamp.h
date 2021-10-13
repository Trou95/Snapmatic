
#ifndef _CSAMP_H_
#define _CSAMP_H_


#include <Windows.h>
#include <string>


#include <fstream>





using namespace std;

extern fstream mFile;

void Log(const char* message);




#define SAMP_MAX_TEXTDRAWS 2048
#define SAMP_MAX_PLAYERTEXTDRAWS 256





enum eVersion
{
	VERSION_UNSUPPORT = 0,
	VERSION_037,
	VERSION_037_R4_2,
	VERSION_037_DL
};


static const DWORD sampInfoPtr[]{ 0x21A0F8,0x26EA0C,0x2ACA24 };
static const DWORD sampInputPtr[]{ 0x21A0E8 ,0x26E9FC ,0x2ACA14 };
static const DWORD sampMiscPtr[]{ 0x21A10C,0x26EA24,0x2ACA3C };

static const unsigned int sampInfoOffset[]{ 0x3CD,0x3DE,0x3DE };
static const unsigned int sampInfoPoolOffset[]{ 0x10,0x20,0x20 };

static const DWORD sampFuncPtr[][3]{
	{0xA0530,0x9BD30,0x9BC10},
	{0xA0530,0xA0750,0xA04C8},
	{0xA0530,0xA0530,0xA0410}
};









class CSAMP
{
	bool bInit;
	DWORD dwSampAddr = NULL;
	DWORD* sampInfo = nullptr;
	DWORD* sampInput = nullptr;
	byte version;
	bool textdraws[SAMP_MAX_TEXTDRAWS];
	bool playerTextDraws[SAMP_MAX_PLAYERTEXTDRAWS];
	bool bIsTextDrawShow;
	bool bIsNameTagShow;

	DWORD* getTextDrawPool();
	int* getTextDraw(int id);
	int* getTextDraw(int, DWORD*);
	int* getPlayerTextDraw(int, DWORD*);
	bool IsTextDrawExist(int, DWORD*);
	bool IsPlayerTextDrawExist(int, DWORD*);

	byte getNameTags();

	 ~CSAMP();


public:
	CSAMP();
	byte init();
	bool IsInit() { return bInit; };

	byte getVersion();
	void addChatMessage(int color, const char* text);

	void showTextDraws();
	void hideTextDraws();
	void SetTextDrawState(bool);
	bool IsTextDrawsVisible();

	void toggleNameTags(bool);
	bool IsNameTagsVisible();

	void toggleSampCursor(bool);

	bool IsSampChatVisible();

	int getSamp() { return (int)sampInfo; };

	friend class CSnapmatic;

};




#endif 














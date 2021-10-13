#include "CSamp.h"



CSAMP::CSAMP()
{
	bInit =
	bIsNameTagShow = false;
	bIsTextDrawShow = true;
	version = 0;
	memset(textdraws, 0, SAMP_MAX_TEXTDRAWS);
	memset(playerTextDraws, 0, SAMP_MAX_PLAYERTEXTDRAWS);
}


byte CSAMP::init()
{
	if (bInit)
		return true;
	if (dwSampAddr == NULL)
		dwSampAddr = (DWORD)GetModuleHandleA("samp.dll");
	if (!dwSampAddr)
	{
		while(dwSampAddr)
			dwSampAddr = (DWORD)GetModuleHandleA("samp.dll");

	}
	version = getVersion();
	if (!version)
	{
		return 0;
	}
	sampInfo = *reinterpret_cast<DWORD**>(dwSampAddr + sampInfoPtr[--version]);
	if (!sampInfo)
	{
		while (sampInfo)
		{
			sampInfo = *reinterpret_cast<DWORD**>(dwSampAddr + sampInfoPtr[version]);
			Sleep(100);
		}
	}
	sampInput = (DWORD*)(dwSampAddr + sampInputPtr[version]);
	if (!sampInput)
	{
		sampInput = (DWORD*)(dwSampAddr + sampInputPtr[version]);
		while (sampInput)
		{
			sampInput = (DWORD*)(dwSampAddr + sampInputPtr[version]);
			Sleep(100);
		}
	}
	bInit = true;
	return true;
}



byte CSAMP::getVersion()
{
	if (dwSampAddr == NULL)
		return 0;
	unsigned int _version = *(unsigned int*)(dwSampAddr + 0x128);
	if (_version == 0x5542F47A)
		return eVersion::VERSION_037;
	else if (_version == 0x5A6A3130)
		return eVersion::VERSION_037_DL;
	return eVersion::VERSION_UNSUPPORT;
}


DWORD* CSAMP::getTextDrawPool()
{
	return (DWORD*)((char*)(*(DWORD*)((char*)sampInfo + sampInfoOffset[version])) + sampInfoPoolOffset[version]);

}

int* CSAMP::getTextDraw(int id)
{
	return (int*)((char*)*getTextDrawPool()) + id;
}

int* CSAMP::getTextDraw(int id, DWORD* pool)
{
	return (int*)(char*)*pool + id;
}

int* CSAMP::getPlayerTextDraw(int id, DWORD* pool)
{
	return (int*)((char*)*pool + 0x2000) + id;
}

bool CSAMP::IsTextDrawExist(int id, DWORD* pool)
{
	return *(DWORD**)((char*)*pool + 0x2400 + (id * 4)) != nullptr ? true : false;
}


bool CSAMP::IsPlayerTextDrawExist(int id, DWORD* pool)
{
	return *(DWORD**)((char*)*pool + 0x4400 + (id * 4)) != nullptr ? true : false;
}


void CSAMP::hideTextDraws()
{
	DWORD* pool = getTextDrawPool();
	for (int i = 0; i < SAMP_MAX_TEXTDRAWS; i++)
	{
		int *textDraw;
		if (i < SAMP_MAX_PLAYERTEXTDRAWS)
		{
			textDraw = getPlayerTextDraw(i, pool);
			if (*textDraw)
			{
				*textDraw = 0;
				playerTextDraws[i] = true;
			}
		}
		textDraw = getTextDraw(i, pool);
		if (*textDraw)
		{
			*textDraw = 0;
			textdraws[i] = true;			
		}
	}
}

void CSAMP::showTextDraws()
{
	DWORD *pool = getTextDrawPool();
	for (int i = 0; i < SAMP_MAX_TEXTDRAWS; i++)
	{
		if (i < SAMP_MAX_PLAYERTEXTDRAWS)
		{
			if (playerTextDraws[i])
			{
				if (IsPlayerTextDrawExist(i, pool))
					*getPlayerTextDraw(i, pool) = 1;
			}
		}
		if (textdraws[i])
		{
			if (IsTextDrawExist(i, pool))
				*getTextDraw(i, pool) = 1;
		}
	}
	memset(textdraws, false, SAMP_MAX_TEXTDRAWS);
	memset(playerTextDraws, false, SAMP_MAX_PLAYERTEXTDRAWS);
	SetTextDrawState(true);
}

void CSAMP::SetTextDrawState(bool state)
{
	bIsTextDrawShow = state;
}

bool CSAMP::IsTextDrawsVisible()
{
	return bIsTextDrawShow;
}

byte CSAMP::getNameTags()
{
	return *(byte*)((char*)(*(DWORD*)((char*)sampInfo + 965)) + 56);
}

void CSAMP::toggleNameTags(bool state)
{
	*(byte*)((char*)(*(DWORD*)((char*)sampInfo + 965)) + 56) = state;
	bIsNameTagShow = state;
}

bool CSAMP::IsNameTagsVisible()
{
	return bIsNameTagShow;
}


void CSAMP::toggleSampCursor(bool state)
{

	void* obj = *(void**)(dwSampAddr + sampMiscPtr[version]);
	((void(__thiscall*) (void*, int, bool)) (dwSampAddr + sampFuncPtr[version][1]))(obj, state ? 3 : 0, !state);
	if(!state) ((void(__thiscall*) (void*)) (dwSampAddr + sampFuncPtr[version][2]))(obj);
}

bool CSAMP::IsSampChatVisible()
{
	if (!sampInput)
		return false;
	return *(bool*)(*sampInput + 0x14E0);
}


//Unused
//Only for debug
void CSAMP::addChatMessage(int color,const char* message)
{
	DWORD	chatinfo = dwSampAddr + 0x21A0E4;
	DWORD	func = dwSampAddr + 0x64010;

	void* obj = *(void**)(chatinfo);
	((void(__thiscall*)(void*, int, const char*, int, int, int))(func))(obj, 8, message, 0, color, 0);
}


CSAMP::~CSAMP()
{
	delete sampInfo;
}


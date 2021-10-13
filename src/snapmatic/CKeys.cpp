

#include "CKeys.h"





Key _keys[__KEY_SIZE__] = {};


std::string _keyInfo[__KEY_SIZE__] = {
	"Key Move Forward",
	"Key Move Backward",
	"Key Move Left",
	"Key Move Right",
	"Key Move Up",
	"Key Move Down",
	"Key Show Menu",
	"Toggle Freecam",
	"Key Toggle Smooth Cam",
	"Take Screenshot"
};

int keyRange[][2] =
{
	{'0','9'},
	{'A','Z'},
	{96,105},
	{112,123},
	{37,40}
};



CKeys::CKeys()
{
	keyIndex = -1;
	for (int i = 0; i < __KEY_SIZE__; i++)
	{
		bIsSelect[i] = false;
	}
	ResetKeys();
}

bool CKeys::IsKeyMode()
{
	return keyIndex > -1;
}

bool CKeys::IsValidKey(Key keyid)
{
	for (auto key : keyRange)
		if (keyid >= key[0] && keyid <= key[1]) return true;
	return false;
}


int CKeys::getKeyIndex()
{
	return keyIndex;
}

void CKeys::setKeyIndex(int keyindex)
{
	if (keyindex < -1) keyindex = -1;
	else if (keyindex >= __KEY_SIZE__) keyindex = __KEY_SIZE__ - 1;
	this->keyIndex = keyindex;
}

void CKeys::setKey(eKeys key, Key keyid)
{
	keys[key] = keyid;
}

Key CKeys::getKey(eKeys keyid)
{
	return keys[keyid];
}

Key CKeys::getKey(int keyid)
{
	return keys[keyid];
}

eKeyGroup CKeys::getKeyGroup(eKeys keyid)
{
	if (keyid == eKeys::KEY_MENU) return eKeyGroup::KEY_GROUP_MENU;
	else if (keyid <= eKeys::KEY_MOVED) return eKeyGroup::KEY_GROUP_MOVE;
	else if (keyid <= eKeys::KEY_CAMERASPEED) return eKeyGroup::KEY_GROUP_SETTINGS;
	else return eKeyGroup::KEY_GROUP_SNAP;
}

void CKeys::ResetKeys()
{
	for (int key = 0; key < sizeof(keyTick) / sizeof(*keyTick); key++)
		keyTick[key] = 0;
}

std::string CKeys::keyName(Key key)
{
	if ((key >= 48 && key <= 57) || (key >= 65 && key <= 90))
	{
		char keyText[3];
		sprintf(keyText,"%c",key);
		return keyText;
	}
	else if (key >= 96 && key <= 105)
	{
		char keyText[7];
		sprintf(keyText, "Num%d", key - 96);
		return keyText;
	}
	else if (key >= 112 && key <= 123)
	{
		char keyText[4];
		sprintf(keyText, "F%d", (key - 112) + 1);
		return keyText;
	}
	else if (key >= 37 && key <= 40)
	{	
		std::string keyText = key == 37 ? "Left" : key == 38 ? "Up" : key == 39 ? "Right" : "Down";
		return keyText.append(" Arrow");
	}
	return std::string("Undefined");
}

#ifndef _CKEYS_H_
#define _CKEYS_H_


#include <string>



typedef unsigned char Key;



enum eMoveDirection
{
	MOVE_FORWARD = 0,
	MOVE_BACK,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN
};

constexpr auto __BEGIN__ = __LINE__;
enum eKeys {
	KEY_MOVEF = 0,
	KEY_MOVEB,
	KEY_MOVEL,
	KEY_MOVER,
	KEY_MOVEU,
	KEY_MOVED,
	KEY_MENU,
	KEY_CAMERA,
	KEY_CAMERASPEED,
	KEY_SNAP
};
constexpr auto __KEY_SIZE__ = __LINE__ - __BEGIN__ - 3;


enum eKeyGroup
{
	KEY_GROUP_MENU = 0,
	KEY_GROUP_MOVE,
	KEY_GROUP_SETTINGS,
	KEY_GROUP_SNAP
};



class CKeys
{
	int keyIndex;
	Key keys[__KEY_SIZE__];

	void ResetKeys();

public:
	bool bIsSelect[__KEY_SIZE__];
	int keyTick[4];

	CKeys();
	bool IsKeyMode();
	bool IsValidKey(Key);
	int getKeyIndex();
	void setKeyIndex(int);
	void setKey(eKeys,Key);
	Key getKey(eKeys);
	Key getKey(int);
	eKeyGroup getKeyGroup(eKeys);
	std::string keyName(Key key);

};






























#endif



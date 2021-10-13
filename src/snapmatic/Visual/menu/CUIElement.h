
#ifndef _CUIELEMENT_H_
#define _CUIELEMENT_H_


#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_internal.h"



#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")



#include "../../Game/CGame.h"



#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 238


#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 30



class CUIElement
{
public:
	const char* name;

	virtual ~CUIElement() = default;
	virtual bool render() = 0;

	template<typename T>
	bool IsType() { return (dynamic_cast<T*>(this) != NULL); };
};


class CSelectable
{
public:
	bool bIsSelected;
};

template<class T>
class CSlider
{
public:
	T value;
	T minValue;
	T maxValue;

	T getValue() { return value; }
};

class CSelectBox : CSelectable
{
	const char* name;
	const char** items;
	int itemSize;
public:
	const char* selectedItem;
	CSelectBox() { ; };
	CSelectBox(const char* name, const char** items, int size);

	friend class CWeather;
};
































#endif

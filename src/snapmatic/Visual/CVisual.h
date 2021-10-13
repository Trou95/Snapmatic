
#ifndef _CVISUAL_H_
#define _CVISUAL_H_


#include "menu/CMenu.h"




class CVisual
{
	bool bInit;
	CMenu *pMenu;
	int screenWidth;
	int screenHeight;
	bool bTakeScreenShot; // Take Screenshot on next frame
	
	IDirect3DDevice9* device;


	void SaveScreenShot();


	static HRESULT WINAPI OnPresent(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
	static HRESULT WINAPI OnReset(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
public:
	CVisual();
	bool init();
	void initDevice();
	bool IsInit();
	CMenu *getMenu();
	void TakeScreenShot();
	void getScreenResolution(int&, int&);

	void DrawFilter(IDirect3DDevice9*, float, float, DWORD color);

	

};






#endif


#include "CVisual.h"
#include "../CSnapmatic.h"

#include <Windows.h>
#include <future>


#define IMGUI_IMPL_WIN32_DISABLE_GAMEPAD
#define IMGUI_IMPL_WIN32_DISABLE_LINKING_XINPUT



typedef HRESULT(WINAPI* _Present)(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*); //прототип
_Present oPresent;

typedef HRESULT(WINAPI* _Reset)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
_Reset oReset;



extern CSnapmatic *snapmatic;



extern HWND gameWindow;




IDirect3DSurface9* surface;



HRESULT WINAPI CVisual::OnPresent(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hdest, const RGNDATA* pDirtyRegion)
{
	if (!snapmatic->getVisual()->IsInit())
	{
		
		if (gameWindow)
		{
			snapmatic->getVisual()->getMenu()->Init();
			HRESULT hr = D3DXCreateTextureFromFileA(pDevice, FILE_PATH "res\\snapmatic.png", &snapmatic->getVisual()->getMenu()->mIcon);
			
			ImGui_ImplWin32_Init(gameWindow);
			ImGui_ImplDX9_Init(pDevice);
			snapmatic->getVisual()->initDevice();
			snapmatic->getVisual()->device = pDevice;
		}


	}
	else if (!snapmatic->getGame()->IsInMenu())
	{
		if(snapmatic->IsShowFilter()) snapmatic->getVisual()->DrawFilter(pDevice, snapmatic->getVisual()->screenWidth,snapmatic->getVisual()->screenHeight, ImColor(snapmatic->filterColor[2],snapmatic->filterColor[1],snapmatic->filterColor[0],snapmatic->filterColor[3]));
		if (snapmatic->getVisual()->getMenu()->IsVisible())
		{

			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();


			snapmatic->getVisual()->getMenu()->Render();
			if (snapmatic->getVisual()->getMenu()->IsSettingsVisible()) snapmatic->getVisual()->getMenu()->RenderSettings();


			ImGui::EndFrame();

			if (pDevice->BeginScene() >= 0)
			{
				ImGui::Render();
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
				pDevice->EndScene();
			}

		}

	}
	
	return oPresent(pDevice, pSourceRect, pDestRect, hdest, pDirtyRegion); // возврат оригинала
}



HRESULT WINAPI CVisual::OnReset(IDirect3DDevice9* m_pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	auto  result = oReset(m_pDevice, pPresentationParameters);
	return result;
}



CVisual::CVisual()
{
	bInit = false;
	bTakeScreenShot = false;
	device = nullptr;
	pMenu = new CMenu();
	getScreenResolution(screenWidth, screenHeight);
}


bool CVisual::init()
{
	void** vTableDevice = *(void***)(*(DWORD*)0xC97C28);
	VMTHookManager* vmtHooks = new VMTHookManager(vTableDevice);
	oPresent = (_Present)vmtHooks->Hook(17, (void*)OnPresent);
	oReset = (_Reset)vmtHooks->Hook(16, (void*)OnReset);
	return true;
}


void CVisual::initDevice()
{
	bInit = true;
}


bool CVisual::IsInit()
{
	return bInit;
}

CMenu* CVisual::getMenu()
{
	return pMenu;
}

void CVisual::getScreenResolution(int& x, int& y)
{
	x = GetSystemMetrics(SM_CXSCREEN);
	y = GetSystemMetrics(SM_CYSCREEN);
}


struct vertex
{
	FLOAT x, y, z, rhw;
	DWORD color;
};


void CVisual::DrawFilter(IDirect3DDevice9* pDevice, float x, float y, DWORD color)
{

	LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
	LPDIRECT3DINDEXBUFFER9  g_pIB = NULL;

	vertex V[4];

	V[0].color = V[1].color = V[2].color = V[3].color = color;


	V[0].z = V[1].z = V[2].z = V[3].z = 0;
	V[0].rhw = V[1].rhw = V[2].rhw = V[3].rhw = 0;

	V[0].x = 0;
	V[0].y = 0;
	V[1].x = x;
	V[1].y = 0;
	V[2].x = x;
	V[2].y = y;
	V[3].x = 0;
	V[3].y = y;

	unsigned short indexes[] = { 0, 1, 3, 1, 2, 3 };

	pDevice->CreateVertexBuffer(4 * sizeof(vertex), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB, NULL);
	pDevice->CreateIndexBuffer(2 * sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL);

	VOID* pVertices;
	g_pVB->Lock(0, sizeof(V), (void**)&pVertices, 0);
	memcpy(pVertices, V, sizeof(V));
	g_pVB->Unlock();

	VOID* pIndex;
	g_pIB->Lock(0, sizeof(indexes), (void**)&pIndex, 0);
	memcpy(pIndex, indexes, sizeof(indexes));
	g_pIB->Unlock();

	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(NULL);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetStreamSource(0, g_pVB, 0, sizeof(vertex));
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetIndices(g_pIB);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	g_pVB->Release();
	g_pIB->Release();
}


void CVisual::TakeScreenShot()
{
	if (device == nullptr)
	{
		bTakeScreenShot = false;
		return;
	}
	if (!bTakeScreenShot)
	{
		int x, y;
		getScreenResolution(x, y);
		device->CreateOffscreenPlainSurface(x, y, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &surface, NULL);
		if (device->GetFrontBufferData(0, surface) == D3D_OK) SaveScreenShot();
		else bTakeScreenShot = false;
	}
}






void CVisual::SaveScreenShot()
{
	if (surface)
	{
		if (std::async([] {
			auto time = std::time(0);
			auto dateTime = std::localtime(&time);

			char _time[25];
			strftime(_time, sizeof(_time), "%d-%m-%Y_%H-%M-%S.jpg", dateTime);

			string filePath = FILE_PATH "images\\image_";
			filePath.append(_time);

			snapmatic->PlayGameSound(1132);

			D3DXSaveSurfaceToFileA(filePath.c_str(), D3DXIFF_JPG, surface, NULL, NULL);
			surface->Release();

			snapmatic->ShowInfo("Screenshot taken");

			return true;

			}).get()) {

			bTakeScreenShot = false;

		} 

	}
	bTakeScreenShot = false;

}







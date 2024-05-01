#include "stdafx.h"
#include "kg_lab.h"

namespace directx
{
	IDirect3D9* pD3D = 0;
	IDirect3DDevice9* pD3DDev = 0;
	bool boInvalid = false;
	D3DPRESENT_PARAMETERS PP = {};
	void FillParams()
	{
		RECT rc = {};
		GetClientRect(main::hWnd, &rc);
		PP.BackBufferWidth = rc.right - rc.left;
		PP.BackBufferHeight = rc.bottom - rc.top;
		PP.BackBufferFormat = D3DFMT_X8R8G8B8;
		PP.BackBufferCount = 0;
		PP.MultiSampleType = D3DMULTISAMPLE_NONE;
		PP.MultiSampleQuality = 0;
		PP.SwapEffect = D3DSWAPEFFECT_DISCARD;
		PP.hDeviceWindow = main::hWnd;
		PP.Windowed = true;
		PP.EnableAutoDepthStencil = true;
		PP.AutoDepthStencilFormat = D3DFMT_D24S8;
		PP.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
		PP.FullScreen_RefreshRateInHz = 0;
		PP.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}
	bool InitDX()
	{
		pD3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (!pD3D)
			return false;
		FillParams();
		pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			main::hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&PP, &pD3DDev);
		if (!pD3DDev)
		{

				pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF,
					main::hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&PP, &pD3DDev);
			if (!pD3DDev)
			{
				main::message_box_("Неможливо ініціалізувати DirectX!"); //(L"Неможливо ініціалізувати DirectX!");
				return false;
			} // if( !pD3DDev )
		} // if ( !pD3DDev )
		if (!render::LoadResources(pD3DDev))
			return false;
		return true;
	}
	void CloseDX()
	{
		render::OnExit(pD3DDev);
		if (pD3DDev)
		{
			pD3DDev->Release();
			pD3DDev = 0;
		} // if ( pD3DDev )
		if (pD3D)
		{
			pD3D->Release();
			pD3D = 0;
		} // if( pD3D )
		CoUninitialize();
	}
	void FlipPages()
	{
		pD3DDev->Present(0, 0, 0, 0);
	}
	void Invalidate()
	{
		if (!pD3DDev || boInvalid)
			return;
		render::OnLostDevice(pD3DDev);
		pD3DDev->EvictManagedResources();
		boInvalid = true;
	}
	void Restore()
	{
		if (!pD3DDev || !boInvalid)
			return;
		boInvalid = pD3DDev->Reset(&PP) != S_OK;

		if (!boInvalid)
			render::OnRestoreDevice(pD3DDev);
	
	}

		bool TestAvailDev()
	{
		if (!pD3DDev)
			return false;
		switch (pD3DDev->TestCooperativeLevel())
		{
		case D3DERR_DEVICELOST: { Invalidate(); break; }
		case D3DERR_DEVICENOTRESET: { Restore(); break; }
		} // switch( pD3DDev->TestCooperativeLevel() )
		return !boInvalid;
	}
	void Paint()
	{
		if (!pD3DDev)
			return;
		if (!TestAvailDev() || pD3DDev->BeginScene() != D3D_OK)
			return;
		pD3DDev->Clear(0, 0, D3DCLEAR_STENCIL | D3DCLEAR_TARGET |
			D3DCLEAR_ZBUFFER, 0xf0ffff, 1.f, 0);
		render::RenderScene(pD3DDev, render::CurRenderMethod);
		pD3DDev->EndScene();
		FlipPages();
	}
	void Pump()
	{
		if (!main::boActive)
			Sleep(20);
		Paint();
	}
}; // namespace directx
#include "stdafx.h"
#include "kg_lab.h"
namespace main
{
	HINSTANCE hInst;
	bool boActive = false;
	HWND hWnd = 0;
	const TCHAR* szClass = "KG Lab Class";
	const TCHAR* szTitle = "Комп'ютерна графіка. Лабораторна робота.";
	void message_box_(const TCHAR* mes)
	{
		::MessageBox(0, mes, 0, MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
	ATOM RegisterClass(HINSTANCE hInstance)
	{
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = main::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;


			wcex.hInstance = hInstance;
		wcex.hIcon = 0;
		wcex.hCursor = LoadCursor(0, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = 0;
		wcex.lpszClassName = szClass;
		wcex.hIconSm = 0;
		return RegisterClassEx(&wcex);
	}
	bool InitInstance(HINSTANCE hInstance, int nCmdShow)
	{
		hInst = hInstance;
		DWORD wid = GetSystemMetrics(SM_CXSCREEN);
		DWORD hei = GetSystemMetrics(SM_CYSCREEN);
		hWnd = CreateWindow(szClass, szTitle, WS_CAPTION | WS_VISIBLE |
			WS_SYSMENU | WS_POPUP, 0, 0, wid, hei, 0, 0, hInstance, 0);

		if (!hWnd)
		{
			message_box_("Неможливо створити вікно додатка!");
			return false;
		} // if ( !hWnd )
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
		return true;
	}
	LRESULT CALLBACK WndProc(HWND hWnd, UINT Message,

		WPARAM wParam, LPARAM lParam)

	{
		switch (Message)
		{
		case WM_ACTIVATEAPP:
		{
			boActive = wParam == 1;
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);


		}
		return 0;
	}
}; // namespace main
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,

	LPTSTR lpCmdLine, int nCmdShow)

{
	CoInitializeEx(0, COINIT_MULTITHREADED);
	main::RegisterClass(hInstance);
	if (!main::InitInstance(hInstance, nCmdShow))
		return -1;
	MSG msg;
	do
	{
		if (!PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			continue;
		} // if( !PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	} while (WM_QUIT != msg.message);
	return (int)msg.wParam;
}
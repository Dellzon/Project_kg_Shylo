#pragma once
#pragma warning (disable:4100)
namespace main
{
	extern HWND hWnd;
	extern bool boActive;
	void message_box_(const TCHAR* mes);
	ATOM RegisterClass(HINSTANCE hInstance);
	bool InitInstance(HINSTANCE, int);
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
}; // namespace main

#pragma once
#pragma warning (disable:4100)

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace main
{
	extern HWND hWnd;
	extern bool boActive;
	void message_box_(const TCHAR* mes);
	ATOM RegisterClass(HINSTANCE hInstance);
	bool InitInstance(HINSTANCE, int);
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
}; // namespace main
namespace directx
{
	void FillParams();
	bool InitDX();
	void CloseDX();
	void FlipPages();
	void Invalidate();
	void Restore();
	bool TestAvailDev();
	void Paint();
	void Pump();
	typedef D3DXVECTOR3 s_vector3;


		typedef D3DXVECTOR4 s_vector4;
	typedef D3DXMATRIX s_matrix;
	typedef WORD t_index;
	const float deg2rad = 3.14f / 180.f;
	const s_vector3 vec0 = s_vector3(0.f, 0.f, 0.f);
	const s_vector3 vec1 = s_vector3(1.f, 1.f, 1.f);
	struct s_vertex
	{
		s_vertex() {}
		s_vertex(const s_vector3& Pos_, const s_vector3& Norm_ = vec0) :
			Pos(Pos_), Norm(Norm_) {}
		s_vector3 Pos;
		s_vector3 Norm;
	};
	extern D3DPRESENT_PARAMETERS PP;
}; // namespace directx

namespace render
{
	enum
	{
		RM_WIRE,
		RM_MAX,
	};
	const int CurRenderMethod = RM_WIRE;
	const DWORD BackColor = 0xff000000UL;
	bool LoadResources(IDirect3DDevice9* Dev);
	void RenderScene(IDirect3DDevice9* Dev, int TN);
	void OnLostDevice(IDirect3DDevice9* Dev);
	void OnRestoreDevice(IDirect3DDevice9* Dev);
	void OnExit(IDirect3DDevice9* Dev);
	extern D3DXHANDLE hMatWorld;
	extern D3DXHANDLE hObjColor;
	extern D3DXHANDLE hPower;
	extern D3DXHANDLE hSpecLevel;
	extern D3DXHANDLE hLigColor;
	extern D3DXHANDLE hAmbColor;
	extern D3DXHANDLE hLigDir;
	extern D3DXHANDLE hLigPos;
	extern D3DXHANDLE hMatViewProj;
	extern D3DXHANDLE hMatIView;
}; // namespace render
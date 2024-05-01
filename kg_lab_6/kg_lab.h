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
		RM_LAMBERT,
		RM_PHONG,
		RM_MAX,
	};
	const int CurRenderMethod = RM_PHONG;
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
namespace scene
{
	using namespace directx;
	using namespace render;
	void RenderFigures(IDirect3DDevice9* Dev, LPD3DXEFFECT pEffect);
	void UpdateSceneMatrices(LPD3DXEFFECT pEffect);
	void color2vec(DWORD color_, s_vector4& obj_color);
	struct s_figure
	{
		s_vector3 obj_scale, obj_rot, obj_pos;
		s_vector4 obj_color;
		float level, spower;
		mutable s_matrix world;
		mutable bool changes;
		bool anim;
		virtual const s_vertex* verts(DWORD& cnt) const = 0;
		virtual const t_index* inds(DWORD& cnt) const = 0;
		const s_matrix& matrix() const;
		const s_vector4& color() const { return obj_color; }
		float spec_level() const { return level; }
		float power() const { return spower; }
		void init();
		void scale(const s_vector3& scale_) { obj_scale = scale_; changes = true; }
		void rotate(const s_vector3& rot_) { obj_rot = rot_; changes = true; }
		void translate(const s_vector3& pos_) { obj_pos = pos_; changes = true; }
		void set_color(DWORD color_) { color2vec(color_, obj_color); }
		s_figure(const s_vector3& pos_, const s_vector3& rot_ = vec0,
			const s_vector3& scale_ = vec1, DWORD color_ = 0xFF808080UL,
			float level_ = 0.5f, float spower_ = 16.f, bool anim_ = true);
		void comp_normals();
	};


		void ReleaseScene();
	void InitScene();
}; // namespace scene
namespace figures
{
	using namespace directx;
	struct s_cube : public scene::s_figure
	{
		virtual const s_vertex* verts(DWORD& cnt) const;
		virtual const t_index* inds(DWORD& cnt) const;
		s_cube(const s_vector3& pos_, const s_vector3& rot_ = vec0,
			const s_vector3& scale_ = vec1, DWORD color_ = 0xff808080UL,
			float level_ = 0.5f, float spower_ = 16.f) :
			scene::s_figure(pos_, rot_, scale_, color_, level_, spower_) { comp_normals(); }
	};
}; // namespace figures
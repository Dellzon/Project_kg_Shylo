#include "stdafx.h"
#include "kg_lab.h"
namespace scene
{
	s_figure* pSceneRoot = 0;
	s_vector3 vEyePos;
	s_vector3 vAtPos;
	float fFovY;
	void color2vec(DWORD color_, s_vector4& obj_color)
	{
		DWORD red = (color_ >> 16) & 0xff;
		DWORD green = (color_ >> 8) & 0xff;
		DWORD blue = color_ & 0xff;
		DWORD alpha = (color_ >> 24) & 0xff;
		obj_color = s_vector4(red / 255.f, green / 255.f, blue / 255.f, alpha / 255.f);
	}
	void RenderFigures(IDirect3DDevice9* Dev, LPD3DXEFFECT pEffect)
	{
		const s_figure* f = pSceneRoot;
		DWORD vcnt = 0, icnt = 0;
		const s_vertex* v = f->verts(vcnt);
		const t_index* i = f->inds(icnt);
		DWORD tri_cnt = icnt / 3;
		const s_matrix& MatWorld = f->matrix();
		const s_vector4& vObjColor = f->color();
		pEffect->SetMatrix(hMatWorld, &MatWorld);
		pEffect->SetVector(hObjColor, &vObjColor);
		pEffect->CommitChanges();
		Dev->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, vcnt, tri_cnt,

			i, D3DFMT_INDEX16, v, sizeof(s_vertex));

	}
	s_figure::s_figure(const s_vector3& pos_, const s_vector3& rot_,
		const s_vector3& scale_, DWORD color_, float level_, float spower_, bool anim_) :
		obj_scale(scale_), obj_rot(rot_), obj_pos(pos_), level(level_), spower(spower_),
		changes(true)

	{
		D3DXMatrixIdentity(&world);
		set_color(color_);
	}
	const s_matrix& s_figure::matrix() const
	{
		if (changes)
		{
			s_matrix matS, matR, matT, matSR;
			D3DXMatrixScaling(&matS, obj_scale.x, obj_scale.y, obj_scale.z);
			D3DXMatrixRotationYawPitchRoll(&matR, obj_rot.x * deg2rad,
				obj_rot.y * deg2rad, obj_rot.z * deg2rad);
			D3DXMatrixTranslation(&matT, obj_pos.x, obj_pos.y, obj_pos.z);
			D3DXMatrixMultiply(&matSR, &matS, &matR);
			D3DXMatrixMultiply(&world, &matSR, &matT);
			changes = false;
		} // if( changes )
		return world;
	}
	void ReleaseScene()
	{
		delete pSceneRoot;
		pSceneRoot = 0;
	}
	void InitScene()
	{
		vEyePos = vec0;
		vAtPos = s_vector3(0.f, 0.f, 1.f);
		fFovY = 60.f;
		pSceneRoot = new figures::s_cube(
			s_vector3( 1.f, 0.f, 25.f ), s_vector3( 45.f, 0.f, 0.f ), s_vector3( 2.f, 2.f, 2.f ), 0xFF000FF00UL );

	}

	void UpdateSceneMatrices(LPD3DXEFFECT pEffect)
	{
		const s_vector3 Up(0.f, 1.f, 0.f);
		s_matrix MatView, MatIView;
		D3DXMatrixLookAtLH(&MatView, &vEyePos, &vAtPos, &Up);
		float FOV = fFovY * deg2rad;
		float Aspect = (float)PP.BackBufferWidth / PP.BackBufferHeight;
		float ZNear = 1.f;
		float ZFar = 100.f;
		s_matrix MatProj;
		D3DXMatrixPerspectiveFovLH(&MatProj, FOV, Aspect, ZNear, ZFar);
		s_matrix MatViewProj;
		D3DXMatrixMultiply(&MatViewProj, &MatView, &MatProj);
		float det;
		D3DXMatrixInverse(&MatIView, &det, &MatView);
		pEffect->SetMatrix(hMatIView, &MatIView);
		pEffect->SetMatrix(hMatViewProj, &MatViewProj);
	}
}; // namespace scene
#include "stdafx.h"
#include "kg_lab.h"

namespace render
{
	IDirect3DVertexDeclaration9* pDecl = 0;
	LPD3DXEFFECT pEffect = 0;
	D3DXHANDLE hTechnique[RM_MAX] = {};
	D3DXHANDLE hMatViewProj = 0;
	D3DXHANDLE hMatIView = 0;
	D3DXHANDLE hMatWorld = 0;
	D3DXHANDLE hObjColor = 0;
	D3DXHANDLE hPower = 0;
	D3DXHANDLE hSpecLevel = 0;
	D3DXHANDLE hLigColor = 0;
	D3DXHANDLE hAmbColor = 0;
	D3DXHANDLE hLigDir = 0;
	D3DXHANDLE hLigPos = 0;
	void OnLostDevice(IDirect3DDevice9* Dev)
	{
		if (pEffect)
			pEffect->OnLostDevice();

	}
	void OnRestoreDevice(IDirect3DDevice9* Dev)
	{
		if (pEffect)
			pEffect->OnResetDevice();

	}
	void OnExit(IDirect3DDevice9* Dev)
	{
		scene::ReleaseScene();
		if (pEffect)
		{
			pEffect->Release();
			pEffect = 0;
		} // if( pEffect )


			if (pDecl)
			{
				pDecl->Release();
				pDecl = 0;
			} // if (pDecl)
	}
	bool LoadResources(IDirect3DDevice9* Dev)
	{
		LPD3DXBUFFER errors = 0;
		D3DXCreateEffectFromFile(Dev, "shader.txt", 0, 0, 0, 0, &pEffect, &errors); //D3DXCreateEffectFromFile(Dev, L"shader.txt", 0, 0, 0, 0, &pEffect, &errors); 
		if (errors)
		{
			const char* e = (const char*)errors->GetBufferPointer();
			TCHAR buf[512];
			::MultiByteToWideChar(CP_ACP, 0, e, -1, (LPWSTR)buf, sizeof(buf) / sizeof(buf[0]));
			main::message_box_(buf);
			errors->Release();
			return false;
		} // if( errors )
		if (!pEffect)
		{
			main::message_box_("Шейдер не знайдено!"); //main::message_box_(L"Шейдер не знайдено!");
			return false;
		} // if( !pEffect )
		static const char* tnames[RM_MAX] = { "wire","lambert" };
		for (int i = 0; i < RM_MAX; ++i)
		{
			hTechnique[i] = pEffect->GetTechniqueByName(tnames[i]);
			if (!hTechnique[i])
			{
				main::message_box_("Відповідний метод рендеру не найден!"); //main::message_box_(L"Відповідний метод рендеру не найден!");
				return false;
			} // if( !hTechnique[i] )
		} // for( int i = 0; i < RM_MAX; ++i )
		hMatViewProj = pEffect->GetParameterByName(0, "m_view_proj");
		hMatIView = pEffect->GetParameterByName(0, "m_iview");
		hMatWorld = pEffect->GetParameterByName(0, "m_world");
		hObjColor = pEffect->GetParameterByName(0, "v_obj_color");
		hPower = pEffect->GetParameterByName(0, "f_power");
		hSpecLevel = pEffect->GetParameterByName(0, "f_spec_level");


			hLigColor = pEffect->GetParameterByName(0, "v_lig_color");
		hAmbColor = pEffect->GetParameterByName(0, "v_amb_color");
		hLigDir = pEffect->GetParameterByName(0, "v_lig_dir");
		hLigPos = pEffect->GetParameterByName(0, "v_lig_pos");
		static const D3DVERTEXELEMENT9 dcl[] =
		{
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,
			D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,
		D3DDECLUSAGE_NORMAL, 0 },
		D3DDECL_END()
		};
		Dev->CreateVertexDeclaration(dcl, &pDecl);
		if (!pDecl)
			return false;
		scene::InitScene();
		return true;
	}
	void RenderScene(IDirect3DDevice9* Dev, int TN)
	{
		if (!pEffect || !hTechnique || !pDecl)
			return;
		pEffect->SetTechnique(hTechnique[TN]);
		Dev->SetVertexDeclaration(pDecl);
		scene::UpdateSceneMatrices(pEffect);
		UINT passes = 0;
		if (pEffect->Begin(&passes, 0) != D3D_OK)
			return;
		for (UINT i = 0; i < passes; ++i)
		{
			if (pEffect->BeginPass(i) != D3D_OK)
				break;
			scene::RenderFigures(Dev, pEffect);
			pEffect->EndPass();
		} // for( UINT i = 0; i < passes; ++i )
		pEffect->End();
	}
}; // namespace render
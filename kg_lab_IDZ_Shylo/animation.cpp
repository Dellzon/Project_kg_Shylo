#include "stdafx.h"
#include "kg_lab.h"
namespace animation
{
	float fYaw = 0.f;
	float fPitch = 0.f;
	//отримання часу який пройшов з минулого кадру
	float PeekTimeDelta()
	{
		static int t = GetTickCount();
		int dt = GetTickCount() - t;
		t = GetTickCount();
		return 0.001f * dt;
	}
	void UpdateSceneObjects(scene::s_figure* pRoot)
	{
		float dt = PeekTimeDelta();
		fYaw += dt * 15.f;
		fPitch += dt * 25.f;
		pRoot->rotate(s_vector3(fYaw, fPitch, 0.f));
	}
}// namespace animation
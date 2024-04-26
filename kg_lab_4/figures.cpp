#include "stdafx.h"
#include "kg_lab.h"
namespace figures
{
	const s_vertex* s_cube::verts(DWORD& cnt) const
	{
		static s_vertex verts[] =
		{
			s_vertex(s_vector3(-1.f, -1.f, -1.f)),
			s_vertex(s_vector3(1.f, -1.f, -1.f)),
			s_vertex(s_vector3(-1.f, 1.f, -1.f)),
			s_vertex(s_vector3(1.f, 1.f, -1.f)),
			s_vertex(s_vector3(-1.f, -1.f, 1.f)),
			s_vertex(s_vector3(1.f, -1.f, 1.f)),
			s_vertex(s_vector3(-1.f, 1.f, 1.f)),
			s_vertex(s_vector3(1.f, 1.f, 1.f)),
			s_vertex(s_vector3(-1.f, -1.f, -1.f)),
			s_vertex(s_vector3(1.f, -1.f, -1.f)),

			s_vertex(s_vector3(-1.f, -1.f, 1.f)),
			s_vertex(s_vector3(1.f, -1.f, 1.f)),

			s_vertex(s_vector3(-1.f, 1.f, -1.f)),
			s_vertex(s_vector3(1.f, 1.f, -1.f)),
			s_vertex(s_vector3(-1.f, 1.f, 1.f)),
			s_vertex(s_vector3(1.f, 1.f, 1.f)),
			s_vertex(s_vector3(-1.f, -1.f, -1.f)),
			s_vertex(s_vector3(-1.f, -1.f, 1.f)),
			s_vertex(s_vector3(-1.f, 1.f, -1.f)),
			s_vertex(s_vector3(-1.f, 1.f, 1.f)),
			s_vertex(s_vector3(1.f, -1.f, -1.f)),
			s_vertex(s_vector3(1.f, -1.f, 1.f)),
			s_vertex(s_vector3(1.f, 1.f, -1.f)),
			s_vertex(s_vector3(1.f, 1.f, 1.f)),
		};
		cnt = sizeof(verts) / sizeof(verts[0]);
		return verts;
	}
	const t_index* s_cube::inds(DWORD& cnt) const
	{
		static const t_index inds[] =
		{
			1, 0, 2, 1, 2, 3, //далека грань
			4, 5, 6, 5, 7, 6, //ближня грань
			8, 9, 10, 9, 11, 10, //верхня грань
			14, 13, 12, 14, 15, 13,//нижня грань
			16, 17, 19, 16, 19, 18,//ліва грань
			21, 20, 23, 20, 22, 23,//права грань
		};
		cnt = sizeof(inds) / sizeof(inds[0]);
		return inds;
	}
}; // namespace figures
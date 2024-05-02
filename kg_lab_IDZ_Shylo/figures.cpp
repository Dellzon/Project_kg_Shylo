#include "stdafx.h"
#include "kg_lab.h"
namespace figures
{
	const s_vertex* s_my_figure::verts(DWORD& cnt) const
	{
		static s_vertex verts[] =
		{
			// координати вершин
			s_vector3(-0.525731f, 0.0f, 0.850651f),
			s_vector3(0.525731f, 0.0f, 0.850651f),
			s_vector3(-0.525731f, 0.0f, -0.850651f),
			s_vector3(0.525731f, 0.0f, -0.850651f),
			s_vector3(0.0f, 0.850651f, 0.525731f),
			s_vector3(0.0f, 0.850651f, -0.525731f),
			s_vector3(0.0f, -0.850651f, 0.525731f),
			s_vector3(0.0f, -0.850651f, -0.525731f),
			s_vector3(0.850651f, 0.525731f, 0.0f),
			s_vector3(-0.850651f, 0.525731f, 0.0f),
			s_vector3(0.850651f, -0.525731f, 0.0f),
			s_vector3(-0.850651f, -0.525731f, 0.0f),
			s_vector3(0.525731f, 0.0f, 0.850651f),
			s_vector3(-0.525731f, 0.0f, 0.850651f),
			s_vector3(0.0f, 0.850651f, 0.525731f),
			s_vector3(0.0f, 0.850651f, -0.525731f),
			s_vector3(0.0f, -0.850651f, 0.525731f),
			s_vector3(0.0f, -0.850651f, -0.525731f),
			s_vector3(0.525731f, 0.0f, -0.850651f),
			s_vector3(-0.525731f, 0.0f, -0.850651f)

		};
		cnt = sizeof(verts) / sizeof(verts[0]);
		return verts;
	}
	const t_index* s_my_figure::inds(DWORD& cnt) const
	{
		static const t_index inds[] =
		{
			0, 1, 4,
			0, 4, 9,
			9, 4, 5,
			4, 8, 5,
			4, 1, 8,
			8, 1, 10,
			8, 10, 3,
			5, 8, 3,
			5, 3, 2,
			2, 3, 7,
			7, 3, 10,
			7, 10, 6,
			7, 6, 11,
			11, 6, 0,
			0, 6, 1,
			6, 10, 1,
			9, 11, 0,
			9, 2, 11,
			9, 5, 2,
			7, 11, 2
		};
		cnt = sizeof(inds) / sizeof(inds[0]);
		return inds;
	}
}; // namespace figures
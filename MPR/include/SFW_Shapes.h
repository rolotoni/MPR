// ---------------------------------------------------------------------------
// Project Name		:	Simple Framework
// File Name		:	SFW_Shapes.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2009/09/29
// Purpose			:	Collection of simple objects
// ---------------------------------------------------------------------------

#ifndef SFW_SHAPES_H
#define SFW_SHAPES_H

// ---------------------------------------------------------------------------
// includes

#include "SFW.h"

// ---------------------------------------------------------------------------

namespace SFW
{

// ---------------------------------------------------------------------------

class Shape
{
public:
	enum
	{
		TYPE_PLANE = 0, 
		TYPE_CUBE, 
		TYPE_CONE, 
		TYPE_CYLINDER, 
		TYPE_SPHERE, 
		TYPE_TORUS, 

		TYPE_NUM, 
	};

	// ---------------------------------------------------------------------------
	// simple vertex structure

	struct Vtx
	{
		Vec3	pos;
		Vec3	nrm;
		Vec4	clr;
		Vec3	tex;
		
		// tangent and binormal
		Vec3	tan;
		Vec3	bin;
	};

	// ---------------------------------------------------------------------------
	// simple triangle structure. It contains the 3 indices to the vertex list.

	struct Tri
	{
		union
		{
			struct
			{
				u32	p0, p1, p2;
			};
			u32	v[3];
		};
	};

	// ---------------------------------------------------------------------------

	static void	Init			(u32 subDiv = 16);
	static void	Free			();
	
	static void	Draw			(u32 type);
	static void	DrawNormal		(u32 type);
	static void	DrawWireFrame	(u32 type);

	// get the pointer to the vertex list and how many of them
	static Vtx*	VtxList			(u32 type);
	static u32	VtxNum			(u32 type);
	
	// get the pointer to the index list and how many of them
	// * the indices to pass to glDrawElements to render with triangle strip
	static u32*	IdxList			(u32 type);
	static u32	IdxNum			(u32 type);

	// get the pointer to the triangle list and how many of them
	static Tri*	TriList			(u32 type);
	static u32	TriNum			(u32 type);
};

// ---------------------------------------------------------------------------

} // namespace SFW

// ---------------------------------------------------------------------------

#endif // SFW_H



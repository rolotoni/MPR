// ---------------------------------------------------------------------------
// File Name		:	phong.vs
// Author			:	Jesse Harrison
// Creation Date	:	2/6/12
// Purpose			:	phong fragment shader
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// varyings

varying vec3 normal;
varying vec3 pos;
// ---------------------------------------------------------------------------

void main()
{
	// calculate the position in projection space
	gl_Position		=	ftransform();
	
	// calculate the normal in camera space
	normal			=	gl_NormalMatrix * gl_Normal;
	
	pos = (gl_ModelViewMatrix * gl_Vertex).xyz;

	// pass along the vertex color unmodified
	gl_FrontColor	=	gl_Color;
	
}


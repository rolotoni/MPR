// ---------------------------------------------------------------------------
// File Name		:	phong.fs
// Author			:	Jesse Harrison
// Creation Date	:	2/6/12
// Purpose			:	phong fragment shader
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// uniforms
uniform vec3 light_pos;
uniform vec3 light_dir;

// ---------------------------------------------------------------------------
// varyings

varying vec3	normal;
varying vec3    pos;

// ---------------------------------------------------------------------------

vec4 Gambient = vec4(0.2,0.2,0.2,1);
vec4 Kambient = vec4(0.2);
vec4 Kdiffuse = vec4(0.8,0.8,0.8,1);
vec3 d_att    = vec3(1.0,0.1,0.0);


void main()
{
    normal = normalize(normal);

	vec3 L = normalize(light_pos - pos);

	vec4 Diffuse  = Kambient  * gl_Color + Kdiffuse * gl_Color * max(dot(normal,L), 0.0);
      
	gl_FragColor = Diffuse;
}

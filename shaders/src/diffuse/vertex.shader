$input a_position, a_texcoord0, a_normal
$output v_texcoord0, v_normal

#include "../common.shader"

uniform vec4 u_tiling_offset;

void main() 
{
	v_texcoord0 = a_texcoord0 * u_tiling_offset.xy + u_tiling_offset.zw;
	
	v_normal = mul(u_model[0], vec4(a_normal, 0.0)).xyz;

	v_normal = normalize(v_normal);

	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
}

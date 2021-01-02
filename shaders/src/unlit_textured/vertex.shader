$input a_position, a_texcoord0
$output v_texcoord0

#include "../common.shader"

uniform vec4 u_tiling_offset;

void main() 
{
	v_texcoord0 = a_texcoord0 * u_tiling_offset.xy + u_tiling_offset.zw;
	
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
}

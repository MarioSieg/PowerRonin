$input a_position
$output v_texcoord0

#include "../../common.shader"

void main() {
	v_texcoord0 = a_position;
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
}

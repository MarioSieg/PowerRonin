$input v_texcoord0, v_normal

#include "../common.shader"

SAMPLER2D(s_texColor,  0);

void main() {
	gl_FragColor = texture2D(s_texColor, v_texcoord0);
}

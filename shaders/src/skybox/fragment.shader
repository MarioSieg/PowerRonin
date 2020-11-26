$input v_texcoord0

#include "../../common.shader"

SAMPLERCUBE(s_tex_cube, 0);

void main() {
	gl_FragColor = textureCube(s_tex_cube, v_texcoord0);
}

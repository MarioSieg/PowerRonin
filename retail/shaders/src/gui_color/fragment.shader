$input v_color0, v_texcoord0

#include "../common.shader"

SAMPLER2D(s_tex, 0);

void main() 
{
	vec4 texel = texture2D(s_tex, v_texcoord0);
	
	gl_FragColor = texel * v_color0; 

	gl_FragColor.rgb = pow(gl_FragColor.rgb, vec3_splat(2.2));
}

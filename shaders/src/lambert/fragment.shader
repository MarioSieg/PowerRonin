$input v_texcoord0, v_normal

#include "../../common.shader"

SAMPLER2D(s_tex_color,  0);
uniform vec4 u_color;
uniform vec4 u_light_dir;

void main() {
	/*
	float light_intensity = saturate(dot(v_normal, u_light_dir.xyz));
	gl_FragColor = texture2D(s_tex_color, v_texcoord0) * u_color;
	gl_FragColor = saturate(gl_FragColor * light_intensity);
	*/

	float light_intensity = saturate(dot(v_normal, u_light_dir.xyz));
	gl_FragColor = vec4(0.3, 0.3, 0.3, 0.3);
	gl_FragColor += saturate(u_color * light_intensity);
}

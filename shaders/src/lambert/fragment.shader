$input v_texcoord0, v_normal

#include "../../common.shader"

SAMPLER2D(s_tex_color,  0);
uniform vec4 u_mat_color;
uniform vec4 u_ambient_color;
uniform vec4 u_light_dir;
uniform vec4 u_light_color;

void main() {
	vec3 ambient = u_light_color.rgb * u_ambient_color.rgb;
	float light_intensity = saturate(dot(v_normal, u_light_dir.xyz));
	vec3 diffuse = u_light_color.rgb * saturate(u_mat_color.rgb * light_intensity);
	gl_FragColor = texture2D(s_tex_color, v_texcoord0) * vec4(ambient + diffuse, 1.0);
}

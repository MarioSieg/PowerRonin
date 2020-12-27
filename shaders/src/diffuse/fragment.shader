$input v_texcoord0, v_normal

#include "../common.shader"

SAMPLER2D(s_tex_color,  0);

uniform vec4 u_ambient_color;
uniform vec4 u_light_dir;
uniform vec4 u_light_color;

void main() 
{
	float light_intensity = saturate(dot(v_normal, u_light_dir.xyz));

	vec3 ambient = u_ambient_color.rgb;

	vec3 diffuse = u_light_color.rgb * light_intensity;

	vec3 albedo = ambient + diffuse;
	
	gl_FragColor = vec4(albedo, 1.0) * texture2D(s_tex_color, v_texcoord0);
}

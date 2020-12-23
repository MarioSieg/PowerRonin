$input v_texcoord0, v_normal, v_tangent, v_bitangent

// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../../common.shader"

SAMPLER2D(s_tex_color,  0);
SAMPLER2D(s_normal_map, 1);
uniform vec4 u_ambient_color;
uniform vec4 u_light_dir;
uniform vec4 u_light_color;

void main() {
	vec3 normal_map = texture2D(s_normal_map, v_texcoord0).xyz;
	normal_map = (normal_map * 2.0) - 1.0;
	vec3 normal = (normal_map.x * v_tangent) + (normal_map.y * v_bitangent) + (normal_map.z * v_normal);
	float light_intensity = saturate(dot(normal, u_light_dir.xyz));
	vec3 ambient = u_ambient_color.rgb;
	vec3 diffuse = u_light_color.rgb * light_intensity;
	vec3 albedo = ambient + diffuse;
	gl_FragColor = vec4(albedo, 1.0) * texture2D(s_tex_color, v_texcoord0);
}

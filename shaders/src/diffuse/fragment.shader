$input v_texcoord0, v_normal

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
uniform vec4 u_ambient_color;
uniform vec4 u_light_dir;
uniform vec4 u_light_color;

void main() {
	float light_intensity = saturate(dot(v_normal, u_light_dir.xyz));
	vec3 ambient = u_ambient_color.rgb;
	vec3 diffuse = u_light_color.rgb * light_intensity;
	vec3 albedo = ambient + diffuse;
	gl_FragColor = vec4(albedo, 1.0) * texture2D(s_tex_color, v_texcoord0);
}

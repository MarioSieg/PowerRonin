$input a_position, a_texcoord0, a_normal, a_tangent
$output v_texcoord0, v_normal, v_tangent, v_bitangent

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

void main() {
	v_texcoord0 = a_texcoord0;
	vec3 normal = a_normal * 2.0 - 1.0;
	vec3 tangent = a_tangent * 2.0 - 1.0;
	v_normal = normalize(mul(u_model[0], vec4(normal, 0.0)).xyz);
	v_tangent = normalize(mul(u_model[0], vec4(tangent, 0.0)).xyz);
	v_bitangent = cross(v_normal, v_tangent);
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
}

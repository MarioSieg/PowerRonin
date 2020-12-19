$input a_position, a_texcoord0, a_color0
$output v_color0, v_texcoord0

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
	vec2 pos = 2.0*a_position.xy*u_viewTexel.xy;
	gl_Position = vec4(pos.x - 1.0, 1.0 - pos.y, 0.0, 1.0);
	v_texcoord0 = a_texcoord0;
	v_color0    = a_color0;
}

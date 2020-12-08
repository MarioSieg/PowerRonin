$input v_color0, v_texcoord0

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

SAMPLER2D(s_tex, 0);

void main() {
	vec4 texel = texture2D(s_tex, v_texcoord0);
	gl_FragColor = texel * v_color0; 
	gl_FragColor.rgb = pow(gl_FragColor.rgb, vec3_splat(2.2));
}

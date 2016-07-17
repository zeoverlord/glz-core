// Copyright 2013 Peter Wallström
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and limitations under the License.

// while it is not required i like to request a few things
// 1. please do share any meaningfull/usefull changes/additions/fixes you make with me so that i could include it in any future version
// 2. likewise do share any ideas for improvements
// 3. If you make something comersiol or at least something you release publicly that relies on this code then i would like to know and maybe use in my CV
// 4. Please do include me in your credits

// glz shader toolkit - Warning does not produce actual shade
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#include "..\utilities\type.h"

namespace GLZ
{
	
	// basic passtrough program uses no transformation at all
	std::string const passtrough_vertex_legacy = {

		"#version 120\r\n"
		""
		"attribute vec3 Position;"
		"attribute vec2 TexCoord;"
		"varying vec4 tc;"
		"void main() {"
		"	gl_Position = vec4(Position.xyz, 1.0);"
		"	tc = vec4(TexCoord.xy, 0.0, 1.0);"
		"}"
		"" };

	std::string const passtrough_fragment_legacy = {
		"#version 120\r\n"
		""
		"varying vec4 tc;"
		"uniform sampler2D texunit0;"
		"void main() {"
		"vec4 base = texture2D(texunit0, tc.xy);"
		"gl_FragColor = base;"
		"}"
		"" };


	std::string const basic_vertex_legacy = {

		"#version 120\r\n"
		""
		"attribute vec3 Position;"
		"attribute vec2 TexCoord;"
		"uniform  mat4 projMat;"
		"varying vec4 tc;"
		"void main() {"
		"vec4 pos=vec4(Position.xyz,1.0);"
		"gl_Position = projMat*pos;"
		"	tc = vec4(TexCoord.xy, 0.0, 1.0);"
		"}"
		"" };

	std::string const basic_fragment_legacy = {
		"#version 120\r\n"
		""
		"varying vec4 tc;"
		"uniform  vec4 color;"
		"uniform sampler2D texunit0;"
		"void main() {"
		"vec4 base = texture2D(texunit0, tc.xy);"
		"gl_FragColor = base*color;"
		"}"
		"" };

	std::string const colortint_vertex_legacy = {

		"#version 120\r\n"
		""
		"attribute vec3 Position;"
		"uniform  mat4 projMat;"
		"void main() {"
		"vec4 pos=vec4(Position.xyz,1.0);"
		"gl_Position = projMat*pos;"
		"}"
		"" };

	std::string const colortint_fragment_legacy = {
		"#version 120\r\n"
		""
		"uniform vec4 color;"
		"uniform sampler2D texunit0;"
		"void main() {"
		"gl_FragColor = color;"
		"}"
		"" };


	std::string const tilemap_vertex_legacy = {
		"#version 120\r\n"
		""
		"attribute vec3 Position;"
		"attribute vec2 TexCoord;"
		"attribute vec3 Normal;"
		"uniform  mat4 projMat;"
		"varying vec4 txcoord;"
		""
		"void main() {"
		"vec4 pos = vec4(Position.xyz, 1.0);"
		"gl_Position = projMat*pos;"
		"txcoord = vec4(TexCoord.xy, 0.0, 1.0);"
		""
		"}"
		"" };


	std::string const tilemap_fragment_legacy = {
		"#version 120\r\n"
		""
		"varying vec4 txcoord;\r\n"
		"uniform  vec4 color;\r\n"
		""
		"uniform sampler2D texunit0; // atlas reference map\r\n"
		"uniform sampler2D texunit1; // atlas map\r\n"
		"uniform  int layer;\r\n"
		"uniform  int anim;\r\n"
		""
		"uniform int width;  // height and width of the atlas reference map\r\n"
		"uniform int height;\r\n"
		""
		"uniform int a_width;  // height and width of the atlas map\r\n"
		"uniform int a_height;\r\n"
		""
		"void main() {\r\n"
		"	float sx = 0.0;\r\n"
		"	float sy = 0.0;\r\n"
		"	float pb = 0.001;\r\n"
		"	float pbMul = 1.0 - (pb * 2);\r\n"
		""
		"	vec4 arm = texture2D(texunit0, txcoord.xy);\r\n"
		""
		"	if (layer == 0)\r\n"
		"	{\r\n"
		"		sx = floor(arm.x*256.0);\r\n"
		"		sy = floor(arm.y*256.0);\r\n"
		"	}\r\n"
		""
		"	if (layer == 1)\r\n"
		"	{\r\n"
		"		sx = floor(arm.z*256.0);\r\n"
		"		sy = floor(arm.w*256.0);\r\n"
		"	}\r\n"
		""
		"	float atl = 0.0;\r\n"
		""
		"	if (layer == 2)\r\n"
		"	{"
		"		atl = floor(arm.x*256.0);\r\n"
		"		sx = mod(atl, 16.0);\r\n"
		"		sy = floor(atl / 16.0);\r\n"
		"	}\r\n"
		""
		"	if (layer == 3)\r\n"
		"	{\r\n"
		"		atl = floor(arm.y*256.0);\r\n"
		"		sx = mod(atl, 16.0);\r\n"
		"		sy = floor(atl / 16.0);\r\n"
		"	}\r\n"
		""
		"	if (layer == 4)\r\n"
		"	{\r\n"
		"		atl = floor(arm.z*256.0);\r\n"
		"		sx = mod(atl, 16.0);\r\n"
		"		sy = floor(atl / 16.0);\r\n"
		"	}\r\n"
		""
		"	if (layer == 5)\r\n"
		"	{\r\n"
		"		atl = floor(arm.w*256.0);\r\n"
		"		sx = mod(atl, 16.0);\r\n"
		"		sy = floor(atl / 16.0);\r\n"
		"	}\r\n"
		""
		"	int  animate = 0;\r\n"
		"	float extra = 0.0;\r\n"
		""
		"	//strip animation flag\r\n"
		"	if (sx>127)\r\n"
		"	{\r\n"
		"		sx -= 128;\r\n"
		"		animate = 1;\r\n"
		"	}\r\n"
		""
		"	//strip extra flag\r\n"
		"	if (sy>127)\r\n"
		"	{\r\n"
		"		sy -= 128;\r\n"
		"		extra = 1.0;\r\n"
		"	}\r\n"
		""
		"	//get animation block\r\n"
		"	float ani_b = floor(sx / 4.0);\r\n"
		"	float ani_o = mod((fract(sx / 4.0))*4.0 + anim, 4.0);\r\n"
		""
		"	if (animate == 1) sx = (ani_b*4.0) + ani_o;\r\n"
		""
		"   vec2 sprLocal;"
		""
		"	if (extra == 1)\r\n"
		"		sprLocal = vec2(fract(-txcoord.x*width), fract(txcoord.y*height));\r\n"
		"	else\r\n"
		"		sprLocal = vec2(fract(txcoord.x*width), fract(txcoord.y*height));\r\n"
		""
		"   sprLocal *= vec2(pbMul, pbMul);\r\n"
		"   sprLocal += vec2(pb, pb);\r\n"
		""
		"	sy = (a_height - 1) - sy;\r\n"
		""
		"	sprLocal /= vec2(a_width, a_height);\r\n"
		"	sprLocal.x += (1.0 / a_width)*sx;\r\n"
		"	sprLocal.y += (1.0 / a_height)*sy;\r\n"
		""
		"vec4 am = texture2D(texunit1, sprLocal.xy);\r\n"
		""
		"gl_FragColor = am*color;\r\n"
		"}"
		"" };

		std::string const tiledSprite_vertex_legacy = {

		"#version 120\r\n"
		""
		"attribute vec3 Position;"
		//	"in vec2 TexCoord;"
		"uniform mat4 projMat;"
		"uniform vec2 spritepos;"
		"uniform vec2 spritesize;"
		"uniform vec2 spriteoffset;"
		"uniform vec2 spritescale;"
		"varying vec4 tc;"
		"void main() {"
		"vec4 pos=vec4(Position.xyz,1.0);"
		"gl_Position = projMat*pos;"
		"	tc = vec4((Position.xy*spritesize.xy*spritescale.xy)+(spriteoffset.xy*spritesize.xy*spritescale.xy), 0.0, 1.0);"
		"}"
		"" };

		std::string const tiledSprite_fragment_legacy = {
		"#version 120\r\n"
		""
		"varying vec4 tc;"
		"uniform  vec4 color;\r\n"
		"uniform sampler2D texunit0;"
		"uniform vec2 spritepos;"
		"uniform vec2 spritesize;"
		"uniform vec2 spritescale;"
		"void main() {"
		"float sx = mod(tc.x, spritesize.x);\r\n"
		"float sy = mod(tc.y, spritesize.y);\r\n"
		"vec4 base = texture2D(texunit0,  vec2(sx,sy)+spritepos.xy);"
		"gl_FragColor = base*color;"
		"}"
		"" };


}
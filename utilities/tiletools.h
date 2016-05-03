// Copyright 2013 Peter Wallstr�m
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

// tile helper functions
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#pragma once

#include "type.h"
#include "..\image\tex.h"
#include "glz.h"
#include <windows.h>											// Header File For Windows
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glext.h>

namespace GLZ
{

	enum class glzTileType { DOUBLE_LAYER, QUAD_LAYER };

	class glztiles{
	public:

		int width;
		int height;
		glzTileType type;
		img_head imghdr;
		unsigned char *data;
		unsigned int tex;
		std::string img_filename;
		bool tex_changed;
		bool data_changed;

		void load(std::string const filename, glzTileType intype);

		void update_texture(void);
		void save(void);

		// helper functions to read an write data
		char get_pixel(int x, int y, int layer);
		void put_pixel(int x, int y, int layer, char value);


		void paint_pixel(int x, int y, int px, int py, bool animate, bool flip, int layer);
		void put_extra_bit(int x, int y, bool bitdata, int layer);

		bool getTilecolision(float x, float y, int layer, bool flip_y);

		~glztiles();

	};
}
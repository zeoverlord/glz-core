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

// glz texture toolkit - will load any image in the world as long as it's a small subset of the .tga format
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#include <math.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "imagePNG.h"
#include <stdio.h>
#include <windows.h>													// Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include <gl/glext.h>
#include "..\app\appbase.h"

#include "png/lodepng.h"

namespace GLZ
{


	// this function will only read the head of a tga file and report back things like size dimetions and color channels
	// it is mainly used to get the size of the data buffer you need to load this image, it is in img.imageSize for ease of use later on
	void glzReadPngHead(img_head *img, std::string filename)
	{
		//initialize or reset image info
		img->m_width = 0;
		img->m_height = 0;
		img->m_bpp = 0;
		img->m_id = 0;
		img->m_type = 0;
		img->imageSize = 0;
		img->origin = glzOrigin::TOP_LEFT;

		std::vector<unsigned char> buffer;
		std::vector<unsigned char> image;
		unsigned int w, h;

		if(lodepng::load_file(buffer, filename)) //load the image file with given filename
		{
			return;
		}

		lodepng::State state;

		unsigned error = lodepng::decode(image, w, h, state, buffer);
		img->m_bpp = lodepng_get_channels(&state.info_png.color);

		img->m_width = w;
		img->m_height = h;
		img->imageSize = img->m_width * img->m_height * img->m_bpp;
		return;
	}


	// this function on the oter hand will load the entire tga into the data buffer

	void glzLoadPng(img_head *img, std::string filename, unsigned char *data)
	{
		unsigned int w, h;

		std::vector<unsigned char> image;
		unsigned error = lodepng::decode(image, w, h, filename);
		int i = 0;
		for(unsigned char value : image)
		{
			data[i] = value;
			++i;
		}


		img->m_type = GL_RGB;
		if(img->m_bpp == 4)
		{
			img->m_type = GL_RGBA;
		}

		return;
	}




	void glzSavePng(std::string filename, int x, int y, glzTexCompression type, unsigned int tex_type, unsigned char *in_data)
	{
		bool has_alpha = false;
		if(tex_type == GL_RGBA)
		{
			has_alpha = true;
		}
		if(tex_type == GL_RGB)
		{
			has_alpha = false;
		}

		// get the image data
		long imageSize = x * y * 3;
		if(has_alpha)
		{
			imageSize = x * y * 4;
		}
		unsigned char *data = new unsigned char[imageSize];
		unsigned char cdata[4];  //new space for an yline


		delete(data);

	}

}
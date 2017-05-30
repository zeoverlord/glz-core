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

#include <png.h>

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
		img->origin = glzOrigin::BOTTOM_LEFT;

		unsigned char header[8];    // 8 is the maximum size that can be checked

		FILE *fp = fopen(filename.c_str(), "rb");

		png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if(!png)
		{
			return;
		}

		png_infop info = png_create_info_struct(png);
		if(!info)
		{
			png_destroy_write_struct(&png, &info);
			return;
		}

		if(setjmp(png_jmpbuf(png)))
		{
			png_destroy_write_struct(&png, &info);
			return;
		}

		png_init_io(png, fp);

		png_read_info(png, info);

		img->m_width = png_get_image_width(png, info);
		img->m_height = png_get_image_height(png, info);
		if(png_get_color_type(png, info) == PNG_COLOR_TYPE_RGB)
		{
			img->m_bpp = 3;
		}

		if(png_get_color_type(png, info) != PNG_COLOR_TYPE_RGBA)
		{
			img->m_bpp = 4;
		}

		img->imageSize = img->m_width * img->m_height * img->m_bpp;

		fclose(fp);
		return;
	}


	// this function on the oter hand will load the entire tga into the data buffer

	void glzLoadPng(img_head *img, std::string filename, unsigned char *data)
	{
		int x, y;
		png_infop info_ptr;
		png_bytep * row_pointers;

		unsigned char header[8];    // 8 is the maximum size that can be checked

		/* open file and test for it being a png */
		FILE *fp = fopen(filename.c_str(), "rb");
		if(!fp)
		{
			return;
		}
		fread(header, 1, 8, fp);
		if(!png_check_sig(header, 8))
		{
			return;
		}


		/* initialize stuff */
		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

		if(!png_ptr)
		{
			return;
		}

		info_ptr = png_create_info_struct(png_ptr);
		if(!info_ptr)
		{
			return;
		}

		if(setjmp(png_jmpbuf(png_ptr)))
		{
			return;
		}

		png_init_io(png_ptr, fp);
		png_set_sig_bytes(png_ptr, 8);

		png_read_info(png_ptr, info_ptr);

		img->m_width = png_get_image_width(png_ptr, info_ptr);
		img->m_height = png_get_image_height(png_ptr, info_ptr);
		png_read_update_info(png_ptr, info_ptr);


		/* read file */
		if(setjmp(png_jmpbuf(png_ptr)))
		{
			return;
		}

		row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * img->m_height);
		for(y = 0; y < img->m_height; y++)
		{
			row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));
		}

		png_read_image(png_ptr, row_pointers);

		fclose(fp);

		if(png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
		{
			img->m_bpp = 3;
		}

		if(png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
		{
			img->m_bpp = 4;
		}

		for(y = 0; y < img->m_height; y++)
		{
			png_byte* row = row_pointers[y];
			for(x = 0; x < img->m_width * img->m_bpp; x++)
			{
				data[y * img->m_height + x] = row[x];
			}
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
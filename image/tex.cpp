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
#include "tex.h"
#include "tga.h"
#include <stdio.h>
#include <windows.h>													// Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include <gl/glext.h>
#include "..\app\appbase.h"
#include "..\utilities\filetype.h"

namespace GLZ
{

	static bool isinited_tex;

	unsigned int filter_max;
	unsigned int filter_min;
	unsigned int filter_wrap;
	unsigned int filter_mip;
	int filter_ansio;

	static PFNGLGENERATEMIPMAPPROC glGenerateMipmap;


	void ini_tex(void)
	{
		glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");

		isinited_tex = true;
	}

	// no need to be concerned about this one except if you want to add more filtering modes, then just add a new define and do the filtering settings here
	// later i might end up changing this to be a bit more thourough with both wrapping and filtering, but i will probably not need to break any code you write that uses this
	void chooseFilter(glzTexFilter filter)
	{
		filter_mip = 0;
		filter_ansio = 0;

		switch(filter)
		{
			case glzTexFilter::NONE:
				filter_max = GL_NEAREST;
				filter_min = GL_NEAREST;
				filter_wrap = GL_REPEAT;
				break;

			case glzTexFilter::NEAREST:
				filter_max = GL_NEAREST;
				filter_min = GL_NEAREST;
				filter_wrap = GL_REPEAT;
				break;

			case glzTexFilter::LINEAR:
				filter_max = GL_LINEAR;
				filter_min = GL_LINEAR;
				filter_wrap = GL_REPEAT;
				break;

			case glzTexFilter::BILINEAR:
				filter_max = GL_LINEAR;
				filter_min = GL_LINEAR_MIPMAP_NEAREST;
				filter_wrap = GL_REPEAT;
				filter_mip = 1;
				break;

			case glzTexFilter::TRILINEAR:
				filter_max = GL_LINEAR;
				filter_min = GL_LINEAR_MIPMAP_LINEAR;
				filter_wrap = GL_REPEAT;
				filter_mip = 1;
				break;

			case glzTexFilter::ANSIO_2:
				filter_max = GL_LINEAR;
				filter_min = GL_LINEAR_MIPMAP_LINEAR;
				filter_wrap = GL_REPEAT;
				filter_ansio = 2;
				filter_mip = 1;
				break;

			case glzTexFilter::ANSIO_4:
				filter_max = GL_LINEAR;
				filter_min = GL_LINEAR_MIPMAP_LINEAR;
				filter_wrap = GL_REPEAT;
				filter_ansio = 4;
				filter_mip = 1;
				break;

			case glzTexFilter::ANSIO_8:
				filter_max = GL_LINEAR;
				filter_min = GL_LINEAR_MIPMAP_LINEAR;
				filter_wrap = GL_REPEAT;
				filter_ansio = 8;
				filter_mip = 1;
				break;

			case glzTexFilter::ANSIO_16:
				filter_max = GL_LINEAR;
				filter_min = GL_LINEAR_MIPMAP_LINEAR;
				filter_wrap = GL_REPEAT;
				filter_ansio = 16;
				filter_mip = 1;
				break;

			case glzTexFilter::ANSIO_MAX:
				filter_max = GL_LINEAR;
				filter_min = GL_LINEAR_MIPMAP_LINEAR;
				filter_wrap = GL_REPEAT;
				glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &filter_ansio);
				filter_mip = 1;
				break;

		}
	}




	unsigned int glzGetDefaultTextturehandle(void)
	{
		if(!isinited_tex)
		{
			ini_tex();
		}


		GLubyte checkImage[32][32][4];
		unsigned int id;

		int i, j, c;

		for(i = 0; i < 32; i++)
		{
			for(j = 0; j < 32; j++)
			{
				c = ((((i & 0x8) == 0) ^ ((j & 0x8) == 0))) * 255;
				checkImage[i][j][0] = (GLubyte)c;
				checkImage[i][j][1] = (GLubyte)c;
				checkImage[i][j][2] = (GLubyte)c;
				checkImage[i][j][3] = (GLubyte)255;
			}
		}


		chooseFilter(glzTexFilter::LINEAR);

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, filter_wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, filter_wrap);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

		//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 2,2, GL_RGBA, GL_UNSIGNED_BYTE, data);
		return id;
	}


	// unless you either made your own texture or changed the texture data somehow you should really let glzLoadTexture do the job
	void glzMaketex(img_head *img, unsigned char data[], glzTexFilter filter)
	{
		glzAppinitialization app;
		if(!isinited_tex)
		{
			ini_tex();
		}


		unsigned int texID;
		chooseFilter(filter);

		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, filter_wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, filter_wrap);

		if(!app.data.legacyMode)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, img->m_type, img->m_width, img->m_height, 0, img->m_type, GL_UNSIGNED_BYTE, data);
			if(filter_mip)
			{
				glGenerateMipmap(GL_TEXTURE_2D);
			}
		}
		else
		{
			if(!filter_mip)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, img->m_type, img->m_width, img->m_height, 0, img->m_type, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				gluBuild2DMipmaps(GL_TEXTURE_2D, img->m_type, img->m_width, img->m_height, img->m_type, GL_UNSIGNED_BYTE, data);
			}
		}

		img->m_id = texID;

		return;

	}







	// this is pretty self explanatory, supply filename and filter type (GLZ_FILTER_ANSIO_MAX is reccomended) and it spits out a texture handle
	unsigned int glzLoadTexture(std::string filename, glzTexFilter filter)
	{
		if(!isinited_tex)
		{
			ini_tex();
		}

		img_head img;
		unsigned char *data;

		if(getFiletype(filename) == glzFileTypes::TGA)
		{
			glzReadTgaHead(&img, filename);
		}

		data = new unsigned char[img.imageSize];
		if(getFiletype(filename) == glzFileTypes::TGA)
		{
			glzLoadTga(&img, filename, data);
		}
		glzMaketex(&img, data, filter);

		delete[] data;
		data = NULL;


		return img.m_id;

	}


	// most oftenly the use will be "glzScreenShot("myfile.tga",width,height,GLZ_COMPRESSED)" but i added a few fancy things if you like to fiddle with it
	// glzScreenShotADV adds x and y offsets and lossy compression, the lossy compression basically just lowers the sensitivity on the rle segments with +- the lossy argument
	// it's especially useful if you have lots of low amplidude high frequency noice and few gradients, but it can look uggly if set to high or if it is animated, below 5 should be ok in most cases

	void glzScreenShot(std::string filename, int x, int y, glzTexCompression type)
	{
		glzScreenShotADV(filename, 0, 0, x, y, type);
	}

	void glzScreenShotADV(std::string filename, int xoffset, int yoffset, int x, int y, glzTexCompression type)
	{
		// get the image data
		long const imageSize = x * y * 3;
		unsigned char *data = new unsigned char[imageSize];
		unsigned char cdata[4];  //new space for an yline

		glReadPixels(xoffset, yoffset, x, y, GL_RGB, GL_UNSIGNED_BYTE, data);

		if(getFiletype(filename) == glzFileTypes::TGA)
		{
			glzSaveTGA(filename, x, y, type, GL_RGB, data);
		}

		delete[] data;
		data = NULL;
	}

}
// things i like to add in the future

// openEXR support, both loading and saving
// More explicit saving, much like how the texture loading is split in many functions i would like to do the same with screenshots
// various texture loading styles, like texture arrays and cubemaps
// tools that will help with various forms of megatexturing
// a way to kill textures
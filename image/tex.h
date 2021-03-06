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

// glz texture toolkit - will load any image in the world as long as it's a small subset of the .tga format
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#pragma once

#include "..\utilities\type.h"
#include "textureData.h"

namespace GLZ
{



	//type signifies the type of data to choose from, if set at GLZ_AUTO it chooses the default settings



	//loading

	unsigned int glzGetDefaultTextturehandle(void);
	// segmented loading, for if you want to load a texture into the cpu
	void glzMaketex(img_head *img, unsigned char data[], glzTexFilter filter);
	unsigned int glzLoadTexture(std::string filename, glzTexFilter filter);  // type is here which image type (same as in openGL) and filter is the texture filtering


	void glzReadImageHead(img_head *img, std::string filename);
	void glzLoadImage(img_head *img, std::string filename, unsigned char *data);



	// saving

	void glzScreenShot(std::string filename, int x, int y, glzTexCompression type);  // auto saves a compressed file
	void glzScreenShotADV(std::string filename, int xoffset, int yoffset, int x, int y, glzTexCompression type);

	void glzSaveImage(std::string filename, int x, int y, glzTexCompression type, unsigned int tex_type, unsigned char *in_data);
}

/*
// future stuff

* split texture loading and texture creation into files
* multiple save formats
* Multiple load formats bmp, openEXR, GTF(my own format) and maybe others
* better image preprocessing (for cubemaps and so on)
* subtexture loading, using chunks for megatextures
* procedural texture generation, also megatexture capable
* some FBO management
* texture array manager - load textures as a large 4k texture array so that you only have to tell the shader where that texture is, so basically a bind once use forever texture
* dynamic texture manager for the above, defrags a texture array to make more space.

*/
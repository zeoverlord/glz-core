// Copyright 2018 Peter Wallstr�m
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

// glz Object - general purpose objects for rendering
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#pragma once

#include <windows.h>
#include <memory>
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include <gl/glext.h>
#include <vector>
#include "..\utilities\vectormath.h"
#include "..\utilities\node3.h"

namespace GLZ
{

	class glzObject
	{
		glzObject() {}
		~glzObject()
		{
			deinitialize();
		}
		virtual bool initialize();
		virtual void deinitialize(void);
		virtual void onUpdate(float seconds);
		void update(float seconds);
		virtual void render(void);

		virtual std::string getType () const;

		std::shared_ptr<node3> mNodeParent;
		node3 mNodeLocal;
	};
}







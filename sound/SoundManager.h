// Copyright 2017 Peter Wallström
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

// glz Sound manager
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#pragma once


#include "..\utilities\type.h"
#include "..\utilities\glz.h"
#include "..\utilities\resourcemanager.h"
#include "..\utilities\vectormath.h"

#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <memory>
#include <al/al.h>
#include <al/alc.h>


namespace GLZ
{
	class glzSoundManager
	{
	public:
		glzSoundManager();
		~glzSoundManager();

	private:
		struct BufferData
		{
			ALint mALBuffer;
			std::string mResourceName;
			std::string mFileName;
			ALuint mSamplerate;
		};

		bool mIsInitialized;
		bool mCanPlaySound;

		std::vector<BufferData> mBuffers;


	public:

		void initialize();
		int LoadWAV(std::string inFilename, std::string inResourceName);

	};
}
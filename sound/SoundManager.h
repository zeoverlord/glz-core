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
	bool processError();

	class SoundResource
	{
	public:

		bool mIsInitialized;
		bool mCanPlaySound;
		unsigned int idcounter;


		SoundResource() :
			mIsInitialized(false),
			mCanPlaySound(false)
		{
		}

		~SoundResource()
		{
		}

		unsigned int getNewId(void)
		{
			idcounter++;
			return idcounter;
		}

	};


	class SoundSource
	{
	public:

		ALuint mSourceHandle;

		SoundSource() :
			mSourceHandle(0)
		{
		}

		~SoundSource()
		{
			alDeleteSources(1, &mSourceHandle);
		}

		void init();

		void setPitch(float inPitch)
		{
			alGetError();
			alSourcef(mSourceHandle, AL_PITCH, inPitch / 440.0);
			processError();
		}

		void setGain(float inGain)
		{
			alGetError();
			alSourcef(mSourceHandle, AL_GAIN, inGain);
			processError();
		}

		void setPosition(vert3 inPosition)
		{
			alGetError();
			alSource3f(mSourceHandle, AL_POSITION, inPosition.x, inPosition.y, inPosition.z);
			processError();
		}

		void setPosition(vec3 inVelocity)
		{
			alGetError();
			alSource3f(mSourceHandle, AL_VELOCITY, inVelocity.x, inVelocity.y, inVelocity.z);
			processError();
		}

		void setLooping(ALboolean inLooping)
		{
			alGetError();
			alSourcei(mSourceHandle, AL_LOOPING, inLooping);
			processError();
		}

	};

	class glzSoundManager
	{
	public:
		glzSoundManager();
		~glzSoundManager();

	public:

		struct SoundBufferData
		{
			ALint mALBuffer;
			std::string mResourceName;
			std::string mFileName;
			ALuint mSamplerate;
			int mUid;
		};

	public:

		ALboolean initOpenAL();
		void initialize();
		int LoadWAV(std::string inFilename, std::string inResourceName);
		void setListnerPossition(vert3 inPosition);
		void setListnerVelocity(vec3 inVelocity);
		void setListnerOrientation(vec3 inOrientation, vec3 inUp);
		void setListner(node3 inNode);

		void playSound(SoundSource *inSoundsource, std::string inResourceName);
	};
}
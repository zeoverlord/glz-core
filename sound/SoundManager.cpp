// Copyright 2016 Peter Wallström
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

// glz viewport
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#include "SoundManager.h"


namespace GLZ
{

	/**
	* Default constructor
	*/
	glzSoundManager::glzSoundManager() :
		mIsInitialized(false),
		mCanPlaySound(false)
	{
		mBuffers.clear();
	}

	/**
	* Destructor
	*/
	glzSoundManager::~glzSoundManager()
	{

	}

	void glzSoundManager::initialize()
	{
		ALCdevice *device;
		ALCcontext *context;

		device = alcOpenDevice(NULL);
		if(!device)
		{
			return;
		}

		context = alcCreateContext(device, NULL);
		if(!context)
		{
			return;
		}

		mIsInitialized = true;
		mCanPlaySound = true;

		alGetError();

	}

	int glzSoundManager::LoadWAV(std::string inFilename, std::string inResourceName)
	{
		FILE *fp = NULL;
		fp = fopen(inFilename.c_str(), "rb");

		char type[4];
		DWORD size, chunkSize;
		short formatType, channels;
		DWORD sampleRate, avgBytesPerSec;
		short bytesPerSample, BitsPerSample;
		DWORD dataSize;

		fread(type, sizeof(char), 4, fp);
		if(type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')
		{
			return -1;
		}

		fread(&size, sizeof(DWORD), 1, fp);

		fread(type, sizeof(char), 4, fp);
		if(type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
		{
			return -1;
		}

		fread(type, sizeof(char), 4, fp);
		if(type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
		{
			return -1;
		}

		fread(&chunkSize, sizeof(DWORD), 1, fp);
		fread(&formatType, sizeof(short), 1, fp);
		fread(&channels, sizeof(short), 1, fp);
		fread(&sampleRate, sizeof(DWORD), 1, fp);
		fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
		fread(&bytesPerSample, sizeof(short), 1, fp);
		fread(&BitsPerSample, sizeof(short), 1, fp);

		fread(type, sizeof(char), 4, fp);
		if(type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')
		{
			return -1;
		}

		fread(&dataSize, sizeof(DWORD), 1, fp);

		unsigned char* buf = new unsigned char(dataSize);
		fread(buf, sizeof(BYTE), dataSize, fp);


		ALuint buffer;
		ALenum format;

		alGenBuffers(1, &buffer);

		if(BitsPerSample == 8)
		{
			if(channels == 1)
			{
				format = AL_FORMAT_MONO8;
			}
			else if(channels == 2)
			{
				format = AL_FORMAT_STEREO8;
			}
		}
		else if(BitsPerSample == 16)
		{
			if(channels == 1)
			{
				format = AL_FORMAT_MONO16;
			}
			else if(channels == 2)
			{
				format = AL_FORMAT_STEREO16;
			}
		}
		alBufferData(buffer, format, buf, dataSize, sampleRate);

		mBuffers.push_back(BufferData({ buffer, inResourceName, inFilename, sampleRate }));

		delete(buf);

		return buffer;
	}

}
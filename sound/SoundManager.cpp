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

// glz sound manager
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#include "SoundManager.h"
#include <assert.h>
#include "aldlist.h"

#pragma comment( lib, "OpenAL32.lib" )							// Search For OpenGL32.lib While Linking



namespace GLZ
{

	static SoundResource sri;

	static std::vector<glzSoundManager::SoundBufferData> mBuffers;


	bool processError()
	{
		ALCenum error;

		error = alGetError();
		switch(error)
		{
			case AL_NO_ERROR:
				return false;
				break;
			case AL_INVALID_NAME:
				return true;
				break;
			case AL_ILLEGAL_ENUM:
				return true;
				break;
			case AL_INVALID_VALUE:
				return true;
				break;
			case AL_ILLEGAL_COMMAND:
				return true;
				break;
			case AL_OUT_OF_MEMORY:
				return true;
				break;

			default:
				return false;
				break;

		}
	}


	void SoundSource::init()
	{
		alGetError();
		mSourceHandle = 0;
		alGenSources(1, &mSourceHandle);
		processError();

		alSourcef(mSourceHandle, AL_PITCH, 1);
		alSourcef(mSourceHandle, AL_GAIN, 1);
		alSource3f(mSourceHandle, AL_POSITION, 0, 0, 0);
		alSource3f(mSourceHandle, AL_VELOCITY, 0, 0, 0);
		alSourcei(mSourceHandle, AL_LOOPING, AL_FALSE);
		processError();
	}

	/**
	* Default constructor
	*/
	glzSoundManager::glzSoundManager()
	{
		if(sri.mIsInitialized == false)
		{
			mBuffers.clear();
		}
	}

	/**
	* Destructor
	*/
	glzSoundManager::~glzSoundManager()
	{

	}


	ALboolean glzSoundManager::initOpenAL()
	{
		ALDeviceList *pDeviceList = NULL;
		ALCcontext *pContext = NULL;
		ALCdevice *pDevice = NULL;
		ALboolean bReturn = AL_FALSE;

		pDeviceList = new ALDeviceList();
		if((pDeviceList) && (pDeviceList->GetNumDevices()))
		{
			pDevice = alcOpenDevice(pDeviceList->GetDeviceName(0));
			if(pDevice)
			{
				pContext = alcCreateContext(pDevice, NULL);
				if(pContext)
				{
					alcMakeContextCurrent(pContext);
					bReturn = AL_TRUE;
				}
				else
				{
					alcCloseDevice(pDevice);
				}
			}

			delete pDeviceList;
		}

		return bReturn;
	}


	void glzSoundManager::initialize()
	{
		if(!initOpenAL())
		{
			return;
		}

		processError();

		ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
		ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
		ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

		alListenerfv(AL_POSITION, ListenerPos);
		alListenerfv(AL_VELOCITY, ListenerVel);
		alListenerfv(AL_ORIENTATION, ListenerOri);

		sri.mIsInitialized = true;
		sri.mCanPlaySound = true;

		alGetError();

	}

	int glzSoundManager::LoadWAV(std::string inFilename, std::string inResourceName)
	{
		FILE *fp = NULL;
		fp = fopen(inFilename.c_str(), "rb");

		if(!fp)
		{
			return -1;
		}

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

		unsigned char* buf = new unsigned char[dataSize];
		fread(buf, sizeof(char), dataSize, fp);


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
		processError();
		alBufferData(buffer, format, buf, dataSize, sampleRate);

		int uid = sri.getNewId();

		mBuffers.push_back(SoundBufferData({ buffer, inResourceName, inFilename, sampleRate, uid}));

		delete[dataSize] buf;

		processError();

		return buffer;
	}


	void glzSoundManager::setListnerPossition(vert3 inPosition)
	{
		alGetError();
		ALfloat ListenerPos[] = { inPosition.x, inPosition.y, inPosition.z };
		alListenerfv(AL_POSITION, ListenerPos);
		processError();
	}

	void glzSoundManager::setListnerVelocity(vec3 inVelocity)
	{
		alGetError();
		ALfloat ListenerVel[] = { inVelocity.x, inVelocity.y, inVelocity.z };
		alListenerfv(AL_VELOCITY, ListenerVel);
		processError();
	}

	void glzSoundManager::setListnerOrientation(vec3 inOrientation, vec3 inUp)
	{
		alGetError();
		ALfloat ListenerOri[] = { inOrientation.x, inOrientation.y, inOrientation.z, inUp.x, inUp.y, inUp.z };
		alListenerfv(AL_ORIENTATION, ListenerOri);
		processError();
	}

	void glzSoundManager::setListner(node3 inNode)
	{
		alGetError();
		setListnerPossition(inNode.pos);
		setListnerVelocity(inNode.dir);

		vec3 orientation(inNode.m.m[0], inNode.m.m[1], inNode.m.m[2]);
		vec3 up(inNode.m.m[4], inNode.m.m[5], inNode.m.m[6]);

		setListnerOrientation(orientation, up);
		processError();
	}

	void glzSoundManager::playSound(SoundSource *inSoundsource, std::string inResourceName)
	{
		alGetError();
		if(sri.mCanPlaySound)
		{
			for(auto& buffer : mBuffers)
				if(buffer.mResourceName == inResourceName)
				{
					ALint source_state;

					alGetSourcei(inSoundsource->mSourceHandle, AL_SOURCE_STATE, &source_state);
					// check for errors
					if(source_state != AL_PLAYING)
					{

						alSourcei(inSoundsource->mSourceHandle, AL_BUFFER, buffer.mALBuffer);
						processError();
						alSourcePlay(inSoundsource->mSourceHandle);
						processError();
					}

				}
		}
	}
}
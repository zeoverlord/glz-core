// Copyright 2016 Peter Wallstr�m
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

// glz input - i think it's usefull
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#pragma once


#include "..\utilities\type.h"

namespace GLZ
{
	class glzInputData{

	public:
		bool keyDown[256];								// Holds TRUE / FALSE For Each Key
		bool LMdown;
		bool MMdown;
		bool RMdown;
		int Mpos_x;
		int Mpos_y;
		int Mweel;
		bool Mactive;
		bool pulsar1;
		bool pulsar2;
		bool pulsar4;
		bool pulsar8;
		bool pulsar16;
		float pulsartimer;
		int pulsarcounter;

		glzInputData();
	};



	class glzInput{

	public:
		glzInput(); // grab the global data on construction
		~glzInput(); // should return data into the global


		void updateKeys(float inSeconds);

		// pulsars - these just pulse for one frame every now and then
		bool getPulsar1(void);
		bool getPulsar2(void);
		bool getPulsar4(void);
		bool getPulsar8(void);
		bool getPulsar16(void);


		// keys
		void addKeyEvent(int key, bool keydown);
		bool getKeyState(int key);

		//mouse
		void SetMouseL(bool keydown);
		void SetMouseM(bool keydown);
		void SetMouseR(bool keydown);

		bool getMouseL(void);
		bool getMouseM(void);
		bool getMouseR(void);

		void setMouseX(int x);
		void setMouseY(int y);
		int getMouseX(void);
		int getMouseY(void);

		void setMouseWeel(int m);
		void addMouseWeel(int m);
		int getMouseWeel(void);

	};
}
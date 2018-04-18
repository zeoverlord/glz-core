// Copyright 2014 Peter Wallström
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

// common glz vector and matrix classes
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#pragma once

#include "vectormath.h"
#include "type.h"

namespace GLZ
{

	class node3  //3-Dimetional possition class
	{

	public:

		node3() : mPossition(vert3()), mDirection(vec3()), mRotation(glzQuaternion()), mRotationVelocity(glzQuaternion()), mScale(vec3(1.0, 1.0, 1.0))
		{
			update_matrix();
		}
		node3(vert3 posin, vec3 dirin, glzQuaternion rin, glzQuaternion rsin) : mPossition{ posin }, mDirection{ dirin }, mRotation{ rin }, mRotationVelocity{ rsin }, mScale(vec3(1.0, 1.0, 1.0))
		{
			update_matrix();
		}
		node3(vert3 posin) : mPossition{ posin }, mDirection(vec3()), mRotation(glzQuaternion()), mRotationVelocity(glzQuaternion()), mScale(vec3(1.0, 1.0, 1.0))
		{
			update_matrix();
		}

		node3(vert3 posin, glzQuaternion rin) : mPossition{ posin }, mDirection(vec3()), mRotation(glzQuaternion()), mRotationVelocity(glzQuaternion()), mScale(vec3(1.0, 1.0, 1.0))
		{
			update_matrix();
		}

		node3(vert3 posin, float angle, float scalein);

		void update_matrix();

		void tick(float seconds);


		/*
		turn to
		move to
		align to

		*/


	public:
		vert3 getPosition() const;
		void setPosition(vert3 inPosition);

		vec3 getDirection() const;
		void setDirection(vec3 inDirection);

		glzQuaternion getRotation() const;
		void setRotation(glzQuaternion inRotation);

		glzQuaternion getRotationVelocity() const;
		void setRotationVelocity(glzQuaternion inRotationVelocity);

		vec3 getScale() const;
		void setScale(vec3 inScale);

		glzMatrix getMatrix() const;

	private:

		vert3 mPossition;
		vec3 mDirection;
		glzQuaternion mRotation;
		glzQuaternion mRotationVelocity;
		vec3 mScale;
		glzMatrix mMatrix;

	};
}



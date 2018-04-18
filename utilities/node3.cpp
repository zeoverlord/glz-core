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



#include "node3.h"

namespace GLZ
{

	node3::node3(vert3 posin, float angle, float scalein)
	{
		mPossition = posin;
		mScale = vec3(scalein, scalein, scalein);
		mRotation.rotate(angle, 0.0, 0.0, 1.0);
		update_matrix();
	}

	void node3::update_matrix()
	{
		mMatrix.LoadIdentity();
		mMatrix.translate(mPossition);
		mMatrix.scale(mScale);
		mMatrix.loadQuanternion(mRotation);
	}

	void node3::tick(float seconds)
	{
		mPossition += mDirection * seconds;

		glzQuaternion rt;
		rt *= mRotationVelocity;
		rt *= seconds;

		mRotation *= rt;
		update_matrix();
	}

	vert3 node3::getPosition() const
	{
		return mPossition;
	}
	void node3::setPosition(vert3 inPosition)
	{
		mPossition = inPosition;
	}

	vec3 node3::getDirection() const
	{
		return mDirection;
	}
	void node3::setDirection(vec3 inDirection)
	{
		mDirection = inDirection;
	}

	glzQuaternion node3::getRotation() const
	{
		return mRotation;
	}
	void node3::setRotation(glzQuaternion inRotation)
	{
		mRotation = inRotation;
	}

	glzQuaternion node3::getRotationVelocity() const
	{
		return mRotationVelocity;
	}
	void node3::setRotationVelocity(glzQuaternion inRotationVelocity)
	{
		mRotationVelocity = inRotationVelocity;
	}

	vec3 node3::getScale() const
	{
		return mScale;
	}
	void node3::setScale(vec3 inScale)
	{
		mScale = inScale;
	}

	glzMatrix node3::getMatrix() const

	{
		return mMatrix;
	}

}
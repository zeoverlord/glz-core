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

// color class
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#include <math.h>
#include "type.h"
#include "glz.h"
#include "color.h"
namespace GLZ
{

	glzColor::glzColor(unsigned long inHex)
	{
		r = ((inHex >> 16) & 0xFF) / 255.0f;  // Extract the RR byte
		g = ((inHex >> 8) & 0xFF) / 255.0f;   // Extract the GG byte
		b = ((inHex)& 0xFF) / 255.0f;        // Extract the BB byte
	}
	
	void glzColor::recalcMaxMin()
	{
		max = 'r';
		min = 'r';
		maxval = r;
		minval = r;

		if(maxval<g) { maxval = g; max = 'g'; }
		if(maxval<b) { maxval = b; max = 'b'; }

		if(minval>g) { minval = g; min = 'g'; }
		if(minval>b) { minval = b; min = 'b'; }

		delta = maxval - minval;
		alpha = 0.5f*(2.0f * r - g - b);
		beta = (sqrt(3.0f) / 2.0f)*(g - b);
		h = 0.0f;
	}

	float glzColor::hue()
	{
		recalcMaxMin();

		if(max == min) return 0.0f;


		switch(max)
		{
		case 'a': h = ((g - b) / (delta)) / 6.0f; break;
		case 'b': h = (2.0f + (b - r) / (delta)) / 6.0f; break;
		case 'c': h = (4.0f + (r - g) / (delta)) / 6.0f; break;
		}

		if(h < 0)
			h += 1.0f;

		return h;
	}

	float glzColor::hue2()
	{
		recalcMaxMin();

		if(max == min) return 0.0f;
		h = (float)atan2(beta, alpha)*(float)PI_OVER_180_REVERSE;
		if(h < 0)
			h += 360.0f;
		return h / 360.f;
	}

	float glzColor::croma()
	{
		recalcMaxMin();
		return delta;
	}

	float glzColor::croma2()
	{
		recalcMaxMin();
		return sqrt((alpha*alpha) + (beta*beta));
	}

	float glzColor::value()
	{
		recalcMaxMin();
		return maxval;
	}

	float glzColor::lightness()
	{
		recalcMaxMin();
		return 0.5f*(maxval + minval);
	}

	float glzColor::intensity()
	{
		return (1.0f / 3.0f)*(r + g + b);
	}

	float glzColor::luma()
	{
		return (0.3f*r) + (0.59f*g) + (0.11f*b);
	}

	float glzColor::shsv()
	{
		recalcMaxMin();
		if(max == min) return 0.0f;
		return delta / maxval;
	}

	float glzColor::shsl()
	{
		recalcMaxMin();
		if(max == min) return 0.0f;

		if(lightness()>0.5f)	return delta / (2.0f - (2.0f * lightness()));
		else		return delta / (2.0f * lightness());
	}

	float glzColor::shsi()
	{
		recalcMaxMin();
		if(max == min) return 0.0f;
		return 1.0f - (minval / intensity());
	}

	unsigned long glzColor::hex()
	{
		return ((static_cast<unsigned long>(r*255.0f) & 0xff) << 16) + ((static_cast<unsigned long>(g*255.0f) & 0xff) << 8) + (static_cast<unsigned long>(b*255.0f) & 0xff);
	}

	unsigned long glzColor::hex32()
	{
		return ((static_cast<unsigned long>(r*255.0f) & 0xff) << 24) + ((static_cast<unsigned long>(g*255.0f) & 0xff) << 16) + ((static_cast<unsigned long>(b*255.0f) & 0xff) << 8)
			+ (static_cast<unsigned long>(a*255.0f) & 0xff);
	}
}
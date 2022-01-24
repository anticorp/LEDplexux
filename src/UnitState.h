#pragma once

#include <Color.h>

namespace plx
{
	namespace __
	{
		struct UNITSTATE
		{
			UNITSTATE()
				:	currIntensity(0),
					setIntensity(0) {}
			uint8_t currIntensity;
			uint8_t setIntensity;
		};
		
		struct RGBSTATE
		{
			RGBSTATE()
				:	baseColor(0,0,0, "Base Color"),
					currColor(0,0,0, "Current Color"),
					setColor(0,0,0, "Set Color") {}
			color::RGBColor baseColor;
			color::RGBColor currColor;
			color::RGBColor setColor;
		};
	}
}
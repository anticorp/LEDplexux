#pragma once
#include <Color.h>

namespace plx
{
	namespace __FX
	{
		struct FXGOFER
		{
			FXGOFER() 
			:	StateChange(false),
				currPWRstate(false),
				setPWRstate(false),
				currIntensity(0),
				setIntensity(0),
				ColorChange(false){}
			bool StateChange;
			bool currPWRstate;
			bool setPWRstate;
			uint8_t currIntensity;
			uint8_t setIntensity;
			bool ColorChange;
			color::RGBColor currColor;
			color::RGBColor setColor;
			operator bool() { return StateChange; }
		};
	}
}
#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define __Lplex__MAX__LED__SLOTS	20
#define __Lplex__MAX__BLIP__SLOTS	10


#include <LEDunit.h>
#include <ClockCache.h>
#include <Color.h>

namespace plx
{
	class PLEXUS
	{
	public:
		PLEXUS();
		~PLEXUS();
		static void RefreshAll();
		static void SetRefreshRate(size_t refreshRate);
		static bool RegisterNewUnit(LEDunit* _newUnit);
		static uint8_t RegisterBlip(LEDunit* _blipUnit);
		static bool DeRegisterBlip(uint8_t blipID);

	private:
		static const size_t StackSize = __Lplex__MAX__LED__SLOTS;
		static LEDunit* _RefreshStack[StackSize];
		static size_t LEDunitCount;

		static const size_t mBlipStackSize = __Lplex__MAX__BLIP__SLOTS;
		static LEDunit* _BlipStack[mBlipStackSize];
		static size_t mBlipsInStack;

		static uint32_t LoopCount;
		static size_t plx_RefreshStackIterator;
		static uint32_t plx_RefreshRate;
		static ClockCache RefreshClock;
		static bool SplitProcessRefresh;
	};
	extern PLEXUS LEDplexus;
}
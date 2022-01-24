#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Color.h>
#include <ClockCache.h>
#include <UnitState.h>

namespace plx
{
	namespace __FX
	{
		class BLIPFX
		{
		public:
			BLIPFX();
			virtual bool Update(ClockCache& _RefreshClock, __::UNITSTATE& _UnitState) {}
			virtual bool Update(ClockCache& _RefreshClock, __::RGBSTATE& _rgbState) {}
			virtual bool Refresh(__::UNITSTATE& _inState) {}
			virtual bool Refresh(__::RGBSTATE& _inRGBstate) {}
			bool Destroy();
			~BLIPFX();
			/* Returns the signal to Destroy the blipFX and Return to normal operations */
		protected:
			bool mDestroy;

		};

		class BLIP : public BLIPFX
		{
		public:
			BLIP();
			BLIP(uint32_t blipRiseFall, uint32_t blipHold, uint8_t blipIntensity, __::UNITSTATE& _inState);
			BLIP(uint32_t blipRiseFall, uint32_t blipHold, color::RGBColor& blipColor);
			bool Update(ClockCache& _RefreshClock, __::UNITSTATE& _UnitState);
			bool Update(ClockCache& _RefreshClock, __::RGBSTATE& _rgbState);
			bool Refresh(__::UNITSTATE& _inState);
			bool Refresh(__::RGBSTATE& _inRGBstate);
			~BLIP();


		private:
			bool FreshStart;
			bool mRise;
			bool mFall;
			bool mHold;
			ClockCache mStartTime;
			uint32_t mHoldTime;
			uint32_t mRiseFallTime;
			ClockCache timeSinceBlipStart;
			uint8_t mBaseIntensity;
			uint8_t mTargetIntensity;
			color::RGBColor mBlipColor;
			bool UniversalUpdate();

		};

		class HARDBLIP : public BLIPFX
		{
		public:
			HARDBLIP();
			HARDBLIP(uint32_t blipRiseFall, uint32_t blipHold, uint8_t blipIntensity, __::UNITSTATE& _inState);
			HARDBLIP(uint32_t blipRiseFall, uint32_t blipHold, color::RGBColor& blipColor);
			bool Update(ClockCache& _RefreshClock, __::UNITSTATE& _UnitState);
			bool Update(ClockCache& _RefreshClock, __::RGBSTATE& _rgbState);
			bool Refresh(__::UNITSTATE& _inState);
			bool Refresh(__::RGBSTATE& _inRGBstate);
			~HARDBLIP();


		private:
			bool FreshStart;
			bool mRise;
			bool mFall;
			bool mHold;
			ClockCache mStartTime;
			uint32_t mHoldTime;
			uint32_t mRiseFallTime;
			ClockCache timeSinceBlipStart;
			uint8_t mBaseIntensity;
			uint8_t mTargetIntensity;
			color::RGBColor mBlipColor;
			bool UniversalUpdate();

		};

	}

}
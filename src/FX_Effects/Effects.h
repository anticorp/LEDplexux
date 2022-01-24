#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

//#include "FXgopher.h"
#include "UnitState.h"
#include <Color.h>
#include <ClockCache.h>

namespace plx
{
	namespace __FX
	{
		class FX
		{
		public:
			FX();
			virtual bool Update(ClockCache& _RefreshClock, __::UNITSTATE& _UnitState) {}
			virtual bool Update(ClockCache& _RefreshClock, __::RGBSTATE& _rgbState) {}
			virtual bool Refresh(__::UNITSTATE& _inState) {}
			virtual bool Refresh(__::RGBSTATE& _inRGBstate) {}
			~FX();
		};
		class BLINKER : public FX
		{
		public:
			BLINKER();
			BLINKER(const size_t& _ONperiod, const size_t& _OFFperiod);
			BLINKER(const size_t& _ONperiod, const size_t& _OFFperiod, const color::RGBColor& highColor, const color::RGBColor& lowColor);
			void TurnOff();
			void TurnOn();
			void Blink(const size_t& _ONperiod, const size_t& _OFFperiod);

			void SetNewPeriods(const size_t& _ONperiod, const size_t& _OFFperiod);
			bool Update(ClockCache& _RefreshClock, __::UNITSTATE& _UnitState) override;
			bool Update(ClockCache& _RefreshClock, __::RGBSTATE& _rgbState) override;
			bool Refresh(__::RGBSTATE& _state) override;
			bool Refresh(__::UNITSTATE& _state) override;
			~BLINKER();

		private:
			bool CheckOnUpdate(ClockCache& _RefreshClock, const uint8_t& _intensity);
			size_t mON;
			size_t mOFF;
			bool m_CurrentKnownState;
			uint32_t m_MinPollTime;
			ClockCache mLastFXclock;
			bool m_Update;
			color::RGBColor mHighBlinkColor;
			color::RGBColor mLowBlinkColor;

		};

		class BICOLORSWEEP : public FX
		{
		public:
			BICOLORSWEEP();
			BICOLORSWEEP(const color::RGBColor& upColor, const color::RGBColor& downColor, uint32_t upTime, uint32_t sweepTime);
			bool Update(ClockCache& _RefreshClock, __::RGBSTATE& _rgbState) override;
			bool Refresh(__::RGBSTATE& _state) override;
			void StartFresh(const color::RGBColor& upColor, const color::RGBColor& downColor, uint32_t upTime, uint32_t sweepTime);
		private:
			int SignedIntensityPercentFactor(const int ColorChannelIntensity);
			uint8_t NewPinValue(uint8_t currentColorChannel, const int signedChangeFactor);
			bool m_HoldUp;
			bool m_HoldDown;
			bool m_SweepUp;
			bool m_SweepDown;
			bool m_FreshStart;
			color::RGBColor mUpColor;
			color::RGBColor mDownColor;
			uint32_t m_HoldTime;
			ClockCache m_HoldStart;

			uint32_t m_SweepTime;
			ClockCache m_LastFXtime;
			ClockCache m_SweepStart;
			ClockCache mSweepCycleDelta;
			int m_SweepDownRange[3];
			int m_SweepUpRange[3];
		};
	}
}
#pragma once
#include "Effects.h"
#include <ADM.h>


namespace plx
{
	namespace __FX
	{
		BLINKER::BLINKER()
		{
		}
		BLINKER::BLINKER(const size_t& ONperiod, const size_t& OFFperiod)
		{
			mON = ONperiod;
			mOFF = OFFperiod;
		}
		BLINKER::BLINKER(const size_t& ONperiod, const size_t& OFFperiod, const color::RGBColor& highColor, const color::RGBColor& lowColor)
		{
			mON = ONperiod;
			mOFF = OFFperiod;
			mLowBlinkColor = lowColor;
			mHighBlinkColor = highColor;
		}
		void BLINKER::Blink(const size_t& _ONperiod, const size_t& _OFFperiod)
		{
			mON = _ONperiod;
			mOFF = _OFFperiod;
		}
		void BLINKER::SetNewPeriods(const size_t& _ONperiod, const size_t& _OFFperiod)
		{
			mON = _ONperiod;
			mOFF = _OFFperiod;
		}
		bool BLINKER::Update(ClockCache& _RefreshClock, __::UNITSTATE& state)
		{
			return CheckOnUpdate(_RefreshClock, state.currIntensity);
		}
		bool BLINKER::Update(ClockCache& _RefreshClock, __::RGBSTATE& _state)
		{
			return CheckOnUpdate(_RefreshClock, _state.currColor.getAvg());
			return false;
		}
		bool BLINKER::Refresh(__::RGBSTATE& state)
		{
			if (state.currColor.getAvg() > 0)
			{
				state.setColor = mLowBlinkColor;	// if the RBG gets single changes, it applies change to all colors equally.
				mLastFXclock.Mark();
				return true;
			}
			else
			{
				state.setColor = mHighBlinkColor;
				mLastFXclock.Mark();
				return true;
			}
			return false;
		}
		bool BLINKER::Refresh(__::UNITSTATE& state)
		{
			if (state.currIntensity)
			{
				state.setIntensity = NULL;	// if the RBG gets single changes, it applies change to all colors equally.
				mLastFXclock.Mark();
				return true;
			}
			else
			{
				state.setIntensity = 255;
				mLastFXclock.Mark();
				return true;
			}
			return false;
		}
		BLINKER::~BLINKER()
		{
		}
		bool BLINKER::CheckOnUpdate(ClockCache& _RefreshClock, const uint8_t& _intensity)
		{
			if (_intensity > 0)
			{
				if ((_RefreshClock - mLastFXclock) > mON)
				{
					return true;
				}
			}
			else if ((_RefreshClock - mLastFXclock) > mOFF)
			{
				return true;
			}
			return false;
		}
		BICOLORSWEEP::BICOLORSWEEP()
		{
			m_HoldUp = false;
			m_HoldDown = false;
			m_SweepUp = false;
			m_SweepDown = false;
			m_FreshStart = true;
		}
		BICOLORSWEEP::BICOLORSWEEP(const color::RGBColor& upColor, const color::RGBColor& downColor, uint32_t colorHoldTime, uint32_t sweepTime)
		{
			m_HoldUp = false;
			m_HoldDown = false;
			m_SweepUp = false;
			m_SweepDown = false;
			m_FreshStart = true;
			mUpColor = upColor;
			mDownColor = downColor;
			m_HoldTime = colorHoldTime;
			m_SweepTime = sweepTime;
			m_SweepDownRange[0] = mDownColor.R - mUpColor.R;
			m_SweepDownRange[1] = mDownColor.G - mUpColor.G;
			m_SweepDownRange[2] = mDownColor.B - mUpColor.B;
			m_SweepUpRange[0] = mUpColor.R - mDownColor.R;
			m_SweepUpRange[1] = mUpColor.G - mDownColor.G;
			m_SweepUpRange[2] = mUpColor.B - mDownColor.B;
		}
		bool BICOLORSWEEP::Update(ClockCache& _RefreshClock, __::RGBSTATE& _rgbState)
		{
			if (m_HoldUp || m_HoldDown)
			{
				if ((_RefreshClock - m_HoldStart) > m_HoldTime) return true;
				return false;
			}

			if (m_SweepUp || m_SweepDown) {
				mSweepCycleDelta = _RefreshClock - m_SweepStart;
				return true;
			}

			if (m_FreshStart)
			{
				m_SweepStart = _RefreshClock;
				mSweepCycleDelta = _RefreshClock - m_SweepStart;
				m_FreshStart = false;
				m_SweepUp = true;
				return true;
			}
			return false;
		}
		bool BICOLORSWEEP::Refresh(__::RGBSTATE& _state)
		{
			if (m_FreshStart)
			{
				m_FreshStart = false;
			}
			if (m_HoldUp)
			{
				m_HoldUp = false;
				m_SweepDown = true;
				m_SweepStart.Mark();
				mSweepCycleDelta = 0;
			}
			if (m_HoldDown)
			{
				m_HoldDown = false;
				m_SweepUp = true;
				m_SweepStart.Mark();
				mSweepCycleDelta = 0;

			}
			if (m_SweepDown)
			{
				if (mSweepCycleDelta > m_SweepTime)
				{
					m_HoldDown = true;
					m_SweepDown = false;
					_state.setColor = mDownColor;
					m_HoldStart.Mark();
					return true; // Just here to break out of function. Return doesn't do anything.
				}
				int dR = SignedIntensityPercentFactor(m_SweepDownRange[0]);
				int dG = SignedIntensityPercentFactor(m_SweepDownRange[1]);
				int dB = SignedIntensityPercentFactor(m_SweepDownRange[2]);
				
				uint8_t R = NewPinValue(mUpColor.R, dR);
				uint8_t G = NewPinValue(mUpColor.G, dG);
				uint8_t B = NewPinValue(mUpColor.B, dB);
				_state.setColor.R = R;
				_state.setColor.G = G;
				_state.setColor.B = B;
				return true;
			}
			if (m_SweepUp)
			{
				if (mSweepCycleDelta > m_SweepTime)
				{
					m_HoldUp = true;
					m_SweepUp = false;
					_state.setColor = mUpColor;
					m_HoldStart.Mark();
					return true; // Just here to break out of function. Return doesn't do anything.
				}

				int dR = SignedIntensityPercentFactor(m_SweepUpRange[0]);
				int dG = SignedIntensityPercentFactor(m_SweepUpRange[1]);
				int dB = SignedIntensityPercentFactor(m_SweepUpRange[2]);
				uint8_t R = NewPinValue(mDownColor.R, dR);
				uint8_t G = NewPinValue(mDownColor.G, dG);
				uint8_t B = NewPinValue(mDownColor.B, dB);
				_state.setColor.R = R;
				_state.setColor.G = G;
				_state.setColor.B = B;
				return true;
			}
			return false;
		}
		void BICOLORSWEEP::StartFresh(const color::RGBColor& upColor, const color::RGBColor& downColor, uint32_t colorHoldTime, uint32_t sweepTime)
		{
			m_HoldUp = false;
			m_HoldDown = false;
			m_SweepUp = false;
			m_SweepDown = false;
			m_FreshStart = true;
			mUpColor = upColor;
			mDownColor = downColor;
			m_HoldTime = colorHoldTime;
			m_SweepTime = sweepTime;
			m_SweepDownRange[0] = mDownColor.R - mUpColor.R;
			m_SweepDownRange[1] = mDownColor.G - mUpColor.G;
			m_SweepDownRange[2] = mDownColor.B - mUpColor.B;
			m_SweepUpRange[0] = mUpColor.R - mDownColor.R;
			m_SweepUpRange[1] = mUpColor.G - mDownColor.G;
			m_SweepUpRange[2] = mUpColor.B - mDownColor.B;
		}
		int BICOLORSWEEP::SignedIntensityPercentFactor(const int ColorChannelRange)
		{
			double temp = double(mSweepCycleDelta) / double(m_SweepTime);
			double other = temp * double(ColorChannelRange);
			return other;
		}
		uint8_t BICOLORSWEEP::NewPinValue(uint8_t currentColorChannel, const int signedChangeAmount)
		{
			int newValue = currentColorChannel + signedChangeAmount;
			return uint8_t((newValue < 0 ? 0 : newValue) > 255 ? 255 : newValue);
		}
		FX::FX()
		{		
		}
		FX::~FX()
		{
		}
	}
}
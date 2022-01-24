#include "blipFX.h"
#include <ADM.h>
#include <NumSafe.h>

namespace plx
{
	using namespace adm::SHORTSTREAMKEYWORDS;
	namespace __FX
	{
		BLIP::BLIP()
		{
		}
		BLIP::BLIP(uint32_t blipRiseFallTime, uint32_t blipHoldTime, uint8_t blipIntensity, __::UNITSTATE& _unitState)
		{
			mRiseFallTime = blipRiseFallTime;
			mHoldTime = blipHoldTime;
			mTargetIntensity = blipIntensity;
			mBaseIntensity = _unitState.currIntensity;
			mDestroy = false;
			mRise = false;
			mFall = false;
			mHold = false;
			FreshStart = true;
		}
		BLIP::BLIP(uint32_t blipRiseFallTime, uint32_t blipHoldTime, color::RGBColor& blipColor)
		{
			mBlipColor = blipColor;
			mDestroy = false;
			mRise = false;
			mFall = false;
			mHold = false;
			FreshStart = true;
			mStartTime.Mark();
		}
		bool BLIP::Update(ClockCache& _RefreshClock, __::UNITSTATE& _UnitState)
		{
			timeSinceBlipStart = _RefreshClock - mStartTime;
			return UniversalUpdate();
		}
		bool BLIP::Update(ClockCache& _RefreshClock, __::RGBSTATE& _rgbState)
		{
			timeSinceBlipStart = _RefreshClock - mStartTime;
			return UniversalUpdate();
		}
		bool BLIP::UniversalUpdate()
		{
			if (FreshStart)
			{
				mRise = true;
				FreshStart = false;
			}
			if(mRise) /* START CYCLE */
			{
				if(timeSinceBlipStart > mRiseFallTime)
				{
					mRise = false;
					mHold = true;
					return true;
				}
				return true;
			}
			if(mFall) /* FINISH CYCLE */
			{
				if((timeSinceBlipStart - mRiseFallTime - mHoldTime) > mRiseFallTime)
				{
					mFall = false;
					mDestroy = true;
				}
				return true;
			}
			if(mHold) /* MID CYCLE */
			{
				if((timeSinceBlipStart - mRiseFallTime) > mHoldTime)
				{
					mHold = false;
					mFall = true;
					return true;
				}
				return false;
			}
			return false;
		}
		bool BLIP::Refresh(__::UNITSTATE& _inState)
		{
			if(mRise)
			{
				_inState.setIntensity = numsafe::GetTimeFactoredPinValue(mBaseIntensity, mTargetIntensity, timeSinceBlipStart, mRiseFallTime);
				return true;
			}
			if(mFall)
			{
				_inState.setIntensity = numsafe::GetTimeFactoredPinValue(mTargetIntensity, mBaseIntensity, timeSinceBlipStart, mRiseFallTime);
				return true;
			}
			if(mHold)
			{
				_inState.setIntensity = mTargetIntensity;
				return true;
			}
			if (mDestroy)
			{
				_inState.setIntensity = mBaseIntensity;
				return true;
			}
			return false;
		}
		bool BLIP::Refresh(__::RGBSTATE& _inRGBstate)
		{
			return false;
		}
		BLIP::~BLIP()
		{
		}
		BLIPFX::BLIPFX()
		{
		}
		bool BLIPFX::Destroy()
		{
			return mDestroy;
		}
		BLIPFX::~BLIPFX()
		{
		}

	}

}
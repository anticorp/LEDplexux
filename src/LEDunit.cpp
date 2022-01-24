#include "LEDunit.h"
#include "ADM.h"
#include "FX_Effects/Effects.h"
#include "FX_Effects/blipFX.h"
#include "PLEXUS.h"
#include <NumSafe.h>

namespace plx
{
	using namespace adm::SHORTSTREAMKEYWORDS;
	LEDunit::LEDunit()
	{
	}

	SingleLEDunit::SingleLEDunit(uint32_t pinNo, bool pwm, uint8_t intensity, const char* LEDname)
	{
		if (!mConfigured)
		{
			LEDunit* newPointer;
			newPointer = this;
			if (PLEXUS::RegisterNewUnit(newPointer)) {
				mPin.Configure(pinNo, pwm);
				_FX = nullptr;
				mFXactive = false;
				mBlipping = false;
				mPreBlip = false;
				mInitialized = false;
				mStaticMode = true;
				mState.currIntensity = intensity;
				//mLEDname = LEDname;
				mActive = false;
				mConfigured = true;
			}
		}
	}
	bool SingleLEDunit::Initialize()
	{
		if(mConfigured && !mInitialized)
		{			
			mInitialized = mPin.Initialize();
			mActive = mInitialized;
			return mInitialized;
		}
		return false;
	}
	void SingleLEDunit::SpeakUp()
	{
		Serial.print(" =[ *S* ]=[ PIN ]=[ ");
		Serial.print(mPin.GetPinNo());
		Serial.print(" ]= ");

	}
	void SingleLEDunit::TurnOn()
	{
		if (mInitialized)
		{
			mState.setIntensity = 255;
			mPin.SetIntensity(mState.setIntensity);
			mState.currIntensity = mState.setIntensity;
			mStaticMode = true;
			mFXactive = false;
			mActive = true;
		}
	}
	void SingleLEDunit::TurnOn(const uint8_t Intensity)
	{
		//WipeFX();
		mState.setIntensity = numsafe::Uint8bit(Intensity);
		mPin.SetIntensity(mState.setIntensity);
		mState.currIntensity = mPin.GetIntensity();
		mStaticMode = true;
		mFXactive = false; 
		mActive = true;
	}
	void SingleLEDunit::TurnOff()
	{
		mState.setIntensity = 0;
		mPin.SetIntensity(mState.setIntensity);
		mState.currIntensity = mState.setIntensity;
		mStaticMode = true;
		//WipeFX();
		mFXactive = false;
		mActive = true;
	}
	bool SingleLEDunit::Update(ClockCache& _RefreshClock)
	{
		if (mFXactive)
		{			
			return _FX->Update(_RefreshClock, mState);
		}	
	}
	void SingleLEDunit::Refresh()
	{
		if(mFXactive)
		{
			
			_FX->Refresh(mState);
			if (!mBlipping || !mPreBlip)
			{
				mPin.SetIntensity(mState.setIntensity);
			}
			mState.currIntensity = mState.setIntensity;			
		}	
	}
	void SingleLEDunit::Blink(uint32_t onPeriod, uint32_t offPeriod)
	{
		if (mInitialized)
		{
			mBlinker.Blink(onPeriod, offPeriod);
			_FX = &mBlinker;
			//WipeFX();
			//_FX = new __FX::BLINKER(onPeriod, offPeriod);
			mFXactive = true;
			mStaticMode = false;
		}
	}

	void SingleLEDunit::PreBlipDarken(uint8_t darkIntensity)
	{
		if(mActive)
		{
			if(!mPreBlip && !mBlipping)
			{
				mBlipDarkenState.setIntensity = darkIntensity;
				mPin.SetIntensity(mBlipDarkenState.setIntensity);
				mPreBlip = true;			
			}
		} 
	}
	void SingleLEDunit::BlipRefresh()
	{
		if(!mPreBlip)
		{
			if(mBlipClock.Delta() > mBlipDuration)
			{
				/* Revert to whatever Current State is */
				mPin.SetIntensity(mState.currIntensity);
				mBlipping = false;
				PLEXUS::DeRegisterBlip(mBlipID);
			}
		}
	}
	void SingleLEDunit::Blip(uint32_t blipDuration, uint8_t blipIntensity)
	{
		if(mActive)
		{
			if(!mBlipping || mPreBlip)
			{
				mPreBlip = false;
				LEDunit* me = this;
				mBlipID = PLEXUS::RegisterBlip(me);
				mBlipping = true;
				mBlipClock.Mark();
				mBlipBlipState.setIntensity = blipIntensity;
				mPin.SetIntensity(mBlipBlipState.setIntensity);
				mBlipBlipState.currIntensity = mBlipBlipState.setIntensity;
			}
		}
	}
	void SingleLEDunit::UnlockBlipDarken()
	{
		if(mPreBlip && !mBlipping)
		{
			mPin.SetIntensity(mState.currIntensity);
			mPreBlip = false;
		}
	}
	bool SingleLEDunit::PowerState()
	{
		return false;
	}
	bool LEDunit::WipeFX()
	{
		if (_FX != nullptr) 
		{
			delete _FX;
			_FX = nullptr;
			mFXactive = false;
			return true;
		}
		mFXactive = false;
	}

	RGBLEDUnit::RGBLEDUnit(uint32_t REDpin, uint32_t GREENpin, uint32_t BLUEpin, bool REDpwm, bool GREENpwm, bool BLUEpwm, const color::RGBColor& inColor, const char* LEDname)
	{
		if (!mConfigured)
		{
			LEDunit* newPointer;
			newPointer = this;
			if(PLEXUS::RegisterNewUnit(newPointer)) {
				//WipeFX();
				mRpin.Configure(REDpin, REDpwm);
				mGpin.Configure(GREENpin, GREENpwm);
				mBpin.Configure(BLUEpin, BLUEpwm);
				mFXactive = false;
				mBlipping = false;
				mPreBlip = false;
				mStaticMode = true;
				mState.baseColor.R = inColor.R;
				mState.baseColor.G = inColor.G;
				mState.baseColor.B = inColor.B;
				mState.setColor.R = inColor.R;
				mState.setColor.G = inColor.G;
				mState.setColor.B = inColor.B;
				mState.currColor.R = inColor.R;
				mState.currColor.G = inColor.G;
				mState.currColor.B = inColor.B;
				//mLEDname = LEDname;
				mInitialized = false;
				mActive = false;
				mConfigured = true;
			}
		}
	}

	/* RGB - MAIN CONSTRUCTOR */
	bool RGBLEDUnit::Initialize()
	{
		if(mConfigured && !mInitialized)
		{			
			bool R = mRpin.Initialize();
			bool G = mGpin.Initialize();
			bool B = mBpin.Initialize();
			mInitialized = R && R && B;
			mActive = mInitialized;
			return mInitialized;
		}
		return false;
	}
	void RGBLEDUnit::TurnOn()
	{
		TurnOn(mState.baseColor);
	}
	void RGBLEDUnit::TurnOn(const color::RGBColor& Color)
	{
		if(mInitialized)
		{
	
			mState.setColor.R = Color.R;
			mState.setColor.G = Color.G;
			mState.setColor.B = Color.B;

			mRpin.SetIntensity(mState.setColor.R);
			mGpin.SetIntensity(mState.setColor.G);
			mBpin.SetIntensity(mState.setColor.B);

			mState.currColor.R = mState.setColor.R;
			mState.currColor.G = mState.setColor.G;
			mState.currColor.B = mState.setColor.B;

			mFXactive = false;
			mStaticMode = true;
			mActive = true;
		}
	}
	void RGBLEDUnit::TurnOff()
	{
		if (mInitialized)
		{
			mState.setColor.R = 0;
			mState.setColor.G = 0;
			mState.setColor.B = 0;

			mRpin.SetIntensity(mState.setColor.R);
			mGpin.SetIntensity(mState.setColor.G);
			mBpin.SetIntensity(mState.setColor.B);

			mState.currColor.R = mState.setColor.R;
			mState.currColor.G = mState.setColor.G;
			mState.currColor.B = mState.setColor.B;

			mStaticMode = true;
			mFXactive = false;
			mActive = true;
		}
	}
	void RGBLEDUnit::Blink(uint32_t onPeriod, uint32_t offPeriod)
	{
		if (mInitialized)
		{
			//WipeFX();
			//_FX = new __FX::BLINKER(onPeriod, offPeriod, mState.currColor, color::Black);
			mFXactive = true;
			mStaticMode = false;
		}		
	}
	void RGBLEDUnit::BiColorSweep(const color::RGBColor& upColor, const color::RGBColor& downColor, uint32_t upTime, uint32_t sweepTime)
	{
		mFXactive = false;
		mBiColorSweep.StartFresh(upColor, downColor, upTime, sweepTime);
		_FX = &mBiColorSweep;
		mFXactive = true;
		mStaticMode = false;
		//bug << xpara << "RGB: Done Setting!";
	}
	void RGBLEDUnit::ChangeColor(const color::RGBColor& _rgb)
	{
		mState.baseColor = _rgb;
		mState.currColor = mState.baseColor;
		if(!mFXactive)	TurnOn();
	}
	void RGBLEDUnit::ChangeColor(uint8_t REDintensity, uint8_t GREENintensity, uint8_t BLUEintensity)
	{
		mState.setColor = { REDintensity, GREENintensity, BLUEintensity, "Set Color" };
	}
	void RGBLEDUnit::SpeakUp()
	{		
	}

	bool RGBLEDUnit::Update(ClockCache& _RefreshClock)
	{
		if (mFXactive)
		{
			mFXmute = _FX->Update(_RefreshClock, mState);
		}
		return mFXmute;
	}
	void RGBLEDUnit::Refresh()
	{
		_FX->Refresh(mState);
		mRpin.SetIntensity(mState.setColor.R);
		mGpin.SetIntensity(mState.setColor.G);
		mBpin.SetIntensity(mState.setColor.B);
		mState.currColor.R = mRpin.GetIntensity();
		mState.currColor.G = mRpin.GetIntensity();
		mState.currColor.B = mRpin.GetIntensity();
	}
	
}
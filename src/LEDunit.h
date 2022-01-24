#pragma once

#ifndef _LEDunit_h
#define _LEDunit_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <PinBase.h>
#include <UnitState.h>
#include <ClockCache.h>
#include <Color.h>
#include <FX_Effects/Effects.h>

namespace plx
{
	class LEDunit
	{
	public:
		operator bool() { return mActive && !mStaticMode; }
		virtual bool Update(ClockCache& _RefreshClock) {}
		virtual bool BlipUpdate(ClockCache& _RefreshClock) {}
		virtual bool BlipActive() {}
		virtual void BlipRefresh() {}
		virtual void Refresh() {}
		virtual void SpeakUp() {}

	protected:
		bool WipeFX();
		LEDunit();
		friend class PLEXUS;
		bool mConfigured = false;
		bool mInitialized = false;
		bool mPWM;
		bool mActive;
		bool mFXactive;
		bool mFXmute;
		bool mBlipping;
		bool mPreBlip;
		bool mStaticMode;
		bool mStoredStatic;
		bool mBlipHasDefaults;
		uint32_t mBlipDuration;
		uint8_t mBlipID;
		ClockCache mBlipClock;
		__FX::FX* _FX;
		//String mLEDname;		
		const char* mName = "LED";

	private:
	};
	/*									*/
	/*		SINGLE LED UNIT CLASS		*/
	/*									*/
	class SingleLEDunit : public LEDunit
	{
	public:
		SingleLEDunit(uint32_t pinNo, bool pwm, uint8_t intensity, const char* LEDname);
		bool Initialize();
		void SpeakUp() override;
		void TurnOn();
		/* Still turns on LED, but intensity only affects PWM LEDs. An intensity of 1 on a non-PWM is full brightness. ALSO Unlike TurnOn(), this one will reset the LED and wipe the FX in order to set the new solid intensity. */
		void TurnOn(uint8_t Intensity);
		void TurnOff();
		bool Update(ClockCache& _RefreshClock) override;
		void Refresh() override;
		void Blink(uint32_t onPeriod, uint32_t offPeriod);
		/*		When Defaults are set, using Blip() without parameters
			on an LED object will use those defaults. This is to
			allow for quick easy Blips anywhere needed.*/
		void BlipDefaultSet(uint32_t blipRiseFall, uint32_t blipHold, uint8_t blipIntensity);
		/*		If called without user Defaults set, this will simply
			cause a blip of 800 milliseconds, with 200 milliseconds for
			each the rise and fall, and holding ON for 400 milliseconds. */

		void PreBlipDarken(uint8_t darkIntensity);
		void UnlockBlipDarken();
		void Blip(uint32_t blipDuration, uint8_t blipIntensity);
		bool PowerState();
		void BlipRefresh() override;

	protected:
		friend class PLEXUS;
		__FX::BLINKER mBlinker = __FX::BLINKER();

	private:
		int StartValue;
		uint32_t mBlipRiseFallDefault;
		uint32_t mBlipHoldDefault;
		uint8_t mBlipIntensityDefault;
		uint32_t mPinNo;

		pinbase::PINBASE mPin;
		__::UNITSTATE mState;
		__::UNITSTATE mStateBackup;
		__::UNITSTATE mBlipDarkenState;
		__::UNITSTATE mBlipBlipState;

	};

	/*														*/
	/*		RGB LED UNIT CLASS								*/
	/*														*/
	class RGBLEDUnit : public LEDunit
	{
	public:
		RGBLEDUnit() {}
		RGBLEDUnit(uint32_t REDpin, uint32_t GREENpin, uint32_t BLUEpin, bool REDpwm, bool GREENpwm, bool BLUEpwm, const color::RGBColor& BASEcolor, const char* LEDname);
		bool Initialize();
		void SpeakUp() override;
		void TurnOn();
		void TurnOn(const color::RGBColor& Color);
		void TurnOff();
		bool Update(ClockCache& _RefreshClock) override;
		void Refresh() override;
		void Blink(uint32_t onPeriod, uint32_t offPeriod);
		void BiColorSweep(const color::RGBColor& upColor, const color::RGBColor& downColor, uint32_t upTime, uint32_t sweepTime);
		/*		Behaviour of Change Color is up to the FX if they're set.
			Some FX, such as Blink() will keep blinking, but with a
			change in color. For a Solid ON state at a set color, use
			TurnOn(myColor) instead. That will reset the FX. */
		void ChangeColor(const xCol::RGBColor& _rgb);
		void ChangeColor(uint8_t REDintensity, uint8_t GREENintensity, uint8_t BLUEintensity);

	private:
		__FX::BICOLORSWEEP mBiColorSweep = __FX::BICOLORSWEEP();
		__::RGBSTATE mState;
		__::RGBSTATE mBlipState;
		color::RGBColor* mBaseColor;
		pinbase::PINBASE mRpin;
		pinbase::PINBASE mGpin;
		pinbase::PINBASE mBpin;
	};
}

#endif
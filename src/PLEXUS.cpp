#include "PLEXUS.h"
#include "Color.h"
#include <ADM.h>
//#include "LEDunit.h"

namespace plx
{
	PLEXUS LEDplexus = PLEXUS();
	using namespace adm::SHORTSTREAMKEYWORDS;
	const size_t StackSize = __Lplex__MAX__LED__SLOTS;
	LEDunit* PLEXUS::_RefreshStack[StackSize];
	size_t PLEXUS::LEDunitCount = 0;

	const size_t mBlipStackSize = __Lplex__MAX__BLIP__SLOTS;
	LEDunit* PLEXUS::_BlipStack[mBlipStackSize];
	size_t PLEXUS::mBlipsInStack = 0;

	uint32_t PLEXUS::LoopCount = 0;
	size_t PLEXUS::plx_RefreshStackIterator = 0;
	uint32_t PLEXUS::plx_RefreshRate = 110000;
	ClockCache PLEXUS::RefreshClock;

	PLEXUS::PLEXUS()		// Number of loops to skip before doing a refresh on FX, or checking for a state change on a solid
	{
	}
	PLEXUS::~PLEXUS()
	{
	}
	void PLEXUS::RefreshAll()
	{
		if (mBlipsInStack)
		{
			uint8_t i = 0;
			while (true)
			{
				if (i >= mBlipsInStack) break;
				_BlipStack[i]->BlipRefresh();
				i++;
			}
		}
		LoopCount++;
		if (LoopCount > plx_RefreshRate)
		{
			size_t i = (plx_RefreshStackIterator + 1) % LEDunitCount;
			/*		Before we refresh the hardware or do anything else
				We'll let the LED Unit dictate whether it needs to be
				updated or not. First by declaring whether it's active
				or not. This allows an LED with FX to be turned on or
				off without changing the FX themselves. All LEDs are
				created in the Active State. */
			if (_RefreshStack[plx_RefreshStackIterator]) /* Activated Test */
			{
				/*		Clock Cache is auto marking and internally stores
					current Millis() time. */
				RefreshClock.Mark();
				if (_RefreshStack[plx_RefreshStackIterator]->Update(RefreshClock))
				{
					_RefreshStack[plx_RefreshStackIterator]->Refresh();
				}
			}
			plx_RefreshStackIterator = i;
			LoopCount = 0;
		}
	}
	void PLEXUS::SetRefreshRate(size_t refreshRate)
	{
		plx_RefreshRate = refreshRate;
	}

	bool PLEXUS::RegisterNewUnit(LEDunit* _newUnit)
	{
		if (LEDunitCount < StackSize)
		{
			_RefreshStack[LEDunitCount] = _newUnit;
			LEDunitCount++;
			return true;
		}
		return false;
	}

	uint8_t PLEXUS::RegisterBlip(LEDunit* _blipUnit)
	{
		uint8_t i = (mBlipsInStack + 1) % mBlipStackSize;
		if(i)
		{			
			_BlipStack[mBlipsInStack] = _blipUnit;
			mBlipsInStack = i;			
			return i;
		}
		return 0;
	}

	bool PLEXUS::DeRegisterBlip(uint8_t blipID)
	{
		uint8_t updateID = blipID;
			while (true)
			{
				
				if (updateID < mBlipsInStack) break;
				if (updateID == mBlipsInStack)
				{
					
					_BlipStack[updateID - 1] = nullptr;
					mBlipsInStack--;
					return true;
				}
				_BlipStack[updateID - 1] = _BlipStack[updateID];
				updateID++;
			}
		return false;
	}

}
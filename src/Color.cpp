#include "Color.h"
#include <ADM.h>

namespace plx
{
	namespace color
	{
		RGBColor::RGBColor(bool byOutputValue, uint8_t redValue, uint8_t greenValue, uint8_t blueValue, const String& name)
		{

			if (!byOutputValue)
			{
				/* Has Safety built in */
				R = PercentTo8bit(redValue);
				G = PercentTo8bit(greenValue);
				B = PercentTo8bit(blueValue);
			}
			else
			{
				R = redValue;
				G = greenValue;
				B = blueValue;

			}
			mName = name;
		}
		RGBColor::RGBColor(uint8_t redPercent, uint8_t greenPercent, uint8_t bluePercent, const String& name)
		{
			/* Percent To 8bit has safties built in */
			R = PercentTo8bit(redPercent);
			G = PercentTo8bit(greenPercent);
			B = PercentTo8bit(bluePercent);
			mName = name;
		}
		RGBColor& RGBColor::operator ++ ()
		{
			uint8_t xR = R + 1;
			uint8_t xG = G + 1;
			uint8_t xB = B + 1;
			R = xR > 255 ? 255 : xR;
			G = xG > 255 ? 255 : xG;
			B = xB > 255 ? 255 : xB;
			return *this;
		}
		uint8_t PercentTo8bit(uint8_t& _inPercent)
			{
				uint8_t correctedPercent = _inPercent > 100 ? 100 : _inPercent;
				float_t floatPercent = correctedPercent / 100.00f;
				return uint8_t(255 * floatPercent);
			}
		uint8_t Make8bitSafe(uint8_t& _in)
		{
			return (_in > 255 ? 255 : _in);
		}
		RGBColor operator + (const RGBColor& _inRGB1, const RGBColor& _inRGB2)
		{
			uint8_t R = _inRGB1.R + _inRGB2.R;
			uint8_t G = _inRGB1.G + _inRGB2.G;
			uint8_t B = _inRGB1.B + _inRGB2.B;	
			return RGBColor(true,
							R > 255 ? 255 : R,
							G > 255 ? 255 : G,
							B > 255 ? 255 : B,
							"Added Color"	);
		}
		RGBColor operator - (const RGBColor& _inRGB1, const RGBColor& _inRGB2)
		{
			int16_t nR = (_inRGB1.R - _inRGB2.R);
			int16_t nG = (_inRGB1.G - _inRGB2.G);
			int16_t nB = (_inRGB1.B - _inRGB2.B);
			uint8_t R = nR < 0 ? 0 : nR;
			uint8_t G = nG < 0 ? 0 : nG;
			uint8_t B = nB < 0 ? 0 : nB;

			return RGBColor(true, R, G, B, "Subtracted Color");
		}
		RGBColor& RGBColor::operator = (const RGBColor& in)
		{
			R = in.R;
			G = in.G;
			B = in.B;
			mName = in.mName;
			return *this;
		}
		uint8_t RGBColor::getAvg()
		{
			return uint8_t((R + G + B) / 3);
		}
		const bool RGBColor::SpeakUp() const
		{
			xbugWatch(__FUNCTION__);
			bug << "\n[ \"" << mName << "\" ]=" bugVar(R) << bugVar(G) << bugVar(B);
		}
		bool operator == (const RGBColor& _inRGB1, const RGBColor& _inRGB2)
		{
			return ((_inRGB1.R == _inRGB2.R)&&
					(_inRGB1.G == _inRGB2.G)&&
					(_inRGB1.B == _inRGB2.B));
		}
		bool operator != (const RGBColor& _inRGB1, const RGBColor& _inRGB2)
		{
			return !(_inRGB1 == _inRGB2);
		}
		RGBColor Avg(const RGBColor& _inRGB1, const RGBColor& _inRGB2)
		{
			uint8_t R = ((_inRGB1.R + _inRGB2.R) / 2);
			uint8_t G = ((_inRGB1.G + _inRGB2.G) / 2);
			uint8_t B = ((_inRGB1.B + _inRGB2.B) / 2);
			return RGBColor(true, R, G, B, "TripleAveraged Color");
		}	
	}
}

#if (__LEDplexus__Use_xCol_Namespace)
namespace xCol
{
	//using namespace Lplex::color;
}
#endif


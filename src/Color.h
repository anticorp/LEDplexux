#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
//#include "WProgram.h"
#endif

//#include "BUILD_SETTINGS/_BUILD_SETTINGS.h"
#define __LEDplexus__Xtend_Color_Palette true
#define __LEDplexus__Include_Xtended_Red true
#define __LEDplexus__Include_Xtended_Blue true
#define __LEDplexus__Include_Xtended_Green true
#define __LEDplexus__Include_Xtended_Orange true
#define __LEDplexus__Include_Xtended_Yellow true
#define __LEDplexus__Include_Xtended_Purple true

#define __LEDplexus__Use_xCol_Namespace true

namespace plx
{
	namespace color
	{
		struct RGBColor
			{
				RGBColor() {}
				RGBColor(uint8_t redPercent, uint8_t greenPercent, uint8_t bluePercent, const String& name);
				RGBColor(bool ByPinValue, uint8_t redValue, uint8_t greenValue, uint8_t blueValue, const String& name);
				uint8_t R;
				uint8_t G;
				uint8_t B;
				String mName;
				const char* thing = "blah";
				RGBColor& operator ++ ();
				RGBColor& operator = (const RGBColor& _rgb);
				uint8_t getAvg();
				const bool SpeakUp() const;
			};

		uint8_t PercentTo8bit(uint8_t&);
		uint8_t Make8bitSafe(uint8_t&);
		RGBColor operator + (const RGBColor& _inRGB1, const RGBColor& _inRGB2);
		RGBColor operator - (const RGBColor& _inRGB1, const RGBColor& _inRGB2);
		bool operator == (const RGBColor& _inRGB1, const RGBColor& _inRGB2);
		bool operator != (const RGBColor& _inRGB1, const RGBColor& _inRGB2);

		RGBColor Avg(const RGBColor& _inRGB1, const RGBColor& _inRGB2);

		const RGBColor Red = RGBColor(true, 255, 0, 0, "Red");
		const RGBColor BrightRed = RGBColor(100, 0, 0, "Bright Red");
		const RGBColor Green = RGBColor(true, 0, 255, 0, "Green");
		const RGBColor Blue = RGBColor(true, 0, 0, 255, "Blue");
		const RGBColor Yellow = RGBColor(true, 200, 200, 0, "Yellow");
		const RGBColor Orange = RGBColor(100, 65, 0, "Orange");
		const RGBColor BrightYellow = RGBColor(true, 255, 255, 0, "Bright Yellow");
		const RGBColor Purple = RGBColor(61, 19, 100, "Purple");
		const RGBColor Brown = RGBColor(65, 16, 16, "Brown");
		const RGBColor White = RGBColor(100, 100, 100, "White");
		const RGBColor BrightWhite = RGBColor(true, 255, 255, 230, "Bright White");
		const RGBColor Black = RGBColor(true, 0, 0, 0, "Black");

	#if defined(__LEDplexus__Xtend_Color_Palette)
		#if (__LEDplexus__Include_Xtended_Red)
			namespace xRed
			{
				const RGBColor LightCoral = RGBColor(94,50,50, "Light Coral");
				const RGBColor Strawberry = RGBColor(75, 15, 15, "Strawberry");
				const RGBColor Gummi = RGBColor(99, 8, 0, "Gummi");
				const RGBColor Salmon = RGBColor(98, 50, 45, "Salmon");
				const RGBColor BroadwayPink = RGBColor(100, 0, 40, "Broadway Pink");
				const RGBColor Cadmium = RGBColor(100, 1, 5, "Red Cadmium");
				/* Rosy Brown 1 = 100 , 76 , 76			 */
				const RGBColor RosyBrown1 = RGBColor(100, 76, 76, "Rosy Brown 1");
				/* Fire Brick 1 = 70 , 13 , 13			 */
				const RGBColor FireBrick = RGBColor(70, 13, 13, "Fire Brike");

			}
		#endif
		#if (__LEDplexus__Include_Xtended_Orange)
			namespace xOrange
			{
				const RGBColor SafetyCone = RGBColor(100, 33, 20, "Safety Cone");
				const RGBColor FleshOchre = RGBColor(100, 34, 13, "Flesh Ochre");
				const RGBColor Coral = RGBColor(100, 50, 31, "Coral");
				const RGBColor Crush = RGBColor(97, 46, 19, "Crush");
				const RGBColor Apricot = RGBColor(98, 63, 42, "Apricot");
				const RGBColor Cadmium = RGBColor(100, 38, 1, "Orange Cadmium");
				/* Orange Red 3 = 80 , 20 , 0			 */
				const RGBColor OrangeRed3 = RGBColor(80, 22, 0, "Orange Red 3");
			}
		#endif
		#if (__LEDplexus__Include_Xtended_Yellow)
			namespace xYellow
			{
				const RGBColor Goldenrod = RGBColor(100, 76, 15, "Goldenrod");
				const RGBColor BartlettPear = RGBColor(80, 67, 18, "Barlett Pear");
				const RGBColor Mustard = RGBColor(100, 80, 7, "Mustard");
				const RGBColor Gold = RGBColor(100, 84, 0, "Gold");
				const RGBColor CadmiumLemon = RGBColor(100, 89, 1, "Cadmium Lemon");
				const RGBColor Khaki1 = RGBColor(100, 96, 56, "Khaki 1");
				/* Gold 3 = 80 , 68 , 0			 */
				const RGBColor Gold3 = RGBColor(80, 68, 0, "Gold 3");
			}
		#endif
		#if (__LEDplexus__Include_Xtended_Green)
			namespace Xgreen
			{
				/* Spring Green = 78 , 96 , 15		*/
				const RGBColor SafetyVest = RGBColor(78, 96, 15, "Safety Vest");
				/* Chartreuse Verte = 74 , 91 , 22	*/
				const RGBColor ChartreuseVerte = RGBColor(74, 91, 22, "Chartreuse Verte");
				/* Jolly Green = 61 , 80 , 10		*/
				const RGBColor JollyGreen = RGBColor(61, 80, 10, "Jolly Green");
				/* Lawn Green = 49 , 99 , 0			*/
				const RGBColor LawnGreen = RGBColor(49, 99, 0, "Lawn Green");
				/* Spring Green = 0 , 100 , 20		*/
				const RGBColor SpringGreen = RGBColor(0, 100, 20, "Spring Green");
				/* Pale Green = 60 , 98, 60			*/
				const RGBColor PaleGreen = RGBColor(60, 98, 60, "Pale Green");
				/* Robs Startup Green = 40 , 60 , 5			 */
				const RGBColor RobsStartupGreen = RGBColor(30, 70, 5, "Startup Green");
				/* Parrot Green = 20 , 100 , 20			 */
				const RGBColor ParrotGreen = RGBColor(20, 100, 20, "Parrot Green");
			}
		#endif
		#if (__LEDplexus__Include_Xtended_Blue)
			namespace xBlue
			{
				const RGBColor LightTeal = RGBColor(0, 100, 80, "Light Teal");
				const RGBColor Aqua = RGBColor(0, 100, 100, "Aqua");
				const RGBColor Cadet = RGBColor(60, 96, 100, "Cadet");
				const RGBColor PoliceStrobe = RGBColor(4, 71, 100, "Police Strobe");
				const RGBColor Ice = RGBColor(45, 73, 98, "Ice");
				const RGBColor Slate = RGBColor(0, 50, 100, "Slate");
				const RGBColor Neon = RGBColor(30, 30, 100, "Neon");
			}
		#endif
		#if (__LEDplexus__Include_Xtended_Purple)
			namespace xPurple
			{
				const RGBColor Grape = RGBColor(80, 0, 100, "Grape");
				const RGBColor MediumOrchid = RGBColor(88, 40, 100, "Medium Orchid");
				const RGBColor Plum = RGBColor(87, 63, 87, "Plum");
				const RGBColor Fuchsia = RGBColor(100, 0, 100, "Fuchsia");
				const RGBColor Rose = RGBColor(100, 0, 80, "Rose");
				const RGBColor Violet = RGBColor(93, 51, 93, "Violet");
			}
		#endif
	#endif
	}
}

#if (__LEDplexus__Use_xCol_Namespace)
	namespace xCol
	{
		using namespace plx::color;
		//#if defined(__LEDplexus__Xtend_Color_Palette)
		//	#if !defined(__LEDplexus__Exclude_Xtended_Red)
		//		using namespace Lplex::color::xRed;
		//	#endif
		//	#if !defined(__LEDplexus__Exclude_Xtended_Red)
		//		using namespace Lplex::color::Xgreen;
		//	#endif
		//	#if !defined(__LEDplexus__Exclude_Xtended_Red)
		//		using namespace Lplex::color::xBlue;
		//	#endif
		//	#if !defined(__LEDplexus__Exclude_Xtended_Red)
		//		using namespace Lplex::color::xYellow;
		//	#endif
		//	#if !defined(__LEDplexus__Exclude_Xtended_Red)
		//		using namespace Lplex::color::xOrange;
		//	#endif
		//	#if !defined(__LEDplexus__Exclude_Xtended_Red)
		//		using namespace Lplex::color::xPurple;
		//	#endif
		//#endif
	}
#endif

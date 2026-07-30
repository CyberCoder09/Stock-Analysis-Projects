#pragma once // Ensures that everything is compiled once and that no duplicates exist.
#include "aCandlestick.h" // Including declaration of aCandlestick class to create instances.

#include <cmath> // Include cmath for math functions like abs, max, min.

using namespace System; // namespace for String, DateTime, etc.

namespace COP4931
{
	public ref class aSmartCandlestick : public aCandlestick
	{
		public:
			property float range; //
			property float bodyRange; //
			property float upperRange;
			property float lowerRange;
			property float bodyTop;
			property float bodyBottom;
			property bool isBullish;
			property bool isBearish;

		aSmartCandlestick() : aCandlestick()
		{
			calculateRanges(); // 
		}

		aSmartCandlestick(aCandlestick^ sourceCandlestick) : aCandlestick(sourceCandlestick)
		{
			calculateRanges();
		}

		aSmartCandlestick(DateTime d, float o, float h, float l, float c, unsigned long v) : aCandlestick(d, o, h, l, c, v)
		{
			calculateRanges();
		}

		aSmartCandlestick(String^ line) : aCandlestick(line)
		{
			calculateRanges();
		}

		aSmartCandlestick(aSmartCandlestick^ sourceSmartCandlestick) : aCandlestick((aCandlestick^)sourceSmartCandlestick)
		{
			this->range = sourceSmartCandlestick->range;
			this->bodyRange = sourceSmartCandlestick->bodyRange;
			this->bodyTop = sourceSmartCandlestick->bodyTop;
			this->bodyBottom = sourceSmartCandlestick->bodyBottom;
			this->upperRange = sourceSmartCandlestick->upperRange;
			this->lowerRange = sourceSmartCandlestick->lowerRange;
			this->isBullish = sourceSmartCandlestick->isBullish;
			this->isBearish = sourceSmartCandlestick->isBearish; //
		}

        public:
			void calculateRanges()
			{
				this->range = this->high - this->low;
				this->bodyRange = Math::Abs(this->close - this->open);
				this->bodyTop = Math::Max(this->open, this->close);
				this->bodyBottom = Math::Min(this->open, this->close);
				this->upperRange = this->high - bodyTop;
				this->lowerRange = this->bodyBottom - this->low;
				this->isBullish = this->close > this->open;
				this->isBearish = this->close < this->open;
			}
	};
}
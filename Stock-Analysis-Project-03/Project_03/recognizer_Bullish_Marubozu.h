#pragma once
#include "aRecognizer.h"

namespace COP4931
{
	ref class recognizer_Bullish_Marubozu : public aRecognizer
	{
		public:
			/// <summary>
			/// Constructs a recognizer_Bullish_Marubozu and initializes its base aRecognizer with the name "Bullish Marubozu" and an identifier of 1.
			/// </summary>
			recognizer_Bullish_Marubozu() : aRecognizer("Bullish Marubozu", 1)
			{
				// The constructor for the recognizer_Bullish_Marubozu class initializes
			}

			virtual bool isMatch(List<aSmartCandlestick^>^ smartCandlesticks) override
			{
				if (smartCandlesticks[0]->isBullish)
				{
					double ratio = smartCandlesticks[0]->bodyRange / smartCandlesticks[0]->range; // Calculates the ratio of the body range to the total range for the first candlestick in the list. This ratio represents how much of the candlestick's total range is occupied by its body, which is a key characteristic of a Marubozu pattern. A Marubozu pattern typically has a very large body relative to its total range, indicating strong buying pressure without significant wicks (shadows) on either end.
					return ratio >= 0.95; // If the body of the candlestick is at least 95% of the total range, it is considered a Marubozu pattern, and the function returns true. Otherwise, it returns false.
				}
				return false; // If the candlestick is not bullish, it cannot be a bullish Marubozu, so the function returns false.
			}

	
			

	};		
}


#pragma once
#include "aRecognizer.h"

namespace COP4931
{

	ref class recognizer_Bearish_Marubozu : public aRecognizer
	{
		public:
			/// <summary>
			/// Constructor that creates a recognizer for the "Bearish Marubozu" pattern and initializes its base aRecognizer with the name "Bearish Marubozu" and the value 1.
			/// </summary>
			recognizer_Bearish_Marubozu() : aRecognizer("Bearish Marubozu", 1)
			{
				// The constructor for the recognizer_Bearish_Marubozu class initializes
			}

			/// <summary>
			/// Checks whether the first candlestick in the provided list is bearish &
			/// its body occupies at least 95% of the candlestick's range.
			/// </summary>
			/// <param name="smartCandlesticks">A managed list of aSmartCandlestick objects. The function inspects the element at index 0, so the list must contain at least one candlestick.</param>
			/// <returns>True if the first candlestick is bearish and (bodyRange / range) >= 0.95; otherwise false.</returns>
			virtual bool isMatch(List<aSmartCandlestick^>^ smartCandlesticks) override
			{
				// Checks if the first candlestick in the provided list is bearish &
				// if its body occupies at least 95% of the total range of the candlestick. 
				// This is done by calculating the ratio of bodyRange to range for 
				// the first candlestick and comparing it to the threshold of 0.95, 
				// but only if the candlestick is bearish (close < open).
				if (smartCandlesticks[0]->isBearish)
				{
					double ratio = smartCandlesticks[0]->bodyRange / smartCandlesticks[0]->range; // Calculates the ratio of the body range to the total range for the first candlestick in the list. This ratio represents how much of the candlestick's total range is occupied by its body, which is a key characteristic of a Marubozu pattern.
					return ratio >= 0.95; // Returns true if the body occupies at least 95% of the range, indicating a Marubozu pattern, otherwise returns false.
				}
				return false; // If the first candlestick is not bearish, returns false immediately without checking the body-to-range ratio, since a Marubozu pattern requires the candlestick to be bearish in this case.
			}

			

	};

}


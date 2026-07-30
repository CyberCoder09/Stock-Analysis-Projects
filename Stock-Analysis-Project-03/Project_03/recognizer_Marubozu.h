#pragma once

#include "aRecognizer.h" //

using namespace System; // namespace for String, DateTime, etc.

namespace COP4931
{
    public ref class recognizer_Marubozu : public aRecognizer
    {
    public:
        recognizer_Marubozu() : aRecognizer("Marubozu", 1)
        {
            // The constructor for the recognizer_Marubozu class initializes
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="smartCandlestick"></param>
        /// <returns></returns>
        virtual bool isMatch(List<aSmartCandlestick^>^ smartCandlestick) override
        {
			/// Checks if the first candlestick in the provided list is either bullish or bearish, and if so, calculates the ratio of the body range to the total range for that candlestick. If the ratio is greater than or equal to 0.95, it indicates that the candlestick has a very large body relative to its total range, which is characteristic of a Marubozu pattern. The function returns true if these conditions are met, indicating a Marubozu pattern, and false otherwise. If the first candlestick is neither bullish nor bearish (e.g., a doji with no body), it returns false immediately without checking the body-to-range ratio, since a Marubozu pattern requires a strong directional candlestick.
            if (smartCandlestick[0]->isBullish || smartCandlestick[0]->isBearish)
            {
				double ratio = smartCandlestick[0]->bodyRange / smartCandlestick[0]->range; // Calculates the ratio of the body range to the total range for the first candlestick in the list. This ratio represents how much of the candlestick's total range is occupied by its body, which is a key characteristic of a Marubozu pattern. A Marubozu pattern typically has a very large body relative to its total range, indicating strong buying or selling pressure without significant wicks (shadows) on either end.
				return ratio >= 0.95; // Returns true if the body occupies at least 95% of the range, indicating a Marubozu pattern, otherwise returns false. This check is only performed if the candlestick is either bullish or bearish, as a Marubozu pattern requires a strong directional candlestick with a significant body relative to its total range.
            }
			return false; // If the first candlestick is neither bullish nor bearish (e.g., a doji with no body), returns false immediately without checking the body-to-range ratio, since a Marubozu pattern requires a strong directional candlestick.
        }
    };
}


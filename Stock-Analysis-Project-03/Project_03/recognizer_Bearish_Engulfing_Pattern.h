#pragma once
#include "aRecognizer.h"

namespace COP4931
{
    ref class recognizer_Bearish_Engulfing_Pattern : public aRecognizer
    {
    public:
        recognizer_Bearish_Engulfing_Pattern() : aRecognizer("Bearish Engulfing Pattern", 2)
        {
            // The constructor for the recognizer_Bearish_Engulfing_Pattern class initializes
        }

        /// <summary>
        /// Determines whether the first two candlesticks in the provided list form a bearish engulfing 
        /// pattern (the previous candlestick is bullish and the current candlestick is bearish &
        /// fully engulfs the previous).
        /// </summary>
        /// <param name="smartCandlestick">A List of aSmartCandlestick^ objects where index 0 is the previous candlestick and index 1 is the current candlestick to evaluate. The function expects at least two elements.</param>
        /// <returns>true if the previous candlestick is bullish, the current candlestick is bearish, and the current candlestick's high is greater than the previous high while its low is lower than the previous low (i.e., the current fully engulfs the previous); otherwise false.</returns>
        virtual bool isMatch(List<aSmartCandlestick^>^ smartCandlestick) override
        {
            aSmartCandlestick^ previousCandlestick = smartCandlestick[0]; // Retrieves the first candlestick in the input list, which is expected to be the previous candlestick in the sequence being evaluated for the engulfing pattern.
            aSmartCandlestick^ currentCandlestick = smartCandlestick[1]; // Retrieves the second candlestick in the input list, which is expected to be the current candlestick being evaluated for the engulfing pattern.

            // Checks if the previous & current candlesticks have opposite colors (one bullish & one bearish) and if the current candlestick's body completely engulfs the previous candlestick's body. This is done by comparing the high and low of the previous candlestick with the high and low of the current candlestick to ensure that the current candlestick's range fully encompasses the previous one.
            return (previousCandlestick->isBullish && currentCandlestick->isBearish) && (previousCandlestick->high < currentCandlestick->high && previousCandlestick->low > currentCandlestick->low);
        }


    };
}


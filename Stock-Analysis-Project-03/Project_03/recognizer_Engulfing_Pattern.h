#pragma once
#include "aCandlestick.h"  // Including declaration of aCandlestick class to create instances.
#include "aSmartCandlestick.h"  // Including declaration of aSmartCandlestick class to create instances.
#include "aCandlestickLoader.h" // Including declaration of aCandlestickLoader class & LoadFromCsv() method..
#include "aRecognizer.h"

using namespace System; // namespace for String, DateTime, etc. 

namespace COP4931
{
    ref class recognizer_Engulfing_Pattern : public aRecognizer
    {
        public:
            recognizer_Engulfing_Pattern() : aRecognizer("Engulfing Pattern", 2)
            {
                // The constructor for the recognizer_Englufing_Pattern class initializes
            }

            virtual bool isMatch(List<aSmartCandlestick^>^ smartCandlestick) override
            {
				aSmartCandlestick^ previousCandlestick = smartCandlestick[0]; // Retrieves the first candlestick in the input list, which is expected to be the previous candlestick in the sequence being evaluated for the engulfing pattern.
				aSmartCandlestick^ currentCandlestick = smartCandlestick[1]; // Retrieves the second candlestick in the input list, which is expected to be the current candlestick being evaluated for the engulfing pattern.

				// Checks if the previous & current candlesticks have opposite colors (one bullish & one bearish) and if the current candlestick's body completely engulfs the previous candlestick's body. This is done by comparing the high and low of the previous candlestick with the high and low of the current candlestick to ensure that the current candlestick's range fully encompasses the previous one.
                return (previousCandlestick->isBullish != currentCandlestick->isBullish || previousCandlestick->isBearish != currentCandlestick->isBearish) && (previousCandlestick->high < currentCandlestick->high && previousCandlestick->low > currentCandlestick->low);
			}
    };
}


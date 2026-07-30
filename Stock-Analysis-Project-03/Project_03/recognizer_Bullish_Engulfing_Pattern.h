#pragma once
#include "aRecognizer.h"

namespace COP4931 
{
public ref class recognizer_Bullish_Engulfing_Pattern : public aRecognizer
    {
        public:
            /// <summary>
            /// Initializes a recognizer for the Bullish Engulfing Pattern by 
            /// calling the base aRecognizer constructor with the name "Bullish Engulfing Pattern"
            /// and an expected input count of 2.
            /// </summary>
            recognizer_Bullish_Engulfing_Pattern() : aRecognizer("Bullish Engulfing Pattern", 2)    
            {
                // The constructor for the recognizer_Bullish_Engulfing_Pattern class initializes
            }

            /// <summary>
            /// Determines whether the provided candlesticks form a bullish engulfing pattern.
            /// </summary>
            /// <param name="smartCandlestick">A list of candlestick objects where smartCandlestick[0] is the previous candlestick and smartCandlestick[1] is the current candlestick to evaluate. The function expects at least two elements.</param>
            /// <returns>true if the previous candlestick is bearish, the current candlestick is bullish, and the current candlestick's range (high/low) fully engulfs the previous candlestick's range; otherwise false.</returns>
            virtual bool isMatch(List<aSmartCandlestick^>^ smartCandlestick) override
            {
                aSmartCandlestick^ previousCandlestick = smartCandlestick[0]; // Retrieves the first candlestick in the input list, which is expected to be the previous candlestick in the sequence being evaluated for the engulfing pattern.
                aSmartCandlestick^ currentCandlestick = smartCandlestick[1]; // Retrieves the second candlestick in the input list, which is expected to be the current candlestick being evaluated for the engulfing pattern.

                // Checks if the previous & current candlesticks have opposite colors (one bullish & one bearish) and if the current candlestick's body completely engulfs the previous candlestick's body. This is done by comparing the high and low of the previous candlestick with the high and low of the current candlestick to ensure that the current candlestick's range fully encompasses the previous one.
                return (previousCandlestick->isBearish && currentCandlestick->isBullish) && (previousCandlestick->high < currentCandlestick->high && previousCandlestick->low > currentCandlestick->low);
			}

            /// <summary>
            /// Determines whether the current candlestick forms a bullish engulfing pattern relative to the previous candlestick.
            /// </summary>
            /// <param name="previousCandlestick">A list of previous candlesticks; the function compares against the candlestick at index 0 (the immediately preceding candlestick).</param>
            /// <param name="currentCandlestick">The current candlestick to evaluate.</param>
            /// <returns>true if the previous candlestick is bearish, the current candlestick is bullish, and the current candlestick's body completely engulfs the previous candlestick's body; otherwise false.</returns>
            bool isMatch(List<aSmartCandlestick^>^ previousCandlestick, aSmartCandlestick^ currentCandlestick)
            {
                bool bodyEngulfs = currentCandlestick->bodyBottom < previousCandlestick[0]->bodyBottom &&
                                    currentCandlestick->bodyTop > previousCandlestick[0]->bodyTop;
                
			    bool bullishEngulfing = previousCandlestick[0]->isBearish && currentCandlestick->isBullish;
                
				return bullishEngulfing && bodyEngulfs; // Returns true if the previous candlestick is bearish, the current candlestick is bullish, and the current candlestick's body completely engulfs the previous candlestick's body; otherwise false.
                
            }

    };
}


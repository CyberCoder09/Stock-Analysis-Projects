#include "pch.h"          // Precompiled header to speed up build by pulling common system & CLR headers.
#include "aCandlestick.h" // Including declaration of aCandlestick class to create instances.

using namespace COP4931;

/// <summary>
/// Constructs a new aCandlestick by copying from an existing managed aCandlestick.
/// </summary>
/// <param name="sourceCandlestick">A managed handle (aCandlestick^) 
/// to the source candlestick to copy from. 
/// May be nullptr to indicate no source.</param>
aCandlestick::aCandlestick(aCandlestick^ sourceCandlestick)
{
    // If sourceCandlestick is null the constructor should typically leave 
    // the new object in a default state,

    // If sourceCandlestick is not-null, copy each property from source to this. 
}

/// <summary>
/// Constructs an aCandlestick instance initialized from the provided managed string.
/// </summary>
/// <param name="line">A managed System::String (String^) containing input data used 
/// to initialize the candlestick (for example, a line of text).</param>
aCandlestick::aCandlestick(String^ line)
{
    // line contains text data for this constructor to validate and use input. 
}

/// <summary>
/// Constructs an aCandlestick object initialized with the specified date, price values, & volume.
/// </summary>
/// <param name="date">The date and time for the candlestick.</param>
/// <param name="open">The opening price.</param>
/// <param name="high">The highest price.</param>
/// <param name="low">The lowest price.</param>
/// <param name="close">The closing price.</param>
/// <param name="volume">The traded volume (number of units) for the period.</param>
aCandlestick::aCandlestick(DateTime date, float open, float high, float low, float close, unsigned long volume)
{
    // Assign parameter values to an object's properties.  
    this->date = date;     // Sets the date value for the aCandlestick instance. 
    this->open = open;     // Sets the opening price value for the aCandlestick instance.
    this->high = high;     // Sets the high price value for the aCandlestick instance.
    this->low = low;       // Sets the low price value for the aCandlestick instance.
    this->close = close;   // Sets the close price value for the aCandlestick instance.
    this->volume = volume; // Sets the volume value for the aCandlestick instance.
}
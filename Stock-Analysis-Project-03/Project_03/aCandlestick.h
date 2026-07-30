#pragma once // Ensures that everything is compiled once and that no duplicates exist.
#include <string> // Adding string library

using namespace System; // Lets you type DateTime or String without System::DateTime or System::String

/// <summary>
/// COP4931::aCandlestick is a managed (C++/CLI) ref class that represents a candlestick (OHLCV) data point with 
/// a date/time, open, high, low, close prices, and volume. It provides a default constructor, a copy constructor,
/// a constructor from explicit OHLCV values and date, a constructor that parses a formatted text line, and a destructor.
/// </summary>

namespace COP4931
{
	/// <summary>
	/// Represents a candlestick (OHLC) data point with date, open, high, low, close, and volume.
	/// Provides constructors to create a default instance, copy an existing instance, construct 
	/// from explicit OHLCV values, or initialize from a formatted text line. 
	/// Includes a destructor for cleanup.
	/// </summary>
	public ref class aCandlestick {
	public:
		property DateTime date;        // Represents a DateTime property named date.
		property float open;		   // Represents a floating-point property named 'open'.
		property float high;           // Represents a floating-point 'high' value.
		property float low;			   // A floating-point property named 'low' that holds a low value.
		property float close;		   // Declares a floating-point property named "close".
		property unsigned long volume; // Represents a volume value stored as an unsigned long.

		/// <summary>
		/// This default constructor defines a function named aCandlestick 
		/// that takes no arguments & returns no value.
		/// </summary>
		aCandlestick() {};

		/// <summary>
		/// Constructs a new aCandlestick instance by copying data from the given source object.
		/// </summary>
		/// <param name="sourceCandlestick">A handle to the source aCandlestick from which to copy state.</param>
		aCandlestick(aCandlestick^ sourceCandlestick);

		/// <summary>
		/// Creates a candlestick data point containing open, high, low, close (OHLC) prices & volume 
		/// for a specific date/time.
		/// </summary>
		/// <param name="d">The date and time for the candlestick.</param>
		/// <param name="o">The opening price for the period.</param>
		/// <param name="h">The highest price during the period.</param>
		/// <param name="l">The lowest price during the period.</param>
		/// <param name="c">The closing price for the period.</param>
		/// <param name="v">The trade volume for the period.</param>
		aCandlestick(DateTime d, float o, float h, float l, float c, unsigned long v);
		

		/// <summary>
		/// Initializes an aCandlestick instance from a text line.
		/// </summary>
		/// <param name="line">A System::String^ containing the candlestick data in right order
		/// (for example, a CSV or otherwise formatted line) used to initialize the object.</param>
		aCandlestick(String^ line);

		/// <summary>
		/// Destructor for aCandlestick. Destroys the object & performs any required cleanup;
		/// currently a no-op because of no unmanaged resources held by this class. .
		/// </summary>
		~aCandlestick() {};
	};
}

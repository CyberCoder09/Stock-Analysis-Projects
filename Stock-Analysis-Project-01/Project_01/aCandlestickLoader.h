#pragma once // To ensure that this header file is included only once during compilation to avioid duplicate definitions. 
#include "aCandlestick.h" // Including declaration of aCandlestick class to create instances.

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;


namespace COP4931 
{
	/// <summary>
	/// Class to provide functions to load candlestick data from external sources. 
	/// This class only one static helper to read CSV files & create objects. 
	/// </summary>
	public ref class aCandlestickLoader 
	{ 
		public:
			/// <summary>
			/// Loading candlestick data from a CSV file which is expected to contain a header row
			/// with 6 values in order (date, open, high, low, close, volume). 
			/// </summary>
			/// <param name="filePath"> The path to the CSV to read. </param>
			/// <returns> A list called candlestick containing one candlestick instance per parsed row. </returns>
			static List<aCandlestick^>^ LoadFromCsv(String^ filePath);
	};
}


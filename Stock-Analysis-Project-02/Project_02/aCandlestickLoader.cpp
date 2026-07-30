#include "pch.h"                // Precompiled header to speed up build by pulling common system & CLR headers.
#include "aCandlestickLoader.h" // Including declaration of aCandlestickLoader class & LoadFromCsv() method. 
#include "aCandlestick.h"       // Including declaration of aCandlestick class to create instances. 

using namespace System;                       // namespace for String, DateTime, etc. 
using namespace System::Collections::Generic; // namespace for Generic collections like List.
using namespace System::IO;                   // namespace for file & stream input & output (IO).
using namespace System::Globalization;        // namespace for Parsing DateTime & number styles. 
using namespace COP4931;                      // namespace for Project. 

List<aSmartCandlestick^>^ ConvertToSmartCandlesticks(List<aCandlestick^>^ candlestickList)
{
	List<aSmartCandlestick^>^ smartList = gcnew List<aSmartCandlestick^>();
	for (int i = 0; i < candlestickList->Count; i++)
	{
		aCandlestick^ candleStick = candlestickList[i];
		aSmartCandlestick^ smartCandleStick = gcnew aSmartCandlestick(candleStick);
		smartList->Add(smartCandleStick);
	}
	return smartList;
}


/// <summary>
/// Loads candlestick data from a CSV located at <paramref name=filePath"/>.
/// Expects the CSV file to have a header, row, followed by rows with at least 6 values 
/// (date, open, high, low, close, volume) in that specific order
/// </summary>
/// <param name="filePath"> Path to CSV file to load </param>
/// <returns> returns list candlestickList containing candlesticks form the file. </returns>
List<aCandlestick^>^ aCandlestickLoader::LoadFromCsv(String^ filePath)
{
	array<wchar_t>^ separators = gcnew array<wchar_t>{ ',', '\"' }; // Set the separators

	// Create a list to fill data & return a list of candlesticks.
	List<aCandlestick^>^ candlestickList = gcnew List<aCandlestick^>();

	// Read all lines from the file into a sting array "lines".
	array<String^>^ lines = File::ReadAllLines(filePath);

	// Starting i at 1 to skip the header row, iterte through length of "lines" array. 
	for (int i = 1; i < lines->Length; i++)
	{
		// Read one line at time from "lines" array. 
		String^ line = lines[i];

		// Splitting CSV file lines into fields using separators & removing empty entries. 
		array<String^>^ values = line->Split(separators, StringSplitOptions::RemoveEmptyEntries);

		DateTime date = DateTime::Parse(values[0]); // Parse datetime for index position 0. 
		double open = Double::Parse(values[1]);		// Parse opening price for index position 1.
		double high = Double::Parse(values[2]);     // Parse high price for index position 2.
		double low = Double::Parse(values[3]);		// Parse low price for index position 3.
		double close = Double::Parse(values[4]);	// Parse closing price for index position 4.

		// Parse traded volume & using static_cast to avoid overflow for index position 5.
		unsigned long volume = static_cast<unsigned long>(Double::Parse(values[5]));

		// Create a new aCandlestick instance with parsed fields. 
		aCandlestick^ candlestick = gcnew aCandlestick(date, open, high, low, close, volume);
		//aCandlestick^ smartCandlestick = gcnew aSmartCandlestick(candlestick); // Create a new aSmartCandlestick instance by passing the created aCandlestick instance to its constructor.	
		// Add the constructed candlestick to the "candlestickList". 
		candlestickList->Add(candlestick);
	}

	return candlestickList; // Returns a list "candlestickList" with all candlestick details in it.
}
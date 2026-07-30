#include "pch.h"                // Precompiled header to speed up build by pulling common system & CLR headers.
#include "aCandlestickLoader.h" // Including declaration of aCandlestickLoader class & LoadFromCsv() method. 
#include "aCandlestick.h"       // Including declaration of aCandlestick class to create instances. 
#include "aSmartCandlestick.h"  // Including declaration of aSmartCandlestick class to create instances.

using namespace System;                       // namespace for String, DateTime, etc. 
using namespace System::Collections::Generic; // namespace for Generic collections like List.
using namespace System::IO;                   // namespace for file & stream input & output (IO).
using namespace System::Globalization;        // namespace for Parsing DateTime & number styles. 
using namespace COP4931;  

/// <summary>
/// 
/// </summary>
/// <param name="candlestickList"></param>
/// <returns></returns>
 List<aSmartCandlestick^>^ ConvertToSmartCandlesticks(List<aCandlestick^>^ candlestickList) // This function takes a list of aCandlestick objects and converts it into a list of aSmartCandlestick objects by iterating through each aCandlestick in the input list, creating a corresponding aSmartCandlestick using the constructor that accepts an aCandlestick, and adding it to the new list of aSmartCandlestick objects, which is then returned.
 {
 	List<aSmartCandlestick^>^ listOfSmartCandlesticks = gcnew List<aSmartCandlestick^>(); // Creates a new empty list to hold aSmartCandlestick objects converted from aCandlestick objects.
 	for (int i = 0; i < candlestickList->Count; i++)
 	{
 		aCandlestick^ candleStick = candlestickList[i]; // Retrieves the aCandlestick object at the current index from the input list to be converted into an aSmartCandlestick.
 		aSmartCandlestick^ smartCandleStick = gcnew aSmartCandlestick(candleStick); // Creates a new aSmartCandlestick object using the retrieved aCandlestick object.
 		listOfSmartCandlesticks->Add(smartCandleStick); // Adds the newly created aSmartCandlestick object to the listOfSmartCandlesticks.
 	}
 	return listOfSmartCandlesticks; // Returns the list of aSmartCandlestick objects that were created by converting each aCandlestick from the input list.
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
	// Create a list to fill data & return a list of candlesticks.
	List<aCandlestick^>^ candlestickList = gcnew List<aCandlestick^>();

	// Read all lines from the file into a sting array "lines".
	array<String^>^ lines = File::ReadAllLines(filePath);

	// Starting i at 1 to skip the header row, iterte through length of "lines" array. 
	for (int i = 1; i < lines->Length; i++)
	{
		// Read one line at time from "lines" array. 
		String^ line = lines[i]; // Get the current line from the array of lines read from the file, which contains the candlestick data for a specific date/time period, to be processed and converted into an aCandlestick object.

		// Create a new aCandlestick instance with parsed fields. 
		aCandlestick^ candlestick = gcnew aCandlestick(line);
		
		// Add the constructed candlestick to the "candlestickList". 
		candlestickList->Add(candlestick);
	}

	return candlestickList; // Returns a list "candlestickList" with all candlestick details in it.
}
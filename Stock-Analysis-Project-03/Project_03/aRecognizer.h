#pragma once
#include "aCandlestick.h"  // Including declaration of aCandlestick class to create instances.
#include "aSmartCandlestick.h"  // Including declaration of aSmartCandlestick class to create instances.
#include "aCandlestickLoader.h" // Including declaration of aCandlestickLoader class & LoadFromCsv() method.

using namespace System; // namespace for String, DateTime, etc.
using namespace System::Collections::Generic; // namespace for Generic collections like List.
using namespace System::Windows::Forms;

namespace COP4931
{
	public ref class aRecognizer abstract // class that inherits from aSmartCandlestick
	{
		public:
			property String^ patternName;
			property int patternSize;
			
			aRecognizer() 
			{
				// Default constructor for Recognizer class, currently empty as there are no specific initialization steps required.
			};

			/// <summary>
			/// Constructor that initializes an aRecognizer instance with a pattern name & size.
			/// </summary>
			/// <param name="name">The pattern name to assign to the instance's patternName property.</param>
			/// <param name="size">The pattern size to assign to the instance's patternSize property.</param>
			aRecognizer(String^ name, int size) 
			{
				patternName = name; // Initializes the patternName property with the provided name when a Recognizer object is created using this constructor.
				patternSize = size; // Initializes the patternSize property with the provided size when a Recognizer object is created using this constructor.			
			};

			// Pure virtual function to be implemented by derived classes to return the length of the pattern this Recognizer is designed to identify.
			virtual bool isMatch(List<aSmartCandlestick^>^ smartCandlestick) = 0; // Pure virtual function to be implemented by derived classes to determine if a given aSmartCandlestick matches the specific pattern this Recognizer is designed to identify.

			List<int>^ RecognizePattern(List<aSmartCandlestick^>^ smartCandlesticks) // This function takes a list of aSmartCandlestick objects and returns a new list containing only those that match the pattern defined by the isMatch() method. It iterates through each aSmartCandlestick in the input list, checks if it matches the pattern using isMatch(), and if it does, adds it to the results list, which is then returned.
			{

				//MessageBox::Show("Total candles: " + smartCandlesticks->Count.ToString());
				//MessageBox::Show("Pattern size: " + patternSize.ToString());	
				List<int>^ matches = gcnew List<int>(); // Creates a new empty list to hold aSmartCandlestick objects that match the pattern defined by this Recognizer.
				int n = patternSize; // Stores the pattern size in a local variable n for easier reference in the loop below.
				if (smartCandlesticks->Count < n)
				{
					return matches; // If the input list of aSmartCandlestick objects has fewer elements than the pattern length required by this Recognizer, returns the empty matches list immediately since it's impossible for any candlestick to match the pattern.
				}

				
				for (int i = patternSize-1; i <= smartCandlesticks->Count-n; i++) // Iterates through each aSmartCandlestick in the input list of smart candlesticks.
				{

					List<aSmartCandlestick^>^ window = smartCandlesticks->GetRange(i, n); // Retrieves the aSmartCandlestick at the current index from the input list to be evaluated against the pattern.
					if (isMatch(window)) // Calls the isMatch() method to check if the current aSmartCandlestick matches the specific pattern this Recognizer is designed to identify.
					{
						matches->Add(i); // If the current aSmartCandlestick matches the pattern, its index is added to the results list.
					}
				}
				return matches; // Returns the list of aSmartCandlestick objects that matched the pattern.
			}


			
			~aRecognizer()
			{
				// Destructor for Recognizer class, currently empty as there are no unmanaged resources to clean up.
			};
	};
};

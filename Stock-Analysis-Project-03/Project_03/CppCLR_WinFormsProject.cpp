#include "pch.h" // Precompiled header to speed up build by pulling common system & CLR headers.

using namespace System; // namespace for String, DateTime, etc.

// int main(array<System::String ^> ^args)
// {
//    return 0;
// }

#include "Form1.h" // Include the header file for the main form of the application, which contains the definition of the Form1 class.

using namespace System::Windows::Forms; // namespace for Forms UI classes like button, label, etc.

[STAThread] // Indicates that the COM threading model for the application is single-threaded apartment, which is necessary for Windows Forms applications to function properly, as it ensures that all UI components are accessed from the same thread.
int main() // The main entry point for the application, marked with the STAThread attribute to indicate that it uses a single-threaded apartment model, which is required for Windows Forms applications to function correctly.
{
	Application::EnableVisualStyles(); // Enables visual styles for the application, allowing it to use the current Windows theme for controls and rendering, resulting in a modern look and feel.
	Application::SetCompatibleTextRenderingDefault(false); // Sets the default text rendering engine for the application to be compatible with older versions of Windows Forms controls, ensuring consistent appearance across different environments.

	String^ filename = "ABBV_daily.csv"; // Defines a managed string variable named filename and initializes it with the value "ABBV_daily.csv", which is likely the name of a CSV file containing stock data that the application will load and display.
	DateTime startDate = DateTime(2021, 01, 28); // Creates a DateTime object named startDate representing January 28, 2021, which will be used as the starting point for filtering stock data by date in the application.
	DateTime endDate = DateTime(2021, 02, 28); // Creates a DateTime object named endDate representing February 28, 2021, which will be used as the ending point for filtering stock data by date in the application.

	Application::Run(gcnew CppCLRWinFormsProject::Form1(filename, startDate, endDate)); // Creates a new instance of the Form1 class, passing the filename, startDate, and endDate as arguments to its constructor, and starts the application's message loop to display the form and handle user interactions.
	
	
	return 0; // Returns 0 to indicate that the application has exited successfully without errors.
};
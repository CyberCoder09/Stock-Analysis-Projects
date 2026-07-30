#pragma once // To ensure that this header file is included only once during compilation to avioid duplicate definitions.
#include "aCandlestick.h"       // Including declaration of aCandlestick class to create instances.
#include "aCandlestickLoader.h" // Including declaration of aCandlestickLoader class & LoadFromCsv() method.
#include "aSmartCandlestick.h"  // Including declaration of aSmartCandlestick class to create instances. 
#include "aRecognizer.h"        // Including declaration of Recognizer class to create instances.
#include "recognizer_Bearish_Engulfing_Pattern.h" // Including declaration of recognizer_Bearish_Engulfing_Pattern class to create instances.
#include "recognizer_Bullish_Engulfing_Pattern.h" // Including declaration of recognizer_Bullish_Engulfing_Pattern class to create instances.
#include "recognizer_Engulfing_Pattern.h" // Including declaration of recognizer_Engulfing_Pattern class to create instances.
#include "recognizer_Marubozu.h" // Including declaration of recognizer_Marubozu class to create instances.
#include "recognizer_Bearish_Marubozu.h" // Including declaration of recognizer_Bearish_Marubozu class to create instances.
#include "recognizer_Bullish_Marubozu.h" // Including declaration of recognizer_Bullish_Marubozu class to create instances.

#include <cmath> // Include cmath for math functions like abs, max, min.

/// <summary>
/// Handles the OpenFileDialog_FileOk event: loads the selected CSV file(s),
/// parses and filters candlestick data according to the UI date range, 
/// updates internal lists, makes the Update Stock button visible,
/// & binds the filtered data to the data grid view.
/// </summary>
namespace CppCLRWinFormsProject {
	using namespace COP4931; // namespace for the aCandlestick and aCandlestickLoader classes.
	using namespace System; // namespace for fundamental types like String, DateTime, etc.
	using namespace System::ComponentModel; // namespace for classes used for component behavior & events.
	using namespace System::Collections;    // namespace for basic collection classes & interfaces. 
	using namespace System::Windows::Forms; // namespace for Forms UI classes like button, label, etc.
	using namespace System::Data;           // namespace for working with datasets & data binding.
	using namespace System::Drawing;        // namespace for classes for UI layout. 
	using namespace System::Windows::Forms::DataVisualization::Charting; // namespace for charting controls & related classes.
	using namespace System::Collections::Generic; // namespace for generic collection classes like List<T>.

	/// <summary>
	/// Main application form that displays candlestick data & provides controls for loading & filtering stock CSV files.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		/// <summary>
		/// Default constructor to call InitializeComponent() & setup UI controls. 
		/// </summary>
		Form1(void)
		{
			InitializeComponent(); // Calls designer-generated method to initialize and lay out all UI controls.
			InitializeRecognizers();// Calls a custom method to initialize recognizers.

		}
		Form1(String^ filename, DateTime startDate, DateTime endDate)
		{
			InitializeComponent(); // Calls designer-generated method to initialize & lay out all UI controls.
			InitializeRecognizers();// Calls a custom method to initialize recognizers.
			HandleData(filename, startDate, endDate); // Calls a custom method to load, filter, & bind data for the given file and date range.
		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components) // Checks if the components container exists before attempting to delete it.
			{
				delete components; // Releases all child components managed by the container to free memory.
			}
		}

		/// <summary>
		/// Managed handle to a Windows Forms Button control used for updating stock data display.
		/// </summary>
	private: System::Windows::Forms::Button^ button_updateStock;

		   /// <summary>
		   /// Reference to a Windows Forms Button control used to trigger loading of a stock CSV file.
		   /// </summary>
	private: System::Windows::Forms::Button^ button_loadStock;

		   /// <summary>
		   /// Managed handle to a label control that represents the start date label.
		   /// </summary>
	private: System::Windows::Forms::Label^ label_startDate; // Handle to a Label control used to display or label the start date.

		   /// <summary>
		   /// Handle to a Label control used to display or label the end date.
		   /// </summary>
	private: System::Windows::Forms::Label^ label_endDate;

		   /// <summary>
		   /// Handle to a Windows Forms DateTimePicker control representing the start date selection.
		   /// </summary>
	private: System::Windows::Forms::DateTimePicker^ DateTimePicker_startDate;

		   /// <summary>
		   /// Handle to a DateTimePicker control used to represent or select the end date.
		   /// </summary>
	private: System::Windows::Forms::DateTimePicker^ DateTimePicker_endDate;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog_LoadStock;

		   /// <summary>
		   /// Field that holds a managed OpenFileDialog used to prompt the user to select a CSV file to load.
		   /// </summary>


		// Internal storage for all loaded candlesticks from the selected CSV file.
	private: List<aCandlestick^>^ listOfCandlesticks;
		   // Internal storage for the date-filtered subset of listOfCandlesticks.
	private: List<aCandlestick^>^ filteredListOfCandlesticks;
	private: List<aSmartCandlestick^>^ smartCandlestick; // Internal storage for the list of aSmartCandlestick objects that match the selected pattern from the combo box.
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart_candlesticks;
	private: System::Windows::Forms::ComboBox^ comboBox_PatternSelector; // Handle to a ComboBox control used to select different candlestick patterns for recognition and display.
	private: System::Windows::Forms::CheckBox^ checkBox_KeepAnnotations;
	private: System::Windows::Forms::Button^ button1;


		   /// <summary>
		   /// Required designer variable that holds the collection of all non-visual components on the form.
		   /// </summary>
		   System::ComponentModel::Container^ components; // A container for components that are not directly visual controls, used by the designer to manage resources.

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// This method initializes all controls & configures the user interface (UI) properties. 
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			   System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			   System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			   System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			   System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			   this->button_updateStock = (gcnew System::Windows::Forms::Button());
			   this->button_loadStock = (gcnew System::Windows::Forms::Button());
			   this->label_startDate = (gcnew System::Windows::Forms::Label());
			   this->label_endDate = (gcnew System::Windows::Forms::Label());
			   this->DateTimePicker_startDate = (gcnew System::Windows::Forms::DateTimePicker());
			   this->DateTimePicker_endDate = (gcnew System::Windows::Forms::DateTimePicker());
			   this->openFileDialog_LoadStock = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->chart_candlesticks = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			   this->comboBox_PatternSelector = (gcnew System::Windows::Forms::ComboBox());
			   this->checkBox_KeepAnnotations = (gcnew System::Windows::Forms::CheckBox());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_candlesticks))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // button_updateStock
			   // 
			   this->button_updateStock->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->button_updateStock->Location = System::Drawing::Point(900, 450);
			   this->button_updateStock->Name = L"button_updateStock";
			   this->button_updateStock->Size = System::Drawing::Size(140, 35);
			   this->button_updateStock->TabIndex = 2;
			   this->button_updateStock->Text = L"Update Stock";
			   this->button_updateStock->UseVisualStyleBackColor = true;
			   this->button_updateStock->Visible = false;
			   this->button_updateStock->Click += gcnew System::EventHandler(this, &Form1::Button_UpdateStock_Click);
			   // 
			   // button_loadStock
			   // 
			   this->button_loadStock->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->button_loadStock->Location = System::Drawing::Point(1100, 450);
			   this->button_loadStock->Name = L"button_loadStock";
			   this->button_loadStock->Size = System::Drawing::Size(140, 35);
			   this->button_loadStock->TabIndex = 0;
			   this->button_loadStock->Text = L"Load Stock";
			   this->button_loadStock->UseVisualStyleBackColor = true;
			   this->button_loadStock->Click += gcnew System::EventHandler(this, &Form1::Button_LoadStock_Click);
			   // 
			   // label_startDate
			   // 
			   this->label_startDate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->label_startDate->AutoSize = true;
			   this->label_startDate->Location = System::Drawing::Point(12, 426);
			   this->label_startDate->Name = L"label_startDate";
			   this->label_startDate->Size = System::Drawing::Size(91, 20);
			   this->label_startDate->TabIndex = 4;
			   this->label_startDate->Text = L"Start Date: ";
			   // 
			   // label_endDate
			   // 
			   this->label_endDate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->label_endDate->AutoSize = true;
			   this->label_endDate->Location = System::Drawing::Point(327, 437);
			   this->label_endDate->Name = L"label_endDate";
			   this->label_endDate->Size = System::Drawing::Size(85, 20);
			   this->label_endDate->TabIndex = 5;
			   this->label_endDate->Text = L"End Date: ";
			   // 
			   // DateTimePicker_startDate
			   // 
			   this->DateTimePicker_startDate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->DateTimePicker_startDate->CustomFormat = L"dddd, MMMM d, yyyy";
			   this->DateTimePicker_startDate->Location = System::Drawing::Point(12, 459);
			   this->DateTimePicker_startDate->Name = L"DateTimePicker_startDate";
			   this->DateTimePicker_startDate->Size = System::Drawing::Size(300, 26);
			   this->DateTimePicker_startDate->TabIndex = 6;
			   this->DateTimePicker_startDate->Value = System::DateTime(2021, 1, 28, 0, 0, 0, 0);
			   // 
			   // DateTimePicker_endDate
			   // 
			   this->DateTimePicker_endDate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->DateTimePicker_endDate->CustomFormat = L"dddd, MMMM d, yyyy";
			   this->DateTimePicker_endDate->Location = System::Drawing::Point(318, 460);
			   this->DateTimePicker_endDate->Name = L"DateTimePicker_endDate";
			   this->DateTimePicker_endDate->Size = System::Drawing::Size(300, 26);
			   this->DateTimePicker_endDate->TabIndex = 7;
			   this->DateTimePicker_endDate->Value = System::DateTime(2021, 2, 28, 0, 0, 0, 0);
			   // 
			   // openFileDialog_LoadStock
			   // 
			   this->openFileDialog_LoadStock->DefaultExt = L"csv";
			   this->openFileDialog_LoadStock->FileName = L"ABBV_daily";
			   this->openFileDialog_LoadStock->Filter = L"All Stocks|*.csv|yearly|*_yearly.csv|monthly|*_monthly.csv|weekly|*_weekly.csv|da"
				   L"ily|*_daily.csv";
			   this->openFileDialog_LoadStock->InitialDirectory = L"C:\\Users\\naren\\Desktop\\Stock_Data";
			   this->openFileDialog_LoadStock->Multiselect = true;
			   this->openFileDialog_LoadStock->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog_loadStock_FileOk);
			   // 
			   // chart_candlesticks
			   // 
			   this->chart_candlesticks->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->chart_candlesticks->BackImageAlignment = System::Windows::Forms::DataVisualization::Charting::ChartImageAlignmentStyle::BottomLeft;
			   chartArea1->AxisY->IsStartedFromZero = false;
			   chartArea1->Name = L"ChartArea_OHLC";
			   chartArea2->AlignWithChartArea = L"ChartArea_OHLC";
			   chartArea2->Name = L"ChartArea_Volume";
			   this->chart_candlesticks->ChartAreas->Add(chartArea1);
			   this->chart_candlesticks->ChartAreas->Add(chartArea2);
			   legend1->Name = L"Legend1";
			   this->chart_candlesticks->Legends->Add(legend1);
			   this->chart_candlesticks->Location = System::Drawing::Point(-5, -2);
			   this->chart_candlesticks->Name = L"chart_candlesticks";
			   series1->ChartArea = L"ChartArea_OHLC";
			   series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Candlestick;
			   series1->CustomProperties = L"PriceUpColor=0\\, 192\\, 0, PriceDownColor=Red";
			   series1->IsXValueIndexed = true;
			   series1->Legend = L"Legend1";
			   series1->Name = L"Series_OHLC";
			   series1->XValueMember = L"date";
			   series1->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::DateTime;
			   series1->YValueMembers = L"high, low, open, close";
			   series1->YValuesPerPoint = 4;
			   series2->ChartArea = L"ChartArea_Volume";
			   series2->IsXValueIndexed = true;
			   series2->Legend = L"Legend1";
			   series2->Name = L"Series_Volume";
			   series2->XValueMember = L"date";
			   series2->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::DateTime;
			   series2->YValueMembers = L"volume";
			   this->chart_candlesticks->Series->Add(series1);
			   this->chart_candlesticks->Series->Add(series2);
			   this->chart_candlesticks->Size = System::Drawing::Size(1316, 392);
			   this->chart_candlesticks->TabIndex = 8;
			   this->chart_candlesticks->Text = L"chart1";
			   // 
			   // comboBox_PatternSelector
			   // 
			   this->comboBox_PatternSelector->AllowDrop = true;
			   this->comboBox_PatternSelector->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->comboBox_PatternSelector->FormattingEnabled = true;
			   this->comboBox_PatternSelector->Location = System::Drawing::Point(633, 458); // Sets the location of the combo box control to coordinates (633, 458) within the form, positioning it near the "Keep Annotations" checkbox for easy access when selecting patterns to recognize and annotate on the chart.
			   this->comboBox_PatternSelector->Name = L"comboBox_PatternSelector";
			   this->comboBox_PatternSelector->Size = System::Drawing::Size(237, 28);
			   this->comboBox_PatternSelector->TabIndex = 9;
			   this->comboBox_PatternSelector->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox_PatternSelection); // Subscribes to the SelectedIndexChanged event of the combo box control, allowing the application to respond when the user selects a different pattern from the dropdown list, which may trigger pattern recognition and annotation updates on the chart based on the newly selected pattern.
			   // 
			   // checkBox_KeepAnnotations
			   // 
			   this->checkBox_KeepAnnotations->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right)); // Sets the Anchor property of the checkbox control to anchor it to all sides of the form, allowing it to maintain its position relative to the form's edges when the form is resized.
			   this->checkBox_KeepAnnotations->AutoSize = true; // Sets the AutoSize property of the checkbox control to true, allowing it to automatically adjust its size based on the content (text) it contains, ensuring that the entire label "Keep Annotations" is visible without being cut off.
			   this->checkBox_KeepAnnotations->Location = System::Drawing::Point(633, 421); // Sets the location of the checkbox control to coordinates (633, 421) within the form, positioning it near the pattern selector combo box for easy access when selecting patterns to recognize and annotate on the chart.
			   this->checkBox_KeepAnnotations->Name = L"checkBox_KeepAnnotations"; // Sets the Name property of the checkbox control to "checkBox_KeepAnnotations", which can be used to reference this control in the code-behind for event handling and other interactions.
			   this->checkBox_KeepAnnotations->Size = System::Drawing::Size(162, 24); // Sets the size of the checkbox control to 162 pixels in width and 24 pixels in height, providing enough space to display the text "Keep Annotations" next to the checkbox.
			   this->checkBox_KeepAnnotations->TabIndex = 10; // Sets the tab index for the checkbox control to 10, determining its position in the tab order when navigating through controls using the keyboard.
			   this->checkBox_KeepAnnotations->Text = L"Keep Annotations";// Sets the text displayed next to the checkbox to "Keep Annotations", indicating that when checked, existing annotations on the chart will be preserved when new patterns are recognized and annotated.
			   this->checkBox_KeepAnnotations->UseVisualStyleBackColor = true; // Sets the UseVisualStyleBackColor property of the checkbox control to true, allowing it to use the visual styles defined by the operating system for its background, ensuring a consistent look and feel with other controls on the form.
			   this->checkBox_KeepAnnotations->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox_KeepAnnotations_CheckedChanged); // Subscribes to the CheckedChanged event of the checkbox control, allowing the application to respond when the user checks or unchecks the "Keep Annotations" option, which may affect how pattern recognition results are displayed on the chart.
		
			  
			   // 
			   // Form1
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->AutoSize = true;
			   this->ClientSize = System::Drawing::Size(1300, 500);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->checkBox_KeepAnnotations);
			   this->Controls->Add(this->comboBox_PatternSelector);
			   this->Controls->Add(this->chart_candlesticks);
			   this->Controls->Add(this->DateTimePicker_endDate);
			   this->Controls->Add(this->DateTimePicker_startDate);
			   this->Controls->Add(this->label_endDate);
			   this->Controls->Add(this->label_startDate);
			   this->Controls->Add(this->button_loadStock);
			   this->Controls->Add(this->button_updateStock);
			   this->Name = L"Form1";
			   this->Text = L"Form1";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_candlesticks))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }

#pragma endregion // End of designer-generated code region.

		   /// <summary>
		   /// Handles the Load Stock button click event by opening the file dialog
		   /// so the user can browse and select a stock CSV file to load.
		   /// </summary>
		   /// <param name="sender">The source of the event (the Load Stock button).</param>
		   /// <param name="e">Standard event arguments for the click event.</param>
	private: System::Void Button_LoadStock_Click(System::Object^ sender, System::EventArgs^ e)
	{
		openFileDialog_LoadStock->ShowDialog(); // Opens the OpenFileDialog window so the user can browse for and select a CSV file.
	}

		   /// <summary>
		   /// Event handler invoked when the OpenFileDialog 'FileOk' event is raised. 
		   /// Calls DisplayData to load, filter, & display data from the selected file path.
		   /// </summary>
		   /// <param name="sender">The source of the event, typically the OpenFileDialog that raised the FileOk event.</param>
		   /// <param name="e">Event data (System::ComponentModel::CancelEventArgs^) for the FileOk event; provides a Cancel property that can be used to cancel the operation.</param>
	private: System::Void openFileDialog_loadStock_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
	{
		DisplayData(); // Calls a method to load, filter, and display data from the selected file path.
	}

		   /// <summary>
		   /// Handles the Update Stock button click event by calling a method to filter the stored candlesticks
		   /// based on the current values of the start and end date pickers, and then updates the data grid view with the filtered list.
		   /// </summary>
		   /// <param name="sender">The source of the event (the Update Stock button).</param>
		   /// <param name="e">Standard event arguments for the click event.</param>
	private: System::Void Button_UpdateStock_Click(System::Object^ sender, System::EventArgs^ e)
	{
		chart_candlesticks->Annotations->Clear(); // Clears any existing annotations from the chart to prepare for new data visualization.
		UpdateStockData(); // Calls a method to filter the stored candlesticks by the start & end date pickers and update the data grid view with the filtered list.
	}

	private: aRecognizer^ createRecognizer(String^ patternName)
	{
		if (patternName == "Marubozu")
		{
			return gcnew recognizer_Marubozu(); // If the selected pattern is "Marubozu", creates a new instance of the recognizer_Marubozu class and returns it.
		}

		if (patternName == "Bearish Marubozu")
		{
			return gcnew recognizer_Bearish_Marubozu(); // If the selected pattern is "Bearish Marubozu", creates a new instance of the recognizer_Bearish_Marubozu class and returns it.
		}

		if (patternName == "Bullish Marubozu")
		{
			return gcnew recognizer_Bullish_Marubozu(); // If the selected pattern is "Bullish Marubozu", creates a new instance of the recognizer_Bullish_Marubozu class and returns it.
		}

		if (patternName == "Engulfing Pattern")
		{
			return gcnew recognizer_Engulfing_Pattern(); // If the selected pattern is "Bearish Engulfing", creates a new instance of the recognizer_Bearish_Engulfing_Pattern class and returns it.
		}

		if (patternName == "Bearish Engulfing Pattern")
		{
			return gcnew recognizer_Bearish_Engulfing_Pattern(); // If the selected pattern is "Bearish Engulfing", creates a new instance of the recognizer_Bearish_Engulfing_Pattern class and returns it.
		}

		if (patternName == "Bullish Engulfing Pattern")
		{
			return gcnew recognizer_Bullish_Engulfing_Pattern(); // If the selected pattern is "Bullish Engulfing", creates a new instance of the recognizer_Bullish_Engulfing_Pattern class and returns it.
		}

		return nullptr;
	}

	

		   /// <summary>
		   /// Returns a new list containing candlesticks from loc whose date falls within the inclusive range [startDate, endDate].
		   /// </summary>
		   /// <param name="listOfCandlesticks">The source list of aCandlestick objects to filter, expected to be sorted ascending by date.</param>
		   /// <param name="startDate">Inclusive start of the date range to include.</param>
		   /// <param name="endDate">Inclusive end of the date range; scanning stops once this date is reached.</param>
		   /// <returns>A new List of aCandlestick objects whose dates fall within [startDate, endDate], in original order.</returns>
	public: List<aCandlestick^>^ filterCandlesticks(List<aCandlestick^>^ listOfCandlesticks, DateTime startDate, DateTime endDate)
	{
		List<aCandlestick^>^ filteredListOfCandlesticks = gcnew List<aCandlestick^>(); // Creates a new empty list to hold candlesticks that fall within the date range.

		for (int i = 0; i < listOfCandlesticks->Count; i++) // Iterates through every candlestick in the source list from first to last.
		{
			aCandlestick^ candleStick = listOfCandlesticks[i]; // Retrieves the candlestick at the current index for date comparison.

			DateTime date = candleStick->date; // Extracts the date property from the current candlestick for range checking.

			if (date >= startDate && date <= endDate) // Checks if the candlestick date falls within the inclusive [startDate, endDate] range.
			{
				filteredListOfCandlesticks->Add(candleStick); // Adds the in-range candlestick to the filtered output list.
			}

			if (date >= endDate) // Checks if the current date has reached or passed the end date.
				break;           // Stops iterating early since all remaining dates will be beyond the range.
		}

		return filteredListOfCandlesticks; // Returns the filtered list containing only candlesticks within the selected date range.
	}

		  /// <summary>
		  /// Loads candlestick data from the specified CSV file, filters it based on the provided date range 
		  /// & binds the filtered data to the chart control for visualization. 
		  /// It determines the overall minimum low and maximum high values from the filtered data. 
		  /// </summary>
		  /// <param name="filename"> The path of the CSV to load the data from. </param>
		  /// <param name="startDate"> The date specifying the start date for fltering. </param>
		  /// <param name="endDate"> The date specifying the end date for fltering. </param> 



	
	private: void HandleData(String^ filename, DateTime startDate, DateTime endDate)
	{
		this->Text = filename; // Sets Form's caption to that the file name
		this->listOfCandlesticks = aCandlestickLoader::LoadFromCsv(filename); // Loads list of candlestick object one by one for index position i
		this->filteredListOfCandlesticks = this->filterCandlesticks(this->listOfCandlesticks, startDate, endDate); // Calls a function that opens a window with filtered list candlesticks 

		if (this->filteredListOfCandlesticks->Count == 0) // Checks if the filtered list of candlesticks is empty, meaning no candlesticks fall within the selected date range.
		{
			return; // If there are no candlesticks in the filtered list, exits the function early to avoid further processing or errors.
		}

		candlestickBindingData(filteredListOfCandlesticks); // Binds the filtered list of candlesticks to the chart control for visualization.
		this->button_updateStock->Visible = true; // Makes the Update Stock visible

		double minLow = filteredListOfCandlesticks[0]->low; // Initializes minLow and maxHigh to the low and high of the first candlestick in the filtered list, respectively.
		double maxHigh = filteredListOfCandlesticks[0]->high; // Initializes minLow and maxHigh to the low and high of the first candlestick in the filtered list, respectively.

		for (int i = 0; i < filteredListOfCandlesticks->Count; i++) // Iterates through each candlestick in the filtered list to find the overall minimum low & maximum high values.
		{
			aCandlestick^ candlestick = this->filteredListOfCandlesticks[i]; // Retrieves the candlestick at the current index for high/low comparison.

			if (candlestick->high > maxHigh) // Checks if the current candlestick's high is higher than the current maximum high value.
			{
				maxHigh = candlestick->high; // Update maxHigh if the current candlestick's high is higher than the current maxHigh.
			}

			if (candlestick->low < minLow) // Checks if the current candlestick's low is lower than the current minimum low value.
			{
				minLow = candlestick->low; // Update minLow if the current candlestick's low is lower than the current minLow.
			}
		}
	}

	private: System::Void comboBox_PatternSelection(System::Object^ sender, System::EventArgs^ e)
	{
		ShowSelectedPattern();
	}

		   /// <summary>
		   /// This function takes a list of filtered candlesticks & binds it with a candlestick object
		   /// </summary>
		   /// <param name="filteredListOfCandlesticks">The filtered list of aCandlestick object</param>
	private: void candlestickBindingData(List<aCandlestick^>^ filteredListOfCandlesticks)
	{
		// Sets the data source of the chart control to the provided list of filtered candlesticks, enabling data binding for visualization.
		chart_candlesticks->DataSource = filteredListOfCandlesticks; // Sets the data source of the chart control to the provided list of filtered candlesticks, enabling data binding for visualization.
		chart_candlesticks->DataBind(); // Binds the data from the filtered list to the chart control, causing it to update its display based on the new data source.
		chart_candlesticks->Show();     // Makes the chart control visible to display the bound candlestick data.
	}

		   /// <summary>
		   /// Loads candlestick data from the file(s) selected in openFileDialog_LoadStock, 
		   /// filters the data by the start & end dates taken from the DateTimePicker controls, 
		   /// binds the filtered data to the chart control, and makes the Update Stock button visible. 
		   /// If multiple files are selected, creates and shows an additional Form1 for each extra file 
		   /// & repeats the load/filter/bind steps for each.
		   /// </summary>
	public: void DisplayData()
	{
		String^ filename = openFileDialog_LoadStock->FileName; // Retrieves the full file path of the CSV file the user selected in the dialog.
		Text = filename; // Updates the form title bar to show the selected file's name without its extension.

		DateTime startDate = this->DateTimePicker_startDate->Value; // Reads the start date the user selected in the start DateTimePicker.
		DateTime endDate = this->DateTimePicker_endDate->Value;     // Reads the end date the user selected in the end DateTimePicker.

		aCandlestickLoader^ candlestickLoader = gcnew aCandlestickLoader(); // Creates a new instance of the loader (used for object-oriented access if needed).
		this->listOfCandlesticks = aCandlestickLoader::LoadFromCsv(filename); // Calls the static LoadFromCsv method to parse all candlestick rows from the selected CSV file.
		this->filteredListOfCandlesticks = filterCandlesticks(listOfCandlesticks, startDate, endDate); // Filters the full candlestick list to only those within the selected date range. 
		candlestickBindingData(filteredListOfCandlesticks); // Sets the data source of the chart control to the filtered list of candlesticks, allowing it to display the data.
		button_updateStock->Visible = true; // Makes the Update Stock button visible now that a file has been successfully loaded.

		// If the user selected multiple files, this loop will create a new form for each additional file & load its data in the same way as the first file.
		for (int i = 1; i < openFileDialog_LoadStock->FileNames->Length; i++)
		{
			String^ filenameI = openFileDialog_LoadStock->FileNames[i]; // Retrieves the full file path of the i-th CSV file selected by the user in the dialog.
			Form1^ newForm = gcnew Form1(filenameI, startDate, endDate); //Creates a new instance of a Form object
			newForm->Text = filenameI; // Sets Form's caption to that the file name
			aCandlestickLoader^ candlestickLoader = gcnew aCandlestickLoader(); // Creates a new instance of the loader (used for object-oriented access if needed).
			newForm->listOfCandlesticks = aCandlestickLoader::LoadFromCsv(filenameI); // Calls the static LoadFromCsv method to parse all candlestick rows from the selected CSV file.
			newForm->filteredListOfCandlesticks = newForm->filterCandlesticks(newForm->listOfCandlesticks, startDate, endDate); // Filters the full candlestick list to only those within the selected date range.
			newForm->chart_candlesticks->DataSource = newForm->filteredListOfCandlesticks; // Sets the data source of the chart control on the new form to the filtered list of candlesticks, allowing it to display the data.
			newForm->chart_candlesticks->DataBind(); // Binds the filtered list of candlesticks to the chart control on the new form to update its display.
			newForm->button_updateStock->Visible = true; // Makes the Update Stock button visible now that a file has been successfully loaded.
			newForm->Show(); // Displays the new form to the user.
		}
	}

		  /// <summary>
		  /// Updates the chart's candlestick data based on the user-selected start & end dates by 
		  /// filtering the full candlestick list and rebinding the filtered data to the chart control.
		  /// </summary>
	public: void UpdateStockData()
	{
		DateTime startDate = this->DateTimePicker_startDate->Value; // Reads the start date the user selected in the start DateTimePicker.
		DateTime endDate = this->DateTimePicker_endDate->Value;     // Reads the end date the user selected in the end DateTimePicker.

		this->filteredListOfCandlesticks = filterCandlesticks(this->listOfCandlesticks, startDate, endDate); // Filters the full candlestick list to only those within the selected date range. 
		candlestickBindingData(filteredListOfCandlesticks); // Sets the data source of the chart control to the filtered list of candlesticks, allowing it to display the data.
	}

		  /// <summary>
		  /// Loads the available candlestick patterns into the pattern selector combo box.
		  /// </summary>
	public: void LoadComboBox()
	{
		comboBox_PatternSelector->Items->Clear(); // Clears all existing items from the pattern selector combo box to prepare for adding new options.

		for (int i = 0; i < listOfRecognizers->Count; i++) // Iterates through the list of recognizer objects to add their pattern names as options in the combo box.
		{
			comboBox_PatternSelector->Items->Add(listOfRecognizers[i]->patternName); // Adds the pattern name of each recognizer in the list as an option in the combo box.
		}
	}

	
	 // Create a list of Recognizers & add one of each type to the list
	public: List<aRecognizer^>^ listOfRecognizers;

	public: void InitializeRecognizers()
	{
		listOfRecognizers = gcnew List<aRecognizer^>();
		listOfRecognizers->Add(gcnew recognizer_Marubozu());
		listOfRecognizers->Add(gcnew recognizer_Bullish_Marubozu());
		listOfRecognizers->Add(gcnew recognizer_Bearish_Marubozu());
		listOfRecognizers->Add(gcnew recognizer_Engulfing_Pattern());
		listOfRecognizers->Add(gcnew recognizer_Bullish_Engulfing_Pattern());
		listOfRecognizers->Add(gcnew recognizer_Bearish_Engulfing_Pattern());

		LoadComboBox();
	}

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

	public: void ClearPatternAnnotations()
	{
		chart_candlesticks->Annotations->Clear();
	}

	/// <summary>
	/// Adds text annotations to the chart for the specified pattern matches.
	/// </summary>
	/// <param name="matchIndexes">A list of indexes where the pattern was recognized.</param>
	/// <param name="patternName">The name of the recognized pattern.</param>
	public: void AddTextAnnotations(List<int>^ matchIndexes, String^ patternName)
	{
		chart_candlesticks->Annotations->Clear(); // Clears any existing annotations from the chart to prepare for adding new ones based on the current pattern matches.

		Series^ ohlcSeries = chart_candlesticks->Series["Series_OHLC"]; // Retrieves the OHLC series from the chart control, which contains the data points corresponding to the candlestick data. This is necessary to anchor the annotations to the correct data points on the chart.

		for (int i = 0; i < matchIndexes->Count; i++)
		{
			int pointIndex = matchIndexes[i]; // Retrieves the index of the data point where the pattern was recognized from the matchIndexes list.

			if (pointIndex < 0 || pointIndex >= ohlcSeries->Points->Count)
				continue;

			DataPoint^ dataPoint = ohlcSeries->Points[pointIndex]; // Retrieves the DataPoint object from the OHLC series at the specified index, which represents the specific point on the chart where the pattern was recognized. This DataPoint will be used to anchor the annotation so that it appears at the correct location on the chart corresponding to the recognized pattern.

			TextAnnotation^ annotation = gcnew TextAnnotation(); // Creates a new TextAnnotation object to display the pattern name on the chart.
			annotation->Text = patternName; // Sets the text of the annotation to the name of the recognized pattern.
			annotation->AnchorDataPoint = dataPoint; // Anchors the annotation to the specific data point where the pattern was recognized.
			annotation->AnchorAlignment = ContentAlignment::BottomCenter;
			annotation->AnchorOffsetY = -5; // Pushes it slightly above the candle
			annotation->ClipToChartArea = "ChartArea_OHLC"; // Ensures the annotation is clipped to the OHLC chart area so it doesn't overflow into other areas of the chart.
			annotation->ForeColor = Color::Red; // Sets the text color of the annotation to red for visibility.
			annotation->BackColor = Color::Yellow;   // make it obvious first
			annotation->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold); // Sets the font of the annotation text to Arial, size 10, and bold for better visibility.

			chart_candlesticks->Annotations->Add(annotation); // Adds the configured annotation to the chart's Annotations collection so it will be displayed on the chart.
		}

		chart_candlesticks->Invalidate(); // Invalidates the chart control to trigger a repaint, ensuring that the new annotations are rendered on the chart immediately.
		chart_candlesticks->Refresh(); // Refreshes the chart control to apply the invalidation and update the display.
	}
	public: void ShowSelectedPattern()
	{
		if (comboBox_PatternSelector->SelectedIndex < 0)
			return;

		if (filteredListOfCandlesticks == nullptr || filteredListOfCandlesticks->Count == 0)
			return; 

		int selectedIndex = comboBox_PatternSelector->SelectedIndex;

		if (selectedIndex < 0 || selectedIndex >= listOfRecognizers->Count)
			return;

		aRecognizer^ selectedRecognizer = listOfRecognizers[selectedIndex];

		List<aSmartCandlestick^>^ smartCandlesticks = ConvertToSmartCandlesticks(filteredListOfCandlesticks);
		
		List<int>^ matchIndexes = selectedRecognizer->RecognizePattern(smartCandlesticks);

		AddTextAnnotations(matchIndexes, selectedRecognizer->patternName);
	}
	private: System::Void checkBox_KeepAnnotations_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		if (!checkBox_KeepAnnotations->Checked)
		{
			ClearPatternAnnotations(); // Clear annotations when "Keep Annotations" is unchecked
		}
	}

};
}

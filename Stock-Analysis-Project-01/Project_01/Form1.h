#pragma once // To ensure that this header file is included only once during compilation to avioid duplicate definitions.
#include "aCandlestick.h"       // Including declaration of aCandlestick class to create instances.
#include "aCandlestickLoader.h" // Including declaration of aCandlestickLoader class & LoadFromCsv() method.

/// <summary>
/// Handles the OpenFileDialog_FileOk event: loads the selected CSV file(s),
/// parses and filters candlestick data according to the UI date range, 
/// updates internal lists, makes the Update Stock button visible,
/// & binds the filtered data to the data grid view.
/// </summary>
namespace CppCLRWinFormsProject {
	using namespace COP4931;
	using namespace System;
	using namespace System::ComponentModel; // namespace for classes used for component behavior & events.
	using namespace System::Collections;    // namespace for basic collection classes & interfaces. 
	using namespace System::Windows::Forms; // namespace for Forms UI classes like button, label, etc.
	using namespace System::Data;           // namespace for working with datasets & data binding.
	using namespace System::Drawing;        // namespace for classes for UI layout. 

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
		/// Managed handle to a DataGridView control used to display tabular candlestick data.
		/// </summary>
	private: System::Windows::Forms::DataGridView^ dataGridView_dataDisplay;

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
	private: System::Windows::Forms::Label^ label_startDate;

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

		   /// <summary>
		   /// Field that holds a managed OpenFileDialog used to prompt the user to select a CSV file to load.
		   /// </summary>
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog_Load;

		   // Internal storage for all loaded candlesticks from the selected CSV file.
	private: List<aCandlestick^>^ listOfCandlesticks;

		   // Internal storage for the date-filtered subset of listOfCandlesticks.
	private: List<aCandlestick^>^ filteredList;

		   /// <summary>
		   /// Required designer variable that holds the collection of all non-visual components on the form.
		   /// </summary>
		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// This method initializes all controls & configures the user interface (UI) properties. 
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   // Instantiate all UI controls before configuring their properties.
			   this->dataGridView_dataDisplay = (gcnew System::Windows::Forms::DataGridView());
			   this->button_updateStock = (gcnew System::Windows::Forms::Button());
			   this->button_loadStock = (gcnew System::Windows::Forms::Button());
			   this->label_startDate = (gcnew System::Windows::Forms::Label());
			   this->label_endDate = (gcnew System::Windows::Forms::Label());
			   this->DateTimePicker_startDate = (gcnew System::Windows::Forms::DateTimePicker());
			   this->DateTimePicker_endDate = (gcnew System::Windows::Forms::DateTimePicker());
			   this->openFileDialog_Load = (gcnew System::Windows::Forms::OpenFileDialog());

			   // Begin initialization of the DataGridView to suppress redraws during setup.
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_dataDisplay))->BeginInit();

			   // Temporarily suspends layout logic while controls are being initialized for better performance.
			   this->SuspendLayout();

			   // 
			   // dataGridView_dataDisplay
			   // 
			   this->dataGridView_dataDisplay->AllowUserToAddRows = false; // Prevents users from manually adding new rows to the grid.
			   this->dataGridView_dataDisplay->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( // Anchors all four edges so the grid resizes with the form.
				   (((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
					   | System::Windows::Forms::AnchorStyles::Left)
					   | System::Windows::Forms::AnchorStyles::Right));
			   this->dataGridView_dataDisplay->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;      // Makes all columns share the available width equally.
			   this->dataGridView_dataDisplay->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::DisplayedCells;  // Sizes rows to fit displayed cell content, removing empty overflow rows.
			   this->dataGridView_dataDisplay->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize; // Automatically adjusts column header height to fit content.
			   this->dataGridView_dataDisplay->EditMode = System::Windows::Forms::DataGridViewEditMode::EditOnEnter; // Begins cell editing as soon as a cell receives focus.
			   this->dataGridView_dataDisplay->GridColor = System::Drawing::SystemColors::Control; // Sets the grid line color to match the system control color.
			   this->dataGridView_dataDisplay->Location = System::Drawing::Point(-5, -2);          // Positions the grid slightly off the top-left edge to eliminate border gap.
			   this->dataGridView_dataDisplay->Name = L"dataGridView_dataDisplay";                 // Sets the internal name used to reference this control in code.
			   this->dataGridView_dataDisplay->RowHeadersWidth = 62;                               // Sets the width of the row header column on the left side of the grid.
			   this->dataGridView_dataDisplay->RowTemplate->Height = 28;                           // Sets the default height for each data row in the grid.
			   this->dataGridView_dataDisplay->Size = System::Drawing::Size(1313, 375);            // Sets the initial pixel dimensions of the DataGridView control.
			   this->dataGridView_dataDisplay->TabIndex = 1;                                       // Sets the tab order index so pressing Tab moves focus here second.

			   // 
			   // button_updateStock
			   // 
			   this->button_updateStock->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( // Pins the button to the bottom-right so it stays there when the form resizes.
				   (System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->button_updateStock->Location = System::Drawing::Point(893, 420); // Sets the pixel position of the Update Stock button on the form.
			   this->button_updateStock->Name = L"button_updateStock";                // Sets the internal name used to reference this button in code.
			   this->button_updateStock->Size = System::Drawing::Size(140, 35);       // Sets the width and height of the Update Stock button in pixels.
			   this->button_updateStock->TabIndex = 2;                                // Sets the tab order so pressing Tab moves focus here third.
			   this->button_updateStock->Text = L"Update Stock";                      // Sets the visible label text displayed on the Update Stock button.
			   this->button_updateStock->UseVisualStyleBackColor = true;              // Applies the system visual style to the button background color.
			   this->button_updateStock->Visible = false;                             // Hides the Update Stock button until a file has been successfully loaded.
			   this->button_updateStock->Click += gcnew System::EventHandler(this, &Form1::Button_UpdateStock_Click); // Registers Button_UpdateStock_Click as the handler for click events.

			   // 
			   // button_loadStock
			   // 
			   this->button_loadStock->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( // Pins the button to the bottom-right so it stays there when the form resizes.
				   (System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->button_loadStock->Location = System::Drawing::Point(1069, 420); // Sets the pixel position of the Load Stock button on the form.
			   this->button_loadStock->Name = L"button_loadStock";                   // Sets the internal name used to reference this button in code.
			   this->button_loadStock->Size = System::Drawing::Size(140, 35);        // Sets the width and height of the Load Stock button in pixels.
			   this->button_loadStock->TabIndex = 0;                                 // Sets the tab order to 0 so this button has focus when the application starts.
			   this->button_loadStock->Text = L"Load Stock";                         // Sets the visible label text displayed on the Load Stock button.
			   this->button_loadStock->UseVisualStyleBackColor = true;               // Applies the system visual style to the button background color.
			   this->button_loadStock->Click += gcnew System::EventHandler(this, &Form1::Button_LoadStock_Click); // Registers Button_LoadStock_Click as the handler for click events.

			   // 
			   // label_startDate
			   // 
			   this->label_startDate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( // Pins the label to the bottom-left so it stays aligned with the date picker on resize.
				   (System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->label_startDate->AutoSize = true;                                // Automatically resizes the label to fit its text content.
			   this->label_startDate->Location = System::Drawing::Point(138, 393);   // Sets the pixel position of the Start Date label on the form.
			   this->label_startDate->Name = L"label_startDate";                     // Sets the internal name used to reference this label in code.
			   this->label_startDate->Size = System::Drawing::Size(91, 20);          // Sets the initial width and height of the Start Date label in pixels.
			   this->label_startDate->TabIndex = 4;                                  // Sets the tab order index for this label control.
			   this->label_startDate->Text = L"Start Date: ";                        // Sets the visible text displayed by the Start Date label.

			   // 
			   // label_endDate
			   // 
			   this->label_endDate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( // Pins the label to the bottom-left so it stays aligned with the date picker on resize.
				   (System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->label_endDate->AutoSize = true;                                // Automatically resizes the label to fit its text content.
			   this->label_endDate->Location = System::Drawing::Point(552, 393);    // Sets the pixel position of the End Date label on the form.
			   this->label_endDate->Name = L"label_endDate";                        // Sets the internal name used to reference this label in code.
			   this->label_endDate->Size = System::Drawing::Size(85, 20);           // Sets the initial width and height of the End Date label in pixels.
			   this->label_endDate->TabIndex = 5;                                   // Sets the tab order index for this label control.
			   this->label_endDate->Text = L"End Date: ";                           // Sets the visible text displayed by the End Date label.

			   // 
			   // DateTimePicker_startDate
			   // 
			   this->DateTimePicker_startDate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( // Pins the picker to the bottom-left so it stays in position when the form resizes.
				   (System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->DateTimePicker_startDate->CustomFormat = L"dddd, MMMM d, yyyy"; // Sets the display format to show full day name, full month name, day, and year.
			   this->DateTimePicker_startDate->Location = System::Drawing::Point(99, 429); // Sets the pixel position of the start date picker on the form.
			   this->DateTimePicker_startDate->Name = L"DateTimePicker_startDate";         // Sets the internal name used to reference this control in code.
			   this->DateTimePicker_startDate->Size = System::Drawing::Size(299, 26);      // Sets the width and height of the start date picker in pixels.
			   this->DateTimePicker_startDate->TabIndex = 6;                               // Sets the tab order index for the start date picker control.
			   this->DateTimePicker_startDate->Value = System::DateTime(2021, 1, 28, 0, 0, 0, 0); // Sets the default start date to January 28, 2021 as required by the spec.

			   // 
			   // DateTimePicker_endDate
			   // 
			   this->DateTimePicker_endDate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( // Pins the picker to the bottom-left so it stays in position when the form resizes.
				   (System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->DateTimePicker_endDate->CustomFormat = L"dddd, MMMM d, yyyy"; // Sets the display format to show full day name, full month name, day, and year.
			   this->DateTimePicker_endDate->Location = System::Drawing::Point(490, 429); // Sets the pixel position of the end date picker on the form.
			   this->DateTimePicker_endDate->Name = L"DateTimePicker_endDate";            // Sets the internal name used to reference this control in code.
			   this->DateTimePicker_endDate->Size = System::Drawing::Size(299, 26);       // Sets the width and height of the end date picker in pixels.
			   this->DateTimePicker_endDate->TabIndex = 7;                          // Sets the tab order index for the end date picker control.
			   this->DateTimePicker_endDate->Value = System::DateTime(2021, 2, 28, 0, 0, 0, 0); // Sets the default end date to February 28, 2021 as required by the spec.

			   // 
			   // openFileDialog_Load
			   // 
			   this->openFileDialog_Load->DefaultExt = L"csv";          // Sets the default file extension so files without an extension are treated as CSV.
			   this->openFileDialog_Load->FileName = L"ABBV_daily";     // Pre-selects ABBV_daily so the grader can press Enter twice to load data immediately.
			   this->openFileDialog_Load->Filter = L"All Stocks|*.csv|yearly|*_yearly.csv|monthly|*_monthly.csv|weekly|*_weekly.csv|daily|*_daily.csv"; // Provides dropdown filters so the user can view all files or filter by period type.
			   this->openFileDialog_Load->InitialDirectory = L"C:\\Users\\naren\\Desktop\\Stock_Data"; // Opens the dialog directly in the Stock_Data folder where CSV files are stored.
			   this->openFileDialog_Load->Multiselect = true;           // Allows the user to select multiple CSV files at once from the dialog.
			   this->openFileDialog_Load->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk); // Registers openFileDialog1_FileOk as the handler called when the user confirms file selection.

			   // 
			   // Form1
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(9, 20); // Sets the reference font size used to scale controls when the system DPI changes.
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font; // Scales all controls proportionally based on the current font size.
			   this->AutoSize = true;                                             // Allows the form to automatically resize to fit all its contained controls.
			   this->ClientSize = System::Drawing::Size(1309, 500);              // Sets the initial inner dimensions of the form excluding the title bar and borders.

			   // Add all controls to the form in reverse z-order (last added appears behind earlier ones).
			   this->Controls->Add(this->DateTimePicker_endDate);   // Adds the end date picker to the form's control collection.
			   this->Controls->Add(this->DateTimePicker_startDate); // Adds the start date picker to the form's control collection.
			   this->Controls->Add(this->label_endDate);            // Adds the end date label to the form's control collection.
			   this->Controls->Add(this->label_startDate);          // Adds the start date label to the form's control collection.
			   this->Controls->Add(this->button_loadStock);         // Adds the Load Stock button to the form's control collection.
			   this->Controls->Add(this->button_updateStock);       // Adds the Update Stock button to the form's control collection.
			   this->Controls->Add(this->dataGridView_dataDisplay); // Adds the DataGridView to the form's control collection.

			   this->Name = L"Form1"; // Sets the internal name of the form used to reference it in code.
			   this->Text = L"Form1"; // Sets the title bar text displayed at the top of the form window.

			   // End DataGridView initialization and re-enable layout processing.
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView_dataDisplay))->EndInit();
			   this->ResumeLayout(false);  // Re-enables layout logic that was suspended during initialization.
			   this->PerformLayout();      // Forces an immediate layout pass to apply all pending size and position changes.
		   }
#pragma endregion

		   /// <summary>
		   /// Handles the Load Stock button click event by opening the file dialog
		   /// so the user can browse and select a stock CSV file to load.
		   /// </summary>
		   /// <param name="sender">The source of the event (the Load Stock button).</param>
		   /// <param name="e">Standard event arguments for the click event.</param>
	private: System::Void Button_LoadStock_Click(System::Object^ sender, System::EventArgs^ e)
	{
		openFileDialog_Load->ShowDialog(); // Opens the OpenFileDialog window so the user can browse for and select a CSV file.
	}

		   /// <summary>
		   /// Event handler for the OpenFileDialog FileOk event. Loads the selected CSV file,
		   /// filters candlestick data by the UI date range, updates internal data lists, 
		   /// makes the update button visible, and binds the filtered data to the data grid.
		   /// </summary>
		   /// <param name="sender">The source of the event (typically the OpenFileDialog control).</param>
		   /// <param name="e">A CancelEventArgs instance that can be used to cancel the file selection.</param>
	private: System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
	{
		String^ filename = openFileDialog_Load->FileName; // Retrieves the full file path of the CSV file the user selected in the dialog.
		Text = System::IO::Path::GetFileNameWithoutExtension(filename); // Updates the form title bar to show the selected file's name without its extension.

		DateTime startDate = this->DateTimePicker_startDate->Value; // Reads the start date the user selected in the start DateTimePicker.
		DateTime endDate = this->DateTimePicker_endDate->Value;     // Reads the end date the user selected in the end DateTimePicker.

		aCandlestickLoader^ candlestickLoader = gcnew aCandlestickLoader(); // Creates a new instance of the loader (used for object-oriented access if needed).
		this->listOfCandlesticks = aCandlestickLoader::LoadFromCsv(filename); // Calls the static LoadFromCsv method to parse all candlestick rows from the selected CSV file.
		this->filteredList = filterCandlesticks(listOfCandlesticks, startDate, endDate); // Filters the full candlestick list to only those within the selected date range.
		button_updateStock->Visible = true; // Makes the Update Stock button visible now that a file has been successfully loaded.

		dataGridView_dataDisplay->DataSource = this->filteredList; // Binds the filtered candlestick list to the DataGridView so it displays the date-range data.
	}

		/// <summary>
		/// Handles the Update Stock button click: filters the stored candlesticks by the start 
	/// & end date pickers and updates the data grid view with the filtered list.
	/// </summary>
	/// <param name="sender">The source of the event (the Update Stock button).</param>
	/// <param name="e">Standard event arguments for the click event.</param>
	private: System::Void Button_UpdateStock_Click(System::Object^ sender, System::EventArgs^ e)
	{
		DateTime startDate = this->DateTimePicker_startDate->Value; // Reads the current start date from the start DateTimePicker control.
		DateTime endDate = this->DateTimePicker_endDate->Value;     // Reads the current end date from the end DateTimePicker control.

		List<aCandlestick^>^ filteredLoc = filterCandlesticks(this->listOfCandlesticks, startDate, endDate); // Filters the full candlestick list using the newly selected date range.
		dataGridView_dataDisplay->DataSource = filteredLoc; // Rebinds the DataGridView to the updated filtered list to refresh the displayed data.
	}

		   /// <summary>
		   /// Returns a new list containing candlesticks from loc whose date falls within the inclusive range
		   /// [startDate, endDate].
		   /// </summary>
		   /// <param name="loc">The source list of aCandlestick objects to filter, expected to be sorted ascending by date.</param>
		   /// <param name="startDate">Inclusive start of the date range to include.</param>
		   /// <param name="endDate">Inclusive end of the date range; scanning stops once this date is reached.</param>
		   /// <returns>A new List of aCandlestick objects whose dates fall within [startDate, endDate], in original order.</returns>
	public: List<aCandlestick^>^ filterCandlesticks(List<aCandlestick^>^ loc, DateTime startDate, DateTime endDate)
	{
		List<aCandlestick^>^ filteredList = gcnew List<aCandlestick^>(); // Creates a new empty list to hold candlesticks that fall within the date range.

		for (int i = 0; i < loc->Count; i++) // Iterates through every candlestick in the source list from first to last.
		{
			aCandlestick^ candleStick = loc[i]; // Retrieves the candlestick at the current index for date comparison.

			DateTime date = candleStick->date; // Extracts the date property from the current candlestick for range checking.

			if (date >= startDate && date <= endDate) // Checks if the candlestick date falls within the inclusive [startDate, endDate] range.
			{
				filteredList->Add(candleStick); // Adds the in-range candlestick to the filtered output list.
			}

			if (date >= endDate) // Checks if the current date has reached or passed the end date.
				break;           // Stops iterating early since all remaining dates will be beyond the range.
		}

		return filteredList; // Returns the filtered list containing only candlesticks within the selected date range.
	}
	};
}

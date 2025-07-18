#include "AdvancedSettings.hpp"

#include <iostream>

AdvancedSettings::AdvancedSettings(int x, int y, int w, int h, Settings* sett) : Fl_Window(x, y, w, h), X(x), Y(y), W(w), H(h), SettingsFileContent(sett) {
	box(FL_BORDER_BOX);

	//this->SettingsFileContent = ReadSettings();

	/*----------------------------------------------------------------------------------*/
	ButtonHeightx = 50;
	ButtonHeighty = 0;

	this->MaxXButtonHeightInput = new Fl_Value_Input(ButtonHeightx, ButtonHeighty,70,20);
	this->MaxXButtonHeightInput->label("MaxX");
	this->MaxXButtonHeightInput->value(this->SettingsFileContent->MaxXButtonHeight);

	this->MinXButtonHeightInput = new Fl_Value_Input(ButtonHeightx, ButtonHeighty + 20, 70, 20);
	this->MinXButtonHeightInput->label("MinX");
	this->MinXButtonHeightInput->value(this->SettingsFileContent->MinXButtonHeight);
	
	this->MaxYButtonHeightInput = new Fl_Value_Input(ButtonHeightx + 150, ButtonHeighty, 70, 20);
	this->MaxYButtonHeightInput->label("MaxY");
	this->MaxYButtonHeightInput->value(this->SettingsFileContent->MaxYButtonHeight);

	this->MinYButtonHeightInput = new Fl_Value_Input(ButtonHeightx + 150, ButtonHeighty + 20, 70, 20);
	this->MinYButtonHeightInput->label("MinY");
	this->MinYButtonHeightInput->value(this->SettingsFileContent->MinYButtonHeight);
	this->hide();
	/*----------------------------------------------------------------------------------*/
	Loggingx = 70;
	Loggingy = 70;

	this->LoggingStrength = new Fl_Hor_Slider(Loggingx, Loggingy, 100, 20,"Logging");
	this->LoggingStrength->range(0, 3);
	this->LoggingStrength->step(1);
	this->LoggingStrength->value(this->SettingsFileContent->LoggingStrenght);
	this->LoggingStrength->align(FL_ALIGN_LEFT);
	this->LoggingStrength->callback(SetLoggingStrenght, this);

	this->LoggingStrengthTextContent = new Fl_Text_Buffer();

	this->LoggingStrengthText = new Fl_Text_Display(Loggingx + 100, Loggingy, 80, 23);
	this->LoggingStrengthText->buffer(LoggingStrengthTextContent);
	this->LoggingStrengthText->box(FL_NO_BOX);
	this->LoggingStrengthText->align(FL_ALIGN_CENTER);
	this->LoggingStrength->do_callback();

	/*----------------------------------------------------------------------------------*/
	range_slider_value_shovingx = 60;
	range_slider_value_shovingy = 90;

	this->range_slider_value_shoving = new Fl_Check_Button(range_slider_value_shovingx, range_slider_value_shovingy, 20,20,"value shoving");
	this->range_slider_value_shoving->tooltip("Enables or disables value shoving on range sliders");
	this->range_slider_value_shoving->value(this->SettingsFileContent->Range_slider_value_shoving);

	//------------------------------------------------
	TrashbinPathx = 155;
	TrashbinPathy = 170;
	TrashbinPathw = 0;
	TrashbinPathh = 0;

	this->TrashbinPath = new Fl_Input(TrashbinPathx, TrashbinPathy, 700, 20, "Trashbin Folder Path");
	this->TrashbinPath->value(this->SettingsFileContent->TrashbinPath.c_str());
	this->TrashbinPath->tooltip("this is the folder the program will put images set for deletion in");

}

AdvancedSettings::~AdvancedSettings()
{
	delete (this->MinXButtonHeightInput);
	delete (this->MaxYButtonHeightInput);
	delete (this->MinYButtonHeightInput);
	delete (this->MaxXButtonHeightInput);
	delete (this->LoggingStrength);
	delete (this->LoggingStrengthText);
	delete (this->LoggingStrengthTextContent);
	delete (this->range_slider_value_shoving);
}

void AdvancedSettings::SetLoggingStrenght(Fl_Widget* w, void* data) {
	AdvancedSettings* Gui = static_cast<AdvancedSettings*>(data);

	switch ((int)Gui->LoggingStrength->value())
	{
	case(0):
		Gui->LoggingStrengthTextContent->text("INFO");
		break;
	case(1):
		Gui->LoggingStrengthTextContent->text("WARNING");
		break;
	case(2):
		Gui->LoggingStrengthTextContent->text("ERROR");
		break;
	case(3):
		Gui->LoggingStrengthTextContent->text("FATAL");
		break;
	default:
		Gui->LoggingStrengthTextContent->text("FATAL");
		break;
	}
}
#include "GeneralSettings.hpp"
#include <iostream>

GeneralSettings::GeneralSettings(int x, int y, int w , int h, Settings* sett, SettGui* Gui): Fl_Window(x, y, w, h), SettingsFileContent(sett), mainGui(Gui) {


	//this->SettingsFileContent = ReadSettings();
	box(FL_BORDER_BOX);

//------------------------------------------------
	SettingsPathx = 130;
	SettingsPathy = 20;
	SettingsPathw = 0;
	SettingsPathh = 0;

	this->SettingsPath = new Fl_Input(SettingsPathx, SettingsPathy, 700, 20, "Settings file Path");
	//this->SettingsPath->value(this->SettingsFileContent->ImageFolderPath.c_str());
	this->SettingsPath->tooltip("select the settings file that should be loaded");
	this->SettingsPath->value(SettingsFileContent->SettingsFilePath.c_str());
	this->SettingsPathChooser = new Fl_File_Chooser("test", "*.txt", 2, "Choose a Settings file");
	this->SettingsPathChooser->callback(SetSettingsPath, this);
	this->SettingsPathChooserButton = new Fl_Button(SettingsPathx + 700 ,SettingsPathy,30,20);
	this->SettingsPathChooserButton->label("...");
	this->SettingsPathChooserButton->callback(ActivatePathChooser, this);
	this->SettingsLoaderButton = new Fl_Button(SettingsPathx ,SettingsPathy + 20,40,20);
	this->SettingsLoaderButton->label("load");
	this->SettingsLoaderButton->callback(LoadSettings, this);

//------------------------------------------------
	FunctionSelectorx = 150;
	FunctionSelectory = 100;
	FunctionSelectorw = 15;
	FunctionSelectorh = 100;
	
	this->main_function_selector_pack = new Fl_Pack(FunctionSelectorx, FunctionSelectory, FunctionSelectorw, FunctionSelectorh, "main function");
	this->main_function_selector_pack->type(Fl_Pack::VERTICAL);
	this->main_function_selector_pack->box(FL_FLAT_BOX);
	this->main_function_selector_pack->spacing(1);
	this->main_function_selector_pack->color(208);

	
	this->main_function_selector_popups = new Fl_Radio_Button(0, 0, 15, 15, "Popups");
	this->main_function_selector_popups->align(FL_ALIGN_LEFT);
	this->main_function_selector_content_sorting = new Fl_Radio_Button(0, 0 , 15, 15, "Content_sorting");
	this->main_function_selector_content_sorting->align(FL_ALIGN_LEFT);
	
	this->main_function_selector_pack->add(*this->main_function_selector_popups);
	this->main_function_selector_pack->add(*this->main_function_selector_content_sorting);
	
	if (this->SettingsFileContent->mainFunction == "Popups" ) {
		this->main_function_selector_popups->value(1);
	}
	if (this->SettingsFileContent->mainFunction == "Content_sorting" ) {
		this->main_function_selector_popups->value(1);
	}
	hide();
}



void GeneralSettings::ActivatePathChooser(Fl_Widget* w, void* data) {
	GeneralSettings* Gui = static_cast<GeneralSettings*>(data);
	Gui->SettingsPathChooser->show();
}

void GeneralSettings::LoadSettings(Fl_Widget* w, void* data) {
	GeneralSettings* Gui = static_cast<GeneralSettings*>(data);
	Gui->mainGui->settingsFileLocation = Gui->SettingsPath->value();
	Gui->mainGui->update(0);
	Gui->SettingsPath->value(Gui->mainGui->settingsFileLocation.c_str());
}

void GeneralSettings::SetSettingsPath(Fl_File_Chooser* chooser, void* data) {
GeneralSettings* Gui = static_cast<GeneralSettings*>(data);

	Gui->SettingsPath->value(chooser->value());
}

GeneralSettings::~GeneralSettings() {
	delete (this->SettingsPath);
	delete (this->SettingsPathChooser);
	delete (this->SettingsPathChooserButton);
}
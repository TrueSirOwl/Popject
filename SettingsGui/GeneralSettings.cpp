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
	this->SettingsLoaderButton = new Fl_Button(SettingsPathx ,SettingsPathy + 20,30,20);
	this->SettingsLoaderButton->label("load");
	this->SettingsLoaderButton->callback(LoadSettings, this);

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

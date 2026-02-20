#include "GeneralSettings.hpp"
#include <iostream>

GeneralSettings::GeneralSettings(int x, int y, int w , int h, Settings* sett, SettGui* Gui): Fl_Window(x, y, w, h), SettingsFileContent(sett), mainGui(Gui) {


	//this->SettingsFileContent = ReadSettings();
	box(FL_BORDER_BOX);


//------------------------------------------------
	Namex = 180;
	Namey = 1;
	Namew = 0;
	Nameh = 0;

	this->Name_input = new Fl_Input(Namex, Namey, 600, 20, "Settings Name");
	this->Name_input->value(SettingsFileContent->Name.c_str());
	this->Name_input->tooltip("Sets the display name of the loaded settings file");

	//------------------------------------------------
	SettingsPathx = 180;
	SettingsPathy = 20;
	SettingsPathw = 0;
	SettingsPathh = 0;

	this->SettingsPath = new Fl_Input(SettingsPathx, SettingsPathy, 600, 20, "Load new settings file");
	//this->SettingsPath->value(this->SettingsFileContent->ImageFolderPath.c_str());
	this->SettingsPath->tooltip("select the path to a settings file that should be loaded");
	this->SettingsPath->value(SettingsFileContent->SettingsFilePath.c_str());
	this->SettingsPathChooser = new Fl_File_Chooser("test", "*.txt", 2, "Choose a Settings file");
	this->SettingsPathChooser->callback(SetSettingsPath, this);
	this->SettingsPathChooserButton = new Fl_Button(SettingsPathx + 601 ,SettingsPathy,30,20);
	this->SettingsPathChooserButton->label("...");
	this->SettingsPathChooserButton->callback(ActivatePathChooser, this);
	this->NewSettingsLoaderButton = new Fl_Button(SettingsPathx + 632 ,SettingsPathy,40,20);
	this->NewSettingsLoaderButton->label("load");
	this->NewSettingsLoaderButton->callback(LoadNewSettings, this);
	this->NewSettingsLoaderButton->tooltip("try to load the file at the specified path");

	this->KnownSettingsChoice = new Fl_Choice(SettingsPathx, SettingsPathy + 20, 600, 20, "Load known settings file");
	this->known_settings_files = create_settings_list(Gui->database);
	this->KnownSettingsChoice->clear();
	for (const std::pair<std::string,std::string>& loc : this->known_settings_files) {
		this->KnownSettingsChoice->add(loc.first.c_str());
	}
	this->KnownSettingsChoice->value(0);
	this->KnownSettingsLoaderButton = new Fl_Button(SettingsPathx + 601 ,SettingsPathy + 20,40,20);
	this->KnownSettingsLoaderButton->label("load");
	this->KnownSettingsLoaderButton->callback(LoadKnownSettings, this);
	this->KnownSettingsLoaderButton->tooltip("try to load selected setting");
	this->mainGui->Gui->label(this->SettingsFileContent->Name.c_str());
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
	++w = NULL;
	GeneralSettings* Gui = static_cast<GeneralSettings*>(data);
	Gui->SettingsPathChooser->show();
}

void GeneralSettings::LoadNewSettings(Fl_Widget* w, void* data) {
	GeneralSettings* Gui = static_cast<GeneralSettings*>(data);
	std::string temp = Gui->mainGui->settingsFileLocation;
	Gui->mainGui->settingsFileLocation = Gui->SettingsPath->value();
	int err = Gui->mainGui->update(0);
	if(err != 0) {
		LOG(WARNING, "Selected Filepath is not a valid settings file");
		fl_message("Selected Filepath is not a valid settings file");
		Gui->mainGui->settingsFileLocation = temp;
		int err = Gui->mainGui->update(0);
		return;
	}
	Gui->SettingsPath->value(Gui->mainGui->settingsFileLocation.c_str());
	while (insert_new_setting_into_settings_table(Gui->mainGui->settingsFileLocation, Gui->mainGui->SettingsFileContent->Name, Gui->mainGui->database) == -2){
		std::string n = "A Settings file with the name: " + Gui->mainGui->SettingsFileContent->Name + " already exists, please enter a new name";
		Gui->mainGui->SettingsFileContent->Name = fl_input(n.c_str());
	}
	Gui->known_settings_files = create_settings_list(Gui->mainGui->database);
	Gui->KnownSettingsChoice->clear();
	for (const std::pair<std::string,std::string>& loc : Gui->known_settings_files) {
		Gui->KnownSettingsChoice->add(loc.first.c_str());
	}
	Gui->KnownSettingsChoice->value(0);
}

void GeneralSettings::LoadKnownSettings(Fl_Widget* w, void* data) {
	GeneralSettings* Gui = static_cast<GeneralSettings*>(data);
	std::map<std::string,std::string>::iterator selected_setting;
	std::string setting_name = Gui->KnownSettingsChoice->text();
	int selected_setting_number = Gui->KnownSettingsChoice->value();
	selected_setting = Gui->known_settings_files.find(setting_name);
	if (selected_setting == Gui->known_settings_files.end()) {
		std::cerr << "no such settings file found" << std::endl;
	}
	std::string setting_location = selected_setting->second;
	Gui->mainGui->settingsFileLocation = setting_location;
	change_last_opened_setting(Gui->mainGui->database, setting_location);
	Gui->mainGui->update(0);
}

void GeneralSettings::SetSettingsPath(Fl_File_Chooser* chooser, void* data) {
	GeneralSettings* Gui = static_cast<GeneralSettings*>(data);
	Gui->SettingsPath->value(chooser->value());
}

GeneralSettings::~GeneralSettings() {
	delete (this->SettingsPath);
	delete (this->SettingsPathChooser);
	delete (this->SettingsPathChooserButton);
	delete (this->Name_input);
}
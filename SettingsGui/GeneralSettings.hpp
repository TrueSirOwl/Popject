#pragma once
#include "SettGui.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Input.H>
#include "../shared/Settings.hpp"
#include <string>
#include <Fl/Fl_File_Chooser.H>
#include <Fl/Fl_Toggle_Round_Button.H>
#include <Fl/Fl_Radio_Button.H>
#include <Fl/Fl_Pack.H>
#include <Fl/Fl_Choice.H>
#include "Sqlite.hpp"

class SettGui;

class GeneralSettings : public Fl_Window
{
private:

	Settings* SettingsFileContent;

	SettGui* mainGui;

public:

	GeneralSettings(int x, int y, int w, int h, Settings* sett, SettGui* mainGui);
	~GeneralSettings();

//------------------------------------------------
	int Namex, Namey, Namew, Nameh;
	Fl_Input* Name_input;
//------------------------------------------------

	int SettingsPathx, SettingsPathy, SettingsPathw, SettingsPathh;
	Fl_Input* SettingsPath;
	Fl_File_Chooser* SettingsPathChooser;
	Fl_Button* SettingsPathChooserButton;
	Fl_Button* NewSettingsLoaderButton;
	Fl_Choice* KnownSettingsChoice;
	Fl_Button* KnownSettingsLoaderButton;

	std::map<std::string, std::string> known_settings_files;

//------------------------------------------------
	int FunctionSelectorx, FunctionSelectory, FunctionSelectorw, FunctionSelectorh;
	Fl_Pack* main_function_selector_pack;
	Fl_Radio_Button* main_function_selector_popups;
	Fl_Radio_Button* main_function_selector_content_sorting;

	static void ActivatePathChooser(Fl_Widget* w, void* data);
	static void SetSettingsPath(Fl_File_Chooser* chooser, void* data);
	static void LoadNewSettings(Fl_Widget* w, void* data);
	static void LoadKnownSettings(Fl_Widget* w, void* data);

};


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

class SettGui;

class GeneralSettings : public Fl_Window
{
private:

	Settings* SettingsFileContent;

	SettGui* mainGui;

public:

	GeneralSettings(int x, int y, int w, int h, Settings* sett, SettGui* mainGui);

	int SettingsPathx, SettingsPathy, SettingsPathw, SettingsPathh;
	Fl_Input* SettingsPath;
	Fl_File_Chooser* SettingsPathChooser;
	Fl_Button* SettingsPathChooserButton;
	Fl_Button* SettingsLoaderButton;


	static void ActivatePathChooser(Fl_Widget* w, void* data);
	static void SetSettingsPath(Fl_File_Chooser* chooser, void* data);
	static void LoadSettings(Fl_Widget* w, void* data);

};


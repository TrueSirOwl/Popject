#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Input.H>
#include "../shared/Settings.hpp"
#include <string>

class ImagesSettings : public Fl_Window
{
private:

	Settings* SettingsFileContent;

public:

	ImagesSettings(int x, int y, int w, int h, Settings* sett);

};

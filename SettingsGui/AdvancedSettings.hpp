#pragma once
#include <FL/Fl_Window.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Hor_Slider.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Check_Button.H>
#include "../shared/Settings.hpp"

class AdvancedSettings : public Fl_Window
{
private:

	Settings* SettingsFileContent;

public:

	int X, Y, W, H;
	/*-----------------------------------*/
	int ButtonHeightx, ButtonHeighty;

	Fl_Value_Input* MinXButtonHeightInput;
	Fl_Value_Input* MaxXButtonHeightInput;
	Fl_Value_Input* MinYButtonHeightInput;
	Fl_Value_Input* MaxYButtonHeightInput;
	/*-----------------------------------*/
	int Loggingx, Loggingy;

	Fl_Hor_Slider* LoggingStrength;
	Fl_Text_Display* LoggingStrengthText;
	Fl_Text_Buffer* LoggingStrengthTextContent;
	/*-----------------------------------*/
	int range_slider_value_shovingx,range_slider_value_shovingy;

	Fl_Check_Button* range_slider_value_shoving;
	//------------------------------------------------
	int TrashbinPathx, TrashbinPathy, TrashbinPathw, TrashbinPathh;

	Fl_Input* TrashbinPath;

	static void SetLoggingStrenght(Fl_Widget* w, void* data);

	AdvancedSettings(int x, int y, int w, int h, Settings* sett);
	~AdvancedSettings();
};


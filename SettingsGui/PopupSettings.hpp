#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Hor_Value_Slider.H>
#include <FL/Fl_Hor_Slider.H>
#include <FL/Fl_Check_Button.H>
#include <FL/fl_ask.H>
#include "../shared/Settings.hpp"
#include <string>
#include <algorithm>
#include "RangeSlider.hpp"
#include <Fl/Fl_File_Chooser.H>


class PopupSettings : public Fl_Double_Window
{
private:

	Settings* SettingsFileContent;

public:
	int X, Y , W, H;

	RangeSlider* test;

	//------------------------------------------------
	int Buttonx, Buttony, Buttonw, Buttonh;
	Fl_Value_Slider* ButtonXinput;
	Fl_Value_Slider* ButtonYinput;
	Fl_Input* ButtonTextInput;
	//------------------------------------------------
	int Fadex, Fadey, Fadew, Fadeh;
	RangeSlider* PopupFadeOutStepsRangeSlider;
	RangeSlider* PopupFadeOutTimeRangeSlider;
	RangeSlider* PopupFadeInTimeRangeSlider;
	//------------------------------------------------
	int Opacityx, Opacityy, Opacityw, Opacityh;
	RangeSlider* PopupOpacityRangeSlider;
	Fl_Check_Button* Overlay;
	//------------------------------------------------
	int Lifespanx, Lifespany, Lifespanw, Lifespanh;
	Fl_Check_Button* PopupLifespan;
	RangeSlider* PopupLifespanRangeSlider;
	//------------------------------------------------
	int FolderPathx, FolderPathy, FolderPathw, FolderPathh;
	Fl_Input* ImageFolderPath;
	Fl_File_Chooser* ImageFolderPathChooser;
	Fl_Button* ImageFolderPathChooserButton;
	//------------------------------------------------
	int Multipopx, Multipopy;
	RangeSlider* MultipopRangeSlider;
	RangeSlider* MultipopTimingRangeSlider;
	RangeSlider* TimeBetweenMultipopsRangeSlider;
	//------------------------------------------------
	int ImageScalex, ImageScaley, ImageScalew, ImageScaleh;

	RangeSlider* ImageScaleRangeSlider;
	//------------------------------------------------


	static void ActivatePathChooser(Fl_Widget* w, void* data);
	static void SetSettingsPath(Fl_File_Chooser* chooser, void* data);

	static void ResizeButtonTextField(Fl_Widget* w, void* data);
	static void ActivateFadeout(Fl_Widget* w, void* data);

	PopupSettings(int x, int y, int w, int h, Settings* sett);
	~PopupSettings();
};


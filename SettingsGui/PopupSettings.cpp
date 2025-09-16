#include "PopupSettings.hpp"
#include <iostream>
#include <cmath>

PopupSettings::PopupSettings(int x, int y, int w, int h, Settings* sett) : Fl_Double_Window(x, y, w, h),X(x),Y(y),W(w),H(h), SettingsFileContent(sett) {
	box(FL_BORDER_BOX);

	//this->SettingsFileContent = ReadSettings();
	//------------------------------------------------
	this->ButtonXinput = new Fl_Value_Slider(w-50, h- this->SettingsFileContent->MaxYButtonHeight -120, 40, 100, "ButtonX");
	this->ButtonXinput->value(this->SettingsFileContent->ButtonX);
	this->ButtonXinput->maximum(this->SettingsFileContent->MinXButtonHeight);
	this->ButtonXinput->minimum(this->SettingsFileContent->MaxXButtonHeight);
	this->ButtonXinput->step(1);
	this->ButtonXinput->tooltip("Sets the X extent of the Button in the bottom right Corner");
	this->ButtonXinput->callback(ResizeButtonTextField, this);

	this->ButtonYinput = new Fl_Value_Slider(w-100, h- this->SettingsFileContent->MaxYButtonHeight -120, 40, 100, "ButtonY");
	this->ButtonYinput->value(this->SettingsFileContent->ButtonY);
	this->ButtonYinput->maximum(this->SettingsFileContent->MinYButtonHeight);
	this->ButtonYinput->minimum(this->SettingsFileContent->MaxYButtonHeight);
	this->ButtonYinput->step(1);
	this->ButtonYinput->tooltip("Sets the Y extent of the Button in the bottom right Corner");
	this->ButtonYinput->callback(ResizeButtonTextField, this);
	
	this->ButtonTextInput = new Fl_Input(w - this->SettingsFileContent->ButtonX, h- this->SettingsFileContent->ButtonY, this->SettingsFileContent->ButtonX, this->SettingsFileContent->ButtonY);
	this->ButtonTextInput->value(this->SettingsFileContent->ButtonText.c_str());
	this->ButtonTextInput->tooltip("Sets the Text on the Button in the bottom right Corner");
	//------------------------------------------------

	this->Fadex = 200;
	this->Fadey = 10;
	this->Fadew = 300;
	this->Fadeh = 60;

	this->PopupFadeOutStepsRangeSlider = new RangeSlider(Fadex, Fadey, 220, 20, "Fade Steps", sett);
	this->PopupFadeOutStepsRangeSlider->value(this->SettingsFileContent->lowPopupFadeOutSteps, this->SettingsFileContent->highPopupFadeOutSteps);
	this->PopupFadeOutStepsRangeSlider->tooltip("Sets the amount of Steps the Fade out takes to dissapear (one step takes one time");
	this->PopupFadeOutStepsRangeSlider->step(1);
	this->PopupFadeOutStepsRangeSlider->maximum(5000);
	this->PopupFadeOutStepsRangeSlider->minimum(10);

	this->PopupFadeOutTimeRangeSlider = new RangeSlider(Fadex, Fadey+20, 220, 20, "Fade out Time", sett);
	this->PopupFadeOutTimeRangeSlider->value(this->SettingsFileContent->lowPopupFadeOutTime,this->SettingsFileContent->highPopupFadeOutTime);
	this->PopupFadeOutTimeRangeSlider->tooltip("Sets the time the Fade out takes");
	this->PopupFadeOutTimeRangeSlider->step(1);
	this->PopupFadeOutTimeRangeSlider->maximum(10000);
	this->PopupFadeOutTimeRangeSlider->minimum(0);

	this->PopupFadeInTimeRangeSlider = new RangeSlider(Fadex, Fadey+40, 220, 20, "Fade in Time", sett);
	this->PopupFadeInTimeRangeSlider->value(this->SettingsFileContent->lowPopupFadeInTime,this->SettingsFileContent->highPopupFadeInTime);
	this->PopupFadeInTimeRangeSlider->tooltip("Sets the time the Fade in takes");
	this->PopupFadeInTimeRangeSlider->step(1);
	this->PopupFadeInTimeRangeSlider->maximum(10000);
	this->PopupFadeInTimeRangeSlider->minimum(0);
	//------------------------------------------------
	Opacityx = 200;
	Opacityy = 70;
	Opacityw = 0;
	Opacityh = 0;

	this->PopupOpacityRangeSlider = new RangeSlider(Opacityx, Opacityy,220,20,"Opacity",sett);
	this->PopupOpacityRangeSlider->value(this->SettingsFileContent->lowPopupOpacity, this->SettingsFileContent->highPopupOpacity);
	this->PopupOpacityRangeSlider->maximum(1);
	this->PopupOpacityRangeSlider->minimum(0);
	this->PopupOpacityRangeSlider->step(0.01);
	this->PopupOpacityRangeSlider->tooltip("Sets the Opactity of the Popups");

	//this->PopupOpacityInput = new Fl_Value_Input(Opacityx);

	//------------------------------------------------

	Lifespanx = 200;
	Lifespany = 90;
	Lifespanw = 0;
	Lifespanh = 0;

	this->PopupLifespanRangeSlider = new RangeSlider(Lifespanx, Lifespany, 200, 20, "Popup Lifespan",sett);
	this->PopupLifespanRangeSlider->minimum(0);
	this->PopupLifespanRangeSlider->maximum(10000);
	this->PopupLifespanRangeSlider->step(1);
	this->PopupLifespanRangeSlider->value(this->SettingsFileContent->lowPopupLifespan, this->SettingsFileContent->highPopupLifespan);
	this->PopupLifespanRangeSlider->tooltip("Sets how long each Popup exists untill it begins to dissapear");

	//------------------------------------------------

	Multipopx= 200;
	Multipopy = 110;
	
	this->MultipopRangeSlider = new RangeSlider(Multipopx, Multipopy, 220, 20, "Multipop", sett);
	this->MultipopRangeSlider->value(this->SettingsFileContent->lowMultipop, this->SettingsFileContent->highMultipop);
	this->MultipopRangeSlider->minimum(1);
	this->MultipopRangeSlider->maximum(100);
	this->MultipopRangeSlider->step(1);
	this->MultipopRangeSlider->tooltip("Sets Amount of Popups per activation");
	
	this->MultipopTimingRangeSlider = new RangeSlider(Multipopx, Multipopy + 20, 220, 20, "Multipop Timing", sett);
	this->MultipopTimingRangeSlider->value(this->SettingsFileContent->lowMultipopTiming, this->SettingsFileContent->highMultipopTiming);
	this->MultipopTimingRangeSlider->minimum(0);
	this->MultipopTimingRangeSlider->maximum(10000);
	this->MultipopTimingRangeSlider->step(1);
	this->MultipopTimingRangeSlider->tooltip("Sets Timing between Popups in a multipop, Min time is always image loading time");

	this->TimeBetweenMultipopsRangeSlider = new RangeSlider(Multipopx, Multipopy + 40, 200, 20, "time between multipops", sett);
	this->TimeBetweenMultipopsRangeSlider->minimum(0);
	this->TimeBetweenMultipopsRangeSlider->maximum(10000);
	this->TimeBetweenMultipopsRangeSlider->step(1);
	this->TimeBetweenMultipopsRangeSlider->value(this->SettingsFileContent->lowTimeBetweenPopups, this->SettingsFileContent->highTimeBetweenPopups);
	this->TimeBetweenMultipopsRangeSlider->tooltip("Sets the time between multipops, Min time is always image loading time");

	//------------------------------------------------
	FolderPathx = 150;
	FolderPathy = 170;
	FolderPathw = 0;
	FolderPathh = 0;

	this->ImageFolderPath = new Fl_Input(FolderPathx, FolderPathy, 700, 20, "Image Folder Path");
	this->ImageFolderPath->value(this->SettingsFileContent->ImageFolderPath.c_str());
	this->ImageFolderPath->tooltip("this is the path the program will get all its images from");
	this->ImageFolderPathChooser = new Fl_File_Chooser("test", "", 4, "Choose a folder");
	this->ImageFolderPathChooser->callback(SetSettingsPath, this);
	this->ImageFolderPathChooserButton = new Fl_Button(FolderPathx + 700 ,FolderPathy,30,20);
	this->ImageFolderPathChooserButton->label("...");
	this->ImageFolderPathChooserButton->callback(ActivatePathChooser, this);
	//------------------------------------------------
	
	ImageScalex = 200;
	ImageScaley = 400;
	ImageScalew = 0;
	ImageScaleh = 0;;

	this->ImageScaleRangeSlider = new RangeSlider(ImageScalex, ImageScaley,220,20,"ImageScaleMax",sett);
	this->ImageScaleRangeSlider->value(this->SettingsFileContent->lowImageScale, this->SettingsFileContent->highImageScale);
	this->ImageScaleRangeSlider->maximum(1);
	this->ImageScaleRangeSlider->minimum(0);
	this->ImageScaleRangeSlider->step(0.01);
	this->ImageScaleRangeSlider->tooltip("Sets the Max size of the Popups in relation to actual image size, limited by screen size");

	hide();
}

void PopupSettings::ActivatePathChooser(Fl_Widget* w, void* data) {
	PopupSettings* Gui = static_cast<PopupSettings*>(data);
	Gui->ImageFolderPathChooser->show();
}

void PopupSettings::SetSettingsPath(Fl_File_Chooser* chooser, void* data) {
	PopupSettings* Gui = static_cast<PopupSettings*>(data);

	Gui->ImageFolderPath->value(chooser->value());
}


void PopupSettings::ResizeButtonTextField(Fl_Widget* w, void* data) {
	PopupSettings* Gui = static_cast<PopupSettings*>(data);
	Gui->ButtonTextInput->resize(Gui->W - Gui->ButtonXinput->value(), Gui->H - Gui->ButtonYinput->value(), Gui->ButtonXinput->value(), Gui->ButtonYinput->value());
	Gui->redraw();
}

PopupSettings::~PopupSettings() {
	delete (this->ButtonXinput);
	delete (this->ButtonYinput);
	delete (this->ButtonTextInput);
	delete (this->PopupFadeOutStepsRangeSlider);
	delete (this->PopupFadeOutTimeRangeSlider);
	delete (this->PopupFadeInTimeRangeSlider);
	delete (this->PopupOpacityRangeSlider);
	delete (this->PopupLifespanRangeSlider);
	delete (this->TimeBetweenMultipopsRangeSlider);
	delete (this->ImageFolderPath);
	delete (this->MultipopRangeSlider);
	delete (this->MultipopTimingRangeSlider);
	delete (this->ImageScaleRangeSlider);
}
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

	this->PopupFadeOut = new Fl_Check_Button(Fadex, Fadey, 20, 20, "Fade Out");
	this->PopupFadeOut->align(FL_ALIGN_LEFT);
	this->PopupFadeOut->value(this->SettingsFileContent->PopupFadeOut);
	this->PopupFadeOut->tooltip("Enables Popup Fadeout after Lifetime runs out");
	this->PopupFadeOut->callback(ActivateFadeout, this);

	this->PopupFadeOutStepsRangeSlider = new RangeSlider(Fadex, Fadey+20, 220, 20, "Steps", sett);
	this->PopupFadeOutStepsRangeSlider->value(this->SettingsFileContent->lowPopupFadeOutSteps, this->SettingsFileContent->highPopupFadeOutSteps);
	this->PopupFadeOutStepsRangeSlider->tooltip("Sets the amount of Steps the Fade out takes to dissapear (one step takes one time");
	this->PopupFadeOutStepsRangeSlider->step(1);
	this->PopupFadeOutStepsRangeSlider->maximum(5000);
	this->PopupFadeOutStepsRangeSlider->minimum(10);

	this->PopupFadeOutTimeRangeSlider = new RangeSlider(Fadex, Fadey+40, 220, 20, "Time", sett);
	this->PopupFadeOutTimeRangeSlider->value(this->SettingsFileContent->lowPopupFadeOutTime,this->SettingsFileContent->highPopupFadeOutTime);
	this->PopupFadeOutTimeRangeSlider->tooltip("Sets the time the Fade out takes");
	this->PopupFadeOutTimeRangeSlider->step(1);
	this->PopupFadeOutTimeRangeSlider->maximum(10000);
	this->PopupFadeOutTimeRangeSlider->minimum(100);


	if (this->PopupFadeOut->value() == 0) {
		this->PopupFadeOutTimeRangeSlider->deactivate();
		this->PopupFadeOutStepsRangeSlider->deactivate();
	}
	//------------------------------------------------
	Opacityx = 200;
	Opacityy = 90;
	Opacityw = 0;
	Opacityh = 0;

	this->PopupOpacityRangeSlider = new RangeSlider(Opacityx, Opacityy,220,20,"Opacity",sett);
	this->PopupOpacityRangeSlider->value(this->SettingsFileContent->lowPopupOpacity, this->SettingsFileContent->highPopupOpacity);
	this->PopupOpacityRangeSlider->maximum(1);
	this->PopupOpacityRangeSlider->minimum(0);
	this->PopupOpacityRangeSlider->step(0.01);
	this->PopupOpacityRangeSlider->tooltip("Sets the Opactity of the Popups");

	
	this->Overlay = new Fl_Check_Button(Opacityx, Opacityy + 20, 20, 20,"Overlay");
	this->Overlay->value(this->SettingsFileContent->Overlay);
	this->Overlay->align(FL_ALIGN_LEFT);
	this->Overlay->tooltip("Makes Popups Overlays");

	//this->PopupOpacityInput = new Fl_Value_Input(Opacityx);

	//------------------------------------------------

	Lifespanx = 2000;
	Lifespany = 70;
	Lifespanw = 0;
	Lifespanh = 0;

	this->PopupLifespanRangeSlider = new RangeSlider(Lifespanx, Lifespany, 200, 20, "Popup Lifespan",sett);
	this->PopupLifespanRangeSlider->minimum(0);
	this->PopupLifespanRangeSlider->maximum(10000);
	this->PopupLifespanRangeSlider->step(1);
	this->PopupLifespanRangeSlider->value(this->SettingsFileContent->lowPopupLifespan, this->SettingsFileContent->highPopupLifespan);
	this->PopupLifespanRangeSlider->tooltip("Sets how long each Popup exists untill it begins to dissapear");

	//------------------------------------------------

	FolderPathx = 150;
	FolderPathy = 170;
	FolderPathw = 0;
	FolderPathh = 0;

	this->ImageFolderPath = new Fl_Input(FolderPathx, FolderPathy, 700, 20, "Image Folder Path");
	this->ImageFolderPath->value(this->SettingsFileContent->ImageFolderPath.c_str());
	this->ImageFolderPath->tooltip("this is the path the program will get all its images from");
	//------------------------------------------------

	TimeBetweenx = 200;
	TimeBetweeny = 150;
	TimeBetweenw = 0;
	TimeBetweenh = 0;

	this->TimeBetweenPopupsRangeSlider = new RangeSlider(TimeBetweenx, TimeBetweeny, 200, 20, "TimeBetweenPopups", sett);
	this->TimeBetweenPopupsRangeSlider->minimum(0);
	this->TimeBetweenPopupsRangeSlider->maximum(10000);
	this->TimeBetweenPopupsRangeSlider->step(1);
	this->TimeBetweenPopupsRangeSlider->value(this->SettingsFileContent->lowTimeBetweenPopups, this->SettingsFileContent->highTimeBetweenPopups);
	this->TimeBetweenPopupsRangeSlider->tooltip("Sets the time between Popups, Min time is always image loading time");
	//------------------------------------------------

	Multipopx= 200;
	Multipopy = 130;

	this->MultipopRangeSlider = new RangeSlider(Multipopx, Multipopy, 220, 20, "Multipop", sett);
	this->MultipopRangeSlider->value(this->SettingsFileContent->lowMultipop, this->SettingsFileContent->highMultipop);
	this->MultipopRangeSlider->minimum(1);
	this->MultipopRangeSlider->maximum(100);
	this->MultipopRangeSlider->step(1);
	this->MultipopRangeSlider->tooltip("Sets Amount of Popups per activation");

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


void PopupSettings::ResizeButtonTextField(Fl_Widget* w, void* data) {
	PopupSettings* Gui = static_cast<PopupSettings*>(data);
	Gui->ButtonTextInput->resize(Gui->W - Gui->ButtonXinput->value(), Gui->H - Gui->ButtonYinput->value(), Gui->ButtonXinput->value(), Gui->ButtonYinput->value());
	Gui->redraw();
}


void PopupSettings::ActivateFadeout(Fl_Widget* w, void* data) {
	PopupSettings* Gui = static_cast<PopupSettings*>(data);
	if (Gui->PopupFadeOut->value() == 0) {
		Gui->PopupFadeOutTimeRangeSlider->deactivate();
		Gui->PopupFadeOutStepsRangeSlider->deactivate();
	}
	else {
		Gui->PopupFadeOutTimeRangeSlider->activate();
		Gui->PopupFadeOutStepsRangeSlider->activate();
	}
}

PopupSettings::~PopupSettings() {
	delete (this->ButtonXinput);
	delete (this->ButtonYinput);
	delete (this->ButtonTextInput);
	delete (this->PopupFadeOut);
	delete (this->PopupFadeOutStepsRangeSlider);
	delete (this->PopupFadeOutTimeRangeSlider);
	delete (this->PopupOpacityRangeSlider);
	delete (this->Overlay);
	delete (this->PopupLifespanRangeSlider);
	delete (this->TimeBetweenPopupsRangeSlider);
	delete (this->ImageFolderPath);
	delete (this->MultipopRangeSlider);
	delete (this->ImageScaleRangeSlider);
}
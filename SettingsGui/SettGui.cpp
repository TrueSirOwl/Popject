#include "SettGui.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include "PopupSettings.hpp"
#include "GeneralSettings.hpp"

SettGui::SettGui(std::string loc) : W(std::min(900,Fl::w())), H(std::min(800,Fl::h())), settingsFileLocation(loc) {
	CreateLogFile();
	this->SettingsFileContent = ReadSettings(settingsFileLocation);
	this->Gui = new Fl_Window(0,0, W, H, "Settings");
	this->saveButton = new Fl_Button(0,H-20,W,20,"Save");
	this->saveButton->callback(save, this);
	this->BuildMenueSelectorPanel(this->SelectorPanelButtonNames);
	this->GenSett = new GeneralSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent, this);
	Gui->add(GenSett);
	this->PopSett = new PopupSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent);
	Gui->add(PopSett);
	this->AdvSett = new AdvancedSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent);
	Gui->add(AdvSett);
	this->ImgSett = new ImagesSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent);
	Gui->add(ImgSett);
	Gui->show();
	Gui->callback(Close,this);
	save(NULL,this);
}


void SettGui::update(int CurrentlyOpenPageNum)
{
	delete (this->SettingsFileContent);
	this->SettingsFileContent = ReadSettings(settingsFileLocation);
	delete(this->GenSett);
	this->GenSett = new GeneralSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent, this);
	Gui->add(GenSett);
	delete(this->PopSett);
	this->PopSett = new PopupSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent);
	Gui->add(PopSett);
	delete(this->AdvSett);
	this->AdvSett = new AdvancedSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent);
	Gui->add(AdvSett);
	delete(this->ImgSett);
	this->ImgSett = new ImagesSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent);
	Gui->add(ImgSett);
	if (CurrentlyOpenPageNum >= 0) {
		ShowSettingWindow(SelectorPanelButtons[CurrentlyOpenPageNum], this);
	}
}

void SettGui::ShowSettingWindow(Fl_Widget* w,void* name) {
	SettGui* Gui = static_cast<SettGui*>(name);
	for (size_t i = 0; i < Gui->SelectorPanelButtons.size(); i++) {
		Gui->SelectorPanelButtons[i]->box(FL_UP_BOX);
		Gui->SelectorPanelButtons[i]->redraw();
	}
	Gui->GenSett->hide();
	Gui->PopSett->hide();
	Gui->AdvSett->hide();
	Gui->ImgSett->hide();
	if (!strcmp(w->label(), "General")) {
		Gui->GenSett->show();
	}
	else if (!strcmp(w->label(), "Popups")) {
		Gui->PopSett->show();
	}
	else if (!strcmp(w->label(), "Advanced")) {
		Gui->AdvSett->show();
	}
	else if (!strcmp(w->label(), "Images")) {
		Gui->ImgSett->show();
	}
	w->box(FL_DOWN_BOX);
}

void SettGui::BuildMenueSelectorPanel(std::vector<const char*> &names) {
	this->SelectorButtonW = this->W / names.size();
	this->SelectorButtonH = std::max<int>(SelectorButtonW / 4, 20);

	for (size_t i = 0; i < names.size(); i++) {
		std::cout << names[i] << std::endl;
		Fl_Button *Butt = new Fl_Button(SelectorButtonW * i, 0, SelectorButtonW, SelectorButtonH, names[i]);
		SelectorPanelButtons.push_back(Butt);
		Butt->callback(ShowSettingWindow,static_cast<void*>(this));
	}
}

int SettGui::GetCurrentlyOpenPage()
{
	for (unsigned int i = 0; i < this->SelectorPanelButtons.size(); i++)
	{
		if (this->SelectorPanelButtons[i]->box() == FL_DOWN_BOX) {
			return (i);
		}
	}
	return (-1);
}

void SettGui::setButtonX(int src) {
	this->PopSett->ButtonXinput->value(src);
}

int SettGui::getButtonX() {
	return (this->PopSett->ButtonXinput->value());
}

void SettGui::setButtonY(int src) {
	this->PopSett->ButtonYinput->value(src);
}

int SettGui::getButtonY() {
	return (this->PopSett->ButtonYinput->value());
}

void SettGui::setButtonText(char* src) {
	this->PopSett->ButtonTextInput->value(src);
}

const char* SettGui::getButtonText() {
	return (this->PopSett->ButtonTextInput->value());
}

double SettGui::getlowPopupLifespan() {
	return (this->PopSett->PopupLifespanRangeSlider->get_low_value());
}

double SettGui::gethighPopupLifespan() {
	return (this->PopSett->PopupLifespanRangeSlider->get_high_value());
}

void SettGui::setImageFolderPath(char* src) {
	this->PopSett->ImageFolderPath->value(src);
}

const char* SettGui::getImageFolderPath() {
	return(this->PopSett->ImageFolderPath->value());
}

double SettGui::getlowTimeBetweenPopups() {
	return(this->PopSett->TimeBetweenMultipopsRangeSlider->get_low_value());
}

double SettGui::gethighTimeBetweenPopups() {
	return(this->PopSett->TimeBetweenMultipopsRangeSlider->get_high_value());
}

void SettGui::setMinXButtonHeight(int src) {
	this->AdvSett->MinXButtonHeightInput->value(src);
}

int SettGui::getMinXButtonHeight() {
	return(this->AdvSett->MinXButtonHeightInput->value());
}

void SettGui::setMaxXButtonHeight(int src) {
	this->AdvSett->MaxXButtonHeightInput->value(src);
}

int SettGui::getMaxXButtonHeight() {
	return(this->AdvSett->MaxXButtonHeightInput->value());
}

void SettGui::setMinYButtonHeight(int src) {
	this->AdvSett->MinYButtonHeightInput->value(src);
}

int SettGui::getMinYButtonHeight() {
	return(this->AdvSett->MinYButtonHeightInput->value());
}

void SettGui::setMaxYButtonHeight(int src) {
	this->AdvSett->MaxYButtonHeightInput->value(src);
}

int SettGui::getMaxYButtonHeight() {
	return(this->AdvSett->MaxYButtonHeightInput->value());
}

int SettGui::getRange_slider_value_shoving() {
	return(this->AdvSett->range_slider_value_shoving->value());
}

double SettGui::gethighPopupFadeOutSteps() {
	return(this->PopSett->PopupFadeOutStepsRangeSlider->get_high_value());
}

double SettGui::getlowPopupFadeOutSteps() {
	return(this->PopSett->PopupFadeOutStepsRangeSlider->get_low_value());
}

int SettGui::getlowPopupFadeOutTime() {
	return(this->PopSett->PopupFadeOutTimeRangeSlider->get_low_value());
}

int SettGui::gethighPopupFadeOutTime() {
	return(this->PopSett->PopupFadeOutTimeRangeSlider->get_high_value());
}

double SettGui::getlowPopupFadeInTime() {
	return(this->PopSett->PopupFadeInTimeRangeSlider->get_low_value());
}

double SettGui::gethighPopupFadeInTime() {
	return(this->PopSett->PopupFadeInTimeRangeSlider->get_high_value());
}

double SettGui::getlowPopupOpacity() {
	return(this->PopSett->PopupOpacityRangeSlider->get_low_value());
}

double SettGui::gethighPopupOpacity() {
	return(this->PopSett->PopupOpacityRangeSlider->get_high_value());
}

int SettGui::getLoggingStrength() {
	return(this->AdvSett->LoggingStrength->value());
}

double SettGui::getlowMultipop() {
	return(this->PopSett->MultipopRangeSlider->get_low_value());
}

double SettGui::gethighMultipop() {
	return(this->PopSett->MultipopRangeSlider->get_high_value());
}

double SettGui::gethighMultipopTiming() {
	return(this->PopSett->MultipopTimingRangeSlider->get_high_value());
}

double SettGui::getlowMultipopTiming() {
	return(this->PopSett->MultipopTimingRangeSlider->get_low_value());
}

double SettGui::gethighImageScale() {
	return(this->PopSett->ImageScaleRangeSlider->get_low_value());
}

double SettGui::getlowImageScale() {
	return(this->PopSett->ImageScaleRangeSlider->get_high_value());
}

const char* SettGui::getTrashbinPath() {
	return(this->AdvSett->TrashbinPath->value());
}

const char* SettGui::getSettingsPath() {
	return(this->GenSett->SettingsPath->value());
}

void Close(Fl_Widget* win, void* Src) {
	SettGui* Gui = static_cast<SettGui*>(Src);
	switch (fl_choice("do you want to save?", "cancel" , "yes", "no")) {
	case 0:
		std::cout << "0 (cancel)" << std::endl;
		break;
	case 1:
		std::cout << "1 (save)" << std::endl;
		save(win, Src);
		win->hide();
		break;
	case 2:
		std::cout << "2 (close)" << std::endl;
		win->hide();
		break;
	default:
		break;
	}
}

void save(Fl_Widget* win, void* Src) {
	SettGui* Gui = static_cast<SettGui*>(Src);
	std::ofstream Settings(Gui->settingsFileLocation);
	std::cout << Gui->getSettingsPath() << std::endl;
	if (Settings.is_open() == false) {
		std::cout << "error: could not open Settings File" << std::endl;
	}
	Settings << "ButtonX=" << std::min(Gui->getButtonX(), Gui->getMaxXButtonHeight()) << std::endl;
	Settings << "ButtonY=" << std::min(Gui->getButtonY(), Gui->getMaxYButtonHeight()) << std::endl;
	Settings << "ButtonText=" << Gui->getButtonText() << std::endl;
	Settings << "lowPopupLifespan=" << Gui->getlowPopupLifespan() << std::endl;
	Settings << "highPopupLifespan=" << Gui->gethighPopupLifespan() << std::endl;
	Settings << "ImageFolderPath=" << Gui->getImageFolderPath() << std::endl;
	Settings << "lowTimeBetweenPopups=" << Gui->getlowTimeBetweenPopups() << std::endl;
	Settings << "highTimeBetweenPopups=" << Gui->gethighTimeBetweenPopups() << std::endl;
	Settings << "MinXButtonHeight=" << Gui->getMinXButtonHeight() << std::endl;
	Settings << "MaxXButtonHeight=" << Gui->getMaxXButtonHeight() << std::endl;
	Settings << "MinYButtonHeight=" << Gui->getMinYButtonHeight() << std::endl;
	Settings << "MaxYButtonHeight=" << Gui->getMaxYButtonHeight() << std::endl;
	Settings << "lowMultipop=" << Gui->getlowMultipop() << std::endl;
	Settings << "highMultipop=" << Gui->gethighMultipop() << std::endl;
	Settings << "lowMultipopTiming=" << Gui->getlowMultipopTiming() << std::endl;
	Settings << "highMultipopTiming=" << Gui->gethighMultipopTiming() << std::endl;
	Settings << "lowPopupFadeOutSteps=" << Gui->getlowPopupFadeOutSteps() << std::endl;
	Settings << "highPopupFadeOutSteps=" << Gui->gethighPopupFadeOutSteps() << std::endl;
	Settings << "lowPopupFadeOutTime=" << Gui->getlowPopupFadeOutTime() << std::endl;
	Settings << "highPopupFadeOutTime=" << Gui->gethighPopupFadeOutTime() << std::endl;
	Settings << "lowPopupFadeInTime=" << Gui->getlowPopupFadeInTime() << std::endl;
	Settings << "highPopupFadeInTime=" << Gui->gethighPopupFadeInTime() << std::endl;
	Settings << "lowPopupOpacity=" << Gui->getlowPopupOpacity() << std::endl;
	Settings << "highPopupOpacity=" << Gui->gethighPopupOpacity() << std::endl;
	Settings << "LoggingStrength=" << Gui->getLoggingStrength() << std::endl;
	Settings << "lowImageScale=" << Gui->gethighImageScale() << std::endl;
	Settings << "highImageScale=" << Gui->getlowImageScale() << std::endl;
	Settings << "Range_slider_value_shoving=" << Gui->getRange_slider_value_shoving() << std::endl;
	Settings << "SettingsFilePath=" << Gui->getSettingsPath() << std::endl;

	Settings << "TrashbinPath=" << Gui->getTrashbinPath() << std::endl;
	std::filesystem::path neww(Gui->getTrashbinPath());
	std::filesystem::create_directories(neww);
	if (Gui->SettingsFileContent->TrashbinPath != Gui->getTrashbinPath()) {
		std::filesystem::path old(Gui->SettingsFileContent->TrashbinPath);
		std::filesystem::rename(old, neww);
		fl_choice("Trash location changed", "ok",0,0);
	}
	Gui->update(Gui->GetCurrentlyOpenPage());
}

SettGui::~SettGui()
{
	delete (this->PopSett);
	delete (this->GenSett);
	delete (this->AdvSett);
	delete (this->SettingsFileContent);
	while (this->SelectorPanelButtons.empty() == false) {
		delete(this->SelectorPanelButtons[0]);
		this->SelectorPanelButtons.erase(this->SelectorPanelButtons.begin());
	}
	this->SelectorPanelButtons.clear();
}
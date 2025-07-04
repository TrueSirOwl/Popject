#include "SettGui.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include "PopupSettings.hpp"
#include "GeneralSettings.hpp"

SettGui::SettGui(const char* loc) : W(std::min(900,Fl::w())), H(std::min(800,Fl::h())), settingsFileLocation(loc) {
	CreateLogFile();
	this->SettingsFileContent = ReadSettings(settingsFileLocation);
	this->Gui = new Fl_Window(0,0, W, H, "Settings");
	this->saveButton = new Fl_Button(0,H-20,W,20,"Save");
	this->saveButton->callback(saveAndClose, this);
	this->BuildMenueSelectorPanel(this->SelectorPanelButtonNames);
	this->GenSett = new GeneralSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent);
	Gui->add(GenSett);
	this->PopSett = new PopupSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent);
	Gui->add(PopSett);
	this->AdvSett = new AdvancedSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent);
	Gui->add(AdvSett);
	Gui->show();
	Gui->callback(saveAndClose,this);
}


void SettGui::update(int CurrentlyOpenPageNum)
{
	delete (this->SettingsFileContent);
	this->SettingsFileContent = ReadSettings(settingsFileLocation);
	delete(this->GenSett);
	this->GenSett = new GeneralSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent);
	Gui->add(GenSett);
	delete(this->PopSett);
	this->PopSett = new PopupSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent);
	Gui->add(PopSett);
	delete(this->AdvSett);
	this->AdvSett = new AdvancedSettings(2, 2 + SelectorButtonH, W - 4, H - SelectorButtonH - 24, this->SettingsFileContent);
	Gui->add(AdvSett);
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
	if (!strcmp(w->label(), "General")) {
		Gui->GenSett->show();
	}
	else if (!strcmp(w->label(), "Popups")) {
		Gui->PopSett->show();
	}
	else if (!strcmp(w->label(), "Advanced")) {
		Gui->AdvSett->show();
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

void SettGui::setPopupLifespan(int src) {
	this->PopSett->PopupLifespanInput->value(src);
}

int SettGui::getPopupLifespan() {
	return (this->PopSett->PopupLifespanInput->value());
}

void SettGui::setImageFolderPath(char* src) {
	this->PopSett->ImageFolderPath->value(src);
}

const char* SettGui::getImageFolderPath() {
	return(this->PopSett->ImageFolderPath->value());
}

double SettGui::getTimeBetweenPopups() {
	return(this->PopSett->TimeBetweenPopupsInput->value());
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

int SettGui::getMultiplicatior() {
	return(this->PopSett->MultiplicatiorInput->value());
}

void SettGui::setMultiplicatior(int src) {
	this->PopSett->MultiplicatiorInput->value(src);
}

int SettGui::getPopupFadeOut() {
	return(this->PopSett->PopupFadeOut->value());
}

double SettGui::gethighPopupFadeOutSteps() {
	return(this->PopSett->PopupFadeOutStepsRangeSlider->get_high_value());
}

double SettGui::getlowPopupFadeOutSteps() {
	return(this->PopSett->PopupFadeOutStepsRangeSlider->get_low_value());
}

int SettGui::getPopupFadeOutTime() {
	return(this->PopSett->PopupFadeOutTimeInput->value());
}

double SettGui::getPopupOpacity() {
	return(this->PopSett->PopupOpacitySlider->value());
}

int SettGui::getPopupOverlay() {
	return(this->PopSett->Overlay->value());
}

int SettGui::getLoggingStrength() {
	return(this->AdvSett->LoggingStrength->value());
}

int SettGui::getBurstAmt() {
	return(this->PopSett->BurstAmountSlider->value());
}

double SettGui::getImageSizeMin() {
	return(this->PopSett->ImageScaleMinSlider->value());
}

double SettGui::getImageSizeMax() {
	return(this->PopSett->ImageScaleMaxSlider->value());

}

void saveAndClose(Fl_Widget* win, void* Src) {
	SettGui* Gui = static_cast<SettGui*>(Src);
	std::ofstream Settings("shared/Settings.txt");
	if (Settings.is_open() == false) {
		std::cout << "error could not open Settings File" << std::endl;
	}
	Settings << "ButtonX=" << std::min(Gui->getButtonX(), Gui->getMaxXButtonHeight()) << std::endl;
	Settings << "ButtonY=" << std::min(Gui->getButtonY(), Gui->getMaxYButtonHeight()) << std::endl;
	Settings << "ButtonText=" << Gui->getButtonText() << std::endl;
	Settings << "PopupLifespan=" << Gui->getPopupLifespan() << std::endl;
	Settings << "ImageFolderPath=" << Gui->getImageFolderPath() << std::endl;
	Settings << "TimeBetweenPopups=" << Gui->getTimeBetweenPopups() << std::endl;
	Settings << "MinXButtonHeight=" << Gui->getMinXButtonHeight() << std::endl;
	Settings << "MaxXButtonHeight=" << Gui->getMaxXButtonHeight() << std::endl;
	Settings << "MinYButtonHeight=" << Gui->getMinYButtonHeight() << std::endl;
	Settings << "MaxYButtonHeight=" << Gui->getMaxYButtonHeight() << std::endl;
	Settings << "Multiplicator=" << Gui->getMultiplicatior() << std::endl;
	Settings << "BurstAmt=" << Gui->getBurstAmt() << std::endl;
	Settings << "PopupFadeOut=" << Gui->getPopupFadeOut() << std::endl;
	Settings << "lowPopupFadeOutSteps=" << Gui->getlowPopupFadeOutSteps() << std::endl;
	Settings << "highPopupFadeOutSteps=" << Gui->gethighPopupFadeOutSteps() << std::endl;
	Settings << "PopupFadeOutTime=" << Gui->getPopupFadeOutTime() << std::endl;
	Settings << "PopupOpacity=" << Gui->getPopupOpacity() << std::endl;
	Settings << "PopupOverlay=" << Gui->getPopupOverlay() << std::endl;
	Settings << "LoggingStrength=" << Gui->getLoggingStrength() << std::endl;
	Settings << "ImageSizeMin=" << Gui->getImageSizeMin() << std::endl;
	Settings << "ImageSizeMax=" << Gui->getImageSizeMax() << std::endl;
	//Settings << "" << Gui << std::endl;
	if (Fl::event() == FL_CLOSE) {
		win->hide();
	}
	else {
		Gui->update(Gui->GetCurrentlyOpenPage());
	}
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
#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <Fl/fl_ask.H>
#include "PopupSettings.hpp"
#include "GeneralSettings.hpp"
#include "AdvancedSettings.hpp"
#include "ImagesSettings.hpp"
#include "../shared/Settings.hpp"

#include <FL/Fl_Box.H>
#include <FL/Fl_Hor_Value_Slider.H>
#include <vector>
#include <string>
#include <filesystem>

class GeneralSettings;

class SettGui {
private:
	int W, H;

	int SelectorButtonW;
	int SelectorButtonH;

	Fl_Window* Gui;
	Fl_Button* saveButton;

	PopupSettings* PopSett;
	GeneralSettings* GenSett;
	AdvancedSettings* AdvSett;
	ImagesSettings* ImgSett;
	
	std::vector<Fl_Button*> SelectorPanelButtons;
	std::vector<const char*> SelectorPanelButtonNames = {
		{"General"},
		{"Popups"},
		{"Images"},
		{"test2"},
		{"Advanced"}
	};
	
	static void ShowSettingWindow(Fl_Widget* w, void* name);
	
	public:
	std::string settingsFileLocation;
	Settings* SettingsFileContent;
	SettGui(std::string loc = "./shared/Settings.txt");
	~SettGui();

	void update(int CurrentlyOpenPageNum);

	void BuildMenueSelectorPanel(std::vector<const char*> &names);
	int GetCurrentlyOpenPage();

	void BuildPopupSettings();

	void setButtonX(int src);
	int getButtonX();
	void setButtonY(int src);
	int getButtonY();
	void setButtonText(char* src);
	const char* getButtonText();
	double gethighPopupLifespan();
	double getlowPopupLifespan();
	void setImageFolderPath(char* src);
	const char* getImageFolderPath();
	double getlowTimeBetweenPopups();
	double gethighTimeBetweenPopups();
	int getMinXButtonHeight();
	void setMinXButtonHeight(int src);
	int getMaxXButtonHeight();
	void setMaxXButtonHeight(int src);
	int getMinYButtonHeight();
	void setMinYButtonHeight(int src);
	int getMaxYButtonHeight();
	void setMaxYButtonHeight(int src);
	int getRange_slider_value_shoving();
	double gethighPopupFadeOutSteps();
	double getlowPopupFadeOutSteps();
	int getlowPopupFadeOutTime();
	int gethighPopupFadeOutTime();	
	double getlowPopupOpacity();
	double gethighPopupOpacity();
	int getLoggingStrength();
	double getlowMultipop();
	double gethighMultipop();
	double gethighMultipopTiming();
	double getlowMultipopTiming();
	double gethighImageScale();
	double getlowImageScale();
	const char* getTrashbinPath();
	double getlowPopupFadeInTime();
	double gethighPopupFadeInTime();
	const char* getSettingsPath();
	const char* getSelectedMainFunction();
	const char* getMainFunction();
};

void Close(Fl_Widget* win, void* Src);
void save(Fl_Widget* Gui, void* Src);
#pragma once

#include <string>
#include <map>
#include "Debug.hpp"

enum Setting
{
	nosett = -1,
	ButtonX,
	ButtonY,
	ButtonText,
	PopupLifespan,
	TimeBetweenPopups,
	ImageFolderPath,
	MinXButtonHeight,
	MaxXButtonHeight,
	MinYButtonHeight,
	MaxYButtonHeight,
	Multiplicator,
	BurstAmt,
	PopupFadeOut,
	Range_slider_value_shoving,
	lowPopupFadeOutSteps,
	highPopupFadeOutSteps,
	PopupFadeOutTime,
	PopupOpacity,
	LoggingStrength,
	Overlay,
	ImageSizeMin,
	ImageSizeMax
};


struct Settings
{
	int ButtonX, ButtonY;
	std::string ButtonText;
	int PopupLifespan;
	double TimeBetweenPopups;
	std::string ImageFolderPath;
	int MinXButtonHeight;
	int MaxXButtonHeight;
	int MinYButtonHeight;
	int MaxYButtonHeight;
	int Multiplicator;
	int BurstAmt;
	bool PopupFadeOut;
	bool Range_slider_value_shoving;
	double lowPopupFadeOutSteps;
	double highPopupFadeOutSteps;
	int PopupFadeOutTime;
	double PopupOpacity;
	int LoggingStrenght;
	int Overlay;
	double ImageSizeMin;
	double ImageSizeMax;
};

Settings*	ReadSettings(const char* str);
Setting		OwOWhatSettingDis(const std::string line, const std::map<std::string, Setting> lineToEnumMap);
void		assign_from_file(std::string line, Setting sett, Settings *settingStruct);
void		setStandardSettingsFile(Settings* sett);

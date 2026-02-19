#pragma once

#include <string>
#include <map>
#include <set>
#include "Debug.hpp"



enum Setting
{
	nosett = -1,
	Name,
	ButtonX,
	ButtonY,
	ButtonText,
	lowPopupLifespan,
	highPopupLifespan,
	lowTimeBetweenPopups,
	highTimeBetweenPopups,
	ImageFolderPath,
	MinXButtonHeight,
	MaxXButtonHeight,
	MinYButtonHeight,
	MaxYButtonHeight,
	lowMultipop,
	highMultipop,
	lowPopupFadeOutSteps,
	highPopupFadeOutSteps,
	lowPopupFadeOutTime,
	highPopupFadeOutTime,
	lowPopupFadeInTime,
	highPopupFadeInTime,
	Range_slider_value_shoving,
	lowPopupOpacity,
	highPopupOpacity,
	LoggingStrength,
	lowImageScale,
	highImageScale,
	TrashbinPath,
	lowMultipopTiming,
	highMultipopTiming,
	SettingsFilePath,
	mainFunction,
};


struct Settings {
	std::string Name;
	int ButtonX, ButtonY;
	std::string ButtonText;
	double lowPopupLifespan;
	double highPopupLifespan;
	double lowTimeBetweenPopups;
	double highTimeBetweenPopups;
	std::string ImageFolderPath;
	int MinXButtonHeight;
	int MaxXButtonHeight;
	int MinYButtonHeight;
	int MaxYButtonHeight;
	double lowMultipop;
	double highMultipop;
	bool Range_slider_value_shoving;
	double lowPopupFadeOutSteps;
	double highPopupFadeOutSteps;
	double lowPopupFadeOutTime;
	double highPopupFadeOutTime;
	double lowPopupFadeInTime;
	double highPopupFadeInTime;
	double lowPopupOpacity;
	double highPopupOpacity;
	double lowImageScale;
	double highImageScale;
	std::string TrashbinPath;
	double lowMultipopTiming;
	double highMultipopTiming;
	std::string SettingsFilePath;
	std::string mainFunction;
};

Settings*				ReadSettings(std::string str);
Setting					OwOWhatSettingDis(const std::string line, const std::map<std::string, Setting> lineToEnumMap);
void					load_from_file(std::string line, Setting sett, Settings *settingStruct);
void					setStandardSettingsFile(Settings* sett);
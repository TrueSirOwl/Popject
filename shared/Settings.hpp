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
	PopupFadeOut,
	Range_slider_value_shoving,
	lowPopupFadeOutSteps,
	highPopupFadeOutSteps,
	lowPopupFadeOutTime,
	highPopupFadeOutTime,
	lowPopupOpacity,
	highPopupOpacity,
	LoggingStrength,
	lowImageScale,
	highImageScale,
	TrashbinPath,
	lowMultipopTiming,
	highMultipopTiming
};


struct Settings
{
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
	bool PopupFadeOut;
	bool Range_slider_value_shoving;
	double lowPopupFadeOutSteps;
	double highPopupFadeOutSteps;
	double lowPopupFadeOutTime;
	double highPopupFadeOutTime;
	double lowPopupOpacity;
	double highPopupOpacity;
	int LoggingStrenght;
	double lowImageScale;
	double highImageScale;
	std::string TrashbinPath;
	double lowMultipopTiming;
	double highMultipopTiming;
};

Settings*	ReadSettings(std::string str);
Setting		OwOWhatSettingDis(const std::string line, const std::map<std::string, Setting> lineToEnumMap);
void		load_from_file(std::string line, Setting sett, Settings *settingStruct);
void		setStandardSettingsFile(Settings* sett);

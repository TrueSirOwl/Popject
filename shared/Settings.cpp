#include "Settings.hpp"
#include <fstream>
#include <iostream>

Settings *ReadSettings(std::string loc) {
	Settings* SettingsStruct = new Settings;
	std::string line;
	std::ifstream setting(loc);
	std::string stdpath = "./shared/Settings.txt";
	if (setting.is_open() == false) {
		std::cerr << "Setting file at: " << loc << " could not be opened!" << std::endl;
		if (loc == stdpath) {
			std::cout << "Standard settings file was not found, creating it" << std::endl;
			std::ofstream creator("shared/Settings.txt");
			setStandardSettingsFile(SettingsStruct);
		} else {
			exit(1);
		}
	} else {
		std::cout << "Standard settings file opened" << std::endl;
	}
	const std::map<std::string, Setting> lineToEnumMap = {
		{"ButtonX", Setting::ButtonX},
		{"ButtonY", Setting::ButtonY},
		{"ButtonText", Setting::ButtonText},
		{"lowPopupLifespan", Setting::lowPopupLifespan},
		{"highPopupLifespan", Setting::highPopupLifespan},
		{"lowTimeBetweenPopups", Setting::lowTimeBetweenPopups},
		{"highTimeBetweenPopups", Setting::highTimeBetweenPopups},
		{"Range_slider_value_shoving", Setting::Range_slider_value_shoving},
		{"ImageFolderPath", Setting::ImageFolderPath},
		{"MinXButtonHeight", Setting::MinXButtonHeight},
		{"MaxXButtonHeight", Setting::MaxXButtonHeight},
		{"MinYButtonHeight", Setting::MinYButtonHeight},
		{"MaxYButtonHeight", Setting::MaxYButtonHeight},
		{"lowMultipop", Setting::lowMultipop},
		{"highMultipop", Setting::highMultipop},
		{"lowMultipopTiming", Setting::lowMultipopTiming},
		{"highMultipopTiming", Setting::highMultipopTiming},
		{"PopupFadeOut", Setting::PopupFadeOut},
		{"lowPopupFadeOutSteps", Setting::lowPopupFadeOutSteps},
		{"highPopupFadeOutSteps", Setting::highPopupFadeOutSteps},
		{"lowPopupFadeOutTime", Setting::lowPopupFadeOutTime},
		{"highPopupFadeOutTime", Setting::highPopupFadeOutTime},
		{"lowPopupOpacity", Setting::lowPopupOpacity},
		{"highPopupOpacity", Setting::highPopupOpacity},
		{"PopupOverlay", Setting::Overlay},
		{"LoggingStrength", Setting::LoggingStrength},
		{"highImageScale",Setting::highImageScale},
		{"lowImageScale", Setting::lowImageScale},
		{"TrashbinPath", Setting::TrashbinPath}
	};
	int settingsDone = 0;
	while (std::getline(setting, line)) {
		load_from_file(line, OwOWhatSettingDis(line, lineToEnumMap), SettingsStruct);
		++settingsDone;
	}

	if (settingsDone < lineToEnumMap.size()) {
		LOG(HERROR,1,"Settings File Corrupt, restoring to standard settings file");
		setStandardSettingsFile(SettingsStruct);
	}
	return(SettingsStruct);
}

Setting OwOWhatSettingDis(std::string line, const std::map<std::string, Setting> lineToEnumMap) {
	const std::string LineSetting = line.substr(0, line.find('='));
	std::map<std::string,Setting>::const_iterator it = lineToEnumMap.find(LineSetting);
	if (it != lineToEnumMap.end()) {
		return (it->second);
	}
	else {
		std::cerr << "invalid setting: " << LineSetting << std::endl;
		return (nosett);
	}
}

void load_from_file(std::string line, Setting sett, Settings* SettingsStruct) {
	switch (sett)
	{
	case Setting::ButtonX:
		SettingsStruct->ButtonX = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::ButtonY:
		SettingsStruct->ButtonY = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::ButtonText:
		SettingsStruct->ButtonText = line.substr(line.find('=') + 1, line.length());
		break;

	case Setting::lowPopupLifespan:
		SettingsStruct->lowPopupLifespan = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highPopupLifespan:
		SettingsStruct->highPopupLifespan = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::lowTimeBetweenPopups:
		SettingsStruct->lowTimeBetweenPopups = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highTimeBetweenPopups:
		SettingsStruct->highTimeBetweenPopups = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::ImageFolderPath:
		SettingsStruct->ImageFolderPath = line.substr(line.find('=') + 1, line.length());
		break;

	case Setting::MinXButtonHeight:
		SettingsStruct->MinXButtonHeight = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::MaxXButtonHeight:
		SettingsStruct->MaxXButtonHeight = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::MinYButtonHeight:
		SettingsStruct->MinYButtonHeight = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;
	
	case Setting::MaxYButtonHeight:
		SettingsStruct->MaxYButtonHeight = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::lowMultipop:
		SettingsStruct->lowMultipop = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highMultipop:
		SettingsStruct->highMultipop = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::PopupFadeOut:
		SettingsStruct->PopupFadeOut = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::lowPopupFadeOutSteps:
		SettingsStruct->lowPopupFadeOutSteps = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highPopupFadeOutSteps:
		SettingsStruct->highPopupFadeOutSteps = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::lowPopupFadeOutTime:
		SettingsStruct->lowPopupFadeOutTime = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highPopupFadeOutTime:
		SettingsStruct->highPopupFadeOutTime = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::lowPopupOpacity:
		SettingsStruct->lowPopupOpacity = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highPopupOpacity:
		SettingsStruct->highPopupOpacity = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::Overlay:
		SettingsStruct->Overlay = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::LoggingStrength:
		SettingsStruct->LoggingStrenght = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::lowImageScale:
		SettingsStruct->lowImageScale = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highImageScale:
		SettingsStruct->highImageScale = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::Range_slider_value_shoving:
		SettingsStruct->Range_slider_value_shoving = std::stoi(line.substr(line.find('=') + 1, line.length()));

	case Setting::TrashbinPath:
		SettingsStruct->TrashbinPath = line.substr(line.find('=') + 1, line.length());
		break;

	case Setting::lowMultipopTiming:
		SettingsStruct->lowMultipopTiming = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highMultipopTiming:
		SettingsStruct->highMultipopTiming = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	default:
		break;
	}
}

void setStandardSettingsFile(Settings* sett) {
	sett->lowMultipop = 1;
	sett->highMultipop = 2;
	sett->ButtonText = "test";
	sett->ButtonX = 10;
	sett->ButtonY = 10;
	sett->ImageFolderPath = "";
	sett->LoggingStrenght = 0;
	sett->MaxXButtonHeight = 100;
	sett->MaxYButtonHeight = 100;
	sett->MinXButtonHeight = 10;
	sett->MinYButtonHeight = 10;
	sett->Overlay = 1;
	sett->PopupFadeOut = true;
	sett->Range_slider_value_shoving = false;
	sett->lowPopupFadeOutSteps = 100;
	sett->highPopupFadeOutSteps = 1000;
	sett->lowPopupFadeOutTime = 1000;
	sett->highPopupFadeOutTime = 5000;
	sett->lowPopupLifespan = 10000;
	sett->highPopupLifespan = 10000;
	sett->lowPopupOpacity = 0.20;
	sett->highPopupOpacity = 0.50;
	sett->lowTimeBetweenPopups = 5000;
	sett->highTimeBetweenPopups = 10000;
	sett->lowImageScale = 0.7;
	sett->highImageScale = 1;
	sett->TrashbinPath = "./Trash";
	sett->lowMultipopTiming = 0;
	sett->highMultipopTiming = 300;
}

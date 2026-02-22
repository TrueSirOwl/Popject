#include "Settings.hpp"
#include "Sqlite.hpp"
#include "Debug.hpp"

Settings* ReadSettings(std::string loc) {
	Settings* SettingsStruct = new Settings;
	std::string line;
	std::ifstream setting(loc);
	std::string stdpath = "./shared/Settings.txt";
	if (setting.is_open() == false) {
		LOG(HERROR, "Setting file at: " + loc + " could not be opened!\nFalling back to standard Settings file");
		if (loc == stdpath) {
			LOG(WARNING, "Standard Settings file was not found, recreating it");
			std::ofstream creator("shared/Settings.txt");
			setStandardSettingsFile(SettingsStruct);
		} else if (loc == "") {
			LOG(WARNING, "Settings location string was empty, loading Standard Settings file");
			setting = std::ifstream(stdpath);
		} else {
			LOG(FATAL, "Unexpected Settings file condition, Aborting");
			exit(1);
		}
		// open settings database,
		// find last opened setting
		// open it
		// read it
		// return struct
	} else {
		LOG(INFO,"Setting file at: " + loc + " opened!" );
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
		{"lowPopupFadeOutSteps", Setting::lowPopupFadeOutSteps},
		{"highPopupFadeOutSteps", Setting::highPopupFadeOutSteps},
		{"lowPopupFadeOutTime", Setting::lowPopupFadeOutTime},
		{"highPopupFadeOutTime", Setting::highPopupFadeOutTime},
		{"lowPopupFadeInTime", Setting::lowPopupFadeInTime},
		{"highPopupFadeInTime", Setting::highPopupFadeInTime},
		{"lowPopupOpacity", Setting::lowPopupOpacity},
		{"highPopupOpacity", Setting::highPopupOpacity},
		{"LoggingStrength", Setting::LoggingStrength},
		{"highImageScale",Setting::highImageScale},
		{"lowImageScale", Setting::lowImageScale},
		{"TrashbinPath", Setting::TrashbinPath},
		{"mainFunction", Setting::mainFunction},
	};
	long unsigned int settingsDone = 0;
	std::set<Setting> done_settings_set;
	Setting found_setting;
	while (std::getline(setting, line)) {
		found_setting = OwOWhatSettingDis(line, lineToEnumMap);
		load_from_file(line, found_setting, SettingsStruct);
		done_settings_set.emplace(found_setting);
		++settingsDone;
	}

	std::set<std::string> missed_settings;

	for (const std::pair<const std::string, Setting>& entry : lineToEnumMap) {
		const std::string& setting_name = entry.first;
		const Setting& setting_enum = entry.second;
		if (done_settings_set.find(setting_enum) == done_settings_set.end()) {
			missed_settings.insert(setting_name);
		}
	}
	
	if (missed_settings.empty() == false) {
		LOG(HERROR, "Settings File Corrupt, or missing entries:" );
		for (const auto& missed : missed_settings) {
			LOG(WARNING, missed);
		}
		if (loc == stdpath) {
			LOG(WARNING, "Standard Settings file was broken, to restore it please save it again");
			setStandardSettingsFile(SettingsStruct);
			return(SettingsStruct);
		}
		setting.close();
		delete (SettingsStruct);
		return(NULL);
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
		LOG(HERROR,"invalid setting: " + LineSetting );
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

	case Setting::lowPopupFadeOutSteps:
		SettingsStruct->lowPopupFadeOutSteps = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highPopupFadeOutSteps:
		SettingsStruct->highPopupFadeOutSteps = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::lowPopupFadeOutTime:
		SettingsStruct->lowPopupFadeOutTime = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highPopupFadeOutTime:
		SettingsStruct->highPopupFadeOutTime = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::lowPopupFadeInTime:
		SettingsStruct->lowPopupFadeInTime = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highPopupFadeInTime:
		SettingsStruct->highPopupFadeInTime = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::lowPopupOpacity:
		SettingsStruct->lowPopupOpacity = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highPopupOpacity:
		SettingsStruct->highPopupOpacity = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::LoggingStrength:
		Log_strength = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::lowImageScale:
		SettingsStruct->lowImageScale = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highImageScale:
		SettingsStruct->highImageScale = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::Range_slider_value_shoving:
		SettingsStruct->Range_slider_value_shoving = std::stoi(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::TrashbinPath:
		SettingsStruct->TrashbinPath = line.substr(line.find('=') + 1, line.length());
		break;

	case Setting::lowMultipopTiming:
		SettingsStruct->lowMultipopTiming = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::highMultipopTiming:
		SettingsStruct->highMultipopTiming = std::stod(line.substr(line.find('=') + 1, line.length()));
		break;

	case Setting::mainFunction:
		SettingsStruct->mainFunction = line.substr(line.find('=') + 1, line.length());
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
	sett->ImageFolderPath = "./Trash";
	sett->MaxXButtonHeight = 100;
	sett->MaxYButtonHeight = 100;
	sett->MinXButtonHeight = 10;
	sett->MinYButtonHeight = 10;
	sett->Range_slider_value_shoving = false;
	sett->lowPopupFadeOutSteps = 100;
	sett->highPopupFadeOutSteps = 1000;
	sett->lowPopupFadeOutTime = 1000;
	sett->highPopupFadeOutTime = 5000;
	sett->lowPopupFadeOutTime = 100;
	sett->highPopupFadeOutTime = 1000;
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
	sett->mainFunction = "Popups";
}

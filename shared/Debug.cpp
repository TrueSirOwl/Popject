#include "Debug.hpp"
#include <algorithm>
#include <ctime>
#include <chrono>
#include <filesystem>

std::ofstream Log;

void CreateLogFile() {
	std::filesystem::create_directory("logs");

	auto runt = std::chrono::system_clock::now();
	std::time_t runTime = std::chrono::system_clock::to_time_t(runt);
	std::string time = "logs/Log_";
	time.append(std::ctime(&runTime));
	time.erase(time.find("\n"));
	time.append(".testlog");
	std::replace(time.begin(), time.end(), ' ', '_');
	std::replace(time.begin() + 2, time.end(), ':', '_');
	Log = std::ofstream(time.c_str());
}

void LOG(HornySeverity s, std::string message) {
	switch (s) {
	case INFO:
		if (Log_strength <= INFO) {
			Log << "INFO: " << message << std::endl;
		}
		break;
	case WARNING:
		if (Log_strength <= WARNING) {
			Log << "WARNING: " << message << std::endl;
		}
		break;
	case HERROR:
		if (Log_strength <= HERROR) {
			Log << "ERROR: " << message << std::endl;
		}
		break;
	case FATAL:
		if (Log_strength <= FATAL) {
			Log << "FATAL: " << message << std::endl;
		}
		break;
	default:
		break;
	}
}
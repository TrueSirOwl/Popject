#pragma once

#include <fstream>
#include <string>

extern std::ofstream Log;
extern int Log_strength;

enum HornySeverity {
	INFO,
	WARNING,
	HERROR,
	FATAL
};

void CreateLogFile();
void LOG(HornySeverity s, std::string message);
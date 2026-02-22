#include "SettGui.hpp"
#include "Sqlite.hpp"
#include <iostream>
#include "Debug.hpp"

int Log_strength = 0;

int main(int argc, char* argv[]) {
	CreateLogFile();
	sqlite3* database;
	SettGui* Gui;
	if(sqlite3_open("shared/Settings_Storage", &database) != SQLITE_OK) {
		LOG(FATAL,"Failed to open databse: ");
		LOG(FATAL,sqlite3_errmsg(database));
		exit(1);
	}
	if (argc < 2) {
		LOG(INFO, "no argument given, trying to load last settings file");
		std::string loc =  Find_last_setting_location(database);
		Gui = new SettGui(database, loc.c_str());
	} else {
		LOG(INFO, "trying to load setting file from: ");
		LOG(INFO, argv[1]);
		std::cout << "trying to load setting file from: " << argv[1] << std::endl;
		std::string str(argv[1]);
		Gui = new SettGui(database, str);
	}
	int i = Fl::run();
	delete(Gui);
	sqlite3_close(database);
	return(i);
}
#pragma once

#include <sqlite3.h>
#include <fstream>
#include <iostream>
#include <map>
#include "Debug.hpp"

void        Restore_default_table(sqlite3* Database);
int         Table_exists_callback(void* data, int argc, char** argv, char** colNames);
std::string Find_last_setting_location(sqlite3* Database);
std::map<std::string, std::string> create_settings_list(sqlite3* database);
int         insert_new_setting_into_settings_table(std::string location, std::string name, sqlite3* database);
void        make_standard_setting_last_opened(sqlite3* database);
void        remove_last_opened_settings_entry(sqlite3* database);
void        change_last_opened_setting(sqlite3* database, std::string location);
std::string get_name_of_setting(sqlite3* database, std::string location);
void        change_settings_name(sqlite3* database, std::string oldname, std::string newname);
void        remove_named_settings_entry(sqlite3* database, std::string name);
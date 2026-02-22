#include "Sqlite.hpp"

int Table_exists_callback(void* data, int argc, char** argv, char** colNames) {
	bool* tableExists = reinterpret_cast<bool*>(data);
	if (argc > 0 && argv[0] != nullptr) {
		*tableExists = true;
	} else {
		*tableExists = false;
	}
	return 0;
}

int get_settings_location_callback(void* data, int argc, char** argv, char** colNames) {
	std::string* output;
	output = static_cast<std::string*>(data);
	if (output->empty() == true) {
		*output = argv[0];
	} else {
		LOG(WARNING, "Database contains more than one last opened file");
		return(1);
	}
	return (0);
}

int row_exists_callback(void* data, int argc, char** argv, char** colNames) {
	bool* rowExists = reinterpret_cast<bool*>(data);
	if (argc > 0 && argv[0] != nullptr) {
		*rowExists = (std::string(argv[0]) == "1");
	} else {
		*rowExists = false;
	}
	return 0;
}

std::string get_name_of_setting(sqlite3* database, std::string location) {
	char* err = NULL;
	std::string name;
	std::string sql = "SELECT NAME FROM SETTINGS_STORAGE WHERE LOCATION = '" + location + "'";
	int ret = sqlite3_exec(database, sql.c_str(), get_settings_location_callback, &name, &err);
	if (ret != SQLITE_OK) {
		LOG(HERROR, err);
		sqlite3_free(err);
	}
	return(name);
}

std::string Find_last_setting_location(sqlite3* database) {
	char* err = NULL;
	bool row_exists = false;
	const char *sql = "SELECT EXISTS(SELECT 1 FROM SETTINGS_STORAGE WHERE OPENED_LAST = 1)";
	int ret = sqlite3_exec(database, sql, row_exists_callback, &row_exists, &err);
	if (row_exists == false) {
		make_standard_setting_last_opened(database);
	}
	sql = "SELECT LOCATION FROM SETTINGS_STORAGE WHERE OPENED_LAST = 1";
	std::string loc;
	static bool retried = false;
	ret = sqlite3_exec(database, sql, get_settings_location_callback, &loc, &err);
	if (ret != SQLITE_OK) {
		if (retried == true) {
			LOG(HERROR,"retry failed");
			sqlite3_free(err);
			exit(1);
		}
		LOG(HERROR,  err);
		LOG(HERROR, "restoring standard table and retrying.");
		sqlite3_free(err);
		Restore_default_table(database);
		retried = true;
		return(Find_last_setting_location(database));
	}
	if (loc == "") {
		LOG(HERROR, "table entry contained no location, removing table entry, and restoring last openend to standard file");
		remove_last_opened_settings_entry(database);
		make_standard_setting_last_opened(database);
	}
	return (loc);
}

void make_standard_setting_last_opened(sqlite3* database) {
	const char *sql = "UPDATE SETTINGS_STORAGE SET OPENED_LAST = 1 WHERE LOCATION = './shared/Settings.txt'";
	char* err = NULL;
	LOG(INFO, "Restoring last opened file to standard file");
	int ret = sqlite3_exec(database, sql, NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		LOG(HERROR, err);
		sqlite3_free(err);
		LOG(INFO, "standard file not found. restoring whole table");
		Restore_default_table(database);
	}
}

void remove_last_opened_settings_entry(sqlite3* database) {
	const char *sql = "DELETE FROM FROM SETTINGS_STORAGE WHERE OPENED_LAST = 1";
	char* err = NULL;
	int ret = sqlite3_exec(database, sql, NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		LOG(HERROR,  err);
		sqlite3_free(err);
	}
}

void remove_named_settings_entry(sqlite3* database, std::string name) {
	std::string sql = "DELETE FROM SETTINGS_STORAGE WHERE NAME = '" + name + "'";
	char* err = NULL;
	int ret = sqlite3_exec(database, sql.c_str(), NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		LOG(HERROR,  err);
		sqlite3_free(err);
	}
}

int create_settings_list_callback(void* set, int argc, char** argv, char** colNames) {
	std::map<std::string, std::string>* locations = static_cast<std::map<std::string, std::string>*>(set);
	if (argc > 0 && argv[0] && argv[1]) {
		locations->emplace(argv[1],argv[0]);
	}
	return 0;
}

std::map<std::string, std::string> create_settings_list(sqlite3* database){
	const char *sql = "SELECT LOCATION, NAME FROM SETTINGS_STORAGE";
	char* err = NULL;
	std::map<std::string, std::string> locations;
	if (sqlite3_exec(database, sql, create_settings_list_callback, &locations, &err) != SQLITE_OK) {
		LOG(WARNING,  err);
		sqlite3_free(err);
	}
	return (locations);
}

int insert_new_setting_into_settings_table(std::string location, std::string name, sqlite3* database) {
	std::string sql = "SELECT * FROM SETTINGS_STORAGE WHERE OPENED_LAST = 1";
	char* err = NULL;
	std::string loc;
	int ret = sqlite3_exec(database, sql.c_str(), get_settings_location_callback, &loc, &err);
	if (ret != SQLITE_OK) {
		LOG(WARNING,  err);
		sqlite3_free(err);
	}
	sql = "UPDATE SETTINGS_STORAGE SET OPENED_LAST = 0 WHERE OPENED_LAST = 1";
	ret = sqlite3_exec(database, sql.c_str(), NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		LOG(WARNING,  err);
		sqlite3_free(err);
	}
	sql = "INSERT INTO SETTINGS_STORAGE VALUES('" + location + "', '" + name + "', '1')";
	ret = sqlite3_exec(database, sql.c_str(), NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		int extended = sqlite3_extended_errcode(database);
		LOG(WARNING,  err);
		sqlite3_free(err);
		sql = "UPDATE SETTINGS_STORAGE SET OPENED_LAST = 1 WHERE LOCATION = " + loc;
		int ret = sqlite3_exec(database, sql.c_str(), NULL, NULL, &err);
		if (ret != SQLITE_OK) {
			LOG(WARNING,  err);
			sqlite3_free(err);
		}
		if (extended == SQLITE_CONSTRAINT_UNIQUE) {
			return(-2);
		}
		return(-1);
	}
	return(0);
}

void change_settings_name(sqlite3* database, std::string oldname, std::string newname) {
	std::string sql = "UPDATE SETTINGS_STORAGE SET NAME = '" + newname + "' WHERE NAME = '" + oldname + "'";
	char* err = NULL;
	int ret = sqlite3_exec(database, sql.c_str(), NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		LOG(WARNING,  err);
		sqlite3_free(err);
	}
}

void change_last_opened_setting(sqlite3* database, std::string location) {
	std::string sql = "UPDATE SETTINGS_STORAGE SET OPENED_LAST = 0 WHERE OPENED_LAST = 1";
	char* err = NULL;
	int ret = sqlite3_exec(database, sql.c_str(), NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		LOG(WARNING,  err);
		sqlite3_free(err);
	}
	sql = "UPDATE SETTINGS_STORAGE SET OPENED_LAST = 1 WHERE LOCATION = '" + location + "'";
	ret = sqlite3_exec(database, sql.c_str(), NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		LOG(WARNING,  err);
		sqlite3_free(err);
	}
}

void Restore_default_table(sqlite3* Database) {
	char* errmsg;
	std::string command =	"CREATE TABLE IF NOT EXISTS SETTINGS_STORAGE("
				"LOCATION		TEXT	NOT NULL PRIMARY KEY,"
				"NAME			TEXT	NOT NULL UNIQUE,"
				"OPENED_LAST	INTEGER	NOT NULL)";
	int err = sqlite3_exec(Database, command.c_str(), NULL, 0, &errmsg);
	if (err == SQLITE_OK) {
		command = "INSERT INTO SETTINGS_STORAGE VALUES('./shared/Settings.txt', 'default', '1')";
		err = sqlite3_exec(Database, command.c_str(), NULL, 0, &errmsg);
		if (err == SQLITE_OK) {
			LOG(INFO,"restoring default table succesful");
			return;
		} else {
			LOG(HERROR, "restoring default table  failed:");
			LOG(FATAL,  errmsg);
			sqlite3_free(errmsg);
		}
	} else {
		LOG(FATAL,  "restoring default Database failed:");
		LOG(FATAL,  errmsg);
		sqlite3_free(errmsg);
		exit(1);
	}
}
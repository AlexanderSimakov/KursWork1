#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "SQLWORK.h"
#include <conio.h>
#include <time.h>

using namespace std;

namespace console {
	string get_authorization_login(SQLWork *db);
	string get_exists_login(SQLWork* db);
	string get_exists_field(SQLWork* db, string field);
	string get_non_existent_field(SQLWork* db, string field);
	string get_free_login(SQLWork* db);
	bool is_all_symbols_and_nums(string line);
	string get_authorization_password(string true_hash, string true_salt);
	string password_format_input();
	int get_number(bool is_positive = false);
	int get_number_from_range(int min, int max);

}

namespace help {
	string get_generated_salt();
	string generate_hash(string line, string salt);

}





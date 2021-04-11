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
	string get_free_login(SQLWork* db);
	bool is_login_symbols_ok(string login);
	string get_authorization_password(string true_hash, string true_salt);
	string password_format_input();

}

namespace help {
	string get_generated_salt();
	string generate_hash(string line, string salt);

}





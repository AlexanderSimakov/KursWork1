#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "SQLWORK.h"
#include <conio.h>

using namespace std;

namespace console {
	string get_authorization_login(SQLWork *db);
	string get_free_login(SQLWork* db);
	bool is_login_symbols_ok(string login);
	string get_authorization_password(string true_password);
	string password_format_input();

}





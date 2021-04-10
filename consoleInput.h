#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "SQLWORK.h"

using namespace std;

namespace console {
	string get_login(SQLWork *db);
	bool is_login_symbols_ok(string login);



}





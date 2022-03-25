#pragma once
#include <string>
#include <iostream>
#include "Account/Account.h"
#include "../sqlwork/SQLWORK.h"
#include "Console/ConsoleOut.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <conio.h>
#include <Windows.h>
#endif


using namespace std;

namespace console {
	string get_login(SQLWork *db);
	string get_exists_login(SQLWork* db, string line_for_user = "Login: ");
	string get_free_login(SQLWork* db, string line_for_user = "\n> ");
	string get_password(string true_hash, string true_salt);

	string get_exists_product_name(SQLWork* db, string line_for_user = "Name: ");
	string get_non_existent_product_name(SQLWork* db, string line_for_user = "Name: ");
	
	string get_format_date(string line_for_user = "\n> ");

	string password_format_input(string line_for_user = "");
	bool is_all_symbols_and_nums(string line);
	int get_number(bool is_positive = false, string line_for_user = "\n> ");
	int get_number_from_range(int min, int max, string out_line = "\n> ");
}

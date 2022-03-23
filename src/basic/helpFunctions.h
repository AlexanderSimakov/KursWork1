#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include "../sqlwork/SQLWORK.h"
#include "../sha/sha256.h"
#include "ConsoleOut.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <conio.h>
#include <Windows.h>
#endif


using namespace std;

namespace console {
	enum Color {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
 		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Yellow = 14,
		White = 15  
#elif __linux__
		Black = 30,
		Red = 31,
		Green = 32,
		Yellow = 33,
		Blue = 34,
		Magenta = 35,
		Cyan = 36,
		White = 37,
#endif
	};

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

namespace help_functions {
	const int SALT_SIZE = 16; 
	const int SYMBOLS_SIZE = 62;
	string get_generated_salt();
	string get_generated_hash(string line, string salt);
	string get_symbols_for_salt();
	string generate_salt(int salt_size);
	bool is_symbol_right_for_password(char symbol);
}

#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "SQLWORK.h"
#include <conio.h>
#include <time.h>
#include <Windows.h>

using namespace std;


namespace console {
	enum Color {
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};

	string get_true_confirmed_login(SQLWork *db);
	string get_exists_login(SQLWork* db, string line_for_user = "Логин: ");
	string get_free_login(SQLWork* db, string line_for_user = "\n> ");
	string get_suitable_password(string true_hash, string true_salt);

	string get_exists_product_name(SQLWork* db, string line_for_user = "Название: ");
	string get_non_existent_product_name(SQLWork* db, string line_for_user = "Название: ");
	
	string get_format_date();

	string password_format_input(string line_for_user = "");
	bool is_all_symbols_and_nums(string line);
	int get_number(bool is_positive = false, string line_for_user = "\n> ");
	int get_number_from_range(int min, int max, string out_line = "\n> ");

	void show_error(string message, string pref_line = "\t", string post_line = "\n");
	void show_title(string title, string pref_line = "\t", string post_line = "\n");
	void show_info(string info, string pref_line = "\t", string post_line = "\n");
	void set_color(Color text_color = Color::White, Color back_color = Color::Black);
}

namespace help_functions {
	string get_generated_salt();
	string get_generated_hash(string line, string salt);
}





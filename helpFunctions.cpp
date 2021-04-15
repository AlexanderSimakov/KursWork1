#pragma once
#include "helpFunctions.h"



string console::get_authorization_login(SQLWork* db) {
	string login, user_hash;
	while (true) {
		cout << "Логин: ";
		cin >> login;
		cin.ignore(256, '\n');
		user_hash = db->get_text("LOGIN", login, 1);

		if (login == "0") { // 0 - для выхода
			return "0";
		}
		else if (login.size() < 4) {
			show_error_message("Слишком маленький логин");
		}
		else if (!console::is_all_symbols_and_nums(login)) {
			show_error_message("Логин содержит недопустимые символы");
		}
		else if (user_hash == "") {
			show_error_message("Аккаунта с таким логином не существует");
		}
		else if (db->get_int("LOGIN", login, 4) == 0) {
			show_error_message("В данный момент использование аккаунта невозможно, так как администратор еще не подтвердил его");
		}
		else {
			return login;
		}
	}
}

string console::get_exists_login(SQLWork* db) {
	string login, user_hash;
	while (true) {
		cout << "Логин: ";
		cin >> login;
		cin.ignore(256, '\n');
		user_hash = db->get_text("LOGIN", login, 1);

		if (login == "0") { // 0 - для выхода
			return "0";
		}
		else if (login.size() < 4) {
			show_error_message("Слишком маленький логин");
		}
		else if (!console::is_all_symbols_and_nums(login)) {
			show_error_message("Логин содержит недопустимые символы");
		}
		else if (user_hash == "") {
			show_error_message("Аккаунта с таким логином не существует");
		}
		else {
			return login;
		}
	}
}

string console::get_exists_field(SQLWork* db, string field) {
	string input, reg_name;
	while (true) {
		cout << "> ";
		getline(cin, input);

		reg_name = db->get_text(field, input, 4);

		if (input == "0") { // 0 - для выхода
			return "0";
		}
		else if (reg_name == "") {
			show_error_message("Ошибка, проверьте ввод");
		}
		else {
			return input;
		}
	}
}

string console::get_non_existent_field(SQLWork* db, string field) {
	string input, reg_name;
	while (true) {
		cout << "> ";
		getline(cin, input);
		
		reg_name = db->get_text(field, input, 4);

		if (input == "0") { // 0 - для выхода
			return "0";
		}
		else if (reg_name != "") {
			show_error_message("Товар с таким полем уже существует");
		}
		else {
			return input;
		}
	}

	
}

string console::get_format_data() {
	string data;
	
	while (true) {
		cout << "> ";
		cin >> data;
		cin.ignore(256, '\n');

		if (data == "0") return "0";
		else if (data.size() < 10) {
			show_error_message("Слишком маленькое введенное значение");
		}
		else if (data[4] == '-' && data[7] == '-') {
			return data;
		}
		else {
			show_error_message("Ошибка, проверьте формат введенной даты (ГГГГ-ММ-ДД)");
		}
	}
}

string console::get_free_login(SQLWork* db, string out_line) {
	string login;
	while (true) {
		cout << out_line;
		cin >> login;
		cin.ignore(256, '\n');

		if (login == "0") { // 0 - для выхода
			return "0";
		}
		else if (login.size() < 4) {
			show_error_message("Слишком маленький логин");
		}
		else if (!console::is_all_symbols_and_nums(login)) {
			show_error_message("Логин содержит недопустимые символы");
		}
		else if (db->get_text("LOGIN", login, 1) != "") {
			show_error_message("Логин занят");
		}
		else {
			return login;
		}
	}
}

bool console::is_all_symbols_and_nums(string line) {
	int ch;
	for (int ch = 0, i = 0; i < line.size(); i++) {
		ch = (int)line[i];
		if (ch < 48 || ch > 57 && ch < 65 || ch > 90 && ch < 97 || ch > 122) {
			return false;
		}
	}
	return true;
}

string console::get_authorization_password(string true_hash, string true_salt) {
	string input_password;

	while (true) {
		cout << "Пароль: ";
		input_password = console::password_format_input();
		if (input_password == "0") {
			return "0";
		}
		else if (true_hash != help::generate_hash(input_password, true_salt)) {
			show_error_message("Вы ввели неправильный пароль, попробуйте снова");
		}
		else break;
	}

	return input_password;
}

string console::password_format_input(string out_line) {
	string input_password;
	unsigned char p;

	cout << out_line;

	do
	{
		p = _getch();

		if (p == 13) {
			cout << endl;
			break;
		}
		if (p == '\b' && !input_password.empty())
		{
			cout << '\b' << ' ' << '\b';

			input_password.pop_back();
			continue;
		}
		if (isalnum((unsigned char)p))
		{
			cout << '*';
			input_password.push_back(p);
		}

	} while (true);

	return input_password;
}

int console::get_number(bool is_positive, string out_line) {
	int number;
	while (true) {
		cout << out_line;
		cin >> number;

		if (cin.get() == '\n') {
			if (is_positive && number >= 0) {
				break;
			}
			else if (!is_positive) {
				break;
			}
			else {
				show_error_message("Число должно быть положительным");
			}
		}
		else {
			cin.clear();
			cin.ignore(256, '\n');
			show_error_message("Неправильный ввод");
		}
	}
	return number;
}

int console::get_number_from_range(int min, int max, string out_line) {
	int number;

	while (true) {
		number = get_number(false, out_line);
		if (number >= min && number <= max) return number;
		else show_error_message("Введенное значение должно принадлежать промежутку [" + to_string(min) + ", " + to_string(max) + "]");
	}
}

string help::get_generated_salt() {
	srand(time(0));
	const char SYMBOLS[] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
	string salt = "";

	for (int i = 0; i < 30; i++) {
		salt += SYMBOLS[rand() % 53];
	}

	return salt;
}

string help::generate_hash(string line, string salt) {
	return to_string(hash<decltype(line)>{}(line + salt));
}

void console::show_error_message(string message, string pref_line, string post_line) {
	set_color(Color::LightRed);
	cout << pref_line + "<-- " + message + " -->" + post_line;
	set_color();
}

void console::show_title(string title, string pref_line, string post_line) {
	set_color(Color::Yellow);
	cout << pref_line + "<-- " + title + " -->" + post_line;
	set_color();
}

void console::set_color(Color text_color, Color back_color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((back_color << 4) | text_color));
}





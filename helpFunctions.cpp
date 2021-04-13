#pragma once
#include "helpFunctions.h"



string console::get_authorization_login(SQLWork* db) {
	string login, user_hash;
	while (true) {
		cout << "Логин: ";
		cin >> login;
		user_hash = db->get_text("LOGIN", login, 1);

		if (login == "0") { // 0 - для выхода
			return "0";
		}
		else if (login.size() < 4) {
			cout << "<-- Слишком маленький логин -->\n" << endl;
		}
		else if (!console::is_all_symbols_and_nums(login)) {
			cout << "<-- Логин содержит недопустимые символы -->\n" << endl;
		}
		else if (user_hash == "") {
			cout << "Аккаунта с таким логином не существует\n" << endl;
		}
		else if (db->get_int("LOGIN", login, 4) == 0) {
			cout << "В данный момент использование аккаунта невозможно, так как администратор еще не подтвердил его.\n" << endl;
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
		user_hash = db->get_text("LOGIN", login, 1);

		if (login == "0") { // 0 - для выхода
			return "0";
		}
		else if (login.size() < 4) {
			cout << "<-- Слишком маленький логин -->\n" << endl;
		}
		else if (!console::is_all_symbols_and_nums(login)) {
			cout << "<-- Логин содержит недопустимые символы -->\n" << endl;
		}
		else if (user_hash == "") {
			cout << "Аккаунта с таким логином не существует\n" << endl;
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
		
		cin >> input;

		reg_name = db->get_text(field, input, 4);

		if (input == "0") { // 0 - для выхода
			return "0";
		}
		else if (reg_name == "") {
			cout << "<- Ошибка, проверьте ввод ->\n" << endl;
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
		
		cin >> input;
		
		reg_name = db->get_text(field, input, 4);

		if (input == "0") { // 0 - для выхода
			return "0";
		}
		else if (reg_name != "") {
			cout << "<- Товар с таким полем уже существует ->\n" << endl;
		}
		else {
			return input;
		}
	}

	
}

string console::get_free_login(SQLWork* db) {
	string login;
	while (true) {
		cout << "Логин: ";
		cin >> login;

		if (login == "0") { // 0 - для выхода
			return "0";
		}
		else if (login.size() < 4) {
			cout << "<-- Слишком маленький логин -->\n" << endl;
		}
		else if (!console::is_all_symbols_and_nums(login)) {
			cout << "<-- Логин содержит недопустимые символы -->\n" << endl;
		}
		else if (db->get_text("LOGIN", login, 1) != "") {
			cout << "<-- Логин занят -->\n" << endl;
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
			cout << "Вы ввели неправильный пароль, попробуйте снова.\n" << endl;
		}
		else break;
	}

	return input_password;
}

string console::password_format_input() {
	string input_password;
	unsigned char p;
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

int console::get_number(bool is_positive) {
	int number;
	while (true) {
		cout << "\n> ";
		cin >> number;

		if (cin.get() == '\n') {
			if (is_positive && number >= 0) {
				break;
			}
			else if (!is_positive) {
				break;
			}
			else {
				cout << "<-- Число должно быть положительным -->" << endl;
			}
		}
		else {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "<-- Неправильный ввод -->" << endl;
		}
	}
	return number;
}

int console::get_number_from_range(int min, int max) {
	int number;

	while (true) {
		number = get_number();
		if (number >= min && number <= max) return number;
		else cout << "<-- Введенное значение должно принадлежать промежутку [" << min << ", " << max << "]... -->" << endl;
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

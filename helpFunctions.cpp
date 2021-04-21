#pragma once
#include "helpFunctions.h"


// возвращает логин с проверкой ввода и только тогда, когда аккаунт подтвержден. '0' - для выхода
string console::get_true_confirmed_login(SQLWork* db) {
	string input_login, account_hash;
	while (true) {
		cout << "Логин: ";
		cin >> input_login;
		cin.ignore(256, '\n');
		account_hash = db->get_text("LOGIN", input_login, 1);

		if (input_login == "0") { // 0 - для выхода
			return "0";
		}
		else if (input_login.size() < 4) {
			show_error("Слишком маленький логин");
		}
		else if (!console::is_all_symbols_and_nums(input_login)) {
			show_error("Логин содержит недопустимые символы");
		}
		else if (account_hash == "") {
			show_error("Аккаунта с таким логином не существует");
		}
		else if (db->get_int("LOGIN", input_login, 4) == 0) {
			show_error("В данный момент использование аккаунта невозможно, так как администратор еще не подтвердил его");
		}
		else {
			return input_login;
		}
	}
}

// возвращает существующий логин. '0' - для выхода
string console::get_exists_login(SQLWork* db, string line_for_user) {
	string input_login, account_hash;
	while (true) {
		cout << line_for_user;
		cin >> input_login;
		cin.ignore(256, '\n');
		account_hash = db->get_text("LOGIN", input_login, 1);

		if (input_login == "0") { // 0 - для выхода
			return "0";
		}
		else if (input_login.size() < 4) {
			show_error("Слишком маленький логин");
		}
		else if (!console::is_all_symbols_and_nums(input_login)) {
			show_error("Логин содержит недопустимые символы");
		}
		else if (account_hash == "") {
			show_error("Аккаунта с таким логином не существует");
		}
		else {
			return input_login;
		}
	}
}

// возвращает логин, которого нет в базе данных. '0' - для выхода
string console::get_free_login(SQLWork* db, string line_for_user) {
	string input_login;
	while (true) {
		cout << line_for_user;
		cin >> input_login;
		cin.ignore(256, '\n');

		if (input_login == "0") { // 0 - для выхода
			return "0";
		}
		else if (input_login.size() < 4) {
			show_error("Слишком маленький логин");
		}
		else if (!console::is_all_symbols_and_nums(input_login)) {
			show_error("Логин содержит недопустимые символы");
		}
		else if (db->get_text("LOGIN", input_login, 1) != "") {
			show_error("Логин занят");
		}
		else {
			return input_login;
		}
	}
}

// возвращает пароль, подходящий к введенному хешу и соли. '0' - для выхода
string console::get_suitable_password(string true_hash, string true_salt) {
	string input_password;

	while (true) {
		cout << "Пароль: ";
		input_password = console::password_format_input();
		if (input_password == "0") {
			return "0";
		}
		else if (true_hash != help_functions::get_generated_hash(input_password, true_salt)) {
			show_error("Вы ввели неправильный пароль, попробуйте снова");
		}
		else break;
	}

	return input_password;
}

// возвращет название существующего товара. '0' - для выхода
string console::get_exists_product_name(SQLWork* db, string line_for_user) {
	string input, reg_name;
	while (true) {
		cout << line_for_user;
		getline(cin, input);

		reg_name = db->get_text("NAME", input, 4);

		if (input == "0") { // 0 - для выхода
			return "0";
		}
		else if (reg_name == "") {
			show_error("Товар с таким названием не найден");
		}
		else {
			return input;
		}
	}
}

// возвращет название не существующего товара. '0' - для выхода
string console::get_non_existent_product_name(SQLWork* db, string line_for_user) {
	string input, reg_name;
	while (true) {
		cout << line_for_user;
		getline(cin, input);
		
		reg_name = db->get_text("NAME", input, 4);

		if (input == "0") { // 0 - для выхода
			return "0";
		}
		else if (reg_name != "") {
			show_error("Товар с таким названием уже существует");
		}
		else {
			return input;
		}
	}

	
}

// возвращает дату с проверкой ввода
string console::get_format_date() {
	string date;
	
	while (true) {
		cout << "> ";
		cin >> date;
		cin.ignore(256, '\n');

		if (date == "0") return "0";
		else if (date.size() < 10) {
			show_error("Слишком маленькое введенное значение");
		}
		else if (date[4] == '-' && date[7] == '-') {
			return date;
		}
		else {
			show_error("Ошибка, проверьте формат введенной даты (ГГГГ-ММ-ДД)");
		}
	}
}

// возвращает введенный звездочками пароль
string console::password_format_input(string line_for_user) {
	string input_password;
	unsigned char symbol;

	cout << line_for_user;
	do
	{
		symbol = _getch();

		if (symbol == 13) {
			cout << endl;
			break;
		}
		else if (symbol == '\b' && !input_password.empty()){
			cout << '\b' << ' ' << '\b';
			input_password.pop_back();
		}
		else if (isalnum((unsigned char)symbol)){
			cout << '*';
			input_password.push_back(symbol);
		}

	} while (true);

	return input_password;
}

// возвращает true, если строка состоит только из букв и цифр
bool console::is_all_symbols_and_nums(string line) {
	for (int symbol = 0, i = 0; i < line.size(); i++) {
		symbol = (int)line[i];
		if (symbol < 48 || symbol > 57 && symbol < 65 || symbol > 90 && symbol < 97 || symbol > 122) {
			return false;
		}
	}
	return true;
}

// возвращает целое число с проверкой ввода
int console::get_number(bool is_positive, string line_for_user) {
	int number;
	while (true) {
		cout << line_for_user;
		cin >> number;

		if (cin.get() == '\n') {
			if (is_positive && number >= 0) {
				break;
			}
			else if (!is_positive) {
				break;
			}
			else {
				show_error("Число должно быть положительным");
			}
		}
		else {
			cin.clear();
			cin.ignore(256, '\n');
			show_error("Неправильный ввод");
		}
	}
	return number;
}

// возвращает целое число с проверкой ввода из интервала
int console::get_number_from_range(int min, int max, string line_for_user) {
	int number;

	while (true) {
		number = get_number(false, line_for_user);
		if (number >= min && number <= max) return number;
		else show_error("Введенное значение должно принадлежать промежутку [" + to_string(min) + ", " + to_string(max) + "]");
	}
}

// выводит сообщение в формате ошибки
void console::show_error(string message, string pref_line, string post_line) {
	set_color(Color::LightRed);
	cout << pref_line + "<-- " + message + " -->" + post_line;
	set_color();
}

// выводит сообщение в формате заголовка
void console::show_title(string title, string pref_line, string post_line) {
	set_color(Color::Yellow);
	cout << pref_line + "<-- " + title + " -->" + post_line;
	set_color();
}

// выводит сообщение в формате информации
void console::show_info(string info, string pref_line, string post_line) {
	set_color(Color::Green);
	cout << pref_line + "<-- " + info + " -->" + post_line;
	set_color();
}

// устанавливает цвет и фон последующего текста
void console::set_color(Color text_color, Color back_color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((back_color << 4) | text_color));
}


// возвращает сгенерированную рандомно соль
string help_functions::get_generated_salt() {
	srand(time(0));
	const char SYMBOLS[] = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890";
	string salt = "";

	for (int i = 0; i < 30; i++) {
		salt += SYMBOLS[rand() % 63];
	}

	return salt;
}

// возвращает хешированную солью строку
string help_functions::get_generated_hash(string line, string salt) {
	return to_string(hash<decltype(line)>{}(line + salt));
}



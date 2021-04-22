#pragma once
#include "helpFunctions.h"

// возвращает логин с проверкой ввода. '0' - для выхода
string console::get_login(SQLWork* db) {
	string input_login;
	while (true) {
		cout << "Логин: ";
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

// возвращает пароль, подходящий к введенному хешу и соли. '0' - выхода. '-1' - неправильный логин или пароль
string console::get_password(string true_hash, string true_salt) {
	string input_password = console::password_format_input("Пароль: ");
	if (input_password == "0") { // выход
		return "0";
	}
	else if (true_hash != help_functions::get_generated_hash(input_password, true_salt)) { // неправильный логин или пароль
		return "-1";
	}
	else { // все хорошо
		return input_password;
	}
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
string console::get_format_date(string line_for_user) {
	string date;
	
	while (true) {
		cout << line_for_user;
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
		else if (help_functions::is_symbol_right_for_password(symbol)){
			cout << '*';
			input_password.push_back(symbol);
		}

	} while (true);

	return input_password;
}

// возвращает true, если символ подходит для пароля
bool help_functions::is_symbol_right_for_password(char symbol) {
	string right_symbols = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
	for (int i = 0; i < right_symbols.size(); i++) {
		if (symbol == right_symbols[i]) return true;
	}
	return false;
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
	return generate_salt(SALT_SIZE);
}

// возвращает хешированную солью строку
string help_functions::get_generated_hash(string line, string salt) {
	return sha1(sha1(line + salt) + sha1(line));
}

// генерирует строку из символов и чисел для соли
string help_functions::get_symbols_for_salt(){
	string symbols;
	symbols.reserve(SYMBOLS_SIZE);

	char little_letter = 'a';
	char big_letter = 'A';
	char number = '0';
	for (int k = 0; k < 26; k++){
		symbols.push_back(little_letter++);
		symbols.push_back(big_letter++);
		if (k < 10) symbols.push_back(number++);
	}

	return symbols;
}

// возвращает сгенерированную соль
string help_functions::generate_salt(int salt_size){
	string symbols = get_symbols_for_salt();

	srand(time(NULL));

	string salt;
	salt.reserve(salt_size);

	for (int i = 0; i < salt_size; i++){
		salt.push_back(symbols[rand() % SYMBOLS_SIZE]);
	}

	return salt;
}

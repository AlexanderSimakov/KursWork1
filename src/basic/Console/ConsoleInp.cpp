#include "ConsoleInp.h"


string ConsoleInp::get_login() {
	string input_login;
	while (true) {
		cout << "Login: ";
		cin >> input_login;
		cin.ignore(256, '\n');
		
		if (input_login == "0") {
			return "0";
		}
		else if (input_login.size() < 4) {
			ConsoleOut::show_error("Login is too small");
		}
		else if (!is_all_symbols_and_nums(input_login)) {
			ConsoleOut::show_error("Login contains wrong symbols");
		}
		else {
			return input_login;
		}
	}
}

string ConsoleInp::get_exists_login(AccountsDB* db, string line_for_user) {
	string input_login;
	while (true) {
		cout << line_for_user;
		cin >> input_login;
		cin.ignore(256, '\n');

		if (input_login == "0") {
			return "0";
		}
		else if (input_login.size() < 4) {
			ConsoleOut::show_error("Login is too small");
		}
		else if (!is_all_symbols_and_nums(input_login)) {
			ConsoleOut::show_error("Login contains wrong symbols");
		}
		else if (!db->is_account_exists(input_login)) {
			ConsoleOut::show_error("There is no account with such login");
		}
		else {
			return input_login;
		}
	}
}

string ConsoleInp::get_free_login(AccountsDB* db, string line_for_user) {
	string input_login;
	while (true) {
		cout << line_for_user;
		cin >> input_login;
		cin.ignore(256, '\n');

		if (input_login == "0") {
			return "0";
		}
		else if (input_login.size() < 4) {
			ConsoleOut::show_error("Login is too small");
		}
		else if (!is_all_symbols_and_nums(input_login)) {
			ConsoleOut::show_error("Login contains wrong symbols");
		}
		else if (db->is_account_exists(input_login)) {
			ConsoleOut::show_error("This login already exists");
		}
		else {
			return input_login;
		}
	}
}

string ConsoleInp::get_password(string true_hash, string true_salt) {
	string input_password = password_format_input("Password: ");
	if (input_password == "0") {
		return "0";
	}
	else if (true_hash != Account::get_generated_hash(input_password, true_salt)) {
		return "-1";
	}
	else {
		return input_password;
	}
}

string ConsoleInp::get_exists_product_name(ProductsDB* db, string line_for_user) {
	string name;
	while (true) {
		cout << line_for_user;
		getline(cin, name);

		if (name == "0") {
			return "0";
		}
		else if (!db->is_product_exists(name)) {
			ConsoleOut::show_error("There are no product with such name");
		}
		else {
			return name;
		}
	}
}

string ConsoleInp::get_non_existent_product_name(ProductsDB* db, string line_for_user) {
	string name;
	while (true) {
		cout << line_for_user;
		getline(cin, name);
		
		if (name == "0") {
			return "0";
		}
		else if (db->is_product_exists(name)) {
			ConsoleOut::show_error("Product with such name already exist");
		}
		else {
			return name;
		}
	}
}

string ConsoleInp::get_format_date(string line_for_user) {
	string date;
	
	while (true) {
		cout << line_for_user;
		cin >> date;
		cin.ignore(256, '\n');

		if (date == "0") return "0";
		else if (date.size() < 10) {
			ConsoleOut::show_error("Wrong input, shoud be (yyyy-mm-dd)");
		}
		else if (date[4] == '-' && date[7] == '-') {
			return date;
		}
		else {
			ConsoleOut::show_error("Wrong input, shoud be (yyyy-mm-dd)");
		}
	}
}

string ConsoleInp::password_format_input(string line_for_user) {
	// TODO check input
	string input_password;
	unsigned char symbol;

	cout << line_for_user;
	cin >> input_password;
	return input_password;
}

bool ConsoleInp::is_all_symbols_and_nums(string line) {
	for (int symbol = 0, i = 0; i < line.size(); i++) {
		symbol = (int)line[i];
		if (symbol < 48 || symbol > 57 && symbol < 65 || symbol > 90 && symbol < 97 || symbol > 122) {
			return false;
		}
	}
	return true;
}

int ConsoleInp::get_number(bool is_positive, string line_for_user) {
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
				ConsoleOut::show_error("Number should be positive");
			}
		}
		else {
			cin.clear();
			cin.ignore(256, '\n');
			ConsoleOut::show_error("Wrong input");
		}
	}
	return number;
}

int ConsoleInp::get_number_from_range(int min, int max, string line_for_user) {
	int number;

	while (true) {
		number = get_number(false, line_for_user);
		if (number >= min && number <= max) return number;
		else ConsoleOut::show_error("Input number should be between [" + to_string(min) + ", " + to_string(max) + "]");
	}
}

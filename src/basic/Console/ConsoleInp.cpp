#include "ConsoleInp.hpp"

string ConsoleInp::get_login() 
{
	string login;
	while (true) 
	{
		cout << "Login: ";
		cin >> login;
		cin.ignore(256, '\n');
		
		if (login == "0") return "0";
		else if (login.size() < 4) ConsoleOut::show_error("Login is too small");
		else if (!is_all_symbols_and_nums(login)) ConsoleOut::show_error("Login contains wrong symbols");
		else return login;
	}
}

string ConsoleInp::get_exists_login(AccountsDB* accounts_db) 
{
	string login;
	while (true) 
	{
		login = get_login();

		if(login == "0" || accounts_db->is_account_exists(login)) return login;
		else ConsoleOut::show_error("There is no account with such login");
	}
}

string ConsoleInp::get_free_login(AccountsDB* accounts_db) 
{
	string login;
	while (true) 
	{
		login = get_login();

		if (accounts_db->is_account_exists(login)) ConsoleOut::show_error("This login already exists");	
		else return login;
	}
}

string ConsoleInp::get_password(string hash, string salt) 
{
	string password = password_format_input();
	if (password == "0") return "0";
	else if (hash != Account::get_generated_hash(password, salt)) return "-1";
	else return password;
}

string ConsoleInp::get_exists_product_name(ProductsDB* products_db) 
{
	string name;
	while (true) 
	{
		cout << "Name: ";
		getline(cin, name);

		if (name == "0") return "0";
		else if (!products_db->is_product_exists(name)) ConsoleOut::show_error("There are no product with such name");
		else return name;
	}
}

string ConsoleInp::get_non_existent_product_name(ProductsDB* products_db) 
{
	string name;
	while (true) 
	{
		cout << "Name: ";
		getline(cin, name);
		
		if (name == "0") return "0";
		else if (products_db->is_product_exists(name)) ConsoleOut::show_error("Product with such name already exist");
		else return name;
	}
}

string ConsoleInp::get_format_date() 
{
	string date;
	while (true) 
	{
		cout << "Date: ";
		cin >> date;
		cin.ignore(256, '\n');

		if (date == "0") return "0";
		else if (date.size() < 10) ConsoleOut::show_error("Wrong input, shoud be (yyyy-mm-dd)");
		else if (date[4] == '-' && date[7] == '-') return date;
		else ConsoleOut::show_error("Wrong input, shoud be (yyyy-mm-dd)");
	}
}

string ConsoleInp::password_format_input() 
{
	// TODO check input
	string input_password;

	cout << "Password: ";
	cin >> input_password;
	return input_password;
}

bool ConsoleInp::is_all_symbols_and_nums(string line) 
{
	for (int symbol = 0, i = 0; i < line.size(); i++) 
	{
		symbol = (int)line[i];
		if (symbol < 48 || symbol > 57 && symbol < 65 || symbol > 90 && symbol < 97 || symbol > 122) 
		{
			return false;
		}
	}
	return true;
}

int ConsoleInp::get_number(bool is_positive, string line_for_user) 
{
	int number;
	while (true) 
	{
		cout << line_for_user;
		cin >> number;

		if (cin.get() == '\n') 
		{
			if (is_positive && number >= 0) break;
			else if (!is_positive) break;
			else ConsoleOut::show_error("Number should be positive");
		}
		else 
		{
			cin.clear();
			cin.ignore(256, '\n');
			ConsoleOut::show_error("Wrong input");
		}
	}
	return number;
}

int ConsoleInp::get_number_from_range(int min, int max, string line_for_user) 
{
	int number;
	while (true) 
	{
		number = get_number(false, line_for_user);
		if (number >= min && number <= max) return number;
		else ConsoleOut::show_error("Input number should be between [" + to_string(min) + ", " + to_string(max) + "]");
	}
}

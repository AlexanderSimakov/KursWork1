#pragma once
#include "session.h"


Session::Session(SQLWork* product_db, SQLWork* account_db) {
	this->product_db = product_db;
	this->account_db = account_db;
	init_admin_menu();
	init_user_menu();
	init_confirm_operation_menu();
}

void Session::init_admin_menu() {
	admin_menu = new Menu("<- Admin menu ->",
		{ " Accounts",
		  " Products",
		  " Log Out" });
	admin_menu->set_start_with_first_line(true);

	accounts_manage_menu = new Menu("<- Accounts ->",
		{ " Show",
		  " Add new",
		  " Edit",
		  " Delete",
		  " Confirm",
		  " Block",
		  " Exit" });

	products_manage_menu = new Menu("<- product manage menu ->",
		{ " show",
		  " add",
		  " delete",
		  " edit",
		  " individual task",
		  " find by name",
		  " find by name of registrant",
		  " find by date",
		  " sort by name",
		  " sort by price to higher",
		  " sort by amount to higher",
		  " exit" });

	account_edit_menu = new Menu({ " login", " password", " role", " exit" });
	account_edit_menu->set_start_with_first_line(true);

	product_edit_menu = new Menu({ " name", " amount", " price", " date", " product registrant", " exit" });
	product_edit_menu->set_start_with_first_line(true);
}

void Session::init_user_menu() {
	user_menu = new Menu("<- ���� ������ � �������� ->",
		{ " product table",
		  " individual task",
		  " find products by name",
		  " find products by name registrant",
		  " find products by date",
		  " sort products by name",
		  " sort products by price to higher",
		  " sort products by amount to higher",
		  " log out" });
}

void Session::init_confirm_operation_menu() {
	confirm_operation_menu = new Menu({ " Yes", " No" });
	confirm_operation_menu->set_start_with_first_line(true);
}

void Session::start_as_user(string login) {
	this->session_account_login = login;
	int choise = 0;
	while (true) {
		choise = user_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0:
			show_products_table();
			system("pause");
			break;
		case 1:
			individual_task();
			break;
		case 2:
			find_products_by_name();
			break;
		case 3:
			find_products_by_name_of_registrant();
			break;
		case 4:
			find_products_by_date();
			break;
		case 5:
			sort_products_by_name();
			break;
		case 6:
			sort_products_by_price_to_higher();
			break;
		case 7:
			sort_products_by_amount_to_higher();
			break;
		case 8: case -1:
			if (confirm_menu_start("confirm?")) {
				user_menu->set_pointer_to_start();
				return;
			}
			break;

		default:
			break;
		}
	}
}

void Session::start_as_admin(string login) {
	this->session_account_login = login;
	int choise = 0;
	while (true) {
		choise = admin_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0:
			admin_manage_accounts_start();
			break;
		case 1:
			admin_manage_products_start();
			break;
		case 2: case -1:
			if (confirm_menu_start("<- confirm? ->")) {
				return;
			}
			break;
		default:
			break;
		}
	}
}

bool Session::confirm_menu_start(string title) {
	confirm_operation_menu->set_title(title);
	int choise = 0;
	while (true) {
		choise = confirm_operation_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // yes 
			return true;
		case 1: // No 
			return false;
		case -1: default:
			break;
		}
	}
}

void Session::admin_manage_accounts_start() {
	int choise = 0;
	while (true) {
		choise = accounts_manage_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: 
			show_accounts_table();
			system("pause");
			break;
		case 1: 
			add_new_account();
			break;
		case 2:  
			start_edit_account_menu();
			break;
		case 3: 
			delete_account();
			break;
		case 4: 
			confirm_account();
			break;
		case 5: 
			block_account();
			break;
		case 6:	case -1: 
			accounts_manage_menu->set_pointer_to_start();
			return;
			break;
		default:
			break;
		}
	}
}

void Session::show_accounts_table(string sql_start, string sql_end) {
	console::show_title("accounts table", "    ");
	account_db->show_table(sql_start, sql_end,
		{ "     �����", "����", "������" },
		{ 0, 3, 4 },
		{ 18, 7, 9 });
	cout << endl;
}

void Session::add_new_account() {
	Account account;
	console::show_title("add new account");

	account.login = console::get_free_login(account_db, "Login: ");
	if (account.login == "0") return;

	string pass = console::password_format_input("Password: ");
	if (pass == "0") return;

	account.role = console::get_number_from_range(0, 1, "role: ");


	if (confirm_menu_start("<- confirm? ->")) {
		account.access = 1;
		account.salt = help_functions::get_generated_salt();
		account.salted_hash_password = help_functions::get_generated_hash(pass, account.salt);

		account_db->push_back({ "'" + account.login + "'",
							"'" + account.salted_hash_password + "'",
							"'" + account.salt + "'",
						   to_string(account.role),
						   to_string(account.access) });

		console::show_info("������� ��� ������", "\t", "\n\n");
	}
	else {
		console::show_info("������� �� ��� ������", "\t", "\n\n");
	}
	system("pause");
}

void Session::start_edit_account_menu() {
	console::show_title("Edit account");
	
	string login = console::get_exists_login(account_db);
	if (login == "0") return;

	account_edit_menu->set_title("<- Editing accout '" + login + "' ->");
	int choise = 0;
	while (true) {
		choise = account_edit_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: 
			edit_account_login(&login);
			account_edit_menu->set_title("<- �������������� �������� '" + login + "' ->");
			break;
		case 1: 
			edit_account_password(login);
			break;
		case 2:  
			edit_account_role(login);
			break;
		case 3: case -1: 
			return;
			break;

		default:
			break;
		}
	}
}

void Session::edit_account_login(string* login) {
	console::show_title("edit account login", "\t", "\n\n");
	cout << "old login: " << *login << endl;
	string new_login = console::get_free_login(account_db, "new login: ");

	if (new_login == "0") return;
	else if (confirm_menu_start("<- confirm '" + new_login + "' ? ->")) {
		account_db->update("LOGIN", "'" + new_login + "'", "LOGIN='" + *login + "'");
		*login = new_login;
		console::show_info("��������� ���� �������", "\t", "\n\n");
	}
	else {
		console::show_info("��������� �� ���� �������", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_account_password(string login) {
	console::show_title("Edit password", "\t", "\n\n");
	string pass = console::password_format_input("new password: ");

	if (pass == "0") return;
	else if (confirm_menu_start("<- confirm? ->")) {
		string salt = help_functions::get_generated_salt();
		string hash = help_functions::get_generated_hash(pass, salt);
		account_db->update("HASH", "'" + hash + "'", "LOGIN='" + login + "'");
		account_db->update("SALT", "'" + salt + "'", "LOGIN='" + login + "'");

		console::show_info("��������� ���� �������", "\t", "\n\n");
	}
	else {
		console::show_info("��������� �� ���� �������", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_account_role(string login) {
	if (login != session_account_login) {
		console::show_title("Edit role", "\t", "\n\n");
		int new_role = console::get_number_from_range(-1, 1, "new role: ");

		if (new_role == -1) return;
		else if (confirm_menu_start("<- confirm? ->")) {
			account_db->update("ROLE", to_string(new_role), "LOGIN='" + login + "'");
			console::show_info("��������� ���� �������", "\t", "\n\n");
		}
		else {
			console::show_info("��������� �� ���� �������", "\t", "\n\n");
		}
	}
	else {
		console::show_error("��� ������� ������ ������������ ��� ������ ��������", "\t", "\n\n");
	}
	system("pause");

}

void Session::delete_account() {
	console::show_title("delete account", "", "\n\n");
	show_accounts_table();

	string login = console::get_exists_login(account_db);

	if (login == "0") return;
	else if (login == session_account_login) {
		console::show_error("������ ������� ���� �������", "\t", "\n");
	}
	else if (confirm_menu_start("<- confirm '" + login + "' ? ->")) {
		account_db->delete_field("LOGIN='" + login + "'");
		console::show_info("������� '" + login + "' ��� ������", "\t", "\n\n");
	}
	else {
		console::show_info("��������� �� ���� �������", "\t", "\n\n");
	}
	system("pause");
}

void Session::confirm_account() {
	console::show_title("confirm account", "", "\n\n");
	show_accounts_table();

	string login = console::get_exists_login(account_db);

	if (login == "0") return;
	else if (login == session_account_login) {
		console::show_error("��� ������� ������ ������������ ��� ������ ��������", "\n\t", "\n\n");
	}
	else if (account_db->get_int("LOGIN", login, 4) == 1) {
		console::show_info("���� ������� ��� �����������", "\n\t", "\n\n");
	}
	else {
		account_db->update("ACCESS", "1", "LOGIN='" + login + "'");
		console::show_info("������� '" + login + "' ��� �����������", "\n\t", "\n\n");
	}
	system("pause");
}

void Session::block_account() {
	console::show_title("block account", "", "\n\n");
	show_accounts_table();

	string login = console::get_exists_login(account_db);

	if (login == "0") return;
	else if (login == session_account_login) {
		console::show_error("��� ������� ������ ������������ ��� ������ ��������", "\n\t", "\n\n");
	}
	else if (account_db->get_int("LOGIN", login, 4) == 0) {
		console::show_info("���� ������� ��� ������������", "\n\t", "\n\n");
	}
	else {
		account_db->update("ACCESS", "0", "LOGIN='" + login + "'");
		console::show_info("������� '" + login + "' ��� ������������", "\n\t", "\n\n");
	}
	system("pause");
}

void Session::admin_manage_products_start() {
	int choise = 0;
	while (true) {
		choise = products_manage_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0:
			show_products_table();
			system("pause");
			break;
		case 1:
			add_new_product();
			break;
		case 2:
			delete_product();
			break;
		case 3:
			start_edit_product_menu();
			break;
		case 4:
			individual_task();
			break;
		case 5:
			find_products_by_name();
			break;
		case 6:
			find_products_by_name_of_registrant();
			break;
		case 7:
			find_products_by_date();
			break;
		case 8:
			sort_products_by_name();
			break;
		case 9:
			sort_products_by_price_to_higher();
			break;
		case 10:
			sort_products_by_amount_to_higher();
			break;
		case 11: case -1:
			products_manage_menu->set_pointer_to_start();
			return;
			break;
		default:
			break;
		}
	}
}

void Session::show_products_table(string sql_start, string sql_end) {
	console::show_title("products", "                                          ");
	product_db->show_table(sql_start, sql_end,
		{ "         ��������", "����������", "  ����", "���� �����������", "    ��� �������������������" },
		{ 0, 1, 2, 3, 4 },
		{ 28, 13, 12, 19, 35 });
	cout << endl;
}

void Session::add_new_product() {
	Product product;
	console::show_title("add new product");

	product.name = console::get_non_existent_product_name(product_db);
	if (product.name == "0") return;

	product.amount = console::get_number(true, "amount: ");
	if (product.amount == 0) return;

	product.price = console::get_number(true, "price: ");
	if (product.price == 0) return;

	cout << "date (yyyy-mm-dd): ";
	product.date = console::get_format_date();
	if (product.date == "0") return;

	cout << "name of registrant: ";
	getline(cin, product.name_of_registrant);
	if (product.name_of_registrant == "0") return;

	product_db->push_back({ "'" + product.name + "'",
						to_string(product.amount),
						"'" + to_string(product.price) + "'",
						"'" + product.date + "'",
						"'" + product.name_of_registrant + "'" });

	console::show_info("product added", "\n\t", "\n\n");
	system("pause");
}

void Session::delete_product() {
	console::show_title("delete product", "", "\n\n");
	show_products_table();

	string name = console::get_exists_product_name(product_db);

	if (name == "0") return;
	else if (confirm_menu_start("<- �� �������, ��� ������ ������� ����� '" + name + "' ? ->")) {
		product_db->delete_field("NAME='" + name + "'");
		console::show_info("����� ��� ������.", "\t", "\n\n");
	}
	else {
		console::show_info("��������� �� ���� �������.", "\t", "\n\n");
	}
	system("pause");
}

void Session::start_edit_product_menu() {
	console::show_title("Edit product munu");

	string name = console::get_exists_product_name(product_db);
	if (name == "0") return;

	product_edit_menu->set_title("<- product: " + name + " ->");
	int choise = 0;
	while (true) {
		choise = product_edit_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0:
			edit_product_name(&name);
			product_edit_menu->set_title("<- product: " + name + " ->");
			break;
		case 1:
			edit_product_amount(name);
			break;
		case 2:
			edit_product_price(name);
			break;
		case 3:
			edit_product_date(name);
			break;
		case 4:
			edit_name_of_product_registrant(name);
			break;
		case 5: case -1:
			return;
			break;

		default:
			break;
		}
	}

}

void Session::edit_product_name(string* name) {
	console::show_title("Edit product name", "\t", "\n\n");
	
	cout << "old name: " << *name << endl;
	string new_name = console::get_non_existent_product_name(product_db, "new name: ");

	if (new_name == "0") return;
	else if (confirm_menu_start("�� �������, ��� ������ �������� �������� �� '" + new_name + "' ?")) {
		product_db->update("NAME", "'" + new_name + "'", "NAME='" + *name + "'");
		*name = new_name;
		console::show_info("��������� ���� �������.", "\t", "\n\n");
	}
	else {
		console::show_info("��������� �� ���� �������.", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_product_amount(string name) {
	console::show_title("Edit amount", "\t", "\n\n");

	cout << "old amount: " << product_db->get_int("NAME", name, 1) << endl;
	int amount = console::get_number(true, "new amount: ");

	if (amount == 0) return;
	else {
		product_db->update("AMOUNT", "'" + to_string(amount) + "'", "NAME='" + name + "'");
		console::show_info("��������� ���� �������.", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_product_price(string name) {
	console::show_title("Edit product price", "\t", "\n\n");
	
	cout << "old price: " << product_db->get_int("NAME", name, 2) << endl;
	int price = console::get_number(true, "new price: ");

	if (price == 0) return;
	else {
		product_db->update("PRICE", "'" + to_string(price) + "'", "NAME='" + name + "'");
		console::show_info("��������� ���� �������.", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_product_date(string name) {
	console::show_title("Edit product date", "\t", "\n\n");

	cout << "old date: " << product_db->get_text("NAME", name, 3) << endl;
	string date = console::get_format_date("new date: ");

	if (date == "0") return;
	else {
		product_db->update("DATE", "'" + date + "'", "NAME='" + name + "'");
		console::show_info("��������� ���� �������.", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_name_of_product_registrant(string name) {
	console::show_title("Edit name of product registrant", "\t", "\n\n");

	cout << "old name: " << product_db->get_text("NAME", name, 4) << endl;
	cout << "new name: ";
	string reg_name;
	getline(cin, reg_name);

	if (reg_name == "0") return;
	else {
		product_db->update("REG_NAME", "'" + reg_name + "'", "NAME='" + name + "'");
		console::show_info("��������� ���� �������.", "\t", "\n\n");
	}
	system("pause");
}

void Session::individual_task() {
	console::show_title("individual task", "\t", "\n\n");

	int mounth_amount = console::get_number(true, "mounth amount: ");
	if (mounth_amount == 0) return;

	int price = console::get_number(true, "price: ");
	if (price == 0) return;

	string data = product_db->get_date_mounth_ago(to_string(mounth_amount));
	cout << "\ndate: " << data << "\n" << endl;

	show_products_table("SELECT * FROM ", " WHERE DATE > '" + data + "' AND PRICE > '" + to_string(price) + "' ORDER BY NAME ASC;");
	system("pause");
}

void Session::find_products_by_name() {
	console::show_title("find product by name", "\t", "\n\n");
	
	cout << "name\n>";
	string name;
	getline(cin, name);
	if (name == "0") return;

	cout << endl;
	show_products_table("SELECT * FROM ", " WHERE NAME GLOB '*" + name + "*';");
	system("pause");
}

void Session::find_products_by_name_of_registrant() {
	console::show_title("find by registrant name", "\t", "\n\n");

	cout << "Registrant name\n>";
	string name;
	getline(cin, name);
	if (name == "0") return;

	cout << endl;
	show_products_table("SELECT * FROM ", " WHERE REG_NAME GLOB '*" + name + "*';");
	system("pause");
}

void Session::find_products_by_date() {
	string date;
	console::show_title("find by date", "\t", "\n\n");

	cout << "�� ������ ������������ ���� * ��� ����������� ����������� �������. (������: *-12-05, 2021-*-*)" << endl;
	cout << "date: ";
	cin >> date;
	cin.ignore(256, '\n');
	if (date == "0") return;

	cout << endl;
	show_products_table("SELECT * FROM ", " WHERE DATE GLOB '" + date + "';");
	system("pause");
}

void Session::sort_products_by_name() {
	console::show_title("products sorted by name", "\t", "\n\n");
	show_products_table("SELECT * FROM ", " ORDER BY NAME ASC ;");
	system("pause");
}

void Session::sort_products_by_price_to_higher() {
	console::show_title("products sorted by price to higher", "\t", "\n\n");
	show_products_table("SELECT * FROM ", " ORDER BY PRICE ASC ;");
	system("pause");
}

void Session::sort_products_by_amount_to_higher() {
	console::show_title("products sorted by amount to higher", "\t", "\n\n");
	show_products_table("SELECT * FROM ", " ORDER BY AMOUNT ASC ;");
	system("pause");
}

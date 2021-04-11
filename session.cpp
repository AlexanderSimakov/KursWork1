#pragma once
#include "session.h"


Session::Session(SQLWork* product_db, SQLWork* account_db) {
	this->product_db = product_db;
	this->account_db = account_db;
	init_admin_menu();
	init_user_menu();
	init_confirm_operation_menu();
}


void Session::start_as_admin(string login) {
	this->user_login = login;
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = main_menu->get_choise();
		switch (choise)
		{
		case 0:
			admin_manage_accounts_start();
			break;
		case 1:
			admin_manage_products_start();
			break;
		case 2: case -1:
			if (confirm_menu_start("�� �������, ��� ������ ����� �� ��������?")) {
				is_exit = true;
			}
			break;
		default:
			break;
		}
	}
}

void Session::admin_manage_accounts_start() {
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = manage_menu->get_choise();
		switch (choise)
		{
		case 0: // �������� ���� �������
			show_accounts_table();
			system("pause");
			break;
		case 1: // ���������� �����
			add_new_account();
			break;
		case 2: // �������������� 
			edit_account_menu_start();
			break;
		case 3: // �������� ������� ������
			delete_account();
			break;
		case 4: // ������������� ������� ������
			confirm_account();
			break;
		case 5: // ���������� ������� ������
			block_account();
			break;
		case 6:	case -1: // �����
			is_exit = true;
			break;
		default:
			break;
		}
	}
}

void Session::admin_manage_products_start() {
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = data_menu->get_choise();
		switch (choise)
		{
		case 0: // �������� ���� �������
			show_products();
			break;
		case 1: // ���������� �����
			add_new_product();
			break;
		case 2: // ��������
			delete_product();
			break;
		case 3: // ��������������
			edit_product_menu_start();
			break;
		case 4: // ������������
			individual_task();
			break;
		case 5: // ����� �� ��������
			find_by_name();
			break;
		case 6: // ����� �� ����� �����������������
			find_by_reg_name();
			break;
		case 7: // ����� �� ����
			find_by_data();
			break;
		case 8: // ���������� �� �����
			sort_by_name();
			break;
		case 9: // ���������� �� ����
			sort_by_price_to_higher();
			break;
		case 10: // ���������� ����������
			sort_by_amount_to_higher();
			break;
		case 11: case -1: // �����
			is_exit = true;
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
		choise = confirm_operation_menu->get_choise();
		switch (choise)
		{
		case 0: // ��
			return true;
		case 1: // ���
			return false;
		case -1: default:
			break;
		}
	}
}

void Session::start_as_user(string login) {
	this->user_login = login;
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = user_menu->get_choise();
		switch (choise)
		{
		case 0: // �������� ���� �������
			show_products();
			break;
		case 1: // ������������
			individual_task();
			break;
		case 2: // ����� �� ��������
			find_by_name();
			break;
		case 3: // ����� �� ����� �����������������
			find_by_reg_name();
			break;
		case 4: // ����� �� ����
			find_by_data();
			break;
		case 5: // ���������� �� �����
			sort_by_name();
			break;
		case 6: // ���������� �� ����
			sort_by_price_to_higher();
			break;
		case 7: // ���������� ����������
			sort_by_amount_to_higher();
			break;
		case 8: case -1: // �����
			if (confirm_menu_start("�� �������, ��� ������ ����� �� ��������?")) {
				is_exit = true;
			}
			break;

		default:
			break;
		}
	}
}



void Session::init_admin_menu() {
	main_menu = new Menu("<- ������� ���� ->",
		{ " ���������� �������� ��������",
		  " ���������� ��������",
		  " ����� �� ��������" });

	manage_menu = new Menu("<- ���������� �������� �������� ->",
		{ " �������� ���� ������� �������",
		  " ���������� ����� ������� ������",
		  " �������������� ������� ������",
		  " �������� ������� ������",
		  " ������������� ������� ������",
		  " ���������� ������� ������",
		  " �����" });

	data_menu = new Menu("<- ���������� �������� ->",
		{ " �������� ���� �������",
		  " ���������� ������ ������",
		  " �������� ������",
		  " �������������� ����������� � ������",
		  " �������� ������� ������� ������ � �������, � ����� ������ �",
		  " ����� �� ��������",
		  " ����� �� ��� �������������������",
		  " ����� �� ���� ����������� �� �����",
		  " ���������� �� �������� ������",
		  " ���������� �� ���� ������ (�����������)",
		  " ���������� �� ���������� ������ (�����������)",
		  " �����" });

	account_edit_menu = new Menu("<- ����� ������ ��� �������������� �������� ->", 
		{ " �����",
		  " ������",
		  " ����",
		  " �����" });

	product_edit_menu = new Menu("<- ����� ������ ��� �������������� ������ ->",
		{ " ��������",
		  " ����������",
		  " ����",
		  " ���� ����������� �� �����",
		  " ��� �������������������",
		  " �����" });
}

void Session::init_user_menu() {
	user_menu = new Menu("<- ���� ������ � �������� ->",
		{ " �������� ���� �������",
		  " �������� ������� ������� ������ � �������, � ����� ������ �",
		  " ����� �� ��������",
		  " ����� �� ��� �������������������",
		  " ����� �� ���� ����������� �� �����",
		  " ���������� �� �������� ������",
		  " ���������� �� ���� ������ (�����������)",
		  " ���������� �� ���������� ������ (�����������)",
		  " ����� �� ��������" });

}

void Session::init_confirm_operation_menu() {
	confirm_operation_menu = new Menu("�� �������?", { " ��", " ���" });
}


void Session::show_accounts_table() {
	cout << "    <- ��� ������� ������: ->" << endl;
	cout << "    �����\t|  ����\t| ������" << endl;
	account_db->show({ " ", "\t\t|   ", "\t|   " }, {0, 3, 4});
	cout << endl;
}

void Session::add_new_account() {
	Account account;
	
	cout << "<- �������� ������ ��������. (0 � ����� �� �����, ����� ����, ��� ������) ->" << endl;

	account.login = console::get_free_login(account_db);
	if (account.login == "0") return;


	cout << "������: ";
	string pass = console::password_format_input();
	if (pass == "0") return;
	

	cout << "����";
	account.role = console::get_number_from_range(0, 1);

	if (confirm_menu_start("�� �������, ��� ������ ������� �������?")) {
		account.access = 1;
		account.salt = help::get_generated_salt();
		account.salted_hash_password = help::generate_hash(pass, account.salt);

		account_db->push_back({ "'" + account.login + "'",
							"'" + account.salted_hash_password + "'",
							"'" + account.salt + "'",
						   to_string(account.role),
						   to_string(account.access) });

		cout << "*** ������� ��� ������ ***\n" << endl;
	}
	else {
		cout << "*** ������� �� ��� ������ ***\n" << endl;
	}
	system("pause");
}

void Session::delete_account() {
	string login;
	cout << "<- �������� �������� (������� '0' ��� ������) ->\n" << endl;
	show_accounts_table();
	cout << "������� ����� ��������, ������� ������ �������." << endl;
	
	login = console::get_exists_login(account_db);
	
	if (login == "0") return;
	else if (login == user_login) {
		cout << "\n*** ������ ������� ���� �������.***\n" << endl;
	}
	else if (confirm_menu_start("�� �������, ��� ������ ������� ������� '"+ login + "' ?")) {
		account_db->delete_field("LOGIN='" + login + "'");
		cout << "*** ������� '" << login << "' ��� ������. ***\n" << endl;
	}
	else {
		cout << "*** ��������� �� ���� �������.***\n" << endl;
	}
	system("pause");
}

void Session::confirm_account() {
	string login;
	cout << "<- ������������� �������� ('0' ��� ������) ->\n" << endl;
	show_accounts_table();
	cout << "������� ����� ��������, ������� ������ �����������." << endl;
	login = console::get_exists_login(account_db);

	if (login == "0") return;
	else if (login == user_login) {
		cout << "\n*** ��� ������� ������ ������������ ��� ������ ��������, �� ��� �����������. ***\n" << endl;
	}
	else if (account_db->get_int("LOGIN", login, 4) == 1) {
		cout << "\n*** ���� ������� ��� �����������. ***\n" << endl;
	}
	else {
		account_db->update("ACCESS", "1", "LOGIN='" + login + "'");
		cout << "\n*** ������� '" + login + "' ��� �����������. ***\n" << endl;
	}
	system("pause");
}

void Session::block_account() {
	string login;
	cout << "<- ���������� �������� ('0' ��� ������) ->\n" << endl;
	show_accounts_table();
	cout << "������� ����� ��������, ������� ������ �������������." << endl;

	login = console::get_exists_login(account_db);
	
	if (login == "0") return;
	else if (login == user_login) {
		cout << "\n*** ��� ������� ������ ������������ ��� ������ ��������. ***\n" << endl;
	}
	else if (account_db->get_int("LOGIN", login, 4) == 0) {
		cout << "\n*** ���� ������� ��� ������������. ***\n" << endl;
	}
	else {
		account_db->update("ACCESS", "0", "LOGIN='" + login + "'");
		cout << "\n*** ������� '" + login + "' ��� ������������. ***\n" << endl;
	}
	system("pause");
}

void Session::edit_account_menu_start() {
	string login;
	cout << "������� ����� �������� ��� ��������������." << endl;
	login = console::get_exists_login(account_db);

	account_edit_menu->set_title("<- �������������� �������� '" + login + "' ->");
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = account_edit_menu->get_choise();
		switch (choise)
		{
		case 0: // �����
			edit_login(&login);
			account_edit_menu->set_title("<- �������������� �������� '" + login + "' ->");
			break;
		case 1: // ������
			edit_password(login);
			break;
		case 2: // ���� 
			edit_role(login);
			break;
		case 3: case -1: // �����
			is_exit = true;
			break;

		default:
			break;
		}
	}
}

void Session::edit_login(string *login) {
	cout << "<- ��������� ������ ('0' ��� ������). ->" << endl;
	cout << "������ �����: " << *login << endl;
	cout << "������� ����� �����." << endl;

	string new_login = console::get_free_login(account_db);
	
	if (new_login == "0") {
		return;
	}
	else if (confirm_menu_start("�� �������, ��� ������ �������� ����� �� '" + new_login + "' ?")){
		account_db->update("LOGIN", "'" + new_login + "'", "LOGIN='" + *login + "'");
		*login = new_login;
		cout << "*** ��������� ���� �������. ***\n" << endl;
	}
	else {
		cout << "*** ��������� �� ���� �������. ***\n" << endl;
	}
	system("pause");
}

void Session::edit_password(string login) {
	cout << "<- ��������� ������ ('0' ��� ������). ->" << endl;
	cout << "������� ����� ������." << endl;
	cout << "������: ";
	string pass = console::password_format_input();

	if (pass == "0") {
		return;
	}
	else if (confirm_menu_start("�� �������, ��� ������ �������� ������?")) {
		string salt = help::get_generated_salt();
		string hash = help::generate_hash(pass, salt);
		account_db->update("HASH", "'" + hash + "'", "LOGIN='" + login + "'");
		account_db->update("SALT", "'" + salt + "'", "LOGIN='" + login + "'");

		cout << "*** ��������� ���� �������. ***\n" << endl;
	}
	else {
		cout << "*** ��������� �� ���� �������. ***\n" << endl;
	}
	system("pause");
}

void Session::edit_role(string login) {
	if (login != user_login) {
		int new_role;
		cout << "<- ��������� ���� ('-1' ��� ������). ->" << endl;
		cout << "������� ����� ����.";

		new_role = console::get_number_from_range(-1, 1);

		if (new_role == -1) {
			return;
		}
		else if (confirm_menu_start("�� �������, ��� ������ �������� ����?")) {
			account_db->update("ROLE", to_string(new_role), "LOGIN='" + login + "'");
			cout << "*** ��������� ���� �������. ***\n" << endl;
		}
		else {
			cout << "*** ��������� �� ���� �������. ***\n" << endl;
		}
	}
	else {
		cout << "*** ��� ������� ������ ������������ ��� ������ ��������. ***\n" << endl;
	}
	system("pause");

}




void Session::show_products() {
	cout << "��� ������:\n" << endl;
	product_db->show_endl({ "��������: ", "����������: ", "����: ", "���� �����������: ", "��� �������������������: " }, { 0, 1, 2, 3, 4 });
	std::system("pause");
}

void Session::add_new_product() {
	Product product;
	cout << "���������� ������ ��������." << endl;


	cout << "�������� ������: ";
	cin >> product.name;
	cout << "���������� �������: ";
	cin >> product.amount;
	cout << "���� ������: ";
	cin >> product.price;
	cout << "���� ����������� �� �����: ";
	(cin >> product.date).get();
	cout << "��� �������������������: ";
	getline(cin, product.reg_name);

	product_db->push_back({ "'" + product.name + "'",
						to_string(product.amount),
						"'" + to_string(product.price) + "'",
					    "'" + product.date + "'",
					    "'" + product.reg_name + "'" });

}

void Session::delete_product() {
	string name;
	cout << "�������� ��������" << endl;
	cout << "������� �������� ��������, ������� ������ �������.\n> ";
	cin >> name;
	product_db->delete_field("NAME='" + name + "'");
}

void Session::edit_product_menu_start() {
	string name;
	cout << "������� �������� �������� ��� ��������������\n>";
	cin >> name;


	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = product_edit_menu->get_choise();
		switch (choise)
		{
		case 0: // ��������
			edit_name(&name);
			break;
		case 1: // ����������
			edit_amount(name);
			break;
		case 2: // ����
			edit_price(name);
			break;
		case 3: // ����
			edit_data(name);
			break;
		case 4: // ���
			edit_reg_name(name);
			break;
		case 5: case -1: // �����
			cout << "�����." << endl;
			is_exit = true;
			break;

		default:
			break;
		}
	}
}

void Session::edit_name(string* name) {
	string new_name;
	cout << "����� ��������: ";
	cin >> new_name;
	product_db->update("NAME", "'" + new_name + "'", "NAME='" + *name + "'");
	*name = new_name;
}

void Session::edit_amount(string name) {
	string amount;
	cout << "����� ����������: ";
	cin >> amount;
	product_db->update("AMOUNT", "'" + amount + "'", "NAME='" + name + "'");
}

void Session::edit_price(string name) {
	int price;
	cout << "����� ����: ";
	cin >> price;
	product_db->update("PRICE", "'" + to_string(price) + "'", "NAME='" + name + "'");
}

void Session::edit_data(string name) {
	string data;
	cout << "������ ����: ";
	cin >> data;
	product_db->update("DATE", "'" + data + "'", "NAME='" + name + "'");
}

void Session::edit_reg_name(string name) {
	string reg_name;
	cout << "����� ��� �����������������: ";
	cin >> reg_name;
	product_db->update("REG_NAME", "'" + reg_name + "'", "NAME='" + name + "'");
}

void Session::individual_task() {
	int mounth_amount, price;
	cout << "���������� �������: ";
	cin >> mounth_amount;
	cout << "���������: ";
	cin >> price;
	string data =  product_db->date_mounhth_befor(to_string(mounth_amount));
	cout << "\n����: " << data << "\n" << endl;
	product_db->show("SELECT * FROM ", " WHERE DATE > '" + data + "' AND PRICE > '" + to_string(price) + "' ORDER BY NAME ASC;",
		{ "��������: ", "����: ", "���� �����������: " }, { 0, 2, 3 });
}

void Session::find_by_name() {
	string name;
	cout << "������� �������� ��� ��� ����� ��� ������\n>";
	cin >> name;
	product_db->find_and_show("NAME", "*" + name + "*",
		{ "��������: ", "����������: ", "����: ", "���� �����������: ", "��� �������������������: " }, { 0, 1, 2, 3, 4 });
}

void Session::find_by_reg_name() {
	string name;
	cout << "������� ��� ������������������� ��� ��� ����� ��� ������\n>";
	cin >> name;
	product_db->find_and_show("REG_NAME", "*" + name + "*",
		{ "��������: ", "����������: ", "����: ", "���� �����������: ", "��� �������������������: " }, { 0, 1, 2, 3, 4 });
}

void Session::find_by_data() {
	string data;
	cout << "����� �� ����. �� ������ ������������ ���� * ��� ����������� ����������� ������� (������: 12.05.*, *.*.2021)" << endl;
	cout << "����: ";
	cin >> data;
	cout << endl;
	product_db->find_and_show("DATE", data,
		{ "��������: ", "����������: ", "����: ", "���� �����������: ", "��� �������������������: " }, { 0, 1, 2, 3, 4 });
}

void Session::sort_by_name() {
	product_db->sort("NAME ASC", 
		{ "��������: ", "����������: ", "����: ", "���� �����������: ", "��� �������������������: " }, { 0, 1, 2, 3, 4 });
}

void Session::sort_by_price_to_higher() {
	product_db->sort("PRICE ASC",
		{ "��������: ", "����������: ", "����: ", "���� �����������: ", "��� �������������������: " }, { 0, 1, 2, 3, 4 });
}

void Session::sort_by_amount_to_higher() {
	product_db->sort("AMOUNT ASC",
		{ "��������: ", "����������: ", "����: ", "���� �����������: ", "��� �������������������: " }, { 0, 1, 2, 3, 4 });
}


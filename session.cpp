#pragma once
#include "session.h"


Session::Session(SQLWork* product_db, SQLWork* account_db) {
	this->product_db = product_db;
	this->account_db = account_db;
	init_admin_menu();
	init_user_menu();
}


void Session::start_as_admin() {
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
			cout << "����� �� ��������" << endl;
			is_exit = true;
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
			show_accounts();
			break;
		case 1: // ���������� �����
			add_new_account();
			system("pause");
			break;
		case 2: // �������������� 
			edit_account_menu_start();
			system("pause");
			break;
		case 3: // �������� ������� ������
			delete_account();
			system("pause");
			break;
		case 4: // ������������� ������� ������
			confirm_account();
			system("pause");
			break;
		case 5: // ���������� ������� ������
			block_account();
			system("pause");
			break;
		case 6:	case -1: // �����
			cout << "�����." << endl;
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
			system("pause");
			break;
		case 2: // ��������
			delete_product();
			system("pause");
			break;
		case 3: // ��������������
			edit_product_menu_start();
			system("pause");
			break;
		case 4: // ������������
			individual_task();
			system("pause");
			break;
		case 5: // ����� �� ��������
			find_by_name();
			system("pause");
			break;
		case 6: // ����� �� ����� �����������������
			find_by_reg_name();
			system("pause");
			break;
		case 7: // ����� �� ����
			find_by_data();
			system("pause");
			break;
		case 8: // ���������� �� �����
			sort_by_name();
			system("pause");
			break;
		case 9: // ���������� �� ����
			sort_by_price_to_higher();
			system("pause");
			break;
		case 10: // ���������� ����������
			sort_by_amount_to_higher();
			system("pause");
			break;
		case 11: case -1: // �����
			cout << "�����" << endl;
			is_exit = true;
			break;

		default:
			break;
		}
	}
}

bool Session::confirm_menu_start() {
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = confirm_operation_menu->get_choise();
		switch (choise)
		{
		case 0: // ��
			return true;
		case 1: case -1: // ���
			return false;
		default:
			break;
		}
	}
}

void Session::start_as_user() {
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
			system("pause");
			break;
		case 2: // ����� �� ��������
			find_by_name();
			system("pause");
			break;
		case 3: // ����� �� ����� �����������������
			find_by_reg_name();
			system("pause");
			break;
		case 4: // ����� �� ����
			find_by_data();
			system("pause");
			break;
		case 5: // ���������� �� �����
			sort_by_name();
			system("pause");
			break;
		case 6: // ���������� �� ����
			sort_by_price_to_higher();
			system("pause");
			break;
		case 7: // ���������� ����������
			sort_by_amount_to_higher();
			system("pause");
			break;
		case 8: case -1: // �����
			cout << "�����" << endl;
			is_exit = true;
			break;

		default:
			break;
		}
	}
}



void Session::init_admin_menu() {
	main_menu = new Menu("������� ��������������",
		{ " ���������� �������� ��������",
		  " ������ � �������",
		  " ����� �� ��������" });

	manage_menu = new Menu("���������� �������� ��������",
		{ " �������� ���� ������� �������",
		  " ���������� ����� ������",
		  " �������������� ������� ������",
		  " �������� ������� ������",
		  " ������������� ������� ������",
		  " ���������� ������� ������",
		  " �����" });

	data_menu = new Menu("������ � �������",
		{ " �������� ���� ������",
		  " ���������� ����� ������",
		  " �������� ������",
		  " �������������� ������",
		  " ������������ ...",
		  " ����� �� ��������",
		  " ����� �� ��� �������������������",
		  " ����� �� ����",
		  " ���������� �� �������� ������",
		  " ���������� �� ���� (�����������)",
		  " ���������� �� ���������� (�����������)",
		  " �����" });

	account_edit_menu = new Menu("���� ��� ��������������", 
		{ " �����",
		  " ������",
		  " ����",
		  " �����" });

	product_edit_menu = new Menu("���� ��� ��������������",
		{ " ��������",
		  " ����������",
		  " ����",
		  " ���� ����������� ������",
		  " ��� �������������������",
		  " �����" });
}

void Session::init_user_menu() {
	user_menu = new Menu("������ � �������",
		{ " �������� ���� ������",
		  " ������������",
		  " ����� �� ��������",
		  " ����� �� ��� �������������������",
		  " ����� �� ����",
		  " ���������� �� �������� ������",
		  " ���������� �� ���� (�����������)",
		  " ���������� �� ���������� (�����������)",
		  " ����� �� ��������" });

}

void Session::init_confirm_operation_menu() {
	user_menu = new Menu("�� �������?",
		{ " ��",
		  " ���" });
}


void Session::show_accounts() {
	cout << "��� ������� ������:\n" << endl;
	account_db->show({ "�����: ", "����: ", "������: " }, {0, 3, 4});
	system("pause");
}

void Session::add_new_account() {
	Account account;
	
	cout << "�������� ������ ��������." << endl;

	
	account.login = console::get_free_login(account_db);

	cout << "������: ";
	string pass = console::password_format_input();
	account.salt = help::get_generated_salt();
	account.salted_hash_password = help::generate_hash(pass, account.salt);
	
	cout << "����: ";
	cin >> account.role;
	account.access = 1;

	account_db->push_back({ "'" + account.login + "'",
						"'" + account.salted_hash_password + "'",
						"'" + account.salt + "'",
					   to_string(account.role),
					   to_string(account.access) });

}

void Session::delete_account() {
	string login;
	cout << "�������� ��������" << endl;
	cout << "������� ����� ��������, ������� ������ �������.\n> ";
	cin >> login;
	account_db->delete_field("LOGIN='" + login + "'");
}

void Session::confirm_account() {
	string login;
	cout << "������������� ��������." << endl;
	cout << "������� �����\n>";
	cin >> login;
	account_db->update("ACCESS", "1", "LOGIN='" + login + "'");
}

void Session::block_account() {
	string login;
	cout << "���������� ��������." << endl;
	cout << "������� �����\n>";
	cin >> login;
	account_db->update("ACCESS", "0", "LOGIN='" + login + "'");
}

void Session::edit_account_menu_start() {
	string login;
	cout << "������� ����� �������� ��� ��������������\n>";
	cin >> login;


	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = account_edit_menu->get_choise();
		switch (choise)
		{
		case 0: // �����
			edit_login(&login);
			break;
		case 1: // ������
			edit_password(login);
			break;
		case 2: // ���� 
			edit_role(login);
			break;
		case 3: case -1: // �����
			cout << "�����." << endl;
			is_exit = true;
			break;

		default:
			break;
		}
	}
}

void Session::edit_login(string *login) {
	string new_login = console::get_free_login(account_db);
	account_db->update("LOGIN", "'" + new_login + "'", "LOGIN='" + *login + "'");
	*login = new_login;
}

void Session::edit_password(string login) {
	cout << "������: ";
	string pass = console::password_format_input();
	string salt = help::get_generated_salt();
	string hash = help::generate_hash(pass, salt);

	account_db->update("HASH", "'" + hash + "'", "LOGIN='" + login + "'");
	account_db->update("SALT", "'" + salt + "'", "LOGIN='" + login + "'");
}

void Session::edit_role(string login) {
	string new_role;
	cout << "����� ����: ";
	cin >> new_role;
	account_db->update("ROLE", new_role, "LOGIN='" + login + "'");

}




void Session::show_products() {
	cout << "��� ������:\n" << endl;
	product_db->show({ "��������: ", "����������: ", "����: ", "���� �����������: ", "��� �������������������: " }, { 0, 1, 2, 3, 4 });
	system("pause");
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


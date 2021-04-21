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
		choise = main_menu->get_num_of_choisen_line();
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
		choise = manage_menu->get_num_of_choisen_line();
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
		choise = data_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // �������� ���� �������
			show_products_table();
			system("pause");
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
		choise = confirm_operation_menu->get_num_of_choisen_line();
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
		choise = user_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // �������� ���� �������
			show_products_table();
			system("pause");
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


void Session::show_accounts_table(string sql_start, string sql_end) {
	console::show_title("��� ������� ������", "    ");
	account_db->show_table(sql_start, sql_end,
		{ "     �����", "����", "������" },
		{ 0, 3, 4},
		{ 18, 7, 9});
	cout << endl;
}

void Session::add_new_account() {
	Account account;
	console::show_title("�������� ������ ��������. (0 � ����� �� �����, ����� ����, ��� ������)");

	account.login = console::get_free_login(account_db, "�����: ");
	if (account.login == "0") return;

	string pass = console::password_format_input("������: ");
	if (pass == "0") return;
	
	account.role = console::get_number_from_range(0, 1, "����: ");


	if (confirm_menu_start("�� �������, ��� ������ ������� �������?")) {
		account.access = 1;
		account.salt = help::get_generated_salt();
		account.salted_hash_password = help::generate_hash(pass, account.salt);

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

void Session::delete_account() {
	string login;
	console::show_title("�������� �������� (������� '0' ��� ������)", "", "\n\n");
	show_accounts_table();
	cout << "������� ����� ��������, ������� ������ �������." << endl;
	
	login = console::get_exists_login(account_db);
	
	if (login == "0") return;
	else if (login == user_login) {
		console::show_error("������ ������� ���� �������", "\t", "\n");
	}
	else if (confirm_menu_start("�� �������, ��� ������ ������� ������� '"+ login + "' ?")) {
		account_db->delete_field("LOGIN='" + login + "'");
		console::show_info("������� '" + login + "' ��� ������", "\t", "\n\n");
	}
	else {
		console::show_info("��������� �� ���� �������", "\t", "\n\n");
	}
	system("pause");
}

void Session::confirm_account() {
	string login;
	console::show_title("������������� �������� ('0' ��� ������)", "", "\n\n");
	show_accounts_table();
	cout << "������� ����� ��������, ������� ������ �����������." << endl;
	login = console::get_exists_login(account_db);

	if (login == "0") return;
	else if (login == user_login) {
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
	string login;
	console::show_title("���������� �������� ('0' ��� ������)", "", "\n\n");
	show_accounts_table();
	cout << "������� ����� ��������, ������� ������ �������������." << endl;

	login = console::get_exists_login(account_db);
	
	if (login == "0") return;
	else if (login == user_login) {
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

void Session::edit_account_menu_start() {
	string login;
	cout << "������� ����� �������� ��� �������������� ('0' ��� ������)." << endl;
	login = console::get_exists_login(account_db);
	if (login == "0") return;

	account_edit_menu->set_title("<- �������������� �������� '" + login + "' ->");
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = account_edit_menu->get_num_of_choisen_line();
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
	console::show_title("��������� ������ ('0' ��� ������)", "\t", "\n\n");
	cout << "������ �����: " << *login << endl;
	cout << "������� ����� �����." << endl;

	string new_login = console::get_free_login(account_db, "�����: ");
	
	if (new_login == "0") {
		return;
	}
	else if (confirm_menu_start("�� �������, ��� ������ �������� ����� �� '" + new_login + "' ?")){
		account_db->update("LOGIN", "'" + new_login + "'", "LOGIN='" + *login + "'");
		*login = new_login;
		console::show_info("��������� ���� �������", "\t", "\n\n");
	}
	else {
		console::show_info("��������� �� ���� �������", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_password(string login) {
	console::show_title("��������� ������ ('0' ��� ������)", "\t", "\n\n");
	cout << "������� ����� ������." << endl;
	string pass = console::password_format_input("������: ");

	if (pass == "0") {
		return;
	}
	else if (confirm_menu_start("�� �������, ��� ������ �������� ������?")) {
		string salt = help::get_generated_salt();
		string hash = help::generate_hash(pass, salt);
		account_db->update("HASH", "'" + hash + "'", "LOGIN='" + login + "'");
		account_db->update("SALT", "'" + salt + "'", "LOGIN='" + login + "'");

		console::show_info("��������� ���� �������", "\t", "\n\n");
	}
	else {
		console::show_info("��������� �� ���� �������", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_role(string login) {
	if (login != user_login) {
		int new_role;
		console::show_title("��������� ���� ('-1' ��� ������)", "\t", "\n\n");

		cout << "������� ����� ����." << endl;
		new_role = console::get_number_from_range(-1, 1, "����: ");

		if (new_role == -1) {
			return;
		}
		else if (confirm_menu_start("�� �������, ��� ������ �������� ����?")) {
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




void Session::show_products_table(string sql_start, string sql_end) {
	console::show_title("������", "                                          ");
	product_db->show_table(sql_start, sql_end,
						{ "         ��������", "����������", "  ����", "���� �����������", "    ��� �������������������" }, 
						{ 0, 1, 2, 3, 4 }, 
						{28, 13, 12, 19, 35});
	cout << endl;
}

void Session::add_new_product() {
	Product product;
	console::show_title("���������� ������ ��������. ('0' ��� ������)");


	cout << "�������� ������: ";
	product.name = console::get_non_existent_field(product_db, "NAME");
	if (product.name == "0") return;

	cout << "���������� �������: ";
	product.amount = console::get_number(true);
	if (product.amount == 0) return;

	cout << "���� ������: ";
	product.price = console::get_number(true);
	if (product.price == 0) return;


	cout << "���� ����������� �� ����� (����-��-��): ";
	product.date = console::get_format_data();
	if (product.date == "0") return;

	cout << "��� �������������������: ";
	getline(cin, product.name_of_registrant);
	if (product.name_of_registrant == "0") return;

	product_db->push_back({ "'" + product.name + "'",
						to_string(product.amount),
						"'" + to_string(product.price) + "'",
					    "'" + product.date + "'",
					    "'" + product.name_of_registrant + "'" });

	console::show_info("����� ��������", "\n\t", "\n\n");
	system("pause");

}

void Session::delete_product() {
	string name;
	console::show_title("�������� ������. ('0' ��� ������)", "", "\n\n");
	show_products_table();
	cout << "������� �������� ������, ������� ������ �������" << endl;
	name = console::get_exists_field(product_db, "NAME");
	
	if (name == "0") {
		return;
	}
	else if (confirm_menu_start("�� �������, ��� ������ ������� ����� '" + name + "' ?")) {
		product_db->delete_field("NAME='" + name + "'");
		console::show_info("����� ��� ������.", "\t", "\n\n");
	}
	else {
		console::show_info("��������� �� ���� �������.", "\t", "\n\n");
	}
	system("pause");

	
}

void Session::edit_product_menu_start() {
	string name;
	cout << "������� �������� �������� ��� ��������������. (0 - ��� ������)" << endl;
	name = console::get_exists_field(product_db, "NAME");
	if (name == "0") return;

	product_edit_menu->set_title("<- �������������� ������: " + name + " ->");
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = product_edit_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // ��������
			edit_name(&name);
			product_edit_menu->set_title("<- �������������� ������: " + name + " ->");
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
	console::show_title("��������� �������� ('0' ��� ������)", "\t", "\n\n");
	cout << "������ ��������: " << *name << endl;
	cout << "������� ����� ��������." << endl;
	new_name = console::get_non_existent_field(product_db, "NAME");
	
	if (new_name == "0") {
		return;
	}
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

void Session::edit_amount(string name) {
	int amount;
	console::show_title("��������� ���������� ('0' ��� ������)", "\t", "\n\n");
	cout << "������ ����������: " << product_db->get_int("NAME", name, 1) << endl;
	cout << "������� ����� ����������." << endl;
	cout << "����������: ";
	amount = console::get_number(true);

	if (amount == 0) {
		return;
	}
	else  {
		product_db->update("AMOUNT", "'" + to_string(amount) + "'", "NAME='" + name + "'");
		console::show_info("��������� ���� �������.", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_price(string name) {
	int price;
	console::show_title("��������� ���� ('0' ��� ������)", "\t", "\n\n");
	cout << "������ ����: " << product_db->get_int("NAME", name, 2) << endl;
	cout << "������� ����� ����." << endl;
	cout << "����: ";
	price = console::get_number(true);

	if (price == 0) {
		return;
	}
	else {
		product_db->update("PRICE", "'" + to_string(price) + "'", "NAME='" + name + "'");
		console::show_info("��������� ���� �������.", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_data(string name) {
	string data;
	console::show_title("��������� ���� ('0' ��� ������)", "\t", "\n\n");
	cout << "������ ����: " << product_db->get_text("NAME", name, 3) << endl;
	cout << "������� ����� ����." << endl;
	cout << "����: ";
	data = console::get_format_data();

	if (data == "0") {
		return;
	}
	else {
		product_db->update("DATE", "'" + data + "'", "NAME='" + name + "'");
		console::show_info("��������� ���� �������.", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_reg_name(string name) {
	string reg_name;
	console::show_title("��������� ��� ������������������� ('0' ��� ������)", "\t", "\n\n");
	cout << "������ ���: " << product_db->get_text("NAME", name, 4) << endl;
	cout << "������� ����� ���.\n> " << endl;
	getline(cin, reg_name);

	if (reg_name == "0") {
		return;
	}
	else {
		product_db->update("REG_NAME", "'" + reg_name + "'", "NAME='" + name + "'");
		console::show_info("��������� ���� �������.", "\t", "\n\n");
	}
	system("pause");
}

void Session::individual_task() {
	int mounth_amount, price;
	console::show_title("�������� ������� ������� ������ � �������, � ����� ������ � ('0' ��� ������)", "\t", "\n\n");

	mounth_amount = console::get_number(true, "���������� �������: ");
	if (mounth_amount == 0) return;

	price = console::get_number(true, "���������: ");
	if (price == 0) return;

	string data =  product_db->date_mounhth_befor(to_string(mounth_amount));
	cout << "\n����: " << data << "\n" << endl;

	show_products_table("SELECT * FROM ", " WHERE DATE > '" + data + "' AND PRICE > '" + to_string(price) + "' ORDER BY NAME ASC;");
	system("pause");
}

void Session::find_by_name() {
	string name;
	console::show_title("����� ������ �� �������� ('0' ��� ������)", "\t", "\n\n");
	
	cout << "������� �������� ��� ��� ����� ��� ������\n>";
	getline(cin, name);
	if (name == "0") return;

	cout << endl;
	show_products_table("SELECT * FROM ", " WHERE NAME GLOB '*" + name + "*';");
	system("pause");
}

void Session::find_by_reg_name() {
	string name;
	console::show_title("����� �� ��� ������������������� ����� ('0' ��� ������)", "\t", "\n\n");
	
	cout << "������� ��� ������������������� ��� ��� ����� ��� ������\n>";
	getline(cin, name);
	if (name == "0") return;

	cout << endl;
	show_products_table("SELECT * FROM ", " WHERE REG_NAME GLOB '*" + name + "*';");
	system("pause");
}

void Session::find_by_data() {
	string data;
	console::show_title("����� �� ���� ('0' ��� ������)", "\t", "\n\n");
	
	cout << "�� ������ ������������ ���� * ��� ����������� ����������� ������� (������: *-12-05, 2021-*-*)" << endl;
	cout << "����: ";
	cin >> data;
	cin.ignore(256, '\n');
	if (data == "0") return;


	cout << endl;
	show_products_table("SELECT * FROM ", " WHERE DATE GLOB '" + data + "';");
	system("pause");
}

void Session::sort_by_name() {
	console::show_title("������ ������������� � ���������� �������", "\t", "\n\n");
	show_products_table("SELECT * FROM ", " ORDER BY NAME ASC ;");
	system("pause");
}

void Session::sort_by_price_to_higher() {
	console::show_title("������ ������������� �� ���� (�� ������� � �������)", "\t", "\n\n");
	show_products_table("SELECT * FROM ", " ORDER BY PRICE ASC ;");
	system("pause");
}

void Session::sort_by_amount_to_higher() {
	console::show_title("������ ������������� �� ���������� (�� �������� � ��������)", "\t", "\n\n");
	show_products_table("SELECT * FROM ", " ORDER BY AMOUNT ASC ;");
	system("pause");
}


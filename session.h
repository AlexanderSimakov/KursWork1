#pragma once
#include <iostream>
#include "SQLWORK.h"
#include "account.h"
#include "product.h"
#include <string>
#include "menu.h"
#include "helpFunctions.h"

class Session
{
public:
	Session(SQLWork *product_db, SQLWork *account_db);
	void start_as_user(string login);
	void start_as_admin(string login);

private:
	string user_login = "";
	SQLWork* product_db = nullptr;
	SQLWork* account_db = nullptr;
	Menu *main_menu = nullptr;
	Menu* manage_menu = nullptr;
	Menu *data_menu = nullptr;
	Menu *user_menu = nullptr;
	Menu* account_edit_menu = nullptr;
	Menu* product_edit_menu = nullptr;
	Menu* confirm_operation_menu = nullptr;

	void init_user_menu();
	void init_admin_menu(); 
	void init_confirm_operation_menu();

	void admin_manage_accounts_start();
	void admin_manage_products_start();
	bool confirm_menu_start(string title);

	void show_accounts_table(string sql_start = "SELECT * FROM ", string sql_end = " ;"); // сделать роль администратор\пользователь?
	void add_new_account(); 
	void delete_account();
	void confirm_account();
	void block_account();
	void edit_account_menu_start(); 
	void edit_login(string *login);
	void edit_password(string login);
	void edit_role(string login);

	void add_new_product(); // -проверки ввода
	void delete_product(); 
	void show_products_table(string sql_start = "SELECT * FROM ", string sql_end = " ;");
	void edit_product_menu_start(); 
	void edit_name(string *name); // -проверка ввода
	void edit_amount(string name); // -проверка ввода
	void edit_price(string name); // -проверка ввода
	void edit_data(string name); // -проверка ввода
	void edit_reg_name(string name); // -проверка ввода
	void individual_task(); // -проверки ввода
	void find_by_name(); // -проверки ввода
	void find_by_reg_name(); // -проверки ввода
	void find_by_data(); // -проверки ввода
	void sort_by_name();
	void sort_by_price_to_higher();
	void sort_by_amount_to_higher();
};

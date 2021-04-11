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

	void show_accounts(); // -сделать вывод таблицей -красиво оформить
	void add_new_account(); // -красивое оформление -проверки ввода
	void delete_account();
	void confirm_account();
	void block_account();
	void edit_account_menu_start(); 
	void edit_login(string *login); // -показывать старый вариант -меню подтверждения -проверка ввода
	void edit_password(string login); // -меню подтверждения -новый пароль не может быть таким же как и старый -проверка ввода
	void edit_role(string login); // -показывать старый вариант -меню подтверждения проверка ввода

	void add_new_product(); // -проверки ввода -крсивое оформление -вывод получившейся информации о продукте и запрос о подтверждении -проверки ввода
	void delete_product(); // -сначала найти продукт и вывести информацию о нем -запрос о подтверждении операции
	void show_products(); // -красивое оформление -вывод в форме таблицы
	void edit_product_menu_start(); // -сначала находить продукт -в меню каждой из операции показывать старый вариант
	void edit_name(string *name); // -показывать старый вариант -меню подтверждения -проверка ввода
	void edit_amount(string name); // -показывать старый вариант -меню подтверждения -проверка ввода
	void edit_price(string name); // -показывать старый вариант -меню подтверждения -проверка ввода
	void edit_data(string name); // -показывать старый вариант -меню подтверждения -проверка ввода
	void edit_reg_name(string name); // -показывать старый вариант -меню подтверждения -проверка ввода
	void individual_task(); // -красивое оформление -проверки ввода -проверка ввода
	void find_by_name(); // -проверки ввода -вывод в виде таблицы -провекра ввода
	void find_by_reg_name(); // -проверки ввода -вывод в виде таблицы -проверка ввода
	void find_by_data(); // -проверки ввода -вывод в виде таблицы -проверка ввода
	void sort_by_name(); // -вывод в виде таблицы -красивое оформление
	void sort_by_price_to_higher(); // -вывод в виде таблицы -красивое оформление
	void sort_by_amount_to_higher(); // -вывод в виде таблицы -красивое оформление
};

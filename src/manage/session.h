#pragma once
#include <iostream>
#include <string>
#include "../sqlwork/SQLWORK.h"
#include "../sqlwork/AccountsDB.h"
#include "../sqlwork/ProductsDB.h"
#include "../basic/Account/Account.h"
#include "../basic/Product/Product.h"
#include "../basic/helpFunctions.h"
#include "../menu/menu.h"
#include "../basic/ConsoleOut.h"

using namespace std;

class Session
{
public:
	Session(SQLWork *product_db, SQLWork *account_db);
	void start_as_admin(string login);
	void start_as_user(string login);

private:
	AccountsDB accountsdb;
	ProductsDB productsdb;
	string session_account_login = "";
	SQLWork *product_db = nullptr;
	SQLWork *account_db = nullptr;
	Menu *admin_menu = nullptr;
	Menu *accounts_manage_menu = nullptr;
	Menu *products_manage_menu = nullptr;
	Menu *user_menu = nullptr;
	Menu *account_edit_menu = nullptr;
	Menu *product_edit_menu = nullptr;
	Menu *confirm_operation_menu = nullptr;

	void init_admin_menu();
	void init_user_menu(); 
	void init_confirm_operation_menu();

	void admin_manage_accounts_start();
	void admin_manage_products_start();
	bool confirm_menu_start(string title);

	void add_new_account(); 
	void delete_account();
	void confirm_account();
	void block_account();
	void start_edit_account_menu(); 
	void edit_account_login(string *login);
	void edit_account_password(string login);
	void edit_account_role(string login);

	void add_new_product();
	void delete_product();
	void start_edit_product_menu(); 
	void edit_product_name(string *name); 
	void edit_product_amount(string name);
	void edit_product_price(string name);
	void edit_product_date(string name); 
	void edit_name_of_product_registrant(string name);
	void individual_task();
	void find_products_by_name(); 
	void find_products_by_name_of_registrant();
	void find_products_by_date();
};

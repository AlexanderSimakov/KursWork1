#pragma once
#include <iostream>
#include <string>
#include "../sqlwork/SQLWORK.h"
#include "../sqlwork/AccountsDB/AccountsDB.h"
#include "../sqlwork/ProductsDB/ProductsDB.h"
#include "../basic/Account/Account.h"
#include "../basic/Product/Product.h"
#include "../basic/Console/ConsoleInp.h"
#include "../menu/menu.h"
#include "../menu/confirm/ConfirmationMenu.h"
#include "../basic/Console/ConsoleOut.h"

using namespace std;

class Session
{
public:
	Session(ProductsDB *product_db, AccountsDB *accountsdb);
	void start_as_admin(string login);
	void start_as_user(string login);

private:
	AccountsDB *accountsdb;
	ProductsDB *productsdb;
	string session_account_login = "";
	Menu *admin_menu = nullptr;
	Menu *accounts_manage_menu = nullptr;
	Menu *products_manage_menu = nullptr;
	Menu *user_menu = nullptr;
	Menu *account_edit_menu = nullptr;
	Menu *product_edit_menu = nullptr;

	void init_admin_menu();
	void init_user_menu(); 

	void admin_manage_accounts_start();
	void admin_manage_products_start();

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
	void find_products_by_name(); 
	void find_products_by_name_of_registrant();
	void find_products_by_date();
};

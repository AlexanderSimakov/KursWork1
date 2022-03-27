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
#include "../menu/factory/MenuFactory.h"
#include "../menu/confirm/ConfirmationMenu.h"
#include "../basic/Console/ConsoleOut.h"

using namespace std;

class Session
{
public:
	Session();
	Session(ProductsDB *product_db, AccountsDB *accountsdb);
	void start(Account* account);

private:
	AccountsDB *accountsdb;
	Menu *admin_menu = nullptr;
	Menu *accounts_manage_menu = nullptr;
	Menu *products_manage_menu = nullptr;
	Menu *user_menu = nullptr;
	Menu *account_edit_menu = nullptr;
	Menu *product_edit_menu = nullptr;

	void start_as_admin();
	void start_as_user();

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

protected:
	ProductsDB *productsdb;
	Account* session_account;

	void find_products_by_name(); 
	void find_products_by_name_of_registrant();
	void find_products_by_date();
};

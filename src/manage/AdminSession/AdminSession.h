#pragma once
#include "../session.cpp"
#include "../../menu/menu.h"
#include "../../menu/confirm/ConfirmationMenu.h"
#include "../../menu/factory/MenuFactory.h"
#include "../../sqlwork/AccountsDB/AccountsDB.h"
#include "../../sqlwork/ProductsDB/ProductsDB.h"

class AdminSession : Session
{
public:
    AdminSession(AccountsDB* accounts_db, ProductsDB* products_db);
    void start(Account* account);

private:
    AccountsDB* accounts_db;
    Menu *admin_menu;
	Menu *accounts_manage_menu;
	Menu *products_manage_menu;
	Menu *user_menu;
	Menu *account_edit_menu;
	Menu *product_edit_menu;

    void start_accounts_managing();
	void start_products_managing();

	void add_account(); 
	void delete_account();
	void confirm_account();
	void block_account();
	void start_account_editing(); 
	void edit_login(string *login);
	void edit_password(string login);
	void edit_role(string login);

	void add_product();
	void delete_product();
	void start_product_editing(); 
	void edit_name(string *name); 
	void edit_amount(string name);
	void edit_price(string name);
	void edit_date(string name); 
	void edit_registrant(string name);
};

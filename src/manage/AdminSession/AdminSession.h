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
    AdminSession(AccountsDB* accountsDb, ProductsDB* productsDB);
    void start(Account* account);

private:
    AccountsDB* accountsDB = nullptr;
    Menu *admin_menu = nullptr;
	Menu *accounts_manage_menu = nullptr;
	Menu *products_manage_menu = nullptr;
	Menu *user_menu = nullptr;
	Menu *account_edit_menu = nullptr;
	Menu *product_edit_menu = nullptr;

    void start_accounts_managing();
	void start_products_managing();

	void add_new_account(); 
	void delete_account();
	void confirm_account();
	void block_account();
	void start_account_editing(); 
	void edit_account_login(string *login);
	void edit_account_password(string login);
	void edit_account_role(string login);

	void add_new_product();
	void delete_product();
	void start_product_editing(); 
	void edit_product_name(string *name); 
	void edit_product_amount(string name);
	void edit_product_price(string name);
	void edit_product_date(string name); 
	void edit_product_registrant(string name);
};

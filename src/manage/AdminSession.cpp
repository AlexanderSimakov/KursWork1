#include "AdminSession.h"

AdminSession::AdminSession(AccountsDB* accountsDB, ProductsDB* productsDB){
    this->productsdb = productsDB;
	this->accountsDB = accountsDB;
    {
    	admin_menu = MenuFactory::create_admin_menu();
	    accounts_manage_menu = MenuFactory::create_accounts_manage_menu();
    	products_manage_menu = MenuFactory::create_products_manage_menu();
	    account_edit_menu = MenuFactory::create_account_edit_menu();
	    product_edit_menu = MenuFactory::create_product_edit_menu();
	    user_menu = MenuFactory::create_user_menu();
    }
}

void AdminSession::start(Account* account){
    session_account = account;
     
}
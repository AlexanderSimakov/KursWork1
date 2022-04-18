#pragma once
#include <iostream>
#include <string>
#include "../sqlwork/ProductsDB/ProductsDB.hpp"
#include "../basic/Account/Account.hpp"
#include "../basic/Console/ConsoleInp.hpp"
#include "../menu/confirm/ConfirmationMenu.hpp"
#include "../basic/Console/ConsoleOut.hpp"

using namespace std;

class Session
{
protected:
	ProductsDB *products_db;
	Account* session_account;

	inline void find_products_by_name(); 
	inline void find_products_by_registrant();
	inline void find_products_by_date();
};

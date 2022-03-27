#pragma once
#include <iostream>
#include <string>
#include "../sqlwork/ProductsDB/ProductsDB.h"
#include "../basic/Account/Account.h"
#include "../basic/Console/ConsoleInp.h"
#include "../menu/confirm/ConfirmationMenu.h"
#include "../basic/Console/ConsoleOut.h"

using namespace std;

class Session
{
protected:
	ProductsDB *productsdb;
	Account* session_account;

	inline void find_products_by_name(); 
	inline void find_products_by_name_of_registrant();
	inline void find_products_by_date();
};

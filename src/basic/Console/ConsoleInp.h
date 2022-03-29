#pragma once 
#include <string>
#include "../../sqlwork/SQLWORK.h"
#include "../../sqlwork/AccountsDB/AccountsDB.h"
#include "../../sqlwork/ProductsDB/ProductsDB.h"
#include "ConsoleOut.h"
#include "../Account/Account.h"

class ConsoleInp
{
public:
    static string get_login();
	static string get_exists_login(AccountsDB* accounts_db);
	static string get_free_login(AccountsDB* accounts_db);
	static string get_password(string true_hash, string true_salt);

	static string get_exists_product_name(ProductsDB* products_db);
	static string get_non_existent_product_name(ProductsDB* products_db);
	
	static string get_format_date();

	static string password_format_input();
	static bool is_all_symbols_and_nums(string line);
	static int get_number(bool is_positive = false, string line_for_user = "\n> ");
	static int get_number_from_range(int min, int max, string out_line = "\n> ");
};

#pragma once 
#include <string>
#include "../../sqlwork/SQLWORK.h"
#include "../../sqlwork/AccountsDB/AccountsDB.h"
#include "../../sqlwork/ProductsDB.h"
#include "ConsoleOut.h"
#include "../Account/Account.h"

class ConsoleInp
{
public:
    static string get_login();
	static string get_exists_login(AccountsDB* db, string line_for_user = "Login: ");
	static string get_free_login(AccountsDB* db, string line_for_user = "\n> ");
	static string get_password(string true_hash, string true_salt);

	static string get_exists_product_name(ProductsDB* db, string line_for_user = "Name: ");
	static string get_non_existent_product_name(ProductsDB* db, string line_for_user = "Name: ");
	
	static string get_format_date(string line_for_user = "\n> ");

	static string password_format_input(string line_for_user = "");
	static bool is_all_symbols_and_nums(string line);
	static int get_number(bool is_positive = false, string line_for_user = "\n> ");
	static int get_number_from_range(int min, int max, string out_line = "\n> ");
};

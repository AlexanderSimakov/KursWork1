#pragma once
#include <iostream>
#include "../sqlwork/SQLWORK.h"
#include "../basic/Account/Account.h"
#include "../basic/Console/ConsoleOut.h"
#include "../basic/Console/ConsoleInp.h"

using namespace std;

class Registration
{
public:
	Registration(SQLWork *sql_db);
	void start();

private:
	Account account;
	SQLWork *sql_db = nullptr;

	void add_account_to_data_base();
};

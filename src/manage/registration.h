#pragma once
#include <iostream>
#include "../basic/account.h"
#include "../sqlwork/SQLWORK.h"
#include "../basic/helpFunctions.h"
#include "../basic/ConsoleOut.h"

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

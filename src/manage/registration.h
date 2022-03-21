#pragma once
#include <iostream>
#include "src/basic/account.h"
#include "src/sql/SQLWORK.h"
#include "src/basic/helpFunctions.h"

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

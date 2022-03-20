#pragma once
#include <iostream>
#include "account.h"
#include "SQLWORK.h"
#include "helpFunctions.h"

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

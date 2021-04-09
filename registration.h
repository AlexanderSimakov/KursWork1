#pragma once
#include <iostream>
#include "account.h"
#include "SQLWORK.h"

using namespace std;

class Registration
{
public:
	Registration(SQLWork *sql_db);
	void start();


private:
	Account account;
	SQLWork *sql_db;

	void add_to_data_base();

};

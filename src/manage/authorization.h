#pragma once
#include <iostream>
#include <string>
#include "src/sql/SQLWORK.h"
#include "src/basic/helpFunctions.h"

using namespace std;

class Authorization
{
public:
	Authorization(SQLWork* sql_db);
	int start();
	string get_login();

private:
	SQLWork *sql_db = nullptr;
	string login = "";
};

#pragma once
#include <iostream>
#include <string>
#include "../sqlwork/SQLWORK.h"
#include "../basic/helpFunctions.h"

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

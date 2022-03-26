#pragma once
#include <iostream>
#include <string>
#include "../sqlwork/AccountsDB.h"
#include "../basic/Console/ConsoleInp.h"
#include "../basic/Console/ConsoleOut.h"

using namespace std;

class Authorization
{
public:
	Authorization(AccountsDB* db);
	int start();
	string get_login();

private:
	AccountsDB *db = nullptr;
	string login = "";
};

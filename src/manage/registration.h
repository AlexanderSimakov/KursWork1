#pragma once
#include <iostream>
#include "../sqlwork/SQLWORK.h"
#include "../sqlwork/AccountsDB.h"
#include "../basic/Account/Account.h"
#include "../basic/Console/ConsoleOut.h"
#include "../basic/Console/ConsoleInp.h"

using namespace std;

class Registration
{
public:
	Registration(AccountsDB *db);
	void start();

private:
	Account account;
	AccountsDB *db = nullptr;
};

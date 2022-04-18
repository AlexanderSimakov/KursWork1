#pragma once
#include <iostream>
#include "../../sqlwork/SQLWORK.hpp"
#include "../../sqlwork/AccountsDB/AccountsDB.hpp"
#include "../../basic/Account/Account.hpp"
#include "../../basic/Console/ConsoleOut.hpp"
#include "../../basic/Console/ConsoleInp.hpp"

using namespace std;

class Registration
{
public:
	static void start(AccountsDB* accounts_db);
};

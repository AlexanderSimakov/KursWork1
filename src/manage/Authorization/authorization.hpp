#pragma once
#include <iostream>
#include <string>
#include "../../sqlwork/AccountsDB/AccountsDB.hpp"
#include "../../basic/Console/ConsoleInp.hpp"
#include "../../basic/Console/ConsoleOut.hpp"

using namespace std;

class Authorization
{
public:
	static Account* start(AccountsDB* accounts_db);
};

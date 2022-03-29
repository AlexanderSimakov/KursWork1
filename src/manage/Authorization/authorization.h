#pragma once
#include <iostream>
#include <string>
#include "../../sqlwork/AccountsDB/AccountsDB.h"
#include "../../basic/Console/ConsoleInp.h"
#include "../../basic/Console/ConsoleOut.h"

using namespace std;

class Authorization
{
public:
	static Account* start(AccountsDB* accounts_db);
};

#pragma once
#include <iostream>
#include "SQLWORK.h"
#include "consoleInput.h"


using namespace std;


class Authorization
{
public:
	Authorization(SQLWork* sql_db);
	int start();

private:
	SQLWork *sql_db;

};

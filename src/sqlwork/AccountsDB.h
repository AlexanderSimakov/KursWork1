#pragma once
#include "SQLWORK.h"
#include "../basic/ConsoleOut.h"
#include <string>

using namespace std;

class AccountsDB
{
private:
	static SQLWork *data_base;

public:
    static const string DATABASE_FILENAME;
    static const string DATABASE_NAME;
    static const string LOGIN;
    static const string HASH;
    static const string SALT;
    static const string ROLE;
    static const string ACCESS;


    

};



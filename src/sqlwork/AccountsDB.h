#pragma once
#include "SQLWORK.h"
#include "../basic/Console/ConsoleOut.h"
#include "../basic/Account/Account.h"
#include <string>

using namespace std;

class AccountsDB
{
public:
    AccountsDB();
    AccountsDB(SQLWork *db);
    void init();
    void show_table();
    void add_new(Account account); 
    void _delete(string login);
    void confirm(string login);
    void block(string login);
    void update_login(string old_login, string new_login);
    void update_password(string login, string password);
    void update_role(string login, int role);

    bool is_have_access(string login);

    SQLWork *db;

private:
	static const string DATABASE_FILENAME;
    static const string DATABASE_NAME;
    static const string LOGIN;
    static const string HASH;
    static const string SALT;
    static const string ROLE;
    static const string ACCESS;
};



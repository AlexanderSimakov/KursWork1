#pragma once
#include "../SQLWORK.hpp"
#include "../../basic/Console/ConsoleOut.hpp"
#include "../../basic/Account/Account.hpp"
#include <string>

using namespace std;

class AccountsDB
{
public:
    AccountsDB();
    AccountsDB(SQLWork *db);
    void init();
    void close();
    void show_table();
    void add_new(Account account); 
    void _delete(string login);
    void confirm(string login);
    void block(string login);
    void update_login(string old_login, string new_login);
    void update_password(string login, string password);
    void update_role(string login, Role role);

    bool is_have_access(string login);
    bool is_account_exists(string login);
    string get_salt(string login);
    string get_hash(string login);
    Role get_role(string login);

private:
	static const string DATABASE_FILENAME;
    static const string DATABASE_NAME;
    static const string LOGIN;
    static const string HASH;
    static const string SALT;
    static const string ROLE;
    static const string ACCESS;

    SQLWork *db;
};



#pragma once
#include <string>
#include "../sha/sha256.h"

using namespace std;


enum Role { USER, ADMIN };
enum Access { NO, YES };

class Account
{
public:
    Account();
    Account(string login, string hash, string salt, Role role, Access access);

    void set_login(string login);
    void set_hash(string hash);
    void set_salt(string salt);
    void set_role(Role role);
    void set_access(Access access);

    string get_login();
    string get_hash();
    string get_salt();
    Role get_role();
    Access get_access();

    static string get_generated_salt();
    static string get_generated_hash(string password, string salt);
   

private:
    static const int SALT_SIZE = 16; 
	static const int SYMBOLS_SIZE = 62;
    string login;
    string hash;
    string salt;
    Role role;
    Access access; 

    static string get_symbols_for_salt();
};


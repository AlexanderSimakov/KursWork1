#include "Account.h"


Account::Account(){ }

Account::Account(string login, string hash, string salt, Role role, Access access)
{ 
    this->login = login;
    this->hash = hash;
    this->salt = salt;
    this->role = role;
    this->access = access;
}

Account* Account::generate_empty()
{
    return new Account("empty", "empty", "empty", Role::USER, Access::NO);
}

bool Account::is_empty()
{
    return login == "empty" && hash == "empty" && salt == "empty" && 
           role == Role::USER && access == Access::NO;
}

void Account::set_login(string login)
{ 
    this->login = login; 
}

void Account::set_hash(string hash)
{ 
    this->hash = hash; 
}

void Account::set_salt(string salt)
{ 
    this->salt = salt; 
}

void Account::set_role(Role role)
{ 
    this->role = role; 
}

void Account::set_access(Access access)
{ 
    this->access = access; 
}

string Account::get_login()
{ 
    return login; 
}

string Account::get_hash()
{ 
    return hash; 
}

string Account::get_salt()
{ 
    return salt; 
}

Role Account::get_role()
{ 
    return role; 
}

Access Account::get_access()
{ 
    return access; 
}

string Account::get_generated_salt()
{
    string symbols = get_symbols_for_salt();
	srand(time(NULL));

	string salt;
	salt.reserve(SALT_SIZE);

	for (int i = 0; i < SALT_SIZE; i++) salt.push_back(symbols[rand() % SYMBOLS_SIZE]);

	return salt;    
}
 
string Account::get_symbols_for_salt()
{
	string symbols;
	symbols.reserve(SYMBOLS_SIZE);

	char little_letter = 'a';
	char big_letter = 'A';
	char number = '0';
	for (int k = 0; k < 26; k++)
    {
		symbols.push_back(little_letter++);
		symbols.push_back(big_letter++);
		if (k < 10) symbols.push_back(number++);
	}

	return symbols;
}

string Account::get_generated_hash(string password, string salt)
{ 
	return sha1(sha1(password + salt) + sha1(password));
}
 
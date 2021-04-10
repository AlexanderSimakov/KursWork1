#pragma once
#include <string>
#include "SQLWORK.h"

using namespace std;

const string ACCOUNTS_DATABASE_FILENAME = "accounts.db";
const string ACCOUNTS_DATABASE_NAME = "ACCOUNTS";


struct Account {
	string login = "";
	string salted_hash_password = "";
	string salt = "";
	int role = 0;
	bool access = false;
};
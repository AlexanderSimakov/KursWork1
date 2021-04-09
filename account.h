#pragma once
#include <string>
#include "SQLWORK.h"

using namespace std;

const string ACCOUNTS_DATABASE_FILENAME = "accounts.db";
const string ACCOUNTS_DATABASE_NAME = "ACCOUNTS";


struct Account {
	string login = "";
	int salted_hash_password = 0;
	string salt = "";
	int role = 0;
	bool access = false;
};
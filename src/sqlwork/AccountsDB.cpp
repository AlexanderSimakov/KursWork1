#include "AccountsDB.h"

const string AccountsDB::DATABASE_FILENAME = "accounts.db";
const string AccountsDB::DATABASE_NAME = "ACCOUNTS";
const string AccountsDB::LOGIN = "LOGIN";
const string AccountsDB::HASH = "HASH";
const string AccountsDB::SALT = "SALT";
const string AccountsDB::ROLE = "ROLE";
const string AccountsDB::ACCESS = "ACCESS";

void AccountsDB::init()
{
    data_base = SQLWork(DATABASE_FILENAME);

    data_base.open();
	data_base.create_table_if_not_exists({ SQL_cell{ LOGIN,  "TEXT PRIMARY KEY NOT NULL"},
				 SQL_cell{ HASH,   "TEXT NOT NULL"},
				 SQL_cell{ SALT,   "TEXT NOT NULL"},
				 SQL_cell{ ROLE,   "INT NOT NULL"},
				 SQL_cell{ ACCESS, "INT NOT NULL"} },
		         DATABASE_NAME);

    if (data_base.get_text(LOGIN, "admin", 2) == "") 
	{
		string salt = help_functions::get_generated_salt();
		string salted_hash_password = help_functions::get_generated_hash("admin", salt);

		data_base.push_back({ "'admin'", "'" + salted_hash_password + "'", "'" + salt + "'", "1", "1" });
	}
}

void AccountsDB::show_table()
{
    ConsoleOut::show_title("Accounts", "    ");
	data_base.show_table("SELECT * FROM ", " ;",
		{ "     name", "role", "access" },
		{ 0, 3, 4 },
		{ 18, 7, 9 });
	cout << endl;
}

void AccountsDB::add_new(Account account)
{
    data_base.push_back({ "'" + account.login + "'",
						  "'" + account.salted_hash_password + "'",
						  "'" + account.salt + "'",
						  to_string(account.role),
						  to_string(account.access) });
}

void AccountsDB::_delete(string login){
	data_base.delete_field(LOGIN + "='" + login + "'");
}

void AccountsDB::confirm(string login){
	data_base.update(ACCESS, "1", LOGIN + "='" + login + "'");
}

void AccountsDB::block(string login){
	data_base.update(ACCESS, "0", LOGIN + "='" + login + "'");
}

void AccountsDB::update_login(string old_login, string new_login){
	data_base.update(LOGIN, "'" + new_login + "'", LOGIN + "='" + old_login + "'");
}

void AccountsDB::update_password(string login, string password){
	string salt = help_functions::get_generated_salt();
	string hash = help_functions::get_generated_hash(password, salt);
	data_base.update(HASH, "'" + hash + "'", LOGIN + "='" + login + "'");
	data_base.update(SALT, "'" + salt + "'", LOGIN + "='" + login + "'");
}

void AccountsDB::update_role(string login, int role){
	data_base.update(ROLE, to_string(role), LOGIN + "='" + login + "'");
}
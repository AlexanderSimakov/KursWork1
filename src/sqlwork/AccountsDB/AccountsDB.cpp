#include "AccountsDB.h"

const string AccountsDB::DATABASE_FILENAME = "accounts.db";
const string AccountsDB::DATABASE_NAME = "ACCOUNTS";
const string AccountsDB::LOGIN = "LOGIN";
const string AccountsDB::HASH = "HASH";
const string AccountsDB::SALT = "SALT";
const string AccountsDB::ROLE = "ROLE";
const string AccountsDB::ACCESS = "ACCESS";


AccountsDB::AccountsDB(){ }

AccountsDB::AccountsDB(SQLWork *db){ this->db = db; }

void AccountsDB::init()
{
    db = new SQLWork(DATABASE_FILENAME);

    db->open();
	db->create_table_if_not_exists({ 
				SQL_cell{ LOGIN,  "TEXT PRIMARY KEY NOT NULL"},
				SQL_cell{ HASH,   "TEXT NOT NULL"},
				SQL_cell{ SALT,   "TEXT NOT NULL"},
				SQL_cell{ ROLE,   "INT NOT NULL"},
				SQL_cell{ ACCESS, "INT NOT NULL"} },
		        DATABASE_NAME);

    if (db->get_text(LOGIN, "admin", 2) == "") 
	{
		string salt = Account::get_generated_salt();
		string hash = Account::get_generated_hash("admin", salt);

		db->push_back({ "'admin'", "'" + hash + "'", "'" + salt + "'", to_string(Role::ADMIN), to_string(Access::YES) });
	}
}

void AccountsDB::show_table()
{
    ConsoleOut::show_title("Accounts", "    ");
	db->show_table("SELECT * FROM ", " ;",
		{ "     name", "role", "access" },
		{ 0, 3, 4 },
		{ 18, 7, 9 });
	cout << endl;
}

void AccountsDB::add_new(Account account)
{
    db->push_back({ "'" + account.get_login() + "'",
				    "'" + account.get_hash() + "'",
					"'" + account.get_salt() + "'",
					to_string(account.get_role()),
					to_string(account.get_access()) });
}

void AccountsDB::_delete(string login)
{
	db->delete_field(LOGIN + "='" + login + "'");
}

void AccountsDB::confirm(string login)
{
	db->update(ACCESS, to_string(Access::YES), LOGIN + "='" + login + "'");
}

void AccountsDB::block(string login)
{
	db->update(ACCESS, to_string(Access::NO), LOGIN + "='" + login + "'");
}

void AccountsDB::update_login(string old_login, string new_login)
{
	db->update(LOGIN, "'" + new_login + "'", LOGIN + "='" + old_login + "'");
}

void AccountsDB::update_password(string login, string password)
{
	string salt = Account::get_generated_salt();
	string hash = Account::get_generated_hash(password, salt);
	db->update(HASH, "'" + hash + "'", LOGIN + "='" + login + "'");
	db->update(SALT, "'" + salt + "'", LOGIN + "='" + login + "'");
}

void AccountsDB::update_role(string login, Role role)
{
	db->update(ROLE, to_string(role), LOGIN + "='" + login + "'");
}

bool AccountsDB::is_have_access(string login)
{
	return db->get_int(LOGIN, login, 4) == Access::YES; 
}

bool AccountsDB::is_account_exists(string login)
{
	return "" != db->get_text(LOGIN, login, 1);
}

string AccountsDB::get_salt(string login)
{
	return db->get_text(LOGIN, login, 2);
}

string AccountsDB::get_hash(string login)
{
	return db->get_text(LOGIN, login, 1);
}

Role AccountsDB::get_role(string login)
{
	return (Role) db->get_int(LOGIN, login, 3);
}

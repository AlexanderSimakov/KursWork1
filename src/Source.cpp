#include <iostream>
#include "menu/menu.h"
#include "manage/registration.h"
#include "manage/authorization.h"
#include "manage/session.h"
#include "sqlwork/SQLWORK.h"
#include "sqlwork/AccountsDB.h"
#include "basic/account.h"
#include "basic/product.h"
#include "basic/helpFunctions.h"

using namespace std;

void init_accounts_db(SQLWork* db);
void init_product_db(SQLWork* db);
void add_admin_account_if_not_exists(SQLWork* db);


int main() {
	SQLWork accounts_db(ACCOUNTS_DATABASE_FILENAME);
	SQLWork product_db(PRODUCT_DATABASE_FILENAME);
	init_accounts_db(&accounts_db);
	init_product_db(&product_db);
	add_admin_account_if_not_exists(&accounts_db);

	Registration registration(&accounts_db);
	Authorization authorization(&accounts_db);
	Session session(&product_db, &accounts_db);

	Menu main_menu("<- Main menu ->",
				 { " Log in",
				   " Create account",
				   " Exit" });
	main_menu.set_start_with_first_line(true);


	int choise = 0, role = -1;
	while (true) {
		choise = main_menu.get_num_of_choisen_line();
		switch (choise)
		{
		case 0: 
			role = authorization.start();
			if (role == 0) { 
				session.start_as_user(authorization.get_login());
			}
			else if (role == 1) {
				session.start_as_admin(authorization.get_login());
			}
			break;
		case 1:
			registration.start();
			break;
		case 2: case -1:
			accounts_db.close();
			product_db.close();
			return 0;
		default:
			break;
		}
	}

	return 0;
}

void init_accounts_db(SQLWork* db) {
	db->open();
	db->create_table_if_not_exists({ SQL_cell{ "LOGIN",  "TEXT PRIMARY KEY NOT NULL"},
				 SQL_cell{ "HASH",   "TEXT NOT NULL"},
				 SQL_cell{ "SALT",   "TEXT NOT NULL"},
				 SQL_cell{ "ROLE",   "INT NOT NULL"},
				 SQL_cell{ "ACCESS", "INT NOT NULL"} },
		ACCOUNTS_DATABASE_NAME);
}

void init_product_db(SQLWork* db) {
	db->open();
	db->create_table_if_not_exists({ SQL_cell{ "NAME",     "TEXT PRIMARY KEY NOT NULL"},
				 SQL_cell{ "AMOUNT",   "INT NOT NULL"},
				 SQL_cell{ "PRICE",    "INT NOT NULL"},
				 SQL_cell{ "DATE",     "TEXT NOT NULL"},
				 SQL_cell{ "REG_NAME", "TEXT NOT NULL"} },
		PRODUCT_DATABASE_NAME);
}

void add_admin_account_if_not_exists(SQLWork* db) {
	if (db->get_text("LOGIN", "admin", 2) == "") {
		string salt = help_functions::get_generated_salt();
		string salted_hash_password = help_functions::get_generated_hash("admin", salt);

		db->push_back({ "'admin'", "'" + salted_hash_password + "'", "'" + salt + "'", "1", "1" });
	}
}

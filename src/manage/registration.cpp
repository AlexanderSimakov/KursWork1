#pragma once
#include "registration.h"

Registration::Registration(SQLWork *sql_db) {
	this->sql_db = sql_db;
}

void Registration::start() {
	ConsoleOut::show_title("Creating an account (0 - exit)");

	account.set_login(ConsoleInp::get_free_login(sql_db, "Login: "));
	if (account.get_login() == "0") return;
	string pass = ConsoleInp::password_format_input("Password: ");
	if (pass == "0") return;
	account.set_salt(Account::get_generated_salt());
	account.set_hash(Account::get_generated_hash(pass, account.get_salt()));

	add_account_to_data_base();

	ConsoleOut::show_info("Your account was created and waiting to get access", "\n\t", "\n\n");

	system("pause");
}

void Registration::add_account_to_data_base() {
	sql_db->push_back({ "'" + account.get_login() + "'",
					    "'" + account.get_hash()  + "'",
					    "'" + account.get_salt() + "'",
					   to_string(account.get_role()),
					   to_string(account.get_access()) });
}


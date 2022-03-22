#pragma once
#include "src/manage/registration.h"

Registration::Registration(SQLWork *sql_db) {
	this->sql_db = sql_db;
}

void Registration::start() {
	console::show_title("Registration. (0 - exit)");

	account.login = console::get_free_login(sql_db, "Login: ");
	if (account.login == "0") return;
	string pass = console::password_format_input("Password: ");
	if (pass == "0") return;
	account.salt = help_functions::get_generated_salt();
	account.salted_hash_password = help_functions::get_generated_hash(pass, account.salt);


	add_account_to_data_base();

	console::show_info("Your account was created and waiting to get access", "\n\t", "\n\n");

	system("pause");
}

void Registration::add_account_to_data_base() {
	sql_db->push_back({ "'" + account.login + "'",
					    "'" + account.salted_hash_password  + "'",
					    "'" + account.salt + "'",
					   to_string(account.role),
					   to_string(account.access) });
}


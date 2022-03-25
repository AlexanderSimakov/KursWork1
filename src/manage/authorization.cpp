#pragma once
#include "authorization.h"

Authorization::Authorization(SQLWork* sql_db) {
	this->sql_db = sql_db;
}

int Authorization::start() {
	string input_login, db_account_hash, db_account_salt, input_password;

	ConsoleOut::show_title("Log In (0 - exit)");

	while (true) {
		input_login = ConsoleInp::get_login();
		if (input_login == "0") return -1;

		db_account_hash = sql_db->get_text("LOGIN", input_login, 1);
		db_account_salt = sql_db->get_text("LOGIN", input_login, 2);
		input_password = ConsoleInp::get_password(db_account_hash, db_account_salt);

		if (input_password == "0") return -1;
		else if (input_password == "-1") {
			ConsoleOut::show_error("Wrong password");
		}
		else if (sql_db->get_int("LOGIN", input_login, 4) == 0) {
			ConsoleOut::show_error("Account have no access");
		}
		else {
			break;
		}
	}

	this->login = input_login;
	return sql_db->get_int("LOGIN", input_login, 3);
}

string Authorization::get_login() {
	return this->login;
}

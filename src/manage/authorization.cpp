#pragma once
#include "authorization.h"

Authorization::Authorization(AccountsDB* db) {
	this->db = db;
}

int Authorization::start() {
	string login, password;

	ConsoleOut::show_title("Log In (0 - exit)");

	while (true) {
		login = ConsoleInp::get_login();
		if (login == "0") return -1;

		password = ConsoleInp::get_password(db->get_hash(login), db->get_salt(login));

		if (password == "0") return -1;
		else if (password == "-1") {
			ConsoleOut::show_error("Wrong password");
		}
		else if (!db->is_have_access(login)) {
			ConsoleOut::show_error("Account have no access");
		}
		else {
			break;
		}
	}

	this->login = login;
	return db->get_role(login);
}

string Authorization::get_login() {
	return this->login;
}

#pragma once
#include "registration.h"

Registration::Registration(AccountsDB *db) {
	this->db = db;
}

void Registration::start() {
	ConsoleOut::show_title("Creating an account (0 - exit)");

	account.set_login(ConsoleInp::get_free_login(db, "Login: "));
	if (account.get_login() == "0") return;
	string pass = ConsoleInp::password_format_input("Password: ");
	if (pass == "0") return;
	account.set_salt(Account::get_generated_salt());
	account.set_hash(Account::get_generated_hash(pass, account.get_salt()));

	db->add_new(account);

	ConsoleOut::show_info("Your account was created and waiting to get access", "\n\t", "\n\n");
	ConsoleOut::pause();
}

#pragma once
#include "authorization.h"

Account* Authorization::start(AccountsDB* db) 
{
	Account* account = Account::generate_empty();
	string login, password;

	ConsoleOut::show_title("Log In (0 - exit)");

	while (true) 
	{
		login = ConsoleInp::get_login();
		if (login == "0") return Account::generate_empty();

		password = ConsoleInp::get_password(db->get_hash(login), db->get_salt(login));

		if (password == "0") return Account::generate_empty();
		else if (password == "-1") {
			ConsoleOut::show_error("Wrong password");
		}
		else if (!db->is_have_access(login)) {
			ConsoleOut::show_error("Account have no access");
		}
		else {
			account->set_login(login);
			account->set_hash(db->get_hash(login));
			account->set_salt(db->get_salt(login));
			account->set_role(db->get_role(login));
			account->set_access(Access::YES);
			break;
		}
	}

	return account;
}

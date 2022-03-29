#pragma once
#include "authorization.h"

Account* Authorization::start(AccountsDB* accounts_db) 
{
	ConsoleOut::show_title("Log In (0 - exit)");
	Account* account = Account::generate_empty();
	string login, password;

	while (true) 
	{
		login = ConsoleInp::get_login();
		if (login == "0") return Account::generate_empty();

		password = ConsoleInp::get_password(accounts_db->get_hash(login), accounts_db->get_salt(login));

		if (password == "0") return Account::generate_empty();
		else if (password == "-1") 
		{
			ConsoleOut::show_error("Wrong password");
		}
		else if (!accounts_db->is_have_access(login)) 
		{
			ConsoleOut::show_error("Account have no access");
		}
		else 
		{
			account->set_login(login);
			account->set_hash(accounts_db->get_hash(login));
			account->set_salt(accounts_db->get_salt(login));
			account->set_role(accounts_db->get_role(login));
			account->set_access(Access::YES);
			break;
		}
	}

	return account;
}

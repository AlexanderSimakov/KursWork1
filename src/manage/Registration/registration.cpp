#pragma once
#include "registration.hpp"

void Registration::start(AccountsDB* accounts_db) 
{
	ConsoleOut::show_title("Creating an account (0 - exit)");
	Account account;

	account.set_login(ConsoleInp::get_free_login(accounts_db));
	if (account.get_login() == "0") return;

	string pass = ConsoleInp::password_format_input();
	if (pass == "0") return;

	account.set_salt(Account::get_generated_salt());
	account.set_hash(Account::get_generated_hash(pass, account.get_salt()));
	account.set_access(Access::NO);
	account.set_role(Role::USER);
	accounts_db->add_new(account);

	ConsoleOut::show_info("Your account was created and waiting to get access", "\n\t", "\n\n");
	ConsoleOut::pause();
}

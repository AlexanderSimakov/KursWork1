#pragma once
#include "registration.h"

Registration::Registration(SQLWork *sql_db) {
	this->sql_db = sql_db;
}

// запуск регистрации и добавление аккаунта в базу данных
void Registration::start() {
	console::show_title("Регистрация. (Для выхода введите 0 в любом из полей)");

	account.login = console::get_free_login(sql_db, "Логин: ");
	if (account.login == "0") return;
	string pass = console::password_format_input("Пароль: ");
	if (pass == "0") return;
	account.salt = help_functions::get_generated_salt();
	account.salted_hash_password = help_functions::get_generated_hash(pass, account.salt);


	add_account_to_data_base();

	console::show_info("Ваш аккаунт был создан и будет ожидать подтверждения администратором", "\n\t", "\n\n");

	system("pause");
}

// добавление аккаунта в базу данных
void Registration::add_account_to_data_base() {
	sql_db->push_back({ "'" + account.login + "'",
					    "'" + account.salted_hash_password  + "'",
					    "'" + account.salt + "'",
					   to_string(account.role),
					   to_string(account.access) });
}


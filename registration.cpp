#pragma once
#include "registration.h"

Registration::Registration(SQLWork *sql_db) {
	this->sql_db = sql_db;
}

void Registration::start() {
	cout << "Регистрация нового пользователя. (Для выхода введите 0 в любом из полей)" << endl;

	cout << "Логин: ";
	cin >> account.login;
	cout << "Пароль: ";
	cin >> account.salt;


	add_to_data_base();
}

void Registration::add_to_data_base() {
	sql_db->push_back({ "'" + account.login + "'",
					    "'" + account.salt  + "'",
					    "'" + to_string(account.salted_hash_password) + "'",
					   to_string(account.role),
					   to_string(account.access) });
}
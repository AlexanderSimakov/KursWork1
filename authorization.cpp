#pragma once
#include "authorization.h"


Authorization::Authorization(SQLWork* sql_db) {
	this->sql_db = sql_db;
}

// запуск начала авторизации, возвращает роль
int Authorization::start() {
	string input_login, db_account_hash, db_account_salt, input_password;

	console::show_title("Авторизация. (Для выхода введите в любое из полей 0)");
	
	input_login = console::get_authorization_login(sql_db);
	if (input_login == "0") return -1;

	db_account_hash = sql_db->get_text("LOGIN", input_login, 1);
	db_account_salt = sql_db->get_text("LOGIN", input_login, 2);

	input_password = console::get_authorization_password(db_account_hash, db_account_salt);
	if (input_password == "0") return -1;

	this->login = input_login;
	return sql_db->get_int("LOGIN", input_login, 3);
}

string Authorization::get_login() {
	return this->login;
}

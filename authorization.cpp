#pragma once
#include "authorization.h"


Authorization::Authorization(SQLWork* sql_db) {
	this->sql_db = sql_db;
}

int Authorization::start() {
	string login, db_account_pass, user_input_pass;

	cout << "Авторизация. (Для выхода введите в любое из полей 0)" << endl;
	
	login = console::get_login(sql_db);
	if (login == "0") return -1;
	db_account_pass = sql_db->get_text("LOGIN", login, 1);
	

	while (true) {
		cout << "Пароль: ";
		cin >> user_input_pass;
		if (user_input_pass == "0") {
			return -1;
		}
		else if (db_account_pass != user_input_pass) {
			cout << "Вы ввели неправильный пароль, попробуйте снова.\n" << endl;
		}
		else {
			cout << "Вы вошли в систему.\n" << endl;
			break;
		}
	}
	
	return sql_db->get_int("LOGIN", login, 3);
}

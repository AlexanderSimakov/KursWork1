#pragma once
#include "authorization.h"


Authorization::Authorization(SQLWork* sql_db) {
	this->sql_db = sql_db;
}

int Authorization::start() {
	cout << "Авторизация. (Для выхода введите в любое из полей 0)" << endl;

	string login, pass_akk, pass_user;

	while (true) {
		cout << "Логин: ";
		cin >> login;
		pass_akk = sql_db->get_text("LOGIN", login, 1);
		if (login == "0") {
			return -1;
		}
		else if (pass_akk == "") {
			cout << "Аккаунта с таким логином не существует, попробуйте снова.\n" << endl;
		}
		else if (sql_db->get_int("LOGIN", login, 4) == 0) {
			cout << "В данный момент использование аккаунта невозможно, так как администратор еще не подтвердил его.\n" << endl;
		}
		else {
			cout << endl;
			break;
		}
	}

	while (true) {
		cout << "Пароль: ";
		cin >> pass_user;
		if (pass_user == "0") {
			return -1;
		}
		else if (pass_akk != pass_user) {
			cout << "Вы ввели неправильный пароль, попробуйте снова.\n" << endl;
		}
		else {
			cout << "Вы вошли в систему.\n" << endl;
			break;
		}
	}
	
	return sql_db->get_int("LOGIN", login, 3);
}

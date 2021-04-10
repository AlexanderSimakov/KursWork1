#include "menu.h"
#include <iostream>
#include "registration.h"
#include "authorization.h"
#include "SQLWORK.h"
#include "account.h"
#include "session.h"
#include "product.h"

using namespace std;

void init_accounts_db(SQLWork *db) {
	db->open();
	db->create({ SQL_cell{ "LOGIN",  "TEXT PRIMARY KEY NOT NULL"},
			   SQL_cell{ "HASH",     "TEXT NOT NULL"},
			   SQL_cell{ "SALT",     "TEXT NOT NULL"},
			   SQL_cell{ "ROLE",     "INT NOT NULL"},
			   SQL_cell{ "ACCESS",   "INT NOT NULL"} }, ACCOUNTS_DATABASE_NAME);
}

void init_product_db(SQLWork* db) {
	db->open();
	db->create({ SQL_cell{ "NAME",   "TEXT PRIMARY KEY NOT NULL"},
			   SQL_cell{ "AMOUNT",   "INT NOT NULL"},
			   SQL_cell{ "PRICE",    "INT NOT NULL"},
			   SQL_cell{ "DATE",     "TEXT NOT NULL"},
			   SQL_cell{ "REG_NAME", "TEXT NOT NULL"} }, PRODUCT_DATABASE_NAME);
}

int main() {
	setlocale(LC_ALL, "rus");

	SQLWork accounts_db(ACCOUNTS_DATABASE_FILENAME);
	SQLWork product_db(PRODUCT_DATABASE_FILENAME);
	init_accounts_db(&accounts_db);
	init_product_db(&product_db);

	Registration registration(&accounts_db);
	Authorization authorization(&accounts_db);
	Session session(&product_db, &accounts_db);
	Menu main_menu(" ---  Главное меню  --- ",
				 { " Авторизация",
				   " Регистрация",
				   " Выход" });

	//accounts_db.push_back({ "'admin'", "'admin'", "'admin'", "1", "1" });



	int choise = 0, role = -1;
	while (true) {
		choise = main_menu.get_choise();
		switch (choise)
		{
		case 0: // Авторизация
			role = authorization.start();
			if (role == 0) { // запуск пользователя
				session.start_as_user();
			}
			else if (role == 1) {//запуск админа
				session.start_as_admin();
			}
			system("pause");
			break;
		case 1: // Регистрация
			registration.start();
			system("pause");
			break;
		case 2: case -1: // Выход
			accounts_db.close();
			product_db.close();
			return 0;
		default:
			break;
		}
	}

	return 0;
}
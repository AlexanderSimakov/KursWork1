#include "menu.h"
#include <iostream>
#include "registration.h"
#include "authorization.h"
#include "SQLWORK.h"
#include "account.h"
#include "session.h"
#include "product.h"
#include "helpFunctions.h"

using namespace std;

void init_accounts_db(SQLWork* db);
void init_product_db(SQLWork* db);


int main() {
	setlocale(LC_ALL, "rus");

	SQLWork accounts_db(ACCOUNTS_DATABASE_FILENAME);
	SQLWork product_db(PRODUCT_DATABASE_FILENAME);
	init_accounts_db(&accounts_db);
	init_product_db(&product_db);

	Registration registration(&accounts_db);
	Authorization authorization(&accounts_db);
	Session session(&product_db, &accounts_db);

	Menu main_menu("<- ������� ���� ->",
				 { " �����������",
				   " �����������",
				   " �����" });
	main_menu.set_start_with_first_line(true);


	int choise = 0, role = -1;
	while (true) {
		choise = main_menu.get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // �����������
			role = authorization.start();
			if (role == 0) { // ������ ������������
				session.start_as_user(authorization.get_login());
			}
			else if (role == 1) {//������ ��������������
				session.start_as_admin(authorization.get_login());
			}
			break;
		case 1: // �����������
			registration.start();
			break;
		case 2: case -1: // �����
			accounts_db.close();
			product_db.close();
			return 0;
		default:
			break;
		}
	}

	return 0;
}


// ��������� � �������������� ���� ������ ���������, ���� ��� �� ����������������� �� �����
void init_accounts_db(SQLWork* db) {
	db->open();
	db->create_table_if_not_exists({ SQL_cell{ "LOGIN",  "TEXT PRIMARY KEY NOT NULL"},
				 SQL_cell{ "HASH",   "TEXT NOT NULL"},
				 SQL_cell{ "SALT",   "TEXT NOT NULL"},
				 SQL_cell{ "ROLE",   "INT NOT NULL"},
				 SQL_cell{ "ACCESS", "INT NOT NULL"} },
		ACCOUNTS_DATABASE_NAME);
}

// ��������� � �������������� ���� ������ ���������, ���� ��� �� ����������������� �� �����
void init_product_db(SQLWork* db) {
	db->open();
	db->create_table_if_not_exists({ SQL_cell{ "NAME",     "TEXT PRIMARY KEY NOT NULL"},
				 SQL_cell{ "AMOUNT",   "INT NOT NULL"},
				 SQL_cell{ "PRICE",    "INT NOT NULL"},
				 SQL_cell{ "DATE",     "TEXT NOT NULL"},
				 SQL_cell{ "REG_NAME", "TEXT NOT NULL"} },
		PRODUCT_DATABASE_NAME);
}


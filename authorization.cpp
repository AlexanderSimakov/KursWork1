#pragma once
#include "authorization.h"


Authorization::Authorization(SQLWork* sql_db) {
	this->sql_db = sql_db;
}

int Authorization::start() {
	cout << "�����������. (��� ������ ������� � ����� �� ����� 0)" << endl;

	string login, pass_akk, pass_user;

	while (true) {
		cout << "�����: ";
		cin >> login;
		pass_akk = sql_db->get_text("LOGIN", login, 1);
		if (login == "0") {
			return -1;
		}
		else if (pass_akk == "") {
			cout << "�������� � ����� ������� �� ����������, ���������� �����.\n" << endl;
		}
		else if (sql_db->get_int("LOGIN", login, 4) == 0) {
			cout << "� ������ ������ ������������� �������� ����������, ��� ��� ������������� ��� �� ���������� ���.\n" << endl;
		}
		else {
			cout << endl;
			break;
		}
	}

	while (true) {
		cout << "������: ";
		cin >> pass_user;
		if (pass_user == "0") {
			return -1;
		}
		else if (pass_akk != pass_user) {
			cout << "�� ����� ������������ ������, ���������� �����.\n" << endl;
		}
		else {
			cout << "�� ����� � �������.\n" << endl;
			break;
		}
	}
	
	return sql_db->get_int("LOGIN", login, 3);
}

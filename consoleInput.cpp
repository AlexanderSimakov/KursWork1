#pragma once
#include "consoleInput.h"



string console::get_login(SQLWork* db) {
	string login, user_pass;
	while (true) {
		cout << "������: ";
		cin >> login;
		user_pass = db->get_text("LOGIN", login, 1);

		if (login == "0") { // 0 - ��� ������
			return "0";
		}
		else if (login.size() < 4) {
			cout << "<-- ������� ��������� �����, ���������� ����� -->\n" << endl;
		}
		else if (!console::is_login_symbols_ok(login)) {
			cout << "<-- ����� �������� ������������ �������, ���������� ����� -->\n" << endl;
		}
		else if (user_pass == "") {
			cout << "�������� � ����� ������� �� ����������, ���������� �����.\n" << endl;
		}
		else if (db->get_int("LOGIN", login, 4) == 0) {
			cout << "� ������ ������ ������������� �������� ����������, ��� ��� ������������� ��� �� ���������� ���.\n" << endl;
		}
		else {
			return login;
		}
	}
}

bool console::is_login_symbols_ok(string login) {
	int ch;
	for (int ch = 0, i = 0; i < login.size(); i++) {
		ch = (int)login[i];
		if (ch < 48 || ch > 57 && ch < 65 || ch > 90 && ch < 97 || ch > 122) {
			return false;
		}
	}
	return true;
}





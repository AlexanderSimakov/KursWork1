#pragma once
#include "registration.h"

Registration::Registration(SQLWork *sql_db) {
	this->sql_db = sql_db;
}

void Registration::start() {
	cout << "����������� ������ ������������. (��� ������ ������� 0 � ����� �� �����)" << endl;

	cout << "�����: ";
	cin >> account.login;
	cout << "������: ";
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
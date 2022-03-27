#pragma once
#include "session.h"

void Session::find_products_by_name() {
	ConsoleOut::show_title("Find product by name", "\t", "\n\n");
	
	cout << "Name\n>";
	string name;
	getline(cin, name);
	if (name == "0") return;

	cout << endl;
	productsdb->find_by_name(name);
}

void Session::find_products_by_name_of_registrant() {
	ConsoleOut::show_title("Find by registrant name", "\t", "\n\n");

	cout << "Name\n>";
	string name;
	getline(cin, name);
	if (name == "0") return;

	cout << endl;
	productsdb->find_by_registrant(name);
}

void Session::find_products_by_date() {
	string date;
	ConsoleOut::show_title("Find by date", "\t", "\n\n");

	cout << "(*-12-05, 2021-*-*, 2022-11-01)" << endl;
	cout << "Date: ";
	cin >> date;
	cin.ignore(256, '\n');
	if (date == "0") return;

	cout << endl;
	productsdb->find_by_date(date);
}

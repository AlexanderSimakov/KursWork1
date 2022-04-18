#pragma once
#include "session.hpp"

void Session::find_products_by_name() 
{
	ConsoleOut::show_title("Find products by name", "\t", "\n\n");
	
	cout << "Name: ";
	string name;
	getline(cin, name);

	if (name != "0")
	{
		cout << endl;
		products_db->find_by_name(name);
	}
}

void Session::find_products_by_registrant() 
{
	ConsoleOut::show_title("Find by registrant", "\t", "\n\n");

	cout << "Name: ";
	string name;
	getline(cin, name);
	
	if (name != "0")
	{
		cout << endl;
		products_db->find_by_registrant(name);
	}
}

void Session::find_products_by_date() 
{
	ConsoleOut::show_title("Find by date", "\t", "\n\n");
	string date;

	cout << "(*-12-05, 2021-*-*, 2022-11-01)\nDate: ";
	cin >> date;
	cin.ignore(256, '\n');

	if (date != "0")
	{
		cout << endl;
		products_db->find_by_date(date);
	}
}

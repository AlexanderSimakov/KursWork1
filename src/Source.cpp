#include <iostream>
#include "menu/menu.h"
#include "manage/registration.h"
#include "manage/authorization.h"
#include "manage/session.h"
#include "sqlwork/AccountsDB/AccountsDB.h"
#include "sqlwork/ProductsDB/ProductsDB.h"
#include "menu/factory/MenuFactory.h"

using namespace std;


int main() {
	AccountsDB accountsDB;
	ProductsDB productsDB;
	accountsDB.init();
	productsDB.init();

	Session session(&productsDB, &accountsDB);
	Account* account;
	Menu* main_menu = MenuFactory::create_main_menu();

	int choise = 0, role = -1;
	while (true) {
		choise = main_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: 
			account = Authorization::start(&accountsDB);
			if (!account->is_empty()) session.start(account);
			break;
		case 1:
			Registration::start(&accountsDB);
			break;
		case 2: case -1:
			accountsDB.db->close();
			productsDB.db->close();
			return 0;
		default:
			break;
		}
	}

	return 0;
}

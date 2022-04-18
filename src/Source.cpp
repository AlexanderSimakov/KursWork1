#include <iostream>
#include "menu/menu.hpp"
#include "manage/Registration/registration.hpp"
#include "manage//Authorization/authorization.hpp"
#include "manage/AdminSession/AdminSession.hpp"
#include "manage/UserSession/UserSession.hpp"
#include "sqlwork/AccountsDB/AccountsDB.hpp"
#include "sqlwork/ProductsDB/ProductsDB.hpp"
#include "menu/factory/MenuFactory.hpp"

using namespace std;


int main() {
	AccountsDB accountsDB;
	ProductsDB productsDB;
	accountsDB.init();
	productsDB.init();

	AdminSession admin_session(&accountsDB, &productsDB);
	UserSession user_session(&productsDB);
	Account* account;
	Menu* main_menu = MenuFactory::create_main_menu();

	int choise = 0, role = -1;
	while (true) 
	{
		choise = main_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: 
			account = Authorization::start(&accountsDB);
			if (account->get_role() == Role::ADMIN) admin_session.start(account);
			else if (account->get_role() == Role::USER) user_session.start();
			break;
		case 1:
			Registration::start(&accountsDB);
			break;
		case 2: case -1:
			accountsDB.close();
			productsDB.close();
			return 0;
		default:
			break;
		}
	}

	return 0;
}

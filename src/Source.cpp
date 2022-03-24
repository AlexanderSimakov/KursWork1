#include <iostream>
#include "menu/menu.h"
#include "manage/registration.h"
#include "manage/authorization.h"
#include "manage/session.h"
#include "sqlwork/SQLWORK.h"
#include "sqlwork/AccountsDB.h"
#include "sqlwork/ProductsDB.h"
#include "basic/Account.h"
#include "basic/product.h"
#include "basic/helpFunctions.h"

using namespace std;


int main() {
	AccountsDB a;
	ProductsDB productsDB;
	a.init();
	productsDB.init();

	Registration registration(a.db);
	Authorization authorization(a.db);
	Session session(productsDB.db, a.db);

	Menu main_menu("<- Main menu ->",
				 { " Log in",
				   " Create account",
				   " Exit" });
	main_menu.set_start_with_first_line(true);


	int choise = 0, role = -1;
	while (true) {
		choise = main_menu.get_num_of_choisen_line();
		switch (choise)
		{
		case 0: 
			role = authorization.start();
			if (role == 0) { 
				session.start_as_user(authorization.get_login());
			}
			else if (role == 1) {
				session.start_as_admin(authorization.get_login());
			}
			break;
		case 1:
			registration.start();
			break;
		case 2: case -1:
			a.db->close();
			productsDB.db->close();
			return 0;
		default:
			break;
		}
	}

	return 0;
}

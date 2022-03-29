#include "UserSession.h"

UserSession::UserSession(ProductsDB* productsDB){
    this->products_db = productsDB;
    user_menu = MenuFactory::create_user_menu();
}

void UserSession::start(){
    while (true) 
	{
		switch (user_menu->get_num_of_choisen_line())
		{
		case 0: products_db->show_table(); ConsoleOut::pause(); break;
		case 1: find_products_by_name(); break;
		case 2: find_products_by_name_of_registrant(); break;
		case 3: find_products_by_date(); break;
		case 4: products_db->show_sorted_by_name(); break;
		case 5: products_db->show_sorted_by_price_to_higher(); break;
		case 6: products_db->show_sorted_by_amount_to_higher(); break;
		case 7: case -1:
			if (ConfirmationMenu::confirm()) 
			{
				user_menu->set_pointer_to_start();
				return;
			}
		default: break;
		}
	}
}

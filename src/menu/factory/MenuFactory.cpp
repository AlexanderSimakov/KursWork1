#include "MenuFactory.h"

Menu* MenuFactory::create_main_menu(){
	Menu* menu = new Menu("<- Main menu ->",
				 { " Log in",
				   " Create account",
				   " Exit" });
	menu->set_start_with_first_line(true);
	return menu;
}

Menu* MenuFactory::create_admin_menu(){
    Menu* menu = new Menu("<- Admin menu ->",
		{ " Accounts",
		  " Products",
		  " Log Out" });
	menu->set_start_with_first_line(true);
    return menu;
}

Menu* MenuFactory::create_accounts_manage_menu(){
    return new Menu("<- Accounts ->",
		{ " Show",
		  " Add new",
		  " Edit",
		  " Delete",
		  " Confirm",
		  " Block",
		  " Exit" }); 
}

Menu* MenuFactory::create_products_manage_menu(){
    return new Menu("<- Products ->",
		{ " Show",
		  " Add",
		  " Delete",
		  " Edit",
		  " Find by name",
		  " Find by name of registrant",
		  " Find by date",
		  " Sort by name",
		  " Sort by price (to higher)",
		  " Sort by amount (to higher)",
		  " Exit" });
}

Menu* MenuFactory::create_user_menu(){
    return new Menu("<- Products ->",
		{ " Show",
		  " Find by name",
		  " Find by registrant name",
		  " Find by date",
		  " Sort by name",
		  " Sort by price (to higher)",
		  " Sort by amount (to higher)",
		  " Log out" });
}

Menu* MenuFactory::create_account_edit_menu(){
    Menu* menu = new Menu({ " login", " password", " role", " exit" });
	menu->set_start_with_first_line(true);
    return menu;
}

Menu* MenuFactory::create_product_edit_menu(){
    Menu* menu = new Menu({ " Name", " Amount", " Price", " Date", " Registrant", " Exit" });
	menu->set_start_with_first_line(true);
    return menu;
}
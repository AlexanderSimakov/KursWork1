#include "AdminSession.h"

AdminSession::AdminSession(AccountsDB* accountsDB, ProductsDB* productsDB){
    this->productsdb = productsDB;
	this->accountsDB = accountsDB;
    {
    	admin_menu = MenuFactory::create_admin_menu();
	    accounts_manage_menu = MenuFactory::create_accounts_manage_menu();
    	products_manage_menu = MenuFactory::create_products_manage_menu();
	    account_edit_menu = MenuFactory::create_account_edit_menu();
	    product_edit_menu = MenuFactory::create_product_edit_menu();
	    user_menu = MenuFactory::create_user_menu();
    }
}

void AdminSession::start(Account* account){
    session_account = account;
    while (true) 
	{
		switch (admin_menu->get_num_of_choisen_line())
		{
		case 0: start_accounts_managing(); break;
		case 1: start_products_managing(); break;
		case 2: case -1: if (ConfirmationMenu::confirm()) return;
		default: break;
		}
	} 
}

void AdminSession::start_accounts_managing(){
    while (true) 
	{
		switch (accounts_manage_menu->get_num_of_choisen_line())
		{
		case 0: accountsDB->show_table(); ConsoleOut::pause(); break;
		case 1: add_new_account(); break;
		case 2: start_account_editing(); break;
		case 3: delete_account(); break;
		case 4: confirm_account(); break;
		case 5: block_account(); break;
		case 6:	case -1: accounts_manage_menu->set_pointer_to_start(); return;
		default: break;
		}
	}
}

void AdminSession::start_products_managing(){
    while (true) 
	{
		switch (products_manage_menu->get_num_of_choisen_line())
		{
		case 0: productsdb->show_table(); ConsoleOut::pause(); break;
		case 1: add_new_product(); break;
		case 2: delete_product(); break;
		case 3: start_product_editing(); break;
		case 4: find_products_by_name(); break;
		case 5: find_products_by_name_of_registrant(); break;
		case 6: find_products_by_date(); break;
		case 7: productsdb->show_sorted_by_name(); break;
		case 8: productsdb->show_sorted_by_price_to_higher(); break;
		case 9: productsdb->show_sorted_by_amount_to_higher(); break;
		case 10: case -1: products_manage_menu->set_pointer_to_start(); return;
		default: break;
		}
	}
}

void AdminSession::add_new_account(){
    Account account;
	ConsoleOut::show_title("Add new account");

	account.set_login(ConsoleInp::get_free_login(accountsDB));
	if (account.get_login() == "0") return;

	string pass = ConsoleInp::password_format_input();
	if (pass == "0") return;

	account.set_role((Role)ConsoleInp::get_number_from_range(0, 1, "Role(0|1): "));


	if (ConfirmationMenu::confirm()) {
		account.set_access(Access::YES);
		account.set_salt(Account::get_generated_salt());
		account.set_hash(Account::get_generated_hash(pass, account.get_salt()));

		accountsDB->add_new(account);

		ConsoleOut::show_info("Account was created", "\t", "\n\n");
	}
	else {
		ConsoleOut::show_info("Account was't created", "\t", "\n\n");
	}
	ConsoleOut::pause();
} 

void AdminSession::delete_account(){
    ConsoleOut::show_title("Delete account", "", "\n\n");
	accountsDB->show_table();

	string login = ConsoleInp::get_exists_login(accountsDB);

	if (login == "0") return;
	else if (login == session_account->get_login()) {
		ConsoleOut::show_error("You cannot delete your account", "\t", "\n");
	}
	else if (ConfirmationMenu::confirm()) {
		accountsDB->_delete(login);
		ConsoleOut::show_info("Account '" + login + "' was deleted", "\t", "\n\n");
	}
	else {
		ConsoleOut::show_info("Account was't deleted", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void AdminSession::confirm_account(){
    ConsoleOut::show_title("Confirm account", "", "\n\n");
	accountsDB->show_table();

	string login = ConsoleInp::get_exists_login(accountsDB);

	if (login == "0") return;
	else if (login == session_account->get_login()) {
		ConsoleOut::show_error("You cannot confirm your account", "\n\t", "\n\n");
	}
	else if (accountsDB->is_have_access(login)) {
		ConsoleOut::show_info("Account already confirmed", "\n\t", "\n\n");
	}
	else {
		accountsDB->confirm(login);
		ConsoleOut::show_info("Account '" + login + "' was confirmed", "\n\t", "\n\n");
	}
	ConsoleOut::pause();   
}

void AdminSession::block_account(){
    ConsoleOut::show_title("Block account", "", "\n\n");
	accountsDB->show_table();

	string login = ConsoleInp::get_exists_login(accountsDB);

	if (login == "0") return;
	else if (login == session_account->get_login()) {
		ConsoleOut::show_error("You cannot block your account", "\n\t", "\n\n");
	}
	else if (!accountsDB->is_have_access(login)) {
		ConsoleOut::show_info("Account already blocked", "\n\t", "\n\n");
	}
	else {
		accountsDB->block(login);
		ConsoleOut::show_info("Account '" + login + "' was blocked", "\n\t", "\n\n");
	}
	ConsoleOut::pause();
}

void AdminSession::start_account_editing(){
    ConsoleOut::show_title("Edit account");
	
	string login = ConsoleInp::get_exists_login(accountsDB);
	if (login == "0") return;

	account_edit_menu->set_title("<- Editing '" + login + "' ->");
	while (true) 
	{
		switch (account_edit_menu->get_num_of_choisen_line())
		{
		case 0: 
			edit_account_login(&login);
			account_edit_menu->set_title("<- Editing '" + login + "' ->");
			break;
		case 1: edit_account_password(login); break;
		case 2: edit_account_role(login); break;
		case 3: case -1: return;
		default: break;
		}
	}
} 

void AdminSession::edit_account_login(string *login){
	ConsoleOut::show_title("Edit login", "\t", "\n\n");
	cout << "Old login: " << *login << endl;
	string new_login = ConsoleInp::get_free_login(accountsDB);

	if (new_login == "0") return;
	else if (ConfirmationMenu::confirm()) {
		accountsDB->update_login(*login, new_login);
		*login = new_login;
		ConsoleOut::show_info("Login was changed", "\t", "\n\n");
	}
	else {
		ConsoleOut::show_info("Login was't changed", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void AdminSession::edit_account_password(string login){
    ConsoleOut::show_title("Edit password", "\t", "\n\n");
	string pass = ConsoleInp::password_format_input();

	if (pass == "0") return;
	else if (ConfirmationMenu::confirm()) {
		accountsDB->update_password(login, pass);
		ConsoleOut::show_info("Password was changed", "\t", "\n\n");
	}
	else {
		ConsoleOut::show_info("Password was't changed", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void AdminSession::edit_account_role(string login){
    if (login != session_account->get_login()) {
		ConsoleOut::show_title("Edit role", "\t", "\n\n");
		int new_role = ConsoleInp::get_number_from_range(-1, 1, "Role: ");

		if (new_role == -1) return;
		else if (ConfirmationMenu::confirm()) {
			accountsDB->update_role(login, new_role);
			ConsoleOut::show_info("Role was changed", "\t", "\n\n");
		}
		else {
			ConsoleOut::show_info("Role was't changed", "\t", "\n\n");
		}
	}
	else {
		ConsoleOut::show_error("You cannot edit your role", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void AdminSession::add_new_product(){
    Product product;
	ConsoleOut::show_title("Add new product");

	product.set_name(ConsoleInp::get_non_existent_product_name(productsdb));
	if (product.get_name() == "0") return;

	product.set_amount(ConsoleInp::get_number(true, "Amount: "));
	if (product.get_amount() == 0) return;

	product.set_price(ConsoleInp::get_number(true, "Price: "));
	if (product.get_price() == 0) return;

	cout << "Date (yyyy-mm-dd): ";
	product.set_date(ConsoleInp::get_format_date());
	if (product.get_date() == "0") return;

	cout << "Name of registrant: ";
	string registrant;
	getline(cin, registrant);
	product.set_registrant(registrant);
	if (product.get_registrant() == "0") return;

	productsdb->add_new(product);

	ConsoleOut::show_info("Product was added", "\n\t", "\n\n");
	ConsoleOut::pause();
}

void AdminSession::delete_product(){
    ConsoleOut::show_title("Delete product", "", "\n\n");
	productsdb->show_table();

	string name = ConsoleInp::get_exists_product_name(productsdb);

	if (name == "0") return;
	else if (ConfirmationMenu::confirm()) {
		productsdb->_delete(name);
		ConsoleOut::show_info("Product was deleted", "\t", "\n\n");
	}
	else {
		ConsoleOut::show_info("Product was't deleted", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void AdminSession::start_product_editing(){
    ConsoleOut::show_title("Edit product munu");

	string name = ConsoleInp::get_exists_product_name(productsdb);
	if (name == "0") return;

	product_edit_menu->set_title("<- Editing: " + name + " ->");
	while (true) 
	{
		switch (product_edit_menu->get_num_of_choisen_line())
		{
		case 0: 
			edit_product_name(&name);
			product_edit_menu->set_title("<- Editing: " + name + " ->");
			break;
		case 1: edit_product_amount(name); break;
		case 2: edit_product_price(name); break;
		case 3: edit_product_date(name); break;
		case 4: edit_product_registrant(name); break;
		case 5: case -1: return;
		default: break;
		}
	}
} 

void AdminSession::edit_product_name(string *name){
    ConsoleOut::show_title("Edit product name", "\t", "\n\n");
	
	cout << "Old name: " << *name << endl;
	string new_name = ConsoleInp::get_non_existent_product_name(productsdb);

	if (new_name == "0") return;
	else if (ConfirmationMenu::confirm()) {
		productsdb->update_name(*name, new_name);
		*name = new_name;
		ConsoleOut::show_info("Product was renamed", "\t", "\n\n");
	}
	else {
		ConsoleOut::show_info("Product was't renamed", "\t", "\n\n");
	}
	ConsoleOut::pause();
} 

void AdminSession::edit_product_amount(string name){
    ConsoleOut::show_title("Edit amount", "\t", "\n\n");

	cout << "Old amount: " << productsdb->get_amount(name) << endl;
	int amount = ConsoleInp::get_number(true, "New amount: ");

	if (amount == 0) return;
	else {
		productsdb->update_amount(name, amount);
		ConsoleOut::show_info("Amount was updated", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void AdminSession::edit_product_price(string name){
    ConsoleOut::show_title("Edit product price", "\t", "\n\n");
	
	cout << "Old price: " << productsdb->get_price(name) << endl;
	int price = ConsoleInp::get_number(true, "New price: ");

	if (price == 0) return;
	else {
		productsdb->update_price(name, price);
		ConsoleOut::show_info("Price was updated", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void AdminSession::edit_product_date(string name){
    ConsoleOut::show_title("Edit date", "\t", "\n\n");

	cout << "Old date: " << productsdb->get_date(name) << endl;
	string date = ConsoleInp::get_format_date();

	if (date == "0") return;
	else {
		productsdb->update_date(name, date);
		ConsoleOut::show_info("Date was updated", "\t", "\n\n");
	}
	ConsoleOut::pause();
} 

void AdminSession::edit_product_registrant(string name){
    ConsoleOut::show_title("Edit registrant name", "\t", "\n\n");

	cout << "Old name: " << productsdb->get_registrant(name) << endl;
	cout << "New name: ";
	string reg_name;
	getline(cin, reg_name);

	if (reg_name == "0") return;
	else {
		productsdb->update_registrant(name, reg_name);
		ConsoleOut::show_info("Name was updated", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

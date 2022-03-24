#pragma once
#include "session.h"


Session::Session(SQLWork* product_db, SQLWork* account_db) {
	this->product_db = product_db;
	this->account_db = account_db;
	accountsdb = AccountsDB(account_db);
	productsdb = ProductsDB(product_db);
	init_admin_menu();
	init_user_menu();
	init_confirm_operation_menu();
}

void Session::init_admin_menu() {
	admin_menu = new Menu("<- Admin menu ->",
		{ " Accounts",
		  " Products",
		  " Log Out" });
	admin_menu->set_start_with_first_line(true);

	accounts_manage_menu = new Menu("<- Accounts ->",
		{ " Show",
		  " Add new",
		  " Edit",
		  " Delete",
		  " Confirm",
		  " Block",
		  " Exit" });

	products_manage_menu = new Menu("<- Products ->",
		{ " Show",
		  " Add",
		  " Delete",
		  " Edit",
		  " Individual task",
		  " Find by name",
		  " Find by name of registrant",
		  " Find by date",
		  " Sort by name",
		  " Sort by price (to higher)",
		  " Sort by amount (to higher)",
		  " Exit" });

	account_edit_menu = new Menu({ " login", " password", " role", " exit" });
	account_edit_menu->set_start_with_first_line(true);

	product_edit_menu = new Menu({ " Name", " Amount", " Price", " Date", " Registrant", " Exit" });
	product_edit_menu->set_start_with_first_line(true);
}

void Session::init_user_menu() {
	user_menu = new Menu("<- Products ->",
		{ " Show",
		  " Individual task",
		  " Find by name",
		  " Find by registrant name",
		  " Find by date",
		  " Sort by name",
		  " Sort by price (to higher)",
		  " Sort by amount (to higher)",
		  " Log out" });
}

void Session::init_confirm_operation_menu() {
	confirm_operation_menu = new Menu({ " Yes", " No" });
	confirm_operation_menu->set_start_with_first_line(true);
}

void Session::start_as_user(string login) {
	this->session_account_login = login;
	int choise = 0;
	while (true) {
		choise = user_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0:
		 	productsdb.show_table();
			ConsoleOut::pause();
			break;
		case 1:
			individual_task();
			break;
		case 2:
			find_products_by_name();
			break;
		case 3:
			find_products_by_name_of_registrant();
			break;
		case 4:
			find_products_by_date();
			break;
		case 5:
		 	productsdb.show_sorted_by_name();
			break;
		case 6:
		 	productsdb.show_sorted_by_price_to_higher();
			break;
		case 7:
			productsdb.show_sorted_by_amount_to_higher();
			break;
		case 8: case -1:
			if (confirm_menu_start("Are you sure?")) {
				user_menu->set_pointer_to_start();
				return;
			}
			break;

		default:
			break;
		}
	}
}

void Session::start_as_admin(string login) {
	this->session_account_login = login;
	int choise = 0;
	while (true) {
		choise = admin_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0:
			admin_manage_accounts_start();
			break;
		case 1:
			admin_manage_products_start();
			break;
		case 2: case -1:
			if (confirm_menu_start("<- Are you sure? ->")) {
				return;
			}
			break;
		default:
			break;
		}
	}
}

bool Session::confirm_menu_start(string title) {
	confirm_operation_menu->set_title(title);
	int choise = 0;
	while (true) {
		choise = confirm_operation_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // yes 
			return true;
		case 1: // No 
			return false;
		case -1: default:
			break;
		}
	}
}

void Session::admin_manage_accounts_start() {
	int choise = 0;
	while (true) {
		choise = accounts_manage_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: 
			accountsdb.show_table();
			ConsoleOut::pause();
			break;
		case 1: 
			add_new_account();
			break;
		case 2:  
			start_edit_account_menu();
			break;
		case 3: 
			delete_account();
			break;
		case 4: 
			confirm_account();
			break;
		case 5: 
			block_account();
			break;
		case 6:	case -1: 
			accounts_manage_menu->set_pointer_to_start();
			return;
			break;
		default:
			break;
		}
	}
}

void Session::add_new_account() {
	Account account;
	ConsoleOut::show_title("Add new account");

	account.set_login(console::get_free_login(account_db, "Login: "));
	if (account.get_login() == "0") return;

	string pass = console::password_format_input("Password: ");
	if (pass == "0") return;

	account.set_role((Role)console::get_number_from_range(0, 1, "Role(0|1): "));


	if (confirm_menu_start("<- Are you sure? ->")) {
		account.set_access(Access::YES);
		account.set_salt(Account::get_generated_salt());
		account.set_hash(Account::get_generated_hash(pass, account.get_salt()));

		accountsdb.add_new(account);

		ConsoleOut::show_info("Account was created", "\t", "\n\n");
	}
	else {
		ConsoleOut::show_info("Account was't created", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void Session::start_edit_account_menu() {
	ConsoleOut::show_title("Edit account");
	
	string login = console::get_exists_login(account_db);
	if (login == "0") return;

	account_edit_menu->set_title("<- Editing '" + login + "' ->");
	int choise = 0;
	while (true) {
		choise = account_edit_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: 
			edit_account_login(&login);
			account_edit_menu->set_title("<- Editing '" + login + "' ->");
			break;
		case 1: 
			edit_account_password(login);
			break;
		case 2:  
			edit_account_role(login);
			break;
		case 3: case -1: 
			return;
			break;

		default:
			break;
		}
	}
}

void Session::edit_account_login(string* login) {
	ConsoleOut::show_title("Edit login", "\t", "\n\n");
	cout << "Old login: " << *login << endl;
	string new_login = console::get_free_login(account_db, "New login: ");

	if (new_login == "0") return;
	else if (confirm_menu_start("<- Are you sure? ->")) {
		accountsdb.update_login(*login, new_login);
		*login = new_login;
		ConsoleOut::show_info("Login was changed", "\t", "\n\n");
	}
	else {
		ConsoleOut::show_info("Login was't changed", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void Session::edit_account_password(string login) {
	ConsoleOut::show_title("Edit password", "\t", "\n\n");
	string pass = console::password_format_input("Password: ");

	if (pass == "0") return;
	else if (confirm_menu_start("<- Are you sure? ->")) {
		accountsdb.update_password(login, pass);
		ConsoleOut::show_info("Password was changed", "\t", "\n\n");
	}
	else {
		ConsoleOut::show_info("Password was't changed", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void Session::edit_account_role(string login) {
	if (login != session_account_login) {
		ConsoleOut::show_title("Edit role", "\t", "\n\n");
		int new_role = console::get_number_from_range(-1, 1, "Role: ");

		if (new_role == -1) return;
		else if (confirm_menu_start("<- Are you sure? ->")) {
			accountsdb.update_role(login, new_role);
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

void Session::delete_account() {
	ConsoleOut::show_title("Delete account", "", "\n\n");
	accountsdb.show_table();

	string login = console::get_exists_login(account_db);

	if (login == "0") return;
	else if (login == session_account_login) {
		ConsoleOut::show_error("You cannot delete your account", "\t", "\n");
	}
	else if (confirm_menu_start("<- Are you sure? ->")) {
		accountsdb._delete(login);
		ConsoleOut::show_info("Account '" + login + "' was deleted", "\t", "\n\n");
	}
	else {
		ConsoleOut::show_info("Account was't deleted", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void Session::confirm_account() {
	ConsoleOut::show_title("Confirm account", "", "\n\n");
	accountsdb.show_table();

	string login = console::get_exists_login(account_db);

	if (login == "0") return;
	else if (login == session_account_login) {
		ConsoleOut::show_error("You cannot confirm your account", "\n\t", "\n\n");
	}
	else if (accountsdb.is_have_access(login)) {
		ConsoleOut::show_info("Account already confirmed", "\n\t", "\n\n");
	}
	else {
		accountsdb.confirm(login);
		ConsoleOut::show_info("Account '" + login + "' was confirmed", "\n\t", "\n\n");
	}
	ConsoleOut::pause();
}

void Session::block_account() {
	ConsoleOut::show_title("Block account", "", "\n\n");
	accountsdb.show_table();

	string login = console::get_exists_login(account_db);

	if (login == "0") return;
	else if (login == session_account_login) {
		ConsoleOut::show_error("You cannot block your account", "\n\t", "\n\n");
	}
	else if (!accountsdb.is_have_access(login)) {
		ConsoleOut::show_info("Account already blocked", "\n\t", "\n\n");
	}
	else {
		accountsdb.block(login);
		ConsoleOut::show_info("Account '" + login + "' was blocked", "\n\t", "\n\n");
	}
	ConsoleOut::pause();
}

void Session::admin_manage_products_start() {
	int choise = 0;
	while (true) {
		choise = products_manage_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0:
		 	productsdb.show_table();
			ConsoleOut::pause();
			break;
		case 1:
			add_new_product();
			break;
		case 2:
			delete_product();
			break;
		case 3:
			start_edit_product_menu();
			break;
		case 4:
			individual_task();
			break;
		case 5:
			find_products_by_name();
			break;
		case 6:
			find_products_by_name_of_registrant();
			break;
		case 7:
			find_products_by_date();
			break;
		case 8:
		 	productsdb.show_sorted_by_name();
			break;
		case 9:
		 	productsdb.show_sorted_by_price_to_higher();
			break;
		case 10:
		 	productsdb.show_sorted_by_amount_to_higher();
			break;
		case 11: case -1:
			products_manage_menu->set_pointer_to_start();
			return;
			break;
		default:
			break;
		}
	}
}

void Session::add_new_product() {
	Product product;
	ConsoleOut::show_title("Add new product");

	product.set_name(console::get_non_existent_product_name(product_db));
	if (product.get_name() == "0") return;

	product.set_amount(console::get_number(true, "Amount: "));
	if (product.get_amount() == 0) return;

	product.set_price(console::get_number(true, "Price: "));
	if (product.get_price() == 0) return;

	cout << "Date (yyyy-mm-dd): ";
	product.set_date(console::get_format_date());
	if (product.get_date() == "0") return;

	cout << "Name of registrant: ";
	string registrant;
	getline(cin, registrant);
	product.set_registrant(registrant);
	if (product.get_registrant() == "0") return;

	productsdb.add_new(product);

	ConsoleOut::show_info("Product was added", "\n\t", "\n\n");
	ConsoleOut::pause();
}

void Session::delete_product() {
	ConsoleOut::show_title("Delete product", "", "\n\n");
	productsdb.show_table();

	string name = console::get_exists_product_name(product_db);

	if (name == "0") return;
	else if (confirm_menu_start("<- Are you sure? ->")) {
		productsdb._delete(name);
		ConsoleOut::show_info("Product was deleted", "\t", "\n\n");
	}
	else {
		ConsoleOut::show_info("Product was't deleted", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void Session::start_edit_product_menu() {
	ConsoleOut::show_title("Edit product munu");

	string name = console::get_exists_product_name(product_db);
	if (name == "0") return;

	product_edit_menu->set_title("<- Editing: " + name + " ->");
	int choise = 0;
	while (true) {
		choise = product_edit_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0:
			edit_product_name(&name);
			product_edit_menu->set_title("<- Editing: " + name + " ->");
			break;
		case 1:
			edit_product_amount(name);
			break;
		case 2:
			edit_product_price(name);
			break;
		case 3:
			edit_product_date(name);
			break;
		case 4:
			edit_name_of_product_registrant(name);
			break;
		case 5: case -1:
			return;
			break;

		default:
			break;
		}
	}

}

void Session::edit_product_name(string* name) {
	ConsoleOut::show_title("Edit product name", "\t", "\n\n");
	
	cout << "Old name: " << *name << endl;
	string new_name = console::get_non_existent_product_name(product_db, "New name: ");

	if (new_name == "0") return;
	else if (confirm_menu_start("Are you sure ?")) {
		productsdb.update_name(*name, new_name);
		*name = new_name;
		ConsoleOut::show_info("Product was renamed", "\t", "\n\n");
	}
	else {
		ConsoleOut::show_info("Product was't renamed", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void Session::edit_product_amount(string name) {
	ConsoleOut::show_title("Edit amount", "\t", "\n\n");

	cout << "Old amount: " << product_db->get_int("NAME", name, 1) << endl;
	int amount = console::get_number(true, "New amount: ");

	if (amount == 0) return;
	else {
		productsdb.update_amount(name, amount);
		ConsoleOut::show_info("Amount was updated", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void Session::edit_product_price(string name) {
	ConsoleOut::show_title("Edit product price", "\t", "\n\n");
	
	cout << "Old price: " << product_db->get_int("NAME", name, 2) << endl;
	int price = console::get_number(true, "New price: ");

	if (price == 0) return;
	else {
		productsdb.update_price(name, price);
		ConsoleOut::show_info("Price was updated", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void Session::edit_product_date(string name) {
	ConsoleOut::show_title("Edit date", "\t", "\n\n");

	cout << "Old date: " << product_db->get_text("NAME", name, 3) << endl;
	string date = console::get_format_date("New date: ");

	if (date == "0") return;
	else {
		productsdb.update_date(name, date);
		ConsoleOut::show_info("Date was updated", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void Session::edit_name_of_product_registrant(string name) {
	ConsoleOut::show_title("Edit registrant name", "\t", "\n\n");

	cout << "Old name: " << product_db->get_text("NAME", name, 4) << endl;
	cout << "New name: ";
	string reg_name;
	getline(cin, reg_name);

	if (reg_name == "0") return;
	else {
		productsdb.update_registrant(name, reg_name);
		ConsoleOut::show_info("Name was updated", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void Session::individual_task() {

}

void Session::find_products_by_name() {
	ConsoleOut::show_title("Find product by name", "\t", "\n\n");
	
	cout << "Name\n>";
	string name;
	getline(cin, name);
	if (name == "0") return;

	cout << endl;
	productsdb.find_by_name(name);
}

void Session::find_products_by_name_of_registrant() {
	ConsoleOut::show_title("Find by registrant name", "\t", "\n\n");

	cout << "Name\n>";
	string name;
	getline(cin, name);
	if (name == "0") return;

	cout << endl;
	productsdb.find_by_registrant(name);
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
	productsdb.find_by_date(date);
}

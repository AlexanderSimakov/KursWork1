#include "AdminSession.hpp"

AdminSession::AdminSession(AccountsDB* accounts_db, ProductsDB* productsDB)
{
    this->products_db = productsDB;
	this->accounts_db = accounts_db;
    {
    	admin_menu = MenuFactory::create_admin_menu();
	    accounts_manage_menu = MenuFactory::create_accounts_manage_menu();
    	products_manage_menu = MenuFactory::create_products_manage_menu();
	    account_edit_menu = MenuFactory::create_account_edit_menu();
	    product_edit_menu = MenuFactory::create_product_edit_menu();
	    user_menu = MenuFactory::create_user_menu();
    }
}

void AdminSession::start(Account* account)
{
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
		case 0: accounts_db->show_table(); ConsoleOut::pause(); break;
		case 1: add_account(); break;
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
		case 0: products_db->show_table(); ConsoleOut::pause(); break;
		case 1: add_product(); break;
		case 2: delete_product(); break;
		case 3: start_product_editing(); break;
		case 4: find_products_by_name(); break;
		case 5: find_products_by_registrant(); break;
		case 6: find_products_by_date(); break;
		case 7: products_db->show_sorted_by_name(); break;
		case 8: products_db->show_sorted_by_price_to_higher(); break;
		case 9: products_db->show_sorted_by_amount_to_higher(); break;
		case 10: case -1: products_manage_menu->set_pointer_to_start(); return;
		default: break;
		}
	}
}

void AdminSession::add_account()
{
    Account account;
	ConsoleOut::show_title("Add new account");

	account.set_login(ConsoleInp::get_free_login(accounts_db));
	if (account.get_login() == "0") return;

	string pass = ConsoleInp::password_format_input();
	if (pass == "0") return;

	account.set_role((Role)ConsoleInp::get_number_from_range(0, 1, "Role(0|1): "));

	if (ConfirmationMenu::confirm()) 
	{
		account.set_access(Access::YES);
		account.set_salt(Account::get_generated_salt());
		account.set_hash(Account::get_generated_hash(pass, account.get_salt()));
		accounts_db->add_new(account);

		ConsoleOut::show_info("Account was created", "\t", "\n\n");
	}
	else ConsoleOut::show_info("Account was't created", "\t", "\n\n");
	
	ConsoleOut::pause();
} 

void AdminSession::delete_account()
{
    ConsoleOut::show_title("Delete account", "", "\n\n");
	accounts_db->show_table();

	string login = ConsoleInp::get_exists_login(accounts_db);

	if (login == "0") return;
	else if (login == session_account->get_login()) 
	{
		ConsoleOut::show_error("You cannot delete your account", "\t", "\n");
	}
	else if (ConfirmationMenu::confirm()) 
	{
		accounts_db->_delete(login);
		ConsoleOut::show_info("Account '" + login + "' was deleted", "\t", "\n\n");
	}
	else ConsoleOut::show_info("Account was't deleted", "\t", "\n\n");

	ConsoleOut::pause();
}

void AdminSession::confirm_account()
{
    ConsoleOut::show_title("Confirm account", "", "\n\n");
	accounts_db->show_table();

	string login = ConsoleInp::get_exists_login(accounts_db);

	if (login == "0") return;
	else if (login == session_account->get_login()) 
	{
		ConsoleOut::show_error("You cannot confirm your account", "\n\t", "\n\n");
	}
	else if (accounts_db->is_have_access(login)) 
	{
		ConsoleOut::show_info("Account already confirmed", "\n\t", "\n\n");
	}
	else 
	{
		accounts_db->confirm(login);
		ConsoleOut::show_info("Account '" + login + "' was confirmed", "\n\t", "\n\n");
	}
	ConsoleOut::pause();   
}

void AdminSession::block_account()
{
    ConsoleOut::show_title("Block account", "", "\n\n");
	accounts_db->show_table();

	string login = ConsoleInp::get_exists_login(accounts_db);

	if (login == "0") return;
	else if (login == session_account->get_login()) 
	{
		ConsoleOut::show_error("You cannot block your account", "\n\t", "\n\n");
	}
	else if (!accounts_db->is_have_access(login)) 
	{
		ConsoleOut::show_info("Account already blocked", "\n\t", "\n\n");
	}
	else 
	{
		accounts_db->block(login);
		ConsoleOut::show_info("Account '" + login + "' was blocked", "\n\t", "\n\n");
	}
	ConsoleOut::pause();
}

void AdminSession::start_account_editing()
{
    ConsoleOut::show_title("Edit account");
	
	string login = ConsoleInp::get_exists_login(accounts_db);
	if (login == "0") return;

	account_edit_menu->set_title("<- Editing '" + login + "' ->");
	while (true) 
	{
		switch (account_edit_menu->get_num_of_choisen_line())
		{
		case 0: 
			edit_login(&login);
			account_edit_menu->set_title("<- Editing '" + login + "' ->");
			break;
		case 1: edit_password(login); break;
		case 2: edit_role(login); break;
		case 3: case -1: return;
		default: break;
		}
	}
} 

void AdminSession::edit_login(string *login)
{
	ConsoleOut::show_title("Edit login", "\t", "\n\n");

	cout << "Old login: " << *login << endl;
	string new_login = ConsoleInp::get_free_login(accounts_db);

	if (new_login == "0") return;
	else if (ConfirmationMenu::confirm()) 
	{
		*login = new_login;
		accounts_db->update_login(*login, new_login);
		ConsoleOut::show_info("Login was changed", "\t", "\n\n");
	}
	else ConsoleOut::show_info("Login was't changed", "\t", "\n\n");

	ConsoleOut::pause();
}

void AdminSession::edit_password(string login)
{
    ConsoleOut::show_title("Edit password", "\t", "\n\n");
	string password = ConsoleInp::password_format_input();

	if (password == "0") return;
	else if (ConfirmationMenu::confirm()) 
	{
		accounts_db->update_password(login, password);
		ConsoleOut::show_info("Password was changed", "\t", "\n\n");
	}
	else ConsoleOut::show_info("Password was't changed", "\t", "\n\n");

	ConsoleOut::pause();
}

void AdminSession::edit_role(string login)
{
    if (login != session_account->get_login()) 
	{
		ConsoleOut::show_title("Edit role", "\t", "\n\n");
		int new_role = ConsoleInp::get_number_from_range(-1, 1, "Role: ");

		if (new_role == -1) return;
		else if (ConfirmationMenu::confirm()) 
		{
			accounts_db->update_role(login, (Role)new_role);
			ConsoleOut::show_info("Role was changed", "\t", "\n\n");
		}
		else ConsoleOut::show_info("Role was't changed", "\t", "\n\n");
	}
	else ConsoleOut::show_error("You cannot edit your role", "\t", "\n\n");
	
	ConsoleOut::pause();
}

void AdminSession::add_product()
{
	ConsoleOut::show_title("Add new product");
    Product product;

	product.set_name(ConsoleInp::get_non_existent_product_name(products_db));
	if (product.get_name() == "0") return;

	product.set_amount(ConsoleInp::get_number(true, "Amount: "));
	if (product.get_amount() == 0) return;

	product.set_price(ConsoleInp::get_number(true, "Price: "));
	if (product.get_price() == 0) return;

	cout << "(yyyy-mm-dd)" << endl;
	product.set_date(ConsoleInp::get_format_date());
	if (product.get_date() == "0") return;

	cout << "Registrant: ";
	string registrant;
	getline(cin, registrant);
	product.set_registrant(registrant);
	if (product.get_registrant() == "0") return;

	products_db->add_new(product);

	ConsoleOut::show_info("Product was added", "\n\t", "\n\n");
	ConsoleOut::pause();
}

void AdminSession::delete_product()
{
    ConsoleOut::show_title("Delete product", "", "\n\n");
	products_db->show_table();

	string name = ConsoleInp::get_exists_product_name(products_db);

	if (name == "0") return;
	else if (ConfirmationMenu::confirm()) 
	{
		products_db->_delete(name);
		ConsoleOut::show_info("Product was deleted", "\t", "\n\n");
	}
	else ConsoleOut::show_info("Product was't deleted", "\t", "\n\n");
	
	ConsoleOut::pause();
}

void AdminSession::start_product_editing()
{
    ConsoleOut::show_title("Edit product munu");

	string name = ConsoleInp::get_exists_product_name(products_db);
	if (name == "0") return;

	product_edit_menu->set_title("<- Editing: " + name + " ->");
	while (true) 
	{
		switch (product_edit_menu->get_num_of_choisen_line())
		{
		case 0: 
			edit_name(&name);
			product_edit_menu->set_title("<- Editing: " + name + " ->");
			break;
		case 1: edit_amount(name); break;
		case 2: edit_price(name); break;
		case 3: edit_date(name); break;
		case 4: edit_registrant(name); break;
		case 5: case -1: return;
		default: break;
		}
	}
} 

void AdminSession::edit_name(string *name)
{
    ConsoleOut::show_title("Edit product name", "\t", "\n\n");
	
	cout << "Old name: " << *name << endl;
	string new_name = ConsoleInp::get_non_existent_product_name(products_db);

	if (new_name == "0") return;
	else if (ConfirmationMenu::confirm()) 
	{
		products_db->update_name(*name, new_name);
		*name = new_name;
		ConsoleOut::show_info("Product was renamed", "\t", "\n\n");
	}
	else ConsoleOut::show_info("Product was't renamed", "\t", "\n\n");

	ConsoleOut::pause();
} 

void AdminSession::edit_amount(string name)
{
    ConsoleOut::show_title("Edit amount", "\t", "\n\n");

	cout << "Old amount: " << products_db->get_amount(name) << endl;
	int amount = ConsoleInp::get_number(true, "New amount: ");

	if (amount == 0) return;
	else 
	{
		products_db->update_amount(name, amount);
		ConsoleOut::show_info("Amount was updated", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void AdminSession::edit_price(string name)
{
    ConsoleOut::show_title("Edit product price", "\t", "\n\n");
	
	cout << "Old price: " << products_db->get_price(name) << endl;
	int price = ConsoleInp::get_number(true, "New price: ");

	if (price == 0) return;
	else 
	{
		products_db->update_price(name, price);
		ConsoleOut::show_info("Price was updated", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

void AdminSession::edit_date(string name)
{
    ConsoleOut::show_title("Edit date", "\t", "\n\n");

	cout << "Old date: " << products_db->get_date(name) << endl;
	string date = ConsoleInp::get_format_date();

	if (date == "0") return;
	else 
	{
		products_db->update_date(name, date);
		ConsoleOut::show_info("Date was updated", "\t", "\n\n");
	}
	ConsoleOut::pause();
} 

void AdminSession::edit_registrant(string name)
{
    ConsoleOut::show_title("Edit registrant name", "\t", "\n\n");

	cout << "Old name: " << products_db->get_registrant(name) << endl;
	cout << "New name: ";
	string reg_name;
	getline(cin, reg_name);

	if (reg_name == "0") return;
	else 
	{
		products_db->update_registrant(name, reg_name);
		ConsoleOut::show_info("Name was updated", "\t", "\n\n");
	}
	ConsoleOut::pause();
}

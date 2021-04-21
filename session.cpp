#pragma once
#include "session.h"


Session::Session(SQLWork* product_db, SQLWork* account_db) {
	this->product_db = product_db;
	this->account_db = account_db;
	init_admin_menu();
	init_user_menu();
	init_confirm_operation_menu();
}


void Session::start_as_admin(string login) {
	this->user_login = login;
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = main_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0:
			admin_manage_accounts_start();
			break;
		case 1:
			admin_manage_products_start();
			break;
		case 2: case -1:
			if (confirm_menu_start("Вы уверены, что хотите выйти из аккаунта?")) {
				is_exit = true;
			}
			break;
		default:
			break;
		}
	}
}

void Session::admin_manage_accounts_start() {
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = manage_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // просмотр всех записей
			show_accounts_table();
			system("pause");
			break;
		case 1: // добавление новой
			add_new_account();
			break;
		case 2: // редактирование 
			edit_account_menu_start();
			break;
		case 3: // удаление учетной записи
			delete_account();
			break;
		case 4: // подтверждение учетной записи
			confirm_account();
			break;
		case 5: // блокировка учетной записи
			block_account();
			break;
		case 6:	case -1: // выход
			is_exit = true;
			break;
		default:
			break;
		}
	}
}

void Session::admin_manage_products_start() {
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = data_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // просмотр всех записей
			show_products_table();
			system("pause");
			break;
		case 1: // добавление новой
			add_new_product();
			break;
		case 2: // удаление
			delete_product();
			break;
		case 3: // редактирование
			edit_product_menu_start();
			break;
		case 4: // индивидуалка
			individual_task();
			break;
		case 5: // поиск по названию
			find_by_name();
			break;
		case 6: // поиск по имени регистрировавшего
			find_by_reg_name();
			break;
		case 7: // поиск по дате
			find_by_data();
			break;
		case 8: // сортировка по имени
			sort_by_name();
			break;
		case 9: // сортировка по цене
			sort_by_price_to_higher();
			break;
		case 10: // сортировка количеству
			sort_by_amount_to_higher();
			break;
		case 11: case -1: // выход
			is_exit = true;
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
		case 0: // да
			return true;
		case 1: // нет
			return false;
		case -1: default:
			break;
		}
	}
}

void Session::start_as_user(string login) {
	this->user_login = login;
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = user_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // просмотр всех записей
			show_products_table();
			system("pause");
			break;
		case 1: // индивидуалка
			individual_task();
			break;
		case 2: // поиск по названию
			find_by_name();
			break;
		case 3: // поиск по имени регистрировавшего
			find_by_reg_name();
			break;
		case 4: // поиск по дате
			find_by_data();
			break;
		case 5: // сортировка по имени
			sort_by_name();
			break;
		case 6: // сортировка по цене
			sort_by_price_to_higher();
			break;
		case 7: // сортировка количеству
			sort_by_amount_to_higher();
			break;
		case 8: case -1: // выход
			if (confirm_menu_start("Вы уверены, что хотите выйти из аккаунта?")) {
				is_exit = true;
			}
			break;

		default:
			break;
		}
	}
}



void Session::init_admin_menu() {
	main_menu = new Menu("<- Главное меню ->",
		{ " Управление учетными записями",
		  " Управление товарами",
		  " Выход из аккаунта" });

	manage_menu = new Menu("<- Управление учетными записями ->",
		{ " Просмотр всех учетных записей",
		  " Добавление новой учетной записи",
		  " Редактирование учетной записи",
		  " Удаление учетной записи",
		  " Подтверждение учетной записи",
		  " Блокировка учетной записи",
		  " Выход" });

	data_menu = new Menu("<- Управление товарами ->",
		{ " Просмотр всех товаров",
		  " Добавление нового товара",
		  " Удаление товара",
		  " Редактирование информациии о товаре",
		  " Просмотр товаров лежащих больше х месяцев, с ценой больше у",
		  " Поиск по названию",
		  " Поиск по ФИО зарегестрировавшего",
		  " Поиск по дате поступления на склад",
		  " Сортировка по названию товара",
		  " Сортировка по цене товара (возрастание)",
		  " Сортировка по количеству товара (возрастание)",
		  " Выход" });

	account_edit_menu = new Menu("<- Выбор пункта для редактирования аккаунта ->", 
		{ " Логин",
		  " Пароль",
		  " Роль",
		  " Выход" });

	product_edit_menu = new Menu("<- Выбор пункта для редактирования товара ->",
		{ " Название",
		  " Количество",
		  " Цена",
		  " Дата поступления на склад",
		  " ФИО зарегестрировавшего",
		  " Выход" });
}

void Session::init_user_menu() {
	user_menu = new Menu("<- Меню работы с товарами ->",
		{ " Просмотр всех товаров",
		  " Просмотр товаров лежащих больше х месяцев, с ценой больше у",
		  " Поиск по названию",
		  " Поиск по ФИО зарегестрировавшего",
		  " Поиск по дате поступления на склад",
		  " Сортировка по названию товара",
		  " Сортировка по цене товара (возрастание)",
		  " Сортировка по количеству товара (возрастание)",
		  " Выход из аккаунта" });

}

void Session::init_confirm_operation_menu() {
	confirm_operation_menu = new Menu("Вы уверены?", { " Да", " Нет" });
}


void Session::show_accounts_table(string sql_start, string sql_end) {
	console::show_title("Все учетные записи", "    ");
	account_db->show_table(sql_start, sql_end,
		{ "     Логин", "Роль", "Доступ" },
		{ 0, 3, 4},
		{ 18, 7, 9});
	cout << endl;
}

void Session::add_new_account() {
	Account account;
	console::show_title("Создание нового аккаунта. (0 в любом из полей, кроме роли, для выхода)");

	account.login = console::get_free_login(account_db, "Логин: ");
	if (account.login == "0") return;

	string pass = console::password_format_input("Пароль: ");
	if (pass == "0") return;
	
	account.role = console::get_number_from_range(0, 1, "Роль: ");


	if (confirm_menu_start("Вы уверены, что хотите создать аккаунт?")) {
		account.access = 1;
		account.salt = help::get_generated_salt();
		account.salted_hash_password = help::generate_hash(pass, account.salt);

		account_db->push_back({ "'" + account.login + "'",
							"'" + account.salted_hash_password + "'",
							"'" + account.salt + "'",
						   to_string(account.role),
						   to_string(account.access) });

		console::show_info("Аккаунт был создан", "\t", "\n\n");
	}
	else {
		console::show_info("Аккаунт не был создан", "\t", "\n\n");
	}
	system("pause");
}

void Session::delete_account() {
	string login;
	console::show_title("Удаление аккаунта (введите '0' для выхода)", "", "\n\n");
	show_accounts_table();
	cout << "Введите логин аккаунта, который хотите удалить." << endl;
	
	login = console::get_exists_login(account_db);
	
	if (login == "0") return;
	else if (login == user_login) {
		console::show_error("Нельзя удалить свой аккаунт", "\t", "\n");
	}
	else if (confirm_menu_start("Вы уверены, что хотите удалить аккаунт '"+ login + "' ?")) {
		account_db->delete_field("LOGIN='" + login + "'");
		console::show_info("Аккаунт '" + login + "' был удален", "\t", "\n\n");
	}
	else {
		console::show_info("Изменения не были внесены", "\t", "\n\n");
	}
	system("pause");
}

void Session::confirm_account() {
	string login;
	console::show_title("Подтверждение аккаунта ('0' для выхода)", "", "\n\n");
	show_accounts_table();
	cout << "Введите логин аккаунта, который хотите подтвердить." << endl;
	login = console::get_exists_login(account_db);

	if (login == "0") return;
	else if (login == user_login) {
		console::show_error("Эту функцию нельзя использовать для своего аккаунта", "\n\t", "\n\n");
	}
	else if (account_db->get_int("LOGIN", login, 4) == 1) {
		console::show_info("Этот аккаунт уже подтвержден", "\n\t", "\n\n");
	}
	else {
		account_db->update("ACCESS", "1", "LOGIN='" + login + "'");
		console::show_info("Аккаунт '" + login + "' был подтвержден", "\n\t", "\n\n");
	}
	system("pause");
}

void Session::block_account() {
	string login;
	console::show_title("Блокировка аккаунта ('0' для выхода)", "", "\n\n");
	show_accounts_table();
	cout << "Введите логин аккаунта, который хотите заблокировать." << endl;

	login = console::get_exists_login(account_db);
	
	if (login == "0") return;
	else if (login == user_login) {
		console::show_error("Эту функцию нельзя использовать для своего аккаунта", "\n\t", "\n\n");
	}
	else if (account_db->get_int("LOGIN", login, 4) == 0) {
		console::show_info("Этот аккаунт уже заблокирован", "\n\t", "\n\n");
	}
	else {
		account_db->update("ACCESS", "0", "LOGIN='" + login + "'");
		console::show_info("Аккаунт '" + login + "' был заблокирован", "\n\t", "\n\n");
	}
	system("pause");
}

void Session::edit_account_menu_start() {
	string login;
	cout << "Введите логин аккаунта для редактирования ('0' для выхода)." << endl;
	login = console::get_exists_login(account_db);
	if (login == "0") return;

	account_edit_menu->set_title("<- Редактирование аккаунта '" + login + "' ->");
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = account_edit_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // Логин
			edit_login(&login);
			account_edit_menu->set_title("<- Редактирование аккаунта '" + login + "' ->");
			break;
		case 1: // пароль
			edit_password(login);
			break;
		case 2: // роль 
			edit_role(login);
			break;
		case 3: case -1: // выход
			is_exit = true;
			break;

		default:
			break;
		}
	}
}

void Session::edit_login(string *login) {
	console::show_title("Изменение логина ('0' для выхода)", "\t", "\n\n");
	cout << "Старый логин: " << *login << endl;
	cout << "Введите новый логин." << endl;

	string new_login = console::get_free_login(account_db, "Логин: ");
	
	if (new_login == "0") {
		return;
	}
	else if (confirm_menu_start("Вы уверены, что хотите изменить логин на '" + new_login + "' ?")){
		account_db->update("LOGIN", "'" + new_login + "'", "LOGIN='" + *login + "'");
		*login = new_login;
		console::show_info("Изменения были внесены", "\t", "\n\n");
	}
	else {
		console::show_info("Изменения не были внесены", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_password(string login) {
	console::show_title("Изменение пароля ('0' для выхода)", "\t", "\n\n");
	cout << "Введите новый пароль." << endl;
	string pass = console::password_format_input("Пароль: ");

	if (pass == "0") {
		return;
	}
	else if (confirm_menu_start("Вы уверены, что хотите изменить пароль?")) {
		string salt = help::get_generated_salt();
		string hash = help::generate_hash(pass, salt);
		account_db->update("HASH", "'" + hash + "'", "LOGIN='" + login + "'");
		account_db->update("SALT", "'" + salt + "'", "LOGIN='" + login + "'");

		console::show_info("Изменения были внесены", "\t", "\n\n");
	}
	else {
		console::show_info("Изменения не были внесены", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_role(string login) {
	if (login != user_login) {
		int new_role;
		console::show_title("Изменение роли ('-1' для выхода)", "\t", "\n\n");

		cout << "Введите новую роль." << endl;
		new_role = console::get_number_from_range(-1, 1, "Роль: ");

		if (new_role == -1) {
			return;
		}
		else if (confirm_menu_start("Вы уверены, что хотите изменить роль?")) {
			account_db->update("ROLE", to_string(new_role), "LOGIN='" + login + "'");
			console::show_info("Изменения были внесены", "\t", "\n\n");
		}
		else {
			console::show_info("Изменения не были внесены", "\t", "\n\n");
		}
	}
	else {
		console::show_error("Эту функцию нельзя использовать для своего аккаунта", "\t", "\n\n");
	}
	system("pause");

}




void Session::show_products_table(string sql_start, string sql_end) {
	console::show_title("товары", "                                          ");
	product_db->show_table(sql_start, sql_end,
						{ "         Название", "Количество", "  Цена", "Дата поступления", "    ФИО зарегестрировавшего" }, 
						{ 0, 1, 2, 3, 4 }, 
						{28, 13, 12, 19, 35});
	cout << endl;
}

void Session::add_new_product() {
	Product product;
	console::show_title("Добавление нового продукта. ('0' для выхода)");


	cout << "Название товара: ";
	product.name = console::get_non_existent_field(product_db, "NAME");
	if (product.name == "0") return;

	cout << "Количество товаров: ";
	product.amount = console::get_number(true);
	if (product.amount == 0) return;

	cout << "Цена товара: ";
	product.price = console::get_number(true);
	if (product.price == 0) return;


	cout << "Дата поступления на склад (ГГГГ-ММ-ДД): ";
	product.date = console::get_format_data();
	if (product.date == "0") return;

	cout << "ФИО зарегестрировавшего: ";
	getline(cin, product.name_of_registrant);
	if (product.name_of_registrant == "0") return;

	product_db->push_back({ "'" + product.name + "'",
						to_string(product.amount),
						"'" + to_string(product.price) + "'",
					    "'" + product.date + "'",
					    "'" + product.name_of_registrant + "'" });

	console::show_info("Товар добавлен", "\n\t", "\n\n");
	system("pause");

}

void Session::delete_product() {
	string name;
	console::show_title("Удаление товара. ('0' для выхода)", "", "\n\n");
	show_products_table();
	cout << "Введите название товара, который хотите удалить" << endl;
	name = console::get_exists_field(product_db, "NAME");
	
	if (name == "0") {
		return;
	}
	else if (confirm_menu_start("Вы уверены, что хотите удалить товар '" + name + "' ?")) {
		product_db->delete_field("NAME='" + name + "'");
		console::show_info("Товар был удален.", "\t", "\n\n");
	}
	else {
		console::show_info("Изменения не были внесены.", "\t", "\n\n");
	}
	system("pause");

	
}

void Session::edit_product_menu_start() {
	string name;
	cout << "Введите название продукта для редактирования. (0 - для выхода)" << endl;
	name = console::get_exists_field(product_db, "NAME");
	if (name == "0") return;

	product_edit_menu->set_title("<- Редактирование товара: " + name + " ->");
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = product_edit_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // название
			edit_name(&name);
			product_edit_menu->set_title("<- Редактирование товара: " + name + " ->");
			break;
		case 1: // количество
			edit_amount(name);
			break;
		case 2: // цена
			edit_price(name);
			break;
		case 3: // дата
			edit_data(name);
			break;
		case 4: // ФИО
			edit_reg_name(name);
			break;
		case 5: case -1: // выход
			cout << "Выход." << endl;
			is_exit = true;
			break;

		default:
			break;
		}
	}

}

void Session::edit_name(string* name) {
	string new_name;
	console::show_title("Изменение названия ('0' для выхода)", "\t", "\n\n");
	cout << "Старое название: " << *name << endl;
	cout << "Введите новое название." << endl;
	new_name = console::get_non_existent_field(product_db, "NAME");
	
	if (new_name == "0") {
		return;
	}
	else if (confirm_menu_start("Вы уверены, что хотите изменить название на '" + new_name + "' ?")) {
		product_db->update("NAME", "'" + new_name + "'", "NAME='" + *name + "'");
		*name = new_name;
		console::show_info("Изменения были внесены.", "\t", "\n\n");
	}
	else {
		console::show_info("Изменения не были внесены.", "\t", "\n\n");
	}
	system("pause");

}

void Session::edit_amount(string name) {
	int amount;
	console::show_title("Изменение количества ('0' для выхода)", "\t", "\n\n");
	cout << "Старое количество: " << product_db->get_int("NAME", name, 1) << endl;
	cout << "Введите новое количество." << endl;
	cout << "Количество: ";
	amount = console::get_number(true);

	if (amount == 0) {
		return;
	}
	else  {
		product_db->update("AMOUNT", "'" + to_string(amount) + "'", "NAME='" + name + "'");
		console::show_info("Изменения были внесены.", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_price(string name) {
	int price;
	console::show_title("Изменение цены ('0' для выхода)", "\t", "\n\n");
	cout << "Старая цена: " << product_db->get_int("NAME", name, 2) << endl;
	cout << "Введите новую цену." << endl;
	cout << "Цена: ";
	price = console::get_number(true);

	if (price == 0) {
		return;
	}
	else {
		product_db->update("PRICE", "'" + to_string(price) + "'", "NAME='" + name + "'");
		console::show_info("Изменения были внесены.", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_data(string name) {
	string data;
	console::show_title("Изменение даты ('0' для выхода)", "\t", "\n\n");
	cout << "Старая дата: " << product_db->get_text("NAME", name, 3) << endl;
	cout << "Введите новую дату." << endl;
	cout << "Дата: ";
	data = console::get_format_data();

	if (data == "0") {
		return;
	}
	else {
		product_db->update("DATE", "'" + data + "'", "NAME='" + name + "'");
		console::show_info("Изменения были внесены.", "\t", "\n\n");
	}
	system("pause");
}

void Session::edit_reg_name(string name) {
	string reg_name;
	console::show_title("Изменение ФИО зарегестрировавшего ('0' для выхода)", "\t", "\n\n");
	cout << "Старое ФИО: " << product_db->get_text("NAME", name, 4) << endl;
	cout << "Введите новое ФИО.\n> " << endl;
	getline(cin, reg_name);

	if (reg_name == "0") {
		return;
	}
	else {
		product_db->update("REG_NAME", "'" + reg_name + "'", "NAME='" + name + "'");
		console::show_info("Изменения были внесены.", "\t", "\n\n");
	}
	system("pause");
}

void Session::individual_task() {
	int mounth_amount, price;
	console::show_title("Просмотр товаров лежащих больше х месяцев, с ценой больше у ('0' для выхода)", "\t", "\n\n");

	mounth_amount = console::get_number(true, "Количество месяцев: ");
	if (mounth_amount == 0) return;

	price = console::get_number(true, "Стоимость: ");
	if (price == 0) return;

	string data =  product_db->date_mounhth_befor(to_string(mounth_amount));
	cout << "\nДата: " << data << "\n" << endl;

	show_products_table("SELECT * FROM ", " WHERE DATE > '" + data + "' AND PRICE > '" + to_string(price) + "' ORDER BY NAME ASC;");
	system("pause");
}

void Session::find_by_name() {
	string name;
	console::show_title("Поиск товара по названию ('0' для выхода)", "\t", "\n\n");
	
	cout << "Введите название или его часть для поиска\n>";
	getline(cin, name);
	if (name == "0") return;

	cout << endl;
	show_products_table("SELECT * FROM ", " WHERE NAME GLOB '*" + name + "*';");
	system("pause");
}

void Session::find_by_reg_name() {
	string name;
	console::show_title("Поиск по ФИО зарегестрировавшего товар ('0' для выхода)", "\t", "\n\n");
	
	cout << "Введите ФИО зарегестрировавшего или его часть для поиска\n>";
	getline(cin, name);
	if (name == "0") return;

	cout << endl;
	show_products_table("SELECT * FROM ", " WHERE REG_NAME GLOB '*" + name + "*';");
	system("pause");
}

void Session::find_by_data() {
	string data;
	console::show_title("Поиск по дате ('0' для выхода)", "\t", "\n\n");
	
	cout << "Вы можете использовать знак * для обозначения неизвестных искомых (Пример: *-12-05, 2021-*-*)" << endl;
	cout << "Дата: ";
	cin >> data;
	cin.ignore(256, '\n');
	if (data == "0") return;


	cout << endl;
	show_products_table("SELECT * FROM ", " WHERE DATE GLOB '" + data + "';");
	system("pause");
}

void Session::sort_by_name() {
	console::show_title("Товары отсортированы в алфавитном порядке", "\t", "\n\n");
	show_products_table("SELECT * FROM ", " ORDER BY NAME ASC ;");
	system("pause");
}

void Session::sort_by_price_to_higher() {
	console::show_title("Товары отсортированы по цене (от меньшей к большей)", "\t", "\n\n");
	show_products_table("SELECT * FROM ", " ORDER BY PRICE ASC ;");
	system("pause");
}

void Session::sort_by_amount_to_higher() {
	console::show_title("Товары отсортированы по количеству (от меньшего к большему)", "\t", "\n\n");
	show_products_table("SELECT * FROM ", " ORDER BY AMOUNT ASC ;");
	system("pause");
}


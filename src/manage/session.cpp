#pragma once
#include "session.h"


Session::Session(SQLWork* product_db, SQLWork* account_db) {
	this->product_db = product_db;
	this->account_db = account_db;
	init_admin_menu();
	init_user_menu();
	init_confirm_operation_menu();
}

// инициализация меню администратора, управления учетными записями, товарами, редактирования аккаунта и товара
void Session::init_admin_menu() {
	admin_menu = new Menu("<- Меню администратора ->",
		{ " Управление учетными записями",
		  " Управление товарами",
		  " Выход из аккаунта" });
	admin_menu->set_start_with_first_line(true);

	accounts_manage_menu = new Menu("<- Управление учетными записями ->",
		{ " Просмотр всех учетных записей",
		  " Добавление",
		  " Редактирование",
		  " Удаление",
		  " Подтверждение",
		  " Блокировка",
		  " Выход" });

	products_manage_menu = new Menu("<- Управление товарами ->",
		{ " Просмотр всех товаров",
		  " Добавление",
		  " Удаление",
		  " Редактированиее",
		  " Просмотр товаров лежащих больше х месяцев, с ценой больше у",
		  " Поиск по названию",
		  " Поиск по ФИО зарегестрировавшего",
		  " Поиск по дате поступления на склад",
		  " Сортировка по названию",
		  " Сортировка по цене (возрастание)",
		  " Сортировка по количеству (возрастание)",
		  " Выход" });

	account_edit_menu = new Menu({ " Логин", " Пароль", " Роль", " Выход" });
	account_edit_menu->set_start_with_first_line(true);

	product_edit_menu = new Menu({ " Название", " Количество", " Цена", " Дата поступления на склад", " ФИО зарегестрировавшего", " Выход" });
	product_edit_menu->set_start_with_first_line(true);
}

// инициализация меню пользователя
void Session::init_user_menu() {
	user_menu = new Menu("<- Меню работы с товарами ->",
		{ " Просмотр всех товаров",
		  " Просмотр товаров лежащих больше х месяцев, с ценой больше у",
		  " Поиск по названию",
		  " Поиск по ФИО зарегестрировавшего",
		  " Поиск по дате поступления на склад",
		  " Сортировка по названию",
		  " Сортировка по цене (возрастание)",
		  " Сортировка по количеству (возрастание)",
		  " Выход из аккаунта" });
}

// инициализация меню подтверждения
void Session::init_confirm_operation_menu() {
	confirm_operation_menu = new Menu({ " Да", " Нет" });
	confirm_operation_menu->set_start_with_first_line(true);
}

// старт сессии пользователя
void Session::start_as_user(string login) {
	this->session_account_login = login;
	int choise = 0;
	while (true) {
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
			find_products_by_name();
			break;
		case 3: // поиск по имени регистрировавшего
			find_products_by_name_of_registrant();
			break;
		case 4: // поиск по дате
			find_products_by_date();
			break;
		case 5: // сортировка по имени
			sort_products_by_name();
			break;
		case 6: // сортировка по цене
			sort_products_by_price_to_higher();
			break;
		case 7: // сортировка количеству
			sort_products_by_amount_to_higher();
			break;
		case 8: case -1: // выход
			if (confirm_menu_start("Вы уверены, что хотите выйти из аккаунта?")) {
				user_menu->set_pointer_to_start();
				return;
			}
			break;

		default:
			break;
		}
	}
}

// старт сессии администратора
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
			if (confirm_menu_start("<- Вы уверены, что хотите выйти из аккаунта? ->")) {
				return;
			}
			break;
		default:
			break;
		}
	}
}

// запуск меню подтверждения действия
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

// старт меню управления аккаунтами
void Session::admin_manage_accounts_start() {
	int choise = 0;
	while (true) {
		choise = accounts_manage_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // просмотр всех записей
			show_accounts_table();
			system("pause");
			break;
		case 1: // добавление нового
			add_new_account();
			break;
		case 2: // редактирование 
			start_edit_account_menu();
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
			accounts_manage_menu->set_pointer_to_start();
			return;
			break;
		default:
			break;
		}
	}
}

// конструктор по умолчанию выводит все учетные записи
void Session::show_accounts_table(string sql_start, string sql_end) {
	console::show_title("Все учетные записи", "    ");
	account_db->show_table(sql_start, sql_end,
		{ "     Логин", "Роль", "Доступ" },
		{ 0, 3, 4 },
		{ 18, 7, 9 });
	cout << endl;
}

// создание и добавление новой учетной записи
void Session::add_new_account() {
	Account account;
	console::show_title("Создание нового аккаунта. (0 в любом из полей, кроме роли, для выхода)");

	account.login = console::get_free_login(account_db, "Логин: ");
	if (account.login == "0") return;

	string pass = console::password_format_input("Пароль: ");
	if (pass == "0") return;

	account.role = console::get_number_from_range(0, 1, "Роль: ");


	if (confirm_menu_start("<- Вы уверены, что хотите создать аккаунт? ->")) {
		account.access = 1;
		account.salt = help_functions::get_generated_salt();
		account.salted_hash_password = help_functions::get_generated_hash(pass, account.salt);

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

// старт меню редактирования учетной записи
void Session::start_edit_account_menu() {
	console::show_title("Введите логин аккаунта для редактирования ('0' для выхода).");
	
	string login = console::get_exists_login(account_db);
	if (login == "0") return;

	account_edit_menu->set_title("<- Редактирование аккаунта '" + login + "' ->");
	int choise = 0;
	while (true) {
		choise = account_edit_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // Логин
			edit_account_login(&login);
			account_edit_menu->set_title("<- Редактирование аккаунта '" + login + "' ->");
			break;
		case 1: // пароль
			edit_account_password(login);
			break;
		case 2: // роль 
			edit_account_role(login);
			break;
		case 3: case -1: // выход
			return;
			break;

		default:
			break;
		}
	}
}

// редактирование логина
void Session::edit_account_login(string* login) {
	console::show_title("Изменение логина. ('0' для выхода)", "\t", "\n\n");
	cout << "Старый логин: " << *login << endl;
	string new_login = console::get_free_login(account_db, "Новый логин: ");

	if (new_login == "0") return;
	else if (confirm_menu_start("<- Вы уверены, что хотите изменить логин на '" + new_login + "' ? ->")) {
		account_db->update("LOGIN", "'" + new_login + "'", "LOGIN='" + *login + "'");
		*login = new_login;
		console::show_info("Изменения были внесены", "\t", "\n\n");
	}
	else {
		console::show_info("Изменения не были внесены", "\t", "\n\n");
	}
	system("pause");
}

// редактирование пароля
void Session::edit_account_password(string login) {
	console::show_title("Изменение пароля. ('0' для выхода)", "\t", "\n\n");
	string pass = console::password_format_input("Новый пароль: ");

	if (pass == "0") return;
	else if (confirm_menu_start("<- Вы уверены, что хотите изменить пароль? ->")) {
		string salt = help_functions::get_generated_salt();
		string hash = help_functions::get_generated_hash(pass, salt);
		account_db->update("HASH", "'" + hash + "'", "LOGIN='" + login + "'");
		account_db->update("SALT", "'" + salt + "'", "LOGIN='" + login + "'");

		console::show_info("Изменения были внесены", "\t", "\n\n");
	}
	else {
		console::show_info("Изменения не были внесены", "\t", "\n\n");
	}
	system("pause");
}

// редактирование роли
void Session::edit_account_role(string login) {
	if (login != session_account_login) {
		console::show_title("Изменение роли. ('-1' для выхода)", "\t", "\n\n");
		int new_role = console::get_number_from_range(-1, 1, "Новая роль: ");

		if (new_role == -1) return;
		else if (confirm_menu_start("<- Вы уверены, что хотите изменить роль? ->")) {
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

// удаление учетной записи
void Session::delete_account() {
	console::show_title("Удаление аккаунта. (введите '0' для выхода)", "", "\n\n");
	show_accounts_table();

	string login = console::get_exists_login(account_db);

	if (login == "0") return;
	else if (login == session_account_login) {
		console::show_error("Нельзя удалить свой аккаунт", "\t", "\n");
	}
	else if (confirm_menu_start("<- Вы уверены, что хотите удалить аккаунт '" + login + "' ? ->")) {
		account_db->delete_field("LOGIN='" + login + "'");
		console::show_info("Аккаунт '" + login + "' был удален", "\t", "\n\n");
	}
	else {
		console::show_info("Изменения не были внесены", "\t", "\n\n");
	}
	system("pause");
}

// подтверждение учетной записи
void Session::confirm_account() {
	console::show_title("Подтверждение аккаунта. ('0' для выхода)", "", "\n\n");
	show_accounts_table();

	string login = console::get_exists_login(account_db);

	if (login == "0") return;
	else if (login == session_account_login) {
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

// блокировка учетной записи
void Session::block_account() {
	console::show_title("Блокировка аккаунта. ('0' для выхода)", "", "\n\n");
	show_accounts_table();

	string login = console::get_exists_login(account_db);

	if (login == "0") return;
	else if (login == session_account_login) {
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

// старт меню управления товарами
void Session::admin_manage_products_start() {
	int choise = 0;
	while (true) {
		choise = products_manage_menu->get_num_of_choisen_line();
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
			start_edit_product_menu();
			break;
		case 4: // индивидуалка
			individual_task();
			break;
		case 5: // поиск по названию
			find_products_by_name();
			break;
		case 6: // поиск по имени регистрировавшего
			find_products_by_name_of_registrant();
			break;
		case 7: // поиск по дате
			find_products_by_date();
			break;
		case 8: // сортировка по имени
			sort_products_by_name();
			break;
		case 9: // сортировка по цене
			sort_products_by_price_to_higher();
			break;
		case 10: // сортировка количеству
			sort_products_by_amount_to_higher();
			break;
		case 11: case -1: // выход
			products_manage_menu->set_pointer_to_start();
			return;
			break;
		default:
			break;
		}
	}
}

// конструктор по умолчанию выводит все товары
void Session::show_products_table(string sql_start, string sql_end) {
	console::show_title("товары", "                                          ");
	product_db->show_table(sql_start, sql_end,
		{ "         Название", "Количество", "  Цена", "Дата поступления", "    ФИО зарегестрировавшего" },
		{ 0, 1, 2, 3, 4 },
		{ 28, 13, 12, 19, 35 });
	cout << endl;
}

// создание и добавление нового товара
void Session::add_new_product() {
	Product product;
	console::show_title("Добавление нового товара. ('0' для выхода)");

	product.name = console::get_non_existent_product_name(product_db);
	if (product.name == "0") return;

	product.amount = console::get_number(true, "Количество товаров: ");
	if (product.amount == 0) return;

	product.price = console::get_number(true, "Цена товара: ");
	if (product.price == 0) return;

	cout << "Дата поступления на склад (ГГГГ-ММ-ДД): ";
	product.date = console::get_format_date();
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

// удаление товара
void Session::delete_product() {
	console::show_title("Удаление товара. ('0' для выхода)", "", "\n\n");
	show_products_table();

	string name = console::get_exists_product_name(product_db);

	if (name == "0") return;
	else if (confirm_menu_start("<- Вы уверены, что хотите удалить товар '" + name + "' ? ->")) {
		product_db->delete_field("NAME='" + name + "'");
		console::show_info("Товар был удален.", "\t", "\n\n");
	}
	else {
		console::show_info("Изменения не были внесены.", "\t", "\n\n");
	}
	system("pause");
}

// старт меню редактирования товара
void Session::start_edit_product_menu() {
	console::show_title("Введите название продукта для редактирования. (0 - для выхода)");

	string name = console::get_exists_product_name(product_db);
	if (name == "0") return;

	product_edit_menu->set_title("<- Редактирование товара: " + name + " ->");
	int choise = 0;
	while (true) {
		choise = product_edit_menu->get_num_of_choisen_line();
		switch (choise)
		{
		case 0: // название
			edit_product_name(&name);
			product_edit_menu->set_title("<- Редактирование товара: " + name + " ->");
			break;
		case 1: // количество
			edit_product_amount(name);
			break;
		case 2: // цена
			edit_product_price(name);
			break;
		case 3: // дата
			edit_product_date(name);
			break;
		case 4: // ФИО
			edit_name_of_product_registrant(name);
			break;
		case 5: case -1: // выход
			return;
			break;

		default:
			break;
		}
	}

}

// редактирование названия товара
void Session::edit_product_name(string* name) {
	console::show_title("Изменение названия. ('0' для выхода)", "\t", "\n\n");
	
	cout << "Старое название: " << *name << endl;
	string new_name = console::get_non_existent_product_name(product_db, "Новое название: ");

	if (new_name == "0") return;
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

// редактирование количества товара
void Session::edit_product_amount(string name) {
	console::show_title("Изменение количества. ('0' для выхода)", "\t", "\n\n");

	cout << "Старое количество: " << product_db->get_int("NAME", name, 1) << endl;
	int amount = console::get_number(true, "Новое количество: ");

	if (amount == 0) return;
	else {
		product_db->update("AMOUNT", "'" + to_string(amount) + "'", "NAME='" + name + "'");
		console::show_info("Изменения были внесены.", "\t", "\n\n");
	}
	system("pause");
}

// редактирование цены на товар
void Session::edit_product_price(string name) {
	console::show_title("Изменение цены. ('0' для выхода)", "\t", "\n\n");
	
	cout << "Старая цена: " << product_db->get_int("NAME", name, 2) << endl;
	int price = console::get_number(true, "Новая цена: ");

	if (price == 0) return;
	else {
		product_db->update("PRICE", "'" + to_string(price) + "'", "NAME='" + name + "'");
		console::show_info("Изменения были внесены.", "\t", "\n\n");
	}
	system("pause");
}

// изменение даты поступления товара на склад
void Session::edit_product_date(string name) {
	console::show_title("Изменение даты. ('0' для выхода)", "\t", "\n\n");

	cout << "Старая дата: " << product_db->get_text("NAME", name, 3) << endl;
	string date = console::get_format_date("Новая дата: ");

	if (date == "0") return;
	else {
		product_db->update("DATE", "'" + date + "'", "NAME='" + name + "'");
		console::show_info("Изменения были внесены.", "\t", "\n\n");
	}
	system("pause");
}

// изменение ФИО зарегестрировавшего
void Session::edit_name_of_product_registrant(string name) {
	console::show_title("Изменение ФИО зарегестрировавшего. ('0' для выхода)", "\t", "\n\n");

	cout << "Старое ФИО: " << product_db->get_text("NAME", name, 4) << endl;
	cout << "Введите новое ФИО: ";
	string reg_name;
	getline(cin, reg_name);

	if (reg_name == "0") return;
	else {
		product_db->update("REG_NAME", "'" + reg_name + "'", "NAME='" + name + "'");
		console::show_info("Изменения были внесены.", "\t", "\n\n");
	}
	system("pause");
}

// Просмотр товаров лежащих больше х месяцев, с ценой больше у
void Session::individual_task() {
	console::show_title("Просмотр товаров лежащих больше х месяцев, с ценой больше у. ('0' для выхода)", "\t", "\n\n");

	int mounth_amount = console::get_number(true, "Количество месяцев: ");
	if (mounth_amount == 0) return;

	int price = console::get_number(true, "Стоимость: ");
	if (price == 0) return;

	string data = product_db->get_date_mounth_ago(to_string(mounth_amount));
	cout << "\nДата: " << data << "\n" << endl;

	show_products_table("SELECT * FROM ", " WHERE DATE > '" + data + "' AND PRICE > '" + to_string(price) + "' ORDER BY NAME ASC;");
	system("pause");
}

// поиск товаров по названию
void Session::find_products_by_name() {
	console::show_title("Поиск товара по названию. ('0' для выхода)", "\t", "\n\n");
	
	cout << "Введите название или его часть для поиска\n>";
	string name;
	getline(cin, name);
	if (name == "0") return;

	cout << endl;
	show_products_table("SELECT * FROM ", " WHERE NAME GLOB '*" + name + "*';");
	system("pause");
}

// поиск товаров по ФИО зарегестрировавшего
void Session::find_products_by_name_of_registrant() {
	console::show_title("Поиск по ФИО зарегестрировавшего товар. ('0' для выхода)", "\t", "\n\n");

	cout << "Введите ФИО зарегестрировавшего или его часть для поиска\n>";
	string name;
	getline(cin, name);
	if (name == "0") return;

	cout << endl;
	show_products_table("SELECT * FROM ", " WHERE REG_NAME GLOB '*" + name + "*';");
	system("pause");
}

// поиск по дате поступления не склад
void Session::find_products_by_date() {
	string date;
	console::show_title("Поиск по дате. ('0' для выхода)", "\t", "\n\n");

	cout << "Вы можете использовать знак * для обозначения неизвестных искомых. (Пример: *-12-05, 2021-*-*)" << endl;
	cout << "Дата: ";
	cin >> date;
	cin.ignore(256, '\n');
	if (date == "0") return;

	cout << endl;
	show_products_table("SELECT * FROM ", " WHERE DATE GLOB '" + date + "';");
	system("pause");
}

// сортировка товаров по названию
void Session::sort_products_by_name() {
	console::show_title("Товары отсортированы в алфавитном порядке", "\t", "\n\n");
	show_products_table("SELECT * FROM ", " ORDER BY NAME ASC ;");
	system("pause");
}

// сортировка товаров по цене от меньшей к большей
void Session::sort_products_by_price_to_higher() {
	console::show_title("Товары отсортированы по цене. (от меньшей к большей)", "\t", "\n\n");
	show_products_table("SELECT * FROM ", " ORDER BY PRICE ASC ;");
	system("pause");
}

// сортирова товаров по количеству от меньшего к большему
void Session::sort_products_by_amount_to_higher() {
	console::show_title("Товары отсортированы по количеству. (от меньшего к большему)", "\t", "\n\n");
	show_products_table("SELECT * FROM ", " ORDER BY AMOUNT ASC ;");
	system("pause");
}


#pragma once
#include "session.h"


Session::Session(SQLWork* product_db, SQLWork* account_db) {
	this->product_db = product_db;
	this->account_db = account_db;
	init_admin_menu();
	init_user_menu();
}


void Session::start_as_admin() {
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = main_menu->get_choise();
		switch (choise)
		{
		case 0:
			admin_manage_accounts_start();
			break;
		case 1:
			admin_manage_products_start();
			break;
		case 2: case -1:
			cout << "Выход из аккаунта" << endl;
			is_exit = true;
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
		choise = manage_menu->get_choise();
		switch (choise)
		{
		case 0: // просмотр всех записей
			show_accounts();
			break;
		case 1: // добавление новой
			add_new_account();
			system("pause");
			break;
		case 2: // редактирование 
			edit_account_menu_start();
			system("pause");
			break;
		case 3: // удаление учетной записи
			delete_account();
			system("pause");
			break;
		case 4: // подтверждение учетной записи
			confirm_account();
			system("pause");
			break;
		case 5: // блокировка учетной записи
			block_account();
			system("pause");
			break;
		case 6:	case -1: // выход
			cout << "Выход." << endl;
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
		choise = data_menu->get_choise();
		switch (choise)
		{
		case 0: // просмотр всех записей
			show_products();
			break;
		case 1: // добавление новой
			add_new_product();
			system("pause");
			break;
		case 2: // удаление
			delete_product();
			system("pause");
			break;
		case 3: // редактирование
			edit_product_menu_start();
			system("pause");
			break;
		case 4: // индивидуалка
			individual_task();
			system("pause");
			break;
		case 5: // поиск по названию
			find_by_name();
			system("pause");
			break;
		case 6: // поиск по имени регистрировавшего
			find_by_reg_name();
			system("pause");
			break;
		case 7: // поиск по дате
			find_by_data();
			system("pause");
			break;
		case 8: // сортировка по имени
			sort_by_name();
			system("pause");
			break;
		case 9: // сортировка по цене
			sort_by_price_to_higher();
			system("pause");
			break;
		case 10: // сортировка количеству
			sort_by_amount_to_higher();
			system("pause");
			break;
		case 11: case -1: // выход
			cout << "Выход" << endl;
			is_exit = true;
			break;

		default:
			break;
		}
	}
}

bool Session::confirm_menu_start() {
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = confirm_operation_menu->get_choise();
		switch (choise)
		{
		case 0: // да
			return true;
		case 1: case -1: // нет
			return false;
		default:
			break;
		}
	}
}

void Session::start_as_user() {
	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = user_menu->get_choise();
		switch (choise)
		{
		case 0: // просмотр всех записей
			show_products();
			break;
		case 1: // индивидуалка
			individual_task();
			system("pause");
			break;
		case 2: // поиск по названию
			find_by_name();
			system("pause");
			break;
		case 3: // поиск по имени регистрировавшего
			find_by_reg_name();
			system("pause");
			break;
		case 4: // поиск по дате
			find_by_data();
			system("pause");
			break;
		case 5: // сортировка по имени
			sort_by_name();
			system("pause");
			break;
		case 6: // сортировка по цене
			sort_by_price_to_higher();
			system("pause");
			break;
		case 7: // сортировка количеству
			sort_by_amount_to_higher();
			system("pause");
			break;
		case 8: case -1: // выход
			cout << "Выход" << endl;
			is_exit = true;
			break;

		default:
			break;
		}
	}
}



void Session::init_admin_menu() {
	main_menu = new Menu("Аккаунт Администратора",
		{ " Управление учетными записями",
		  " Работа с данными",
		  " Выход из аккаунта" });

	manage_menu = new Menu("Управление учетными записями",
		{ " Просмотр всех учетных записей",
		  " Добавление новой записи",
		  " Редактирование учетной записи",
		  " Удаление учетной записи",
		  " Подтверждение учетной записи",
		  " Блокировка учетной записи",
		  " Выход" });

	data_menu = new Menu("Работа с данными",
		{ " Просмотр всех данных",
		  " Добавление новой записи",
		  " Удаление записи",
		  " Редактирование записи",
		  " Индивидуалка ...",
		  " Поиск по названию",
		  " Поиск по ФИО зарегестрировавшего",
		  " Поиск по дате",
		  " Сортировка по названию товара",
		  " Сортировка по цене (возрастание)",
		  " Сортировка по количеству (возрастание)",
		  " Выход" });

	account_edit_menu = new Menu("Поле для редактирования", 
		{ " Логин",
		  " Пароль",
		  " Роль",
		  " Выход" });

	product_edit_menu = new Menu("Поле для редактирования",
		{ " Название",
		  " Количество",
		  " Цена",
		  " Дата поступления товара",
		  " ФИО зарегестрировавшего",
		  " Выход" });
}

void Session::init_user_menu() {
	user_menu = new Menu("Работа с данными",
		{ " Просмотр всех данных",
		  " Индивидуалка",
		  " Поиск по названию",
		  " Поиск по ФИО зарегестрировавшего",
		  " Поиск по дате",
		  " Сортировка по названию товара",
		  " Сортировка по цене (возрастание)",
		  " Сортировка по количеству (возрастание)",
		  " Выход из аккаунта" });

}

void Session::init_confirm_operation_menu() {
	user_menu = new Menu("Вы уверены?",
		{ " Да",
		  " Нет" });
}


void Session::show_accounts() {
	cout << "Все учетные записи:\n" << endl;
	account_db->show({ "Логин: ", "Роль: ", "Доступ: " }, {0, 3, 4});
	system("pause");
}

void Session::add_new_account() {
	Account account;
	
	cout << "Создание нового аккаунта." << endl;

	
	account.login = console::get_free_login(account_db);

	cout << "Пароль: ";
	string pass = console::password_format_input();
	account.salt = help::get_generated_salt();
	account.salted_hash_password = help::generate_hash(pass, account.salt);
	
	cout << "Роль: ";
	cin >> account.role;
	account.access = 1;

	account_db->push_back({ "'" + account.login + "'",
						"'" + account.salted_hash_password + "'",
						"'" + account.salt + "'",
					   to_string(account.role),
					   to_string(account.access) });

}

void Session::delete_account() {
	string login;
	cout << "Удаление аккаунта" << endl;
	cout << "Введите логин аккаунта, который хотите удалить.\n> ";
	cin >> login;
	account_db->delete_field("LOGIN='" + login + "'");
}

void Session::confirm_account() {
	string login;
	cout << "Подтверждение аккаунта." << endl;
	cout << "Введите логин\n>";
	cin >> login;
	account_db->update("ACCESS", "1", "LOGIN='" + login + "'");
}

void Session::block_account() {
	string login;
	cout << "Блокировка аккаунта." << endl;
	cout << "Введите логин\n>";
	cin >> login;
	account_db->update("ACCESS", "0", "LOGIN='" + login + "'");
}

void Session::edit_account_menu_start() {
	string login;
	cout << "Введите логин аккаунта для редактирования\n>";
	cin >> login;


	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = account_edit_menu->get_choise();
		switch (choise)
		{
		case 0: // Логин
			edit_login(&login);
			break;
		case 1: // пароль
			edit_password(login);
			break;
		case 2: // роль 
			edit_role(login);
			break;
		case 3: case -1: // выход
			cout << "Выход." << endl;
			is_exit = true;
			break;

		default:
			break;
		}
	}
}

void Session::edit_login(string *login) {
	string new_login = console::get_free_login(account_db);
	account_db->update("LOGIN", "'" + new_login + "'", "LOGIN='" + *login + "'");
	*login = new_login;
}

void Session::edit_password(string login) {
	cout << "Пароль: ";
	string pass = console::password_format_input();
	string salt = help::get_generated_salt();
	string hash = help::generate_hash(pass, salt);

	account_db->update("HASH", "'" + hash + "'", "LOGIN='" + login + "'");
	account_db->update("SALT", "'" + salt + "'", "LOGIN='" + login + "'");
}

void Session::edit_role(string login) {
	string new_role;
	cout << "Новая роль: ";
	cin >> new_role;
	account_db->update("ROLE", new_role, "LOGIN='" + login + "'");

}




void Session::show_products() {
	cout << "Все товары:\n" << endl;
	product_db->show({ "Название: ", "Количество: ", "Цена: ", "Дата поступления: ", "ФИО зарегестрировавшего: " }, { 0, 1, 2, 3, 4 });
	system("pause");
}

void Session::add_new_product() {
	Product product;
	cout << "Добавление нового продукта." << endl;


	cout << "Название товара: ";
	cin >> product.name;
	cout << "Количество товаров: ";
	cin >> product.amount;
	cout << "Цена товара: ";
	cin >> product.price;
	cout << "Дата поступления на склад: ";
	(cin >> product.date).get();
	cout << "ФИО зарегестрировавшего: ";
	getline(cin, product.reg_name);

	product_db->push_back({ "'" + product.name + "'",
						to_string(product.amount),
						"'" + to_string(product.price) + "'",
					    "'" + product.date + "'",
					    "'" + product.reg_name + "'" });

}

void Session::delete_product() {
	string name;
	cout << "Удаление продукта" << endl;
	cout << "Введите название продукта, который хотите удалить.\n> ";
	cin >> name;
	product_db->delete_field("NAME='" + name + "'");
}

void Session::edit_product_menu_start() {
	string name;
	cout << "Введите название продукта для редактирования\n>";
	cin >> name;


	int choise = 0;
	bool is_exit = false;
	while (!is_exit) {
		choise = product_edit_menu->get_choise();
		switch (choise)
		{
		case 0: // название
			edit_name(&name);
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
	cout << "Новое название: ";
	cin >> new_name;
	product_db->update("NAME", "'" + new_name + "'", "NAME='" + *name + "'");
	*name = new_name;
}

void Session::edit_amount(string name) {
	string amount;
	cout << "Новое количество: ";
	cin >> amount;
	product_db->update("AMOUNT", "'" + amount + "'", "NAME='" + name + "'");
}

void Session::edit_price(string name) {
	int price;
	cout << "Новая цена: ";
	cin >> price;
	product_db->update("PRICE", "'" + to_string(price) + "'", "NAME='" + name + "'");
}

void Session::edit_data(string name) {
	string data;
	cout << "Новуая дата: ";
	cin >> data;
	product_db->update("DATE", "'" + data + "'", "NAME='" + name + "'");
}

void Session::edit_reg_name(string name) {
	string reg_name;
	cout << "Новое ФИО регестрировавшего: ";
	cin >> reg_name;
	product_db->update("REG_NAME", "'" + reg_name + "'", "NAME='" + name + "'");
}

void Session::individual_task() {
	int mounth_amount, price;
	cout << "Количество месяцев: ";
	cin >> mounth_amount;
	cout << "Стоимость: ";
	cin >> price;
	string data =  product_db->date_mounhth_befor(to_string(mounth_amount));
	cout << "\nДата: " << data << "\n" << endl;
	product_db->show("SELECT * FROM ", " WHERE DATE > '" + data + "' AND PRICE > '" + to_string(price) + "' ORDER BY NAME ASC;",
		{ "Название: ", "Цена: ", "Дата поступления: " }, { 0, 2, 3 });
}

void Session::find_by_name() {
	string name;
	cout << "Введите название или его часть для поиска\n>";
	cin >> name;
	product_db->find_and_show("NAME", "*" + name + "*",
		{ "Название: ", "Количество: ", "Цена: ", "Дата поступления: ", "ФИО зарегестрировавшего: " }, { 0, 1, 2, 3, 4 });
}

void Session::find_by_reg_name() {
	string name;
	cout << "Введите ФИО зарегестрировавшего или его часть для поиска\n>";
	cin >> name;
	product_db->find_and_show("REG_NAME", "*" + name + "*",
		{ "Название: ", "Количество: ", "Цена: ", "Дата поступления: ", "ФИО зарегестрировавшего: " }, { 0, 1, 2, 3, 4 });
}

void Session::find_by_data() {
	string data;
	cout << "Поиск по дате. Вы можете использовать знак * для обозначения неизвестных искомых (Пример: 12.05.*, *.*.2021)" << endl;
	cout << "Дата: ";
	cin >> data;
	cout << endl;
	product_db->find_and_show("DATE", data,
		{ "Название: ", "Количество: ", "Цена: ", "Дата поступления: ", "ФИО зарегестрировавшего: " }, { 0, 1, 2, 3, 4 });
}

void Session::sort_by_name() {
	product_db->sort("NAME ASC", 
		{ "Название: ", "Количество: ", "Цена: ", "Дата поступления: ", "ФИО зарегестрировавшего: " }, { 0, 1, 2, 3, 4 });
}

void Session::sort_by_price_to_higher() {
	product_db->sort("PRICE ASC",
		{ "Название: ", "Количество: ", "Цена: ", "Дата поступления: ", "ФИО зарегестрировавшего: " }, { 0, 1, 2, 3, 4 });
}

void Session::sort_by_amount_to_higher() {
	product_db->sort("AMOUNT ASC",
		{ "Название: ", "Количество: ", "Цена: ", "Дата поступления: ", "ФИО зарегестрировавшего: " }, { 0, 1, 2, 3, 4 });
}


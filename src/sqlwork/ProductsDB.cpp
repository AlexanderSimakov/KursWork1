#include "ProductsDB.h"

const string ProductsDB::DATABASE_FILENAME;
const string ProductsDB::DATABASE_NAME;
const string ProductsDB::NAME = "NAME";
const string ProductsDB::AMOUNT = "AMOUNT";
const string ProductsDB::PRICE = "PRICE";
const string ProductsDB::DATE = "DATE";
const string ProductsDB::REGISTRANT = "REG_NAME";


ProductsDB::ProductsDB() { }

ProductsDB::ProductsDB(SQLWork *db){ this->db = db; }

void ProductsDB::init()
{
    db = new SQLWork(DATABASE_FILENAME);

    db->open();
	db->create_table_if_not_exists({ SQL_cell{ NAME,     "TEXT PRIMARY KEY NOT NULL"},
				SQL_cell{ AMOUNT,   "INT NOT NULL"},
				SQL_cell{ PRICE,    "INT NOT NULL"},
				SQL_cell{ DATE,     "TEXT NOT NULL"},
				SQL_cell{ REGISTRANT, "TEXT NOT NULL"} },
		        DATABASE_NAME);
}

void ProductsDB::show_table(string sql_end)
{
	db->show_table("SELECT * FROM ", " " + sql_end,
		{ "         name", "amount", "  price", "date", "    name of registrant" },
		{ 0, 1, 2, 3, 4 },
		{ 28, 13, 12, 19, 35 });
}

void ProductsDB::show_table()
{
    ConsoleOut::show_title("products", "                                          ");
    show_table(";");
	cout << endl;
}

void ProductsDB::add_new(Product product)
{
    db->push_back({ "'" + product.name + "'",
		to_string(product.amount),
		"'" + to_string(product.price) + "'",
		"'" + product.date + "'",
		"'" + product.name_of_registrant + "'" });
}

void ProductsDB::_delete(string name)
{
	db->delete_field(NAME + "='" + name + "'");
}

void ProductsDB::update_name(string name, string new_name)
{
	db->update(NAME, "'" + new_name + "'", NAME + "='" + name + "'");
}

void ProductsDB::update_amount(string name, int amount)
{
	db->update(AMOUNT, "'" + to_string(amount) + "'", NAME + "='" + name + "'");
}

void ProductsDB::update_price(string name, int price)
{
	db->update(PRICE, "'" + to_string(price) + "'", NAME + "='" + name + "'");
}

void ProductsDB::update_date(string name, string date)
{
	db->update(DATE, "'" + date + "'", NAME + "='" + name + "'");
}

void ProductsDB::update_registrant(string name, string registrant)
{
	db->update(REGISTRANT, "'" + registrant + "'", NAME + "='" + name + "'");
}

void ProductsDB::find_by_name(string name)
{
    show_table("WHERE " + NAME + " GLOB '*" + name + "*';");
	ConsoleOut::pause();
}

void ProductsDB::find_by_registrant(string registrant)
{
    show_table("WHERE " + REGISTRANT + " GLOB '*" + registrant + "*';");
	ConsoleOut::pause();
}

void ProductsDB::find_by_date(string date)
{
    show_table("WHERE " + DATE + " GLOB '" + date + "';");
	ConsoleOut::pause();
}
    
void ProductsDB::show_sorted_by_name()
{
    ConsoleOut::show_title("Products sorted by name", "\t", "\n\n");
	show_table("ORDER BY " + NAME + " ASC ;");
    cout << endl;
	ConsoleOut::pause();
}

void ProductsDB::show_sorted_by_price_to_higher()
{
    ConsoleOut::show_title("Products sorted by price (to higher)", "\t", "\n\n");
	show_table("ORDER BY " + PRICE + " ASC ;");
    cout << endl;
	ConsoleOut::pause();
}

void ProductsDB::show_sorted_by_amount_to_higher()
{
    ConsoleOut::show_title("products sorted by amount (to higher)", "\t", "\n\n");
	show_table("ORDER BY " + AMOUNT + " ASC ;");
    cout << endl;
	ConsoleOut::pause();
}

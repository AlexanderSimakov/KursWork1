#pragma once
#include "../SQLWORK.hpp"
#include <string>
#include "../../basic/Console/ConsoleOut.hpp"
#include "../../basic/Product/Product.hpp"

using namespace std;

class ProductsDB
{
public:
    ProductsDB();
    ProductsDB(SQLWork *db);
    void init();
    void close();

    void show_table();
    void add_new(Product product);
    void _delete(string name);
    void update_name(string name, string new_name);
    void update_amount(string name, int amount);
    void update_price(string name, int price);
    void update_date(string name, string date);
    void update_registrant(string name, string registrant);

    void find_by_name(string name);
    void find_by_registrant(string registrant);
    void find_by_date(string date);
    
    void show_sorted_by_name();
    void show_sorted_by_price_to_higher();
    void show_sorted_by_amount_to_higher();

    bool is_product_exists(string name);
    int get_amount(string name);
    int get_price(string name);
    string get_date(string name);
    string get_registrant(string name);

    SQLWork *db;

private:
    static const string DATABASE_FILENAME;
    static const string DATABASE_NAME;
    static const string NAME;
    static const string AMOUNT;
    static const string PRICE;
    static const string DATE;
    static const string REGISTRANT;

    void show_table(string sql_end);
};

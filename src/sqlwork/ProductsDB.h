#pragma once
#include "SQLWORK.h"
#include <string>

using namespace std;

class ProductsDB
{
public:
    ProductsDB();
    ProductsDB(SQLWork *db);
    void init();

    void show_table();
    void add_new();
    void _delete();
    void update_name();
    void update_amount();
    void update_price();
    void update_date();
    void update_registrant();

    void find_by_name();
    void find_by_registrant();
    void find_by_date();
    
    void show_sorted_by_name();
    void show_sorted_by_price_to_higher();
    void show_sorted_by_amount_to_higher();

private:
    static const string DATABASE_FILENAME;
    static const string DATABASE_NAME;
    static const string NAME;
    static const string AMOUNT;
    static const string PRICE;
    static const string DATE;
    static const string REGISTRANT;
};

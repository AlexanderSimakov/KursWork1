#pragma once
#include <string>

using namespace std;

class Product
{
public:
    Product();
    Product(string name, int amount, int price, string date, string registrant);

    void set_name(string name);
    void set_amount(int amount);
    void set_price(int price);
    void set_date(string date);
    void set_registrant(string registrant);

    string get_name();
    int get_amount();
    int get_price();
    string get_date();
    string get_registrant();

private:
    string name;
    int amount;
    int price;
    string date;
    string registrant;
};

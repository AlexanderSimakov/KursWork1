#include "Product.h"

Product::Product(){ }

Product::Product(string name, int amount, int price, string date, string registrant)
{
    this->name = name;
    this->amount = amount;
    this->price = price;
    this->date = date;
    this->registrant = registrant; 
}

void Product::set_name(string name)
{
    this->name = name;
}

void Product::set_amount(int amount)
{
    this->amount = amount;
}

void Product::set_price(int price)
{
    this->price = price;
}

void Product::set_date(string date)
{
    this->date = date;
}

void Product::set_registrant(string registrant)
{
    this->registrant = registrant;
}

string Product::get_name()
{
    return name;
}

int Product::get_amount()
{
    return amount;
}

int Product::get_price()
{
    return price;
}

string Product::get_date()
{
    return date;
}

string Product::get_registrant()
{
    return registrant;
}

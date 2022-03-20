#pragma once
#include <iostream>

using namespace std;

const string PRODUCT_DATABASE_FILENAME = "product.db";
const string PRODUCT_DATABASE_NAME = "PRODUCTSLIST";

struct Product
{
	string name = "";
	int amount = 0;
	int price = 0;
	string date = "";
	string name_of_registrant = "";
};



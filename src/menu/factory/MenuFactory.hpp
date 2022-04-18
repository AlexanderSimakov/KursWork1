#pragma once
#include <string>
#include "../menu.hpp"

class MenuFactory
{
public:
    static Menu* create_main_menu();
    static Menu* create_admin_menu();
    static Menu* create_accounts_manage_menu();
    static Menu* create_products_manage_menu();
    static Menu* create_user_menu();
    static Menu* create_account_edit_menu();
    static Menu* create_product_edit_menu();
};

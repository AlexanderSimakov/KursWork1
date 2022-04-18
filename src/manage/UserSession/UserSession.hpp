#pragma once
#include "../session.hpp"
#include "../../basic/Account/Account.hpp"
#include "../../menu/menu.hpp"
#include "../../menu/factory/MenuFactory.hpp"

class UserSession : Session
{
public:
    UserSession(ProductsDB* products_db);
    void start();
private:
    Menu* user_menu;
};

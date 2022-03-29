#pragma once
#include "../session.h"
#include "../../basic/Account/Account.h"
#include "../../menu/menu.h"
#include "../../menu/factory/MenuFactory.h"

class UserSession : Session
{
public:
    UserSession(ProductsDB* products_db);
    void start();
private:
    Menu* user_menu;
};

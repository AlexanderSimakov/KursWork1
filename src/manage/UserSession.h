#pragma once
#include "session.h"
#include "../basic/Account/Account.h"
#include "../menu/menu.h"
#include "../menu/factory/MenuFactory.h"

class UserSession : Session
{
public:
    UserSession(ProductsDB* productsDB);
    void start();
private:
    Menu* user_menu;
};

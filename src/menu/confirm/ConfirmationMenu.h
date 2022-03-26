#pragma once
#include <iostream>
#include "../menu.h"

using namespace std;

class ConfirmationMenu
{
public:
    static bool confirm(string title = "Are you sure?");    
private:
	static Menu menu;
};


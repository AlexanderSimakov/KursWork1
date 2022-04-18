#pragma once
#include <iostream>
#include "../menu.hpp"

using namespace std;

class ConfirmationMenu
{
public:
    static bool confirm(string title = "Are you sure?");    
private:
	static Menu menu;
};


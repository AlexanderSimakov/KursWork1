#include "ConfirmationMenu.h"

Menu ConfirmationMenu::menu = Menu({" Yes", " No"});

bool ConfirmationMenu::confirm(string title){
    menu.set_title(title);
    while (true) 
	{
		switch (menu.get_num_of_choisen_line())
		{
		case 0: return true;
		case 1: return false;
		case -1: default: break;
		}
	}
}  

#pragma once
#include "menu.h"

Menu::Menu() 
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}

Menu::Menu(vector<string> lines) 
{
	Menu();
	this->lines = lines;
}

Menu::Menu(string title, vector<string> lines) 
{
	Menu();
	this->title = title;
	this->lines = lines;
}

int Menu::get_num_of_choisen_line() 
{
	clear();
	print_title();
	print_lines();

	if (is_start_with_first_line) num_of_choisen_line = 0;

	int pressed_key = 0;
	while (true) 
	{
		print_pointer();
		pressed_key = (int)ConsoleOut::getchar();

		if (pressed_key == Buttons::ENTER) 
		{
			clear();
			return num_of_choisen_line;
		}
		else if (pressed_key == Buttons::KEU_UP && num_of_choisen_line > 0) 
		{
			num_of_choisen_line--;
		}
		else if (pressed_key == Buttons::KEY_DOWN && num_of_choisen_line < lines.size() - 1) 
		{
			num_of_choisen_line++;
		}
		else if (pressed_key == Buttons::ESC) 
		{
			clear();
			return -1;
		}
	}
}

void Menu::print_title() 
{
	if (title.size()) cout << title << endl;
}

void Menu::print_lines() 
{
	for (int i = 0; i < lines.size(); i++)  cout << " " << lines[i] << endl;
}

void Menu::print_pointer() 
{
	int add = 0;
	if (title.size()) add = 1;
	for (int i = 0; i < lines.size(); i++) 
	{
		if (num_of_choisen_line == i) 
		{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
			FillConsoleOutputCharacter(std_handle, (TCHAR)'>', 1, { 0, (SHORT)(i + add) }, &cWrittenChars);
		else{
			FillConsoleOutputCharacter(std_handle, (TCHAR)' ', 1, { 0, (SHORT)(i + add) }, &cWrittenChars);
		}
#elif __linux__
			printf("\033[%d;%dH>", i + add + 1, 0);
			printf("\033[%d;%dH", 20, 30);
		}
		else {
			printf("\033[%d;%dH ", i + add + 1, 0);
			printf("\033[%d;%dH", 20, 30);
		}
#endif
	}
}

void Menu::add_line(string line) 
{
	lines.push_back(line);
}

void Menu::set_lines(vector<string> lines) 
{
	this->lines = lines;
}

void Menu::set_title(string title) 
{
	this->title = title;
}

void Menu::set_start_with_first_line(bool is_start_with_first_line) 
{
	this->is_start_with_first_line = is_start_with_first_line;
}

void Menu::set_pointer_to_start() 
{
	num_of_choisen_line = 0;
}

void Menu::clear()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	system("cls");
#elif __linux__
	system("clear");
#endif
}

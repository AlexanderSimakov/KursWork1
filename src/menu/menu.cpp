#pragma once
#include "src/menu/menu.h"

Menu::Menu() {
	std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

Menu::Menu(vector<string> lines) {
	std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	this->lines = lines;
}

Menu::Menu(string title, vector<string> lines) {
	std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	this->title = title;
	this->lines = lines;
}

int Menu::get_num_of_choisen_line() {
	char pressed_key = 0;
	system("cls");
	print_title();
	print_lines();

	if (is_start_with_first_line) {
		num_of_choisen_line = 0;
	}

	while (true) {
		print_pointer();
		pressed_key = _getch();

		if ((int)pressed_key == Buttons::ENTER) {
			system("cls");
			return num_of_choisen_line;
		}
		else if ((int)pressed_key == Buttons::KEU_UP && num_of_choisen_line > 0) {
			num_of_choisen_line--;
		}
		else if ((int)pressed_key == Buttons::KEY_DOWN && num_of_choisen_line < lines.size() - 1) {
			num_of_choisen_line++;
		}
		else if ((int)pressed_key == Buttons::ESC) {
			system("cls");
			return -1;
		}
	}
}

void Menu::print_title() {
	if (title.size()) cout << title << std::endl;
}

void Menu::print_lines() {
	for (int i = 0; i < lines.size(); i++) {
		cout << " " << lines[i] << endl;
	}
}

void Menu::print_pointer() {
	int add = 0;
	if (title.size()) add = 1;
	for (int i = 0; i < lines.size(); i++) {
		if (num_of_choisen_line == i) {
			FillConsoleOutputCharacter(std_handle, (TCHAR)'>', 1, { 0, (SHORT)(i + add) }, &cWrittenChars);
		}
		else {
			FillConsoleOutputCharacter(std_handle, (TCHAR)' ', 1, { 0, (SHORT)(i + add) }, &cWrittenChars);
		}
	}
}

void Menu::add_line(string line) {
	lines.push_back(line);
}

void Menu::set_lines(vector<string> lines) {
	this->lines = lines;
}

void Menu::set_title(string title) {
	this->title = title;
}

void Menu::set_start_with_first_line(bool is_start_with_first_line) {
	this->is_start_with_first_line = is_start_with_first_line;
}

void Menu::set_pointer_to_start() {
	num_of_choisen_line = 0;
}

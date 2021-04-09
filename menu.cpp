#pragma once
#include "menu.h"

Menu::Menu() {
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
}

Menu::Menu(vector<string> lines) {
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	this->lines = lines;
}

Menu::Menu(string title, vector<string> lines) {
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	this->title = title;
	this->lines = lines;
}

int Menu::get_choise() {
	char key_pressed = 0;
	//num_of_choisen_line = 0;
	system("cls");
	print_title();
	print_lines();

	while (true) {
		print_pointer();
		key_pressed = _getch();

		if ((int)key_pressed == 13) {
			system("cls");
			return num_of_choisen_line;
		}
		else if ((int)key_pressed == 72 && num_of_choisen_line > 0) {
			num_of_choisen_line--;
		}
		else if ((int)key_pressed == 80 && num_of_choisen_line < lines.size() - 1) {
			num_of_choisen_line++;
		}
		else if ((int)key_pressed == 27) {
			system("cls");
			return -1;
		}
	}
	system("cls");
	return num_of_choisen_line;
}

// добавляет строку в меню
void Menu::add_line(string line) {
	lines.push_back(line);
}

// добавляет сразу весь список строк
void Menu::set_lines(vector<string> lines) {
	this->lines = lines;
}

// устанавливает загаловок меню
void Menu::set_title(string title) {
	this->title = title;
}

void Menu::print_lines() {
	for (int i = 0; i < lines.size(); i++) {
		cout << " " << lines[i] << endl;
	}
}

void Menu::print_title() {
	if (title.size()) cout << title << std::endl;
}

// выводит указатель на выбранную строку
void Menu::print_pointer() {
	int add = 0;
	if (title.size()) add = 1;
	for (int i = 0; i < lines.size(); i++) {
		if (num_of_choisen_line == i) {
			FillConsoleOutputCharacter(wHnd, (TCHAR)'>', 1, { 0, (SHORT)(i + add) }, &cWrittenChars);
		}
		else {
			FillConsoleOutputCharacter(wHnd, (TCHAR)' ', 1, { 0, (SHORT)(i + add) }, &cWrittenChars);
		}
	}
}
#pragma once
#include "menu.h"

Menu::Menu() {
	std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

// инициализация меню с заданными строками
Menu::Menu(vector<string> lines) {
	std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	this->lines = lines;
}

// инициализация меню с заданными строками и заголовком
Menu::Menu(string title, vector<string> lines) {
	std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	this->title = title;
	this->lines = lines;
}

// возвращает номер выбранной строки
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

// выводит на экран заголовок, если он задан
void Menu::print_title() {
	if (title.size()) cout << title << std::endl;
}

// выводит на экран строки меню
void Menu::print_lines() {
	for (int i = 0; i < lines.size(); i++) {
		cout << " " << lines[i] << endl;
	}
}

// выводит указатель на выбранную строку
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

// true, и указатель выбранной строки будет всегда при запуске меню стоять на первом месте
void Menu::set_start_with_first_line(bool is_start_with_first_line) {
	this->is_start_with_first_line = is_start_with_first_line;
}

// устанавливает указатель на первую строку
void Menu::set_pointer_to_start() {
	num_of_choisen_line = 0;
}

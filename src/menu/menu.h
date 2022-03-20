#pragma once
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <iostream>

using namespace std;

enum Buttons {
	ENTER = 13,
	KEU_UP = 72,
	KEY_DOWN = 80,
	ESC = 27
};

class Menu {
public:
	Menu();
	Menu(vector<string> lines);
	Menu(string title, vector<string> lines);

	int get_num_of_choisen_line();
	void add_line(string line);
	void set_lines(vector<string> lines);
	void set_title(string title);
	void set_start_with_first_line(bool is_start_with_first_line);
	void set_pointer_to_start();

private:
	bool is_start_with_first_line = false;
	int num_of_choisen_line = 0;
	vector<string> lines;
	string title;
	HANDLE std_handle;
	DWORD cWrittenChars;

	void print_lines();
	void print_title();
	void print_pointer();
};
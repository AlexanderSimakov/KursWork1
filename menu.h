#pragma once
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <iostream>

using namespace std;

class Menu {
public:
	Menu();
	Menu(vector<string> lines);
	Menu(string title, vector<string> lines);

	int get_choise();
	void add_line(string line);
	void set_title(string title);
	void set_lines(vector<string> lines);

private:
	int num_of_choisen_line;
	vector<string> lines;
	string title;
	HANDLE wHnd;
	DWORD cWrittenChars;

	void print_lines();
	void print_title();
	void print_pointer();
};
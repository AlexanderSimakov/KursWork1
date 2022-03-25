#pragma once
#include "ConsoleOut.h"

void ConsoleOut::pause(){
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    system("pause");
#elif __linux__
    cout << "Press any key to continue..." << endl;
    ConsoleOut::getchar();
#endif
}

char ConsoleOut::getchar()
{	
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	return _getch();
#elif __linux__
	initTermios();
	char ch = std::getchar();
	resetTermios();
	return ch;
#endif
}

void ConsoleOut::clear(){
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	system("cls");
#elif __linux__
	system("clear");
#endif
}

#if __linux__
	void ConsoleOut::initTermios() 
	{
  		tcgetattr(0, &old);
  		current = old;
  		current.c_lflag &= ~ICANON;
    	current.c_lflag &= ~ECHO;
  		tcsetattr(0, TCSANOW, &current);
	}

	void ConsoleOut::resetTermios(void) 
	{
  		tcsetattr(0, TCSANOW, &old);
	}
#endif

void ConsoleOut::show_error(string message, string pref_line, string post_line) {
	set_color(cons::Color::Red);
	cout << pref_line + "<-- " + message + " -->" + post_line;
	set_default_color();
}

void ConsoleOut::show_title(string title, string pref_line, string post_line) {
	set_color(cons::Color::Yellow);
	cout << pref_line + "<-- " + title + " -->" + post_line;
	set_default_color();
}

void ConsoleOut::show_info(string info, string pref_line, string post_line) {
	set_color(cons::Color::Green);
	cout << pref_line + "<-- " + info + " -->" + post_line;
	set_default_color();
}

void ConsoleOut::set_color(cons::Color color) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((30 << 4) | color));
#elif __linux__
	cout << "\033[" << color << "m";
#endif
}

void ConsoleOut::set_default_color(){
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((Color::Black << 4) | Color::White));
#elif __linux__
	cout << "\033[0m";
#endif
}
#pragma once
#include <string>
#include <iostream>

#if __linux__
#include <termios.h>
#include <stdio.h>
#endif

using namespace std;

#if __linux__
static struct termios old, current;
#endif

namespace cons {
	enum Color {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
 		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Yellow = 14,
		White = 15  
#elif __linux__
		Black = 30,
		Red = 31,
		Green = 32,
		Yellow = 33,
		Blue = 34,
		Magenta = 35,
		Cyan = 36,
		White = 37,
#endif
	};
}

class ConsoleOut
{
private:

#if __linux__
	static void initTermios();
	static void resetTermios(void);
	
#endif

public:
    static void pause();
    static char getchar();
    static void clear();
    
    static void show_error(string message, string pref_line = "\t", string post_line = "\n");
	static void show_title(string title, string pref_line = "\t", string post_line = "\n");
	static void show_info(string info, string pref_line = "\t", string post_line = "\n");
	static void set_color(cons::Color color);
	static void set_default_color();
};

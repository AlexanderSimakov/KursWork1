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
};

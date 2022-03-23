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

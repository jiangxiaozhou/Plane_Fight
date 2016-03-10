#include <iostream>
#include "common.h"

void setpos(COORD pos){                     //设置光标
	HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

void setpos(int x, int y){                     //设置光标
	HANDLE hOut;
	COORD pos = {x, y};
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

void HideCursor(){                           //隐藏光标
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
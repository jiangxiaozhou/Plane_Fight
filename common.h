#ifndef __COMMON_H__
#define __COMMON_H__

#include <windows.h>
#include <conio.h>

struct Body {
	COORD left_top;
	COORD right_buttom;
};

void setpos(int,int);
void setpos(COORD);
void HideCursor();

#endif
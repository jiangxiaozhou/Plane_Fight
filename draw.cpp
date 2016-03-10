#include <iostream>
#include "common.h"
using namespace std;

void DrawRow(int x1,int y1, int x2, int y2, char ch) {
	if ((y2 == y1) && (x1 <= x2)) {
		setpos(x1,y1);
		for (; x1 <= x2; x1++) 
			cout << ch;
	} else cout << "Error when draw row!" << endl;
}
			
void DrawCol(int x1, int y1, int x2, int y2, char ch) {
	if((x1 == x2) && (y1 <= y2)) {
		while (y1 <= y2) {
			setpos(x1,y1);
			cout << ch;
			y1++;
		}
	} else cout << "Errot when draw col!" << endl;
}

void DrawBody(Body a,char row,char col) {
	int x1 = a.left_top.X;
	int y1 = a.left_top.Y;
	int x2 = a.right_buttom.X;
	int y2 = a.right_buttom.Y;
	DrawRow(x1,y1,x2,y1,row);
	DrawRow(x1,y2,x2,y2,row);
	DrawCol(x1,y1+1,x1,y2-1,col);
	DrawCol(x2,y1+1,x2,y2-1,col);
}

int DrawMainMemu() {
	setpos(27,2);
	cout << "ÌìÀ×¹ö¹öÖ®À×µç5";
	setpos(32,6);
	cout << "easy";
	setpos(32,8);
	cout << "hard";
	setpos(29,6);
	cout << ">>";
	int y = 6;
	Body a;
	a.left_top.X = 15;
	a.left_top.Y = 0;
	a.right_buttom.X = 55;
	a.right_buttom.Y = 12;
	DrawBody(a,'-','|');
	while(1) {
		if (_kbhit()) {
			char ch = _getch();
			switch(ch) {
			case 'w':
				if (y == 8) {
					setpos(29,8); cout << "  ";
					y = 6;
				}
				break;
			case 's':
				if (y == 6) {
					setpos(29,6); cout << "  ";
					y = 8;
				}
				break;
			}
			setpos(29, y);
			cout << ">>";
			if (ch == '\r') break;
		}
	}
	return y;
}

void Draw_Plane(COORD center_pos) {
	setpos(center_pos.X - 1, center_pos.Y);
	cout << "<$>";
}

void Cancle_Plane(COORD center_pos) {
	setpos(center_pos.X - 1, center_pos.Y);
	cout << "   ";
}

void Draw_Bullet(COORD pos) {
	setpos(pos.X, pos.Y);
	cout << '|';
}

void Draw_Enemy(COORD pos) {
	if(pos.Y == 23) {
		setpos(pos.X - 1, pos.Y);
		cout << "###";
		return;
	}
	setpos(pos.X - 1, pos.Y);
	cout << "###";
	setpos(pos.X, pos.Y + 1);
	cout << '#';
}

void Cancle_Enemy(COORD pos) {
	if(pos.Y == 23) {
		setpos(pos.X - 1, pos.Y);
		cout << "   ";
		return;
	}
	if(pos.Y == 24) {
		setpos(pos.X - 1, pos.Y);
		cout << "---";
		setpos(pos.X, pos.Y + 1);
		cout << ' ';
		return;
	}
	setpos(pos.X - 1, pos.Y);
	cout << "   ";
	setpos(pos.X, pos.Y + 1);
	cout << ' ';
}


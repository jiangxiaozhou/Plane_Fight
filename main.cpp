#include <iostream>
#include <ctime>
#include "game.h"
using namespace std;

int main() {
	HideCursor();
	srand((int)time(0));
	Game game;
	game.play();
}
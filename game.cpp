#include <iostream>
#include <cmath>
#include <ctime>
#include "game.h"
using namespace std;

extern void DrawBody(Body,char,char);
extern int DrawMainMemu();

Game::Game() {
	srand((int)time(0));
	score = 0;
	enemy_time = 0;
	enemy_diffculty = 10;	
	enemy_bullet_speed = 5;
	enemy_bullet_time = 0;
	for (int x = 0; x <= 5; x ++) {
		Enemy a;
		enemy.push_back(a);
	}
}

void Game::setrank(int i) {
	if (i == 6) enemy_diffculty = 10;
	else enemy_diffculty = 6;
}

int Game::DrawMemu() {
	return DrawMainMemu();
}

void Game::GameOver() {
	Body a;
	a.left_top.X = 15;
	a.left_top.Y = 0;
	a.right_buttom.X = 55;
	a.right_buttom.Y = 12;
	DrawBody(a,'-','|');
	setpos(30,6);
	cout << "Game Over!" << endl;
}
void Game::DrawBattlefield() {
	Body field;
	field.left_top.X = 0;
	field.left_top.Y = 0;
	field.right_buttom.X = 50;
	field.right_buttom.Y = 24;
	DrawBody(field,'-','|');
}

void Game::print_score() {
	setpos(0,25);
	cout << "»÷ÂäÊý:" << score;
}

void Game::print_HP() {
	setpos(10,25);
	cout << "HP:" << myplane.HP << ' ';
}

bool Game::JudgeCollision(Enemy enemy) {
	COORD my_pos;
	COORD ene_pos;
	my_pos = myplane.GetPosition();
	ene_pos = enemy.GetPosition();
	if ((my_pos.X == ene_pos.X) && ((my_pos.Y - 1) == ene_pos.Y)) {
		myplane.HP -= 20;
		print_HP();
		return true;
	}
	if (((my_pos.Y - 1) == ene_pos.Y) && (abs(my_pos.X - ene_pos.X) <= 1)) {
		myplane.HP -= 20;
		print_HP();
		return true;
	}
	if ((my_pos.Y == ene_pos.Y) && (abs(my_pos.X - ene_pos.X) <= 2)) {
		myplane.HP -= 20;
		print_HP();
		return true;
	}
	return false;
}

bool Game::JudgeBulletHit(Enemy enemy) {
	Bullet *head = myplane.GetBulletHead();
	COORD ene_pos = enemy.GetPosition();
	while (head != NULL) {
		if ((head -> pos.X == ene_pos.X) && ((head -> pos.Y-1) == ene_pos.Y)) {
			myplane.RemoveBullet(head);
			return true;
		}
		if ((head -> pos.Y == ene_pos.Y) && (abs(head->pos.X - ene_pos.X) <= 1 )) {
			myplane.RemoveBullet(head);
			return true;
		}
		head = head -> next;
	}
	return false;
}

void Game::JudgeMyHitByBullet() {
	COORD my_pos = myplane.GetPosition();
	for (vector<Enemy>::iterator iter = enemy.begin(); iter != enemy.end(); iter ++) {
		Bullet *p = iter->GetBulletHead();
		while(p != NULL) {
			if((p->pos.Y == my_pos.Y) && abs(p->pos.X - my_pos.X) <= 1) {
				myplane.HP -= 20;
				print_HP();
			}
			p = p->next;
		}
	}
}

void Game::JudgeEnemyInFrame() {
	if (!enemy.empty()) {
		vector<Enemy>::iterator iter = enemy.begin();
		while (iter != enemy.end()) {
			COORD ene_pos = iter->GetPosition();
			if (ene_pos.Y >= 24) {
				iter->CancleThisEnemy();
				iter = enemy.erase(iter);
			}
			else iter ++;
		}
	}
}




void Game::play() {
	setrank(DrawMemu());
	system("cls");
	DrawBattlefield();
	myplane.DrawPlane();
	print_score();
	print_HP();
	while(1) {
		Sleep(20);
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {
				myplane.CanclePlane();
				myplane.PlaneMove(ch);
				myplane.DrawPlane();
			}
			else if (ch == 'j') myplane.shoot();
			else if (ch == ' ') {
				while(1) {
					if (_kbhit()) {
						char ch = _getch();
						if (ch == ' ') break;
					}
				}
			}					
		}
		
		enemy_time++;
		if (enemy_time % (5 * enemy_diffculty) == 0) {
				Enemy a;
				enemy.push_back(a);
		}

		if (!enemy.empty()) {
			if (enemy_time % enemy_diffculty == 0) {
				for (vector<Enemy>::iterator iter = enemy.begin(); iter != enemy.end(); iter ++) {
					iter -> CancleThisEnemy();
					iter -> ThisEnemyMove();
				}
			}
			for (vector<Enemy>::iterator iter = enemy.begin(); iter != enemy.end(); iter ++)
				iter -> DrawThisEnemy();
		}

		myplane.CancleAllBullet();
		myplane.BulletMove();
		myplane.DrawBullet();

		enemy_bullet_time++;
		if ((enemy_bullet_time % (4 * enemy_diffculty) == 0) && !enemy.empty()) {
			for (vector<Enemy>::iterator iter = enemy.begin(); iter != enemy.end(); iter ++) {
				iter -> shoot();
			}
		}
		if ((enemy_bullet_time % enemy_diffculty == 0) && !enemy.empty()) {
			for (vector<Enemy>::iterator iter = enemy.begin(); iter != enemy.end(); iter ++) {
				iter -> CancleAllBullet();
				iter -> BulletMove();
			}
		}

		for (vector<Enemy>::iterator iter = enemy.begin(); iter != enemy.end(); iter ++)
			iter->DrawBullet();

		if (!enemy.empty()) {
			vector<Enemy>::iterator iter = enemy.begin();
			while (iter != enemy.end()) {
				if ((JudgeBulletHit(*iter))) {
					iter->CancleThisEnemy();
					iter->CancleAllBullet();
					iter->RemoveAllBullet();
					score ++ ;
					print_score();
					iter = enemy.erase(iter);
				}
				else iter++;
			}
		}

		if ((enemy_time % 2 == 0) && !enemy.empty()) {
			for (vector<Enemy>::iterator iter = enemy.begin(); iter != enemy.end(); iter ++)
				if (JudgeCollision(*iter)) {
					iter -> CancleThisEnemy();
					iter = enemy.erase(iter);
					if (myplane.HP <= 0) {
						myplane.DrawDestroy();
						goto L;
					}
				}
		}
		
		if ((enemy_bullet_time % enemy_diffculty == 0) && !enemy.empty())
			JudgeMyHitByBullet();
		
		if (myplane.HP <= 0) {
			myplane.DrawDestroy();
			goto L;
		}

		JudgeEnemyInFrame();
		print_score();
		print_HP();
	}

L:
	Sleep(2000);
	system("cls");
	GameOver();
	Sleep(2000);
	return;
}

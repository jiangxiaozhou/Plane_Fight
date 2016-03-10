#include "enemy.h"
#include "ctime"
#include <iostream>
#include <cassert>
using namespace std;

extern void Draw_Enemy(COORD pos);
extern void Cancle_Enemy(COORD pos);

Enemy::Enemy() {
	center_pos.Y = 2;
	center_pos.X = rand() % 47 + 2;
	bullet_head = NULL;
}

/*Enemy::~Enemy() {
	RemoveAllBullet();
}*/

void Enemy::DrawThisEnemy() {
	Draw_Enemy(center_pos);
}

void Enemy::CancleThisEnemy() {
	Cancle_Enemy(center_pos);
}

COORD Enemy::GetPosition() {
	return center_pos;
}

void Enemy::ThisEnemyMove() {
	Direction dir;
	while(1) {
		dir = (Direction) (rand() % 5);
		switch (dir) {
			case RIGHT: 
				if (center_pos.X >= 48) { continue; break; }
				center_pos.X ++; ; return;
			case LEFT: 
				if (center_pos.X <= 2) { continue; break; }
				center_pos.X -- ; return;
			case DOWN:center_pos.Y ++; return;
			case RIGHT_DOWN: 
				if (center_pos.X >= 48) { continue; break; }
				center_pos.Y ++; center_pos.X ++; return;
			case LEFT_DOWN:
				if (center_pos.X <= 2 ){ continue; break; }
				center_pos.X --; center_pos.Y ++; return;
			default:assert(0);
		}
	}
}

void Enemy::BulletMove() {
	Bullet *h = bullet_head;
	while(h != NULL) {
		if ( h -> pos.Y >= 23 ) {                   //这个节点必然在链表尾
			Bullet *q = bullet_head;
			if (bullet_head == h) {
				delete q;
				bullet_head = NULL;
				h = NULL;
			}
			else {
				while (q -> next != h) q = q -> next;
				q -> next = h -> next; 
				delete h;
			    h = NULL;
			}	
		} else {
			h -> pos.Y ++;
			h = h -> next;
		}
	}
}

void Enemy::shoot() {
	if (center_pos.Y <= 20) {
		COORD temp;
		temp.X = center_pos.X;
		temp.Y = center_pos.Y + 2;
		Bullet *p = new Bullet(temp);
		p -> next = bullet_head;
		bullet_head = p;
	}
}

void Enemy::RemoveAllBullet() {
	Bullet *p = bullet_head;
	while(p != NULL) {
		bullet_head = bullet_head -> next;
		delete p;
		p = bullet_head;
	}
}
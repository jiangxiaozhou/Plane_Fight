#include <iostream>
#include <cassert>
#include "plane.h"
using namespace std;

extern void Draw_Plane(COORD);
extern void Cancle_Plane(COORD);
extern void Draw_Bullet(COORD);

void Plane::DrawPlane() {
	Draw_Plane(center_pos);
}

void Plane::DrawDestroy() {
	setpos(center_pos.X - 1,center_pos.Y);
	cout << "烫烫";
}

void Plane::CanclePlane() {
	Cancle_Plane(center_pos);
}

Bullet *Plane::GetBulletHead() {
	return bullet_head;
}

void Plane::PlaneMove(char dir) {
	switch (dir) {
	case 'w': 
		if (center_pos.Y > 1) center_pos.Y --;
		break;
	case 'a':
		if (center_pos.X > 2) center_pos.X --;
		break;
	case 'd':
		if (center_pos.X < 48) center_pos.X ++;
		break;
	case 's':
		if (center_pos.Y < 23) center_pos.Y ++;
	default: break;
	}
}

void Plane::DrawBullet() {
	Bullet *h = bullet_head;
	while(h != NULL) {
		Draw_Bullet(h->pos);
		h = h->next;
	}
}

void Plane::BulletMove() {
	Bullet *h = bullet_head;
	while(h != NULL) {
		if ( h -> pos.Y <= 1) {                   //这个节点必然在链表尾
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
			h -> pos.Y --;
			h = h -> next;
		}
	}
}

void Plane::RemoveBullet(Bullet* p) {
	Bullet* h = bullet_head;
	if (bullet_head == p) {
		bullet_head = bullet_head -> next;
		delete h;
	} else {
		while(h -> next != p) h = h -> next;
		if (h == NULL) assert(0);
		else {
			h -> next = p -> next;
			delete p;
		}
	}
}

void Plane::shoot() {
	if (center_pos.Y != 1) {
		COORD temp;
		temp.X = center_pos.X;
		temp.Y = center_pos.Y - 1;
		Bullet *p = new Bullet(temp);
		p -> next = bullet_head;
		bullet_head = p;
	}
}

void Plane::CancleBullet(COORD a) {
	setpos(a);
	cout << ' ';
}

void Plane::CancleAllBullet() {
	Bullet *p = bullet_head;
	while(p != NULL) {
		setpos(p->pos);
		cout << ' ';
		p = p -> next;
	}
}

COORD Plane::GetPosition() {
	return center_pos;
}
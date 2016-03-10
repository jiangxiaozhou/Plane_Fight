#ifndef __PLANE_H__
#define __PLANE_H__

#include "common.h"

struct Bullet {
	COORD pos;
	Bullet *next;
	Bullet(COORD a) {
		pos = a;
		next = NULL;
	}
};

class Plane {
protected :
	COORD center_pos;
    Bullet *bullet_head;
public:
	int HP;
	Plane() {
		center_pos.X = 25;
		center_pos.Y = 22;
		bullet_head = NULL;
		HP = 100;
	}
	void DrawPlane();
	void DrawDestroy();
	void CanclePlane();
	void PlaneMove(char dir);
	virtual void shoot();
	void DrawBullet();
	void CancleBullet(COORD a);
	void CancleAllBullet();
	virtual void BulletMove();
	void RemoveBullet(Bullet* p);
	COORD GetPosition();
	Bullet *GetBulletHead();
};

#endif
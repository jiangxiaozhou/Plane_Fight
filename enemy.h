#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "common.h"
#include "plane.h"

enum Direction { DOWN = 0, LEFT = 1, LEFT_DOWN, RIGHT, RIGHT_DOWN };

class Enemy : public Plane {
//private:
	//COORD center_pos;
public:
	Enemy();
//	~Enemy();
	void DrawThisEnemy();
	void CancleThisEnemy();
	void ThisEnemyMove();
	void shoot();
	void BulletMove();
	void RemoveAllBullet();
	COORD GetPosition();
};

#endif
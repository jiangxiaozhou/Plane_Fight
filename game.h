#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include "common.h"
#include "plane.h"
#include "enemy.h"


class Game {
private:
	int score;
	int enemy_time;
	int enemy_diffculty;
	int enemy_bullet_speed;
	int enemy_bullet_time;
public:
	Plane myplane;
	std::vector<Enemy> enemy;

	Game();
	int DrawMemu();
	void DrawBattlefield();
	void print_score();
	void print_HP();
	void play();
	void setrank(int i);
	bool JudgeCollision(Enemy enemy);
	bool JudgeBulletHit(Enemy enemy);
	void JudgeMyHitByBullet();
	void JudgeEnemyInFrame();
	void GameOver();
};

#endif
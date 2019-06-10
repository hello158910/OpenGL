#include "CObstacle.h"
#include <time.h>

CObstacle::CObstacle() {
	_enemyT = vec3(-10.5f, 10.5f, 0);
	_color = vec4(0.9f, 0.5f, 0.7f, 1.0f);
	CreateEnemy();
}

CObstacle::~CObstacle(){}

void CObstacle::Move(float dt) {
	srand((unsigned)time(NULL));

	_enemyT.x += 2.0f*dt;
	_enemyT.y-=7.5f*dt;
	if (_enemyT.y <= -12.0f) { _enemyT.y = 1.0f; }
	_mxEnemyT = Translate(_enemyT);
	_enemy->SetTRSMatrix(_mxEnemyT);
}
//void CObstacle::Update(float dt) {};
void CObstacle::Update(float dt){
	Move(dt);
}

void CObstacle::Attack(float dt){}

void CObstacle::DrawBullets(){}
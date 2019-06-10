#include "CShooter.h"
#include <math.h>

#define BULLET_NUM 50
CShooter::CShooter() {
	_enemyT = vec3(10.5f, 10.5f, 0);
	_color = vec4(0.8f, 0.5f, 0.7f, 1.0f);
	CreateEnemy();

	_freeNum = BULLET_NUM;
	_usedNum = 0;
	_bullets = new CBullet[BULLET_NUM];
	//_bullets = new CBullet;
	_bullets->SetPos(-4.5f, 5.5f);
	for (int i = 0; i < BULLET_NUM; i++) {
		_freeList.push_front(&_bullets[i]);
	}
}

void CShooter::Move(float dt){
	_count += dt;
	_enemyT.x += 5*cosf(_count)*dt;
	_enemyT.y -= (3*sinf(_count)+0.2f)*dt;
	_mxEnemyT = Translate(_enemyT);
	_enemy->SetTRSMatrix(_mxEnemyT);
}
void CShooter::Update(float dt){
	Move(dt);

	//bullets
	CBullet* get;
	if (_freeNum != 0) {
		get = _freeList.front();
		_freeList.pop_front();
		_inUsedList.push_front(get);
		_freeNum--; _usedNum++;
	}
	Attack(dt);
}
void CShooter::Attack(float dt){
	//_bullets->Move(0, -2.0f*dt);
	std::list <CBullet*>::iterator it;
	for (it = _inUsedList.begin(); it != _inUsedList.end(); it++) {
		(*it)->Move(0,-2.0f*dt);
	}
}

void CShooter::DrawBullets(){}
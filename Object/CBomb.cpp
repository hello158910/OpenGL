#include "CBomb.h"
#include <math.h>
#define BULLET_NUM 20

CBomb::CBomb() {
	_enemyT = vec3(10.5f, 10.5f, 0);
	_color = vec4(0.8f, 1.5f, 1.7f, 1.0f);
	CreateEnemy();

	_freeNum = BULLET_NUM;
	_usedNum = 0;
	_bullets = new CBullet[BULLET_NUM];
	
	//_bullets = new CBullet;
	/*for (int i = 0; i < BULLET_NUM; i++) {
	_freeList.push_front(&_bullets[i]);
	}*/
}

void CBomb::Move(float dt){
	_count += dt;
	_enemyT.x -= 5.0f*dt;
	_enemyT.y += sinf(3.5f*_count)*dt;
	_mxEnemyT = Translate(_enemyT);
	_enemy->SetTRSMatrix(_mxEnemyT);
}
void CBomb::Update(float dt){
	Move(dt);
	
	//bullets
	/*CBullet* get;
	if (_freeNum != 0) {
	get = _freeList.front();
	_freeList.pop_front();
	_inUsedList.push_front(get);
	_freeNum--; _usedNum++;
	}*/
	Attack(dt);
}
void CBomb::Attack(float dt){
	/*std::list <CBullet*>::iterator it;
	for (it = _inUsedList.begin(); it != _inUsedList.end(); it++) {
		(*it)->Move(0, (-6.0f)*dt);
	}*/
	for (int i = 0; i < BULLET_NUM; i++) {
		if(i==0)_bullets[i].Move(0, (-6.0f*dt));

		if (i == 1)_bullets[i].Move(0, (-2.0f*dt));
	}
}

void CBomb::DrawBullets() {
	for (int i = 0; i <BULLET_NUM; i++) {
		_bullets->GL_Display();
	}
}
#include "CEnemy.h"

#define VP_HALFWIDTH  12.0f

CEnemy::CEnemy() {
	_enemy = NULL;
	_bullets = NULL;
}
CEnemy::~CEnemy(){
	delete _enemy;
}

void CEnemy::GL_Display() {
	
	_enemy->Draw();
	DrawBullets();
}


void CEnemy::CreateEnemy() {
	_enemy = new CPentagon;
	_mxProjection = Ortho(-VP_HALFWIDTH, VP_HALFWIDTH, -VP_HALFWIDTH, VP_HALFWIDTH, -1.0f, 1.0f);
	_mxModelView[0].x = 1.0f; _mxModelView[1].y = 1.0f; _mxModelView[2].z = 1.0f; _mxModelView[3].w = 1.0f;
	_mxIdentity[0].x = 1.0f; _mxIdentity[1].y = 1.0f; _mxIdentity[2].z = 1.0f; _mxIdentity[3].w = 1.0f;
	_enemy->SetShader(_mxModelView, _mxProjection);
	_enemy->SetColor(_color);
	_mxEnemyT = Translate(_enemyT);
	_enemy->SetTRSMatrix(_mxEnemyT);
}


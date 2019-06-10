#include "CBullet.h"



CBullet::CBullet(mat4 projection) {
	_bullet = new CQuad;
	_bullet->SetShader(_mxModelView, projection);
	_bullet->SetColor(_color);
	_mxModelView[0].x = 1.0f; _mxModelView[1].y = 1.0f; _mxModelView[2].z = 1.0f; _mxModelView[3].w = 1.0f;
	_mxIdentity[0].x = 1.0f; _mxIdentity[1].y = 1.0f; _mxIdentity[2].z = 1.0f; _mxIdentity[3].w = 1.0f;
	_mxBulletT = Translate(_bulletT);
	_bullet->SetTRSMatrix(_mxBulletT);
	//_bullet->Draw();
}

CBullet::~CBullet() {
	delete _bullet;
}

void CBullet::GL_Display() {
	
	_bullet->Draw();
}


void CBullet::Move(float x,float y) {
	_bulletT.x += x;
	_bulletT.y += y;
	_mxBulletT = Translate(_bulletT.x, _bulletT.y, 0);
	mat4 mxSca;
	vec3 bulletSca = vec3(0.5f, 0.5f, 0);
	mxSca = Scale(bulletSca);
	_bullet->SetTRSMatrix(_mxBulletT*mxSca);
}

void CBullet::Move(float x, float y,float r) {
	_bulletT.x += x;
	_bulletT.y += y;
	_mxBulletT = Translate(_bulletT.x, _bulletT.y, 0);

	mat4 mxSca,mxRot;
	vec3 bulletSca = vec3(0.2f, 0.2f, 0);
	mxSca = Scale(bulletSca);
	
	mxRot = RotateZ(r);
	_bullet->SetTRSMatrix(mxSca*_mxBulletT*mxRot);
}

void CBullet::SetPos(float x, float y) {
	_bulletT = vec3(x, y, 0);
}

vec3 CBullet::GetPos() {
	return(_bulletT);
}
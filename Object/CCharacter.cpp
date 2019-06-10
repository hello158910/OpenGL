#include "CCharacter.h"

#define VP_HALFWIDTH  12.0f
#define BULLET_NUM 200


CCharacter::CCharacter(mat4 projection) {
	_plane = new CQuad;
	_plane->SetShader(_mxModelView, projection);
	_plane->SetColor(_color);
	_mxModelView[0].x = 1.0f; _mxModelView[1].y = 1.0f; _mxModelView[2].z = 1.0f; _mxModelView[3].w = 1.0f;
	_mxIdentity[0].x = 1.0f; _mxIdentity[1].y = 1.0f; _mxIdentity[2].z = 1.0f; _mxIdentity[3].w = 1.0f;
	_mxPlaneT = Translate(_planeT);
	_plane->SetTRSMatrix(_mxPlaneT);

	_freeNum = BULLET_NUM;
	_usedNum = 0; 
	_bullets = new CBullet[BULLET_NUM];
	_bullets->SetPos(-6.5f, -6.5f);
	for (int i = 0; i < BULLET_NUM; i++) {
		_freeList.push_back(&_bullets[i]);
	}

}

CCharacter::~CCharacter() {
	if (_usedNum != 0)_inUsedList.clear();
	if (_freeNum != 0)_freeList.clear();
	delete _plane;
	delete _bullets;
}

void CCharacter::GL_Display() {
	_plane->Draw();
	for (int i = 0; i < BULLET_NUM; i++) {
		_bullets[i].GL_Display();
	}
	//for (int i = 0; i < SHIELD_NUM; i++) {
	//	_shield[i]->DrawW();
	//	
	//}	
}

void CCharacter::createShield(mat4 projection) {
	GLuint uiShaderHandle;
	for (int i = 0; i < SHIELD_NUM; i++) {
		_shield[i] = new CQuad;
		if (i == 0) {
			_shield[i]->SetShader(_mxModelView, projection);
			uiShaderHandle = _shield[i]->GetShaderHandle();
			_color.x = 1.0f; _color.y = 1.0f; _color.z = 1.0f; _color.w = 1.0f;
			_shield[i]->SetColor(_color);
		}
		else {
			_shield[i]->SetShader(_mxModelView, projection, uiShaderHandle);
			_color.x = 1.0f; _color.y = 1.0f; _color.z = 1.0f; _color.w = 1.0f;
			_shield[i]->SetColor(_color);
		}
	}
}

void CCharacter::onFrameMove(float dt) {
	
	if(_planeStatus==STA_HURT){
		_count += dt;
		_color = (0.3f, 0.6f, 0.9f, sin(dt*10));
		_plane->SetColor(_color);
		if (_count >= 3.14f) {
			_count -= 3.14f;
			_planeStatus = STA_NORMAL; 
			_color = (0.3f, 0.6f, 0.9f, 1.0f);
			_plane->SetColor(_color);
		}
	}

	std::list <CBullet*>::iterator it;
	if (_usedNum != 0) {
		for (it = _inUsedList.begin(); it != _inUsedList.end();) {
			(*it)->Move(0, (6.0f)*dt);
			if ((*it)->GetPos().y > 13.0f) {
				_freeList.push_front((*it));
				it=_inUsedList.erase(it);
				_freeNum++; _usedNum--;
			}
			else it++;
		}
	}
	
}

void CCharacter::reset() {

}
void CCharacter::SetPlaneStatus(int x) {
	_planeStatus = x;
}


void CCharacter::Fire() {

	CBullet* get;
	if (_freeNum != 0) {
	get = _freeList.front();
	_freeList.pop_front();
	_inUsedList.push_front(get);
	_freeNum--; _usedNum++;
	get->SetPos(_planeT.x, _planeT.y);
	}
}

void CCharacter::Move(float x, float y) {
	mat4 mxGT,mxT;
	mxGT = Translate(x, y, 0);
	_planeT = vec3(x, y, 0);
	_plane->SetTRSMatrix(mxGT);
}


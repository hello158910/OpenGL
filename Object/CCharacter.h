#ifndef CCHARACTER_H
#define CCHARACTER_H
#include "../header/Angel.h"
#include "../Common/CQuad.h"
#include "../Common/CPentagon.h"
#include "CBullet.h"
#include <list>

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 6  // 3 faces, 3 triangles/face 
#define SHIELD_NUM 3
#define BULLET_NUM 1
#define STA_NORMAL 0
#define STA_HURT 1
#define STA_DYING 2


class CCharacter
{
private:
	int _planeStatus;
	CBullet *_bullets;
	CQuad *_plane;
	CQuad *_shield[SHIELD_NUM];
	vec3 _planeT = (5.2f,5.2f,0);
	float _shieldT[SHIELD_NUM][3] = { 0 };

	mat4 _mxPlaneT, _mxShieldT[SHIELD_NUM];
	mat4 _mxPlaneR, _mxShieldR[SHIELD_NUM];

	mat4 _mxModelView;
	mat4 _mxIdentity;

	vec4 _color = vec4(0.3f, 0.6f, 0.9f, 1.0f);

	GLfloat _shieldAngle = 0;
	GLfloat _Tx = 0, _Ty = 0; // motion

	float _count = 0;

	// bullet
	std::list<CBullet*> _freeList;
	std::list<CBullet*> _inUsedList;
	int _freeNum;
	int _usedNum;
	
public:
	CCharacter(mat4 Projection);
	~CCharacter();

	void createShield(mat4 Projection);
	void GL_Display();
	void onFrameMove(float dt);
//	void UpdateMatrix();

	void Move(float x ,float y);
	
	void Fire();
	void SetPlaneStatus(int x);
	void reset();


};




#endif
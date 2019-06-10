#ifndef CENEMY_H
#define CENEMY_H
#include "../header/Angel.h"
#include "../Common/CQuad.h"
#include "../Common/CPentagon.h"
#include <list>
#include "CBullet.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 9  // 3 faces, 3 triangles/face 
#define SHIELD_NUM 3

class CEnemy
{
protected:
	CPentagon *_enemy;
	vec3 _enemyT = vec3 (-7.5f,10.5f, 0);

	mat4 _mxEnemyT;

	mat4 _mxModelView;
	mat4 _mxIdentity;
	mat4 _mxProjection;

	vec4 _color = vec4(0.3f, 0.5f, 0.7f, 1.0f);

	CBullet *_bullets;
	std::list <CBullet*> _freeList;
	std::list <CBullet*> _inUsedList;
	int _freeNum;
	int _usedNum;

public:
	CEnemy();
	~CEnemy();
	virtual void Attack(float dt)=0;
	virtual void Move(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void DrawBullets() = 0;

	void GL_Display();
	void CreateEnemy();

};




#endif
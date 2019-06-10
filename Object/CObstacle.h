#ifndef COBSTACLE_H
#define COBSTACLE_H
#include "../header/Angel.h"
#include "../Common/CQuad.h"
#include "CEnemy.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;


class CObstacle : public CEnemy
{
private:
	
public:
	CObstacle();
	~CObstacle();

	void Move(float dt);
	void Update(float dt);
	void Attack(float dt);
	void DrawBullets();
};




#endif
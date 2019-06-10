#ifndef CBOMB_H
#define CBOMB_H
#include "../header/Angel.h"
#include "../Common/CQuad.h"
#include "CEnemy.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

class CBomb: public CEnemy
{
private:
	float _count = 0;
public:
	CBomb();
	~CBomb();

	void Move(float dt);
	void Update(float dt);
	void Attack(float dt);
	void DrawBullets();
};




#endif
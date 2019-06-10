#ifndef CBULLET_H
#define CBULLET_H
#include "../header/Angel.h"
#include "../Common/CQuad.h"

#define VP_HALFWIDTH  12.0f

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;


class CBullet
{
private:
	CQuad *_bullet;
	vec3 _bulletT = vec3(8.2f, 8.2f, 0);

	mat4 _mxBulletT;

	mat4 _mxModelView;
	mat4 _mxIdentity;
	mat4 _mxProjection;

	vec4 _color = vec4(0.8f, 0.5f, 0.2f, 1.0f);


public:
	CBullet(mat4 projection= Ortho(-VP_HALFWIDTH, VP_HALFWIDTH, -VP_HALFWIDTH, VP_HALFWIDTH, -1.0f, 1.0f));
	~CBullet();

	vec3 GetPos();
	void SetPos(float x,float y);
	void GL_Display();
	void Move(float x,float y);
	void Move(float x, float y, float r);
	//	void UpdateMatrix();

};




#endif
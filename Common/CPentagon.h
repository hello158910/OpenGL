#ifndef CPENTAGON_H
#define CPENTAGON_H
#include "../header/Angel.h"
#include "CShape.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 9  // 2 faces, 2 triangles/face 

class CPentagon :public CShape
{
private:
	
public:
	CPentagon();
	~CPentagon();
	void Update(float dt);
	GLuint GetShaderHandle() { return _uiProgram;}

	void Draw();
	void DrawW();
};




#endif
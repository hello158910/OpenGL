#ifndef CSHAPE_H
#define CSHAPE_H
#include "../Header/Angel.h"

class CShape {
protected:
	vec4 *_Points;
	int _iNumVtx;

	GLfloat _fColor[4];
	char *_VXshader, *_FSshader;
	//VAO
	GLuint _uiVao;

	//Shader
	GLuint _uiModelView, _uiProjection,_uiColor;
	GLuint _uiProgram;
	GLuint _uiBuffer;

	//Matrix
	mat4 _mxView, _mxProjection, _mxTRS;
	mat4 _mxFinal;
	bool _bProUpdated, _bViewUpdated, _bTRSUpdated;
	bool _bColorUpdated;

	void CreateBufferObject();
	void DrawingSetShader();
	void DrawingWithoutSetShader();

public:
	CShape();
	virtual ~CShape();
	virtual void Draw() = 0;
	virtual void DrawW() = 0;
	virtual void Update(float dt) = 0;

	void SetShaderName(const char vxShader[], const char fsShader[]);
	void SetShader(mat4 &mxModelView, mat4 &mxProjection, GLuint uiShaderHandle = MAX_UNSIGNED_INT);
	void SetShader(GLuint uiShaderHandle = MAX_UNSIGNED_INT);

	void SetColor(vec4 vColor);
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);
	void SetTRSMatrix(mat4 &mat);
	void SetPos(float x, float y, float z);
};

#endif
#ifndef CQuadEX2B_H
#define CQuadEX2B_H
#include "../header/Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#define QUAD_NUM 6  // 2 faces, 2 triangles/face 

class CQuadEX2B
{
private:
	vec4 m_Points[QUAD_NUM];
	vec4 m_Colors[QUAD_NUM];
	// VAO
	GLuint m_uiVao;
	// VBO
	GLuint m_uiBuffer;
	//  for Shader
	GLuint m_uiProgram ;
	// Vertex Position Attribute
	GLuint m_uiModelView, m_uiProjection;
	// Matrix 
	mat4 m_mxView, m_mxProjection;
	mat4 m_mxMVFinal, m_mxTRS;

	// Angle and Translation
	GLuint m_uiAngleLoc, m_uiTranLoc, m_uiGAngleLoc, m_uiScaleLoc;
	float m_fAngle, m_fGAngle;
	float m_fTranslate[3];
	float m_fScale[3];

	// 紀錄是否有矩陣的更新
	bool  m_bUpdateMV;
	bool  m_bUpdateProj;

	void CreateBufferObject();
public:
	CQuadEX2B();

	void SetShader(mat4 &mxModelView, mat4 &mxProjection, GLuint uiShaderHandle=MAX_UNSIGNED_INT);
	GLuint GetShaderHandle() { return m_uiProgram;}
	void SetViewMatrix(mat4 &mat);
	void SetProjectionMatrix(mat4 &mat);
	void SetTRSMatrix(mat4 &mat);
	void SetColor(GLfloat vColor[4]); // Single color
	void SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[]); // four Vertices' Color

	// Angle and Translation
	void SetAngle(float fAngle);
//	void SetGAngle(float fGAngle);
	void SetTranslate(float vT[]);
	void SetTranslate(float x, float y, float z);
//	void SetScale(float vS[]);
	void SetScale(float x, float y, float z);

	void Draw();
	void DrawW();
};




#endif
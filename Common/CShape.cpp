#include "CShape.h"

CShape::CShape() {
	_Points = NULL;
	_bProUpdated = false;
	_bViewUpdated = false;
	_bTRSUpdated = false;
	_bColorUpdated = false;
}

CShape::~CShape()
{
	if (_Points != NULL) delete[] _Points;
	if (_VXshader != NULL) delete[] _VXshader;
	if (_FSshader != NULL) delete[] _FSshader;
}

void CShape::CreateBufferObject()
{
	glGenVertexArrays(1, &_uiVao);
	glBindVertexArray(_uiVao);

	// Create and initialize a buffer object
	glGenBuffers(1, &_uiBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uiBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4)*_iNumVtx, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec4)*_iNumVtx, _Points);
}

void CShape::SetShader(mat4 &mxModelView, mat4 &mxProjection, GLuint uiShaderHandle)
{
	// Load shaders and use the resulting shader program
	if (uiShaderHandle == MAX_UNSIGNED_INT) _uiProgram = InitShader(_VXshader, _FSshader);
	else _uiProgram = uiShaderHandle;

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(_uiProgram, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	_uiModelView = glGetUniformLocation(_uiProgram, "ModelView");
	_mxFinal = _mxView = mxModelView;
	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxView);

	_uiProjection = glGetUniformLocation(_uiProgram, "Projection");
	_mxProjection = mxProjection;
	glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);
	
	_uiColor = glGetUniformLocation(_uiProgram, "vColor");
	glUniform4fv(_uiColor, 1, _fColor);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CShape::SetShader(GLuint uiShaderHandle)
{
	// Load shaders and use the resulting shader program
	if (uiShaderHandle == MAX_UNSIGNED_INT) _uiProgram = InitShader(_VXshader, _FSshader);
	else _uiProgram = uiShaderHandle;

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(_uiProgram, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	_uiModelView = glGetUniformLocation(_uiProgram, "ModelView");
	//	m_mxMVFinal , m_mxView 宣告時就是單位矩陣
	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxView);

	_uiProjection = glGetUniformLocation(_uiProgram, "Projection");
	// m_mxProjection 宣告時就是單位矩陣
	glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);

	_uiColor = glGetUniformLocation(_uiProgram, "vColor");
	glUniform4fv(_uiColor, 1, _fColor);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CShape::DrawingSetShader()
{
	glUseProgram(_uiProgram);
	glBindVertexArray(_uiVao);

	if (_bViewUpdated || _bTRSUpdated) { // Model View 的相關矩陣內容有更動
		_mxFinal = _mxView * _mxTRS;
		_bViewUpdated = _bTRSUpdated = false;
	}
	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxFinal);

	if (_bProUpdated) {
		glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);
		_bProUpdated = false;
	}
	if (_bColorUpdated) {
		glUniform4fv(_uiColor, 1, _fColor);
		_bColorUpdated = false;
	}
}

// 此處預設使用前一個描繪物件所使用的 Shader
void CShape::DrawingWithoutSetShader()
{
	glBindVertexArray(_uiVao);
	if (_bViewUpdated || _bTRSUpdated) { // Model View 的相關矩陣內容有更動
		_mxFinal = _mxView *_mxTRS;
		_bViewUpdated = _bTRSUpdated = false;
	}
	glUniformMatrix4fv(_uiModelView, 1, GL_TRUE, _mxFinal);
	if (_bProUpdated) {
		glUniformMatrix4fv(_uiProjection, 1, GL_TRUE, _mxProjection);
		_bProUpdated = false;
	}
	glUniform4fv(_uiColor, 1, _fColor);
}

void CShape::SetShaderName(const char vxShader[], const char fsShader[])
{
	int len;
	len = strlen(vxShader);
	_VXshader = new char[len + 1];
	memcpy(_VXshader, vxShader, len + 1);

	len = strlen(fsShader);
	_FSshader = new char[len + 1];
	memcpy(_FSshader, fsShader, len + 1);
}

void CShape::SetViewMatrix(mat4 &mat)
{
	_mxView = mat;
	_bViewUpdated = true;
}

void CShape::SetProjectionMatrix(mat4 &mat)
{
	_mxProjection = mat;
	_bProUpdated = true;
}
void CShape::SetTRSMatrix(mat4 &mat)
{
	_mxTRS = mat;
	_bTRSUpdated = true;
}

void CShape::SetColor(vec4 vColor)
{
	_fColor[0] = vColor.x;
	_fColor[1] = vColor.y;
	_fColor[2] = vColor.z;
	_fColor[3] = vColor.w;
	_bColorUpdated = true;
}

void CShape::SetPos(float x, float y, float z) {
	
}
#include "CQuad.h"

CQuad::CQuad()
{
	_iNumVtx = QUAD_NUM+1;
	_Points = NULL;

	_Points = new vec4[_iNumVtx];

	_Points[0] = vec4( -0.5f,  0.5f, 0.0f, 1.0f);
	_Points[1] = vec4(  0.5f,  0.5f, 0.0f, 1.0f);
	_Points[2] = vec4(  0.5f, -0.5f, 0.0f, 1.0f);
	_Points[3] = vec4( -0.5f,  0.5f, 0.0f, 1.0f);
	_Points[4] = vec4(  0.5f, -0.5f, 0.0f, 1.0f);
	_Points[5] = vec4( -0.5f, -0.5f, 0.0f, 1.0f);

	SetShaderName("vsVtxColor.glsl", "fsVtxColor.glsl");
	// Create and initialize a buffer object 
	CreateBufferObject();
	
	_fColor[0] = 1.0f; _fColor[1] = 1.0f; _fColor[2] = 1.0f; _fColor[3] = 1.0f;
}

CQuad::~CQuad(){}

void CQuad::Update(float dt) {

}


void CQuad::Draw()
{
	DrawingSetShader();
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
	/*glUseProgram( _uiProgram );
	glBindVertexArray( m_uiVao );
	if( m_bUpdateMV ) {
		m_mxMVFinal = m_mxView*m_mxTRS;
		m_bUpdateMV = false;
	}
	glUniformMatrix4fv( m_uiModelView, 1, GL_TRUE, m_mxMVFinal );

	if( m_bUpdateProj ) {
		glUniformMatrix4fv( m_uiProjection, 1, GL_TRUE, m_mxProjection );
		m_bUpdateProj = false;
	}
	glDrawArrays( GL_TRIANGLES, 0, QUAD_NUM );*/
}

void CQuad::DrawW()
{
	DrawingWithoutSetShader();
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
	/*glBindVertexArray( m_uiVao );

	if( m_bUpdateMV ) {
		m_mxMVFinal = m_mxView*m_mxTRS;
		m_bUpdateMV = false;
	}

	glUniformMatrix4fv( m_uiModelView, 1, GL_TRUE, m_mxMVFinal );
	if( m_bUpdateProj ) {
		glUniformMatrix4fv( m_uiProjection, 1, GL_TRUE, m_mxProjection );
		m_bUpdateProj = false;
	}
	glDrawArrays( GL_TRIANGLES, 0, QUAD_NUM );*/
}

// Multi Objects with same shader program
// 將每一個四角面的位置改變都移入 Shader 中計算
// 

#include "header/Angel.h"
#include "Common/CQuadEX2B.h"
#include <time.h>
#include "Object\CCharacter.h"

#include "Object\CEnemy.h"
#include "Object\CObstacle.h"
#include "Object\CShooter.h"
#include "Object\CBomb.h"

#define SPACE_KEY 32
#define SCREEN_SIZE 800
#define HALF_SIZE (SCREEN_SIZE/2) 
#define VP_HALFWIDTH  12.0f
#define GRID_SIZE  25 //background
#define ENEMY_NUM 3

// For grid quad
CQuadEX2B *g_pGridQuad[GRID_SIZE]; // bg
float      g_fQuadT[GRID_SIZE][3]={0}; //位置
float	   g_fQuadTPos[GRID_SIZE][3]={ 0 }; // 原始位置

//Character
CCharacter *_plane;

//Enemy
CEnemy *_enemy[ENEMY_NUM];

// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxIdentity(1.0f);
mat4 g_mxProjection;

bool    m_bg = false; 

//----------------------------------------------------------------------------
// 函式的原型宣告
void IdleProcess();
void CreateGridQuad();



void init( void )
{
	//  產生 projection 矩陣，此處為產生正投影矩陣
    g_mxProjection = Ortho(-VP_HALFWIDTH, VP_HALFWIDTH, -VP_HALFWIDTH, VP_HALFWIDTH, -1.0f, 1.0f);
	_plane = new CCharacter(g_mxProjection);
	_enemy[0] = new CObstacle;
	_enemy[1] = new CShooter;
	_enemy[2] = new CBomb;
	// 必須在 glewInit(); 執行完後,在執行物件實體的取得
	CreateGridQuad();
//	_plane->createShield();
    glClearColor( 0.0, 0.0, 0.0, 1.0 ); // black background
}

//----------------------------------------------------------------------------
void bgMove(float dt) {
	
	for (int idx = 0; idx < GRID_SIZE; idx++) {
			g_fQuadT[idx][1] -=8.2f*dt;
			if (g_fQuadT[idx][1] <= -12.0f)
				g_fQuadT[idx][1] = g_fQuadTPos[idx][1];

		}


		for (int i = 0; i < GRID_SIZE; i++) {
			g_pGridQuad[i]->SetTranslate(g_fQuadT[i]);
			//g_pGridQuad[i]->SetAngle(g_fZAngle);
		}
	}



void GL_Display( void )
{
    glClear( GL_COLOR_BUFFER_BIT ); // clear the window

	g_pGridQuad[0]->Draw();
	for( int i = 1 ; i < GRID_SIZE ; i++ )  {
		g_pGridQuad[i]->DrawW();
	}
	_plane->GL_Display();
//	_enemy[0]->GL_Display();
	_enemy[1]->GL_Display();
	_enemy[2]->GL_Display();
	//for( int i = 0 ; i < GRID_SIZE*GRID_SIZE ; i++ )  {
	//	g_pGridQuad[i]->Draw();
	//}
	glutSwapBuffers();	// 交換 Frame Buffer
}

void onFrameMove(float delta)
{
	if(m_bg) bgMove(delta);
	_plane->onFrameMove(delta);
	
	
	_enemy[0]->Update(delta);
	_enemy[1]->Update(delta);
	_enemy[2]->Update(delta);
	GL_Display();
}

//----------------------------------------------------------------------------
void reset()
{ 
	mat4 mxT;
	vec4 vT;
	int idx = 0;
  
	m_bg = false;
	_plane->reset();
	for( int i = 0 ; i < GRID_SIZE ; i++ ) {
		//mxT = Translate(g_fQuadT[idx][0],g_fQuadT[idx][1],g_fQuadT[idx][2]);	
		//g_pGridQuad[idx]->SetTRSMatrix(mxT);
		g_fQuadT[i][0] = g_fQuadTPos[i][0];
		g_pGridQuad[i]->SetTranslate(g_fQuadTPos[i]);
	}
}

//----------------------------------------------------------------------------

void CreateGridQuad()
{
	GLuint uiShaderHandle;
	vec4 vColor = vec4( 0, 0, 0, 1);
	vec4 vT;
	mat4 mxT;
	int idx = 0;

	// x-> -10 -8 -6 -4 -2 0  2  4  6  8  10
	// y->  10  8  6  4  2 0 -2 -4 -6 -8 -10
	srand((unsigned)time(NULL));
	for( int i = 0 ; i < GRID_SIZE ; i++ ) {
	
			g_fQuadT[idx][1] = g_fQuadTPos[idx][1] =  rand() % 24 ;
			g_fQuadT[idx][0] = g_fQuadTPos[idx][0] = rand() % 15- rand()%15;
			g_pGridQuad[idx] = new CQuadEX2B;
			if( idx == 0 )  { // 第一個物件，必須建立 Shader
				g_pGridQuad[idx]->SetShader(g_mxModelView, g_mxProjection);
				uiShaderHandle = g_pGridQuad[idx]->GetShaderHandle(); // 取得 Shader Handle
				vColor.x = 0.15f; vColor.y = 0.3f; vColor.z = 0.3f; vColor.w = 1.0f;
				g_pGridQuad[idx]->SetColor(vColor);
			}
			else {
				g_pGridQuad[idx]->SetShader(g_mxModelView, g_mxProjection, uiShaderHandle);
				vColor.x = 0.23f; vColor.y = 0.36f; vColor.z =0.38f; vColor.w = 1.0f;
				g_pGridQuad[idx]->SetColor(vColor);
			}
			//mxT = Translate(g_fQuadT[idx][0],g_fQuadT[idx][1],g_fQuadT[idx][2]);	
			//g_pGridQuad[idx]->SetTRSMatrix(mxT);
			g_pGridQuad[idx]->SetTranslate(g_fQuadT[idx]);
			g_pGridQuad[idx]->SetAngle(30);
	//		g_pGridQuad[idx]->SetGAngle(30);
			g_pGridQuad[idx]->SetScale(0.1f, 0.05f, 0.2f);
			idx++;
		}
	}

//----------------------------------------------------------------------------
void Win_PassiveMotion(int x, int y) {
	if (m_bg) {
		GLfloat _Tx = 0, _Ty = 0;
		_Tx = 12.0f*(x - HALF_SIZE) / (HALF_SIZE);
		_Ty = -12.0f*(y - HALF_SIZE) / (HALF_SIZE);
		_plane->Move(_Tx, _Ty);
	}
}
void Win_Keyboard( unsigned char key, int x, int y )
{
    switch ( key ) {
	case  SPACE_KEY:
		m_bg = !m_bg;
		break;
	case 81: // Q
	case 113: //q
		_plane->Fire();
		break;
	case 82: // R key
	case 114: // r key
		reset();
		break;
	case 83: // S key
	case 115: // s key
		_plane->SetPlaneStatus(1);
		break;
    case 033:
		glutIdleFunc( NULL );
		for( int i = 0 ; i < GRID_SIZE ; i++ ) delete g_pGridQuad[i];
        exit( EXIT_SUCCESS );
        break;
    }
}
//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) {
	switch(button) {
		case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
			if ( state == GLUT_DOWN )
				if(m_bg)_plane->Fire();
			break;
		case GLUT_MIDDLE_BUTTON:  // 目前按下的是滑鼠中鍵 
			if ( state == GLUT_DOWN ) ;
			break;
		case GLUT_RIGHT_BUTTON:   // 目前按下的是滑鼠右鍵
			if ( state == GLUT_DOWN ) ; 
			break;
		default:
			break;
	} 
}
//----------------------------------------------------------------------------
void Win_SpecialKeyboard(int key, int x, int y) {
	
}
//----------------------------------------------------------------------------

void GL_Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
}

//----------------------------------------------------------------------------

int main( int argc, char **argv )
{
    
	glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( SCREEN_SIZE, SCREEN_SIZE );

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion( 3, 2 );
	glutInitContextProfile( GLUT_CORE_PROFILE );

    glutCreateWindow( "Draw two triangles" );

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE; 
    glewInit();  
	glutPassiveMotionFunc(Win_PassiveMotion);

    init();

	glutMouseFunc(Win_Mouse);
    glutKeyboardFunc( Win_Keyboard );	// 處理 ASCI 按鍵如 A、a、ESC 鍵...等等
	glutSpecialFunc( Win_SpecialKeyboard);	// 處理 NON-ASCI 按鍵如 F1、Home、方向鍵...等等
    glutDisplayFunc( GL_Display );
	glutReshapeFunc( GL_Reshape );
	glutIdleFunc( IdleProcess );
	
    glutMainLoop();
    return 0;
}

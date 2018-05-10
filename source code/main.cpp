#include<glut.h>
#include <windows.h>	
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include"main.h"
#define GL_PI 3.1415
#define PI 3.1415
#define VOLUME 0.2

unsigned char PALETTE[11][3] = {
	{ 255,255,255 }, //0 WHITE
	{ 0,255,255 },	//1 CYAN
	{ 255,0,255 },	//2 PURPLE
	{ 0,0,255 },	//3 BLUE
	{ 0,250,154 },//4 GREEN
	{ 89,198,203 },	//5 SKY BLUE
	{ 68,0,98 },		//6 PURPLE
	{ 250,250,210 },	// 7 Light Goldenrod Yellow
	{ 152,251,152 },	// 8 PALE GREEN
	{ 60,179,113 }	,//9 MEDIUM SEA GREEN
	{ 85,107,47 }	//10 DARK OLIVE GREEN
};

/*Global variable*/
bool click = false;
float originX, originY, dX, dY;
int Width = 500, Height = 500;
static float eyex = 0.0, eyey = 0.0, eyez = 1.0, atx = 0, aty = 0, atz = 0, upx = 0, upy = 1, upz = 0;
float delta_x, delta_y;
float preX=0.0;
GLfloat fAspect = (GLfloat)Width / (GLfloat)Height;
int R_stage;

double B_Rotate;

int count = 0;
static GLfloat L_theta = 0.0;
static GLfloat L_theta2 = 0.0;
static GLfloat scale = 1.0;
int axis = 0.0;
static float R_Leaf_x = 0.0;
static float L_Leaf_x = 0.0;
static float Body_x = 0.0;
static float L_Arm_x = 0.0;
static float R_Arm_x = 0.0;
static float L_Leg_x = 0.0;
static float R_Leg_x = 0.0;
int isDebug = 0;
boolean tap = false;

/*function prototype*/
void init();
void drawL_Arm(float x, float a, float b, float c);
void drawR_Arm(float x, float a, float b, float c);
void drawL_Leg(float x, float a, float b, float c);
void drawR_Leg(float x, float a, float b, float c);
void drawL_Leaf(float x, float a, float b, float c);
void drawR_Leaf(float x, float a, float b, float c);
void display();
void scoring();
void drawRandomBall();
void drawCharacter();
void drawFace();
void drawL_Eye();
void drawR_Eye();
void drawBody();
void sphere(float x, float y, float z, float r);
void cone(GLfloat base, GLfloat height);
void halfSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius);
void cylinder(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius, GLfloat h);
void colorChange(int index);
void MyTimer(int Value);
void spin_leaf();
void drawFloor();
void keyboard_handler(unsigned char key, int x, int y);
void mouse_handler(int btn, int state, int x, int y);
void drawball(double x_B, double z_B, int n);

void drawcone();

void drawcone_nocolor();

void r_drawball(int temp, double z, double time, int n);

void spinball();

void GLViewSetup();
void drawcenter();
void drawwall(int x);
void instanceInit();

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("SaeSsapRun");
	glEnableClientState(GL_COLOR_ARRAY); // notify to use color array
	glColorPointer(3, GL_FLOAT, 0, PALETTE); // set color array pointer
	glutTimerFunc(40, MyTimer, 1);
	glutMouseFunc(mouse_handler);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);
	instanceInit();
	init();
	glutMainLoop();
	return 0;
}
void init() {

	glLoadIdentity();
	GLViewSetup();
	glMatrixMode(GL_PROJECTION);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	gluLookAt(view[0], view[1], view[2], cnt[0], cnt[1], cnt[2], 0, 1, 0);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glOrtho(-100.0, 100.0, -10.0, 10.0, -10.0, 10.0);
}

void instanceInit() {
	theta[0] = 0;
	theta[1] = 0;
	theta[2] = 0;

	m_xPos = 0;
	m_yPos = 0;
	m_zPos = 0;

	m_XScale = 1;
	m_YScale = 1;
	m_ZScale = 1;

	//주시점
	cnt[0] = 0;
	cnt[1] = 10;
	cnt[2] = 20;

	//시점(카메라위치)
	view[0] = sqrt(3) * 100;
	view[1] = sqrt(3) * 200;
	view[2] = 100;

	//카메라
	distC = 100;
	thetaC = 90;
	phaiC = 25;

	//시체적
	fov = 100;
	ratio = 1.0;
	
	m_aLight = 35.0f;
	m_sLight = 100.0f;
	m_dLight = 100.0f;

	m_xLP = 50.0f;
	m_yLP = 180.0f;
	m_zLP = 100.0f;

	//볼의 z 값

	z_B = -100;
	z_B1 = -100;
	z_B2 = -100;
	z_B3 = -100;
	z_B4 = -100;
	z_B5 = -100;


	//볼의 속도추가 값
	speedadd = 0;

	stage = 1;
	R_stage = 1;

	r_position = 0;

	temp = 0;
	temp1 = 0;
	temp2 = 0;
	temp3 = 0;
	temp4 = 0;
	temp5 = 0;

	x_C = 0.;
	
	aa = 0;

	
	//로테이션 변수
	R_leg = 0;
	R_arm = 0;
	GameState = 5;
	
	B_Rotate = 0;
}

void drawcenter()
{
	glPushMatrix();
	glTranslatef(0, -5., 0);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(50, 0, -100);
	glVertex3f(50, 0, 100);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(-50, 0, -100);
	glVertex3f(-50, 0, 100);
	glEnd();
	glPopMatrix();
}

void GLViewSetup() {
	
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		nearZ = 0.2*distC;
		farZ = distC - 200;

		gluPerspective(fov, (double)ratio, nearZ, farZ);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		view[0] = cnt[0] + distC * cos(PI * thetaC / 180) * cos(PI * phaiC / 180);
		view[1] = cnt[1] + distC * sin(PI * phaiC / 180);
		view[2] = cnt[2] + distC * sin(PI * thetaC / 180) * cos(PI * phaiC / 180);
		gluLookAt(view[0], view[1], view[2], cnt[0], cnt[1], cnt[2], 0, 1, 0);

		GLfloat lightPos[] = { m_xLP,m_yLP,m_zLP,1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	}

GLfloat R, G, B = 0.0;
GLint index = 0;

void cylinder(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius, GLfloat h)
{
	/* function createCyliner()
	원기둥의 중심 x,y,z좌표, 반지름, 높이를 받아 원기둥을 생성하는 함수(+z방향으로 원에서 늘어남)
	centerx : 원기둥 원의 중심 x좌표
	centery : 원기둥 원의 중심 y좌표
	centerz : 원기둥 원의 중심 z좌표
	radius : 원기둥의 반지름
	h : 원기둥의 높이
	*/
	GLfloat x, y, angle;

	glBegin(GL_TRIANGLE_FAN);           //원기둥의 윗면
	glNormal3f(0.0f, 0.0f, -1.0f);
	glColor3ub(139, 69, 19);
	glVertex3f(centerx, centery, centerz);



	for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
	{
		x = centerx + radius*sin(angle);
		y = centery + radius*cos(angle);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(x, y, centerz);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);            //원기둥의 옆면
	for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
	{
		x = centerx + radius*sin(angle);
		y = centery + radius*cos(angle);
		glNormal3f(sin(angle), cos(angle), 0.0f);
		glVertex3f(x, y, centerz);
		glVertex3f(x, y, centerz + h);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);           //원기둥의 밑면
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(centerx, centery, centerz + h);
	for (angle = (2.0f*GL_PI); angle > 0.0f; angle -= (GL_PI / 8.0f))
	{
		x = centerx + radius*sin(angle);
		y = centery + radius*cos(angle);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(x, y, centerz + h);
	}
	glEnd();
}

void colorChange(int index) {
	R = PALETTE[index][0] / 255.0f; G = PALETTE[index][1] / 255.0f; B = PALETTE[index][2] / 255.0f;
	glColor3f(R, G, B);
}

void cone(GLfloat base, GLfloat height) {
	if (isDebug) {
		glutWireCone(base, height, 20, 16);
	}
	else {
		glutSolidCone(base, height, 20, 16);
	}
}

void halfSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius)
{
	/* function createHalfSphere()
	구의 중심 x, y, z 좌표를 받아 반구를 만드는 함수
	x : 반구의 중심 x 좌표
	y : 반구의 중심 y 좌표
	z : 반구의 중심 z 좌표
	raidus : 반구의 반지름
	*/
	GLfloat angley;  //y축 값을 구하기 위한 각도
	GLfloat nexty;  //다음 y축 값을 구하기 위한 각도
	GLfloat anglex;  //x, y축 값을 구하기 위한 각도

	glBegin(GL_QUAD_STRIP);
	for (angley = 0.0f; angley <= (0.5f*GL_PI); angley += ((0.5f*GL_PI) / 8.0f))  //반구만 그려야 하므로 0.5곱함
	{
		y = radius*sin(angley);     //y축 값 계산
		nexty = angley + ((0.5f*GL_PI) / 8.0f);  //다음 angley값 저장
		for (anglex = 0.0f; anglex < (2.0f*GL_PI); anglex += (GL_PI / 8.0f))
		{
			x = radius*cos(angley)*sin(anglex);
			z = radius*cos(angley)*cos(anglex);
			glNormal3f(-cos(angley)*sin(anglex), -sin(angley), -cos(angley)*cos(anglex)); //반구의 안쪽으로 normal 벡터 생성
			glVertex3f(x, y, z);

			x = radius*cos(nexty)*sin(anglex);
			z = radius*cos(nexty)*cos(anglex);
			glNormal3f(-cos(nexty)*sin(anglex), -sin(nexty), -cos(nexty)*cos(anglex));
			glVertex3f(x, radius*sin(nexty), z);
		}
	}
	glEnd();
}

void sphere(float x, float y, float z, float r) {
	glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)z);
	glutSolidSphere((GLdouble)r, 50, 50);
}
void drawFace() {
	glPushMatrix();
	glTranslatef(0.0, 1.25, 0.0);
	colorChange(4);
	sphere(0.0, 0.0, 0.0, 0.5);
	glPopMatrix();
}
void drawL_Eye() {
	glPushMatrix();
	glTranslatef(-0.26, 1.28, 0.5);
	colorChange(0);
	sphere(0.0, 0.0, 0.0, 0.12);
	glPopMatrix();
}
void drawR_Eye() {
	glPushMatrix();
	glTranslatef(0.26, 1.28, 0.5);
	colorChange(0);
	sphere(0.0, 0.0, 0.0, 0.12);
	glPopMatrix();
}
void drawBody() {
	glPushMatrix();
	colorChange(7);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	cone(0.4, 1.0);
	glPopMatrix();
}
void drawL_Arm(float x, float a, float b, float c) {
	glPushMatrix();
	colorChange(5);
	glRotatef((GLfloat)x, (GLfloat)a, (GLfloat)b, (GLfloat)c);
	glTranslatef(0.1, 0.7, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	cylinder(0.0, 0.0, 0.0, 0.02, 0.7);
	glPopMatrix();
}
void drawR_Arm(float x, float a, float b, float c) {
	glPushMatrix();
	glRotatef((GLfloat)x, (GLfloat)a, (GLfloat)b, (GLfloat)c);
	colorChange(5);
	glTranslatef(-0.6, 0.2, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(-45.0, 1.0, 0.0, 0.0);


	cylinder(0.0, 0.0, 0.0, 0.02, 0.7);
	glPopMatrix();
}
void drawL_Leg(float x, float a, float b, float c) {
	glPushMatrix();
	glRotatef((GLfloat)x, (GLfloat)a, (GLfloat)b, (GLfloat)c);
	colorChange(5);
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glRotatef(70.0, 1.0, 0.0, 0.0);
	cylinder(0.0, 0.0, 0.0, 0.02, 0.7);
	glPopMatrix();
}
void drawR_Leg(float x, float a, float b, float c) {
	glPushMatrix();
	glRotatef((GLfloat)x, (GLfloat)a, (GLfloat)b, (GLfloat)c);
	colorChange(5);
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glRotatef(110.0, 1.0, 0.0, 0.0);
	cylinder(0.0, 0.0, 0.0, 0.02, 0.7);
	glPopMatrix();
}

void drawL_Leaf(float x, float a, float b, float c) {

	glPushMatrix();
	glRotatef((GLfloat)x, (GLfloat)a, (GLfloat)b, (GLfloat)c);
	colorChange(8);
	glTranslatef(-0.38, 2.1, 0.0);
	glScalef(0.7, 0.7, 0.7);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(40.0, 0.0, 1.0, 0.0);
	cone(0.25, 0.7);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	halfSphere(0.0, 0.0, 0.0, 0.25);

	glPopMatrix();
}
void drawR_Leaf(float x, float a, float b, float c) {

	glPushMatrix();
	glRotatef((GLfloat)x, (GLfloat)a, (GLfloat)b, (GLfloat)c);
	colorChange(8);
	glTranslatef(0.32, 2.1, 0.0);
	glScalef(0.7, 0.7, 0.7);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(-40.0, 0.0, 1.0, 0.0);
	cone(0.25, 0.7);
	colorChange(4);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	halfSphere(0.0, 0.0, 0.0, 0.25);
	glPopMatrix();
}

void drawCharacter() {
	
	glPushMatrix();
	glTranslated(x_C, 0.0, 0.0);
	glTranslated(0.0, 0.0, 60.0);
	glRotatef(Body_x, 0.0, 1.0, 0.0);
	glScaled(20.0, 20.0, 20.0);
	drawFace();
	drawBody();
	drawL_Eye();
	drawR_Eye();
	drawL_Arm(L_Arm_x, 0.0, 1.0, 0.0);
	drawR_Arm(-R_Arm_x, 0.0, 1.0, 0.0);
	drawL_Leg(L_Leg_x, 1.0, 0.0, 0.0);
	drawR_Leg(R_Leg_x, 1.0, 0.0, 0.0);
	drawL_Leaf(L_Leaf_x, 0.0, 1.0, 0.0);
	drawR_Leaf(R_Leaf_x, 0.0, 1.0, 0.0);
	glPopMatrix();
}
void display()
{
	
	if (GameState == 3) {
		printf("끝");
		exit(1);
	}
	
	glPopMatrix();
	drawRandomBall();
	glPushMatrix();
	glPopMatrix();
	drawcenter();
	drawFloor();
	drawwall(-50);
	drawwall(50);
	glPushMatrix();
	drawCharacter();

	scoring();
	
	glutSwapBuffers();
	glutPostRedisplay();
}

void scoring() {

	if (z_B <= 74 && z_B >= 60) {
		if (temp == 0 || temp == 1) {
			if (x_C == 0)
				GameState = 3;
		}
		else if (temp == 2 || temp == 3 || temp == 4) {
			if (x_C == 30)
				GameState = 3;
		}
		else if (temp == 5 || temp == 6 || temp == 7) {
			if (x_C == -30)
				GameState = 3;
		}
		else if (temp == 8 || temp == 9 || temp == 10 || temp == 11) {
			if (x_C == 0 || x_C == 30)
				GameState = 3;
		}
		else if (temp == 12 || temp == 13 || temp == 14 || temp == 15) {
			if (x_C == 0 || x_C == -30)
				GameState = 3;
		}
		else if (temp == 16 || temp == 17) {
			if (x_C == 30 || x_C == -30)
				GameState = 3;
		}
	}
	if (z_B1 <= 74 && z_B1 >= 60) {
		if (temp1 == 0 || temp1 == 1) {
			if (x_C == 0)
				GameState = 3;
		}
		else if (temp1 == 2 || temp1 == 3 || temp1 == 4) {
			if (x_C == 30)
				GameState = 3;
		}
		else if (temp1 == 5 || temp1 == 6 || temp1 == 7) {
			if (x_C == -30)
				GameState = 3;
		}
		else if (temp1 == 8 || temp1 == 9 || temp1 == 10 || temp1 == 11) {
			if (x_C == 0 || x_C == 30)
				GameState = 3;
		}
		else if (temp1 == 12 || temp1 == 13 || temp1 == 14 || temp1 == 15) {
			if (x_C == 0 || x_C == -30)
				GameState = 3;
		}
		else if (temp1 == 16 || temp1 == 17) {
			if (x_C == 30 || x_C == -30)
				GameState = 3;
		}
	}
	if (z_B2 <= 74 && z_B2 >= 60) {
		if (temp2 == 0 || temp2 == 1) {
			if (x_C == 0)
				GameState = 3;
		}
		else if (temp2 == 2 || temp2 == 3 || temp2 == 4) {
			if (x_C == 30)
				GameState = 3;
		}
		else if (temp2 == 5 || temp2 == 6 || temp2 == 7) {
			if (x_C == -30)
				GameState = 3;
		}
		else if (temp2 == 8 || temp2 == 9 || temp2 == 10 || temp2 == 11) {
			if (x_C == 0 || x_C == 30)
				GameState = 3;
		}
		else if (temp2 == 12 || temp2 == 13 || temp2 == 14 || temp2 == 15) {
			if (x_C == 0 || x_C == -30)
				GameState = 3;
		}
		else if (temp2 == 16 || temp2 == 17) {
			if (x_C == 30 || x_C == -30)
				GameState = 3;
		}
	}
	if (z_B3 <= 74 && z_B3 >= 60) {
		if (temp3 == 0 || temp3 == 1) {
			if (x_C == 0)
				GameState = 3;
		}
		else if (temp3 == 2 || temp3 == 3 || temp3 == 4) {
			if (x_C == 30)
				GameState = 3;
		}
		else if (temp3 == 5 || temp3 == 6 || temp3 == 7) {
			if (x_C == -30)
				GameState = 3;
		}
		else if (temp3 == 8 || temp3 == 9 || temp3 == 10 || temp3 == 11) {
			if (x_C == 0 || x_C == 30)
				GameState = 3;
		}
		else if (temp3 == 12 || temp3 == 13 || temp3 == 14 || temp3 == 15) {
			if (x_C == 0 || x_C == -20)
				GameState = 3;
		}
		else if (temp3 == 16 || temp3 == 17) {
			if (x_C == 30 || x_C == -30)
				GameState = 3;
		}
	}
	if (z_B4 <= 74 && z_B4 >= 60) {
		if (temp4 == 0 || temp4 == 1) {
			if (x_C == 0)
				GameState = 3;
		}
		else if (temp4 == 2 || temp4 == 3 || temp4 == 4) {
			if (x_C == 30)
				GameState = 3;
		}
		else if (temp4 == 5 || temp4 == 6 || temp4 == 7) {
			if (x_C == -30)
				GameState = 3;
		}
		else if (temp4 == 8 || temp4 == 9 || temp4 == 10 || temp4 == 11) {
			if (x_C == 0 || x_C == 30)
				GameState = 3;
		}
		else if (temp4 == 12 || temp4 == 13 || temp4 == 14 || temp4 == 15) {
			if (x_C == 0 || x_C == -30)
				GameState = 3;
		}
		else if (temp4 == 16 || temp4 == 17) {
			if (x_C == 30 || x_C == -30)
				GameState = 3;
		}
	}

}

void drawRandomBall() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (z_B >= 100)
		z_B = -100;
	r_drawball(temp, z_B, 0, 0);

	if (z_B1 >= 100)
		z_B1 = -100;
	r_drawball(temp1, z_B1, 0.2, 0);

	if (z_B2 >= 100)
		z_B2 = -100;
	r_drawball(temp2, z_B2, 0.4, 0);

	if (z_B3 >= 100)
		z_B3 = -100;
	r_drawball(temp3, z_B3, 0.6, 0);

	if (z_B4 >= 100)
		z_B4 = -100;
	r_drawball(temp4, z_B4, 0.8, 0);

	srand((double)time(NULL));

	if (z_B == -100) {
		r_position = rand() % 18;
		temp = r_position;
	}
	else if (z_B1 == -100) {
		r_position = rand() % 18;
		temp1 = r_position;
	}
	else if (z_B2 == -100) {
		r_position = rand() % 15;
		temp2 = r_position + 3;
	}
	else if (z_B3 == -100) {
		r_position = rand() % 16;
		temp3 = r_position + 2;
	}
	else if (z_B4 == -100) {
		r_position = rand() % 17;
		temp4 = r_position + 1;
	}
	
}

void MyTimer(int Value) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	spin_leaf();

	L_theta += 0.1;
	L_theta2 += 0.1;
	spinball();
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}

void spin_leaf() {
	
	if (L_theta > 360) L_theta = L_theta - 360;
	if (L_theta2 > 90) L_theta2 = L_theta2 - 90;
	L_Arm_x = sin(L_theta2) * 50;
	R_Arm_x = -L_Arm_x;
	L_Leg_x = sin(L_theta2) * 50;
	R_Leg_x = -L_Leg_x;
	L_Leaf_x = L_theta * 10000;
	R_Leaf_x = L_theta * 10000;
}

void drawFloor() {
	float widG, widFloorX, widFloorZ, x0, z0;
		short i, j, nx, nz;
		int a;

		widFloorX = 100.0f;
		widFloorZ = 2000.0f;
		widG = 12.5f;
		nx = (short)(widFloorX / widG);
		nz = (short)(widFloorZ / widG);
		glPushAttrib(GL_CURRENT_BIT);

		glColor3f(0.2f, 0.2f, 0.2f);

		for (j = 0; j<nz; j++) {
			for (i = 0; i<nx; i++) {
				a = (double)(i + j);
				if (fmod(a, 2.0) == 0.0) {
					//glColor4f(1.0f, 0.3f, 1.0f, 1.0f);
					colorChange(8);
				}
				else {
					//glColor4f(.7f, 0.0f, 1.0f, 1.0f);
					colorChange(7);
				}
				glPushMatrix();
				x0 = -widFloorX / 2.0f + (float)i*widG + widG / 2.0f;
				z0 = -widFloorZ / 2.0f + (float)j*widG + widG / 2.0f;
				glTranslatef(x0, -5.0f, z0);
				glBegin(GL_QUADS);
				glNormal3f(0.0f, 1.0f, 0.0f); //z방향 
				glVertex3f(widG / 2.0f, -0.1f, -widG / 2.0f);
				glVertex3f(-widG / 2.0f, -0.1f, -widG / 2.0f);
				glVertex3f(-widG / 2.0f, -0.1f, widG / 2.0f);
				glVertex3f(widG / 2.0f, -0.1f, widG / 2.0f);
				glEnd();
				glPopMatrix();
			}
		}
		glPopAttrib();
}

void drawwall(int x)
{
	float widG, widFloorY, widFloorZ, y0, z0;
	short i, j, ny, nz;
	int a;

	widFloorY = 200.0f;
	widFloorZ = 2000.0f;
	widG = 12.5f;
	ny = (short)(widFloorY / widG);
	nz = (short)(widFloorZ / widG);
	glPushAttrib(GL_CURRENT_BIT);

	for (j = 0; j<nz; j++) {
		for (i = 0; i<ny; i++) {
			a = (double)(i + j);
			if (fmod(a, 2.0) == 0.0) {
				colorChange(9);
			}
			else {
				colorChange(9);
			}
			glPushMatrix();
			y0 = -widFloorY / 2.0f + (float)i*widG + widG / 2.0f;
			z0 = -widFloorZ / 2.0f + (float)j*widG + widG / 2.0f;
			glTranslatef(x, y0, z0);
			glTranslatef(0, 45, 0);
			glBegin(GL_QUADS);
			if (x >= 0) {
				glNormal3f(1.0f, .0f, 0.0f); //z방향 
				glVertex3f(-0.1f, widG / 2.0f, -widG / 2.0f);
				glVertex3f(-0.1f, -widG / 2.0f, -widG / 2.0f);
				glVertex3f(-0.1f, -widG / 2.0f, widG / 2.0f);
				glVertex3f(-0.1f, widG / 2.0f, widG / 2.0f);
			}
			else if (x<0) {
				glNormal3f(1.0f, .0f, 0.0f); 
				glVertex3f(-0.1f, -widG / 2.0f, widG / 2.0f);
				glVertex3f(-0.1f, -widG / 2.0f, -widG / 2.0f);
				glVertex3f(-0.1f, widG / 2.0f, -widG / 2.0f);
				glVertex3f(-0.1f, widG / 2.0f, widG / 2.0f);

			}

			glEnd();
			glPopMatrix();

		}
	}
	glPopAttrib();

}

void keyboard_handler(unsigned char key, int x, int y) {
	if (key == 'd') { x_C = x_C + 30.0; tap = true; 	if (x_C > 30.0) x_C = 30.0; printf("%f", x_C); }
	if (key == 'a') {
		x_C = x_C - 30.0; tap = true; 	if (x_C < -30.0) x_C = -30.0; printf("%f", x_C);
	}
	if (key == 'n') { eyex = 0.0, eyey = 0.0, eyez = 1.0, atx = 0, aty = 0, atz = 0, upx = 0, upy = 1, upz = 0; printf("new\n"); }
	glutPostRedisplay();
}

void mouse_handler(int btn, int state, int x, int y) {

	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		originX = x;
		originY = y;
		printf("Origin: %f, %f\n", originX, originY);
	}
	else if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		dX = x;
		dY = y;
		printf("Delta: %f, %f\n", dX, dY);
	}

	if (originX != 0.0 && originY != 0.0 && dX != 0.0 && dY != 0.0)
		click = true;

	if (click == true) {
		delta_y = dY - originY;
		delta_x = dX - originX;
		if (fabsf(delta_x) - fabsf(delta_y) >= 0) {
			atx += delta_x / 500;
			delta_y = 0.0;
			printf("delta_x > delta_y, %f\n", delta_x);
		}
		else {
			aty += delta_y / 500;
			delta_x = 0.0;
			printf("delta_x < delta_y, %f\n", delta_y);
		}
		originX = originY = dX = dY = 0;
		click = false;
		printf("\n");
	}
	glutPostRedisplay();
}

void drawball(double x_B, double z_B, int n)// 공그리기
{
	if (n == 0) {
		glPushMatrix();
		int r = (double)rand() / RAND_MAX *(10 - 0) + 1;
		colorChange(r);
		glTranslatef(x_B, 5., z_B);
		glRotatef(B_Rotate, 1, 0, 0);
		glutSolidSphere(10.0, 20, 16);
	}
	else {
		glPushMatrix();
		colorChange(1);
		glTranslatef(x_B, 5., z_B);
		glRotatef(B_Rotate, 1, 0, 0);
		glutSolidSphere(10.0, 20, 16);
	}
	glPopMatrix();
}

void r_drawball(int temp, double z, double time, int n)
{	if (aa >= time) {
		if (temp == 0 || temp == 1) {
			drawball(0.0, z, n);
		}
		else if (temp == 2 || temp == 3 || temp == 4) {
			drawball(20.0, z, n);
		}
		else if (temp == 5 || temp == 6 || temp == 7) {
			drawball(-20.0, z, n);
		}
		else if (temp == 8 || temp == 9 || temp == 10 || temp == 11) {
			drawball(0.0, z, n);
			drawball(20.0, z, n);
		}
		else if (temp == 12 || temp == 13 || temp == 14 || temp == 15) {

			drawball(0.0, z, n);
			drawball(-20.0, z, n);
		}
		else if (temp == 16 || temp == 17) {
			drawball(20.0, z, n);
			drawball(-20.0, z, n);
		}

	}

}

void spinball() {

	stage += 1;
	B_Rotate += 10; //공의 회전
	if (B_Rotate == 360)
		B_Rotate = 0;

	if (z_C < 70)
		z_C += 4;

	if (aa <= 3)
		aa += 0.01;
	else
		aa = 2.8;
	//공의 움직임
	z_B += 2 + speedadd;

	if (aa >= 0.2) {
		z_B1 += 2 + speedadd;
	}
	if (aa >= 0.4) {
		z_B2 += 2 + speedadd;
	}
	if (aa >= 0.6) {
		z_B3 += 2 + speedadd;
	}
	if (aa >= 0.8) {
		z_B4 += 2 + speedadd;
	}

	if (stage == 500) {
		speedadd += 0.5; //공의 가속도
		R_stage += 1;
		stage = 0;
	}
	if (R_stage == 6)//레벨이 6이 되면 게임 종류
		GameState = 2;

}



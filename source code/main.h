#pragma once
#include<glut.h>
#include<stdlib.h>
#include<stdio.h>
double z_B, z_B1, z_B2, z_B3, z_B4, z_B5;	//볼의 z 값
double z_C, x_C;
int R_leg, R_arm;		//발과 다리를 돌리기 위한 값
double speedadd;	//볼의 속도추가 값
int GameState;
int stage;
int r_position;
void GLViewSetup();
int temp, temp1, temp2, temp3, temp4, temp5;
double aa;	//공의 연속출력을 위한 값
double phaiC;	//앙각
double thetaC;	//방향각
double distC;	//주시점에서 카메라까지의 거리	
GLfloat ratio;	//시체적의 가로넓이와 높이의 비율
double farZ;	//시체적의 뒷면
double nearZ;	//시체적의 앞면
double fov;		//시체적의 시야각
double cnt[3];	//주시점
double view[3];	//시점
GLfloat m_ZScale;
GLfloat m_YScale;
GLfloat m_XScale;
GLfloat m_zPos;
GLfloat m_yPos;
GLfloat m_xPos;
GLfloat theta[3];
GLfloat m_aLight;
GLfloat m_AFinalLight;
GLfloat m_SFinalLight;
GLfloat m_DFinalLight;
GLfloat m_sLight;
GLfloat m_dLight;
GLfloat m_xLP;
GLfloat m_yLP;
GLfloat m_zLP;
#pragma once
#include<glut.h>
#include<stdlib.h>
#include<stdio.h>
double z_B, z_B1, z_B2, z_B3, z_B4, z_B5;	//���� z ��
double z_C, x_C;
int R_leg, R_arm;		//�߰� �ٸ��� ������ ���� ��
double speedadd;	//���� �ӵ��߰� ��
int GameState;
int stage;
int r_position;
void GLViewSetup();
int temp, temp1, temp2, temp3, temp4, temp5;
double aa;	//���� ��������� ���� ��
double phaiC;	//�Ӱ�
double thetaC;	//���Ⱒ
double distC;	//�ֽ������� ī�޶������ �Ÿ�	
GLfloat ratio;	//��ü���� ���γ��̿� ������ ����
double farZ;	//��ü���� �޸�
double nearZ;	//��ü���� �ո�
double fov;		//��ü���� �þ߰�
double cnt[3];	//�ֽ���
double view[3];	//����
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
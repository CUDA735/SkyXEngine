
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

/*
gdefines.h
����������������
*/

#ifndef G_DEFINES
#define G_DEFINES

const half2 TexUV_Center = half2(0.5f,0.5f);

//������������ �������� ��� ����� ����� ��������������
#define GREEN_ALPHATEST_VALUE 	0.5

//���������� ��������� �������� ������ ����� ��� pssm [0,1]
#define PSSM_SHADING_LAST 		0.1

//�� ������� ����� ��������� ���������� ��� �������� �� �������� �� ���������� ���������� ��� ��������� �����
#define SHADOWGEN_JITTER_SCALE 1024.0

//��������� �� ������ �� ������� �� ����� ���������������� ������ motion blur (������� ��� ���� ����� �� ��������� ���)
#define PP_MOTION_BLUR_DISTNOBLUR 0.8

#define PI 3.141592654f

//�������� ����������� (���������� ��, ���������� ��)
//{
	
//������������ � �� ����������
#define SURFACE_NOTLIGHTING_NOTTRANSPARENCY 0.0

//���������� � ������������
#define SURFACE_LIGHTING_NOTTRANSPARENCY 	0.333333

//������������ � ����������
#define SURFACE_NOTLIGHTING_TRANSPARENCY 	0.666667

//���������� � ����������
#define SURFACE_LIGHTING_TRANSPARENCY 		1.0

//}

//�������� ��� tone mapping
//{

//������������ �������� � ����������� ��������� ����� � ��������� (����� �� ���� ������� �� 0)
#define TONE_MAPPING_ADAPT_ADD_BIAS 		0.0001f

//����� ������� ����� �������� �� ���������� ��������� ����� � ���������
#define TONE_MAPPING_DENOMENATOR			0.1f

//}

//�������� ������ ��� ��������������
//{
#define GREEN_R_LESSENING	c59
#define GREEN_R_VIEWPOS		c60
#define GREEN_R_BSPHERE		c61
#define GREEN_R_BBMAX		c62
#define GREEN_R_BBMIN		c63
//}

#else
	#error G_DEFINES double include
#endif
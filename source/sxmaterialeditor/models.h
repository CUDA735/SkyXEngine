
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

/*!
\file
������������ ���� ������ ������� ��� ��������� ����������
*/

#ifndef __ME_MODELS_H
#define __ME_MODELS_H

#include <gcore/sxgcore.h>

//! ������� � ���������� ����������� ������ �����
ISXDataStaticModel* CreateModelSphere();

//! ������� � ���������� ����������� ������ ����
ISXDataStaticModel* CreateModelCube();

//! ������� � ���������� ����������� ������ ���������� ���������
ISXDataStaticModel* CreateModelPlane();

#endif
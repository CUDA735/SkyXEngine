
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __CREATORTEXTURES_H
#define __CREATORTEXTURES_H

#include <gdefines.h>
#include <stdio.h>
#include <graphix/graphix.h>
#include <common/array.h>

extern IGXContext *g_pDevice;

//��������� ����������� ��������� ��������
struct CreatedTexture
{
	char Name[64];	//���
	IGXTexture2D* Texture;	//��������
	UINT Level;
	//float CoefFullScreen;		//���� ������ 0 �� ����� ������ �� Desc, ����� ��� ���������� ��������� ������� ������ �� ��� �����
};

class CreatorTextures
{
public:
	CreatorTextures();
	~CreatorTextures();

	ID Add(UINT width, UINT height, UINT levels, DWORD usage, GXFORMAT format, const char* name);

	void Delete(const char* text);
	void Delete(ID num);

	ID GetNum(const char* text);

	void OnLostDevice();
	void OnResetDevice();

	IGXTexture2D* GetTexture(const char* text);
	IGXTexture2D* GetTexture(ID num);
private:
	Array<CreatedTexture*> Arr;
};

#endif
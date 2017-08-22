
#ifndef __CREATORTEXTURES_H
#define __CREATORTEXTURES_H

#include <gdefines.h>
#include <stdio.h>
#include <d3d9.h>
#include <common/array.h>

extern report_func g_fnReportf;
extern IDirect3DDevice9* DXDevice;
extern D3DPRESENT_PARAMETERS D3DAPP;

//��������� ����������� ��������� ��������
struct CreatedTexture
{
	char Name[64];	//���
	IDirect3DTexture9* Texture;	//��������
	D3DSURFACE_DESC Desc;		//�������� ��������, ��� ��������������
	UINT Level;
	float CoefFullScreen;		//���� ������ 0 �� ����� ������ �� Desc, ����� ��� ���������� ��������� ������� ������ �� ��� �����
};

class CreatorTextures
{
public:
	CreatorTextures();
	~CreatorTextures();

	ID Add(UINT width, UINT height, UINT levels, DWORD usage, D3DFORMAT format, D3DPOOL pool, const char* name, float coeffullscreen);

	void Delete(const char* text);
	void Delete(ID num);

	ID GetNum(const char* text);

	void OnLostDevice();
	void OnResetDevice();

	IDirect3DTexture9* GetTexture(const char* text);
	IDirect3DTexture9* GetTexture(ID num);
private:
	Array<CreatedTexture*> Arr;
};

#endif
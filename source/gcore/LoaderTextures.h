
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __LOADERTEXTURES_H
#define __LOADERTEXTURES_H

#include <gdefines.h>
#include <d3d9.h>
#include <common/array.h>
#include <common/String.h>
#include "sxgcore.h"

void LibReport(int iLevel, const char *szFormat, ...);
extern IDirect3DDevice9 *g_pDXDevice;
extern D3DPRESENT_PARAMETERS g_oD3DAPP;

class LoaderTextures
{
public:
	LoaderTextures();
	~LoaderTextures();

	bool FileExists(const char* name);

	void ClearLoaded();

	void Delete(ID id);	//������� �������� id

	ID AddName(const char* name, LOAD_TEXTURE_TYPE type, ID* iddir = 0, ID* idname = 0);	//��������� ��� ��������, ������ �������� �� ��� ID (��������� � �������)
	ID GetID(const char* name);		//�������� id �� �����
	void GetName(ID id, char* name);//�������� ��� �� id

	ID Create(const char* name, IDirect3DTexture9* tex);	//������� ����� ��� �������� tex
	ID Update(const char* name, LOAD_TEXTURE_TYPE type);			//������������� �������� name
	void Update(ID id);

	void LoadTextures();	//�������� ���� ������� ������������ � �������

	IDirect3DTexture9* GetTexture(ID id);//�������� �������� �� id

private:

	//��������� ����������� ����� � ��� �������� � ���, � ������ ���� id ��� �������
	struct TLPath
	{
		TLPath(){}
		~TLPath()
		{
			for (int i = 0; i < ArrTex.size(); ++i)
			{
				mem_delete(ArrTex[i]);
			}
		}

		String Path;	//��� �����

		struct TLTex
		{
			TLTex(){ id = -1; type = LOAD_TEXTURE_TYPE_LOAD; }
			TLTex(ID _id, const char* _name, LOAD_TEXTURE_TYPE _type){ id = _id; name = _name; type = _type; }
			
			ID id;
			String name;
			LOAD_TEXTURE_TYPE type;
		};
		
		Array<TLTex*> ArrTex;
	};

	struct TexAndName
	{
		TexAndName(){ tex = 0; IDDir = -1; }
		~TexAndName(){ mem_release(tex); }
		String name;
		IDirect3DTexture9* tex;
		ID IDDir;
		
	};

	Array<TLPath*> Arr;
	int CurrFirstFree;

	Array<TexAndName*> ArrTextures;
	Array<ID> ArrIDsLoad;
};

#endif

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
#include <common/file_utils.h>
#include "sxgcore.h"

void LibReport(int iLevel, const char *szFormat, ...);
extern IDirect3DDevice9 *g_pDXDevice;
extern D3DPRESENT_PARAMETERS g_oD3DAPP;

//! ��������� �������
class �LoaderTextures
{
public:
	�LoaderTextures();
	~�LoaderTextures();

	//! ���������� �� �������� �� �����
	bool fileExists(const char *szName);

	//! ������� ��� ����������� ��������
	void clearLoaded();

	//! ������� �������� id
	void deleteTexture(ID id);	

	//! ��������� ��� ��������, ������ �������� �� ��� ID (��������� � �������)
	ID addName(const char *szName, LOAD_TEXTURE_TYPE type, ID *pIDdir = 0, ID *pIDname = 0);

	//! �������� id �� �����
	ID getID(const char *szName);

	//�������� ��� �� id
	void getName(ID id, char *szName);

	//! ������� ����� ��� �������� tex
	ID create(const char *szName, IDirect3DTexture9 *pTex);

	//! ������������� �������� name
	ID update(const char *szName, LOAD_TEXTURE_TYPE type);

	//! ������������� �������� �� id
	void update(ID id);

	//! �������� ���� ������� ������������ � �������
	void loadTextures();	

	//! �������� �������� �� id
	IDirect3DTexture9* getTexture2d(ID id);

	//! �������� �������� �� id
	IDirect3DCubeTexture9* getTextureCube(ID id);

	//! ��������� ��� �������� �� ���������� szDir (������������ ���������� �������) � ��������� �� ������ �����������
	bool addConstAllInDir(const char *szDir);

private:

	//! ��������� ����������� ����� � ��� �������� � ���, � ������ ���� id ��� �������
	struct CPath
	{
		CPath(){}
		~CPath()
		{
			for (int i = 0; i < m_aTextures.size(); ++i)
			{
				mem_delete(m_aTextures[i]);
			}
			m_aTextures.clear();
		}

		//! ��� �����
		String m_sPath;	

		//! ������� ������������� ��������
		struct CTex
		{
			CTex(){ m_id = -1; m_type = LOAD_TEXTURE_TYPE_LOAD; }
			CTex(ID id, const char *szNname, LOAD_TEXTURE_TYPE type){ m_id = id; m_sName = szNname; m_type = type; }
			
			//! ���������� �������������
			ID m_id;

			//! ��� ��������
			String m_sName;

			//! ��� #LOAD_TEXTURE_TYPE
			LOAD_TEXTURE_TYPE m_type;
		};
		
		Array<CTex*> m_aTextures;
	};

	//! ������������� ��������
	struct CTexture
	{
		CTexture(){ m_pTex2d = 0; m_pTexCube = 0; m_idDir = -1; }
		~CTexture(){ mem_release(m_pTex2d); mem_release(m_pTexCube); }

		//! ���
		String m_sName;

		//! 2� ��������
		IDirect3DTexture9 *m_pTex2d;

		//! ���������� ��������
		IDirect3DCubeTexture9 *m_pTexCube;

		//! ���������� id ����������
		ID m_idDir;
	};

	//**********************************************************************

	//! ������ ����� � ����������
	Array<CPath*> m_aPathes;

	int CurrFirstFree;

	//! ������ �������, ���� == �������������
	Array<CTexture*> m_aTextures;

	//! ������ id ������� �� ��������
	Array<ID> m_aQueueToLoadIDs;

	//**********************************************************************

	//! �������� 2d ��������
	IDirect3DTexture9* loadTexture2d(const char *szPath);

	//! �������� ���������� ��������
	IDirect3DCubeTexture9* loadTextureCube(const char *szPath);

	//! ���������� ��� ����� ��������
	D3DRESOURCETYPE getTypeFileTex(const char *szPath);
};

#endif
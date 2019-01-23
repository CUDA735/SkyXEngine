
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __LOADERTEXTURES_H
#define __LOADERTEXTURES_H

#include <gdefines.h>
#include <graphix/graphix.h>
#include <common/array.h>
#include <common/String.h>
#include <common/file_utils.h>
#include "sxgcore.h"

void LibReport(int iLevel, const char *szFormat, ...);
extern IGXContext *g_pDevice;

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
	ID create(const char *szName, IGXTexture2D *pTex);

	//! ������������� �������� name
	ID update(const char *szName, LOAD_TEXTURE_TYPE type);

	//! ������������� �������� �� id
	void update(ID id);

	//! �������� ���� ������� ������������ � �������
	void loadTextures();	

	//! �������� �������� �� id
	IGXTexture2D* getTexture2d(ID id);

	//! �������� �������� �� id
	IGXTextureCube* getTextureCube(ID id);

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
		IGXTexture2D *m_pTex2d;

		//! ���������� ��������
		IGXTextureCube *m_pTexCube;

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
	IGXTexture2D* loadTexture2d(const char *szPath);

	//! �������� ���������� ��������
	IGXTextureCube* loadTextureCube(const char *szPath);
};

#endif
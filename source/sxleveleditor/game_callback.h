
#ifndef __GAME_CALLBACK_H
#define __GAME_CALLBACK_H

#include "skyxengine.h"
#include "level_editor.h"

//! ������������� ����� ���������� � ������������ �������� ������� 
LRESULT SXLevelEditor_ButtonGameTab_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//**************************************************************************

//! ���� �� ListViewGameClass
LRESULT SXLevelEditor_ListViewGameClass_Click();

//! ���������� ���������� �������� ��� ��������� �������� �������
LRESULT SXLevelEditor_EditGameValue_Enter(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//! ����� ������� ������ ��� ����� ��������� �������� �������
LRESULT SXLevelEditor_ButtonGameValue_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//! ������� ������� ������
LRESULT SXLevelEditor_ButtonGameCreate_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//**************************************************************************

//! ������� �������� �� ������� ��������
void SXLevelEditor_VeldStringGameConnections(
	proptable_t *pPropTable,	//!< ������� ������ ������� �������� pPropData (�������� ���� ������)
	propdata_t *pPropData,		//!< ����� ����� �� ������� ������ ���� � �������� �������� ���
	int iNumExclude,			//!< ��������� ������ ������� � ���� �������
	char *szStrOut,				//!< ������ � ������� ������������� ��� �������� ������
	int iSize					//!< ������ szStrOut	(�������� ���� ������)
	);

//! ���� �� ������� ����������
LRESULT SXLevelEditor_ListViewGameConnections_Click();

//! ��������� ��������� ����� � EditGameConnectionsName ����� ���� ���������������
LRESULT SXLevelEditor_EditGameConnectionsName_IN(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//! ���������� �������� ���������� � EditGameConnectionsName
LRESULT SXLevelEditor_EditGameConnectionsName_Enter(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//! ���������� ���� ���������� � ���������� � ����������� ����������
LRESULT SXLevelEditor_EditGameConnections_Enter(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//! �������� ������ ����������
LRESULT SXLevelEditor_ButtonGameConnectionsCreate_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//! �������� ����������� ����������
LRESULT SXLevelEditor_ButtonGameConnectionsDelete_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



#endif
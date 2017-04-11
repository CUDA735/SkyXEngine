//------------------------------------------------
// ����: SXGUI_edit.h
// ������� ��������: ����������� ���� ����� ������
// Project S.I.P for SkyXEngine (09,2012)
//------------------------------------------------

#ifndef SXGUI_EDIT_H
#define SXGUI_EDIT_H

#include <SXGUIWinApi\SXGUI_base.h>
#if defined(_USRDLL)
#include <SXGUIWinApi\SXGUI_up_down.cpp>
#else
#include <SXGUIWinApi\SXGUI_up_down.h>
#endif

#define SXGUI_EDIT_ALIGN_LEFT	0
#define SXGUI_EDIT_ALIGN_RIGHT	1
#define SXGUI_EDIT_ALIGN_CENTER	2

#pragma once

class SXGUIEdit : public SXGUITextual, public virtual ISXGUIEdit
{
public:
	SXGUIEdit();// {}
	~SXGUIEdit();// {}
	SXGUIEdit(const char* caption,WORD x,WORD y,WORD width,WORD heigth,DWORD exstyle,DWORD style,HWND parent,WNDPROC handler,DWORD id);
	SXGUIEdit(const char* caption,WORD x,WORD y,WORD width,WORD heigth,HWND parent,WNDPROC handler,DWORD id);

	bool ReadOnly();		//����������� �� �������� "������ ��� ������"
	bool ReadOnly(bool bf);	//������������ ��������� "������ ��� ������", ���������� ��������� ��������

	//��������� ������� ����� ���������� �� *
	bool Password();		//����������� �� ������� ������� ������
	bool Password(bool bf);	//������������ ��������� ������� ������

	WORD Align();			//���������� ���� ������������ ������
	bool Align(WORD align);	//������������� ������������
};

#endif
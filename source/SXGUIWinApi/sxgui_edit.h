
#ifndef SXGUI_EDIT_H
#define SXGUI_EDIT_H

#include <SXGUIWinApi\SXGUI_base.h>

#pragma once

class SXGUIEdit : public SXGUITextual, public virtual ISXGUIEdit
{
public:
	SXGUIEdit();
	~SXGUIEdit();
	SXGUIEdit(const char* caption,WORD x,WORD y,WORD width,WORD heigth,DWORD exstyle,DWORD style,HWND parent,WNDPROC handler,DWORD id);
	SXGUIEdit(const char* caption,WORD x,WORD y,WORD width,WORD heigth,HWND parent,WNDPROC handler,DWORD id);

	bool ReadOnly();		//����������� �� �������� "������ ��� ������"
	bool ReadOnly(bool bf);	//������������ ��������� "������ ��� ������", ���������� ��������� ��������

	//��������� ������� ����� ���������� �� *
	bool Password();		//����������� �� ������� ������� ������
	bool Password(bool bf);	//������������ ��������� ������� ������

	int Align();			//���������� ���� ������������ ������
	bool Align(int align);	//������������� ������������
};

#endif
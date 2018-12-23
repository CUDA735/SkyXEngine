
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __SXGUI_EDIT_H
#define __SXGUI_EDIT_H

#include "base.h"


class CGUIEdit : public CGUITextual, public virtual ISXGUIEdit
{
public:
	CGUIEdit();
	~CGUIEdit();
	CGUIEdit(const char* caption, WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, ID idObj);
	CGUIEdit(const char* caption, WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, ID idObj);

	bool getReadOnly();		//����������� �� �������� "������ ��� ������"
	bool setReadOnly(bool bf);	//������������ ��������� "������ ��� ������", ���������� ��������� ��������

	//��������� ������� ����� ���������� �� *
	bool getStatePassword();		//����������� �� ������� ������� ������
	bool setStatePassword(bool bf);	//������������ ��������� ������� ������

	int getAlign();				//���������� ���� ������������ ������
	bool setAlign(int align);	//������������� ������������
};

#endif
//----------------------------------------
// ����: SXGUI_combo_box.h
// ������� ��������: ����������� combo box
// Project S.I.P for SkyXEngine (09,2012)
//----------------------------------------

#ifndef SXGUI_COMBO_BOX_H
#define SXGUI_COMBO_BOX_H

#include <SXGUIWinApi\SXGUI_base.h>

#pragma once

class SXGUIComboBox : public SXGUIComponent, public virtual ISXGUIComboBox
{
public:
	SXGUIComboBox();
	SXGUIComboBox(const char* caption,WORD x,WORD y,WORD width,WORD heigth,DWORD exstyle,DWORD style,HWND parent,WNDPROC handler,DWORD id);

	//�����: (parent != 0 ? WS_CHILD : 0) | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS
	SXGUIComboBox(const char* caption,WORD x,WORD y,WORD width,WORD heigth,HWND parent,WNDPROC handler,DWORD id);

	bool	InsertItem(int index,const char* text);		//������� ������ � ������
	bool	DeleteItem(int index);						//�������� ������

	int		GetCount();									//���������� �����

	bool	SetSel(int index);							//�������� ������������ ������
	int		GetSel();									//����� ���������� ������

	bool	SetItemData(int index,LPARAM data);			//��������� ��� ������ userdata (32 ����)
	LPARAM	GetItemData(int index);						//��������� userdata

	bool	Clear();									//������� ��� ��������

	bool	SetItemText(int index,const char* text);	//������� ������ � ������, ������� ������
	char*	GetItemText(int index);						//�������� ����� �� ������ (���������� ��������� ������ � ����, ���� ��� ������ �� ����������)
	void	GetItemText(int index,char* buf);			//�������� ����� �� ������ 
	int		GetItemTextLength(int index);				//�������� ����� ������ �� ������
	bool	AddItem(const char* text);					//��������� � ����� ����� ������
};

#endif
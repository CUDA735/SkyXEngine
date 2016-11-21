//-----------------------------------------------------
// ����: SXGUI_list_box.h
// ������� ��������: ����������� list box
// Project S.I.P for SkyXEngine (09,2012)
//-----------------------------------------------------

#ifndef SXGUI_LIST_BOX_H
#define SXGUI_LIST_BOX_H

#include <SXGUIWinApi\SXGUI_base.h>

#pragma once

class SXGUIListBox : public SXGUIComponent, public virtual ISXGUIListBox
{
public:
	SXGUIListBox();
	SXGUIListBox(const char* caption,WORD x,WORD y,WORD width,WORD heigth,DWORD exstyle,DWORD style,HWND parent,WNDPROC handler,DWORD id);
	SXGUIListBox(const char* caption,WORD x,WORD y,WORD width,WORD heigth,HWND parent,WNDPROC handler,DWORD id,bool miltiple_sel);

	bool	MultipleSel();	//������������ �� �������� �������������� ��������� �����

	bool	InsertItem(int index,const char* text);	//�������� ����� � ������ � ������� index
	bool	AddItem(const char* text);				//�������� ������ � ����� ������
	int		GetCountItem();							//���������� ���������� �����

	bool	DeleteItem(int index);					//������� ������ � ������� index

	bool	SetSel(int index);						//�������� ������ � ������� index
	int		GetSel();

	bool	SetItemData(int index,LPARAM data);		//���������� userdata ��� ������ � ������� index
	LPARAM	GetItemData(int index);					//���������� userdata

	bool	Clear();								//��������

	bool	SetTextItem(int index,const char* text);//���������� ����� � ������ � ������� index
	char*	GetItemText(int index);					//���������� ����� �� ������ !!!������ ���������� � ����
	void	GetItemText(int index,char* buf);		//���������� ����� �� ������

	int		GetItemTextLength(int index);			//���������� ����� ������ � ������

	//��������������� �����, ���� this->MultipleSel() == true
	int		GetMultipleSelCount();					//���������� ���������� ���������� �����

	bool	SetMultipleSel(int index,bool sel);		//������������� ��������/�� �������� ������
	bool	GetMultipleSel(int index);				//���������� �������� �� ������

	int*	GetMultipleSelArr();					//���������� ������ � �������� ���������� �����

	//SXGUIFuctinon
	bool ScrollBars(bool h,bool v);
	bool ScrollBarV();
	bool ScrollBarH();
	bool ScrollLine(WORD scroll,WORD dir,int count);
};

#endif
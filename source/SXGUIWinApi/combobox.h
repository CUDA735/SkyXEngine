
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __SXGUI_COMBO_BOX_H
#define __SXGUI_COMBO_BOX_H

#include "base.h"


class CGUIComboBox : public CGUIComponent, public virtual ISXGUIComboBox
{
public:
	CGUIComboBox();
	CGUIComboBox(WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, ID idObj);

	CGUIComboBox(WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, ID idObj);

	bool insertItem(int index,const char* text);		//������� ������ � ������
	bool deleteItem(int index);						//�������� ������

	int	getCount();									//���������� �����

	bool setSel(int index);							//�������� ������������ ������
	int	getSel();									//����� ���������� ������

	bool setItemData(int index,LPARAM data);			//��������� ��� ������ userdata (32 ����)
	LPARAM getItemData(int index);						//��������� userdata

	bool clear();									//������� ��� ��������

	bool setItemText(int index,const char* text);	//������� ������ � ������, ������� ������
	void getItemText(int index,char* buf);			//�������� ����� �� ������ 
	int	getItemTextLength(int index);				//�������� ����� ������ �� ������
	bool addItem(const char* text);					//��������� � ����� ����� ������
};

#endif
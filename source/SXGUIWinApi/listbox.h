
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __SXGUI_LIST_BOX_H
#define __SXGUI_LIST_BOX_H

#include "base.h"


class CGUIListBox : public CGUIComponent, public virtual ISXGUIListBox
{
public:
	CGUIListBox();
	CGUIListBox(WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, ID idObj);
	CGUIListBox(WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, ID idObj, bool miltiple_sel);

	bool getStateMultiSel();	//������������ �� �������� �������������� ��������� �����
	void setStateMultiSel(bool isMultiSel);

	bool insertItem(int index,const char* text);	//�������� ����� � ������ � ������� index
	bool addItem(const char* text);				//�������� ������ � ����� ������
	int getItemCount();							//���������� ���������� �����

	bool deleteItem(int index);					//������� ������ � ������� index

	bool setSel(int index);						//�������� ������ � ������� index
	int	getSel();

	bool setItemData(int index,LPARAM data);		//���������� userdata ��� ������ � ������� index
	LPARAM getItemData(int index);					//���������� userdata

	bool clear();								//��������

	bool setItemText(int index, const char* text);//���������� ����� � ������ � ������� index
	void getItemText(int index,char* buf);		//���������� ����� �� ������

	int	getItemTextLength(int index);			//���������� ����� ������ � ������

	//��������������� �����, ���� this->MultipleSel() == true
	int getMultiSelCount();					//���������� ���������� ���������� �����

	bool setMultiSel(int index,bool sel);		//������������� ��������/�� �������� ������
	bool getMultiSel(int index);				//���������� �������� �� ������

	
	int getMultiSelArr(int **ppArr);					//���������� ������ � �������� ���������� �����
};

#endif
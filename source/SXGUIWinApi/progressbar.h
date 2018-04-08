
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __SXGUI_PROGRESS_BAR_H
#define __SXGUI_PROGRESS_BAR_H

#include "base.h"


class CGUIProgressBar : public CGUIComponent, public virtual ISXGUIProgressBar
{
public:
	CGUIProgressBar();
	CGUIProgressBar(WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, ID idObj);
	CGUIProgressBar(WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, ID idObj, bool vertical, bool smooth);

	//��������/���������� ������� ���������
	int getPos();				//���������� ������� �������
	int setPos(int pos);		//���������� ������ �������

	//��������/���������� ������ ���� ���������
	int getStep();				//���������� ������� ������ ����
	int setStep(int step);		//���������� ������ ������ ����

	//���������� �������������� �������
	int setPosSteps(int steps);	//���������� ������� �� ���������� �����
	int setOneStep();			//��������� ������� �� ���� ���

	//������������� ������� �������� � ��������� ���������
	//��� ������� ���������� ���������� true, ����� false
	bool setMinMax(int min,int max);	

	//���������� �����������/������������ ������� ���������
	int getMin();
	int getMax();

	//����������/�������� ���� ������� (���������� ���� ��������� ������� RGB(51,153,255))
	bool setColorBar(DWORD dwColor);	//��� ������� ���������� ���������� true, ����� false
	DWORD getColorBar();

	//����������/�������� ���� ���� (���������� ���� ����� ����� ���� ��������)
	bool setColorBk(DWORD dwColor); //��� ������� ���������� ���������� true, ����� false
	DWORD getColorBk();
};

#endif

#ifndef SXGUI_PROGRESS_BAR_H
#define SXGUI_PROGRESS_BAR_H

#include <SXGUIWinApi\SXGUI_base.h>

#pragma once

class SXGUIProgressBar : public  SXGUIComponent, public virtual ISXGUIProgressBar
{
public:
	SXGUIProgressBar();
	SXGUIProgressBar(WORD x,WORD y,WORD width,WORD heigth,DWORD exstyle,DWORD style,HWND parent,WNDPROC handler,DWORD id);
	SXGUIProgressBar(WORD x,WORD y,WORD width,WORD heigth,HWND parent,WNDPROC handler,DWORD id,bool vertical,bool smooth);

	//��������/���������� ������� ���������
	int GetPos();				//���������� ������� �������
	int SetPos(int pos);		//���������� ������ �������

	//��������/���������� ������ ���� ���������
	int GetStep();				//���������� ������� ������ ����
	int SetStep(int step);		//���������� ������ ������ ����

	//���������� �������������� �������
	int SetPosSteps(int steps);	//���������� ������� �� ���������� �����
	int SetOneStep();			//��������� ������� �� ���� ���

	//������������� ������� �������� � ��������� ���������
	//��� ������� ���������� ���������� true, ����� false
	bool SetMinMax(int min,int max);	

	//���������� �����������/������������ ������� ���������
	int GetMin();
	int GetMax();

	//����������/�������� ���� ������� (���������� ���� ��������� ������� RGB(51,153,255))
	bool SetBarColor(BYTE r, BYTE g, BYTE b);	//��� ������� ���������� ���������� true, ����� false
	DWORD GetBarColor();

	//����������/�������� ���� ���� (���������� ���� ����� ����� ���� ��������)
	bool SetBkColor(BYTE r, BYTE g, BYTE b); //��� ������� ���������� ���������� true, ����� false
	DWORD GetBkColor();
};

#endif
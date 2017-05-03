
#ifndef SXGUI_HINT_H
#define SXGUI_HINT_H

#include <windows.h>
#include <commctrl.h>

#include <SXGUIWinApi\SXGUI_base.h>

#pragma once

class SXGUIHint : public virtual ISXGUIHint
{
public:
	SXGUIHint();
	SXGUIHint(HWND parent);
	~SXGUIHint();
	void Release(){ mem_del(this); }
	//autopop - ����� ������
	//init - ������� ���� ��������� ��������� ����� ��������� �������
	void SetDelayTime(DWORD init,DWORD autopop);

	bool Parent(HWND parent);
	HWND Parent();

	HWND GetHWND();

	void Visible(bool bf);
	bool Visible();

	void SetText(const char* text);	//��������� ������ ���������
	const char* GetText();				//���������� ��������� �� ����� ���������, ��������� ��� ������ �����������
	void GetText(char* buf);

protected:
	HWND WindowHandle;
	HWND ParentHandle;
	TOOLINFO Hint;
	char hint[SX_HINT_COUNT_BUF_SIZE];
	bool IsVisible;
};

#endif
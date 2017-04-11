//-----------------------------------------------------
// ����: SXGUI_memo.h
// ������� ��������: memo ������������� �� edit
// Project S.I.P for SkyXEngine (09,2012)
//-----------------------------------------------------

#ifndef SXGUI_MEMO_H
#define SXGUI_MEMO_H

#if defined(_USRDLL)
#include <SXGUIWinApi\SXGUI_edit.cpp>
#endif

#pragma once

class SXGUIMemo : public SXGUIEdit, public virtual ISXGUIMemo
{
public:
	SXGUIMemo();
	SXGUIMemo(const char* caption,WORD x,WORD y,WORD width,WORD heigth,DWORD exstyle,DWORD style,HWND parent,WNDPROC handler,DWORD id);
	SXGUIMemo(const char* caption,WORD x,WORD y,WORD width,WORD heigth,HWND parent,WNDPROC handler,DWORD id);

	bool WordWrap();		//���������� �� ����������� ����
	bool WordWrap(bool bf);	//������������ ��������� ����������� ����

	//SXGUIFuctinon
	bool ScrollBars(bool h,bool v);
	bool ScrollBarV();
	bool ScrollBarH();
	bool ScrollLine(WORD scroll,WORD dir,int count);
};

#endif
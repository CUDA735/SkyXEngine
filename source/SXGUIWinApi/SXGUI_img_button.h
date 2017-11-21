
#ifndef SXGUI_IMG_BUTTON_H
#define SXGUI_IMG_BUTTON_H

#include <SXGUIWinApi\SXGUI_base.h>

#pragma once

class SXGUIButtonImg : public SXGUIComponent, public virtual ISXGUIButtonImg
{
public:
	SXGUIButtonImg();
	SXGUIButtonImg(const char* path,WORD x,WORD y,WORD width,WORD heigth,DWORD alpha_color,DWORD bk_color,HWND parent,WNDPROC handler,DWORD id);
	SXGUIButtonImg(WORD button,WORD x,WORD y,WORD width,WORD heigth,DWORD alpha_color,DWORD bk_color,HWND parent,WNDPROC handler,DWORD id);
	void Release(){ mem_del(this); }
	~SXGUIButtonImg();

	void ReInitImage(const char* path);

	void InitCallBack();
	
	void GetPathForImg(char* buf);

	void SetColorFrame(BYTE r, BYTE g, BYTE b);	
	void SetColorFrame(DWORD color);			
	DWORD GetColorFrame();						

	void SetColorBk(BYTE r, BYTE g, BYTE b);	
	void SetColorBk(DWORD color);			
	DWORD GetColorBk();						

	void SetColorAlpha(BYTE r, BYTE g, BYTE b);	
	void SetColorAlpha(DWORD color);			
	DWORD GetColorAlpha();						

	void SetEnable(bool bf);	//!< ��������� ��������� ������ (�������/��������)
	bool GetEnable();			//!< ���������� ��������� ������ (�������/��������)

	void SetEnableActive(bool bf);	//!< ��������� ��������� ���������� ������ (��������/���������)
	bool GetEnableActive();			//!< �������� �� ��������� ���������� ������?

	void SetParentGroup(bool bf);	//!< ���������� ������/�� ������ ������ � ������ ��������� ����� �� ������ ������ ��������
	bool GetParentGroup();

	BITMAP Bitmap;
	HANDLE HBitMap;

	bool IsImages;

	DWORD AlphaColor;	//!< ���� ������� ����� ��������
	DWORD BkColor;		//!< ���� ���� ������
	DWORD FrameColor;	//!< ���� ���� ������

	WORD Pos;			//!< ������� � ������� ������� ������
	bool PosBf[3];		//!< ����� �� ����������� ���������

	bool EnableState;	//!< ��������� ������ (�������/��������)

	bool EnableBf;		//!< �������� �� ��������� ���������� ������
	bool EnableGroup;	//!< �������� �� ������ � ������ ���� �������� ��������� ��������, ��� ���������� ����� �������������� ������ ��� �������� ������ ������


private:
	char PathForImg[1024];
};

#endif
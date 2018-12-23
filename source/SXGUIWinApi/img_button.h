
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __SXGUI_IMG_BUTTON_H
#define __SXGUI_IMG_BUTTON_H

#include "base.h"


class CGUIButtonImg : public CGUIComponent, public virtual ISXGUIButtonImg
{
public:
	CGUIButtonImg();
	CGUIButtonImg(const char* path, WORD x, WORD y, WORD width, WORD heigth, DWORD alpha_color, DWORD bk_color, HWND parent, WNDPROC handler, ID idObj);
	CGUIButtonImg(WORD button, WORD x, WORD y, WORD width, WORD heigth, DWORD alpha_color, DWORD bk_color, HWND parent, WNDPROC handler, ID idObj);
	void Release(){ mem_del(this); }
	~CGUIButtonImg();

	void reInitImage(const char* path);

	void initCallBack();
	
	void getPathForImg(char* buf);

	void setColorFrame(DWORD color);			
	DWORD getColorFrame();						

	void setColorBk(DWORD color);			
	DWORD getColorBk();						

	void setColorAlpha(DWORD color);			
	DWORD getColorAlpha();						

	void setEnable(bool bf);	//!< ��������� ��������� ������ (�������/��������)
	bool getEnable();			//!< ���������� ��������� ������ (�������/��������)

	void setActive(bool bf);	//!< ��������� ��������� ���������� ������ (��������/���������)
	bool getActive();			//!< �������� �� ��������� ���������� ������?

	void setParentGroup(bool bf);	//!< ���������� ������/�� ������ ������ � ������ ��������� ����� �� ������ ������ ��������
	bool getParentGroup();

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
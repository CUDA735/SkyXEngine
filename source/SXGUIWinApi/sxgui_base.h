//-------------------------------------------------
// ����: SXGUI_base.h
// ������� ��������: ��� ������� ������ � �������
// Project S.I.P for SkyXEngine (09,2012)(4,2013)(11,2014)
//------------------------------------------------


#ifndef SXGUI_BASE_H
#define SXGUI_BASE_H


extern class SXGUIButtonImg;

#include <SXGUIWinApi\SXGUI_hint.h>


//������ ������� �����, ������������ ��������� �� ������������
//���������� ������ ��� �������, �� ���� �������� � ���� ������� ������ ��� 
//���������� ��������
class SXGUIControl : public virtual ISXGUIControl
{
public:
	SXGUIControl();
	SXGUIControl(HWND window_handle,HWND parent_handle,WNDPROC handler);
	~SXGUIControl();
	void Release(){ mem_del(this); }
	void Init(HWND window_handle, HWND parent_handle, WNDPROC handler);	//���������� �����������, � ������������� ����� ����������

	HWND Parent();						//���������� HWND ��������
	bool Parent(HWND parent_handle);	//������������� ��������

	HWND GetHWND();

	void Visible(bool bf);				//��������� ��������� ��������
	bool Visible();						//����� �� �������?

	void SetFocus();					//���������� ����� �� �������
	bool Focus();						//���������� �� ����� �� ��������?
	//WNDPROC GetOldProc();// { return OldProc; }
	//WNDPROC OldProc;					//���� �������������� ����� ���������� (����� ����������� ��� Init) �� ������ ����������� �����

/*protected:
	HWND ParentHandle;
	HWND WindowHandle;*/
};
//WNDPROC SXGUIControl::GetOldProc(){ return this->OldProc; }

//������ � ������� ��������, ����� ������������ ���� ������ �� ����
//����� ����������� ���������� ������������ ���������
class SXGUIComponent : public SXGUIControl, public virtual ISXGUIComponent
{
public:
	SXGUIComponent();
	~SXGUIComponent();
	void Release(){ mem_del(this); }
	//������������� ����������� ������ ��� ���������� ���������
	void InitComponent(); //���������� �������� ����� �������������

	//������������ �� �������
	bool Enable();
	void Enable(bool bf);

	//������ �� �������
	//���� name == 0 �� �� ��������� �������� ������,
	//���� name[0] == 0 �� ��������� ����� gui
	//���� ��������� �������� � -1 �� �� �����������
	void SetFont(const char* name, int height, int width, int weight, int italic, int underline, int strike_out);
	void SetFont(HFONT* hfont);
	HFONT GetFont();
	
	bool IsParentFont();	//����������� �� ����� ��������
	HFONT ParentFont();		//�������� ������������ �����

	//������ �� ������� (� �.�. �����������)
	//style_add - ����������� �����
	//style_del - ���������
	bool ModifyStyle(long style_add, long style_del);
	bool ModifyExStyle(long style_add, long style_del);

	//�������������/���������� ������� ���� RECT �������� � ���������� �����������
	bool	SetWinRect(RECT* rect, bool alignment_screen_space);	//alignment_screen_space - ������������ �� ������ �������� ������� (������� ���� ����� ������ �����)
	RECT*	GetWinRect();
	void	GetWinRect(RECT* rect);

	//�������������/���������� ���������� ������� RECT �������� � ���������� �����������
	bool	SetClientRect(RECT* rect, bool alignment_screen_space);	//alignment_screen_space - ������������ �� ������ �������� ������� (������� ���� ����� ������ �����)
	RECT*	GetClientRect();
	void	GetClientRect(RECT* rect);

	//!!!������������� ����� �������� �������� ��������� ���������, ��� � ���� ������ ��� ����������������
	//��������� ���������
	void ShowHint(bool bf);
	bool ShowHint();

	//������ � ������� ��������� ��� ��������
	void SetHintText(const char* text);
	char* GetHintText();
	void GetHintText(char* buf);

	//������� ��� ������
	//set/get ���� ������
	void SetColorText(BYTE r, BYTE g, BYTE b);
	void SetColorText(DWORD color);
	DWORD GetColorText();

	//set/get ������������ ������� ���� ������
	void SetTransparentTextBk(bool bf);
	bool GetTransparentTextBk();

	//set/get ���� ������� ����
	void SetColorTextBk(BYTE r, BYTE g, BYTE b);
	void SetColorTextBk(DWORD color);
	DWORD GetColorTextBk();
	
	//set/get ���� ������� ���� ��������
	bool SetColorBrush(BYTE r, BYTE g, BYTE b);
	bool SetColorBrush(DWORD color);
	DWORD GetColorBrush();
	HBRUSH GetBrush();

	//��� ��� �������� ������������ �������
	///////////////////////////////////////

	//���������� �����������
	bool AddHandler(HandlerMsg Handler, UINT Msg, WPARAM wParam, bool considerWparam, LPARAM lParam, bool considerLparam, bool isMain);
	bool AddHandler(HandlerMsg Handler, UINT Msg);	//��� ��� ����������� �� ������� ���� �� �����������

	//key - ���� � ������� ������������
	HandlerMsg GetHandlerFunction(int key);	//���������� ������� ���������� 
	WORD GetCountKeyArrHandler();			//���������� ������ � ������� ������������

	//��� ��� �������� ������ ���������
	UINT GetMsgHandler(int key);
	WPARAM GetWParamHandler(int key);
	bool GetConsiderWParamHandler(int key);	//��������� WParam?
	LPARAM GetLParamHandler(int key);
	bool GetConsiderLParamHandler(int key);	//��������� LParam?

	bool IsMainFunction(int key);	//��� ������� �������?
	LRESULT ExecuteHandler(int key, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);	//��������� ������� ����������, � ��������� ���������� ���� ���������
	///////////////////////////////////////

	//SXRectBool GAlign;	//������ ������������ ������� �������� ��� ��������� �������� ��� ��������

	void UpdateSize();
	void UpdateRect();

	//������ ����������� ��� UpdateSize
	/*RECT ParentRect;		//��������� ��������
	RECT OffsetParentRect;	//�� ������� ��� ������� ��������
	RECT WinScreenRect;		//��������� �������� ���� ������������ �������� �����

	//������ ������������ ����� �� ������������� ����������� �������
	bool BFSizingChangeTop;		//�� ���� ���� ��������� ������ ... ���� ����
	bool BFSizingChangeBottom;	
	bool BFSizingChangeRight;	
	bool BFSizingChangeLeft;	

	bool BFMinSize;	//���������� �� ����������� ������? ���� �� �� ������ ��� MinSizeX � MinSizeY �� ����� �����������
	WORD MinSizeX;
	WORD MinSizeY;*/

/*protected:
	SXGUIHint *Hint;
	SXHandlerMsgStruct ArrHandler[SXGUI_COUNT_HANDLERS_MSG_IN_ARR];
	int CountKeyArrHandler;

	DWORD ColorBrush;	//���� ������� �����
	HBRUSH HBrush;

	DWORD ColorText;	//���� ������
	bool TransparenTextBf;	//������������ ������������? ���� true �� ������� ���� � ������ �� �����
	DWORD ColorTextBk;	//���� ������� ���� � ������*/
};

//������ (���� ����� �����) ��������, ��������������� �� ������������
//������������� ������� ��� ���������� ������ ����� (��� ������) ��������� ���������
class SXGUITextual : public SXGUIComponent, public virtual ISXGUITextual
{
public:
	SXGUITextual();
	~SXGUITextual();
	void Release(){ mem_del(this); }
	bool	SetText(const char* text);
	//const char*	GetText();
	void	GetText(char* buf, int size);
	int		GetTextLen();
};


#endif

#include <gdefines.h>

#include <windows.h>
#include <commctrl.h>
#include <Winuser.h>
#include <stdio.h>

//��� ������ ����� ���������������� ��� ���������� ���������� ��� � ����� ���������� ���������������� 
/*
//������������ ����� ��������
SXGUIRegClass::RegButtonImg();
SXGUIRegClass::RegToolBar();

INITCOMMONCONTROLSEX icex;

icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
icex.dwICC  = ICC_BAR_CLASSES;
InitCommonControlsEx(&icex);
*/

//��������������� ������� ����� ���������� �� ���� ����������� �����������: \
	SXGUIBaseHandlers::InitHandlerMsg(HWND);
//� ����� �������� �����������:\
	Wnd->AddHandler(MouseWheel,WM_MOUSEWHEEL,0,0,0,0,true);

//!!! main �������-���������� ����� ���� ������ ���� � ������ ���� ������!
//!!! �� ���� �� ��� �� ��� ���� ����� ���������� ::DefWindowProc(hwnd, msg, wParam, lParam)
//!!! � ��� ��������� ����������� CallWindowProc(Component->OldProc,hwnd, msg, wParam, lParam)

#define SXGUI_HORZ_SCROLL	0
#define SXGUI_VERT_SCROLL	1

#define SXGUI_UP_SCROLL		0
#define SXGUI_DOWN_SCROLL	1

#define SXGUI_LEFT_SCROLL	0
#define SXGUI_RIGTH_SCROLL	1

//������������ ���������� ������������
//����� ��������� ����������� ��������
#define SXGUI_COUNT_HANDLERS_MSG_IN_ARR 256

//��� �����������
typedef LRESULT(*HandlerMsg) (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//��������� ������ ��� �����������
struct SXHandlerMsgStruct
{
	HandlerMsg Handler;		//���� �������, ������� ����� ����������
	UINT Msg;
	WPARAM WParam;
	bool BFCondiderWParam;	//��������� WParam?
	LPARAM LParam;
	bool BFCondiderLParam;	//��������� LParam
	bool IsMainFunction;	//������� �� ��� ����������? true - �������� ������������ ������� - ������������ WndProc, ����� ��� 
};

//���������, ����������, ��� ����������� �������� �� ������� �������� �� ��������� ��������
struct SXRectBool
{
	SXRectBool()
	{
		this->top = false;
		this->left = false;
		this->bottom = false;
		this->right = false;
	}
	SXRectBool(bool _top, bool _left, bool _bottom, bool _right)
	{
		this->top = _top;
		this->left = _left;
		this->bottom = _bottom;
		this->right = _right;
	}
	bool top;
	bool left;
	bool bottom;
	bool right;
};

//������ ������� �����, ������������ ��������� �� ������������
//���������� ������ ��� �������, �� ���� �������� � ���� ������� ������ ��� 
//���������� ��������
struct ISXGUIControl : public IBaseObject
{
	virtual ~ISXGUIControl(){};
	virtual void Init(HWND window_handle, HWND parent_handle, WNDPROC handler) = 0;	//���������� �����������, � ������������� ����� ����������

	virtual HWND Parent() = 0;						//���������� HWND ��������
	virtual bool Parent(HWND parent_handle) = 0;	//������������� ��������

	virtual HWND GetHWND() = 0;

	virtual void Visible(bool bf) = 0;				//��������� ��������� ��������
	virtual bool Visible() = 0;						//����� �� �������?

	virtual void SetFocus() = 0;					//���������� ����� �� �������
	virtual bool Focus() = 0;						//���������� �� ����� �� ��������?
	//virtual WNDPROC GetOldProc() = 0;

	WNDPROC OldProc;

protected:
	HWND ParentHandle;
	HWND WindowHandle;
};


//////
//������ ������ ���������
#define SX_HINT_COUNT_BUF_SIZE 1024

struct ISXGUIHint : public IBaseObject
{
	virtual ~ISXGUIHint(){}
	//autopop - ����� ������
	//init - ������� ���� ��������� ��������� ����� ��������� �������
	virtual void SetDelayTime(DWORD init, DWORD autopop) = 0;

	virtual bool Parent(HWND parent) = 0;
	virtual HWND Parent() = 0;

	virtual HWND GetHWND() = 0;

	virtual void Visible(bool bf) = 0;
	virtual bool Visible() = 0;

	virtual void SetText(const char* text) = 0;	//��������� ������ ���������
	virtual char* GetText() = 0;				//���������� ��������� �� ����� ���������, ��������� ��� ������ �����������
	virtual void GetText(char* buf) = 0;
};

SX_LIB_API ISXGUIHint* SXGUICrHint(HWND parent);

////

//������ � ������� ��������, ����� ������������ ���� ������ �� ����
//����� ����������� ���������� ������������ ���������
struct ISXGUIComponent : public virtual ISXGUIControl
{
	virtual ~ISXGUIComponent(){};
	//������������� ����������� ������ ��� ���������� ���������
	virtual void InitComponent() = 0; //���������� �������� ����� �������������

	//������������ �� �������
	virtual bool Enable()=0;
	virtual void Enable(bool bf) = 0;

	//������ �� �������
	//���� name == 0 �� �� ��������� �������� ������,
	//���� name[0] == 0 �� ��������� ����� gui
	//���� ��������� �������� � -1 �� �� �����������
	virtual void SetFont(const char* name, int height, int width, int weight, int italic, int underline, int strike_out) = 0;
	virtual void SetFont(HFONT* hfont) = 0;
	virtual HFONT GetFont() = 0;

	virtual bool IsParentFont() = 0;	//����������� �� ����� ��������
	virtual HFONT ParentFont() = 0;		//�������� ������������ �����

	//������ �� ������� (� �.�. �����������)
	//style_add - ����������� �����
	//style_del - ���������
	virtual bool ModifyStyle(long style_add, long style_del) = 0;
	virtual bool ModifyExStyle(long style_add, long style_del) = 0;

	//�������������/���������� ������� ���� RECT �������� � ���������� �����������
	virtual bool	SetWinRect(RECT* rect, bool alignment_screen_space) = 0;	//alignment_screen_space - ������������ �� ������ �������� ������� (������� ���� ����� ������ �����)
	virtual RECT*	GetWinRect() = 0;
	virtual void	GetWinRect(RECT* rect) = 0;

	//�������������/���������� ���������� ������� RECT �������� � ���������� �����������
	virtual bool	SetClientRect(RECT* rect, bool alignment_screen_space) = 0;	//alignment_screen_space - ������������ �� ������ �������� ������� (������� ���� ����� ������ �����)
	virtual RECT*	GetClientRect() = 0;
	virtual void	GetClientRect(RECT* rect) = 0;

	//!!!������������� ����� �������� �������� ��������� ���������, ��� � ���� ������ ��� ����������������
	//��������� ���������
	virtual void ShowHint(bool bf) = 0;
	virtual bool ShowHint() = 0;

	//������ � ������� ��������� ��� ��������
	virtual void SetHintText(const char* text) = 0;
	virtual char* GetHintText() = 0;
	virtual void GetHintText(char* buf) = 0;

	//������� ��� ������
	//set/get ���� ������
	virtual void SetColorText(BYTE r, BYTE g, BYTE b) = 0;
	virtual void SetColorText(DWORD color) = 0;
	virtual DWORD GetColorText() = 0;

	//set/get ������������ ������� ���� ������
	virtual void SetTransparentTextBk(bool bf) = 0;
	virtual bool GetTransparentTextBk() = 0;

	//set/get ���� ������� ����
	virtual void SetColorTextBk(BYTE r, BYTE g, BYTE b) = 0;
	virtual void SetColorTextBk(DWORD color) = 0;
	virtual DWORD GetColorTextBk() = 0;

	//set/get ���� ������� ���� ��������
	virtual bool SetColorBrush(BYTE r, BYTE g, BYTE b) = 0;
	virtual bool SetColorBrush(DWORD color) = 0;
	virtual DWORD GetColorBrush() = 0;
	virtual HBRUSH GetBrush() = 0;

	//��� ��� �������� ������������ �������
	///////////////////////////////////////

	//���������� �����������
	virtual bool AddHandler(HandlerMsg Handler, UINT Msg, WPARAM wParam, bool considerWparam, LPARAM lParam, bool considerLparam, bool isMain) = 0;
	virtual bool AddHandler(HandlerMsg Handler, UINT Msg) = 0;	//��� ��� ����������� �� ������� ���� �� �����������

	//key - ���� � ������� ������������
	virtual HandlerMsg GetHandlerFunction(int key) = 0;	//���������� ������� ���������� 
	virtual WORD GetCountKeyArrHandler() = 0;			//���������� ������ � ������� ������������

	//��� ��� �������� ������ ���������
	virtual UINT GetMsgHandler(int key) = 0;
	virtual WPARAM GetWParamHandler(int key) = 0;
	virtual bool GetConsiderWParamHandler(int key) = 0;	//��������� WParam?
	virtual LPARAM GetLParamHandler(int key) = 0;
	virtual bool GetConsiderLParamHandler(int key) = 0;	//��������� LParam?

	virtual bool IsMainFunction(int key) = 0;	//��� ������� �������?
	virtual LRESULT ExecuteHandler(int key, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;	//��������� ������� ����������, � ��������� ���������� ���� ���������
	///////////////////////////////////////

	virtual void UpdateSize() = 0;
	virtual void UpdateRect() = 0;


	SXRectBool GAlign;	//������ ������������ ������� �������� ��� ��������� �������� ��� ��������
	//������ ����������� ��� UpdateSize
	RECT ParentRect;		//��������� ��������
	RECT OffsetParentRect;	//�� ������� ��� ������� ��������
	RECT WinScreenRect;		//��������� �������� ���� ������������ �������� �����

	//������ ������������ ����� �� ������������� ����������� �������
	bool BFSizingChangeTop;		//�� ���� ���� ��������� ������ ... ���� ����
	bool BFSizingChangeBottom;
	bool BFSizingChangeRight;
	bool BFSizingChangeLeft;

	bool BFMinSize;	//���������� �� ����������� ������? ���� �� �� ������ ��� MinSizeX � MinSizeY �� ����� �����������
	WORD MinSizeX;
	WORD MinSizeY;

protected:
	ISXGUIHint *Hint;
	SXHandlerMsgStruct ArrHandler[SXGUI_COUNT_HANDLERS_MSG_IN_ARR];
	int CountKeyArrHandler;

	DWORD ColorBrush;	//���� ������� �����
	HBRUSH HBrush;

	DWORD ColorText;	//���� ������
	bool TransparenTextBf;	//������������ ������������? ���� true �� ������� ���� � ������ �� �����
	DWORD ColorTextBk;	//���� ������� ���� � ������
};

//������ (���� ����� �����) ��������, ��������������� �� ������������
//������������� ������� ��� ���������� ������ ����� (��� ������) ��������� ���������
struct ISXGUITextual : public virtual ISXGUIComponent
{
	virtual ~ISXGUITextual(){};
	virtual bool SetText(const char* text)=0;
	//virtual const char*	GetText() = 0;
	virtual void GetText(char* buf, int size) = 0;
	virtual int GetTextLen() = 0;
};

///////

struct ISXGUIBaseWnd : public virtual ISXGUITextual
{
	virtual ~ISXGUIBaseWnd(){};
	virtual bool SetColorBrush(BYTE r, BYTE g, BYTE b) = 0;
	virtual bool SetColorBrush(DWORD color) = 0;
	virtual DWORD GetColorBrush() = 0;
	virtual HBRUSH GetBrush() = 0;

	virtual bool Alpha(WORD alpha) = 0;
	virtual WORD Alpha() = 0;
	virtual bool AlphaBlend(bool bf) = 0;
	virtual bool AlphaBlend() = 0;
};

SX_LIB_API ISXGUIBaseWnd* SXGUICrBaseWnd(
	const char* class_name, const char* caption, const char* menu,
	WORD id, WORD x, WORD y, WORD width, WORD heigth,
	HICON icon, HCURSOR cursor, HBRUSH brush,
	DWORD exstyle, DWORD wndstyle, DWORD style,
	HWND parent, WNDPROC handler=0
	);

/////

#define SXGUI_STATIC_ALIGN_LEFT		0
#define SXGUI_STATIC_ALIGN_RIGHT	1
#define SXGUI_STATIC_ALIGN_CENTER	2

struct ISXGUIStatic : public virtual ISXGUITextual
{
	virtual ~ISXGUIStatic(){}
	virtual WORD Align() = 0;			//���������� ���� ������������ ������
	virtual bool Align(WORD align) = 0;	//������������� ������������ ������

	virtual bool WordWrap() = 0;		//���������� �� ����������� �����
	virtual bool WordWrap(bool bf) = 0; //����������� �� ��������� ����������� �����
};

SX_LIB_API ISXGUIStatic* SXGUICrStaticEx(const char* caption, WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, DWORD id);
SX_LIB_API ISXGUIStatic* SXGUICrStatic(const char* caption, WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id);
//������� �����
SX_LIB_API ISXGUIStatic* SXGUICrStaticLine(WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id, bool vertical);

//////

#define SXGUI_BUTTON_IMAGE_NONE		0
#define SXGUI_BUTTON_IMAGE_ICON		1
#define SXGUI_BUTTON_IMAGE_BITMAT	2


struct ISXGUIButton : public virtual ISXGUITextual
{
	virtual ~ISXGUIButton(){}
	virtual bool SetIconInFile(const char* path) = 0;
	virtual bool SetBmpInFile(const char* path) = 0;

	virtual bool SetIconInResourse(WORD id) = 0;
	virtual bool SetBmpInResourse(WORD id) = 0;
};

SX_LIB_API ISXGUIButton* SXGUICrButtonEx(const char* caption, WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, DWORD id);
SX_LIB_API ISXGUIButton* SXGUICrButton(const char* caption, WORD x, WORD y, WORD width, WORD heigth, WORD image, HWND parent, WNDPROC handler, DWORD id);

/////

SX_LIB_API LRESULT WndProcButtonImgDefault(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define SXGUI_BI_POS_FREE			0
#define SXGUI_BI_POS_MOUSE_MOVE		1
#define SXGUI_BI_POS_MOUSE_CLICK	2

#define SXGUI_BI_SIZE_LINE			1


struct ISXGUIButtonImg : public virtual ISXGUIComponent
{
	virtual ~ISXGUIButtonImg(){}
	virtual void ReInitImage(const char* path) = 0;

	virtual void InitCallBack() = 0;

	DWORD AlphaColor;	//���� ������� ����� ��������
	DWORD BkColor;	//���� ���� ������
	DWORD FrameColor;	//���� ���� ������

	WORD Pos;			//������� � ������� ������� ������
	bool PosBf[3];		//����� �� ����������� ���������

	bool EnableState;	//��������� ������ (�������/��������)

	bool EnableBf;		//�������� �� ��������� ���������� ������
	bool EnableGroup;	//�������� �� ������ � ������ ���� �������� ��������� ��������, ��� ���������� ����� �������������� ������ ��� �������� ������ ������


	BITMAP Bitmap;
	HANDLE HBitMap;

	bool IsImages;

	virtual void GetPathForImg(char* buf) = 0;
};

SX_LIB_API ISXGUIButtonImg* SXGUICrButtonImgEx(const char* path, WORD x, WORD y, WORD width, WORD heigth, DWORD alpha_color, DWORD bk_color, HWND parent, WNDPROC handler, DWORD id);
SX_LIB_API ISXGUIButtonImg* SXGUICrButtonImg(WORD button, WORD x, WORD y, WORD width, WORD heigth, DWORD alpha_color, DWORD bk_color, HWND parent, WNDPROC handler, DWORD id);

///////

#define SXGUI_EDIT_ALIGN_LEFT	0
#define SXGUI_EDIT_ALIGN_RIGHT	1
#define SXGUI_EDIT_ALIGN_CENTER	2

struct ISXGUIEdit : public virtual ISXGUITextual
{
	virtual ~ISXGUIEdit(){}
	virtual bool ReadOnly() = 0;		//����������� �� �������� "������ ��� ������"
	virtual bool ReadOnly(bool bf) = 0;	//������������ ��������� "������ ��� ������", ���������� ��������� ��������

	//��������� ������� ����� ���������� �� *
	virtual bool Password() = 0;		//����������� �� ������� ������� ������
	virtual bool Password(bool bf) = 0;	//������������ ��������� ������� ������

	virtual WORD Align() = 0;			//���������� ���� ������������ ������
	virtual bool Align(WORD align) = 0;	//������������� ������������
};

SX_LIB_API ISXGUIEdit* SXGUICrEditEx(const char* caption, WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, DWORD id);
SX_LIB_API ISXGUIEdit* SXGUICrEdit(const char* caption, WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id);

///////

struct ISXGUIUpDown : public virtual ISXGUIComponent
{
	virtual ~ISXGUIUpDown(){}
	virtual void SetMinMax(long min, long max) = 0;
	virtual long SetPos(long pos) = 0;

	virtual long GetMin() = 0;
	virtual long GetMax() = 0;
	virtual long GetPos() = 0;

	virtual HWND SetBuddy(HWND buddy) = 0;
	virtual HWND GetBuddy() = 0;
};

SX_LIB_API ISXGUIUpDown* SXGUICrUpDownEx(WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, DWORD id, HWND buddy);
SX_LIB_API ISXGUIUpDown* SXGUICrUpDown(WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id, HWND buddy, WORD left_right);

/////

struct ISXGUIMemo : public virtual ISXGUIEdit
{
	virtual ~ISXGUIMemo(){}
	virtual bool WordWrap() = 0;		//���������� �� ����������� ����
	virtual bool WordWrap(bool bf) = 0;	//������������ ��������� ����������� ����

	//SXGUIFuctinon
	virtual bool ScrollBars(bool h, bool v) = 0;
	virtual bool ScrollBarV() = 0;
	virtual bool ScrollBarH() = 0;
	virtual bool ScrollLine(WORD scroll, WORD dir, int count) = 0;
};

SX_LIB_API ISXGUIMemo* SXGUICrMemoEx(const char* caption, WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, DWORD id);
SX_LIB_API ISXGUIMemo* SXGUICrMemo(const char* caption, WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id);

///////

struct ISXGUIComboBox : public virtual ISXGUIComponent
{
	virtual ~ISXGUIComboBox(){}
	virtual bool	InsertItem(int index, const char* text) = 0;		//������� ������ � ������
	virtual bool	DeleteItem(int index) = 0;						//�������� ������

	virtual int		GetCount() = 0;									//���������� �����

	virtual bool	SetSel(int index) = 0;							//�������� ������������ ������
	virtual int		GetSel() = 0;									//����� ���������� ������

	virtual bool	SetItemData(int index, LPARAM data) = 0;			//��������� ��� ������ userdata (32 ����)
	virtual LPARAM	GetItemData(int index) = 0;						//��������� userdata

	virtual bool	Clear() = 0;									//������� ��� ��������

	virtual bool	SetItemText(int index, const char* text) = 0;	//������� ������ � ������, ������� ������
	virtual char*	GetItemText(int index) = 0;						//�������� ����� �� ������ (���������� ��������� ������ � ����, ���� ��� ������ �� ����������)
	virtual void	GetItemText(int index, char* buf) = 0;			//�������� ����� �� ������ 
	virtual int		GetItemTextLength(int index) = 0;				//�������� ����� ������ �� ������
	virtual bool	AddItem(const char* text) = 0;					//��������� � ����� ����� ������
};

SX_LIB_API ISXGUIComboBox* SXGUICrComboBoxEx(const char* caption, WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, DWORD id);

//�����: (parent != 0 ? WS_CHILD : 0) | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS
SX_LIB_API ISXGUIComboBox* SXGUICrComboBox(const char* caption, WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id);

/////

struct ISXGUIListBox : public virtual ISXGUIComponent
{
	virtual ~ISXGUIListBox(){}
	virtual bool	MultipleSel() = 0;	//������������ �� �������� �������������� ��������� �����

	virtual bool	InsertItem(int index, const char* text) = 0;	//�������� ����� � ������ � ������� index
	virtual bool	AddItem(const char* text) = 0;				//�������� ������ � ����� ������
	virtual int		GetCountItem() = 0;							//���������� ���������� �����

	virtual bool	DeleteItem(int index) = 0;					//������� ������ � ������� index

	virtual bool	SetSel(int index) = 0;						//�������� ������ � ������� index
	virtual int		GetSel() = 0;

	virtual bool	SetItemData(int index, LPARAM data) = 0;		//���������� userdata ��� ������ � ������� index
	virtual LPARAM	GetItemData(int index) = 0;					//���������� userdata

	virtual bool	Clear() = 0;								//��������

	virtual bool	SetTextItem(int index, const char* text) = 0;//���������� ����� � ������ � ������� index
	virtual char*	GetItemText(int index) = 0;					//���������� ����� �� ������ !!!������ ���������� � ����
	virtual void	GetItemText(int index, char* buf) = 0;		//���������� ����� �� ������

	virtual int		GetItemTextLength(int index) = 0;			//���������� ����� ������ � ������

	//��������������� �����, ���� this->MultipleSel() == true
	virtual int		GetMultipleSelCount() = 0;					//���������� ���������� ���������� �����

	virtual bool	SetMultipleSel(int index, bool sel) = 0;		//������������� ��������/�� �������� ������
	virtual bool	GetMultipleSel(int index) = 0;				//���������� �������� �� ������

	virtual int*	GetMultipleSelArr() = 0;					//���������� ������ � �������� ���������� �����

	//SXGUIFuctinon
	virtual bool ScrollBars(bool h, bool v) = 0;
	virtual bool ScrollBarV() = 0;
	virtual bool ScrollBarH() = 0;
	virtual bool ScrollLine(WORD scroll, WORD dir, int count) = 0;
};

SX_LIB_API ISXGUIListBox* SXGUICrListBoxEx(const char* caption, WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, DWORD id);
SX_LIB_API ISXGUIListBox* SXGUICrListBox(const char* caption, WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id, bool miltiple_sel);

//////

struct ISXGUIGroupBox : public virtual ISXGUITextual
{
	virtual ~ISXGUIGroupBox(){}
};

SX_LIB_API ISXGUIGroupBox* SXGUICrGroupBoxEx(const char* caption, WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, DWORD id);
SX_LIB_API ISXGUIGroupBox* SXGUICrGroupBox(const char* caption, WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id);

//////

struct ISXGUIProgressBar : public virtual ISXGUIComponent
{
	virtual ~ISXGUIProgressBar(){}
	//��������/���������� ������� ���������
	virtual int GetPos() = 0;				//���������� ������� �������
	virtual int SetPos(int pos) = 0;		//���������� ������ �������

	//��������/���������� ������ ���� ���������
	/*virtual int GetStep() = 0;				//���������� ������� ������ ����
	virtual int SetStep(int step) = 0;		//���������� ������ ������ ����

	//���������� �������������� �������
	virtual int SetPosSteps(int steps) = 0;	//���������� ������� �� ���������� �����
	virtual int SetOneStep() = 0;			//��������� ������� �� ���� ���

	//������������� ������� �������� � ��������� ���������
	//��� ������� ���������� ���������� true, ����� false
	virtual bool SetMinMax(int min, int max) = 0;

	//���������� �����������/������������ ������� ���������
	virtual int GetMin() = 0;
	virtual int GetMax() = 0;

	//����������/�������� ���� ������� (���������� ���� ��������� ������� RGB(51,153,255))
	virtual bool SetBarColor(WORD r, WORD g, WORD b) = 0;	//��� ������� ���������� ���������� true, ����� false
	virtual DWORD GetBarColor() = 0;

	//����������/�������� ���� ���� (���������� ���� ����� ����� ���� ��������)
	virtual bool SetBkColor(WORD r, WORD g, WORD b) = 0; //��� ������� ���������� ���������� true, ����� false
	virtual DWORD GetBkColor() = 0;*/
};

SX_LIB_API ISXGUIProgressBar* SXGUICrProgressBarEx(WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, DWORD id);
SX_LIB_API ISXGUIProgressBar* SXGUICrProgressBar(WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id, bool vertical, bool smooth);

//////

#define SXGUI_RB_UNCHECKED		BST_UNCHECKED
#define SXGUI_RB_CHECKED		BST_CHECKED

struct ISXGUIRadioButton : public virtual ISXGUITextual
{
	virtual ~ISXGUIRadioButton(){}
	virtual void SetCheck(bool check) = 0;
	virtual bool GetCheck() = 0;
};

SX_LIB_API ISXGUIRadioButton* SXGUICrRadioButtonEx(const char* caption, WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, DWORD id);
SX_LIB_API ISXGUIRadioButton* SXGUICrRadioButton(const char* caption, WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id);

/////

#define SXGUI_CB_UNCHECKED		BST_UNCHECKED
#define SXGUI_CB_CHECKED		BST_CHECKED
#define SXGUI_CB_INDETERMINATE	BST_INDETERMINATE

struct ISXGUICheckBox : public virtual ISXGUITextual
{
	virtual ~ISXGUICheckBox(){}
	virtual void SetCheck(int check) = 0;
	virtual int GetCheck() = 0;
};

SX_LIB_API ISXGUICheckBox* SXGUICrCheckBoxEx(const char* caption, WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, DWORD id);
SX_LIB_API ISXGUICheckBox* SXGUICrCheckBox(const char* caption, WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id, bool cb_3_state);

///////

struct ISXGUITrackBar : public virtual ISXGUIComponent
{
	virtual ~ISXGUITrackBar(){}
	virtual void SetPos(int pos) = 0;
	virtual int GetPos() = 0;

	virtual void SetMinMax(int min, int max) = 0;
	virtual int GetMin() = 0;
	virtual int GetMax() = 0;

	virtual bool SetTick(int pos) = 0;
	virtual int GetTick(int index) = 0;

	virtual void SetTickFrequency(int freq) = 0;

	virtual bool SetBuddies(HWND hwnd_left, HWND hwnd_right) = 0;
	virtual HWND GetLeftBuddy() = 0;
	virtual HWND GetRightBuddy() = 0;
};

SX_LIB_API ISXGUITrackBar* SXGUICrTrackBarEx(const char* caption, WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, DWORD id);
SX_LIB_API ISXGUITrackBar* SXGUICrTrackBar(const char* caption, WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id);

///////

#define SXGUI_SB_ALIGN_RS_NONE		0
#define SXGUI_SB_ALIGN_RS_PERCENT	1
#define SXGUI_SB_ALIGN_RS_PROP		2
//!!! ��������� ���, ��� ���� �� ���� � ���������� ������
struct ISXGUIStatusBar : public virtual ISXGUIComponent
{
	virtual ~ISXGUIStatusBar(){}
	virtual bool SetCountParts(WORD count, int *arr) = 0;
	virtual WORD GetCountParts(int **arr) = 0;
	virtual bool SetTextParts(WORD pos, const char* text) = 0;
	virtual const char* GetTextParts(WORD pos) = 0;

	virtual void Update() = 0;
	virtual void UpdateSize() = 0;

	WORD AlignReSizing;
};

SX_LIB_API ISXGUIStatusBar* SXGUICrStatusBarEx(const char* caption, WORD x, WORD y, WORD width, WORD heigth, DWORD exstyle, DWORD style, HWND parent, WNDPROC handler, DWORD id);
SX_LIB_API ISXGUIStatusBar* SXGUICrStatusBar(const char* caption, HWND parent, WNDPROC handler, DWORD id);

///////

#define SXGUI_MENU_ENABLED	0
#define SXGUI_MENU_DISABLED	1
#define SXGUI_MENU_GRAYED	2


struct ISXGUIMenu
{
	virtual ~ISXGUIMenu(){}
	virtual bool InsertItem(int index, const char* text, WORD id, WORD id_sub_menu) = 0;
	virtual bool InsertPopupItem(int index, const char* text, WORD id, WORD id_sub_menu) = 0;
	virtual bool InsertSeparator(int index, WORD id, WORD id_sub_menu) = 0;

	virtual bool DeleteItem(WORD id) = 0;

	virtual HMENU GetSubMenu(WORD id) = 0;

	virtual bool CheckItem(WORD id, bool check) = 0;
	virtual bool EnableItem(WORD id, WORD enable) = 0;

	virtual bool GetCheckedItem(WORD id) = 0;
	virtual WORD GetEnabledItem(WORD id) = 0;

	virtual HMENU GetHMENU() = 0;
	virtual bool SetToWindow(HWND hwnd) = 0;
};

SX_LIB_API ISXGUIMenu* SXGUICrMenu();
SX_LIB_API ISXGUIMenu* SXGUICrMenuEx(WORD menu);

/////////////////////////

struct ISXGUIPopupMenu
{
	virtual ~ISXGUIPopupMenu(){}
	virtual bool InsertItem(int index, const char* text, WORD id, WORD id_sub_menu) = 0;
	virtual bool InsertPopupItem(int index, const char* text, WORD id, WORD id_sub_menu) = 0;
	virtual bool InsertSeparator(int index, WORD id, WORD id_sub_menu) = 0;

	virtual bool DeleteItem(WORD id) = 0;

	virtual HMENU GetSubMenu(WORD id) = 0;

	virtual bool CheckItem(WORD id, bool check) = 0;
	virtual bool EnableItem(WORD id, WORD enable) = 0;

	virtual bool GetCheckedItem(WORD id) = 0;
	virtual WORD GetEnabledItem(WORD id) = 0;

	virtual bool Track(HWND hwnd, int x, int y) = 0;

	virtual HMENU GetHMENU() = 0;
};

SX_LIB_API ISXGUIPopupMenu* SXGUICrPopupMenuEx(WORD menu);
SX_LIB_API ISXGUIPopupMenu* SXGUICrPopupMenu();

//////

struct ISXGUIToolBar : public virtual ISXGUIComponent
{
	virtual ~ISXGUIToolBar(){}
	virtual void AddButton(WORD num, WORD id, const char* hint, WORD id_resource, DWORD mask) = 0;
	virtual void AddSeparator(WORD num) = 0;
};

SX_LIB_API ISXGUIToolBar* SXGUICrToolBar(const char* caption, WORD x, WORD y, WORD width, WORD heigth, WORD width_element, WORD heigth_element, HWND parent, WNDPROC handler, DWORD id);

//////

SX_LIB_API LRESULT CALLBACK WndProcToolBarDefault(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

struct ISXGUIToolBarSX : public virtual ISXGUIComponent
{
	virtual ~ISXGUIToolBarSX(){}
	ISXGUIButtonImg *ImgButton;

	RECT MaxRect;
	RECT MinRect;

	const char* Caption;

	DWORD ColorTop;
	DWORD ColorClient;

	//SXGUIToolBarSX* ArrChildToolBar[1024];
	WORD CountChildToolBar;
};

SX_LIB_API ISXGUIToolBarSX* SXGUICrToolBarSXEx(const char* caption, WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id, const char* path_button_ctrl, DWORD id_ctrl_button);
SX_LIB_API ISXGUIToolBarSX* SXGUICrToolBarSX(const char* caption, WORD x, WORD y, WORD width, WORD heigth, HWND parent, WNDPROC handler, DWORD id, WORD button_res, DWORD id_ctrl_button);

//////

//!!!
//�� ���� ��������� ����� ���� �������� ������ ���� ���������� ������� ����� ���������� ��������
//������� �������� AddHandler (isMain) ������ ���� true
//��������� �� ������ ���� ������ (������� �������� AddHandler false)
//!!!

//����������� ���������� ������� ��� ���� ���������
SX_LIB_API LRESULT CALLBACK WndProcAllDefault(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

////////////////////////

namespace SXGUIFuctinon
{
	//!!!��� �����������
	//!!!���������������� ���������
	SX_LIB_API bool	ScroolBars(ISXGUIControl *Control, bool h, bool v);
	SX_LIB_API bool	ScrollBarV(ISXGUIControl *Control);
	SX_LIB_API bool	ScrollBarH(ISXGUIControl *Control);

	SX_LIB_API bool	ScrollLine(ISXGUIControl *Control, WORD scroll, WORD dir, int count);

	//�������� � ������� ��������
	SX_LIB_API bool	SetText(ISXGUIControl*const Control, const char* text);
	//!!!��������� ������
	//SX_LIB_API char*GetTextOut(ISXGUIControl *Control);
	SX_LIB_API void	GetText(ISXGUIControl *Control, char* buf, int count);
	SX_LIB_API int	GetTextLen(ISXGUIControl *Control);
};

//������� ��������� ������������� ������� ����������� ������������� �������� � ���� ��� �������� ���������
namespace SXGUIEnumChildWindow
{
	//��� ������ SXGUIButtonImg
	//��������� ������� ��������� ������ � � ����������� ������������ ��������� �������
	SX_LIB_API BOOL CALLBACK EnumChildProcUpdateImgButton(HWND hwnd, LPARAM lParam);

	//������� WM_SIZE
	SX_LIB_API BOOL CALLBACK EnumChildProcUpdateSize(HWND hwnd, LPARAM lParam);

	//������� WM_MOVE
	SX_LIB_API BOOL CALLBACK EnumChildProcUpdateRect(HWND hwnd, LPARAM lParam);

	//������� WM_MOUSEMOVE
	SX_LIB_API BOOL CALLBACK EnumChildProcMouseMove(HWND hwnd, LPARAM lParam);
};

namespace SXGUIBaseHandlers
{
	//��������� �������� ������������, ��� ������� SXGUIWinApi ����� �������� �� ���������, � �������� � �� ����� ��������
	//���� ���������� 0 ������ ��� � �����, ����� ���������� ����� ���� ����������� ������� �� ������� ����������
	//������ ������� ���������� ������ ���� �� ��������� ����� ���� �������������� �������� ��� ��������� ����������������� ���������
	SX_LIB_API int InitHandlerMsg(ISXGUIComponent* Component);

	//���������� ������� WM_SIZE
	SX_LIB_API LRESULT SizeChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//���������� ������� WM_CTLCOLORSTATIC WM_CTLCOLOREDIT WM_CTLCOLORBTN WM_CTLCOLORLISTBOX
	//�� ���� ��������� ������ �������� ��������� ���� (static, edit,button, listbox)
	SX_LIB_API LRESULT CtlColorChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//���������� ������� WM_SIZING
	SX_LIB_API LRESULT SizingChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//���������� ������� WM_MOVE
	SX_LIB_API LRESULT MoveChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//���������� ������� WM_MOUSEMOVE
	SX_LIB_API LRESULT MouseMoveChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//���������� ������� WM_SETCURSOR
	SX_LIB_API LRESULT SetCursorChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//���������� ������� WM_COMMAND SC_MAXIMIZE
	SX_LIB_API LRESULT MaximuzeWinChange(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//���������� ������� WM_DESTROY
	SX_LIB_API LRESULT WinDestroy(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

//������ ��������� ������� � ��������� �����������
namespace SXGUIRegClass
{
	//����� ������
	SX_LIB_API bool RegButtonImg();
	//����� �������
	SX_LIB_API bool RegToolBar();
};
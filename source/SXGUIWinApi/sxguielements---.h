


//������ ������� �����, ������������ ��������� �� ������������
//���������� ������ ��� �������, �� ���� �������� � ���� ������� ������ ��� 
//���������� ��������
struct ISXGUIControl
{
	virtual void Init(HWND window_handle, HWND parent_handle, WNDPROC handler){};	//���������� �����������, � ������������� ����� ����������
	virtual void Release(){};
	virtual HWND Parent(){ return (HWND)0; };						//���������� HWND ��������
	virtual bool Parent(HWND parent_handle){ return 0; };	//������������� ��������

	virtual HWND GetHWND(){ return (HWND)0; };

	virtual void Visible(bool bf){};				//��������� ��������� ��������
	virtual bool Visible(){ return 0; };						//����� �� �������?

	virtual void SetFocus(){};					//���������� ����� �� �������
	virtual bool Focus(){ return 0; };						//���������� �� ����� �� ��������?
	virtual WNDPROC GetOldProc(){ return (WNDPROC)0; };
};


//������ � ������� ��������, ����� ������������ ���� ������ �� ����
//����� ����������� ���������� ������������ ���������
struct ISXGUIComponent : public ISXGUIControl
{
	//������������� ����������� ������ ��� ���������� ���������
	virtual void InitComponent(){}; //���������� �������� ����� �������������

	//������������ �� �������
	virtual bool Enable(){ return 0; };
	virtual void Enable(bool bf){};

	//������ �� �������
	//���� name == 0 �� �� ��������� �������� ������,
	//���� name[0] == 0 �� ��������� ����� gui
	//���� ��������� �������� � -1 �� �� �����������
	virtual void SetFont(const char* name, int height, int width, int weight, int italic, int underline, int strike_out){};
	virtual void SetFont(HFONT* hfont){};
	virtual HFONT GetFont(){ return 0; };

	virtual bool IsParentFont(){ return 0; };	//����������� �� ����� ��������
	virtual HFONT ParentFont(){ return 0; };		//�������� ������������ �����

	//������ �� ������� (� �.�. �����������)
	//style_add - ����������� �����
	//style_del - ���������
	virtual bool ModifyStyle(long style_add, long style_del){ return 0; };
	virtual bool ModifyExStyle(long style_add, long style_del){ return 0; };

	//�������������/���������� ������� ���� RECT �������� � ���������� �����������
	virtual bool	SetWinRect(RECT* rect, bool alignment_screen_space){ return 0; };	//alignment_screen_space - ������������ �� ������ �������� ������� (������� ���� ����� ������ �����)
	virtual RECT*	GetWinRect(){ return 0; };
	virtual void	GetWinRect(RECT* rect){};

	//�������������/���������� ���������� ������� RECT �������� � ���������� �����������
	virtual bool	SetClientRect(RECT* rect, bool alignment_screen_space){ return 0; };	//alignment_screen_space - ������������ �� ������ �������� ������� (������� ���� ����� ������ �����)
	virtual RECT*	GetClientRect(){ return 0; };
	virtual void	GetClientRect(RECT* rect){};

	//!!!������������� ����� �������� �������� ��������� ���������, ��� � ���� ������ ��� ����������������
	//��������� ���������
	virtual void ShowHint(bool bf){};
	virtual bool ShowHint(){ return 0; };

	//������ � ������� ��������� ��� ��������
	virtual void SetHintText(const char* text){};
	virtual char* GetHintText(){ return 0; };
	virtual void GetHintText(char* buf){};

	//������� ��� ������
	//set/get ���� ������
	virtual void SetColorText(BYTE r, BYTE g, BYTE b){};
	virtual DWORD GetColorText(){ return 0; };

	//set/get ������������ ������� ���� ������
	virtual void SetTransparentTextBk(bool bf){};
	virtual bool GetTransparentTextBk(){ return 0; };

	//set/get ���� ������� ����
	virtual void SetColorTextBk(BYTE r, BYTE g, BYTE b){};
	virtual DWORD GetColorTextBk(){ return 0; };

	//set/get ���� ������� ���� ��������
	virtual bool SetColorBrush(BYTE r, BYTE g, BYTE b){ return 0; };
	virtual DWORD GetColorBrush(){ return 0; };
	virtual HBRUSH GetBrush(){ return 0; };

	//��� ��� �������� ������������ �������
	///////////////////////////////////////

	//���������� �����������
	virtual bool AddHandler(HandlerMsg Handler, UINT Msg, WPARAM wParam, bool considerWparam, LPARAM lParam, bool considerLparam, bool isMain){ return 0; };
	virtual bool AddHandler(HandlerMsg Handler, UINT Msg){ return 0; };	//��� ��� ����������� �� ������� ���� �� �����������

	//key - ���� � ������� ������������
	virtual HandlerMsg GetHandlerFunction(int key){ return 0; };	//���������� ������� ���������� 
	virtual WORD GetCountKeyArrHandler(){ return 0; };			//���������� ������ � ������� ������������

	//��� ��� �������� ������ ���������
	virtual UINT GetMsgHandler(int key){ return 0; };
	virtual WPARAM GetWParamHandler(int key){ return 0; };
	virtual bool GetConsiderWParamHandler(int key){ return 0; };	//��������� WParam?
	virtual LPARAM GetLParamHandler(int key){ return 0; };
	virtual bool GetConsiderLParamHandler(int key){ return 0; };	//��������� LParam?

	virtual bool IsMainFunction(int key){ return 0; };	//��� ������� �������?
	virtual LRESULT ExecuteHandler(int key, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){ return 0; };	//��������� ������� ����������, � ��������� ���������� ���� ���������
	///////////////////////////////////////

	virtual void UpdateSize(){};
	virtual void UpdateRect(){};
};

//������ (���� ����� �����) ��������, ��������������� �� ������������
//������������� ������� ��� ���������� ������ ����� (��� ������) ��������� ���������
struct ISXGUITextual : public ISXGUIComponent
{
	virtual bool SetText(const char* text){ return 0; };
	virtual const char*	GetText(){ return 0; };
	virtual void GetText(char* buf, int size){};
	virtual int GetTextLen(){ return 0; };
};

////

struct ISXGUIBaseWnd : public ISXGUITextual
{
	virtual bool SetColorBrush(BYTE r, BYTE g, BYTE b){ return 0; };
	virtual void GetColorBrush(DWORD color){};
	virtual HBRUSH GetBrush(){ return 0; };

	virtual bool Alpha(WORD alpha){ return 0; };
	virtual WORD Alpha(){ return 0; };
	virtual bool AlphaBlend(bool bf){ return 0; };
	virtual bool AlphaBlend(){ return 0; };
};

SX_LIB_API ISXGUIBaseWnd* SXCreateBaseWnd(
	const char* class_name, const char* caption, const char* menu,
	WORD id, WORD x, WORD y, WORD width, WORD heigth,
	HICON icon, HCURSOR cursor, HBRUSH brush,
	DWORD exstyle, DWORD wndstyle, DWORD style,
	HWND parent, WNDPROC handler
	);
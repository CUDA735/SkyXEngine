


//������ ������� �����, ������������ ��������� �� ������������
//���������� ������ ��� �������, �� ���� �������� � ���� ������� ������ ��� 
//���������� ��������
struct ISXGUIControl
{
	virtual void Init(HWND window_handle, HWND parent_handle, WNDPROC handler);	//���������� �����������, � ������������� ����� ����������
	virtual void Release();
	virtual HWND& Parent();						//���������� HWND ��������
	virtual bool Parent(HWND parent_handle);	//������������� ��������

	virtual HWND& GetHWND();

	virtual void Visible(bool bf);				//��������� ��������� ��������
	virtual bool Visible();						//����� �� �������?

	virtual void SetFocus();					//���������� ����� �� �������
	virtual bool Focus();						//���������� �� ����� �� ��������?
	virtual WNDPROC& GetOldProc();
};


//������ � ������� ��������, ����� ������������ ���� ������ �� ����
//����� ����������� ���������� ������������ ���������
struct ISXGUIComponent : public ISXGUIControl
{
	//������������� ����������� ������ ��� ���������� ���������
	virtual void InitComponent(); //���������� �������� ����� �������������

	//������������ �� �������
	virtual bool Enable();
	virtual void Enable(bool bf);

	//������ �� �������
	//���� name == 0 �� �� ��������� �������� ������,
	//���� name[0] == 0 �� ��������� ����� gui
	//���� ��������� �������� � -1 �� �� �����������
	virtual void SetFont(const char* name, int height, int width, int weight, int italic, int underline, int strike_out);
	virtual void SetFont(HFONT* hfont);
	virtual HFONT GetFont();

	virtual bool IsParentFont();	//����������� �� ����� ��������
	virtual HFONT ParentFont();		//�������� ������������ �����

	//������ �� ������� (� �.�. �����������)
	//style_add - ����������� �����
	//style_del - ���������
	virtual bool ModifyStyle(long style_add, long style_del);
	virtual bool ModifyExStyle(long style_add, long style_del);

	//�������������/���������� ������� ���� RECT �������� � ���������� �����������
	virtual bool	SetWinRect(RECT* rect, bool alignment_screen_space);	//alignment_screen_space - ������������ �� ������ �������� ������� (������� ���� ����� ������ �����)
	virtual RECT*	GetWinRect();
	virtual void	GetWinRect(RECT* rect);

	//�������������/���������� ���������� ������� RECT �������� � ���������� �����������
	virtual bool	SetClientRect(RECT* rect, bool alignment_screen_space);	//alignment_screen_space - ������������ �� ������ �������� ������� (������� ���� ����� ������ �����)
	virtual RECT*	GetClientRect();
	virtual void	GetClientRect(RECT* rect);

	//!!!������������� ����� �������� �������� ��������� ���������, ��� � ���� ������ ��� ����������������
	//��������� ���������
	virtual void ShowHint(bool bf);
	virtual bool ShowHint();

	//������ � ������� ��������� ��� ��������
	virtual void SetHintText(const char* text);
	virtual char* GetHintText();
	virtual void GetHintText(char* buf);

	//������� ��� ������
	//set/get ���� ������
	virtual void SetColorText(BYTE r, BYTE g, BYTE b);
	virtual DWORD GetColorText();

	//set/get ������������ ������� ���� ������
	virtual void SetTransparentTextBk(bool bf);
	virtual bool GetTransparentTextBk();

	//set/get ���� ������� ����
	virtual void SetColorTextBk(BYTE r, BYTE g, BYTE b);
	virtual DWORD GetColorTextBk();

	//set/get ���� ������� ���� ��������
	virtual bool SetColorBrush(BYTE r, BYTE g, BYTE b);
	virtual DWORD GetColorBrush();
	virtual HBRUSH GetBrush();

	//��� ��� �������� ������������ �������
	///////////////////////////////////////

	//���������� �����������
	virtual bool AddHandler(HandlerMsg Handler, UINT Msg, WPARAM wParam, bool considerWparam, LPARAM lParam, bool considerLparam, bool isMain);
	virtual bool AddHandler(HandlerMsg Handler, UINT Msg);	//��� ��� ����������� �� ������� ���� �� �����������

	//key - ���� � ������� ������������
	virtual HandlerMsg GetHandlerFunction(int key);	//���������� ������� ���������� 
	virtual WORD GetCountKeyArrHandler();			//���������� ������ � ������� ������������

	//��� ��� �������� ������ ���������
	virtual UINT GetMsgHandler(int key);
	virtual WPARAM GetWParamHandler(int key);
	virtual bool GetConsiderWParamHandler(int key);	//��������� WParam?
	virtual LPARAM GetLParamHandler(int key);
	virtual bool GetConsiderLParamHandler(int key);	//��������� LParam?

	virtual bool IsMainFunction(int key);	//��� ������� �������?
	virtual LRESULT ExecuteHandler(int key, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);	//��������� ������� ����������, � ��������� ���������� ���� ���������
	///////////////////////////////////////

	virtual void UpdateSize();
	virtual void UpdateRect();
};

//������ (���� ����� �����) ��������, ��������������� �� ������������
//������������� ������� ��� ���������� ������ ����� (��� ������) ��������� ���������
struct ISXGUITextual : public ISXGUIComponent
{
	virtual bool SetText(const char* text);
	virtual const char*	GetText();
	virtual void GetText(char* buf, int size);
	virtual int GetTextLen();
};

////

struct ISXGUIBaseWnd : public ISXGUITextual
{
	virtual bool SetColorBrush(BYTE r, BYTE g, BYTE b);
	virtual void GetColorBrush(DWORD color);
	virtual HBRUSH GetBrush();

	virtual bool Alpha(WORD alpha);
	virtual WORD Alpha();
	virtual bool AlphaBlend(bool bf);
	virtual bool AlphaBlend();
};

SX_LIB_API ISXGUIBaseWnd* SXCreateBaseWnd(
	const char* class_name, const char* caption, const char* menu,
	WORD id, WORD x, WORD y, WORD width, WORD heigth,
	HICON icon, HCURSOR cursor, HBRUSH brush,
	DWORD exstyle, DWORD wndstyle, DWORD style,
	HWND parent, WNDPROC handler
	);
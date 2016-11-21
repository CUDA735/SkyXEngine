#ifndef SX_INPUT_CLASS_H
#define SX_INPUT_CLASS_H

#include <Mmsystem.h>
#include <DInput.h>

#pragma once

class SXInput
{
public:
	SXInput(const char* name);
	~SXInput();

	long Init(HWND hwnd, HINSTANCE hinst);
	//����������� ���������������� ������� � ����������
	int	ReadMouseData		(IDirectInputDevice8 *DIDevice);	//���������� ���������� ����
	int	ReadKeyBoardData	(IDirectInputDevice8 *DIDevice);	//���������� ��������� ����������

	void	Update();	//���������� �������, �������� � ���� ReadMouseData � ReadKeyBoardData

	//���������������� ������� � ����������

	bool	GetKeyState		(unsigned char Key);	//������ �� ������� ��� ������� Key
	bool	GetButtonState	(unsigned char Number);	//������ �� ������ ���� ��� ������� Number
	bool	IsOtherButtonOn	(unsigned char Button);	//������ �� ������ ������ ����, Button - ��� ������� ����������� ������������ �������

	DWORD	GetKeyEvents	(unsigned char Key);	//�������� ������� ���������� �������� �� ����������
	WORD	GetButtonEvent	(unsigned char Button);	//�������� ������� ���������� ������� ����
	long	GetScroll		();						//�������� ������, -120 - �����, 120 - ������ (120 - 1 ������)
	bool	GetMouseDouble	(unsigned char Button);	//��� �� ������ ������� ���� Button ������� ����

	int		IsMouseClick	(DIMOUSESTATE *DIMouseState);	//���������� ��� ������� ������ ������ ����

	bool	GetExeEvents(SXInMess *Event);					//���� �� ���������� ������ �������
	bool	GetExeEvents(WORD type,WORD sect,WORD code);	//������

	//����������� ���������������� ������� � ����������

	char	KeyStateBuffer		[256];	//������ ��������� ����������
	char	OldKeyStateBuffer	[256];	//������ ��������� ���������� ��� ������� ����������
	DWORD	KeyStateEvents		[256];	//������ ��������� ���������� �� ����������
	DWORD	TimerKeyStateBuffer	[256];	//������ �������� ��� ������ ������� ����������

	DIMOUSESTATE	MouseState;				//������ ����
	DIMOUSESTATE	OldMouseState;			//������ ���� �� ����� ���������� �������� ������� ������, ���������� ��� �������� �����
	DIMOUSESTATE	SomeTimesMouseState;	//������ ���� ��� ������� ����������

	SXStateMouse	EventsMouse;		//������� ���������� �����
	SXStateMouse	OldEventsMouse;		//������� ��� ������� �������

private:
	char Name[CORE_NAME_MAX_LEN];
	IDirectInput8		*DirectInput;
	IDirectInputDevice8	*DeviceKeyBoard;
	IDirectInputDevice8	*DeviceMouse;

	DWORD	InsTime;		//������ ��� ������������ ������� �����
	DWORD	DoubleClick;	//�� ����� ������ ��������� ������� ����, ���� -1 ������ �� �� �����, ��� �������� ��������

	int	ControlMouseButton;	//������, ��� �������� �����������
	int	ShiftEvent;			//���������� ������� ������� ��������� ��� ���������� �������� �����

	long InitKeyboard (HWND hwnd, IDirectInput8 *DirectInput,IDirectInputDevice8** dev);	//������������� ���������� ���������� � ���������� ���
	long InitMouse (HWND hwnd, IDirectInput8 *DirectInput,IDirectInputDevice8** dev);	//������������� ���������� ���� � ���������� ���
};


#endif
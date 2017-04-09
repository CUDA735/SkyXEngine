
#ifndef SX_INPUT_CLASS_H
#define SX_INPUT_CLASS_H

#include <Mmsystem.h>
#include <DInput.h>

#pragma once

//���� ������
#define SX_INPUT_ERROR_NON_ACQUIRE 2
#define SX_INPUT_ERROR_UNKNOWN 1

#define SX_INPUT_ERR_CREATE_DI					-1	/*DirectInput �� �������*/
#define SX_INPUT_ERR_CDI_INVALID_ARG			-12	/*�������� ���������*/
#define SX_INPUT_ERR_CDI_OUT_OF_MEM				-13	/*�������� ������*/
#define SX_INPUT_ERR_CDI_NONE_ERR				-14	/*����������� ������*/

#define SX_INPUT_ERR_ATTACH_THREAD_IN			-2	/*�� ������� ����������� � ����������������� �����*/
#define SX_INPUT_ERR_ATTACH_THREAD_OUT			-3	/*�� ������� ���������� �� ����������������� �����*/

#define SX_INPUT_ERR_CREATE_DEVICE_KEYBOARD		-4	/*�� ������� ������� ���������� "����������"*/
#define SX_INPUT_ERR_SET_DATA_FORMAT_KEYBOARD	-5	/*�� ������� ���������� ������ ����� ��� ���������� "����������"*/
#define SX_INPUT_ERR_COOPERATIVE_KEYBOARD		-6	/*�� ������� ���������� ������� ���������� ��� ���������� "����������"*/
#define SX_INPUT_ERR_ACQUIRE_KEYBOARD			-7	/*�� ������� ��������� ���������� "����������"*/

#define SX_INPUT_ERR_CREATE_DEVICE_MOUSE		-8	/*�� ������� ������� ���������� "����"*/
#define SX_INPUT_ERR_SET_DATA_FORMAT_MOUSE		-9	/*�� ������� ���������� ������ ����� ��� ���������� "����"*/
#define SX_INPUT_ERR_COOPERATIVE_MOUSE			-10	/*�� ������� ���������� ������� ���������� ��� ���������� "����"*/
#define SX_INPUT_ERR_ACQUIRE_MOUSE				-11	/*�� ������� ��������� ���������� "����"*/

//��������� ������ ����
struct StateMouse
{
	InputEvents Buttons[3];	//������� ������� ��� ������ ������ ����
	DWORD Timer[3];
};

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

	
	bool	GetKeyState(InputCode Key);	//������ �� ������� ��� ������� Key
	bool	GetButtonState(InputCode Number);	//������ �� ������ ���� ��� ������� Number
	bool	IsOtherButtonOn(InputCode Button);	//������ �� ������ ������ ����, Button - ��� ������� ����������� ������������ �������

	InputEvents	GetKeyEvents(InputCode Key);	//�������� ������� ���������� �������� �� ����������
	InputEvents	GetButtonEvent(InputCode Button);//�������� ������� ���������� ������� ����
	long	GetScroll		();						//�������� ������, -120 - �����, 120 - ������ (120 - 1 ������)
	bool	GetMouseDouble(InputCode Button);	//��� �� ������ ������� ���� Button ������� ����

	InputCode IsMouseClick();	//���������� ��� ������� ������ ������ ����

	bool	GetExeEvents(InMess *Event);					//���� �� ���������� ������ �������
	bool	GetExeEvents(InputDevice type, InputCode sect, InputEvents code);	//������

private:
	char Name[CORE_NAME_MAX_LEN];
	IDirectInput8		*DirectInput;
	IDirectInputDevice8	*DeviceKeyBoard;
	IDirectInputDevice8	*DeviceMouse;

	char	KeyStateBuffer[256];	//������ ��������� ����������
	char	OldKeyStateBuffer[256];	//������ ��������� ���������� ��� ������� ����������
	InputEvents	KeyStateEvents[256];	//������ ��������� ���������� �� ����������
	DWORD		TimerKeyStateBuffer[256];	//������ �������� ��� ������ ������� ����������

	DIMOUSESTATE	MouseState;				//������ ����
	DIMOUSESTATE	OldMouseState;			//������ ���� �� ����� ���������� �������� ������� ������, ���������� ��� �������� �����
	DIMOUSESTATE	SomeTimesMouseState;	//������ ���� ��� ������� ����������

	StateMouse	EventsMouse;		//������� ���������� �����
	StateMouse	OldEventsMouse;		//������� ��� ������� �������

	DWORD	InsTime;		//������ ��� ������������ �������� �����
	DWORD	DoubleClick;	//�� ����� ������ ��������� ������� ����, ���� -1 ������ �� �� �����, ��� �������� ��������

	int	ControlMouseButton;	//������, ��� �������� �����������
	int	ShiftEvent;			//���������� ������� ������� ��������� ��� ���������� �������� �����

	long InitKeyboard (HWND hwnd, IDirectInput8 *DirectInput,IDirectInputDevice8** dev);	//������������� ���������� ���������� � ���������� ���
	long InitMouse (HWND hwnd, IDirectInput8 *DirectInput,IDirectInputDevice8** dev);	//������������� ���������� ���� � ���������� ���
};


#endif
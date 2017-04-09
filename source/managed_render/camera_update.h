
#ifndef __camera_update
#define __camera_update

namespace CameraUpdate
{
	//��������� ����� ���������� � ����������
	void UpdateInputKeyBoard(DWORD timeDelta);

	//��������� �������� ���� ������ � �����
	void UpdateInputMouseRotate(DWORD timeDelta);

	//��������� �������� ���� ����� ����
	void UpdateInputMouseUpDown(DWORD timeDelta);

	//������������� ������� ����
	void CentererCursor();

	void UpdateEditorial(DWORD timeDelta);
};

#endif
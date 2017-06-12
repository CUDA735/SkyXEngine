#ifndef _SXbaseItem_H_
#define _SXbaseItem_H_

#include "SXbaseAnimating.h"

class SXbaseItem: public SXbaseAnimating
{
	DECLARE_CLASS(SXbaseItem, SXbaseAnimating);
	DECLARE_PROPTABLE();
public:
	DECLARE_CONSTRUCTOR();

	const char * m_szInvName; //!< ���, ������������ � ���������
	bool m_bInvStackable; //!< ����� �� ������� ��������� ������ � ����� ������
	int m_iInvStackCurSize; //!< ���������� ������ � �����
	int m_iInvStackMaxSize; //!< ������������ ���������� ������ � �����
	float m_iInvWeight; //!< ����� �������
	bool m_bPickable; //!< ����� �� ������� ������
};

#endif

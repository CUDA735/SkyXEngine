#ifndef _SXbaseAmmoBox_H_
#define _SXbaseAmmoBox_H_

#include "SXbaseItem.h"

class SXbaseAmmoBox: public SXbaseItem
{
	DECLARE_CLASS(SXbaseAmmoBox, SXbaseItem);
	DECLARE_PROPTABLE();
public:
	ThisClass(EntityManager * pMgr);

	int m_iMaxItems; //!< ������������ ���������� ���������, ������� ���� ����� ������
	int m_iCurItems; //!< ������� ��������
	int m_iItemsPerUse; //!< ������� �������� �� ���

	const char * m_szAmmoType; //!< ��� ��������� ��� ������
};

#endif

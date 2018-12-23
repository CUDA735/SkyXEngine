
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

/*!
\file
���������� ������
*/

#ifndef __PROP_BREAKABLE_H
#define __PROP_BREAKABLE_H

#include "PropDynamic.h"

/*! ����������� ������
\ingroup cbaseanimating
*/
class CPropBreakable: public CPropDynamic
{
	DECLARE_CLASS(CPropBreakable, CPropDynamic);
	DECLARE_PROPTABLE();
public:
	DECLARE_TRIVIAL_CONSTRUCTOR();
	virtual void onPostLoad();

	void onDeath(CBaseEntity *pAttacker, CBaseEntity *pInflictor);
protected:
	void breakInput(inputdata_t * pInputdata);

	output_t m_onBroken;

	const char * m_szSndBreak;
	ID m_idSndBreak = -1;
};

#endif

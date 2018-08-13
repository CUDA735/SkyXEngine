
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

/*!
\file
���������� ����
*/

#ifndef __LOGIC_RELAY_H
#define __LOGIC_RELAY_H

#include "PointEntity.h"

#define LOGIC_START_DISABLED ENT_FLAG_0

/*! ���������� ����
\ingroup cpointentity
*/
class CLogicRelay: public CPointEntity
{
	DECLARE_CLASS(CLogicRelay, CPointEntity);
	DECLARE_PROPTABLE();
public:
	DECLARE_CONSTRUCTOR();
	
protected:
	void turnOn(inputdata_t * pInputdata);
	void turnOff(inputdata_t * pInputdata);
	void trigger(inputdata_t * pInputdata);
	void toggle(inputdata_t * pInputdata);

	void onPostLoad();

	output_t m_onTrigger;

	bool m_isEnabled;
};

#endif
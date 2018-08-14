
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#include "PropButton.h"

/*! \skydocent prop_button
������
*/

BEGIN_PROPTABLE(CPropButton)
	//! ��������
	DEFINE_INPUT(turnOn, "turnOn", "Turn On", PDF_NONE)
	//! ���������
	DEFINE_INPUT(turnOff, "turnOff", "Turn Off", PDF_NONE)
	//! ������
	DEFINE_INPUT(press, "press", "Press", PDF_NONE)
	//! ������
	DEFINE_INPUT(pushUp, "pushUp", "Push up", PDF_NONE)
	//! �����
	DEFINE_INPUT(pushDown, "pushDown", "Push down", PDF_NONE)
	//! �����������
	DEFINE_INPUT(toggle, "toggle", "Toggle", PDF_NONE)

	//! ��� �������
	DEFINE_OUTPUT(m_onPressed, "OnPressed", "On pressed")
	//! ��� �������
	DEFINE_OUTPUT(m_onPushUp, "OnPushUp", "On push up")
	//! ��� ������
	DEFINE_OUTPUT(m_onPushDown, "OnPushDown", "On push down")
	//! ��� ������������
	DEFINE_OUTPUT(m_onToggle, "OnToggle", "On toggle")
	//! ��� ������� ������� � ����������� ���������
	DEFINE_OUTPUT(m_onUseDisabled, "OnUseDisabled", "On use disabled")

	//! ���������� ��������
	DEFINE_FLAG(BUTTON_START_DISABLED, "Start Disabled")
	//! ����� ��������� ������/������
	DEFINE_FLAG(BUTTON_TOGGLEABLE, "Toggleable")
	//! ���������� ������
	DEFINE_FLAG(BUTTON_START_PRESSED, "Start pressed")
END_PROPTABLE()

REGISTER_ENTITY(CPropButton, prop_button);

CPropButton::CPropButton(CEntityManager * pMgr):
	BaseClass(pMgr)
{
	m_isEnabled = true;
	m_isToggleable = false;
	m_bState = false;
}

void CPropButton::turnOn(inputdata_t * pInputdata)
{
	m_isEnabled = true;
}

void CPropButton::turnOff(inputdata_t * pInputdata)
{
	m_isEnabled = false;
}

void CPropButton::press(inputdata_t * pInputdata)
{
	if(m_isEnabled)
	{
		FIRE_OUTPUT(m_onPressed, pInputdata->pInflictor);
		if(m_isToggleable)
		{
			m_bState = !m_bState;
			FIRE_OUTPUT(m_onToggle, pInputdata->pInflictor);
			FIRE_OUTPUT(m_bState ? m_onPushDown : m_onPushUp, pInputdata->pInflictor);
		}
	}
	else
	{
		FIRE_OUTPUT(m_onUseDisabled, pInputdata->pInflictor);
	}
}

void CPropButton::pushUp(inputdata_t * pInputdata)
{
	if(!m_isToggleable)
	{
		return;
	}
	if(m_isEnabled)
	{
		if(m_bState)
		{
			m_bState = false;
			FIRE_OUTPUT(m_onToggle, pInputdata->pInflictor);
			FIRE_OUTPUT(m_onPushUp, pInputdata->pInflictor);
		}
	}
}

void CPropButton::pushDown(inputdata_t * pInputdata)
{
	if(!m_isToggleable)
	{
		return;
	}
	if(m_isEnabled)
	{
		if(!m_bState)
		{
			m_bState = true;
			FIRE_OUTPUT(m_onToggle, pInputdata->pInflictor);
			FIRE_OUTPUT(m_onPushUp, pInputdata->pInflictor);
		}
	}
}

void CPropButton::toggle(inputdata_t * pInputdata)
{
	if(!m_isToggleable)
	{
		return;
	}
	if(m_isEnabled)
	{
		m_bState = !m_bState;
		FIRE_OUTPUT(m_onToggle, pInputdata->pInflictor);
		FIRE_OUTPUT(m_bState ? m_onPushDown : m_onPushUp, pInputdata->pInflictor);
	}
}

void CPropButton::onPostLoad()
{
	m_isEnabled = !(getFlags() & BUTTON_START_DISABLED);
	m_isToggleable = (getFlags() & BUTTON_TOGGLEABLE);
	m_bState = (getFlags() & BUTTON_START_PRESSED);

	BaseClass::onPostLoad();
}

void CPropButton::onUse(CBaseEntity *pUser)
{
	inputdata_t inputdata;
	memset(&inputdata, 0, sizeof(inputdata_t));
	inputdata.pActivator = pUser;
	inputdata.pInflictor = pUser;
	inputdata.type = PDF_NONE;

	press(&inputdata);

	BaseClass::onUse(pUser);
}

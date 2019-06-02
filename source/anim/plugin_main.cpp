#include <xcommon/IXPlugin.h>
#include "Renderable.h"
#include "Updatable.h"
#include "AnimatedModelProvider.h"
#include "DynamicModelProvider.h"


class CDSEPlugin: public IXPlugin
{
public:
	void XMETHODCALLTYPE startup(IXCore *pCore) override
	{
		m_pAnimatedModelProvider = new CAnimatedModelProvider(pCore);
		m_pDynamicModelProvider = new CDynamicModelProvider(pCore);
		m_pRenderable = new CRenderable(getID(), m_pAnimatedModelProvider, m_pDynamicModelProvider);
		m_pUpdatable = new CUpdatable(m_pAnimatedModelProvider);
	}

	void XMETHODCALLTYPE shutdown() override
	{
		mem_delete(m_pRenderable);
		mem_delete(m_pUpdatable);
		mem_delete(m_pAnimatedModelProvider);
		mem_delete(m_pDynamicModelProvider);
	}

	UINT XMETHODCALLTYPE getInterfaceCount() override
	{
		return(4);
	}
	const XGUID * XMETHODCALLTYPE getInterfaceGUID(UINT id) override
	{
		static XGUID s_guid;
		switch(id)
		{
		case 0:
			s_guid = IXRENDERABLE_GUID;
			break;
		case 1:
			s_guid = IXUPDATABLE_GUID;
			break;
		case 2:
			s_guid = IXANIMATEDMODELPROVIDER_GUID;
			break;
		case 3:
			s_guid = IXDYNAMICMODELPROVIDER_GUID;
			break;
		default:
			return(NULL);
		}
		return(&s_guid);
	}
	IXUnknown * XMETHODCALLTYPE getInterface(const XGUID &guid) override
	{
		if(guid == IXRENDERABLE_GUID)
		{
			return(m_pRenderable);
		}
		if(guid == IXUPDATABLE_GUID)
		{
			return(m_pUpdatable);
		}
		if(guid == IXANIMATEDMODELPROVIDER_GUID)
		{
			return(m_pAnimatedModelProvider);
		}
		if(guid == IXDYNAMICMODELPROVIDER_GUID)
		{
			return(m_pDynamicModelProvider);
		}
		return(NULL);
	}

protected:
	CRenderable *m_pRenderable = NULL;
	CUpdatable *m_pUpdatable = NULL;
	CAnimatedModelProvider *m_pAnimatedModelProvider = NULL;
	CDynamicModelProvider *m_pDynamicModelProvider = NULL;
};

DECLARE_XPLUGIN(CDSEPlugin);
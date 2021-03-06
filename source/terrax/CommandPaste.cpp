#include "CommandPaste.h"
#include <common/aastring.h>

extern AssotiativeArray<AAString, IXEditable*> g_mEditableSystems;

bool XMETHODCALLTYPE CCommandPaste::exec()
{
	if(!m_pCommandSelect)
	{
		m_pCommandSelect = new CCommandSelect();
		
		for(UINT i = 0, l = g_pLevelObjects.size(); i < l; ++i)
		{
			if(g_pLevelObjects[i]->isSelected())
			{
				m_pCommandSelect->addDeselected(i);
			}
		}
	}

	m_pCommandSelect->exec();

	_paste_obj *pObj;
	for(UINT i = 0, l = m_aObjects.size(); i < l; ++i)
	{
		pObj = &m_aObjects[i];

		pObj->pObject->setSelected(true);
		pObj->pObject->create();

		pObj->pObject->setPos(pObj->vPos);
		pObj->pObject->setScale(pObj->vScale);
		pObj->pObject->setOrient(pObj->qRotate);
		pObj->pObject->preSetup();
		for(auto i = pObj->mKeyValues.begin(); i; ++i)
		{
			pObj->pObject->setKV(i.first->c_str(), i.second->c_str());
		}
		pObj->pObject->postSetup();
		pObj->pObject->AddRef();
		g_pLevelObjects.push_back(pObj->pObject);
	}
	XUpdatePropWindow();
	return(m_aObjects.size());
}
bool XMETHODCALLTYPE CCommandPaste::undo()
{
	_paste_obj *pObj;
	for(int i = m_aObjects.size() - 1; i >= 0; --i)
	{
		pObj = &m_aObjects[i];

		pObj->pObject->remove();
		pObj->pObject->Release();
		g_pLevelObjects.erase(g_pLevelObjects.size() - 1);
	}

	m_pCommandSelect->undo();

	XUpdatePropWindow();
	return(true);
}

CCommandPaste::~CCommandPaste()
{
	for(UINT i = 0, l = m_aObjects.size(); i < l; ++i)
	{
		mem_release(m_aObjects[i].pObject);
	}
	mem_delete(m_pCommandSelect);
}

UINT CCommandPaste::addObject(const char *szTypeName, const char *szClassName, const float3 &vPos, const float3 &vScale, const SMQuaternion &qRotate)
{
	const AssotiativeArray<AAString, IXEditable*>::Node *pNode;
	if(!g_mEditableSystems.KeyExists(AAString(szTypeName), &pNode))
	{
		LibReport(REPORT_MSG_LEVEL_ERROR, "Unknown object type %s, skipping!", szTypeName);
		return(~0u);
	}

	_paste_obj obj;
	obj.pObject = (*(pNode->Val))->newObject(szClassName);
	obj.vPos = vPos;
	obj.vScale = vScale;
	obj.qRotate = qRotate;

	m_aObjects.push_back(obj);

	return(m_aObjects.size() - 1);
}
void CCommandPaste::setKV(UINT uId, const char *szKey, const char *szValue)
{
	assert(uId < m_aObjects.size());

	m_aObjects[uId].mKeyValues[szKey] = szValue;
}

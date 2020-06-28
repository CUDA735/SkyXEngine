#include "Updatable.h"

CUpdatable::CUpdatable(CScene *pScene):
	m_pScene(pScene)
{

}

UINT CUpdatable::startup()
{
	return(30);
}

void CUpdatable::shutdown()
{
}


ID CUpdatable::run(float fDelta)
{
	return(-1);
}

void CUpdatable::sync()
{
	m_pScene->sync();
}
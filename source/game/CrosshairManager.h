#ifndef _CROSSHAIRMANAGER_H
#define _CROSSHAIRMANAGER_H

#include "sxgame.h"
#include <common/AssotiativeArray.h>
#include <common/AAString.h>
#include "crosshair.h"

class CCrosshairManager
{
public:
	static void loadCrosshair(ID id, CCrosshair * pCrosshair);
	static void loadConfig(const char * szFile);
	static ID getCrosshairID(const char * szName);

protected:
	struct CrosshairDesc
	{
		float fAngle;
		float fRadius;
		int iNumSegments;
		CCrosshair::STYLE style;
		float2_t f2TexOffset;
		float2_t f2TexSize;
		ID idTexture;
	};

	static AssotiativeArray<AAString, ID> m_mIndex;
	static Array<CrosshairDesc> m_vCrosshairList;
};

#endif

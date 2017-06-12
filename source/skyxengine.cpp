
/******************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

#define _CRT_SECURE_NO_WARNINGS
#pragma once

#define SX_EXE
#define SX_GAME

#include <SkyXEngine.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	SkyXEngine_Init();
	
	SGCore_SkyBoxLoadTex("sky_2_cube.dds");
	SGCore_SkyCloudsLoadTex("sky_oblaka.dds");
	SGCore_SkyCloudsSetWidthHeightPos(2000, 2000, &float3(0, 0, 0));

	Level::Load("stalker_atp");

	SGeom_0SettGreenSetFreqGrass(30);

	/*for (int i = 0; i < 20; ++i)
	{
		for (int k = 0; k < 20; ++k)
		{
			ID tmpid = SPE_EffectCopyName("test");
			SPE_EffectPosSet(tmpid, &float3(i, 0, k));
			SPE_EffectEnableSet(tmpid, true);
		}
	}*/

	/*ID tmpid = SPE_EffectGetByName("test");
	SPE_EffectEnableSet(tmpid, true);*/

	SGCore_LoadTexStdPath(GData::Pathes::Textures);
	SGCore_LoadTexLoadTextures();

	/*ID tmpids = SSCore_SndCreate3d("Exclusion_zone.ogg", false, 0, 100, 0.1);
	SSCore_SndPosCurrSet(tmpids, 20, SOUND_POS_SEC);
	SSCore_SndPlay(tmpids);*/
	ID tmpidsnd = SSCore_SndCreate3d("Exclusion_zone.ogg", false, 0, 100, 0.1);
	if (tmpidsnd >= 0)
	{
		SSCore_SndPosCurrSet(tmpidsnd, 20, SOUND_POS_SEC);
		SSCore_SndPlay(tmpidsnd);
	//ms->SoundPanSet(tmpid, DSBPAN_RIGHT, 0);
	//ms->SoundVolumeSet(tmpid, 100);
	}

	
	int result = SkyXEngine_CycleMain();
	SkyXEngine_Kill();
	return result;
}
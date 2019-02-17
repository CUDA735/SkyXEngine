
/******************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

#define _CRT_SECURE_NO_WARNINGS

//#include <vld.h> 
#include <skyxengine.h>
#include <io.h>

#include "terrax.h"
#include "Grid.h"

#include "XStaticGeomObject.h"
#include "UndoManager.h"

extern HWND g_hWndMain;
CGrid *g_pGrid = NULL;
CTerraXRenderStates g_xRenderStates;

ATOM XRegisterClass(HINSTANCE hInstance);
BOOL XInitInstance(HINSTANCE, int);

Array<CXObject*> g_pLevelObjects;
//SGeom_GetCountModels()

static IGXVertexBuffer *g_pBorderVertexBuffer;
static IGXRenderBuffer *g_pBorderRenderBuffer;

CUndoManager *g_pUndoManager = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
//	SkyXEngine_PreviewCreate();
//	SXGUIinit();


	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_LISTVIEW_CLASSES | ICC_TREEVIEW_CLASSES | ICC_BAR_CLASSES | ICC_TAB_CLASSES;
	InitCommonControlsEx(&icex);

	XRegisterClass(hInstance);
	g_pUndoManager = new CUndoManager();

	if(!XInitInstance(hInstance, nCmdShow))
	{
		return(1);
	}

	SkyXEngine_Init(g_hTopLeftWnd, g_hWndMain, lpCmdLine);
	
	SGCore_SkyBoxLoadTex("sky_2_cube.dds");
	SGCore_SkyCloudsLoadTex("sky_oblaka.dds");
	SGCore_SkyBoxSetUse(false);
	SGCore_SkyCloudsSetUse(false);

	g_xConfig.m_pViewportCamera[XWP_TOP_RIGHT] = SGCore_CrCamera();
	g_xConfig.m_pViewportCamera[XWP_TOP_RIGHT]->setPosition(&X2D_TOP_POS);
	g_xConfig.m_pViewportCamera[XWP_TOP_RIGHT]->setOrientation(&X2D_TOP_ROT);

	g_xConfig.m_pViewportCamera[XWP_BOTTOM_LEFT] = SGCore_CrCamera();
	g_xConfig.m_pViewportCamera[XWP_BOTTOM_LEFT]->setPosition(&X2D_SIDE_POS);
	g_xConfig.m_pViewportCamera[XWP_BOTTOM_LEFT]->setOrientation(&X2D_SIDE_ROT);

	g_xConfig.m_pViewportCamera[XWP_BOTTOM_RIGHT] = SGCore_CrCamera();
	g_xConfig.m_pViewportCamera[XWP_BOTTOM_RIGHT]->setPosition(&X2D_FRONT_POS);
	g_xConfig.m_pViewportCamera[XWP_BOTTOM_RIGHT]->setOrientation(&X2D_FRONT_ROT);


//	SkyXEngine_RunGenPreview();
//	Core_0SetCVarInt("r_final_image", DS_RT_COLOR);

	SRender_EditorSetRenderGrid(true);
	SRender_EditorSetRenderAxesStatic(true);

	g_pGrid = new CGrid();
	g_pGrid->setOpacity(0.7f);
	
	int countgc = SGame_EntGetClassListCount();
	const char** listgc = new const char*[countgc];

	SGame_EntGetClassList(listgc, countgc);
	for(int i = 0; i < countgc; ++i)
	{
	//	level_editor::pComboBoxGameClass->addItem(listgc[i]);
	}
	mem_delete_a(listgc);


//	SkyXEngine_PreviewKill();
	IGXContext *pDevice = SGCore_GetDXDevice();

	GXBLEND_DESC blendDesc;
	blendDesc.renderTarget[0].bBlendEnable = true;
	blendDesc.renderTarget[0].srcBlend = blendDesc.renderTarget[0].srcBlendAlpha = GXBLEND_BLEND_FACTOR;
	blendDesc.renderTarget[0].destBlend = blendDesc.renderTarget[0].destBlendAlpha = GXBLEND_INV_BLEND_FACTOR;
	g_xRenderStates.pBlendColorFactor = pDevice->createBlendState(&blendDesc);

	blendDesc.renderTarget[0].srcBlend = blendDesc.renderTarget[0].srcBlendAlpha = GXBLEND_SRC_ALPHA;
	blendDesc.renderTarget[0].destBlend = blendDesc.renderTarget[0].destBlendAlpha = GXBLEND_INV_SRC_ALPHA;
	g_xRenderStates.pBlendAlpha = pDevice->createBlendState(&blendDesc);

	GXRASTERIZER_DESC rsDesc;
	rsDesc.fillMode = GXFILL_WIREFRAME;
	rsDesc.cullMode = GXCULL_NONE;
	g_xRenderStates.pRSWireframe = SGCore_GetDXDevice()->createRasterizerState(&rsDesc);

	g_xRenderStates.idTexturedShaderVS = SGCore_ShaderLoad(SHADER_TYPE_VERTEX, "terrax_textured.vs", "terrax_textured.vs", SHADER_CHECKDOUBLE_PATH);
	g_xRenderStates.idTexturedShaderPS = SGCore_ShaderLoad(SHADER_TYPE_PIXEL, "terrax_textured.ps", "terrax_textured.ps", SHADER_CHECKDOUBLE_PATH);
	g_xRenderStates.idTexturedShaderKit = SGCore_ShaderCreateKit(g_xRenderStates.idTexturedShaderVS, g_xRenderStates.idTexturedShaderPS);

	GXVERTEXELEMENT oLayout[] =
	{
		{0, 0, GXDECLTYPE_FLOAT3, GXDECLUSAGE_POSITION},
		{0, 12, GXDECLTYPE_FLOAT2, GXDECLUSAGE_TEXCOORD},
		GXDECL_END()
	};
	IGXVertexDeclaration *pVD = pDevice->createVertexDeclaration(oLayout);
	g_pBorderVertexBuffer = pDevice->createVertexBuffer(sizeof(XBorderVertex) * 5, GX_BUFFER_USAGE_STREAM | GX_BUFFER_WRITEONLY);
	g_pBorderRenderBuffer = pDevice->createRenderBuffer(1, &g_pBorderVertexBuffer, pVD);
	mem_release(pVD);

	

	int result = SkyXEngine_CycleMain();
	mem_delete(g_pGrid);
	mem_delete(g_pUndoManager);
	SkyXEngine_Kill();
	return result;
}

void XRender3D()
{
	for(UINT i = 0, l = g_pLevelObjects.size(); i < l; ++i)
	{
		if(g_pLevelObjects[i]->isSelected())
		{
			g_pLevelObjects[i]->renderSelection(true);
		}
	}

	if(g_xState.isFrameSelect)
	{
		X_2D_VIEW xCurView = g_xConfig.m_x2DView[g_xState.activeWindow];

		float3_t va, vb, vc, vd;

		switch(xCurView)
		{
		case X2D_TOP:
			va = float3_t(g_xState.vFrameSelectStart.x, 0.0f, g_xState.vFrameSelectStart.y);
			vb = float3_t(g_xState.vWorldMousePos.x, 0.0f, g_xState.vFrameSelectStart.y);
			vc = float3_t(g_xState.vWorldMousePos.x, 0.0f, g_xState.vWorldMousePos.y);
			vd = float3_t(g_xState.vFrameSelectStart.x, 0.0f, g_xState.vWorldMousePos.y);
			break;
		case X2D_FRONT:
			va = float3_t(g_xState.vFrameSelectStart.x, g_xState.vFrameSelectStart.y, 0.0f);
			vb = float3_t(g_xState.vWorldMousePos.x, g_xState.vFrameSelectStart.y, 0.0f);
			vc = float3_t(g_xState.vWorldMousePos.x, g_xState.vWorldMousePos.y, 0.0f);
			vd = float3_t(g_xState.vFrameSelectStart.x, g_xState.vWorldMousePos.y, 0.0f);
			break;
		case X2D_SIDE:
			va = float3_t(0.0f, g_xState.vFrameSelectStart.y, g_xState.vFrameSelectStart.x);
			vb = float3_t(0.0f, g_xState.vFrameSelectStart.y, g_xState.vWorldMousePos.x);
			vc = float3_t(0.0f, g_xState.vWorldMousePos.y, g_xState.vWorldMousePos.x);
			vd = float3_t(0.0f, g_xState.vWorldMousePos.y, g_xState.vFrameSelectStart.x);
			break;
		}

		XDrawBorder(GXCOLOR_ARGB(255, 255, 255, 0), va, vb, vc, vd);
	}
}

void XRender2D(X_2D_VIEW view, float fScale, bool preScene)
{
	if(preScene)
	{
		if(g_xConfig.m_bShowGrid)
		{
			GRID_STEP step = g_xConfig.m_gridStep;
			GRID_STEP minStep = CGrid::GetMinStepForScale(fScale);
			if(step < minStep)
			{
				step = minStep;
			}
			switch(view)
			{
			case X2D_FRONT:
				Core_RMatrixSet(G_RI_MATRIX_WORLD, &SMMatrixRotationX(SM_PIDIV2));
				break;
			case X2D_SIDE:
				Core_RMatrixSet(G_RI_MATRIX_WORLD, &SMMatrixRotationZ(SM_PIDIV2));
				break;
			}
			g_pGrid->setOpacity(g_xConfig.m_fGridOpacity);
			g_pGrid->setDottedMode(g_xConfig.m_bDottedGrid);
			g_pGrid->render(step);

			Core_RMatrixSet(G_RI_MATRIX_WORLD, &SMMatrixIdentity());

		}
	}
	else
	{
		for(UINT i = 0, l = g_pLevelObjects.size(); i < l; ++i)
		{
			if(g_pLevelObjects[i]->isSelected())
			{
				g_pLevelObjects[i]->renderSelection(false);
			}
		}

		if(g_xState.isFrameSelect)
		{
			X_2D_VIEW xCurView = g_xConfig.m_x2DView[g_xState.activeWindow];
			float3_t va, vb, vc, vd;
			switch(xCurView)
			{
			case X2D_TOP:
				va = float3_t(g_xState.vFrameSelectStart.x, 0.0f, g_xState.vFrameSelectStart.y);
				vb = float3_t(g_xState.vWorldMousePos.x, 0.0f, g_xState.vFrameSelectStart.y);
				vc = float3_t(g_xState.vWorldMousePos.x, 0.0f, g_xState.vWorldMousePos.y);
				vd = float3_t(g_xState.vFrameSelectStart.x, 0.0f, g_xState.vWorldMousePos.y);
				break;
			case X2D_FRONT:
				va = float3_t(g_xState.vFrameSelectStart.x, g_xState.vFrameSelectStart.y, 0.0f);
				vb = float3_t(g_xState.vWorldMousePos.x, g_xState.vFrameSelectStart.y, 0.0f);
				vc = float3_t(g_xState.vWorldMousePos.x, g_xState.vWorldMousePos.y, 0.0f);
				vd = float3_t(g_xState.vFrameSelectStart.x, g_xState.vWorldMousePos.y, 0.0f);
				break;
			case X2D_SIDE:
				va = float3_t(0.0f, g_xState.vFrameSelectStart.y, g_xState.vFrameSelectStart.x);
				vb = float3_t(0.0f, g_xState.vFrameSelectStart.y, g_xState.vWorldMousePos.x);
				vc = float3_t(0.0f, g_xState.vWorldMousePos.y, g_xState.vWorldMousePos.x);
				vd = float3_t(0.0f, g_xState.vWorldMousePos.y, g_xState.vFrameSelectStart.x);
				break;
			}
			XDrawBorder(GXCOLOR_ARGB(255, 255, 255, 0), va, vb, vc, vd, fScale);
		}
		if(g_xState.bHasSelection)
		{
			float3_t va, vb, vc, vd;
			switch(view)
			{
			case X2D_TOP:
				va = float3_t(g_xState.vSelectionBoundMin.x, 0.0f, g_xState.vSelectionBoundMin.z);
				vb = float3_t(g_xState.vSelectionBoundMax.x, 0.0f, g_xState.vSelectionBoundMin.z);
				vc = float3_t(g_xState.vSelectionBoundMax.x, 0.0f, g_xState.vSelectionBoundMax.z);
				vd = float3_t(g_xState.vSelectionBoundMin.x, 0.0f, g_xState.vSelectionBoundMax.z);
				break;
			case X2D_FRONT:
				va = float3_t(g_xState.vSelectionBoundMin.x, g_xState.vSelectionBoundMin.y, 0.0f);
				vb = float3_t(g_xState.vSelectionBoundMax.x, g_xState.vSelectionBoundMin.y, 0.0f);
				vc = float3_t(g_xState.vSelectionBoundMax.x, g_xState.vSelectionBoundMax.y, 0.0f);
				vd = float3_t(g_xState.vSelectionBoundMin.x, g_xState.vSelectionBoundMax.y, 0.0f);
				break;
			case X2D_SIDE:
				va = float3_t(0.0f, g_xState.vSelectionBoundMin.y, g_xState.vSelectionBoundMin.z);
				vb = float3_t(0.0f, g_xState.vSelectionBoundMin.y, g_xState.vSelectionBoundMax.z);
				vc = float3_t(0.0f, g_xState.vSelectionBoundMax.y, g_xState.vSelectionBoundMax.z);
				vd = float3_t(0.0f, g_xState.vSelectionBoundMax.y, g_xState.vSelectionBoundMin.z);
				break;
			}
			XDrawBorder(GXCOLOR_ARGB(255, 255, 0, 0), va, vb, vc, vd, fScale);
		}
	}
}

void XLoadLevel(const char *szName)
{
	XResetLevel();

	SLevel_Load(szName, false);
	char szCaption[256];
	sprintf(szCaption, "%s - [%s] | %s", MAIN_WINDOW_TITLE, szName, SKYXENGINE_VERSION4EDITORS);
	SetWindowText(g_hWndMain, szCaption);

	for(ID i = 0, l = SGeom_GetCountModels(); i < l; ++i)
	{
		g_pLevelObjects.push_back(new CXStatixGeomObject(i));
	//	g_pLevelObjects[i]->setSelected(true);
	}
}

void XResetLevel()
{
	SetWindowText(g_hWndMain, MAIN_WINDOW_TITLE " | " SKYXENGINE_VERSION4EDITORS);

	SLevel_Clear();
	ID gid = SLight_GetGlobal();
	if(ID_VALID(gid))
	{
		SLight_DeleteLight(gid);
	}

	for(UINT i = 0, l = g_pLevelObjects.size(); i < l; ++i)
	{
		mem_delete(g_pLevelObjects[i]);
	}
	g_pLevelObjects.clear();
}

bool XSaveLevel(const char *szNewName)
{
	if(szNewName)
	{
		SLevel_Save(szNewName);
		return(true);
	}
	
	if(SLevel_GetName()[0])
	{
		return(XSaveLevel(SLevel_GetName()));
	}
		
	char szPath[1024];
	szPath[0] = 0;
	char szName[1024];
	if(gui_func::dialogs::SelectDirOwn(szName, szPath, Core_RStringGet(G_RI_STRING_PATH_GS_LEVELS), "Save level", false, true, 0))
	{
		return(XSaveLevel(szName));
	}
	
	return(false);
}

void XDrawBorder(GXCOLOR color, const float3_t &vA, const float3_t &vB, const float3_t &vC, const float3_t &vD, float fViewportScale)
{
	float2_t ta, tb, tc, td;
	if(vA.x == vB.x && vB.x == vC.x)
	{
		ta = float2_t(vA.y, vA.z);
		tb = float2_t(vB.y, vB.z);
		tc = float2_t(vC.y, vC.z);
		td = float2_t(vD.y, vD.z);
	}
	else if(vA.y == vB.y && vB.y == vC.y)
	{
		ta = float2_t(vA.x, vA.z);
		tb = float2_t(vB.x, vB.z);
		tc = float2_t(vC.x, vC.z);
		td = float2_t(vD.x, vD.z);
	}
	else
	{
		ta = float2_t(vA.x, vA.y);
		tb = float2_t(vB.x, vB.y);
		tc = float2_t(vC.x, vC.y);
		td = float2_t(vD.x, vD.y);
	}

	XBorderVertex *pData;
	if(g_pBorderVertexBuffer->lock((void**)&pData, GXBL_WRITE))
	{
		pData[0] = {vA, ta / fViewportScale / 6.0f};
		pData[1] = {vB, tb / fViewportScale / 6.0f};
		pData[2] = {vC, tc / fViewportScale / 6.0f};
		pData[3] = {vD, td / fViewportScale / 6.0f};
		pData[4] = pData[0];
		g_pBorderVertexBuffer->unlock();
	}

	IGXContext *pDevice = SGCore_GetDXDevice();
	IGXBlendState *pOldBlendState = pDevice->getBlendState();
	SGCore_ShaderBind(g_xRenderStates.idTexturedShaderKit);

	SMMATRIX mViewProj;
	Core_RMatrixGet(G_RI_MATRIX_VIEWPROJ, &mViewProj);
	SGCore_ShaderSetVRF(SHADER_TYPE_VERTEX, g_xRenderStates.idTexturedShaderVS, "g_mWVP", &SMMatrixTranspose(mViewProj), 4);
	SGCore_ShaderSetVRF(SHADER_TYPE_PIXEL, g_xRenderStates.idTexturedShaderPS, "g_vColor", &GXCOLOR_COLORVECTOR_ARGB(color), 1);
	pDevice->setTexture(SGCore_LoadTexGetTex(SRender_EditorGetDashedTex()));
	pDevice->setBlendState(g_xRenderStates.pBlendAlpha);
	pDevice->setRenderBuffer(g_pBorderRenderBuffer);
	pDevice->setPrimitiveTopology(GXPT_LINESTRIP);
	pDevice->drawPrimitive(0, 4);
	SGCore_ShaderUnBind();

	pDevice->setBlendState(pOldBlendState);
	mem_release(pOldBlendState);
}

void XUpdateUndoRedo();
bool XExecCommand(CCommand *pCommand)
{
	if(g_pUndoManager->execCommand(pCommand))
	{
		XUpdateUndoRedo();
		return(true);
	}
	return(false);
}

void XUpdateSelectionBound()
{
	g_xState.bHasSelection = false;
	float3 vMin, vMax;

	for(UINT i = 0, l = g_pLevelObjects.size(); i < l; ++i)
	{
		if(g_pLevelObjects[i]->isSelected())
		{
			g_pLevelObjects[i]->getBound(&vMin, &vMax);
			if(!g_xState.bHasSelection)
			{
				g_xState.bHasSelection = true;
				g_xState.vSelectionBoundMax = vMax;
				g_xState.vSelectionBoundMin = vMin;
			}
			else
			{
				g_xState.vSelectionBoundMax = (float3)SMVectorMax(g_xState.vSelectionBoundMax, vMax);
				g_xState.vSelectionBoundMin = (float3)SMVectorMin(g_xState.vSelectionBoundMin, vMin);
			}
		}
	}
}

bool XRayCast(X_WINDOW_POS wnd)
{
	float3 vStart, vEnd, vPos, vCamPos;
	if(!g_xConfig.m_pViewportCamera[wnd])
	{
		return(false);
	}
	g_xConfig.m_pViewportCamera[wnd]->getPosition(&vCamPos);
	switch(g_xConfig.m_x2DView[wnd])
	{
	case X2D_NONE:
		return(false);
	case X2D_TOP:
		vStart = float3(g_xState.vWorldMousePos.x, vCamPos.y, g_xState.vWorldMousePos.y);
		vEnd = float3(0.0f, -2000.0f, 0.0f);
		break;
	case X2D_FRONT:
		vStart = float3(g_xState.vWorldMousePos.x, g_xState.vWorldMousePos.y, vCamPos.z);
		vEnd = float3(0.0f, 0.0f, 2000.0f);
		break;
	case X2D_SIDE:
		vStart = float3(vCamPos.x, g_xState.vWorldMousePos.y, g_xState.vWorldMousePos.x);
		vEnd = float3(-2000.0f, 0.0f, 0.0f);
		break;
	}
	vEnd += vStart;
	for(UINT i = 0, l = g_pLevelObjects.size(); i < l; ++i)
	{
		if(g_pLevelObjects[i]->isSelected() && g_pLevelObjects[i]->rayTest(vStart, vEnd, &vPos, NULL))
		{
			return(true);
		}
	}
	return(false);
}
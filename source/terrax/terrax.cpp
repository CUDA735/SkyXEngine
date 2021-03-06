
/******************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

#define _CRT_SECURE_NO_WARNINGS

//#include <vld.h> 
#include <skyxengine.h>
#include <io.h>
#include <windowsx.h>
#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")
#include "resource.h"

#include "terrax.h"
#include "Grid.h"
#include "PropertyWindow.h"

#include <xcommon/editor/IXEditorObject.h>
#include <xcommon/editor/IXEditable.h>
#include <xcommon/IXRenderable.h>
#include <xcommon/resource/IXResourceManager.h>
#include <xcommon/render/IXRenderUtils.h>
#include <mtrl/IXMaterialSystem.h>
#include "UndoManager.h"
#include "Tools.h"

#include <xEngine/IXEngine.h>

#ifdef _DEBUG
#	pragma comment(lib, "xEngine_d.lib")
#else
#	pragma comment(lib, "xEngine.lib")
#endif

GX_ENABLE_HIGH_PERFORMANCE_DUAL_GPU();

extern HWND g_hWndMain;
CGrid *g_pGrid = NULL;
CTerraXRenderStates g_xRenderStates;

extern CPropertyWindow *g_pPropWindow;

ATOM XRegisterClass(HINSTANCE hInstance);
BOOL XInitInstance(HINSTANCE, int);

Array<IXEditable*> g_pEditableSystems;
Array<IXEditorObject*> g_pLevelObjects;
AssotiativeArray<AAString, IXEditable*> g_mEditableSystems;
//SGeom_GetCountModels()

static IGXVertexBuffer *g_pBorderVertexBuffer;
static IGXRenderBuffer *g_pBorderRenderBuffer;

CUndoManager *g_pUndoManager = NULL;
extern HWND g_hComboTypesWnd;

String g_sLevelName;

void XUpdateWindowTitle();

HACCEL g_hAccelTableMain = NULL;
HACCEL g_hAccelTableEdit = NULL;
IXEngine *g_pEngine = NULL;

IGXConstantBuffer *g_pCameraConstantBuffer = NULL;
IGXSwapChain *g_pTopRightSwapChain = NULL;
IGXSwapChain *g_pBottomLeftSwapChain = NULL;
IGXSwapChain *g_pBottomRightSwapChain = NULL;
IGXSwapChain *g_pGuiSwapChain = NULL;
IGXDepthStencilSurface *g_pTopRightDepthStencilSurface = NULL;
IGXDepthStencilSurface *g_pBottomLeftDepthStencilSurface = NULL;
IGXDepthStencilSurface *g_BottomRightDepthStencilSurface = NULL;
IGXDepthStencilSurface *g_pGuiDepthStencilSurface = NULL;
IGXDepthStencilState *g_pDSNoZ;
IGXDepthStencilState *g_pDSDefault;

IGXTexture2D *g_pDashedMaterial = NULL;

void XReleaseViewports();
void XInitViewports();
void XInitViewportLayout(X_VIEWPORT_LAYOUT layout);
void XExportToObj(const char *szMdl);
bool IsEditMessage();
bool IsButtonMessage();

class CEngineCallback: public IXEngineCallback
{
public:
	void XMETHODCALLTYPE onGraphicsResize(UINT uWidth, UINT uHeight, bool isFullscreen, bool isBorderless, IXEngine *pEngine) override
	{
		static const bool *terrax_detach_3d = NULL;
		if(!terrax_detach_3d && m_pCore)
		{
			terrax_detach_3d = m_pCore->getConsole()->getPCVarBool("terrax_detach_3d");
		}

		if(terrax_detach_3d && *terrax_detach_3d)
		{
			RECT rc = {0, 0, (int)uWidth, (int)uHeight};

			HMONITOR monitor = MonitorFromWindow(g_hTopLeftWnd, MONITOR_DEFAULTTONEAREST);
			MONITORINFO info;
			info.cbSize = sizeof(MONITORINFO);
			GetMonitorInfo(monitor, &info);
			bool bForceNoBorder = (rc.right - rc.left == info.rcMonitor.right - info.rcMonitor.left
				&& rc.bottom - rc.top == info.rcMonitor.bottom - info.rcMonitor.top);


			SetClassLong(g_hTopLeftWnd, GCL_STYLE, GetClassLong(g_hTopLeftWnd, GCL_STYLE) | CS_NOCLOSE);

			DWORD wndStyle = GetWindowLong(g_hTopLeftWnd, GWL_STYLE) | WS_MINIMIZEBOX | WS_SYSMENU;

			if(isFullscreen || isBorderless || bForceNoBorder)
			{
				wndStyle &= ~(WS_SYSMENU | WS_CAPTION | WS_MAXIMIZE | WS_MINIMIZE | WS_THICKFRAME);
			}
			else
			{
				wndStyle |= WS_CAPTION | WS_THICKFRAME;
				wndStyle &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
			}

			SetWindowLong(g_hTopLeftWnd, GWL_STYLE, wndStyle);


			AdjustWindowRect(&rc, wndStyle, false);

			UINT uSWPflags = SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOOWNERZORDER;


			int iPosX = 0;
			int iPosY = 0;
			if(!(isFullscreen || isBorderless))
			{
				iPosX = (GetSystemMetrics(SM_CXSCREEN) - (rc.right - rc.left)) / 2;
				iPosY = (GetSystemMetrics(SM_CYSCREEN) - (rc.bottom - rc.top)) / 2;
			}
			RECT rcOld;
			GetWindowRect(g_hTopLeftWnd, &rcOld);


			if(rcOld.right - rcOld.left != rc.right - rc.left || rcOld.bottom - rcOld.top != rc.bottom - rc.top)
			{
				uSWPflags &= ~SWP_NOSIZE;
				//SetWindowPos(m_hWnd, HWND_TOP, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOACTIVATE | SWP_NOCOPYBITS | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
			}

			SetWindowPos(g_hTopLeftWnd, HWND_TOP, iPosX, iPosY, rc.right - rc.left, rc.bottom - rc.top, uSWPflags);
		}
		else
		{
			XReleaseViewports();
			XInitViewports();
		}
	}

	bool XMETHODCALLTYPE processWindowMessages() override
	{
		MSG msg = {0};

		char className[32];

		while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				return(false);
			}
			if(IsEditMessage())
			{
				if(TranslateAccelerator(GetParent((HWND)SGCore_GetHWND()), g_hAccelTableEdit, &msg))
				{
					continue;
				}
			}
			else if(GetActiveWindow() == g_hWndMain)
			{
				if(TranslateAccelerator(GetParent((HWND)SGCore_GetHWND()), g_hAccelTableMain, &msg))
				{
					continue;
				}
			}

			HWND hWnd = msg.hwnd;
			while(hWnd)
			{
				RealGetWindowClass(hWnd, className, sizeof(className));
				if(!strcmp(className, "#32770"))
				{
					break;
				}
				hWnd = GetParent(hWnd);
			}

			if(hWnd && IsDialogMessage(hWnd, &msg))
			{
				continue;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		static time_point tPrev = std::chrono::high_resolution_clock::now();
		time_point tNow = std::chrono::high_resolution_clock::now();
		float fDeltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(tNow - tPrev).count() * 0.000001f;
		tPrev = tNow;

		if(g_is3DRotating || g_is3DPanning || g_is2DPanning)
		{
			int x, y;
			SSInput_GetMouseDelta(&x, &y);
			static const float * sense = GET_PCVAR_FLOAT("cl_mousesense");
			float fCoeff = SMToRadian(0.022) * *sense;
			float dx = (float)x * fCoeff;
			float dy = (float)y * fCoeff;
			ICamera *pCamera = g_xConfig.m_pViewportCamera[XWP_TOP_LEFT];

			if(g_is3DRotating)
			{
				static float3 m_vPitchYawRoll;
				m_vPitchYawRoll.y -= dx;
				m_vPitchYawRoll.x -= dy;
				m_vPitchYawRoll.x = clampf(m_vPitchYawRoll.x, -SM_PIDIV2, SM_PIDIV2);
				while(m_vPitchYawRoll.y < 0.0f)
				{
					m_vPitchYawRoll.y += SM_2PI;
				}
				while(m_vPitchYawRoll.y > SM_2PI)
				{
					m_vPitchYawRoll.y -= SM_2PI;
				}

				pCamera->setOrientation(SMQuaternion(m_vPitchYawRoll.x, 'x') * SMQuaternion(m_vPitchYawRoll.z, 'z') * SMQuaternion(m_vPitchYawRoll.y, 'y'));
			}
			else if(g_is3DPanning)
			{
				float3 vPos = pCamera->getPosition();
				float3 vUp = pCamera->getUp();
				float3 vRight = pCamera->getRight();
				vPos += vUp * -dy * 10.0f + vRight * dx * 10.0f;
				pCamera->setPosition(vPos);
			}
			else if(g_is2DPanning)
			{
				// vWorldDelta
				ICamera *pCamera = g_xConfig.m_pViewportCamera[g_xState.activeWindow];
				X_2D_VIEW xCurView = g_xConfig.m_x2DView[g_xState.activeWindow];
				float3 vWorldDelta = float2(-(float)x, (float)y) * g_xConfig.m_fViewportScale[g_xState.activeWindow];

				// printf("%5d, %5d\n", x, y);

				float3 vWorldDelta3D;
				switch(xCurView)
				{
				case X2D_TOP:
					vWorldDelta3D = float3(vWorldDelta.x, 0.0f, vWorldDelta.y);
					break;
				case X2D_FRONT:
					vWorldDelta3D = float3(vWorldDelta.x, vWorldDelta.y, 0.0f);
					break;
				case X2D_SIDE:
					vWorldDelta3D = float3(0.0f, vWorldDelta.y, vWorldDelta.x);
					break;
				}

				pCamera->setPosition(pCamera->getPosition() + vWorldDelta3D);
			}

			if(g_is3DPanning || g_is3DRotating)
			{
				float3 dir;
				static float s_fSpeed = 0;
				float fMaxSpeed = 10.0f; //@TODO: CVar this!
				float fMaxSpeedBoost = 40.0f; //@TODO: CVar this!
				float fAccelTime = 0.5f; //@TODO: CVar this!
				if(GetAsyncKeyState(VK_SHIFT) < 0)
				{
					fMaxSpeed = fMaxSpeedBoost;
				}
				float fAccel = fMaxSpeed / fAccelTime;
				bool mov = false;
				if(GetAsyncKeyState('W') < 0)
				{
					dir.z += 1.0f;
					mov = true;
				}
				if(GetAsyncKeyState('S') < 0)
				{
					dir.z -= 1.0f;
					mov = true;
				}
				if(GetAsyncKeyState('A') < 0)
				{
					dir.x -= 1.0f;
					mov = true;
				}
				if(GetAsyncKeyState('D') < 0)
				{
					dir.x += 1.0f;
					mov = true;
				}

				if(mov)
				{
					s_fSpeed += fAccel * fDeltaTime;
					if(s_fSpeed > fMaxSpeed)
					{
						s_fSpeed = fMaxSpeed;
					}
					float3 vPos = pCamera->getPosition();
					float3 vDir = pCamera->getLook();
					float3 vRight = pCamera->getRight();
					dir = SMVector3Normalize(dir) * fDeltaTime * s_fSpeed;
					vPos += vDir * dir.z + vRight * dir.x;
					pCamera->setPosition(vPos);
				}
				else
				{
					s_fSpeed = 0;
				}
			}
		}

		XFrameRun(fDeltaTime);

		return(true);
	}

	ICamera* XMETHODCALLTYPE getCameraForFrame() override
	{
		static const bool *terrax_detach_3d = m_pCore->getConsole()->getPCVarBool("terrax_detach_3d");
		if(*terrax_detach_3d)
		{
			return(SGame_GetActiveCamera());
		}
		
		return(g_xConfig.m_pViewportCamera[XWP_TOP_LEFT]);
	}

	void setCore(IXCore *pCore)
	{
		m_pCore = pCore;
	}

protected:
	IXCore *m_pCore = NULL;
};

class CRenderPipeline: public IXUnknownImplementation<IXRenderPipeline>
{
public:
	CRenderPipeline(IXCore *pCore):
		m_pCore(pCore)
	{
		pCore->getRenderPipeline(&m_pOldPipeline);
		pCore->setRenderPipeline(this);

		IPluginManager *pPluginManager = pCore->getPluginManager();
		m_pMaterialSystem = (IXMaterialSystem*)pPluginManager->getInterface(IXMATERIALSYSTEM_GUID);

		{
			//m_pRenderPassGeometry2D = m_pMaterialSystem->getRenderPass("xGBuffer");
			m_pRenderPassGeometry2D = m_pMaterialSystem->registerRenderPass("xEditor2D", "terrax/geom2d.ps", NULL, NULL, NULL, NULL, true);
		}

		m_pCameraVisibility[0] = NULL;
		for(UINT i = 0; i < 3; ++i)
		{
			newVisData(&m_pCameraVisibility[i + 1]);
		}

		IXRenderUtils *pUtils = (IXRenderUtils*)pPluginManager->getInterface(IXRENDERUTILS_GUID);
		pUtils->newGizmoRenderer(&m_pTestRenderer);

		IXTexture *pLineTexture;
		m_pMaterialSystem->loadTexture("dev_line", &pLineTexture);
		IGXBaseTexture *pGXTexture;
		pLineTexture->getAPITexture(&pGXTexture);
		m_pTestRenderer->setTexture(pGXTexture);
		mem_release(pGXTexture);
		mem_release(pLineTexture);

		m_pTestRenderer->setColor(float4(1.0f, 0.0f, 0.0f, 1.0f));
		m_pTestRenderer->setLineWidth(0.04f);
		//m_pTestRenderer->setLineWidth(20.0f);
		m_pTestRenderer->setLineWidth(3.0f);
		m_pTestRenderer->jumpTo(float3(0.0f, 0.0f, 0.0f));
		m_pTestRenderer->lineTo(float3(1.0f, 0.0f, 0.0f));
		m_pTestRenderer->setColor(float4(0.0f, 1.0f, 0.0f, 1.0f));
		m_pTestRenderer->jumpTo(float3(0.0f, 0.0f, 0.0f));
		m_pTestRenderer->lineTo(float3(0.0f, 1.0f, 0.0f));
		m_pTestRenderer->setColor(float4(0.0f, 0.0f, 1.0f, 1.0f));
		m_pTestRenderer->jumpTo(float3(0.0f, 0.0f, 0.0f));
		m_pTestRenderer->lineTo(float3(0.0f, 0.0f, 1.0f));


#if 0
		m_pTestRenderer->drawEllipsoid(float3(2.0f, 2.0f, 2.0f), float3(0.5f, 3.0f, 0.5f));
		m_pTestRenderer->setLineWidth(5.0f);
		m_pTestRenderer->setColor(float4(1.0f, 1.0f, 1.0f, 1.0f));
		m_pTestRenderer->drawAABB(SMAABB(float3(2.0f, 2.0f, 2.0f), float3(3.0f, 4.0f, 5.0f)));

		m_pMaterialSystem->loadTexture("dev_trigger", &pLineTexture);
		pLineTexture->getAPITexture(&pGXTexture);
		m_pTestRenderer->setTexture(NULL);
		mem_release(pGXTexture);
		mem_release(pLineTexture);


		m_pTestRenderer->setPointSize(10.0f);
		m_pTestRenderer->setPointMode(XGPM_ROUND);
		m_pTestRenderer->drawPoint(float3(1.0f, 1.0f, 1.0f));
#endif
		// m_pTestRenderer->jumpTo(float3(0.0f, 0.0f, 3.0f));
		// m_pTestRenderer->lineTo(float3(1.0f, 0.0f, 3.0f));
		// m_pTestRenderer->lineTo(float3(1.0f, 1.0f, 3.0f));
		// m_pTestRenderer->lineTo(float3(1.0f, 1.0f, 4.0f));
	}
	~CRenderPipeline()
	{
		mem_release(m_pTestRenderer);

		for(UINT i = 0; i < 3; ++i)
		{
			mem_release(m_pCameraVisibility[i + 1]);
		}

		m_pCore->setRenderPipeline(m_pOldPipeline);
		mem_release(m_pOldPipeline);
	}

	void resize(UINT uWidth, UINT uHeight, bool isWindowed = true) override
	{
		m_pOldPipeline->resize(uWidth, uHeight, isWindowed);
	}

	void renderFrame(float fDeltaTime) override
	{
		m_pOldPipeline->renderFrame(fDeltaTime);

		static const bool *terrax_detach_3d = m_pCore->getConsole()->getPCVarBool("terrax_detach_3d");

		if(*terrax_detach_3d)
		{
			return;
		}
		
		IGXContext *pDXDevice = getDevice()->getThreadContext();
		pDXDevice->setDepthStencilState(g_pDSDefault);

		m_pMaterialSystem->bindRenderPass(m_pRenderPassGeometry2D);

		XRender3D();

		m_pTestRenderer->render(false);

		//#############################################################################
		HWND hWnds[] = {g_hTopRightWnd, g_hBottomLeftWnd, g_hBottomRightWnd};
		IGXSwapChain *p2DSwapChains[] = {g_pTopRightSwapChain, g_pBottomLeftSwapChain, g_pBottomRightSwapChain};
		IGXDepthStencilSurface *p2DDepthStencilSurfaces[] = {g_pTopRightDepthStencilSurface, g_pBottomLeftDepthStencilSurface, g_BottomRightDepthStencilSurface};
		
		ICamera **pCameras = g_xConfig.m_pViewportCamera + 1;
		float *fScales = g_xConfig.m_fViewportScale + 1;
		X_2D_VIEW *views = g_xConfig.m_x2DView + 1;
		IXRenderableVisibility **pCameraVisibility = m_pCameraVisibility + 1;

		//[i + 1]
		//ICamera *p3DCamera = SRender_GetCamera();
		pDXDevice->setSamplerState(NULL, 0);
		//#############################################################################

		XUpdateSelectionBound();


		for(int i = 0; i < 3; ++i)
		{
			if(!IsWindowVisible(hWnds[i]))
			{
				continue;
			}
			SRender_SetCamera(pCameras[i]);
			IGXSurface *pBackBuffer = p2DSwapChains[i]->getColorTarget();
			pDXDevice->setColorTarget(pBackBuffer);
			pDXDevice->setDepthStencilSurface(p2DDepthStencilSurfaces[i]);
			pDXDevice->clear(GX_CLEAR_COLOR | GX_CLEAR_DEPTH | GX_CLEAR_STENCIL);

			pDXDevice->setRasterizerState(g_xRenderStates.pRSWireframe);
			pDXDevice->setDepthStencilState(g_pDSNoZ);
 			pDXDevice->setBlendState(NULL);
			SMMATRIX mProj = SMMatrixOrthographicLH((float)pBackBuffer->getWidth() * fScales[i], (float)pBackBuffer->getHeight() * fScales[i], 1.0f, 2000.0f);
			SMMATRIX mView = pCameras[i]->getViewMatrix();
			Core_RMatrixSet(G_RI_MATRIX_OBSERVER_VIEW, &mView);
			Core_RMatrixSet(G_RI_MATRIX_VIEW, &mView);
			Core_RMatrixSet(G_RI_MATRIX_OBSERVER_PROJ, &mProj);
			Core_RMatrixSet(G_RI_MATRIX_PROJECTION, &mProj);
			Core_RMatrixSet(G_RI_MATRIX_VIEWPROJ, &(mView * mProj));

			pCameras[i]->updateFrustum(mProj);

			g_pCameraConstantBuffer->update(&SMMatrixIdentity());
			pDXDevice->setVSConstant(g_pCameraConstantBuffer, SCR_OBJECT);

			Core_RMatrixSet(G_RI_MATRIX_WORLD, &SMMatrixIdentity());
			Core_RIntSet(G_RI_INT_RENDERSTATE, RENDER_STATE_FREE);

			XRender2D(views[i], fScales[i], true);

			renderEditor2D(pCameraVisibility[i]);

			Core_RIntSet(G_RI_INT_RENDERSTATE, RENDER_STATE_MATERIAL);
			pDXDevice->setVSConstant(g_pCameraConstantBuffer, SCR_OBJECT);
			XRender2D(views[i], fScales[i], false);


			m_pTestRenderer->render(true);

			mem_release(pBackBuffer);
		}



		g_pMaterialBrowser->render();

		/*
		IGXSurface *pBackBuffer = g_pGuiSwapChain->getColorTarget();
		pDXDevice->setColorTarget(pBackBuffer);
		pDXDevice->setDepthStencilSurface(g_pGuiDepthStencilSurface);
		pDXDevice->clear(GX_CLEAR_COLOR | GX_CLEAR_DEPTH | GX_CLEAR_STENCIL);
		XGuiRender();
		mem_release(pBackBuffer);
		*/
		//#############################################################################
		//SRender_SetCamera(p3DCamera);
		pDXDevice->setColorTarget(NULL);
		pDXDevice->setDepthStencilSurface(NULL);

	}
	void endFrame() override
	{
		m_pOldPipeline->endFrame();

		HWND hWnds[] = {g_hTopRightWnd, g_hBottomLeftWnd, g_hBottomRightWnd};
		IGXSwapChain *p2DSwapChains[] = {g_pTopRightSwapChain, g_pBottomLeftSwapChain, g_pBottomRightSwapChain};
		for(int i = 0; i < 3; ++i)
		{
			if(IsWindowVisible(hWnds[i]))
			{
				p2DSwapChains[i]->swapBuffers();
			}
		}

		g_pMaterialBrowser->swapBuffers();
	}
	void updateVisibility() override
	{
		m_pOldPipeline->updateVisibility();

		static const bool *terrax_detach_3d = m_pCore->getConsole()->getPCVarBool("terrax_detach_3d");

		if(*terrax_detach_3d)
		{
			return;
		}

		HWND hWnds[] = {g_hTopRightWnd, g_hBottomLeftWnd, g_hBottomRightWnd};

		for(UINT i = 0; i < 3; ++i)
		{
			if(!IsWindowVisible(hWnds[i]))
			{
				continue;
			}

			m_pCameraVisibility[i + 1]->updateForCamera(g_xConfig.m_pViewportCamera[i + 1]);
		}
	}

	void renderStage(X_RENDER_STAGE stage, IXRenderableVisibility *pVisibility = NULL) override
	{
		m_pOldPipeline->renderStage(stage, pVisibility);
	}

	IGXDevice *getDevice() override
	{
		return(m_pOldPipeline->getDevice());
	}

	void newVisData(IXRenderableVisibility **ppVisibility) override
	{
		m_pOldPipeline->newVisData(ppVisibility);
	}

//protected:

	void renderPrepare() override
	{
		m_pOldPipeline->renderPrepare();
	}
	void renderGBuffer() override
	{
		m_pOldPipeline->renderGBuffer();
	}
	void renderShadows() override
	{
		m_pOldPipeline->renderShadows();
	}
	void renderGI() override
	{
		m_pOldPipeline->renderGI();
	}
	void renderPostprocessMain() override
	{
		m_pOldPipeline->renderPostprocessMain();
	}
	void renderTransparent() override
	{
		m_pOldPipeline->renderTransparent();
	}
	void renderPostprocessFinal()  override
	{
		m_pOldPipeline->renderPostprocessFinal();
	}
	void renderEditor2D(IXRenderableVisibility *pVisibility) override
	{
		m_pOldPipeline->renderEditor2D(pVisibility);
	}

	IXCore *m_pCore;
	IXRenderPipeline *m_pOldPipeline = NULL;
	IXMaterialSystem *m_pMaterialSystem = NULL;

	XRenderPassHandler *m_pRenderPassGeometry2D = NULL;

	IXRenderableVisibility *m_pCameraVisibility[4];

	IXGizmoRenderer *m_pTestRenderer = NULL;
};

class CCVarEventListener: public IEventListener<XEventCvarChanged>
{
public:
	CCVarEventListener(IXCore *pCore):
		m_pCore(pCore)
	{}
	void onEvent(const XEventCvarChanged *pEvent) override
	{
		static const bool *terrax_detach_3d = m_pCore->getConsole()->getPCVarBool("terrax_detach_3d");

		if(terrax_detach_3d == pEvent->pCvar)
		{
			if(*terrax_detach_3d)
			{
				ShowWindow(g_hTopLeftWnd, SW_HIDE);
				m_lOldStyle = GetWindowLongA(g_hTopLeftWnd, GWL_STYLE);
				SetParent(g_hTopLeftWnd, NULL);
				SetWindowLongA(g_hTopLeftWnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
				SetWindowTextA(g_hTopLeftWnd, "SkyXEngine");

				m_lOldExStyle = GetWindowLongA(g_hTopLeftWnd, GWL_EXSTYLE);
				SetWindowLongA(g_hTopLeftWnd, GWL_EXSTYLE, 0);

				SetWindowPos(g_hTopLeftWnd, 
#ifdef _DEBUG
					HWND_TOP
#else
					HWND_TOPMOST
#endif
					, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);

				EnableWindow(g_hWndMain, FALSE);

				for(UINT i = 0, l = g_pLevelObjects.size(); i < l; ++i)
				{
					g_pLevelObjects[i]->setSimulationMode(true);
				}
			}
			else
			{
				EnableWindow(g_hWndMain, TRUE);

				ShowWindow(g_hTopLeftWnd, SW_HIDE);
				SetParent(g_hTopLeftWnd, g_hWndMain);
				SetWindowLongA(g_hTopLeftWnd, GWL_STYLE, m_lOldStyle);
				SetWindowLongA(g_hTopLeftWnd, GWL_EXSTYLE, m_lOldExStyle);
				SetWindowPos(g_hTopLeftWnd, HWND_TOP, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
				PostMessage(g_hWndMain, WM_SIZE, 0, 0);

				ShowCursor(TRUE);

				for(UINT i = 0, l = g_pLevelObjects.size(); i < l; ++i)
				{
					g_pLevelObjects[i]->setSimulationMode(false);
				}
			}
		}
	}

private:
	IXCore *m_pCore;
	LONG m_lOldStyle;
	LONG m_lOldExStyle;
};

#if defined(_WINDOWS)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);

	int argc = 0;
	char **argv = CommandLineToArgvA(lpCmdLine, &argc);
#else
int main(int argc, char **argv)
{
#endif

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

	//SkyXEngine_Init(g_hTopLeftWnd, g_hWndMain, lpCmdLine);
	IXEngine *pEngine = XEngineInit(argc, argv, "TerraX");
	g_pEngine = pEngine;
	CEngineCallback engineCb;
	pEngine->initGraphics((XWINDOW_OS_HANDLE)g_hTopLeftWnd, &engineCb);
	engineCb.setCore(pEngine->getCore());
	pEngine->getCore()->getConsole()->registerCVar("terrax_detach_3d", false, "", FCVAR_NOTIFY);
	pEngine->getCore()->getConsole()->execCommand("gmode editor");
	pEngine->getCore()->getConsole()->execCommand("exec ../config_editor.cfg");

	pEngine->getCore()->getConsole()->registerCommand("obj_dump", [](int argc, const char **argv){
		if(argc != 2)
		{
			printf("Usage: obj_dump <model>");
			return;
		}

		XExportToObj(argv[1]);
	}, "Export model to obj format");

	CRenderPipeline *pPipeline = new CRenderPipeline(Core_GetIXCore());

	CCVarEventListener cvarListener(pEngine->getCore());
	auto *pChannel = pEngine->getCore()->getEventChannel<XEventCvarChanged>(EVENT_CVAR_CHANGED_GUID);
	pChannel->addListener(&cvarListener);

	RECT rcTopLeft;
	GetClientRect(g_hTopLeftWnd, &rcTopLeft);

	g_pEngine->getCore()->getConsole()->execCommand2("r_win_width %d\nr_win_height %d", rcTopLeft.right - rcTopLeft.left, rcTopLeft.bottom - rcTopLeft.top);


	IPluginManager *pPluginManager = Core_GetIXCore()->getPluginManager();

	IXMaterialSystem *pMaterialSystem = (IXMaterialSystem*)pPluginManager->getInterface(IXMATERIALSYSTEM_GUID);

	pMaterialSystem->scanMaterials();

	GXCOLOR w = GX_COLOR_ARGB(255, 255, 255, 255);
	GXCOLOR t = GX_COLOR_ARGB(0, 255, 255, 255);
	GXCOLOR colorData[] = {
		t, t, t, w, w, w,
		w, t, t, t, w, w,
		w, w, t, t, t, w,
		w, w, w, t, t, t,
		t, w, w, w, t, t,
		t, t, w, w, w, t
	};
	g_pDashedMaterial = SGCore_GetDXDevice()->createTexture2D(6, 6, 1, 0, GXFMT_A8B8G8R8, colorData);
	//pMaterialSystem->addTexture("dev_dashed", pDashedMaterial);
	//mem_release(pDashedMaterial);

	//GXCOLOR tmpColor = GX_COLOR_ARGB(255, 255, 255, 255);
	//IGXTexture2D* pWhiteMaterial = SGCore_GetDXDevice()->createTexture2D(1, 1, 1, 0, GXFMT_A8R8G8B8, &tmpColor);
	////pMaterialSystem->addTexture("dev_white", pWhiteMaterial);
	//mem_release(pDashedMaterial);

	UINT ic = 0;
	IXEditable *pEditable;
	while((pEditable = (IXEditable*)pPluginManager->getInterface(IXEDITABLE_GUID, ic++)))
	{
		if(pEditable->getVersion() == IXEDITABLE_VERSION)
		{
			g_pEditableSystems.push_back(pEditable);
			pEditable->startup(SGCore_GetDXDevice());

			ComboBox_AddString(g_hComboTypesWnd, pEditable->getName());

			IXEditorExtension *pExt = pEditable->getEditorExtension();
			if(pExt)
			{
				for(UINT i = 0, l = pExt->getPropertyTabCount(); i < l; ++i)
				{
					g_pPropWindow->addCustomTab(pExt->getPropertyTab(i));
				}
			}

			g_mEditableSystems[AAString(pEditable->getName())] = pEditable;
		}
	}
	if(g_pEditableSystems.size() > 0)
	{
		ComboBox_SetCurSel(g_hComboTypesWnd, 0);
		SendMessage(GetParent(g_hComboTypesWnd), WM_COMMAND, MAKEWPARAM(IDC_CMB_TYPE, CBN_SELCHANGE), (LPARAM)g_hComboTypesWnd);
		if(g_pEditableSystems.size() == 1)
		{
			ComboBox_Enable(g_hComboTypesWnd, FALSE);
		}
	}
	
	Core_GetIXCore()->getEventChannel<XEventLevel>(EVENT_LEVEL_GUID)->addListener([](const XEventLevel *pData)
	{
		switch(pData->type)
		{
		case XEventLevel::TYPE_LOAD:
			g_sLevelName = pData->szLevelName;
			XUpdateWindowTitle();
			{
				char szPathLevel[1024], szKey[64];
				sprintf(szPathLevel, "%s%s/%s.lvl", Core_RStringGet(G_RI_STRING_PATH_GS_LEVELS), pData->szLevelName, pData->szLevelName);

				ISXConfig *pCfg = Core_OpConfig(szPathLevel);
				const char *szVal;

				szVal = pCfg->getKey("terrax", "vp_layout");
				if(szVal)
				{
					int iVal = 0;
					if(sscanf(szVal, "%d", &iVal) && iVal >= 0 && iVal <= 3)
					{
						XInitViewportLayout((X_VIEWPORT_LAYOUT)iVal);
					}
				}

				szVal = pCfg->getKey("terrax", "grid_step");
				if(szVal)
				{
					int iVal = 0;
					if(sscanf(szVal, "%d", &iVal) && iVal >= GRID_STEP_MINIMAL && iVal <= GRID_STEP_MAXIMAL)
					{
						g_xConfig.m_gridStep = (GRID_STEP)iVal;
					}
				}

				szVal = pCfg->getKey("terrax", "grid_show");
				if(szVal)
				{
					int iVal = 0;
					if(sscanf(szVal, "%d", &iVal))
					{
						g_xConfig.m_bShowGrid = iVal != 0;
					}
				}

				for(UINT i = 0; i < 4; ++i)
				{
					float3 vec;
					sprintf_s(szKey, "cam%u_pos", i);
					szVal = pCfg->getKey("terrax", szKey);
					if(szVal)
					{
						if(sscanf(szVal, "%f %f %f", &vec.x, &vec.y, &vec.z) == 3)
						{
							g_xConfig.m_pViewportCamera[i]->setPosition(vec);
						}
					}

					SMQuaternion q;
					sprintf_s(szKey, "cam%u_rot", i);
					szVal = pCfg->getKey("terrax", szKey);
					if(szVal)
					{
						if(sscanf(szVal, "%f %f %f %f", &q.x, &q.y, &q.z, &q.w) == 4)
						{
							g_xConfig.m_pViewportCamera[i]->setOrientation(q);
						}
					}

					sprintf_s(szKey, "cam%u_scale", i);
					szVal = pCfg->getKey("terrax", szKey);
					if(szVal)
					{
						float fVal = 0.0;
						if(sscanf(szVal, "%f", &fVal) && fVal > 0.0f)
						{
							g_xConfig.m_fViewportScale[i] = fVal;
						}
					}

					sprintf_s(szKey, "cam%u_view", i);
					szVal = pCfg->getKey("terrax", szKey);
					if(szVal)
					{
						int iVal = 0;
						if(sscanf(szVal, "%d", &iVal) && iVal >= -1 && iVal <= 2)
						{
							g_xConfig.m_x2DView[i] = (X_2D_VIEW)iVal;
						}
					}
				}

				mem_release(pCfg);
			}
			break;
		case XEventLevel::TYPE_UNLOAD:

			g_sLevelName = "";

			for(UINT i = 0, l = g_pLevelObjects.size(); i < l; ++i)
			{
				mem_release(g_pLevelObjects[i]);
			}
			g_pLevelObjects.clear();


			g_pUndoManager->reset();

			XUpdateWindowTitle();
			break;

		case XEventLevel::TYPE_SAVE:
			g_sLevelName = pData->szLevelName;
			g_pUndoManager->makeClean();
			{
				char szPathLevel[1024], szKey[64], szVal[1024];
				sprintf(szPathLevel, "%s%s/%s.lvl", Core_RStringGet(G_RI_STRING_PATH_GS_LEVELS), pData->szLevelName, pData->szLevelName);

				ISXConfig *pCfg = Core_OpConfig(szPathLevel);
				
				if(!pCfg->keyExists("level", "type"))
				{
					pCfg->set("level", "type", "indoor");
				}
				if(!pCfg->keyExists("level", "local_name"))
				{
					pCfg->set("level", "local_name", pData->szLevelName);
				}

				for(UINT i = 0; i < 4; ++i)
				{
					float3 vec;
					vec = g_xConfig.m_pViewportCamera[i]->getPosition();
					sprintf_s(szVal, "%f %f %f", vec.x, vec.y, vec.z);
					sprintf_s(szKey, "cam%u_pos", i);
					pCfg->set("terrax", szKey, szVal);

					SMQuaternion q = g_xConfig.m_pViewportCamera[i]->getOrientation();
					sprintf_s(szVal, "%f %f %f %f", q.x, q.y, q.z, q.w);
					sprintf_s(szKey, "cam%u_rot", i);
					pCfg->set("terrax", szKey, szVal);

					sprintf_s(szVal, "%f", g_xConfig.m_fViewportScale[i]);
					sprintf_s(szKey, "cam%u_scale", i);
					pCfg->set("terrax", szKey, szVal);

					sprintf_s(szVal, "%d", g_xConfig.m_x2DView[i]);
					sprintf_s(szKey, "cam%u_view", i);
					pCfg->set("terrax", szKey, szVal);
				}

				sprintf_s(szVal, "%d", g_xConfig.m_xViewportLayout);
				pCfg->set("terrax", "vp_layout", szVal);

				sprintf_s(szVal, "%d", g_xConfig.m_gridStep);
				pCfg->set("terrax", "grid_step", szVal);

				sprintf_s(szVal, "%d", g_xConfig.m_bShowGrid ? 1 : 0);
				pCfg->set("terrax", "grid_show", szVal);

				pCfg->save();
				mem_release(pCfg);
			}
			break;

		case XEventLevel::TYPE_LOAD_END:
			for(UINT ic = 0, il = g_pEditableSystems.size(); ic < il; ++ic)
			{
				IXEditable *pEditable = g_pEditableSystems[ic];
				for(ID i = 0, l = pEditable->getObjectCount(); i < l; ++i)
				{
					g_pLevelObjects.push_back(pEditable->getObject(i));
				}
			}
			break;
		}
	});
	
	Core_SetOutPtr();

	//SGCore_SkyBoxLoadTex("sky_2_cube.dds");
	//SGCore_SkyBoxLoadTex("sky_hdr.dds");
	//SGCore_SkyBoxLoadTex("sky_test_cube.dds");
	//SGCore_SkyCloudsLoadTex("sky_oblaka.dds");
	//SGCore_SkyBoxSetUse(false);
	//SGCore_SkyCloudsSetUse(false);

	static const float *r_default_fov = GET_PCVAR_FLOAT("r_default_fov");

	g_xConfig.m_pViewportCamera[XWP_TOP_LEFT] = SGCore_CrCamera();
	g_xConfig.m_pViewportCamera[XWP_TOP_LEFT]->setFOV(*r_default_fov);

	g_xConfig.m_pViewportCamera[XWP_TOP_RIGHT] = SGCore_CrCamera();
	g_xConfig.m_pViewportCamera[XWP_TOP_RIGHT]->setPosition(X2D_TOP_POS);
	g_xConfig.m_pViewportCamera[XWP_TOP_RIGHT]->setOrientation(X2D_TOP_ROT);

	g_xConfig.m_pViewportCamera[XWP_BOTTOM_LEFT] = SGCore_CrCamera();
	g_xConfig.m_pViewportCamera[XWP_BOTTOM_LEFT]->setPosition(X2D_SIDE_POS);
	g_xConfig.m_pViewportCamera[XWP_BOTTOM_LEFT]->setOrientation(X2D_SIDE_ROT);

	g_xConfig.m_pViewportCamera[XWP_BOTTOM_RIGHT] = SGCore_CrCamera();
	g_xConfig.m_pViewportCamera[XWP_BOTTOM_RIGHT]->setPosition(X2D_FRONT_POS);
	g_xConfig.m_pViewportCamera[XWP_BOTTOM_RIGHT]->setOrientation(X2D_FRONT_ROT);


//	SkyXEngine_RunGenPreview();
	//Core_0SetCVarInt("r_final_image", DS_RT_COLOR);
	Core_0SetCVarInt("r_final_image", DS_RT_SCENELIGHT);
	
	g_pGrid = new CGrid();
	g_pGrid->setOpacity(0.7f);
	
	g_xRenderStates.idColoredShaderVS = SGCore_ShaderLoad(SHADER_TYPE_VERTEX, "terrax_colored.vs");
	g_xRenderStates.idColoredShaderPS = SGCore_ShaderLoad(SHADER_TYPE_PIXEL, "terrax_colored.ps");
	g_xRenderStates.idColoredShaderKit = SGCore_ShaderCreateKit(g_xRenderStates.idColoredShaderVS, g_xRenderStates.idColoredShaderPS);
//	SkyXEngine_PreviewKill();
	IGXDevice *pDevice = SGCore_GetDXDevice();

	GXBlendDesc blendDesc;
	blendDesc.renderTarget[0].useBlend = true;
	blendDesc.renderTarget[0].blendSrcColor = blendDesc.renderTarget[0].blendSrcAlpha = GXBLEND_BLEND_FACTOR;
	blendDesc.renderTarget[0].blendDestColor = blendDesc.renderTarget[0].blendDestAlpha = GXBLEND_INV_BLEND_FACTOR;
	g_xRenderStates.pBlendColorFactor = pDevice->createBlendState(&blendDesc);

	blendDesc.renderTarget[0].blendSrcColor = blendDesc.renderTarget[0].blendSrcAlpha = GXBLEND_SRC_ALPHA;
	blendDesc.renderTarget[0].blendDestColor = blendDesc.renderTarget[0].blendDestAlpha = GXBLEND_INV_SRC_ALPHA;
	g_xRenderStates.pBlendAlpha = pDevice->createBlendState(&blendDesc);

	GXRasterizerDesc rsDesc; 
	rsDesc.cullMode = GXCULL_NONE;
	g_xRenderStates.pRSSolidNoCull = SGCore_GetDXDevice()->createRasterizerState(&rsDesc);

	rsDesc.fillMode = GXFILL_WIREFRAME;
	g_xRenderStates.pRSWireframe = SGCore_GetDXDevice()->createRasterizerState(&rsDesc);

	g_xRenderStates.idTexturedShaderVS = SGCore_ShaderLoad(SHADER_TYPE_VERTEX, "terrax_textured.vs");
	g_xRenderStates.idTexturedShaderPS = SGCore_ShaderLoad(SHADER_TYPE_PIXEL, "terrax_textured.ps");
	g_xRenderStates.idTexturedShaderKit = SGCore_ShaderCreateKit(g_xRenderStates.idTexturedShaderVS, g_xRenderStates.idTexturedShaderPS);

	GXVertexElement oLayout[] =
	{
		{0, 0, GXDECLTYPE_FLOAT3, GXDECLUSAGE_POSITION},
		{0, 12, GXDECLTYPE_FLOAT2, GXDECLUSAGE_TEXCOORD},
		GX_DECL_END()
	};
	IGXVertexDeclaration *pVD = pDevice->createVertexDeclaration(oLayout);
	g_pBorderVertexBuffer = pDevice->createVertexBuffer(sizeof(XBorderVertex) * 5, GXBUFFER_USAGE_STREAM);
	g_pBorderRenderBuffer = pDevice->createRenderBuffer(1, &g_pBorderVertexBuffer, pVD);
	mem_release(pVD);

	// Object handlers
	GXVertexElement oLayoutHandler[] =
	{
		{0, 0, GXDECLTYPE_FLOAT3, GXDECLUSAGE_POSITION, GXDECLSPEC_PER_VERTEX_DATA},
		{1, 0, GXDECLTYPE_FLOAT3, GXDECLUSAGE_TEXCOORD, GXDECLSPEC_PER_INSTANCE_DATA},
		GX_DECL_END()
	};
	pVD = pDevice->createVertexDeclaration(oLayoutHandler);
	g_xRenderStates.pHandlerVB = pDevice->createVertexBuffer(sizeof(float3_t) * 8, GXBUFFER_USAGE_STREAM);
	g_xRenderStates.pHandlerInstanceVB = pDevice->createVertexBuffer(sizeof(float3_t) * 2 * X_MAX_HANDLERS_PER_DIP, GXBUFFER_USAGE_STREAM);
	IGXVertexBuffer *ppVB[] = {g_xRenderStates.pHandlerVB, g_xRenderStates.pHandlerInstanceVB};
	g_xRenderStates.pHandlerRB = pDevice->createRenderBuffer(2, ppVB, pVD);
	g_xRenderStates.idHandlerShaderVS = SGCore_ShaderLoad(SHADER_TYPE_VERTEX, "terrax_handler.vs");
	g_xRenderStates.idHandlerShaderKit = SGCore_ShaderCreateKit(g_xRenderStates.idHandlerShaderVS, g_xRenderStates.idColoredShaderPS);
	g_xRenderStates.idBoundShaderKit = SGCore_ShaderCreateKit(SGCore_ShaderLoad(SHADER_TYPE_VERTEX, "terrax_bound.vs"), g_xRenderStates.idColoredShaderPS);
	USHORT pHandlerIndices[] = {0, 1, 2, 3, 4, 5, 6, 7};
	g_xRenderStates.pHandlerIB = pDevice->createIndexBuffer(sizeof(USHORT)* 8, GXBUFFER_USAGE_STATIC, GXIT_UINT16, pHandlerIndices);

	g_xRenderStates.idIconShaderKit = SGCore_ShaderCreateKit(SGCore_ShaderLoad(SHADER_TYPE_VERTEX, "terrax_icon.vs"), g_xRenderStates.idTexturedShaderPS);

	float3_t cubeData[] = {
		{-0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f, 0.5f},
		{-0.5f, 0.5f, -0.5f},
		{-0.5f, 0.5f, 0.5f},
		{0.5f, -0.5f, -0.5f},
		{0.5f, -0.5f, 0.5f},
		{0.5f, 0.5f, -0.5f},
		{0.5f, 0.5f, 0.5f}
	};
	// for(UINT i = 0; i < 8; ++i)
	// {
	// 	cubeData[i] = (float3)(cubeData[i] * 0.16f);
	// }

	GXVertexElement oLayoutHandler3D[] =
	{
		{0, 0, GXDECLTYPE_FLOAT3, GXDECLUSAGE_POSITION, GXDECLSPEC_PER_VERTEX_DATA},
		{1, 0, GXDECLTYPE_FLOAT3, GXDECLUSAGE_TEXCOORD, GXDECLSPEC_PER_INSTANCE_DATA},
		{1, 12, GXDECLTYPE_FLOAT3, GXDECLUSAGE_TEXCOORD2, GXDECLSPEC_PER_INSTANCE_DATA},
		GX_DECL_END()
	};

	mem_release(pVD);
	pVD = pDevice->createVertexDeclaration(oLayoutHandler3D);
	IGXVertexBuffer *pHandler3DVB = pDevice->createVertexBuffer(sizeof(float3_t) * 8, GXBUFFER_USAGE_STATIC, cubeData);
	IGXVertexBuffer *ppVB3D[] = {pHandler3DVB, g_xRenderStates.pHandlerInstanceVB};
	g_xRenderStates.pHandler3DRB = pDevice->createRenderBuffer(2, ppVB3D, pVD);
	mem_release(pVD);
	mem_release(pHandler3DVB);

	USHORT pHandler3DIndices[] = {0, 1, 0, 2, 0, 4, 6, 4, 6, 2, 6, 7, 5, 4, 5, 7, 5, 1, 3, 7, 3, 1, 3, 2};
	g_xRenderStates.pHandler3DIB = pDevice->createIndexBuffer(sizeof(USHORT) * 24, GXBUFFER_USAGE_STATIC, GXIT_UINT16, pHandler3DIndices);

	// Object icons
	GXVertexElement oLayoutIcon[] =
	{
		{0, 0, GXDECLTYPE_FLOAT3, GXDECLUSAGE_POSITION, GXDECLSPEC_PER_VERTEX_DATA},
		{0, 12, GXDECLTYPE_FLOAT2, GXDECLUSAGE_TEXCOORD, GXDECLSPEC_PER_VERTEX_DATA},
		{1, 0, GXDECLTYPE_FLOAT3, GXDECLUSAGE_TEXCOORD1, GXDECLSPEC_PER_INSTANCE_DATA},
		GX_DECL_END()
	};
	pVD = pDevice->createVertexDeclaration(oLayoutIcon);
	g_xRenderStates.pIconVB = pDevice->createVertexBuffer((sizeof(float3_t) + sizeof(float2_t)) * 4, GXBUFFER_USAGE_STREAM);
	IGXVertexBuffer *ppIconVB3D[] = {g_xRenderStates.pIconVB, g_xRenderStates.pHandlerInstanceVB};
	g_xRenderStates.pIcon3DRB = pDevice->createRenderBuffer(2, ppIconVB3D, pVD);
	mem_release(pVD);

	USHORT pIcon3DIndices[] = {0, 1, 2, 0, 2, 3};
	g_xRenderStates.pIcon3DIB = pDevice->createIndexBuffer(sizeof(USHORT) * 6, GXBUFFER_USAGE_STATIC, GXIT_UINT16, pIcon3DIndices);

	GXSamplerDesc samplerDesc;
	samplerDesc.addressU = samplerDesc.addressV = samplerDesc.addressW = GXTEXTURE_ADDRESS_CLAMP;
	samplerDesc.filter = GXFILTER_MIN_MAG_MIP_LINEAR;
	g_xRenderStates.pSamplerLinearClamp = pDevice->createSamplerState(&samplerDesc);

	{
		// Transform handlers
		GXVertexElement oLayoutHandler[] =
		{
			{0, 0, GXDECLTYPE_FLOAT3, GXDECLUSAGE_POSITION, GXDECLSPEC_PER_VERTEX_DATA},
			GX_DECL_END()
		};
		pVD = pDevice->createVertexDeclaration(oLayoutHandler);
		g_xRenderStates.pTransformHandlerVB = pDevice->createVertexBuffer(sizeof(float3_t)* 32, GXBUFFER_USAGE_STREAM);
		g_xRenderStates.pTransformHandlerRB = pDevice->createRenderBuffer(1, &g_xRenderStates.pTransformHandlerVB, pVD);
		USHORT pHandlerIndices[] = {
			0, 1, 2, 0, 2, 3,
			4, 5, 6, 4, 6, 7,
			8, 9, 10, 8, 10, 11,
			12, 13, 14, 12, 14, 15,

			16, 17, 18, 16, 18, 19,
			20, 21, 22, 20, 22, 23,
			24, 25, 26, 24, 26, 27,
			28, 29, 30, 28, 30, 31
		};
		g_xRenderStates.pTransformHandlerScaleIB = pDevice->createIndexBuffer(sizeof(USHORT)* 48, GXBUFFER_USAGE_STATIC, GXIT_UINT16, pHandlerIndices);
		
		USHORT pHandlerRotateIndices[] = {
			0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 7,
			8, 9, 10, 8, 10, 11, 8, 11, 12, 8, 12, 13, 8, 13, 14, 8, 14, 15,
			16, 17, 18, 16, 18, 19, 16, 19, 20, 16, 20, 21, 16, 21, 22, 16, 22, 23,
			24, 25, 26, 24, 26, 27, 24, 27, 28, 24, 28, 29, 24, 29, 30, 24, 30, 31
		};
		g_xRenderStates.pTransformHandlerRotateIB = pDevice->createIndexBuffer(sizeof(USHORT)* 72, GXBUFFER_USAGE_STATIC, GXIT_UINT16, pHandlerRotateIndices);

		float3_t pVertices[] = {
			float3_t(10000.0f, 0.0f, 0.0f), float3_t(-10000.0f, 0.0f, 0.0f),
			float3_t(0.0f, 10000.0f, 0.0f), float3_t(0.0f, -10000.0f, 0.0f),
			float3_t(0.0f, 0.0f, 10000.0f), float3_t(0.0f, 0.0f, -10000.0f)
		};
		IGXVertexBuffer *pCreateCrossVB = pDevice->createVertexBuffer(sizeof(float3_t) * 6, GXBUFFER_USAGE_STATIC, pVertices);
		g_xRenderStates.pCreateCrossRB = pDevice->createRenderBuffer(1, &pCreateCrossVB, pVD);

		mem_release(pVD);
	}

	GXDepthStencilDesc dsDesc;
	dsDesc.cmpFuncDepth = GXCMP_GREATER_EQUAL;
	g_pDSDefault = SGCore_GetDXDevice()->createDepthStencilState(&dsDesc);

	dsDesc.useDepthTest = FALSE;
	dsDesc.useDepthWrite = FALSE;
	g_pDSNoZ = SGCore_GetDXDevice()->createDepthStencilState(&dsDesc);

	XInitViewports();

	g_pMaterialBrowser->initGraphics(SGCore_GetDXDevice());

	g_pCameraConstantBuffer = SGCore_GetDXDevice()->createConstantBuffer(sizeof(SMMATRIX));

	int result = pEngine->start();

	for(UINT ic = 0, il = g_pEditableSystems.size(); ic < il; ++ic)
	{
		g_pEditableSystems[ic]->shutdown();
	}
	XReleaseViewports();

	pChannel->removeListener(&cvarListener);

	mem_release(g_pDashedMaterial);
	mem_release(g_pDSNoZ);
	mem_release(g_pDSDefault);
	mem_delete(pPipeline);
	mem_release(g_pCameraConstantBuffer);
	mem_delete(g_pGrid);
	//SkyXEngine_Kill();
	mem_release(pEngine);
	mem_delete(g_pUndoManager);
	return result;
}

void XInitViewports()
{
	IGXDevice *pContext = SGCore_GetDXDevice();
	RECT rc;
	GetClientRect(g_hTopRightWnd, &rc);
	g_pTopRightSwapChain = pContext->createSwapChain(rc.right - rc.left, rc.bottom - rc.top, g_hTopRightWnd);
	g_pTopRightDepthStencilSurface = pContext->createDepthStencilSurface(rc.right - rc.left, rc.bottom - rc.top, GXFMT_D24S8, GXMULTISAMPLE_NONE);

	GetClientRect(g_hBottomLeftWnd, &rc);
	g_pBottomLeftSwapChain = pContext->createSwapChain(rc.right - rc.left, rc.bottom - rc.top, g_hBottomLeftWnd);
	g_pBottomLeftDepthStencilSurface = pContext->createDepthStencilSurface(rc.right - rc.left, rc.bottom - rc.top, GXFMT_D24S8, GXMULTISAMPLE_NONE);

	GetClientRect(g_hBottomRightWnd, &rc);
	g_pBottomRightSwapChain = pContext->createSwapChain(rc.right - rc.left, rc.bottom - rc.top, g_hBottomRightWnd);
	g_BottomRightDepthStencilSurface = pContext->createDepthStencilSurface(rc.right - rc.left, rc.bottom - rc.top, GXFMT_D24S8, GXMULTISAMPLE_NONE);
	/*
	GetClientRect(g_pGuiWnd, &rc);
	g_pGuiSwapChain = pContext->createSwapChain(rc.right - rc.left, rc.bottom - rc.top, g_pGuiWnd);
	g_pGuiDepthStencilSurface = pContext->createDepthStencilSurface(rc.right - rc.left, rc.bottom - rc.top, GXFMT_D24S8, GXMULTISAMPLE_NONE);
	*/
}

void XReleaseViewports()
{
	mem_release(g_pTopRightSwapChain);
	mem_release(g_pBottomLeftSwapChain);
	mem_release(g_pBottomRightSwapChain);
	mem_release(g_pGuiSwapChain);
	mem_release(g_pTopRightDepthStencilSurface);
	mem_release(g_pBottomLeftDepthStencilSurface);
	mem_release(g_BottomRightDepthStencilSurface);
	mem_release(g_pGuiDepthStencilSurface);
}

void XRender3D()
{
	IGXDevice *pDevice = SGCore_GetDXDevice();
	IGXContext *pCtx = pDevice->getThreadContext();

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

		XDrawBorder(GX_COLOR_ARGB(255, 255, 255, 0), va, vb, vc, vd);
	}

	static IGXConstantBuffer *s_pColorBuffer = pDevice->createConstantBuffer(sizeof(float4));
	static IGXConstantBuffer *s_mConstW = pDevice->createConstantBuffer(sizeof(SMMATRIX));

	if(g_xState.bCreateMode)
	{
		IGXRasterizerState *pOldRS = pCtx->getRasterizerState();
		pCtx->setRasterizerState(g_xRenderStates.pRSSolidNoCull);
		pCtx->setVSConstant(s_mConstW, SCR_OBJECT);
		pCtx->setPSConstant(s_pColorBuffer);
		SGCore_ShaderBind(g_xRenderStates.idColoredShaderKit);

		pCtx->setRenderBuffer(g_xRenderStates.pCreateCrossRB);
		s_mConstW->update(&SMMatrixTranspose(SMMatrixTranslation(g_xState.vCreateOrigin)));
		s_pColorBuffer->update(&float4(0.0f, 1.0f, 0.0f, 1.0f));
		pCtx->setPrimitiveTopology(GXPT_LINELIST);
		pCtx->drawPrimitive(0, 3);
		pCtx->setPrimitiveTopology(GXPT_TRIANGLELIST);

		pCtx->setRasterizerState(pOldRS);
		mem_release(pOldRS);
	}


	// Draw handlers
	if(g_pLevelObjects.size())
	{
		IGXRasterizerState *pOldRS = pCtx->getRasterizerState();
		pCtx->setRasterizerState(g_xRenderStates.pRSSolidNoCull);

		pCtx->setPSConstant(s_pColorBuffer);

		pCtx->setPrimitiveTopology(GXPT_LINELIST);
		SGCore_ShaderBind(g_xRenderStates.idBoundShaderKit);
		//SGCore_ShaderBind(g_xRenderStates.idHandlerShaderKit);
		pCtx->setIndexBuffer(g_xRenderStates.pHandler3DIB);

		s_pColorBuffer->update(&float4(1.0f, 0.0f, 1.0f, 1.0f));

		struct BoundVertex
		{
			float3_t vPos;
			float3_t vSize;
		};

		BoundVertex *pvData;

		pCtx->setRenderBuffer(g_xRenderStates.pHandler3DRB);
		for(bool isSelected = false;; isSelected = true)
		{
			UINT uHandlerCount = 0;
			pvData = NULL;
			for(UINT i = 0, l = g_pLevelObjects.size(); i < l; ++i)
			{
				float3_t vPos = g_pLevelObjects[i]->getPos();
				//@TODO: Add visibility check
				/*if(fViewportBorders.x > vPos.x || fViewportBorders.z < vPos.x || fViewportBorders.y < vPos.z) // not visible
				{
				continue;
				}*/
				if(isSelected != g_pLevelObjects[i]->isSelected() || (!isSelected && (g_pLevelObjects[i]->hasVisualModel() || g_pLevelObjects[i]->getIcon())))
				{
					continue;
				}
				if(!pvData && !g_xRenderStates.pHandlerInstanceVB->lock((void**)&pvData, GXBL_WRITE))
				{
					break;
				}
				float3 vMin, vMax;
				g_pLevelObjects[i]->getBound(&vMin, &vMax);

				pvData[uHandlerCount++] = {(float3)((vMax + vMin) * 0.5f), (float3)(vMax - vMin)};
				if(uHandlerCount == X_MAX_HANDLERS_PER_DIP)
				{
					g_xRenderStates.pHandlerInstanceVB->unlock();
					pCtx->drawIndexedInstanced(uHandlerCount, 8, 12, 0, 0);
					pvData = NULL;
					uHandlerCount = 0;
				}
			}
			if(pvData)
			{
				g_xRenderStates.pHandlerInstanceVB->unlock();
				pvData = NULL;
			}
			if(uHandlerCount)
			{
				pCtx->drawIndexedInstanced(uHandlerCount, 8, 12, 0, 0);
			}
			if(isSelected)
			{
				break;
			}
			s_pColorBuffer->update(&float4(1.0f, 0.0f, 0.0f, 1.0f));
		}

		SGCore_ShaderUnBind();

		pCtx->setRasterizerState(pOldRS);
		mem_release(pOldRS);

		{
			struct IconVertex
			{
				float3_t vPos;
				float2_t vTex;
			};

			float3 vUp = g_xConfig.m_pViewportCamera[XWP_TOP_LEFT]->getUp() * 0.1f;
			float3 vRight = g_xConfig.m_pViewportCamera[XWP_TOP_LEFT]->getRight() * 0.1f;

			IconVertex *pvIconData;
			if(g_xRenderStates.pIconVB->lock((void**)&pvIconData, GXBL_WRITE))
			{
				pvIconData[0].vPos = float3(-vRight - vUp);
				pvIconData[0].vTex = float2_t(0.0f, 1.0f);
				pvIconData[1].vPos = float3(-vRight + vUp);
				pvIconData[1].vTex = float2_t(0.0f, 0.0f);
				pvIconData[2].vPos = float3(vRight + vUp);
				pvIconData[2].vTex = float2_t(1.0f, 0.0f);
				pvIconData[3].vPos = float3(vRight - vUp);
				pvIconData[3].vTex = float2_t(1.0f, 1.0f);
				g_xRenderStates.pIconVB->unlock();
			}


			s_pColorBuffer->update(&float4(1.0f, 1.0f, 1.0f, 1.0f));
			pCtx->setPrimitiveTopology(GXPT_TRIANGLELIST);
			SGCore_ShaderBind(g_xRenderStates.idIconShaderKit);
			pCtx->setIndexBuffer(g_xRenderStates.pIcon3DIB);
			pCtx->setRenderBuffer(g_xRenderStates.pIcon3DRB);
			pCtx->setSamplerState(g_xRenderStates.pSamplerLinearClamp, 0);

			struct Icon
			{
				IXTexture *pTexture;
				float3_t vPos;
			};
			Array<Icon> aIcons;
			Icon icon;
			for(UINT i = 0, l = g_pLevelObjects.size(); i < l; ++i)
			{
				if((icon.pTexture = g_pLevelObjects[i]->getIcon()))
				{
					icon.vPos = g_pLevelObjects[i]->getPos();
					aIcons.push_back(icon);
				}
			}
			aIcons.quickSort([](const Icon &a, const Icon &b){
				return(a.pTexture < b.pTexture);
			});

			float3_t *pvData2 = NULL;

			UINT uIconCount = 0;
			IXTexture *pTexture = aIcons.size() ? aIcons[0].pTexture : NULL;
			bool bForceDraw = false;
			for(UINT i = 0, l = aIcons.size(); i < l; ++i)
			{
				if(!pvData2)
				{
					if(g_xRenderStates.pHandlerInstanceVB->lock((void**)&pvData2, GXBL_WRITE))
					{
						IGXBaseTexture *pTex = NULL;
						aIcons[i].pTexture->getAPITexture(&pTex);
						pCtx->setPSTexture(pTex);
						mem_release(pTex);
					}
					else
					{
						break;
					}
				}

				if(pTexture == aIcons[i].pTexture)
				{
					pvData2[uIconCount++] = aIcons[i].vPos;
				}
				else
				{
					pTexture = aIcons[i].pTexture;
					bForceDraw = true;
					--i;
				}
				if(bForceDraw || uIconCount == X_MAX_HANDLERS_PER_DIP * 2)
				{
					g_xRenderStates.pHandlerInstanceVB->unlock();
					pCtx->drawIndexedInstanced(uIconCount, 8, 12, 0, 0);
					pvData2 = NULL;
					uIconCount = 0;
				}
			}
			if(pvData2)
			{
				g_xRenderStates.pHandlerInstanceVB->unlock();
				pvData2 = NULL;
			}
			if(uIconCount)
			{
				pCtx->drawIndexedInstanced(uIconCount, 8, 12, 0, 0);
			}
			pCtx->setSamplerState(NULL, 0);
		}
	}
}

void XRender2D(X_2D_VIEW view, float fScale, bool preScene)
{
	IGXDevice *pDevice = SGCore_GetDXDevice();
	IGXContext *pCtx = pDevice->getThreadContext();

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
		static IGXConstantBuffer *s_pColorBuffer = pDevice->createConstantBuffer(sizeof(float4));

		for(UINT i = 0, l = g_pLevelObjects.size(); i < l; ++i)
		{
			if(g_pLevelObjects[i]->isSelected())
			{
				g_pLevelObjects[i]->renderSelection(false);
			}
		}

		// Draw handlers
		if(g_pLevelObjects.size())
		{
			pCtx->setPSConstant(s_pColorBuffer);

			pCtx->setPrimitiveTopology(GXPT_LINELIST);
			SGCore_ShaderBind(g_xRenderStates.idHandlerShaderKit);
			pCtx->setIndexBuffer(g_xRenderStates.pHandlerIB);

			s_pColorBuffer->update(&float4(0.0f, 1.0f, 0.0f, 1.0f));

			float3_t *pvData;
			float fPtSize = 3.5f * fScale;
			if(g_xRenderStates.pHandlerVB->lock((void**)&pvData, GXBL_WRITE))
			{
				pvData[0] = float3_t(fPtSize, fPtSize, fPtSize);
				pvData[1] = (float3)(pvData[0] * -1.0f);

				pvData[2] = float3_t(fPtSize, fPtSize, -fPtSize);
				pvData[3] = (float3)(pvData[2] * -1.0f);

				pvData[4] = float3_t(fPtSize, -fPtSize, fPtSize);
				pvData[5] = (float3)(pvData[4] * -1.0f);

				pvData[6] = float3_t(-fPtSize, fPtSize, fPtSize);
				pvData[7] = (float3)(pvData[6] * -1.0f);

				g_xRenderStates.pHandlerVB->unlock();
			}
			pCtx->setRenderBuffer(g_xRenderStates.pHandlerRB);
			float4 fViewportBorders = g_xState.m_vViewportBorders[g_xState.activeWindow];
			for(bool isSelected = false;; isSelected = true)
			{
				UINT uHandlerCount = 0;
				pvData = NULL;
				for(UINT i = 0, l = g_pLevelObjects.size(); i < l; ++i)
				{
					float3_t vPos = g_pLevelObjects[i]->getPos();
					//@TODO: Add visibility check
					/*if(fViewportBorders.x > vPos.x || fViewportBorders.z < vPos.x || fViewportBorders.y < vPos.z) // not visible
					{
						continue;
					}*/
					if(isSelected != g_pLevelObjects[i]->isSelected())
					{
						continue;
					}
					if(!pvData && !g_xRenderStates.pHandlerInstanceVB->lock((void**)&pvData, GXBL_WRITE))
					{
						break;
					}

					pvData[uHandlerCount++] = vPos;
					if(uHandlerCount == X_MAX_HANDLERS_PER_DIP * 2)
					{
						g_xRenderStates.pHandlerInstanceVB->unlock();
						pCtx->drawIndexedInstanced(uHandlerCount, 8, 4, 0, 0);
						pvData = NULL;
						uHandlerCount = 0;
					}
				}
				if(pvData)
				{
					g_xRenderStates.pHandlerInstanceVB->unlock();
				}
				if(uHandlerCount)
				{
					pCtx->drawIndexedInstanced(uHandlerCount, 8, 4, 0, 0);
				}
				if(isSelected)
				{
					break;
				}
				s_pColorBuffer->update(&float4(1.0f, 0.0f, 0.0f, 1.0f));
			}

			SGCore_ShaderUnBind();
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
			XDrawBorder(GX_COLOR_ARGB(255, 255, 255, 0), va, vb, vc, vd, fScale);
		}

		static IGXConstantBuffer *s_mConstW = pDevice->createConstantBuffer(sizeof(SMMATRIX));
		if(g_xState.bHasSelection)
		{
			float3_t va, vb, vc, vd;
			float4 vBorder;
			float2 vSelectionCenter;
			switch(view)
			{
			case X2D_TOP:
				va = float3_t(g_xState.vSelectionBoundMin.x, 0.0f, g_xState.vSelectionBoundMin.z);
				vb = float3_t(g_xState.vSelectionBoundMax.x, 0.0f, g_xState.vSelectionBoundMin.z);
				vc = float3_t(g_xState.vSelectionBoundMax.x, 0.0f, g_xState.vSelectionBoundMax.z);
				vd = float3_t(g_xState.vSelectionBoundMin.x, 0.0f, g_xState.vSelectionBoundMax.z);
				vBorder = float4(g_xState.vSelectionBoundMin.x, g_xState.vSelectionBoundMin.z,
					g_xState.vSelectionBoundMax.x, g_xState.vSelectionBoundMax.z);
				vSelectionCenter = float2(g_xState.vSelectionBoundMin.x + g_xState.vSelectionBoundMax.x,
					g_xState.vSelectionBoundMin.z + g_xState.vSelectionBoundMax.z) * 0.5f;
				break;
			case X2D_FRONT:
				va = float3_t(g_xState.vSelectionBoundMin.x, g_xState.vSelectionBoundMin.y, 0.0f);
				vb = float3_t(g_xState.vSelectionBoundMax.x, g_xState.vSelectionBoundMin.y, 0.0f);
				vc = float3_t(g_xState.vSelectionBoundMax.x, g_xState.vSelectionBoundMax.y, 0.0f);
				vd = float3_t(g_xState.vSelectionBoundMin.x, g_xState.vSelectionBoundMax.y, 0.0f);
				vBorder = float4(g_xState.vSelectionBoundMin.x, g_xState.vSelectionBoundMin.y,
					g_xState.vSelectionBoundMax.x, g_xState.vSelectionBoundMax.y);
				vSelectionCenter = float2(g_xState.vSelectionBoundMin.x + g_xState.vSelectionBoundMax.x,
					g_xState.vSelectionBoundMin.y + g_xState.vSelectionBoundMax.y) * 0.5f;
				break;
			case X2D_SIDE:
				va = float3_t(0.0f, g_xState.vSelectionBoundMin.y, g_xState.vSelectionBoundMin.z);
				vb = float3_t(0.0f, g_xState.vSelectionBoundMin.y, g_xState.vSelectionBoundMax.z);
				vc = float3_t(0.0f, g_xState.vSelectionBoundMax.y, g_xState.vSelectionBoundMax.z);
				vd = float3_t(0.0f, g_xState.vSelectionBoundMax.y, g_xState.vSelectionBoundMin.z);
				vBorder = float4(g_xState.vSelectionBoundMin.z, g_xState.vSelectionBoundMin.y,
					g_xState.vSelectionBoundMax.z, g_xState.vSelectionBoundMax.y);
				vSelectionCenter = float2(g_xState.vSelectionBoundMin.z + g_xState.vSelectionBoundMax.z,
					g_xState.vSelectionBoundMin.y + g_xState.vSelectionBoundMax.y) * 0.5f;
				break;
			}
			XDrawBorder(GX_COLOR_ARGB(255, 255, 0, 0), va, vb, vc, vd, fScale);

			float3_t *pvData;
			float fPtSize = 3.0f * fScale;
			float fPtMargin = 7.0f * fScale;
			if(g_xRenderStates.pTransformHandlerVB->lock((void**)&pvData, GXBL_WRITE))
			{
				UINT uCV = 0;

				if(g_xState.xformType == X2DXF_SCALE)
				{
					float3 vCenter(vSelectionCenter.x, 0.0f, vBorder.y - fPtMargin);
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, fPtSize));

					vCenter = float3(vBorder.z + fPtMargin, 0.0f, vSelectionCenter.y);
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, fPtSize));

					vCenter = float3(vSelectionCenter.x, 0.0f, vBorder.w + fPtMargin);
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, fPtSize));

					vCenter = float3(vBorder.x - fPtMargin, 0.0f, vSelectionCenter.y);
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, fPtSize));

					vCenter = float3(vBorder.x - fPtMargin, 0.0f, vBorder.y - fPtMargin);
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, fPtSize));

					vCenter = float3(vBorder.z + fPtMargin, 0.0f, vBorder.y - fPtMargin);
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, fPtSize));

					vCenter = float3(vBorder.z + fPtMargin, 0.0f, vBorder.w + fPtMargin);
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, fPtSize));

					vCenter = float3(vBorder.x - fPtMargin, 0.0f, vBorder.w + fPtMargin);
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, fPtSize));
				}
				else if(g_xState.xformType == X2DXF_ROTATE)
				{
					float fPtSize2 = fPtSize * sqrtf(2.0f) * 0.5f;

					float3 vCenter = float3(vBorder.x - fPtMargin, 0.0f, vBorder.y - fPtMargin);
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, 0.0f));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize2, 0.0f, -fPtSize2));
					pvData[uCV++] = (float3)(vCenter + float3(0.0f, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize2, 0.0f, -fPtSize2));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, 0.0f));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize2, 0.0f, fPtSize2));
					pvData[uCV++] = (float3)(vCenter + float3(0.0f, 0.0f, fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize2, 0.0f, fPtSize2));

					vCenter = float3(vBorder.z + fPtMargin, 0.0f, vBorder.y - fPtMargin);
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, 0.0f));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize2, 0.0f, -fPtSize2));
					pvData[uCV++] = (float3)(vCenter + float3(0.0f, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize2, 0.0f, -fPtSize2));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, 0.0f));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize2, 0.0f, fPtSize2));
					pvData[uCV++] = (float3)(vCenter + float3(0.0f, 0.0f, fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize2, 0.0f, fPtSize2));

					vCenter = float3(vBorder.z + fPtMargin, 0.0f, vBorder.w + fPtMargin);
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, 0.0f));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize2, 0.0f, -fPtSize2));
					pvData[uCV++] = (float3)(vCenter + float3(0.0f, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize2, 0.0f, -fPtSize2));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, 0.0f));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize2, 0.0f, fPtSize2));
					pvData[uCV++] = (float3)(vCenter + float3(0.0f, 0.0f, fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize2, 0.0f, fPtSize2));

					vCenter = float3(vBorder.x - fPtMargin, 0.0f, vBorder.w + fPtMargin);
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize, 0.0f, 0.0f));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize2, 0.0f, -fPtSize2));
					pvData[uCV++] = (float3)(vCenter + float3(0.0f, 0.0f, -fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize2, 0.0f, -fPtSize2));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize, 0.0f, 0.0f));
					pvData[uCV++] = (float3)(vCenter + float3(fPtSize2, 0.0f, fPtSize2));
					pvData[uCV++] = (float3)(vCenter + float3(0.0f, 0.0f, fPtSize));
					pvData[uCV++] = (float3)(vCenter + float3(-fPtSize2, 0.0f, fPtSize2));
				}

				g_xRenderStates.pTransformHandlerVB->unlock();
			}

			SMMATRIX mViewProj;
			SMMATRIX mWorld;
			Core_RMatrixGet(G_RI_MATRIX_VIEWPROJ, &mViewProj);
			switch(view)
			{
			case X2D_FRONT:
				mWorld = SMMatrixRotationX(-SM_PIDIV2);
				break;
			case X2D_SIDE:
				mWorld = SMMatrixRotationY(-SM_PIDIV2) * SMMatrixRotationZ(-SM_PIDIV2);
				break;
			}
			
			s_mConstW->update(&SMMatrixTranspose(mWorld));
			pCtx->setVSConstant(s_mConstW, SCR_OBJECT);

			IGXRasterizerState *pOldRS = pCtx->getRasterizerState();
			pCtx->setRasterizerState(g_xRenderStates.pRSSolidNoCull);
			pCtx->setPrimitiveTopology(GXPT_TRIANGLELIST);
			SGCore_ShaderBind(g_xRenderStates.idColoredShaderKit);
			pCtx->setRenderBuffer(g_xRenderStates.pTransformHandlerRB);
			s_pColorBuffer->update(&float4(1.0f, 1.0f, 1.0f, 1.0f));
			pCtx->setPSConstant(s_pColorBuffer);
			if(g_xState.xformType == X2DXF_SCALE)
			{
				pCtx->setIndexBuffer(g_xRenderStates.pTransformHandlerScaleIB);
				pCtx->drawIndexed(32, 16, 0, 0);
			}
			else if(g_xState.xformType == X2DXF_ROTATE)
			{
				pCtx->setIndexBuffer(g_xRenderStates.pTransformHandlerRotateIB);
				pCtx->drawIndexed(32, 24, 0, 0);
			}


			SGCore_ShaderUnBind();
			pCtx->setRasterizerState(pOldRS);
			mem_release(pOldRS);
		}

		if(g_xState.bCreateMode)
		{
			IGXRasterizerState *pOldRS = pCtx->getRasterizerState();
			pCtx->setRasterizerState(g_xRenderStates.pRSSolidNoCull);
			pCtx->setVSConstant(s_mConstW, SCR_OBJECT);
			pCtx->setPSConstant(s_pColorBuffer);
			SGCore_ShaderBind(g_xRenderStates.idColoredShaderKit);

			pCtx->setRenderBuffer(g_xRenderStates.pCreateCrossRB);
			s_mConstW->update(&SMMatrixTranspose(SMMatrixTranslation(g_xState.vCreateOrigin)));
			s_pColorBuffer->update(&float4(0.0f, 1.0f, 0.0f, 1.0f));
			pCtx->setPrimitiveTopology(GXPT_LINELIST);
			pCtx->drawPrimitive(0, 3);
			pCtx->setPrimitiveTopology(GXPT_TRIANGLELIST);

			pCtx->setRasterizerState(pOldRS);
			mem_release(pOldRS);
		}
	}
}

void XLoadLevel(const char *szName)
{
	g_pEngine->getCore()->getConsole()->execCommand2("map %s", szName);
}

void XResetLevel()
{
	g_pEngine->getCore()->getConsole()->execCommand("endmap");
}

bool XSaveLevel(const char *szNewName, bool bForcePrompt)
{
	if(szNewName)
	{
		char szPathDirLevel[1024];
		sprintf(szPathDirLevel, "%s%s/", Core_RStringGet(G_RI_STRING_PATH_GS_LEVELS), szNewName);

		if(!FileExistsDir(szPathDirLevel))
		{
			FileCreateDir(szPathDirLevel);
		}

		XEventLevel ev;
		ev.type = XEventLevel::TYPE_SAVE;
		ev.szLevelName = szNewName;
		Core_GetIXCore()->getEventChannel<XEventLevel>(EVENT_LEVEL_GUID)->broadcastEvent(&ev);
		return(true);
	}
	
	if(!bForcePrompt && g_sLevelName.length())
	{
		// g_sLevelName can changed during save process, so pointer will be broken
		String tmp = g_sLevelName;
		return(XSaveLevel(tmp.c_str()));
	}
		
	char szName[1024];
	int iMaxLength = sizeof(szName);
	if(Tools::DlgPrompt(szName, &iMaxLength, "Level name", "Save new level"))
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

	IGXDevice *pDevice = SGCore_GetDXDevice();
	IGXContext *pCtx = pDevice->getThreadContext();

	IGXBlendState *pOldBlendState = pCtx->getBlendState();
	SGCore_ShaderBind(g_xRenderStates.idTexturedShaderKit);

	static IGXConstantBuffer *s_pColorBuffer = pDevice->createConstantBuffer(sizeof(float4));
	s_pColorBuffer->update(&GX_COLOR_COLOR_TO_F4(color));
	pCtx->setPSConstant(s_pColorBuffer);

	pCtx->setPSTexture(g_pDashedMaterial);
	pCtx->setBlendState(g_xRenderStates.pBlendAlpha);
	pCtx->setRenderBuffer(g_pBorderRenderBuffer);
	pCtx->setPrimitiveTopology(GXPT_LINESTRIP);
	pCtx->drawPrimitive(0, 4);
	SGCore_ShaderUnBind();

	pCtx->setBlendState(pOldBlendState);
	mem_release(pOldBlendState);
}

void XUpdateUndoRedo();
bool XExecCommand(IXEditorCommand *pCommand)
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
	vCamPos = g_xConfig.m_pViewportCamera[wnd]->getPosition();
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

bool XIsMouseInSelection(X_WINDOW_POS wnd)
{
	if(!g_xConfig.m_pViewportCamera[wnd] || !g_xState.bHasSelection)
	{
		return(false);
	}
	const float2_t &fMPos = g_xState.vWorldMousePos;
	float fMargin = g_xConfig.m_fViewportScale[wnd] * 5.0f;
	switch(g_xConfig.m_x2DView[wnd])
	{
	case X2D_TOP:
		return(fMPos.x >= g_xState.vSelectionBoundMin.x - fMargin && fMPos.x <= g_xState.vSelectionBoundMax.x + fMargin &&
			fMPos.y >= g_xState.vSelectionBoundMin.z - fMargin && fMPos.y <= g_xState.vSelectionBoundMax.z + fMargin);

	case X2D_FRONT:
		return(fMPos.x >= g_xState.vSelectionBoundMin.x - fMargin && fMPos.x <= g_xState.vSelectionBoundMax.x + fMargin &&
			fMPos.y >= g_xState.vSelectionBoundMin.y - fMargin && fMPos.y <= g_xState.vSelectionBoundMax.y + fMargin);

	case X2D_SIDE:
		return(fMPos.x >= g_xState.vSelectionBoundMin.z - fMargin && fMPos.x <= g_xState.vSelectionBoundMax.z + fMargin &&
			fMPos.y >= g_xState.vSelectionBoundMin.y - fMargin && fMPos.y <= g_xState.vSelectionBoundMax.y + fMargin);
	}
	return(false);
}

void XUpdateWindowTitle()
{
	const char *szLevelName = g_sLevelName.c_str();
	static char szCaption[256];
	bool isDirty = g_pUndoManager->isDirty();
	if(szLevelName && szLevelName[0])
	{
		sprintf(szCaption, "%s - [%s]%s | %s", MAIN_WINDOW_TITLE, szLevelName, isDirty ? "*" : "", SKYXENGINE_VERSION4EDITORS);
	}
	else
	{
		sprintf(szCaption, "%s%s | %s", MAIN_WINDOW_TITLE, isDirty ? " - *" : "", SKYXENGINE_VERSION4EDITORS);
	}
	PostMessageA(g_hWndMain, WM_SETTITLEASYNC, 0, (LPARAM)szCaption);
	// SetWindowText(g_hWndMain, szCaption);
}

void XExportToObj(const char *szMdl)
{
	IXCore *pCore = g_pEngine->getCore();
	IXResourceManager *pResourceManager = pCore->getResourceManager();
	IFileSystem *pFileSystem = pCore->getFileSystem();

	IXResourceModel *pResource;
	IXResourceModelStatic *pResourceStatic;
	if(!pResourceManager->getModel(szMdl, &pResource))
	{
		LibReport(REPORT_MSG_LEVEL_ERROR, "Unable to load model '%s'!\n", szMdl);
		return;
	}
	if(!(pResourceStatic = pResource->asStatic()))
	{
		LibReport(REPORT_MSG_LEVEL_ERROR, "Model '%s' is not a static model. Cannot export!\n", szMdl);
		mem_release(pResource);
		return;
	}

	const char *szBasename = basename(szMdl);
	char buf[128];
	
	sprintf(buf, "export/%s.mtl", szBasename);
	IFile *pMatFile = pFileSystem->openFile(buf, FILE_MODE_WRITE);

	sprintf(buf, "export/%s.obj", szBasename);
	IFile *pObjFile = pFileSystem->openFile(buf, FILE_MODE_WRITE);
	

	pObjFile->writeText("# File was written by " SKYXENGINE_VERSION4EDITORS "\n# Original model: %s\n\nmtllib %s.mtl\no model\n", szMdl, szBasename);

	UINT uSubsets = pResourceStatic->getSubsetCount(0);
	for(UINT i = 0; i < uSubsets; ++i)
	{
		auto *pSubset = pResourceStatic->getSubset(0, i);
		pObjFile->writeText("\n# Subset %u\n", i);
		for(UINT j = 0; j < pSubset->iVertexCount; ++j)
		{
			auto &v = pSubset->pVertices[j];

			pObjFile->writeText("v %f %f %f\nvt %f %f\nvn %f %f %f\n", 
				v.vPos.x, v.vPos.y, v.vPos.z,
				v.vTex.x, v.vTex.y,
				v.vNorm.x, v.vNorm.y, v.vNorm.z
				);
		}
	}
	// XPT_TRIANGLELIST
	//XPT_TRIANGLESTRIP
	UINT uFaceOffset = 1;
	XPT_TOPOLOGY topology = pResourceStatic->getPrimitiveTopology();
	for(UINT i = 0; i < uSubsets; ++i)
	{
		auto *pSubset = pResourceStatic->getSubset(0, i);
		pObjFile->writeText("\n# Subset %u\ng subset_%u\nusemtl mtl_%u\ns off\n", i, i, pSubset->iMaterialID);
		
		if(topology == XPT_TRIANGLELIST)
		{
			for(UINT j = 0; j < pSubset->iIndexCount; j += 3)
			{
				UINT a = pSubset->pIndices[j] + uFaceOffset;
				UINT b = pSubset->pIndices[j + 1] + uFaceOffset;
				UINT c = pSubset->pIndices[j + 2] + uFaceOffset;
				pObjFile->writeText("f %u/%u/%u %u/%u/%u %u/%u/%u\n",
					a, a, a,
					b, b, b,
					c, c, c
					);
			}
		}
		else if(topology == XPT_TRIANGLESTRIP)
		{
			for(UINT j = 0; j < pSubset->iIndexCount - 2; ++j)
			{
				UINT a = pSubset->pIndices[j] + uFaceOffset;
				UINT b = pSubset->pIndices[j + 1] + uFaceOffset;
				UINT c = pSubset->pIndices[j + 2] + uFaceOffset;
				pObjFile->writeText("f %u/%u/%u %u/%u/%u %u/%u/%u\n",
					a, a, a,
					b, b, b,
					c, c, c
					);
			}
		}
		else
		{
			assert(!"Unknown topology!");
		}

		uFaceOffset += pSubset->iVertexCount;
	}

	UINT uMatCount = pResourceStatic->getMaterialCount();
	for(UINT i = 0; i < uMatCount; ++i)
	{
		const char *szMtl = pResourceStatic->getMaterial(i);

		pMatFile->writeText("newmtl mtl_%u\n", i);

		if(szMtl)
		{
			pMatFile->writeText("  map_Kd %s.dds\n", szMtl);
		}

		pMatFile->writeText("\n");
	}

	mem_release(pMatFile);
	mem_release(pObjFile);
	mem_release(pResource);

	LibReport(REPORT_MSG_LEVEL_NOTICE, "%s was written\n", buf);
}

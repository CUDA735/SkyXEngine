
// "/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'" 
#include <gcore/sxgcore.h>

#define MAIN_WINDOW_CLASS         "X Main Window"
#define RENDER_WINDOW_CLASS		  "X Viewport Window"
#define WIDTH_ADJUST			2

#define	WINDOW_WIDTH			800
#define	WINDOW_HEIGHT			600

#define	SPLITTER_BAR_WIDTH		2

#define MARGIN_TOP              30
#define MARGIN_BOTTOM           22
#define MARGIN_LEFT             50
#define MARGIN_RIGHT            150
#define AB_BUTTON_HEIGHT        40
#define OBJECT_TREE_HEIGHT      300

#include "Grid.h"

enum X_VIEWPORT_LAYOUT
{
	XVIEW_2X2,
	XVIEW_1X2,
	XVIEW_2X1,
	XVIEW_3DONLY
};

extern HWND g_hTopRightWnd;
extern HWND g_hTopLeftWnd;
extern HWND g_hBottomRightWnd;
extern HWND g_hBottomLeftWnd;

enum X_2D_VIEW
{
	X2D_TOP,
	X2D_FRONT,
	X2D_SIDE
};

struct CTerraXConfig
{
	X_2D_VIEW m_x2DTopRightView = X2D_TOP;;
	X_2D_VIEW m_x2DBottomLeftView = X2D_SIDE;
	X_2D_VIEW m_x2DBottomRightView = X2D_FRONT;

	float m_fTopRightScale = 1.0f;
	float m_fBottomLeftScale = 1.0f;
	float m_fBottomRightScale = 1.0f;

	ICamera *m_pTopRightCamera = NULL;
	ICamera *m_pBottomLeftCamera = NULL;
	ICamera *m_pBottomRightCamera = NULL;

	GRID_STEP m_gridStep = GRID_STEP_1M;
	bool m_bShowGrid = true;
	bool m_bSnapGrid = true;
	bool m_bDottedGrid = false;
	float m_fGridOpacity = 0.5f;

	X_VIEWPORT_LAYOUT m_xViewportLayout = XVIEW_2X2;
};

extern CTerraXConfig g_xConfig;

#define X2D_TOP_POS float3(0.0f, 1000.0f, 0.0f)
#define X2D_TOP_ROT SMQuaternion(-SM_PIDIV2, 'x')
#define X2D_FRONT_POS float3(0.0f, 0.0f, 1000.0f)
#define X2D_FRONT_ROT SMQuaternion(-SM_PI, 'y')
#define X2D_SIDE_POS float3(1000.0f, 0.0f, 0.0f)
#define X2D_SIDE_ROT SMQuaternion(SM_PIDIV2, 'y')

extern BOOL g_is3DRotating;
extern BOOL g_is3DPanning;

void XRender2D(X_2D_VIEW view, float fScale);

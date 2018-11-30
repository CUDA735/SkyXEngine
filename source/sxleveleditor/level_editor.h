
#ifndef __LEVEL_EDITOR_H
#define __LEVEL_EDITOR_H

/*
��� ������ ����� ������������ � pListBoxList, 
����������� ���������, ��������������  ����� ����� �� �������������� ��� ��� ������� � ������ (������� ������� ������ ����� ������� �������������)
������� ������� ������ ���� id � �������� ��������� ������, �� ���� ����� ������� id �������, ���� ������� �������� ������ pListBoxList
*/

#define SX_LE_MMENU_WEATHER_BEGIN_ID 50001

#define MAINWIN_SIZE_X	820
#define MAINWIN_SIZE_Y	690

#define SX_LEVEL_EDITOR_NAME "LevelEditor"

#include <common/string.h>
#include <common/array.h>

#include <sxguiwinapi/sxgui.h>
#include <geom/sxgeom.h>
#include <game/sxgame.h>
#include <render/sxrender.h>
#include <aigrid/sxaigrid.h>
#include <level/sxlevel.h>
#include <input/sxinput.h>
#include <sxleveleditor/resource.h>

#include <editors_utils/axes_helper.h>

#include "aigrid_callback.h"
#include "game_callback.h"
#include "green_callback.h"
#include "model_callback.h"
#include "common_callback.h"

//##########################################################################

//! ���������� ��� ��������� ������ ������ � ������� ������
bool HandlerGetPreviewLevel(const char *szPath, char *szBuff);

//##########################################################################

namespace level_editor
{
	extern ISXGUIBaseWnd *pJobWindow;
	extern ISXGUIMenuWindow *pMainMenu;
	extern ISXGUIBaseWnd *pRenderWindow;

	extern ISXGUIToolBar *pToolBar1;
	extern ISXGUIButton *pButtonTBNew;
	extern ISXGUIButton *pButtonTBOpen;
	extern ISXGUIButton *pButtonTBSave;
	extern ISXGUIButton *pButtonTBSaveAs;

	extern ISXGUICheckBox *pCheckBoxTBArrow;
	extern ISXGUICheckBox *pCheckBoxTBPos;
	extern ISXGUICheckBox *pCheckBoxTBRot;
	extern ISXGUICheckBox *pCheckBoxTBScale;

	extern ISXGUICheckBox *pCheckBoxTBGrid;
	extern ISXGUICheckBox *pCheckBoxTBAxes;

	extern ISXGUICheckBox *pCheckBoxTBRColor;
	extern ISXGUICheckBox *pCheckBoxTBRNormal;
	extern ISXGUICheckBox *pCheckBoxTBRParam;
	extern ISXGUICheckBox *pCheckBoxTBRAmDiff;
	extern ISXGUICheckBox *pCheckBoxTBRSpecular;
	extern ISXGUICheckBox *pCheckBoxTBRLighting;

	extern ISXGUICheckBox *pCheckBoxTBSelS;
	extern ISXGUICheckBox *pCheckBoxTBSelZTest;
	extern ISXGUICheckBox *pCheckBoxTBSelMesh;
	extern ISXGUICheckBox *pCheckBoxTBSelCullBack;

	extern ISXGUICheckBox *pCheckBoxTBAIGBound;
	extern ISXGUICheckBox *pCheckBoxTBAIGQuad;
	extern ISXGUICheckBox *pCheckBoxTBAIGGraphPoint;

	extern ISXGUICheckBox *pCheckBoxTBLevelType;
	extern ISXGUICheckBox *pCheckBoxTBGLightEnable;

	extern ISXGUIGroupBox *pGroupBoxList;
	extern ISXGUIGroupBox *pGroupBoxData;
	extern ISXGUIListBox *pListBoxList;
	extern ISXGUIStatic *pStaticListTextCount;
	extern ISXGUIStatic *pStaticListValCount;

	extern ISXGUIButton *pButtonDelete;

	extern ISXGUIButton *pButtonGeometryOpen;
	extern ISXGUIButton *pButtonGreenOpen;
	extern ISXGUIButton *pButtonGameObjectOpen;
	extern ISXGUIButton *pButtonAIGridOpen;


	//model
	//{{
	extern ISXGUIStatic *pStaticGeomName;
	extern ISXGUIEdit *pEditGeomName;

	extern ISXGUIStatic *pStaticGeomModel;
	extern ISXGUIEdit *pEditGeomModel;
	extern ISXGUIButton *pButtonGeomModel;

	extern ISXGUIStatic *pStaticGeomLod1;
	extern ISXGUIEdit *pEditGeomLod1;
	extern ISXGUIButton *pButtonGeomLod1;

	extern ISXGUIStatic *pStaticGeomPhysics;
	extern ISXGUIEdit *pEditGeomPhysics;
	extern ISXGUIButton *pButtonGeomPhysics;

	extern ISXGUICheckBox *pCheckBoxSegmentation;
	
	extern ISXGUIStatic *pStaticGeomPos;
	extern ISXGUIEdit *pEditGeomPosX;
	extern ISXGUIEdit *pEditGeomPosY;
	extern ISXGUIEdit *pEditGeomPosZ;
	extern ISXGUIRadioButton *pRadioButtonGeomPosX;
	extern ISXGUIRadioButton *pRadioButtonGeomPosY;
	extern ISXGUIRadioButton *pRadioButtonGeomPosZ;
	extern ISXGUIStatic *pStaticGeomRot;
	extern ISXGUIEdit *pEditGeomRotX;
	extern ISXGUIEdit *pEditGeomRotY;
	extern ISXGUIEdit *pEditGeomRotZ;
	extern ISXGUIRadioButton *pRadioButtonGeomRotX;
	extern ISXGUIRadioButton *pRadioButtonGeomRotY;
	extern ISXGUIRadioButton *pRadioButtonGeomRotZ;
	extern ISXGUIStatic *pStaticGeomScale;
	extern ISXGUIEdit *pEditGeomScaleX;
	extern ISXGUIEdit *pEditGeomScaleY;
	extern ISXGUIEdit *pEditGeomScaleZ;
	extern ISXGUIRadioButton *pRadioButtonGeomScaleX;
	extern ISXGUIRadioButton *pRadioButtonGeomScaleY;
	extern ISXGUIRadioButton *pRadioButtonGeomScaleZ;
	extern ISXGUIButton *pButtonGeomFinish;
	//}}

	//Green
	//{{
	extern ISXGUIStatic *pStaticGreenName;
	extern ISXGUIEdit *pEditGreenName;

	extern ISXGUIStatic *pStaticGreenModel;
	extern ISXGUIEdit *pEditGreenModel;
	extern ISXGUIButton *pButtonGreenModel;

	extern ISXGUIStatic *pStaticGreenLod1;
	extern ISXGUIEdit *pEditGreenLod1;
	extern ISXGUIButton *pButtonGreenLod1;

	extern ISXGUIStatic *pStaticGreenLod2;
	extern ISXGUIEdit *pEditGreenLod2;
	extern ISXGUIButton *pButtonGreenLod2;

	extern ISXGUIStatic *pStaticGreenMask;
	extern ISXGUIEdit *pEditGreenMask;
	extern ISXGUIButton *pButtonGreenMask;

	extern ISXGUICheckBox *pCheckBoxGreenAveragedRGB;
	
	extern ISXGUIStatic *pStaticGreenNav;
	extern ISXGUIEdit *pEditGreenNav;
	extern ISXGUIButton *pButtonGreenNav;

	extern ISXGUITrackBar *pTrackBarGreenDensity;
	extern ISXGUIButton *pButtonGreenGenerate;
	extern ISXGUIStatic *pStaticGreenDensityText;
	extern ISXGUIStatic *pStaticGreenDensityVal;

	extern ISXGUIEdit *pEditGreenSelX;
	extern ISXGUIEdit *pEditGreenSelY;
	extern ISXGUIEdit *pEditGreenSelZ;
	extern ISXGUIRadioButton *pRadioButtonGreenSelX;
	extern ISXGUIRadioButton *pRadioButtonGreenSelY;
	extern ISXGUIRadioButton *pRadioButtonGreenSelZ;
	extern ISXGUIComboBox *pComboBoxGreenSel;
	extern ISXGUIStatic *pStaticGreenSelX;
	extern ISXGUIStatic *pStaticGreenSelY;
	extern ISXGUIStatic *pStaticGreenSelZ;
	//}}

	//game object
	//{
	extern ISXGUIStatic *pStaticGameClass;
	extern ISXGUIComboBox *pComboBoxGameClass;
	extern ISXGUIButton *pButtonGameTab;

	//! ������� �������� ������ ������� ��������, 0 - ���������, 1 - ����������
	extern int GameTabVal;

	extern ISXGUIListView *pListViewGameClass;
	extern ISXGUIComboBox *pComboBoxGameValue;
	extern ISXGUIEdit *pEditGameValue;
	extern ISXGUIButton *pButtonGameValue;
	extern ISXGUIStatic *pStaticGameHelp;
	extern ISXGUIMemo *pMemoGameHelp;
	extern ISXGUIButton *pButtonGameCreate;

	extern ISXGUICheckBox *pCheckBoxGameFlags[16];
	extern const char *aGameObjectFlags[16];

	extern ISXGUIListView *pListViewGameConnections;
	extern ISXGUIStatic *pStaticGameConnectionsEvent;
	extern ISXGUIComboBox *pComboBoxGameConnectionsEvent;
	extern ISXGUIStatic *pStaticGameConnectionsName;
	extern ISXGUIEdit *pEditGameConnectionsName;
	extern ISXGUIStatic *pStaticGameConnectionsAction;
	extern ISXGUIComboBox *pComboBoxGameConnectionsAction;
	extern ISXGUIStatic *pStaticGameConnectionsDelay;
	extern ISXGUIEdit *pEditGameConnectionsDelay;
	extern ISXGUIStatic *pStaticGameConnectionsParameter;
	extern ISXGUIEdit *pEditGameConnectionsParameter;
	extern ISXGUIButton *pButtonGameConnectionsCreate;
	extern ISXGUIButton *pButtonGameConnectionsDelete;
	//}

	//aigrid
	//{
	extern ISXGUIButton *pButtonAIQuadsDelSel;
	extern ISXGUIButton *pButtonAIGridGen;
	extern ISXGUIButton *pButtonAIGridClear;
	extern ISXGUIButton *pButtonAIClearAll;
	extern ISXGUIStatic *pStaticAIBBDimensions;
	extern ISXGUIStatic *pStaticAIBBDimensionsWidth;
	extern ISXGUIEdit *pEditAIBBDimensionsWidth;
	extern ISXGUIStatic *pStaticAIBBDimensionsHeight;
	extern ISXGUIEdit *pEditAIBBDimensionsHeight;
	extern ISXGUIStatic *pStaticAIBBDimensionsDepth;
	extern ISXGUIEdit *pEditAIBBDimensionsDepth;
	extern ISXGUIStatic *pStaticAIBBPos;
	extern ISXGUIStatic *pStaticAIBBPosX;
	extern ISXGUIEdit *pEditAIBBPosX;
	extern ISXGUIStatic *pStaticAIBBPosY;
	extern ISXGUIEdit *pEditAIBBPosY;
	extern ISXGUIStatic *pStaticAIBBPosZ;
	extern ISXGUIEdit *pEditAIBBPosZ;
	extern ISXGUIButton *pButtonAIBBFinish;
	extern ISXGUIButton *pButtonAIGPGen;
	extern ISXGUIButton *pButtonAIGPClear;
	extern ISXGUIRadioButton *pRadioButtonAIGPAdd;
	extern ISXGUIRadioButton *pRadioButtonAIGPDel;
	extern ISXGUIRadioButton *pRadioButtonAIQuadAdd;
	extern ISXGUIRadioButton *pRadioButtonAIQuadsMSel;
	extern ISXGUIRadioButton *pRadioButtonAIQuadsSelDel;
	extern ISXGUIButton *pButtonAIGridValidation;
	extern ISXGUICheckBox *pCheckBoxAIGridMarkedSplits;
	extern ISXGUIStatic *pStaticAIStatistics;
	extern ISXGUIStatic *pStaticAIStatsCountQuads;
	extern ISXGUIStatic *pStaticAIStatsCountGP;
	extern ISXGUIStatic *pStaticAIStatsCountSplits;
	extern ISXGUIEdit *pEditAIStatsCountQuads;
	extern ISXGUIEdit *pEditAIStatsCountGP;
	extern ISXGUIEdit *pEditAIStatsCountSplits;
	//}

	extern ISXGUIStatusBar *pStatusBar1;

	//######################################################################

	//! ���� �� ������ �� �������������� ����
	bool existsFileStaticGeom(const char *szRelPath);

	//**********************************************************************

	//! ������������� ���� ��������� ����������
	void InitAllElements();

	//! �������� ���� ��������� ����������
	void DeleteAllElements();

	//**********************************************************************

	//! ���������� ������ � ��������� �������
	void LevelEditorUpdate(DWORD timeDelta);

	//! �������� ��������� ������ ��� ���������
	void LEcreateRenderData();

	//! �������� ��������� ������ ���������
	void LEdeleteRenderData();

	void NullingButtonSelTransform();

	//**********************************************************************

	//! ������� ����� ������� (������� ��� ��� ����), useMessage - �������� �� ��������� ���� ���� ����������� �������
	void LevelNew(bool useMessage = true);
	
	//! ������� ������ ������ �������, ���� ����� ������ ������� �� ������� �������
	void LevelOpen();

	//! ��������� �������
	void LevelSave();

	//! ��������� ������� ���
	void LevelSaveAs();

	//**********************************************************************

	//! ������� ������� � ��������� ���� ����� "��������� �����������"
	void FinalImageUncheckedMenu();

	//! ��������� �������� ����������� � ����������� ���������, iSelect - �������� �������
	void FillListBoxGeom(int iSelect=-1);

	void FillListBoxGreen(int iSelect = -1);

	void FillListBoxAIgrid();

	void FillListBoxGameObj(int iSelect = -1);
	
	//**********************************************************************

	void GeomActivateAll(bool bf);
	void GeomActivateCreate(bool bf);
	void GeomActivateTrans(bool bf);
	void GeomSel(int sel);

	//! ��������� ������������ ��� ����������� ���� ��� ����������� ���������
	void GeomTraceSelect();

	void GeomTraceSetPos();

	void GeomTraceCreate();
	
	//! ���������� ��������� ������� �����������
	void GeomUpdateCopyPos();

	//! ����������� ������
	void GeomCopy();

	//! ������������� ������� �� ������ �������
	void GeomTransformByHelper();

	void GeomDelete(int iSelected);

	//**********************************************************************

	void GreenActivateAll(bool bf);
	void GreenActivateMain(bool bf);
	void GreenActivateCreate(bool bf);
	void GreenActivateEdit(bool bf);
	void GreenSel(int iSelect);

	//! ��������� ������������ ��� ����������� ���� ��� ��������������
	void GreenTraceSelect();

	void GreenTraceSetPos();

	//! ������������� �������������� �� ������ �������
	void GreenTransformByHelper();

	void GreenSetPos4Box();

	void GreenDelete(int iSelected);

	//**********************************************************************

	/*! ������������ ��� �������� ���������� ������ � �������� ���������
	 \note ������ ��������� ���������� ���������� ��� ����� ��������
	*/
	void GameVisible4Properties(bool bf);

	//! ��������� ��������� ������� ����������
	void GameVisible4Connections(bool bf);

	//! ��������� �������� ������� �� ������ �� ������ listbox
	void GameSel(int iSelect);

	//! ����������� ���� � ��������� ������� � ����� �����������
	void GameTraceSetPos();

	//! ����������� ���� � �������� � ����� �����������
	void GameTraceCreate();

	//! ����� ������� �� ����� ��� ����������
	CBaseEntity* GameGetObj4Connect(CBaseEntity* pEntity, const char *szName);

	//! ������ ��������� � ������ ���� �� ������ ������� ������ �� ����� (��� #GameGetObj4Connect)
	void GameMessageNotFoundName(const char *szName);

	//! �������� ������� ��� �������� � ������� ���������
	void GameUpdatePosRot();

	//! ��������� ��������� ������� �������
	void GameVisibleProperties(bool bf);

	//! ������������� ������� �������� �� ������ �������
	void GameTransformByHelper();

	//! ������� ������� ������ �� ������ � ������
	void GameDelete(int iSelected);

	//**********************************************************************

	void AIGridActivateAll(bool bf);
	void AIGridEnableBB(bool bf);

	//! ��������� ������������ ��� ����������� ���� ��� �� �����
	void AIGridTraceSelect();

	void AIGridMultiSelect();

	//######################################################################

	/*! \name ���
	@{*/

	//! ��������� ����� ���� (������� �����������)
	extern float3 vRayOrigin;

	//! ����������� ����
	extern float3 vRayDir;

	//! ������ ����������� ���� (����������� �����������)
	extern float3 vRayDirDirect;

	//! ������� ���� ������������� ���� �������
	extern POINT oPointMouse;

	//!@}

	//**********************************************************************

	/*! \name ����������� ���������
	@{*/

	//! ������������ �� �����������
	extern bool useCopyData;

	//! id �������� ��������, ������� ���� �����������
	extern ID idCopy;

	//! ��������� ������� ����� (��� ���������� �����������)
	extern float3 vCopyPos;

	//!@}

	//**********************************************************************

	extern ID3DXMesh *pFigureBox;

	//! ������ ������� �������������
	extern CAxesHelper *pAxesHelper;	


	/*extern float3 vHelperPos;
	extern float3 vHelperRot;
	extern float3 vHelperScale;*/

	//**********************************************************************

	extern int iActiveGroupType;		//!< ������� ���������� ������ ������� ��������� EDITORS_LEVEL_GROUPTYPE_
	extern ID idActiveGreenSplit;		//!< ������� ������������� ������ �������������� (���� �������� ��������������)
	extern ID idActiveGreenObject;		//!< ������� ������������� ������� �������������� (���� �������� ��������������)

	extern ID idActiveElement;			//!< ������� ������������� ����������� �������� �� ������ listbox

	//**********************************************************************

	extern bool canSelSelection;		//!< ��������� �� ���������?
	extern bool canSelZTest;			//!< ������������ �� z-test ��� ���������?
	extern bool canSelMesh;				//!< �������� ������ (true) ��� ������� ������ ��������� (false)?
	extern bool canSelBackFacesCull;	//!< �������� �� ������ ����� ��� ���������?

	//**********************************************************************

	extern bool canAIGBound;			//!< ��������� ������ ai �����
	extern bool canAIGQuad;				//!< ��������� ������ ai �����
	extern bool canAIGGraphPoint;		//!< ��������� ����������� ai �����

	//**********************************************************************

	//bound box ��� ��������� �������� �������� ��������������
	extern bool canGreenRenderBox;		//!< ��������� �� �������� ����?
	extern float3 vGreenBoxPos;			//!< ������� �����
	extern float3_t vGreenBoxWHD;		//!< ������, ������, ����� �����

	//**********************************************************************

	/*! ���������� (true) ���� �������� ������ (false) ���������� ��� �������� ������� 
	 \note ��� ���������� ��� ������ � ���������� ������������ � ����� ���������, ��� �������� ��������� ������������ �� ������� � �� ����� �������� ��������
	*/
	extern bool isAddGameConections;

	extern ID idMtl;
	extern ID idMenuWeatherCurr;
	extern int iMenuWeatherCount;
	extern Array<String> aMenuWeather;
};

#endif

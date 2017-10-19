
#include "particles_editor.h"

namespace SXParticlesEditor
{
	ISXGUIBaseWnd* JobWindow;
	ISXGUIMenu* MainMenu;
	ISXGUIStatusBar* StatusBar1;
	ISXGUIGroupBox* GroupBoxList;
	ISXGUIGroupBox* GroupBoxTabs;
	ISXGUIGroupBox* GroupBoxData;
	ISXGUIGroupBox* GroupBoxData2;
	ISXGUIBaseWnd* WindowRender;

	ISXGUIToolBar* ToolBar1;

	ISXGUIButton* ButtonTBReOpen;
	ISXGUIButton* ButtonTBSave;
	ISXGUICheckBox* CheckBoxTBGrid;
	ISXGUICheckBox* CheckBoxTBAxes;
	ISXGUICheckBox* CheckBoxTBBound;
	ISXGUICheckBox* CheckBoxTBPlay;
	ISXGUICheckBox* CheckBoxTBPause;
	ISXGUICheckBox* CheckBoxTBStop;

	ISXGUIListBox* ListBoxEffects;
	ISXGUIListBox* ListBoxEmitters;
	ISXGUIStatic* StaticEffects;
	ISXGUIButton* ButtonEffectsCreate;
	ISXGUIStatic* StaticEmitters;
	//ISXGUIButton* ButtonEffectsEdit;
	ISXGUIButton* ButtonEffectsDelete;
	ISXGUIButton* ButtonEmittersCreate;
	ISXGUIButton* ButtonEmittersBasis;
	ISXGUIButton* ButtonEmittersDelete;

	ISXGUIRadioButton* ButtonBase;
	ISXGUIRadioButton* ButtonTextureAnimTex;
	ISXGUIRadioButton* ButtonSpawn;
	ISXGUIRadioButton* ButtonBound;
	ISXGUIRadioButton* ButtonCharacters;
	ISXGUIRadioButton* ButtonVelocityAcceleration;
	ISXGUIStatic* StaticEffectsCount;
	ISXGUIStatic* StaticEmittersCount;

	//effect
	//{
	ISXGUIStatic* StaticEffName;
	ISXGUIEdit* EditEffName;
	ISXGUIButton* ButtonEffCreate;
	//}

	//base
	//{
	ISXGUIStatic* StaticName;
	ISXGUIEdit* EditName;
	ISXGUIButton* ButtonEmitterCreate;
	ISXGUIStatic* StaticReCreateCount;
	ISXGUIEdit* EditReCreateCount;
	ISXGUIStatic* StaticCount;
	ISXGUIEdit* EditCount;
	ISXGUIStatic* StaticColorCoef;
	ISXGUIEdit* EditColorCoef;
	ISXGUIStatic* StaticSoftCoef;
	ISXGUIEdit* EditSoftCoef;
	ISXGUIStatic* StaticRefractionCoef;
	ISXGUIEdit* EditRefractionCoef;
	ISXGUIStatic* StaticTransparencyCoef;
	ISXGUIEdit* EditTransparencyCoef;
	ISXGUICheckBox* CheckBoxLighting;
	ISXGUIStatic* StaticFigureType;
	ISXGUIComboBox* ComboBoxFigureType;
	ISXGUIStatic* StaticFigureCountQuads;
	ISXGUIEdit* EditFigureCountQuads;
	ISXGUICheckBox* CheckBoxFigureRotRand;
	ISXGUICheckBox* CheckBoxFigureTapX;
	ISXGUICheckBox* CheckBoxFigureTapY;
	ISXGUICheckBox* CheckBoxFigureTapZ;
	ISXGUIStatic* StaticAlphaBlendType;
	ISXGUIComboBox* ComboBoxAlphaBlendType;

	ISXGUIStatic* StaticColor;
	ISXGUIStatic* StaticColorR;
	ISXGUIEdit* EditColorR;
	ISXGUIStatic* StaticColorG;
	ISXGUIEdit* EditColorG;
	ISXGUIStatic* StaticColorB;
	ISXGUIEdit* EditColorB;
	ISXGUIStatic* StaticColorA;
	ISXGUIEdit* EditColorA;

	ISXGUIStatic* StaticTimeLife;
	ISXGUIEdit* EditTimeLife;
	ISXGUIStatic* StaticTimeLifeDisp;
	ISXGUIEdit* EditTimeLifeDisp;
	ISXGUIStatic* StaticAlphaAgeDepend;
	ISXGUIComboBox* ComboBoxAlphaDependAge;
	ISXGUIStatic* StaticSize;
	ISXGUIStatic* StaticSizeX;
	ISXGUIEdit* EditSizeX;
	ISXGUIStatic* StaticSizeY;
	ISXGUIEdit* EditSizeY;
	ISXGUIStatic* StaticSizeDisp;
	ISXGUIEdit* EditSizeDisp;
	ISXGUIStatic* StaticSizeDependAge;
	ISXGUIComboBox* ComboBoxSizeDependAge;
	ISXGUICheckBox* CheckBoxCollisionDelete;

	ISXGUICheckBox* CheckBoxTrack;
	ISXGUIStatic* StaticTrackSize;
	ISXGUIEdit* EditTrackSize;
	ISXGUIStatic* StaticTrackTime;
	ISXGUIEdit* EditTrackTime;

	//}

	//bound
	//{
	ISXGUIStatic* StaticBoundType;
	ISXGUIComboBox* ComboBoxBoundType;
	ISXGUIStatic* StaticBoundVec1;
	ISXGUIStatic* StaticBoundVec1X;
	ISXGUIEdit* EditBoundVec1X;
	ISXGUIStatic* StaticBoundVec1Y;
	ISXGUIEdit* EditBoundVec1Y;
	ISXGUIStatic* StaticBoundVec1Z;
	ISXGUIEdit* EditBoundVec1Z;
	ISXGUIStatic* StaticBoundVec1W;
	ISXGUIEdit* EditBoundVec1W;
	ISXGUIStatic* StaticBoundVec2;
	ISXGUIStatic* StaticBoundVec2X;
	ISXGUIEdit* EditBoundVec2X;
	ISXGUIStatic* StaticBoundVec2Y;
	ISXGUIEdit* EditBoundVec2Y;
	ISXGUIStatic* StaticBoundVec2Z;
	ISXGUIEdit* EditBoundVec2Z;
	ISXGUIStatic* StaticBoundVec2W;
	ISXGUIEdit* EditBoundVec2W;
	//}

	//character
	//{
	ISXGUICheckBox* CheckBoxCircle;
	ISXGUIStatic* StaticCircleAxis;
	ISXGUIComboBox* ComboBoxCircleAxis;
	ISXGUIStatic* StaticCircleAngle;
	ISXGUIEdit* EditCircleAngle;
	ISXGUIStatic* StaticCircleAngleDisp;
	ISXGUIEdit* EditCircleAngleDisp;
	ISXGUICheckBox* CheckBoxCircleAngleDispNeg;
	ISXGUICheckBox* CheckBoxRotate;
	ISXGUIStatic* StaticRotateAngle;
	ISXGUIEdit* EditRotateAngle;
	ISXGUIStatic* StaticRotateAngleDisp;
	ISXGUIEdit* EditRotateAngleDisp;
	ISXGUICheckBox* CheckBoxRotateAngleDispNeg;
	ISXGUICheckBox* CheckBoxDeviation;
	ISXGUIStatic* StaticDeviationType;
	ISXGUIComboBox* ComboBoxDeviationType;
	ISXGUIStatic* StaticDeviationAmplitude;
	ISXGUIStatic* StaticDeviationCoefAngle;
	ISXGUIEdit* EditDeviationAmplitude;
	ISXGUIEdit* EditDeviationCoefAngle;
	ISXGUIStatic* StaticDeviationAxis;
	ISXGUIComboBox* ComboBoxDeviationAxis;
	ISXGUIStatic* StaticDeviationCountDelayMls;
	ISXGUIEdit* EditDeviationCountDelayMls;
	ISXGUIStatic* StaticDeviationCoefAngleDisp;
	ISXGUIEdit* EditDeviationCoefAngleDisp;
	ISXGUICheckBox* CheckBoxDeviationCoefAngleDispNeg;
	ISXGUICheckBox* CheckBoxDeviationTapX;
	ISXGUICheckBox* CheckBoxDeviationTapY;
	ISXGUICheckBox* CheckBoxDeviationTapZ;
	//}

	//spawn
	//{
	ISXGUIStatic* StaticSpawnPosType;
	ISXGUIComboBox* ComboBoxSpawnPosType;
	ISXGUIStatic* StaticSpawnOrigin;
	ISXGUIStatic* StaticSpawnOriginX;
	ISXGUIEdit* EditSpawnOriginX;
	ISXGUIStatic* StaticSpawnOriginY;
	ISXGUIEdit* EditSpawnOriginY;
	ISXGUIStatic* StaticSpawnOriginZ;
	ISXGUIEdit* EditSpawnOriginZ;
	ISXGUIStatic* StaticSpawnOriginDisp;
	ISXGUIEdit* EditSpawnOriginDisp;
	ISXGUICheckBox* CheckBoxSpawnOriginDispXPos;
	ISXGUICheckBox* CheckBoxSpawnOriginDispXNeg;
	ISXGUICheckBox* CheckBoxSpawnOriginDispYPos;
	ISXGUICheckBox* CheckBoxSpawnOriginDispYNeg;
	ISXGUICheckBox* CheckBoxSpawnOriginDispZPos;
	ISXGUICheckBox* CheckBoxSpawnOriginDispZNeg;
	ISXGUIStatic* StaticSpawnNextTime;
	ISXGUIEdit* EditSpawnNextTime;
	ISXGUIStatic* StaticSpawnNextTimeDisp;
	ISXGUIEdit* EditSpawnNextTimeDisp;
	//}

	//tex
	//{
	ISXGUIStatic* StaticTexture;
	ISXGUIEdit* EditTexture;
	ISXGUIButton* ButtonTextureSel;
	ISXGUIStatic* StaticAnimTexCountCadrsX;
	ISXGUIStatic* StaticAnimTexCountCadrsY;
	ISXGUIEdit* EditAnimTexCountCadrsX;
	ISXGUIEdit* EditAnimTexCountCadrsY;
	ISXGUIStatic* StaticAnimTexRate;
	ISXGUIEdit* EditAnimTexRate;
	ISXGUIStatic* StaticAnimTexRateDisp;
	ISXGUIEdit* EditAnimTexRateDisp;
	ISXGUIStatic* StaticAnimTexStartCadr;
	ISXGUIEdit* EditAnimTexStartCadr;
	ISXGUIStatic* StaticAnimTexStartCadrDisp;
	ISXGUIEdit* EditAnimTexStartCadrDisp;
	//}

	//velocity/acceleration
	//{
	ISXGUIStatic* StaticVelocity;
	ISXGUIStatic* StaticVelocityX;
	ISXGUIEdit* EditVelocityX;
	ISXGUIStatic* StaticVelocityY;
	ISXGUIEdit* EditVelocityY;
	ISXGUIStatic* StaticVelocityZ;
	ISXGUIEdit* EditVelocityZ;
	ISXGUIStatic* StaticVelocityDisp;
	ISXGUIEdit* EditVelocityDisp;
	ISXGUICheckBox* CheckBoxVelocityDispXNeg;
	ISXGUICheckBox* CheckBoxVelocityDispYNeg;
	ISXGUICheckBox* CheckBoxVelocityDispZNeg;
	ISXGUIStatic* StaticAcceleration;
	ISXGUIStatic* StaticAccelerationX;
	ISXGUIEdit* EditAccelerationX;
	ISXGUIStatic* StaticAccelerationY;
	ISXGUIEdit* EditAccelerationY;
	ISXGUIStatic* StaticAccelerationZ;
	ISXGUIEdit* EditAccelerationZ;
	ISXGUIStatic* StaticAccelerationDisp;
	ISXGUIEdit* EditAccelerationDisp;
	ISXGUICheckBox* CheckBoxAccelerationDispXNeg;
	ISXGUICheckBox* CheckBoxAccelerationDispYNeg;
	ISXGUICheckBox* CheckBoxAccelerationDispZNeg;
	//}

	void InitAllElements();

	void UpdateCountInfo();

	void EffReOpen();
	void EffSave();

	void EffInitList();

	void EffVisible(bool visible, bool iscreate);
	void EffNulling();
	void EffDataInit();

	void TabsVisible(bool visible);

	void AllInTabsVisible(bool visible);
	void AllInTabsNulling();

	void EmitterCreateVisible(bool visible);

	void BaseVisible(bool visible);
	void BaseDataInit();
	void BaseNulling();

	void BoundVisible(bool visible);
	void BoundDataInit();
	void BoundNulling();

	void CharacterVisible(bool visible);
	void CharacterDataInit();
	void CharacterNulling();

	void SpawnVisible(bool visible);
	void SpawnDataInit();
	void SpawnNulling();

	void TexVisible(bool visible);
	void TexDataInit();
	void TexNulling();

	void VelocityAccVisible(bool visible);
	void VelocityDataInit();
	void VelocityAccNulling();

	void DeleteAllElements();


	void PEcreateData();
	void PEdeleteData();

	bool canRenderBound = false;

	ID3DXMesh* FigureBox = 0;
	ID3DXMesh* FigureSphere = 0;
	ID3DXMesh* FigureCone = 0;
	float3_t FigureConeParam;
	float3 FigureConePos;

	ID SelEffID = -1;
	ID SelEmitterID = -1;
};


void SXParticlesEditor::InitAllElements()
{
	RECT wrect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &wrect, 0);
	int cx = (wrect.right - MAINWIN_SIZE_X) / 2;
	int cy = (wrect.bottom - MAINWIN_SIZE_Y) / 2;

	SXParticlesEditor::JobWindow = SXGUICrBaseWnd("JobWindow", "SXParticlesEditor", 0, 0, cx, cy, MAINWIN_SIZE_X, MAINWIN_SIZE_Y, 0, 0, CreateSolidBrush(RGB(220, 220, 220)), 0, CS_HREDRAW | CS_VREDRAW, WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION, 0, WndProcAllDefault);
	SXParticlesEditor::JobWindow->Visible(false);
	SXGUIBaseHandlers::InitHandlerMsg(SXParticlesEditor::JobWindow);

	SXParticlesEditor::JobWindow->MinSizeX = MAINWIN_SIZE_X;
	SXParticlesEditor::JobWindow->MinSizeY = MAINWIN_SIZE_Y;

	SXParticlesEditor::JobWindow->AddHandler(ComMenuId, WM_COMMAND);
	SXParticlesEditor::JobWindow->AddHandler(TrueExit, WM_CLOSE, 0, 0, 0, 0, true);
	SXParticlesEditor::JobWindow->AddHandler(MsgEditSize, WM_SIZE);
	SXParticlesEditor::MainMenu = SXGUICrMenuEx(IDR_MENU1);
	SXParticlesEditor::MainMenu->SetToWindow(SXParticlesEditor::JobWindow->GetHWND());

	SXParticlesEditor::StatusBar1 = SXGUICrStatusBar("StatusBar1", SXParticlesEditor::JobWindow->GetHWND(), 0, 0);
	SXParticlesEditor::StatusBar1->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	int arrpart[5];
	arrpart[0] = 300;
	arrpart[1] = -1;
	SXParticlesEditor::StatusBar1->SetCountParts(2, arrpart);
	SXParticlesEditor::StatusBar1->SetTextParts(0, "Playing emitters: 0/0");
	SXParticlesEditor::StatusBar1->SetTextParts(1, "Living particles: 0/0");

	SXParticlesEditor::WindowRender = SXGUICrBaseWnd("WindowRender","Window1",0,0,0,27,600,400,0,0,CreateSolidBrush(RGB(200,200,200)),0,CS_HREDRAW | CS_VREDRAW,WS_CHILD | WS_VISIBLE | WS_BORDER,SXParticlesEditor::JobWindow->GetHWND(),0);
	SXParticlesEditor::WindowRender->GAlign.left = true;
	SXParticlesEditor::WindowRender->GAlign.right = true;
	SXParticlesEditor::WindowRender->GAlign.top = true;
	SXParticlesEditor::WindowRender->GAlign.bottom = true;
	
	SXParticlesEditor::ToolBar1 = SXGUICrToolBar(0, 0, 804, 27, SXParticlesEditor::JobWindow->GetHWND(), WndProcAllDefault, 0);
	SXParticlesEditor::ToolBar1->GAlign.left = true;
	SXParticlesEditor::ToolBar1->GAlign.right = true;
	SXParticlesEditor::ToolBar1->GAlign.top = true;
	SXParticlesEditor::ToolBar1->GAlign.bottom = false;
	SXParticlesEditor::ToolBar1->AddHandler(SXParticlesEditor_ToolBar1_CallWmCommand, WM_COMMAND);

	SXParticlesEditor::ButtonTBReOpen = SXGUICrButtonEx("", 2, 1, 22, 22, 0, WS_CHILD | WS_VISIBLE | BS_PUSHLIKE | BS_BITMAP, SXParticlesEditor::ToolBar1->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonTBReOpen->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonTBReOpen->GAlign.left = true;
	SXParticlesEditor::ButtonTBReOpen->GAlign.top = true;
	SXParticlesEditor::ButtonTBReOpen->SetBmpInResourse(IDB_BITMAP1);

	SXParticlesEditor::ButtonTBSave = SXGUICrButtonEx("", 26, 1, 22, 22, 0, WS_CHILD | WS_VISIBLE | BS_PUSHLIKE | BS_BITMAP, SXParticlesEditor::ToolBar1->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonTBSave->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonTBSave->GAlign.left = true;
	SXParticlesEditor::ButtonTBSave->GAlign.top = true;
	SXParticlesEditor::ButtonTBSave->SetBmpInResourse(IDB_BITMAP2);

	SXParticlesEditor::CheckBoxTBGrid = SXGUICrCheckBoxEx("", 54, 1, 22, 22, 0, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE | BS_BITMAP, SXParticlesEditor::ToolBar1->GetHWND(), 0, 0);
	SXParticlesEditor::CheckBoxTBGrid->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxTBGrid->GAlign.left = true;
	SXParticlesEditor::CheckBoxTBGrid->GAlign.top = true;
	SXParticlesEditor::CheckBoxTBGrid->SetBmpInResourse(IDB_BITMAP3);

	SXParticlesEditor::CheckBoxTBAxes = SXGUICrCheckBoxEx("", 78, 1, 22, 22, 0, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE | BS_BITMAP, SXParticlesEditor::ToolBar1->GetHWND(), 0, 0);
	SXParticlesEditor::CheckBoxTBAxes->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxTBAxes->GAlign.left = true;
	SXParticlesEditor::CheckBoxTBAxes->GAlign.top = true;
	SXParticlesEditor::CheckBoxTBAxes->SetBmpInResourse(IDB_BITMAP4);

	SXParticlesEditor::CheckBoxTBBound = SXGUICrCheckBoxEx("", 102, 1, 22, 22, 0, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE | BS_BITMAP, SXParticlesEditor::ToolBar1->GetHWND(), 0, 0);
	SXParticlesEditor::CheckBoxTBBound->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxTBBound->GAlign.left = true;
	SXParticlesEditor::CheckBoxTBBound->GAlign.top = true;
	SXParticlesEditor::CheckBoxTBBound->SetBmpInResourse(IDB_BITMAP5);

	SXParticlesEditor::CheckBoxTBPlay = SXGUICrCheckBoxEx("", 130, 1, 22, 22, 0, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE | BS_BITMAP, SXParticlesEditor::ToolBar1->GetHWND(), 0, 0);
	SXParticlesEditor::CheckBoxTBPlay->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxTBPlay->GAlign.left = true;
	SXParticlesEditor::CheckBoxTBPlay->GAlign.top = true;
	SXParticlesEditor::CheckBoxTBPlay->SetBmpInResourse(IDB_BITMAP6);

	SXParticlesEditor::CheckBoxTBPause = SXGUICrCheckBoxEx("", 154, 1, 22, 22, 0, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE | BS_BITMAP, SXParticlesEditor::ToolBar1->GetHWND(), 0, 0);
	SXParticlesEditor::CheckBoxTBPause->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxTBPause->GAlign.left = true;
	SXParticlesEditor::CheckBoxTBPause->GAlign.top = true;
	SXParticlesEditor::CheckBoxTBPause->SetBmpInResourse(IDB_BITMAP7);

	SXParticlesEditor::CheckBoxTBStop = SXGUICrCheckBoxEx("", 178, 1, 22, 22, 0, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE | BS_BITMAP, SXParticlesEditor::ToolBar1->GetHWND(), 0, 0);
	SXParticlesEditor::CheckBoxTBStop->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxTBStop->GAlign.left = true;
	SXParticlesEditor::CheckBoxTBStop->GAlign.top = true;
	SXParticlesEditor::CheckBoxTBStop->SetBmpInResourse(IDB_BITMAP8);

	
	
	SXParticlesEditor::GroupBoxList = SXGUICrGroupBox("", 601, 28, 204, 400, SXParticlesEditor::JobWindow->GetHWND(), WndProcAllDefault, 0);
	SXGUIBaseHandlers::InitHandlerMsg(SXParticlesEditor::GroupBoxList);
	SXParticlesEditor::GroupBoxList->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::GroupBoxList->SetColorText(0, 0, 0);
	SXParticlesEditor::GroupBoxList->SetColorTextBk(220, 220, 220);
	SXParticlesEditor::GroupBoxList->SetTransparentTextBk(true);
	SXParticlesEditor::GroupBoxList->SetColorBrush(220, 220, 220);

	SXParticlesEditor::GroupBoxList->GAlign.left = false;
	SXParticlesEditor::GroupBoxList->GAlign.right = true;
	SXParticlesEditor::GroupBoxList->GAlign.top = true;
	SXParticlesEditor::GroupBoxList->GAlign.bottom = true;

	SXParticlesEditor::StaticEffects = SXGUICrStatic("Effects:", 10, 10, 50, 15, SXParticlesEditor::GroupBoxList->GetHWND(), 0, 0);
	SXParticlesEditor::StaticEffects->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticEffects->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticEffects->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticEffects->SetTransparentTextBk(true);
	SXParticlesEditor::StaticEffects->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticEffects->GAlign.left = true;
	SXParticlesEditor::StaticEffects->GAlign.top = true;

	SXParticlesEditor::StaticEffectsCount = SXGUICrStatic("0", 70, 10, 100, 15, SXParticlesEditor::GroupBoxList->GetHWND(), 0, 0);
	SXParticlesEditor::StaticEffectsCount->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticEffectsCount->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticEffectsCount->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticEffectsCount->SetTransparentTextBk(true);
	SXParticlesEditor::StaticEffectsCount->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticEffectsCount->GAlign.left = true;
	SXParticlesEditor::StaticEffectsCount->GAlign.top = true;
	
	SXParticlesEditor::ListBoxEffects = SXGUICrListBox("", 2, 30, 200, 200, SXParticlesEditor::GroupBoxList->GetHWND(), 0, 0, false);
	SXParticlesEditor::ListBoxEffects->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::ListBoxEffects->SetColorText(0,0,0);
	SXParticlesEditor::ListBoxEffects->SetColorTextBk(255,255,255);
	SXParticlesEditor::ListBoxEffects->SetTransparentTextBk(true);
	SXParticlesEditor::ListBoxEffects->SetColorBrush(255,255,255);
	SXParticlesEditor::ListBoxEffects->GAlign.left = true;
	SXParticlesEditor::ListBoxEffects->GAlign.top = true;
	SXParticlesEditor::ListBoxEffects->AddHandler(SXParticlesEditor_ListBoxEffects_Click,WM_LBUTTONUP);
	SXParticlesEditor::ListBoxEffects->AddHandler(SXParticlesEditor_ListBoxEffects_Click, WM_KEYUP, VK_UP, true, 0, false, false);
	SXParticlesEditor::ListBoxEffects->AddHandler(SXParticlesEditor_ListBoxEffects_Click, WM_KEYUP, VK_DOWN, true, 0, false, false);

	SXParticlesEditor::ButtonEffectsCreate = SXGUICrButton("Create", 5, 225, 60, 15, 0, SXParticlesEditor::GroupBoxList->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonEffectsCreate->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonEffectsCreate->GAlign.left = true;
	SXParticlesEditor::ButtonEffectsCreate->GAlign.top = true;
	SXParticlesEditor::ButtonEffectsCreate->AddHandler(SXParticlesEditor_ButtonEffectsCreate_Click, WM_LBUTTONUP);
	/*SXParticlesEditor::ButtonEffectsEdit = SXGUICrButton("Edit", 70, 225, 60, 15, 0, SXParticlesEditor::GroupBoxList->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonEffectsEdit->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonEffectsEdit->GAlign.left = true;
	SXParticlesEditor::ButtonEffectsEdit->GAlign.top = true;*/
	SXParticlesEditor::ButtonEffectsDelete = SXGUICrButton("Delete", 135, 225, 60, 15, 0, SXParticlesEditor::GroupBoxList->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonEffectsDelete->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonEffectsDelete->GAlign.left = true;
	SXParticlesEditor::ButtonEffectsDelete->GAlign.top = true;
	SXParticlesEditor::ButtonEffectsDelete->AddHandler(SXParticlesEditor_ButtonEffectsDelete_Click, WM_LBUTTONUP);


	SXParticlesEditor::StaticEmitters = SXGUICrStatic("Emitters:", 10, 250, 50, 15, SXParticlesEditor::GroupBoxList->GetHWND(), 0, 0);
	SXParticlesEditor::StaticEmitters->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticEmitters->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticEmitters->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticEmitters->SetTransparentTextBk(true);
	SXParticlesEditor::StaticEmitters->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticEmitters->GAlign.left = true;
	SXParticlesEditor::StaticEmitters->GAlign.top = true;

	SXParticlesEditor::StaticEmittersCount = SXGUICrStatic("0", 65, 250, 100, 15, SXParticlesEditor::GroupBoxList->GetHWND(), 0, 0);
	SXParticlesEditor::StaticEmittersCount->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticEmittersCount->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticEmittersCount->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticEmittersCount->SetTransparentTextBk(true);
	SXParticlesEditor::StaticEmittersCount->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticEmittersCount->GAlign.left = true;
	SXParticlesEditor::StaticEmittersCount->GAlign.top = true;

	SXParticlesEditor::ListBoxEmitters = SXGUICrListBox("", 2, 270, 200, 120, SXParticlesEditor::GroupBoxList->GetHWND(), 0, 0, false);
	SXParticlesEditor::ListBoxEmitters->SetFont("MS Shell Dlg",-11,0,400,0,0,0);
	SXParticlesEditor::ListBoxEmitters->SetColorText(0,0,0);
	SXParticlesEditor::ListBoxEmitters->SetColorTextBk(255,255,255);
	SXParticlesEditor::ListBoxEmitters->SetTransparentTextBk(true);
	SXParticlesEditor::ListBoxEmitters->SetColorBrush(255, 255, 255);
	SXParticlesEditor::ListBoxEmitters->GAlign.left = true;
	SXParticlesEditor::ListBoxEmitters->GAlign.top = true;
	SXParticlesEditor::ListBoxEmitters->AddHandler(SXParticlesEditor_ListBoxEmitters_Click, WM_LBUTTONUP);
	SXParticlesEditor::ListBoxEmitters->AddHandler(SXParticlesEditor_ListBoxEmitters_Click, WM_KEYUP, VK_UP, true, 0, false, false);
	SXParticlesEditor::ListBoxEmitters->AddHandler(SXParticlesEditor_ListBoxEmitters_Click, WM_KEYUP, VK_DOWN, true, 0, false, false);
	
	SXParticlesEditor::ButtonEmittersCreate = SXGUICrButton("Create", 5, 380, 60, 15, 0, SXParticlesEditor::GroupBoxList->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonEmittersCreate->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonEmittersCreate->GAlign.left = true;
	SXParticlesEditor::ButtonEmittersCreate->GAlign.top = true;
	SXParticlesEditor::ButtonEmittersCreate->AddHandler(SXParticlesEditor_ButtonEmittersCreate_Click, WM_LBUTTONUP);

	SXParticlesEditor::ButtonEmittersBasis = SXGUICrButton("basis", 70, 380, 60, 15, 0, SXParticlesEditor::GroupBoxList->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonEmittersBasis->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonEmittersBasis->GAlign.left = true;
	SXParticlesEditor::ButtonEmittersBasis->GAlign.top = true;
	SXParticlesEditor::ButtonEmittersBasis->AddHandler(SXParticlesEditor_ButtonEmittersBasis_Click, WM_LBUTTONUP);
	SXParticlesEditor::ButtonEmittersDelete = SXGUICrButton("Delete", 135, 380, 60, 15, 0, SXParticlesEditor::GroupBoxList->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonEmittersDelete->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonEmittersDelete->GAlign.left = true;
	SXParticlesEditor::ButtonEmittersDelete->GAlign.top = true;
	SXParticlesEditor::ButtonEmittersDelete->AddHandler(SXParticlesEditor_ButtonEmittersDelete_Click, WM_LBUTTONUP);


	SXParticlesEditor::GroupBoxData = SXGUICrGroupBox("", 0, 425, 803, 170, SXParticlesEditor::JobWindow->GetHWND(), WndProcAllDefault, 0);
	SXGUIBaseHandlers::InitHandlerMsg(SXParticlesEditor::GroupBoxData);
	//SXParticlesEditor::GroupBoxData->AddHandler(SXLevelEditor_GroupBoxLight_CallWmCommand, WM_COMMAND);
	SXParticlesEditor::GroupBoxData->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::GroupBoxData->SetColorText(0, 0, 0);
	SXParticlesEditor::GroupBoxData->SetColorTextBk(220, 220, 220);
	SXParticlesEditor::GroupBoxData->SetTransparentTextBk(true);
	SXParticlesEditor::GroupBoxData->SetColorBrush(220, 220, 220);

	SXParticlesEditor::GroupBoxData->GAlign.left = true;
	SXParticlesEditor::GroupBoxData->GAlign.right = true;
	SXParticlesEditor::GroupBoxData->GAlign.top = false;
	SXParticlesEditor::GroupBoxData->GAlign.bottom = true;

	SXParticlesEditor::GroupBoxData2 = SXGUICrGroupBox("", 0, 25, 803, 145, SXParticlesEditor::GroupBoxData->GetHWND(), WndProcAllDefault, 0);
	SXGUIBaseHandlers::InitHandlerMsg(SXParticlesEditor::GroupBoxData2);
	//SXParticlesEditor::GroupBoxData->AddHandler(SXLevelEditor_GroupBoxLight_CallWmCommand, WM_COMMAND);
	SXParticlesEditor::GroupBoxData2->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::GroupBoxData2->SetColorText(0, 0, 0);
	SXParticlesEditor::GroupBoxData2->SetColorTextBk(220, 220, 220);
	SXParticlesEditor::GroupBoxData2->SetTransparentTextBk(true);
	SXParticlesEditor::GroupBoxData2->SetColorBrush(220, 220, 220);

	SXParticlesEditor::GroupBoxData2->GAlign.left = true;
	SXParticlesEditor::GroupBoxData2->GAlign.right = true;
	SXParticlesEditor::GroupBoxData2->GAlign.top = false;
	SXParticlesEditor::GroupBoxData2->GAlign.bottom = true;
	SXParticlesEditor::GroupBoxData2->AddHandler(SXParticlesEditor_GroupBoxData2_CallWmCommand, WM_COMMAND);

	SXParticlesEditor::GroupBoxTabs = SXGUICrGroupBox("", 0, 0, 655, 30, SXParticlesEditor::GroupBoxData->GetHWND(), WndProcAllDefault, 0);
	SXGUIBaseHandlers::InitHandlerMsg(SXParticlesEditor::GroupBoxTabs);
	SXParticlesEditor::GroupBoxTabs->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::GroupBoxTabs->SetColorText(0, 0, 0);
	SXParticlesEditor::GroupBoxTabs->SetColorTextBk(220, 220, 220);
	SXParticlesEditor::GroupBoxTabs->SetTransparentTextBk(true);
	SXParticlesEditor::GroupBoxTabs->SetColorBrush(220, 220, 220);

	SXParticlesEditor::GroupBoxTabs->GAlign.left = true;
	SXParticlesEditor::GroupBoxTabs->GAlign.right = false;
	SXParticlesEditor::GroupBoxTabs->GAlign.top = false;
	SXParticlesEditor::GroupBoxTabs->GAlign.bottom = true;


	SXParticlesEditor::ButtonBase = SXGUICrRadioButtonEx("Base", 10, 10, 100, 15, 0, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_PUSHLIKE, SXParticlesEditor::GroupBoxTabs->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonBase->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonBase->GAlign.left = true;
	SXParticlesEditor::ButtonBase->GAlign.top = true;
	SXParticlesEditor::ButtonBase->AddHandler(SXParticlesEditor_ButtonBase_Click, WM_LBUTTONUP);

	SXParticlesEditor::ButtonTextureAnimTex = SXGUICrRadioButtonEx("TextureAnimTex", 115, 10, 100, 15, 0, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_PUSHLIKE, SXParticlesEditor::GroupBoxTabs->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonTextureAnimTex->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonTextureAnimTex->GAlign.left = true;
	SXParticlesEditor::ButtonTextureAnimTex->GAlign.top = true;
	SXParticlesEditor::ButtonTextureAnimTex->AddHandler(SXParticlesEditor_ButtonTextureAnimTex_Click, WM_LBUTTONUP);

	SXParticlesEditor::ButtonSpawn = SXGUICrRadioButtonEx("Spawn", 220, 10, 100, 15, 0, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_PUSHLIKE, SXParticlesEditor::GroupBoxTabs->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonSpawn->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonSpawn->GAlign.left = true;
	SXParticlesEditor::ButtonSpawn->GAlign.top = true;
	SXParticlesEditor::ButtonSpawn->AddHandler(SXParticlesEditor_ButtonSpawn_Click, WM_LBUTTONUP);

	SXParticlesEditor::ButtonBound = SXGUICrRadioButtonEx("Bound", 325, 10, 100, 15, 0, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_PUSHLIKE, SXParticlesEditor::GroupBoxTabs->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonBound->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonBound->GAlign.left = true;
	SXParticlesEditor::ButtonBound->GAlign.top = true;
	SXParticlesEditor::ButtonBound->AddHandler(SXParticlesEditor_ButtonBound_Click, WM_LBUTTONUP);

	SXParticlesEditor::ButtonCharacters = SXGUICrRadioButtonEx("Charaters", 430, 10, 100, 15, 0, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_PUSHLIKE, SXParticlesEditor::GroupBoxTabs->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonCharacters->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonCharacters->GAlign.left = true;
	SXParticlesEditor::ButtonCharacters->GAlign.top = true;
	SXParticlesEditor::ButtonCharacters->AddHandler(SXParticlesEditor_ButtonCharacters_Click, WM_LBUTTONUP);

	SXParticlesEditor::ButtonVelocityAcceleration = SXGUICrRadioButtonEx("VelocityAcceleration", 535, 10, 110, 15, 0, WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | BS_PUSHLIKE, SXParticlesEditor::GroupBoxTabs->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonVelocityAcceleration->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonVelocityAcceleration->GAlign.left = true;
	SXParticlesEditor::ButtonVelocityAcceleration->GAlign.top = true;
	SXParticlesEditor::ButtonVelocityAcceleration->AddHandler(SXParticlesEditor_ButtonVelocityAcceleration_Click, WM_LBUTTONUP);

	SXParticlesEditor::StaticEffName = SXGUICrStatic("Name:", 5, 10, 40, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticEffName->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticEffName->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticEffName->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticEffName->SetTransparentTextBk(true);
	SXParticlesEditor::StaticEffName->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticEffName->GAlign.left = true;
	SXParticlesEditor::StaticEffName->GAlign.top = true;
	SXParticlesEditor::EditEffName = SXGUICrEdit("0", 50, 10, 200, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditEffName->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditEffName->SetColorText(0, 0, 0);
	SXParticlesEditor::EditEffName->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditEffName->SetTransparentTextBk(true);
	SXParticlesEditor::EditEffName->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditEffName->GAlign.left = true;
	SXParticlesEditor::EditEffName->GAlign.top = true;
	SXParticlesEditor::EditEffName->AddHandler(SXParticlesEditor_EditEffName_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);

	SXParticlesEditor::ButtonEffCreate = SXGUICrButton("Create", 260, 10, 50, 15, 0, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonEffCreate->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonEffCreate->GAlign.left = true;
	SXParticlesEditor::ButtonEffCreate->GAlign.top = true;
	SXParticlesEditor::ButtonEffCreate->AddHandler(SXParticlesEditor_ButtonEffCreate_Click, WM_LBUTTONUP);


	//base
	//{
	SXParticlesEditor::StaticName = SXGUICrStatic("Name:", 5, 10, 40, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticName->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticName->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticName->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticName->SetTransparentTextBk(true);
	SXParticlesEditor::StaticName->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticName->GAlign.left = true;
	SXParticlesEditor::StaticName->GAlign.top = true;
	SXParticlesEditor::EditName = SXGUICrEdit("0", 50, 10, 200, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditName->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditName->SetColorText(0, 0, 0);
	SXParticlesEditor::EditName->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditName->SetTransparentTextBk(true);
	SXParticlesEditor::EditName->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditName->GAlign.left = true;
	SXParticlesEditor::EditName->GAlign.top = true;
	SXParticlesEditor::EditName->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditName->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticCount = SXGUICrStatic("Count:", 5, 30, 75, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticCount->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticCount->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticCount->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticCount->SetTransparentTextBk(true);
	SXParticlesEditor::StaticCount->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticCount->GAlign.left = true;
	SXParticlesEditor::StaticCount->GAlign.top = true;
	SXParticlesEditor::EditCount = SXGUICrEdit("0", 50, 30, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditCount->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditCount->SetColorText(0, 0, 0);
	SXParticlesEditor::EditCount->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditCount->SetTransparentTextBk(true);
	SXParticlesEditor::EditCount->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditCount->GAlign.left = true;
	SXParticlesEditor::EditCount->GAlign.top = true;
	SXParticlesEditor::EditCount->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditCount->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticColorCoef = SXGUICrStatic("ColorCoef:", 130, 30, 75, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticColorCoef->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticColorCoef->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticColorCoef->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticColorCoef->SetTransparentTextBk(true);
	SXParticlesEditor::StaticColorCoef->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticColorCoef->GAlign.left = true;
	SXParticlesEditor::StaticColorCoef->GAlign.top = true;
	SXParticlesEditor::EditColorCoef = SXGUICrEdit("0", 180, 30, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditColorCoef->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditColorCoef->SetColorText(0, 0, 0);
	SXParticlesEditor::EditColorCoef->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditColorCoef->SetTransparentTextBk(true);
	SXParticlesEditor::EditColorCoef->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditColorCoef->GAlign.left = true;
	SXParticlesEditor::EditColorCoef->GAlign.top = true;
	SXParticlesEditor::EditColorCoef->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditColorCoef->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::ButtonEmitterCreate = SXGUICrButton("CREATE", 725, 120, 70, 20, 0, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonEmitterCreate->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonEmitterCreate->SetColorText(0, 0, 0);
	SXParticlesEditor::ButtonEmitterCreate->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::ButtonEmitterCreate->SetTransparentTextBk(true);
	SXParticlesEditor::ButtonEmitterCreate->SetColorBrush(220, 220, 220);
	SXParticlesEditor::ButtonEmitterCreate->GAlign.left = true;
	SXParticlesEditor::ButtonEmitterCreate->GAlign.top = true;
	SXParticlesEditor::ButtonEmitterCreate->AddHandler(SXParticlesEditor_ButtonEmitterCreate_Click, WM_LBUTTONUP);

	SXParticlesEditor::StaticReCreateCount = SXGUICrStatic("ReCreateCount:", 5, 50, 75, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticReCreateCount->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticReCreateCount->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticReCreateCount->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticReCreateCount->SetTransparentTextBk(true);
	SXParticlesEditor::StaticReCreateCount->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticReCreateCount->GAlign.left = true;
	SXParticlesEditor::StaticReCreateCount->GAlign.top = true;
	SXParticlesEditor::EditReCreateCount = SXGUICrEdit("0", 100, 50, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditReCreateCount->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditReCreateCount->SetColorText(0, 0, 0);
	SXParticlesEditor::EditReCreateCount->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditReCreateCount->SetTransparentTextBk(true);
	SXParticlesEditor::EditReCreateCount->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditReCreateCount->GAlign.left = true;
	SXParticlesEditor::EditReCreateCount->GAlign.top = true;
	SXParticlesEditor::EditReCreateCount->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditReCreateCount->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticSoftCoef = SXGUICrStatic("SoftCoef:", 5, 70, 50, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSoftCoef->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSoftCoef->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSoftCoef->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSoftCoef->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSoftCoef->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSoftCoef->GAlign.left = true;
	SXParticlesEditor::StaticSoftCoef->GAlign.top = true;
	SXParticlesEditor::EditSoftCoef = SXGUICrEdit("0", 100, 70, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditSoftCoef->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditSoftCoef->SetColorText(0, 0, 0);
	SXParticlesEditor::EditSoftCoef->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditSoftCoef->SetTransparentTextBk(true);
	SXParticlesEditor::EditSoftCoef->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditSoftCoef->GAlign.left = true;
	SXParticlesEditor::EditSoftCoef->GAlign.top = true;
	SXParticlesEditor::EditSoftCoef->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditSoftCoef->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticRefractionCoef = SXGUICrStatic("RefractionCoef:", 5, 90, 75, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticRefractionCoef->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticRefractionCoef->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticRefractionCoef->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticRefractionCoef->SetTransparentTextBk(true);
	SXParticlesEditor::StaticRefractionCoef->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticRefractionCoef->GAlign.left = true;
	SXParticlesEditor::StaticRefractionCoef->GAlign.top = true;
	SXParticlesEditor::EditRefractionCoef = SXGUICrEdit("0", 100, 90, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditRefractionCoef->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditRefractionCoef->SetColorText(0, 0, 0);
	SXParticlesEditor::EditRefractionCoef->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditRefractionCoef->SetTransparentTextBk(true);
	SXParticlesEditor::EditRefractionCoef->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditRefractionCoef->GAlign.left = true;
	SXParticlesEditor::EditRefractionCoef->GAlign.top = true;
	SXParticlesEditor::EditRefractionCoef->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditRefractionCoef->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticTransparencyCoef = SXGUICrStatic("TransparencyCoef:", 5, 110, 90, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticTransparencyCoef->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticTransparencyCoef->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticTransparencyCoef->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticTransparencyCoef->SetTransparentTextBk(true);
	SXParticlesEditor::StaticTransparencyCoef->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticTransparencyCoef->GAlign.left = true;
	SXParticlesEditor::StaticTransparencyCoef->GAlign.top = true;
	SXParticlesEditor::EditTransparencyCoef = SXGUICrEdit("0", 100, 110, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditTransparencyCoef->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditTransparencyCoef->SetColorText(0, 0, 0);
	SXParticlesEditor::EditTransparencyCoef->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditTransparencyCoef->SetTransparentTextBk(true);
	SXParticlesEditor::EditTransparencyCoef->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditTransparencyCoef->GAlign.left = true;
	SXParticlesEditor::EditTransparencyCoef->GAlign.top = true;
	SXParticlesEditor::EditTransparencyCoef->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditTransparencyCoef->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::CheckBoxLighting = SXGUICrCheckBox("Lighting", 180, 50, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxLighting->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxLighting->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxLighting->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxLighting->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxLighting->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxLighting->GAlign.left = true;
	SXParticlesEditor::CheckBoxLighting->GAlign.top = true;

	SXParticlesEditor::CheckBoxCollisionDelete = SXGUICrCheckBox("CollisionDelete", 180, 70, 90, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxCollisionDelete->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxCollisionDelete->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxCollisionDelete->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxCollisionDelete->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxCollisionDelete->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxCollisionDelete->GAlign.left = true;
	SXParticlesEditor::CheckBoxCollisionDelete->GAlign.top = true;


	SXParticlesEditor::StaticFigureType = SXGUICrStatic("FigureType:", 270, 12, 60, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticFigureType->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticFigureType->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticFigureType->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticFigureType->SetTransparentTextBk(true);
	SXParticlesEditor::StaticFigureType->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticFigureType->GAlign.left = true;
	SXParticlesEditor::StaticFigureType->GAlign.top = true;
	SXParticlesEditor::ComboBoxFigureType = SXGUICrComboBox("", 335, 10, 170, 75, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::ComboBoxFigureType->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ComboBoxFigureType->SetColorText(0, 0, 0);
	SXParticlesEditor::ComboBoxFigureType->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::ComboBoxFigureType->SetTransparentTextBk(true);
	SXParticlesEditor::ComboBoxFigureType->SetColorBrush(255, 255, 255);
	SXParticlesEditor::ComboBoxFigureType->AddItem("quad");
	SXParticlesEditor::ComboBoxFigureType->AddItem("billboard");
	SXParticlesEditor::ComboBoxFigureType->AddItem("quad_composite");
	SXParticlesEditor::ComboBoxFigureType->SetSel(0);
	SXParticlesEditor::ComboBoxFigureType->GAlign.left = true;
	SXParticlesEditor::ComboBoxFigureType->GAlign.top = true;

	SXParticlesEditor::StaticFigureCountQuads = SXGUICrStatic("FigureCountQuads:", 270, 35, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticFigureCountQuads->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticFigureCountQuads->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticFigureCountQuads->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticFigureCountQuads->SetTransparentTextBk(true);
	SXParticlesEditor::StaticFigureCountQuads->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticFigureCountQuads->GAlign.left = true;
	SXParticlesEditor::StaticFigureCountQuads->GAlign.top = true;
	SXParticlesEditor::EditFigureCountQuads = SXGUICrEdit("0", 375, 35, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditFigureCountQuads->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditFigureCountQuads->SetColorText(0, 0, 0);
	SXParticlesEditor::EditFigureCountQuads->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditFigureCountQuads->SetTransparentTextBk(true);
	SXParticlesEditor::EditFigureCountQuads->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditFigureCountQuads->GAlign.left = true;
	SXParticlesEditor::EditFigureCountQuads->GAlign.top = true;
	SXParticlesEditor::EditFigureCountQuads->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditFigureCountQuads->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::CheckBoxFigureRotRand = SXGUICrCheckBox("FigureRotRand", 270, 55, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxFigureRotRand->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxFigureRotRand->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxFigureRotRand->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxFigureRotRand->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxFigureRotRand->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxFigureRotRand->GAlign.left = true;
	SXParticlesEditor::CheckBoxFigureRotRand->GAlign.top = true;
	SXParticlesEditor::CheckBoxFigureTapX = SXGUICrCheckBox("FigureTapX", 270, 75, 75, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxFigureTapX->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxFigureTapX->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxFigureTapX->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxFigureTapX->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxFigureTapX->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxFigureTapX->GAlign.left = true;
	SXParticlesEditor::CheckBoxFigureTapX->GAlign.top = true;
	SXParticlesEditor::CheckBoxFigureTapY = SXGUICrCheckBox("FigureTapY", 350, 75, 75, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxFigureTapY->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxFigureTapY->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxFigureTapY->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxFigureTapY->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxFigureTapY->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxFigureTapY->GAlign.left = true;
	SXParticlesEditor::CheckBoxFigureTapY->GAlign.top = true;
	SXParticlesEditor::CheckBoxFigureTapZ = SXGUICrCheckBox("FigureTapZ", 430, 75, 75, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxFigureTapZ->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxFigureTapZ->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxFigureTapZ->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxFigureTapZ->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxFigureTapZ->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxFigureTapZ->GAlign.left = true;
	SXParticlesEditor::CheckBoxFigureTapZ->GAlign.top = true;

	SXParticlesEditor::StaticAlphaBlendType = SXGUICrStatic("AlphaBlendType:", 270, 97, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticAlphaBlendType->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticAlphaBlendType->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticAlphaBlendType->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticAlphaBlendType->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAlphaBlendType->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticAlphaBlendType->GAlign.left = true;
	SXParticlesEditor::StaticAlphaBlendType->GAlign.top = true;
	SXParticlesEditor::ComboBoxAlphaBlendType = SXGUICrComboBox("", 355, 95, 150, 75, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::ComboBoxAlphaBlendType->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ComboBoxAlphaBlendType->SetColorText(0, 0, 0);
	SXParticlesEditor::ComboBoxAlphaBlendType->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::ComboBoxAlphaBlendType->SetTransparentTextBk(true);
	SXParticlesEditor::ComboBoxAlphaBlendType->SetColorBrush(255, 255, 255);
	SXParticlesEditor::ComboBoxAlphaBlendType->AddItem("pabt_alpha");
	SXParticlesEditor::ComboBoxAlphaBlendType->AddItem("pabt_add");
	SXParticlesEditor::ComboBoxAlphaBlendType->SetSel(0);
	SXParticlesEditor::ComboBoxAlphaBlendType->GAlign.left = true;
	SXParticlesEditor::ComboBoxAlphaBlendType->GAlign.top = true;


	SXParticlesEditor::StaticColor = SXGUICrStatic("Color:", 270, 120, 30, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticColor->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticColor->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticColor->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticColor->SetTransparentTextBk(true);
	SXParticlesEditor::StaticColor->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticColor->GAlign.left = true;
	SXParticlesEditor::StaticColor->GAlign.top = true;

	SXParticlesEditor::StaticColorR = SXGUICrStatic("r:", 302, 120, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticColorR->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticColorR->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticColorR->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticColorR->SetTransparentTextBk(true);
	SXParticlesEditor::StaticColorR->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticColorR->GAlign.left = true;
	SXParticlesEditor::StaticColorR->GAlign.top = true;

	SXParticlesEditor::EditColorR = SXGUICrEdit("0", 310, 120, 45, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditColorR->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditColorR->SetColorText(0, 0, 0);
	SXParticlesEditor::EditColorR->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditColorR->SetTransparentTextBk(true);
	SXParticlesEditor::EditColorR->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditColorR->GAlign.left = true;
	SXParticlesEditor::EditColorR->GAlign.top = true;
	SXParticlesEditor::EditColorR->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditColorR->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticColorG = SXGUICrStatic("g:", 356, 120, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticColorG->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticColorG->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticColorG->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticColorG->SetTransparentTextBk(true);
	SXParticlesEditor::StaticColorG->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticColorG->GAlign.left = true;
	SXParticlesEditor::StaticColorG->GAlign.top = true;

	SXParticlesEditor::EditColorG = SXGUICrEdit("0", 365, 120, 45, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditColorG->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditColorG->SetColorText(0, 0, 0);
	SXParticlesEditor::EditColorG->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditColorG->SetTransparentTextBk(true);
	SXParticlesEditor::EditColorG->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditColorG->GAlign.left = true;
	SXParticlesEditor::EditColorG->GAlign.top = true;
	SXParticlesEditor::EditColorG->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditColorG->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticColorB = SXGUICrStatic("b:", 411, 120, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticColorB->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticColorB->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticColorB->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticColorB->SetTransparentTextBk(true);
	SXParticlesEditor::StaticColorB->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticColorB->GAlign.left = true;
	SXParticlesEditor::StaticColorB->GAlign.top = true;

	SXParticlesEditor::EditColorB = SXGUICrEdit("0", 420, 120, 45, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditColorB->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditColorB->SetColorText(0, 0, 0);
	SXParticlesEditor::EditColorB->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditColorB->SetTransparentTextBk(true);
	SXParticlesEditor::EditColorB->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditColorB->GAlign.left = true;
	SXParticlesEditor::EditColorB->GAlign.top = true;
	SXParticlesEditor::EditColorB->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditColorB->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticColorA = SXGUICrStatic("a:", 466, 120, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticColorA->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticColorA->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticColorA->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticColorA->SetTransparentTextBk(true);
	SXParticlesEditor::StaticColorA->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticColorA->GAlign.left = true;
	SXParticlesEditor::StaticColorA->GAlign.top = true;

	SXParticlesEditor::EditColorA = SXGUICrEdit("0", 475, 120, 45, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditColorA->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditColorA->SetColorText(0, 0, 0);
	SXParticlesEditor::EditColorA->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditColorA->SetTransparentTextBk(true);
	SXParticlesEditor::EditColorA->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditColorA->GAlign.left = true;
	SXParticlesEditor::EditColorA->GAlign.top = true;
	SXParticlesEditor::EditColorA->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditColorA->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	/*ISXGUIStatic* StaticColorG;
	ISXGUIEdit* EditColorG;
	ISXGUIStatic* StaticColorB;
	ISXGUIEdit* EditColorB;
	ISXGUIStatic* StaticColorA;
	ISXGUIEdit* EditColorA;*/


	SXParticlesEditor::StaticTimeLife = SXGUICrStatic("TimeLife:", 530, 10, 50, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticTimeLife->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticTimeLife->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticTimeLife->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticTimeLife->SetTransparentTextBk(true);
	SXParticlesEditor::StaticTimeLife->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticTimeLife->GAlign.left = true;
	SXParticlesEditor::StaticTimeLife->GAlign.top = true;
	SXParticlesEditor::EditTimeLife = SXGUICrEdit("0", 585, 10, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditTimeLife->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditTimeLife->SetColorText(0, 0, 0);
	SXParticlesEditor::EditTimeLife->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditTimeLife->SetTransparentTextBk(true);
	SXParticlesEditor::EditTimeLife->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditTimeLife->GAlign.left = true;
	SXParticlesEditor::EditTimeLife->GAlign.top = true;
	SXParticlesEditor::EditTimeLife->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditTimeLife->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticTimeLifeDisp = SXGUICrStatic("TimeLifeDisp:", 660, 10, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticTimeLifeDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticTimeLifeDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticTimeLifeDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticTimeLifeDisp->SetTransparentTextBk(true);
	SXParticlesEditor::StaticTimeLifeDisp->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticTimeLifeDisp->GAlign.left = true;
	SXParticlesEditor::StaticTimeLifeDisp->GAlign.top = true;
	SXParticlesEditor::EditTimeLifeDisp = SXGUICrEdit("0", 730, 10, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditTimeLifeDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditTimeLifeDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::EditTimeLifeDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditTimeLifeDisp->SetTransparentTextBk(true);
	SXParticlesEditor::EditTimeLifeDisp->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditTimeLifeDisp->GAlign.left = true;
	SXParticlesEditor::EditTimeLifeDisp->GAlign.top = true;
	SXParticlesEditor::EditTimeLifeDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditTimeLifeDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticAlphaAgeDepend = SXGUICrStatic("AlphaAgeDepend:", 530, 32, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticAlphaAgeDepend->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticAlphaAgeDepend->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticAlphaAgeDepend->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticAlphaAgeDepend->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAlphaAgeDepend->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticAlphaAgeDepend->GAlign.left = true;
	SXParticlesEditor::StaticAlphaAgeDepend->GAlign.top = true;
	SXParticlesEditor::ComboBoxAlphaDependAge = SXGUICrComboBox("", 630, 30, 170, 75, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::ComboBoxAlphaDependAge->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ComboBoxAlphaDependAge->SetColorText(0, 0, 0);
	SXParticlesEditor::ComboBoxAlphaDependAge->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::ComboBoxAlphaDependAge->SetTransparentTextBk(true);
	SXParticlesEditor::ComboBoxAlphaDependAge->SetColorBrush(255, 255, 255);
	SXParticlesEditor::ComboBoxAlphaDependAge->AddItem("none");
	SXParticlesEditor::ComboBoxAlphaDependAge->AddItem("direct");
	SXParticlesEditor::ComboBoxAlphaDependAge->AddItem("inverse");
	SXParticlesEditor::ComboBoxAlphaDependAge->SetSel(0);
	SXParticlesEditor::ComboBoxAlphaDependAge->GAlign.left = true;
	SXParticlesEditor::ComboBoxAlphaDependAge->GAlign.top = true;

	SXParticlesEditor::StaticSize = SXGUICrStatic("Size:", 530, 55, 25, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSize->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSize->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSize->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSize->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSize->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSize->GAlign.left = true;
	SXParticlesEditor::StaticSize->GAlign.top = true;
	SXParticlesEditor::StaticSizeX = SXGUICrStatic("x:", 555, 55, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSizeX->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSizeX->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSizeX->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSizeX->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSizeX->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSizeX->GAlign.left = true;
	SXParticlesEditor::StaticSizeX->GAlign.top = true;
	SXParticlesEditor::EditSizeX = SXGUICrEdit("0", 565, 55, 65, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditSizeX->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditSizeX->SetColorText(0, 0, 0);
	SXParticlesEditor::EditSizeX->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditSizeX->SetTransparentTextBk(true);
	SXParticlesEditor::EditSizeX->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditSizeX->GAlign.left = true;
	SXParticlesEditor::EditSizeX->GAlign.top = true;
	SXParticlesEditor::EditSizeX->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditSizeX->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticSizeY = SXGUICrStatic("y:", 635, 55, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSizeY->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSizeY->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSizeY->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSizeY->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSizeY->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSizeY->GAlign.left = true;
	SXParticlesEditor::StaticSizeY->GAlign.top = true;
	SXParticlesEditor::EditSizeY = SXGUICrEdit("0", 645, 55, 65, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditSizeY->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditSizeY->SetColorText(0, 0, 0);
	SXParticlesEditor::EditSizeY->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditSizeY->SetTransparentTextBk(true);
	SXParticlesEditor::EditSizeY->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditSizeY->GAlign.left = true;
	SXParticlesEditor::EditSizeY->GAlign.top = true;
	SXParticlesEditor::EditSizeY->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditSizeY->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticSizeDisp = SXGUICrStatic("Disp:", 710, 55, 25, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSizeDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSizeDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSizeDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSizeDisp->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSizeDisp->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSizeDisp->GAlign.left = true;
	SXParticlesEditor::StaticSizeDisp->GAlign.top = true;
	SXParticlesEditor::EditSizeDisp = SXGUICrEdit("0", 735, 55, 65, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditSizeDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditSizeDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::EditSizeDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditSizeDisp->SetTransparentTextBk(true);
	SXParticlesEditor::EditSizeDisp->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditSizeDisp->GAlign.left = true;
	SXParticlesEditor::EditSizeDisp->GAlign.top = true;
	SXParticlesEditor::EditSizeDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditSizeDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticSizeDependAge = SXGUICrStatic("SizeDependAge:", 530, 77, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSizeDependAge->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSizeDependAge->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSizeDependAge->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSizeDependAge->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSizeDependAge->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSizeDependAge->GAlign.left = true;
	SXParticlesEditor::StaticSizeDependAge->GAlign.top = true;
	SXParticlesEditor::ComboBoxSizeDependAge = SXGUICrComboBox("", 630, 75, 170, 75, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::ComboBoxSizeDependAge->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ComboBoxSizeDependAge->SetColorText(0, 0, 0);
	SXParticlesEditor::ComboBoxSizeDependAge->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::ComboBoxSizeDependAge->SetTransparentTextBk(true);
	SXParticlesEditor::ComboBoxSizeDependAge->SetColorBrush(255, 255, 255);
	SXParticlesEditor::ComboBoxSizeDependAge->AddItem("none");
	SXParticlesEditor::ComboBoxSizeDependAge->AddItem("direct");
	SXParticlesEditor::ComboBoxSizeDependAge->AddItem("inverse");
	SXParticlesEditor::ComboBoxSizeDependAge->SetSel(0);
	SXParticlesEditor::ComboBoxSizeDependAge->GAlign.left = true;
	SXParticlesEditor::ComboBoxSizeDependAge->GAlign.top = true;


	SXParticlesEditor::CheckBoxTrack = SXGUICrCheckBox("Track", 530, 100, 50, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxTrack->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxTrack->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxTrack->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxTrack->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxTrack->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxTrack->GAlign.left = true;
	SXParticlesEditor::CheckBoxTrack->GAlign.top = true;

	SXParticlesEditor::StaticTrackSize = SXGUICrStatic("Size:", 580, 100, 25, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticTrackSize->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticTrackSize->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticTrackSize->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticTrackSize->SetTransparentTextBk(true);
	SXParticlesEditor::StaticTrackSize->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticTrackSize->GAlign.left = true;
	SXParticlesEditor::StaticTrackSize->GAlign.top = true;

	SXParticlesEditor::EditTrackSize = SXGUICrEdit("0", 605, 100, 60, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditTrackSize->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditTrackSize->SetColorText(0, 0, 0);
	SXParticlesEditor::EditTrackSize->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditTrackSize->SetTransparentTextBk(true);
	SXParticlesEditor::EditTrackSize->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditTrackSize->GAlign.left = true;
	SXParticlesEditor::EditTrackSize->GAlign.top = true;
	SXParticlesEditor::EditTrackSize->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditTrackSize->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticTrackTime = SXGUICrStatic("Time:", 670, 100, 25, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticTrackTime->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticTrackTime->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticTrackTime->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticTrackTime->SetTransparentTextBk(true);
	SXParticlesEditor::StaticTrackTime->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticTrackTime->GAlign.left = true;
	SXParticlesEditor::StaticTrackTime->GAlign.top = true;

	SXParticlesEditor::EditTrackTime = SXGUICrEdit("0", 700, 100, 60, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditTrackTime->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditTrackTime->SetColorText(0, 0, 0);
	SXParticlesEditor::EditTrackTime->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditTrackTime->SetTransparentTextBk(true);
	SXParticlesEditor::EditTrackTime->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditTrackTime->GAlign.left = true;
	SXParticlesEditor::EditTrackTime->GAlign.top = true;
	SXParticlesEditor::EditTrackTime->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditTrackTime->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);
	//}

	//bound
	//{
	SXParticlesEditor::StaticBoundType = SXGUICrStatic("Bound type:", 5, 12, 60, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticBoundType->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticBoundType->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticBoundType->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticBoundType->SetTransparentTextBk(true);
	SXParticlesEditor::StaticBoundType->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticBoundType->GAlign.left = true;
	SXParticlesEditor::StaticBoundType->GAlign.top = true;
	SXParticlesEditor::ComboBoxBoundType = SXGUICrComboBox("", 80, 10, 140, 100, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::ComboBoxBoundType->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ComboBoxBoundType->SetColorText(0, 0, 0);
	SXParticlesEditor::ComboBoxBoundType->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::ComboBoxBoundType->SetTransparentTextBk(true);
	SXParticlesEditor::ComboBoxBoundType->SetColorBrush(255, 255, 255);
	SXParticlesEditor::ComboBoxBoundType->AddItem("none");
	SXParticlesEditor::ComboBoxBoundType->AddItem("sphere");
	SXParticlesEditor::ComboBoxBoundType->AddItem("box");
	SXParticlesEditor::ComboBoxBoundType->AddItem("cone");
	SXParticlesEditor::ComboBoxBoundType->SetSel(0);
	SXParticlesEditor::ComboBoxBoundType->GAlign.left = true;
	SXParticlesEditor::ComboBoxBoundType->GAlign.top = true;
	SXParticlesEditor::StaticBoundVec1 = SXGUICrStatic("Vector1:", 5, 40, 50, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticBoundVec1->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticBoundVec1->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticBoundVec1->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticBoundVec1->SetTransparentTextBk(true);
	SXParticlesEditor::StaticBoundVec1->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticBoundVec1->GAlign.left = true;
	SXParticlesEditor::StaticBoundVec1->GAlign.top = true;
	SXParticlesEditor::StaticBoundVec1X = SXGUICrStatic("x:", 60, 40, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticBoundVec1X->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticBoundVec1X->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticBoundVec1X->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticBoundVec1X->SetTransparentTextBk(true);
	SXParticlesEditor::StaticBoundVec1X->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticBoundVec1X->GAlign.left = true;
	SXParticlesEditor::StaticBoundVec1X->GAlign.top = true;
	SXParticlesEditor::EditBoundVec1X = SXGUICrEdit("0", 70, 40, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditBoundVec1X->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditBoundVec1X->SetColorText(0, 0, 0);
	SXParticlesEditor::EditBoundVec1X->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditBoundVec1X->SetTransparentTextBk(true);
	SXParticlesEditor::EditBoundVec1X->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditBoundVec1X->GAlign.left = true;
	SXParticlesEditor::EditBoundVec1X->GAlign.top = true;
	SXParticlesEditor::EditBoundVec1X->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditBoundVec1X->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticBoundVec1Y = SXGUICrStatic("y:", 150, 40, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticBoundVec1Y->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticBoundVec1Y->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticBoundVec1Y->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticBoundVec1Y->SetTransparentTextBk(true);
	SXParticlesEditor::StaticBoundVec1Y->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticBoundVec1Y->GAlign.left = true;
	SXParticlesEditor::StaticBoundVec1Y->GAlign.top = true;
	SXParticlesEditor::EditBoundVec1Y = SXGUICrEdit("0", 160, 40, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditBoundVec1Y->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditBoundVec1Y->SetColorText(0, 0, 0);
	SXParticlesEditor::EditBoundVec1Y->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditBoundVec1Y->SetTransparentTextBk(true);
	SXParticlesEditor::EditBoundVec1Y->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditBoundVec1Y->GAlign.left = true;
	SXParticlesEditor::EditBoundVec1Y->GAlign.top = true;
	SXParticlesEditor::EditBoundVec1Y->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditBoundVec1Y->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticBoundVec1Z = SXGUICrStatic("z:", 235, 40, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticBoundVec1Z->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticBoundVec1Z->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticBoundVec1Z->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticBoundVec1Z->SetTransparentTextBk(true);
	SXParticlesEditor::StaticBoundVec1Z->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticBoundVec1Z->GAlign.left = true;
	SXParticlesEditor::StaticBoundVec1Z->GAlign.top = true;
	SXParticlesEditor::EditBoundVec1Z = SXGUICrEdit("0", 245, 40, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditBoundVec1Z->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditBoundVec1Z->SetColorText(0, 0, 0);
	SXParticlesEditor::EditBoundVec1Z->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditBoundVec1Z->SetTransparentTextBk(true);
	SXParticlesEditor::EditBoundVec1Z->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditBoundVec1Z->GAlign.left = true;
	SXParticlesEditor::EditBoundVec1Z->GAlign.top = true;
	SXParticlesEditor::EditBoundVec1Z->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditBoundVec1Z->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticBoundVec1W = SXGUICrStatic("w:", 320, 40, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticBoundVec1W->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticBoundVec1W->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticBoundVec1W->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticBoundVec1W->SetTransparentTextBk(true);
	SXParticlesEditor::StaticBoundVec1W->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticBoundVec1W->GAlign.left = true;
	SXParticlesEditor::StaticBoundVec1W->GAlign.top = true;
	SXParticlesEditor::EditBoundVec1W = SXGUICrEdit("0", 330, 40, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditBoundVec1W->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditBoundVec1W->SetColorText(0, 0, 0);
	SXParticlesEditor::EditBoundVec1W->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditBoundVec1W->SetTransparentTextBk(true);
	SXParticlesEditor::EditBoundVec1W->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditBoundVec1W->GAlign.left = true;
	SXParticlesEditor::EditBoundVec1W->GAlign.top = true;
	SXParticlesEditor::EditBoundVec1W->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditBoundVec1W->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticBoundVec2 = SXGUICrStatic("Vector2:", 5, 60, 50, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticBoundVec2->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticBoundVec2->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticBoundVec2->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticBoundVec2->SetTransparentTextBk(true);
	SXParticlesEditor::StaticBoundVec2->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticBoundVec2->GAlign.left = true;
	SXParticlesEditor::StaticBoundVec2->GAlign.top = true;
	SXParticlesEditor::StaticBoundVec2X = SXGUICrStatic("x:", 60, 60, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticBoundVec2X->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticBoundVec2X->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticBoundVec2X->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticBoundVec2X->SetTransparentTextBk(true);
	SXParticlesEditor::StaticBoundVec2X->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticBoundVec2X->GAlign.left = true;
	SXParticlesEditor::StaticBoundVec2X->GAlign.top = true;
	SXParticlesEditor::EditBoundVec2X = SXGUICrEdit("0", 70, 60, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditBoundVec2X->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditBoundVec2X->SetColorText(0, 0, 0);
	SXParticlesEditor::EditBoundVec2X->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditBoundVec2X->SetTransparentTextBk(true);
	SXParticlesEditor::EditBoundVec2X->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditBoundVec2X->GAlign.left = true;
	SXParticlesEditor::EditBoundVec2X->GAlign.top = true;
	SXParticlesEditor::EditBoundVec2X->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditBoundVec2X->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticBoundVec2Y = SXGUICrStatic("y:", 150, 60, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticBoundVec2Y->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticBoundVec2Y->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticBoundVec2Y->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticBoundVec2Y->SetTransparentTextBk(true);
	SXParticlesEditor::StaticBoundVec2Y->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticBoundVec2Y->GAlign.left = true;
	SXParticlesEditor::StaticBoundVec2Y->GAlign.top = true;
	SXParticlesEditor::EditBoundVec2Y = SXGUICrEdit("0", 160, 60, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditBoundVec2Y->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditBoundVec2Y->SetColorText(0, 0, 0);
	SXParticlesEditor::EditBoundVec2Y->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditBoundVec2Y->SetTransparentTextBk(true);
	SXParticlesEditor::EditBoundVec2Y->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditBoundVec2Y->GAlign.left = true;
	SXParticlesEditor::EditBoundVec2Y->GAlign.top = true;
	SXParticlesEditor::EditBoundVec2Y->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditBoundVec2Y->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticBoundVec2Z = SXGUICrStatic("z:", 235, 60, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticBoundVec2Z->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticBoundVec2Z->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticBoundVec2Z->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticBoundVec2Z->SetTransparentTextBk(true);
	SXParticlesEditor::StaticBoundVec2Z->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticBoundVec2Z->GAlign.left = true;
	SXParticlesEditor::StaticBoundVec2Z->GAlign.top = true;
	SXParticlesEditor::EditBoundVec2Z = SXGUICrEdit("0", 245, 60, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditBoundVec2Z->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditBoundVec2Z->SetColorText(0, 0, 0);
	SXParticlesEditor::EditBoundVec2Z->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditBoundVec2Z->SetTransparentTextBk(true);
	SXParticlesEditor::EditBoundVec2Z->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditBoundVec2Z->GAlign.left = true;
	SXParticlesEditor::EditBoundVec2Z->GAlign.top = true;
	SXParticlesEditor::EditBoundVec2Z->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditBoundVec2Z->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticBoundVec2W = SXGUICrStatic("w:", 320, 60, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticBoundVec2W->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticBoundVec2W->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticBoundVec2W->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticBoundVec2W->SetTransparentTextBk(true);
	SXParticlesEditor::StaticBoundVec2W->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticBoundVec2W->GAlign.left = true;
	SXParticlesEditor::StaticBoundVec2W->GAlign.top = true;
	SXParticlesEditor::EditBoundVec2W = SXGUICrEdit("0", 330, 60, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditBoundVec2W->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditBoundVec2W->SetColorText(0, 0, 0);
	SXParticlesEditor::EditBoundVec2W->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditBoundVec2W->SetTransparentTextBk(true);
	SXParticlesEditor::EditBoundVec2W->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditBoundVec2W->GAlign.left = true;
	SXParticlesEditor::EditBoundVec2W->GAlign.top = true;
	SXParticlesEditor::EditBoundVec2W->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditBoundVec2W->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	//}

	//character
	//{
	SXParticlesEditor::CheckBoxCircle = SXGUICrCheckBox("Circle", 5, 10, 50, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxCircle->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxCircle->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxCircle->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxCircle->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxCircle->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxCircle->GAlign.left = true;
	SXParticlesEditor::CheckBoxCircle->GAlign.top = true;
	SXParticlesEditor::StaticCircleAxis = SXGUICrStatic("CircleAxis:", 5, 32, 50, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticCircleAxis->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticCircleAxis->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticCircleAxis->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticCircleAxis->SetTransparentTextBk(true);
	SXParticlesEditor::StaticCircleAxis->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticCircleAxis->GAlign.left = true;
	SXParticlesEditor::StaticCircleAxis->GAlign.top = true;
	SXParticlesEditor::ComboBoxCircleAxis = SXGUICrComboBox("", 60, 30, 100, 75, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::ComboBoxCircleAxis->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ComboBoxCircleAxis->SetColorText(0, 0, 0);
	SXParticlesEditor::ComboBoxCircleAxis->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::ComboBoxCircleAxis->SetTransparentTextBk(true);
	SXParticlesEditor::ComboBoxCircleAxis->SetColorBrush(255, 255, 255);
	SXParticlesEditor::ComboBoxCircleAxis->AddItem("x");
	SXParticlesEditor::ComboBoxCircleAxis->AddItem("y");
	SXParticlesEditor::ComboBoxCircleAxis->AddItem("z");
	SXParticlesEditor::ComboBoxCircleAxis->SetSel(0);
	SXParticlesEditor::ComboBoxCircleAxis->GAlign.left = true;
	SXParticlesEditor::ComboBoxCircleAxis->GAlign.top = true;
	SXParticlesEditor::StaticCircleAngle = SXGUICrStatic("CircleAngle:", 5, 55, 60, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticCircleAngle->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticCircleAngle->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticCircleAngle->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticCircleAngle->SetTransparentTextBk(true);
	SXParticlesEditor::StaticCircleAngle->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticCircleAngle->GAlign.left = true;
	SXParticlesEditor::StaticCircleAngle->GAlign.top = true;
	SXParticlesEditor::EditCircleAngle = SXGUICrEdit("0", 90, 55, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditCircleAngle->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditCircleAngle->SetColorText(0, 0, 0);
	SXParticlesEditor::EditCircleAngle->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditCircleAngle->SetTransparentTextBk(true);
	SXParticlesEditor::EditCircleAngle->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditCircleAngle->GAlign.left = true;
	SXParticlesEditor::EditCircleAngle->GAlign.top = true;
	SXParticlesEditor::EditCircleAngle->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditCircleAngle->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticCircleAngleDisp = SXGUICrStatic("CircleAngleDisp:", 6, 75, 80, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticCircleAngleDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticCircleAngleDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticCircleAngleDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticCircleAngleDisp->SetTransparentTextBk(true);
	SXParticlesEditor::StaticCircleAngleDisp->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticCircleAngleDisp->GAlign.left = true;
	SXParticlesEditor::StaticCircleAngleDisp->GAlign.top = true;
	SXParticlesEditor::EditCircleAngleDisp = SXGUICrEdit("0", 90, 75, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditCircleAngleDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditCircleAngleDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::EditCircleAngleDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditCircleAngleDisp->SetTransparentTextBk(true);
	SXParticlesEditor::EditCircleAngleDisp->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditCircleAngleDisp->GAlign.left = true;
	SXParticlesEditor::EditCircleAngleDisp->GAlign.top = true;
	SXParticlesEditor::EditCircleAngleDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditCircleAngleDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::CheckBoxRotate = SXGUICrCheckBox("Rotate", 175, 10, 50, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxRotate->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxRotate->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxRotate->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxRotate->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxRotate->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxRotate->GAlign.left = true;
	SXParticlesEditor::CheckBoxRotate->GAlign.top = true;
	SXParticlesEditor::StaticRotateAngle = SXGUICrStatic("RotateAngle:", 175, 30, 85, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticRotateAngle->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticRotateAngle->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticRotateAngle->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticRotateAngle->SetTransparentTextBk(true);
	SXParticlesEditor::StaticRotateAngle->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticRotateAngle->GAlign.left = true;
	SXParticlesEditor::StaticRotateAngle->GAlign.top = true;
	SXParticlesEditor::EditRotateAngle = SXGUICrEdit("0", 265, 30, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditRotateAngle->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditRotateAngle->SetColorText(0, 0, 0);
	SXParticlesEditor::EditRotateAngle->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditRotateAngle->SetTransparentTextBk(true);
	SXParticlesEditor::EditRotateAngle->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditRotateAngle->GAlign.left = true;
	SXParticlesEditor::EditRotateAngle->GAlign.top = true;
	SXParticlesEditor::EditRotateAngle->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditRotateAngle->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticRotateAngleDisp = SXGUICrStatic("RotateAngleDisp:", 175, 50, 85, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticRotateAngleDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticRotateAngleDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticRotateAngleDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticRotateAngleDisp->SetTransparentTextBk(true);
	SXParticlesEditor::StaticRotateAngleDisp->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticRotateAngleDisp->GAlign.left = true;
	SXParticlesEditor::StaticRotateAngleDisp->GAlign.top = true;
	SXParticlesEditor::CheckBoxCircleAngleDispNeg = SXGUICrCheckBox("CircleAngleDispNeg", 5, 95, 120, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxCircleAngleDispNeg->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxCircleAngleDispNeg->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxCircleAngleDispNeg->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxCircleAngleDispNeg->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxCircleAngleDispNeg->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxCircleAngleDispNeg->GAlign.left = true;
	SXParticlesEditor::CheckBoxCircleAngleDispNeg->GAlign.top = true;
	SXParticlesEditor::EditRotateAngleDisp = SXGUICrEdit("0", 265, 50, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditRotateAngleDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditRotateAngleDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::EditRotateAngleDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditRotateAngleDisp->SetTransparentTextBk(true);
	SXParticlesEditor::EditRotateAngleDisp->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditRotateAngleDisp->GAlign.left = true;
	SXParticlesEditor::EditRotateAngleDisp->GAlign.top = true;
	SXParticlesEditor::EditRotateAngleDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditRotateAngleDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::CheckBoxRotateAngleDispNeg = SXGUICrCheckBox("RotateAngleDispNeg", 175, 70, 120, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxRotateAngleDispNeg->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxRotateAngleDispNeg->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxRotateAngleDispNeg->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxRotateAngleDispNeg->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxRotateAngleDispNeg->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxRotateAngleDispNeg->GAlign.left = true;
	SXParticlesEditor::CheckBoxRotateAngleDispNeg->GAlign.top = true;
	SXParticlesEditor::CheckBoxDeviation = SXGUICrCheckBox("Deviation", 350, 10, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxDeviation->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxDeviation->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxDeviation->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxDeviation->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxDeviation->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxDeviation->GAlign.left = true;
	SXParticlesEditor::CheckBoxDeviation->GAlign.top = true;
	SXParticlesEditor::StaticDeviationType = SXGUICrStatic("DeviationType:", 350, 30, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticDeviationType->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticDeviationType->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticDeviationType->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticDeviationType->SetTransparentTextBk(true);
	SXParticlesEditor::StaticDeviationType->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticDeviationType->GAlign.left = true;
	SXParticlesEditor::StaticDeviationType->GAlign.top = true;
	SXParticlesEditor::ComboBoxDeviationType = SXGUICrComboBox("", 455, 25, 130, 75, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::ComboBoxDeviationType->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ComboBoxDeviationType->SetColorText(0, 0, 0);
	SXParticlesEditor::ComboBoxDeviationType->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::ComboBoxDeviationType->SetTransparentTextBk(true);
	SXParticlesEditor::ComboBoxDeviationType->SetColorBrush(255, 255, 255);
	SXParticlesEditor::ComboBoxDeviationType->AddItem("rnd");
	SXParticlesEditor::ComboBoxDeviationType->AddItem("along");
	SXParticlesEditor::ComboBoxDeviationType->AddItem("wave");
	SXParticlesEditor::ComboBoxDeviationType->SetSel(0);
	SXParticlesEditor::ComboBoxDeviationType->GAlign.left = true;
	SXParticlesEditor::ComboBoxDeviationType->GAlign.top = true;
	SXParticlesEditor::StaticDeviationAmplitude = SXGUICrStatic("DeviationAmplitude:", 350, 50, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticDeviationAmplitude->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticDeviationAmplitude->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticDeviationAmplitude->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticDeviationAmplitude->SetTransparentTextBk(true);
	SXParticlesEditor::StaticDeviationAmplitude->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticDeviationAmplitude->GAlign.left = true;
	SXParticlesEditor::StaticDeviationAmplitude->GAlign.top = true;
	SXParticlesEditor::StaticDeviationCoefAngle = SXGUICrStatic("DeviationCoefAngle:", 350, 70, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticDeviationCoefAngle->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticDeviationCoefAngle->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticDeviationCoefAngle->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticDeviationCoefAngle->SetTransparentTextBk(true);
	SXParticlesEditor::StaticDeviationCoefAngle->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticDeviationCoefAngle->GAlign.left = true;
	SXParticlesEditor::StaticDeviationCoefAngle->GAlign.top = true;
	SXParticlesEditor::EditDeviationAmplitude = SXGUICrEdit("0", 490, 50, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditDeviationAmplitude->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditDeviationAmplitude->SetColorText(0, 0, 0);
	SXParticlesEditor::EditDeviationAmplitude->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditDeviationAmplitude->SetTransparentTextBk(true);
	SXParticlesEditor::EditDeviationAmplitude->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditDeviationAmplitude->GAlign.left = true;
	SXParticlesEditor::EditDeviationAmplitude->GAlign.top = true;
	SXParticlesEditor::EditDeviationAmplitude->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditDeviationAmplitude->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::EditDeviationCoefAngle = SXGUICrEdit("0", 490, 70, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditDeviationCoefAngle->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditDeviationCoefAngle->SetColorText(0, 0, 0);
	SXParticlesEditor::EditDeviationCoefAngle->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditDeviationCoefAngle->SetTransparentTextBk(true);
	SXParticlesEditor::EditDeviationCoefAngle->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditDeviationCoefAngle->GAlign.left = true;
	SXParticlesEditor::EditDeviationCoefAngle->GAlign.top = true;
	SXParticlesEditor::EditDeviationCoefAngle->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditDeviationCoefAngle->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticDeviationAxis = SXGUICrStatic("DeviationAxis:", 590, 25, 80, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticDeviationAxis->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticDeviationAxis->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticDeviationAxis->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticDeviationAxis->SetTransparentTextBk(true);
	SXParticlesEditor::StaticDeviationAxis->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticDeviationAxis->GAlign.left = true;
	SXParticlesEditor::StaticDeviationAxis->GAlign.top = true;
	SXParticlesEditor::ComboBoxDeviationAxis = SXGUICrComboBox("", 665, 20, 130, 75, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::ComboBoxDeviationAxis->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ComboBoxDeviationAxis->SetColorText(0, 0, 0);
	SXParticlesEditor::ComboBoxDeviationAxis->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::ComboBoxDeviationAxis->SetTransparentTextBk(true);
	SXParticlesEditor::ComboBoxDeviationAxis->SetColorBrush(255, 255, 255);
	SXParticlesEditor::ComboBoxDeviationAxis->AddItem("x");
	SXParticlesEditor::ComboBoxDeviationAxis->AddItem("y");
	SXParticlesEditor::ComboBoxDeviationAxis->AddItem("z");
	SXParticlesEditor::ComboBoxDeviationAxis->SetSel(0);
	SXParticlesEditor::ComboBoxDeviationAxis->GAlign.left = true;
	SXParticlesEditor::ComboBoxDeviationAxis->GAlign.top = true;
	SXParticlesEditor::StaticDeviationCountDelayMls = SXGUICrStatic("DeviationCountDelayMls:", 590, 45, 120, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticDeviationCountDelayMls->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticDeviationCountDelayMls->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticDeviationCountDelayMls->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticDeviationCountDelayMls->SetTransparentTextBk(true);
	SXParticlesEditor::StaticDeviationCountDelayMls->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticDeviationCountDelayMls->GAlign.left = true;
	SXParticlesEditor::StaticDeviationCountDelayMls->GAlign.top = true;
	SXParticlesEditor::EditDeviationCountDelayMls = SXGUICrEdit("0", 715, 45, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditDeviationCountDelayMls->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditDeviationCountDelayMls->SetColorText(0, 0, 0);
	SXParticlesEditor::EditDeviationCountDelayMls->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditDeviationCountDelayMls->SetTransparentTextBk(true);
	SXParticlesEditor::EditDeviationCountDelayMls->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditDeviationCountDelayMls->GAlign.left = true;
	SXParticlesEditor::EditDeviationCountDelayMls->GAlign.top = true;
	SXParticlesEditor::EditDeviationCountDelayMls->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditDeviationCountDelayMls->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticDeviationCoefAngleDisp = SXGUICrStatic("DeviationCoefAngleDisp:", 350, 90, 120, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticDeviationCoefAngleDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticDeviationCoefAngleDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticDeviationCoefAngleDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticDeviationCoefAngleDisp->SetTransparentTextBk(true);
	SXParticlesEditor::StaticDeviationCoefAngleDisp->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticDeviationCoefAngleDisp->GAlign.left = true;
	SXParticlesEditor::StaticDeviationCoefAngleDisp->GAlign.top = true;
	SXParticlesEditor::EditDeviationCoefAngleDisp = SXGUICrEdit("0", 490, 90, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditDeviationCoefAngleDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditDeviationCoefAngleDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::EditDeviationCoefAngleDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditDeviationCoefAngleDisp->SetTransparentTextBk(true);
	SXParticlesEditor::EditDeviationCoefAngleDisp->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditDeviationCoefAngleDisp->GAlign.left = true;
	SXParticlesEditor::EditDeviationCoefAngleDisp->GAlign.top = true;
	SXParticlesEditor::EditDeviationCoefAngleDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditDeviationCoefAngleDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::CheckBoxDeviationCoefAngleDispNeg = SXGUICrCheckBox("DeviationCoefAngleDispNeg", 350, 110, 160, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxDeviationCoefAngleDispNeg->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxDeviationCoefAngleDispNeg->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxDeviationCoefAngleDispNeg->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxDeviationCoefAngleDispNeg->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxDeviationCoefAngleDispNeg->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxDeviationCoefAngleDispNeg->GAlign.left = true;
	SXParticlesEditor::CheckBoxDeviationCoefAngleDispNeg->GAlign.top = true;
	SXParticlesEditor::CheckBoxDeviationTapX = SXGUICrCheckBox("DeviationTapX", 590, 65, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxDeviationTapX->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxDeviationTapX->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxDeviationTapX->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxDeviationTapX->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxDeviationTapX->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxDeviationTapX->GAlign.left = true;
	SXParticlesEditor::CheckBoxDeviationTapX->GAlign.top = true;
	SXParticlesEditor::CheckBoxDeviationTapY = SXGUICrCheckBox("DeviationTapY", 590, 85, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxDeviationTapY->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxDeviationTapY->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxDeviationTapY->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxDeviationTapY->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxDeviationTapY->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxDeviationTapY->GAlign.left = true;
	SXParticlesEditor::CheckBoxDeviationTapY->GAlign.top = true;
	SXParticlesEditor::CheckBoxDeviationTapZ = SXGUICrCheckBox("DeviationTapZ", 590, 105, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxDeviationTapZ->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxDeviationTapZ->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxDeviationTapZ->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxDeviationTapZ->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxDeviationTapZ->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxDeviationTapZ->GAlign.left = true;
	SXParticlesEditor::CheckBoxDeviationTapZ->GAlign.top = true;
	//}

	//spawn
	//{
	SXParticlesEditor::StaticSpawnPosType = SXGUICrStatic("SpawnPosType:", 5, 12, 80, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSpawnPosType->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSpawnPosType->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSpawnPosType->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSpawnPosType->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSpawnPosType->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSpawnPosType->GAlign.left = true;
	SXParticlesEditor::StaticSpawnPosType->GAlign.top = true;
	SXParticlesEditor::ComboBoxSpawnPosType = SXGUICrComboBox("", 90, 10, 140, 75, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::ComboBoxSpawnPosType->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ComboBoxSpawnPosType->SetColorText(0, 0, 0);
	SXParticlesEditor::ComboBoxSpawnPosType->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::ComboBoxSpawnPosType->SetTransparentTextBk(true);
	SXParticlesEditor::ComboBoxSpawnPosType->SetColorBrush(255, 255, 255);
	SXParticlesEditor::ComboBoxSpawnPosType->AddItem("strictly");
	SXParticlesEditor::ComboBoxSpawnPosType->AddItem("bound");
	SXParticlesEditor::ComboBoxSpawnPosType->SetSel(0);
	SXParticlesEditor::ComboBoxSpawnPosType->GAlign.left = true;
	SXParticlesEditor::ComboBoxSpawnPosType->GAlign.top = true;
	SXParticlesEditor::StaticSpawnOrigin = SXGUICrStatic("SpawnOrigin:", 5, 40, 80, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSpawnOrigin->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSpawnOrigin->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSpawnOrigin->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSpawnOrigin->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSpawnOrigin->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSpawnOrigin->GAlign.left = true;
	SXParticlesEditor::StaticSpawnOrigin->GAlign.top = true;
	SXParticlesEditor::StaticSpawnOriginX = SXGUICrStatic("x:", 90, 40, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSpawnOriginX->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSpawnOriginX->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSpawnOriginX->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSpawnOriginX->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSpawnOriginX->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSpawnOriginX->GAlign.left = true;
	SXParticlesEditor::StaticSpawnOriginX->GAlign.top = true;
	SXParticlesEditor::EditSpawnOriginX = SXGUICrEdit("0", 100, 40, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditSpawnOriginX->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditSpawnOriginX->SetColorText(0, 0, 0);
	SXParticlesEditor::EditSpawnOriginX->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditSpawnOriginX->SetTransparentTextBk(true);
	SXParticlesEditor::EditSpawnOriginX->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditSpawnOriginX->GAlign.left = true;
	SXParticlesEditor::EditSpawnOriginX->GAlign.top = true;
	SXParticlesEditor::EditSpawnOriginX->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditSpawnOriginX->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticSpawnOriginY = SXGUICrStatic("y:", 180, 40, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSpawnOriginY->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSpawnOriginY->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSpawnOriginY->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSpawnOriginY->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSpawnOriginY->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSpawnOriginY->GAlign.left = true;
	SXParticlesEditor::StaticSpawnOriginY->GAlign.top = true;
	SXParticlesEditor::EditSpawnOriginY = SXGUICrEdit("0", 190, 40, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditSpawnOriginY->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditSpawnOriginY->SetColorText(0, 0, 0);
	SXParticlesEditor::EditSpawnOriginY->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditSpawnOriginY->SetTransparentTextBk(true);
	SXParticlesEditor::EditSpawnOriginY->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditSpawnOriginY->GAlign.left = true;
	SXParticlesEditor::EditSpawnOriginY->GAlign.top = true;
	SXParticlesEditor::EditSpawnOriginY->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditSpawnOriginY->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticSpawnOriginZ = SXGUICrStatic("z:", 270, 40, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSpawnOriginZ->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSpawnOriginZ->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSpawnOriginZ->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSpawnOriginZ->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSpawnOriginZ->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSpawnOriginZ->GAlign.left = true;
	SXParticlesEditor::StaticSpawnOriginZ->GAlign.top = true;
	SXParticlesEditor::EditSpawnOriginZ = SXGUICrEdit("0", 280, 40, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditSpawnOriginZ->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditSpawnOriginZ->SetColorText(0, 0, 0);
	SXParticlesEditor::EditSpawnOriginZ->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditSpawnOriginZ->SetTransparentTextBk(true);
	SXParticlesEditor::EditSpawnOriginZ->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditSpawnOriginZ->GAlign.left = true;
	SXParticlesEditor::EditSpawnOriginZ->GAlign.top = true;
	SXParticlesEditor::EditSpawnOriginZ->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditSpawnOriginZ->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticSpawnOriginDisp = SXGUICrStatic("SpawnOriginDisp:", 370, 40, 85, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSpawnOriginDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSpawnOriginDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSpawnOriginDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSpawnOriginDisp->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSpawnOriginDisp->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSpawnOriginDisp->GAlign.left = true;
	SXParticlesEditor::StaticSpawnOriginDisp->GAlign.top = true;
	SXParticlesEditor::EditSpawnOriginDisp = SXGUICrEdit("0", 455, 40, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditSpawnOriginDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditSpawnOriginDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::EditSpawnOriginDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditSpawnOriginDisp->SetTransparentTextBk(true);
	SXParticlesEditor::EditSpawnOriginDisp->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditSpawnOriginDisp->GAlign.left = true;
	SXParticlesEditor::EditSpawnOriginDisp->GAlign.top = true;
	SXParticlesEditor::EditSpawnOriginDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditSpawnOriginDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::CheckBoxSpawnOriginDispXPos = SXGUICrCheckBox("x+", 90, 60, 30, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxSpawnOriginDispXPos->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxSpawnOriginDispXPos->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxSpawnOriginDispXPos->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxSpawnOriginDispXPos->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxSpawnOriginDispXPos->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxSpawnOriginDispXPos->GAlign.left = true;
	SXParticlesEditor::CheckBoxSpawnOriginDispXPos->GAlign.top = true;
	SXParticlesEditor::CheckBoxSpawnOriginDispXNeg = SXGUICrCheckBox("x-", 140, 60, 30, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxSpawnOriginDispXNeg->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxSpawnOriginDispXNeg->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxSpawnOriginDispXNeg->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxSpawnOriginDispXNeg->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxSpawnOriginDispXNeg->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxSpawnOriginDispXNeg->GAlign.left = true;
	SXParticlesEditor::CheckBoxSpawnOriginDispXNeg->GAlign.top = true;
	SXParticlesEditor::CheckBoxSpawnOriginDispYPos = SXGUICrCheckBox("y+", 180, 60, 30, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxSpawnOriginDispYPos->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxSpawnOriginDispYPos->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxSpawnOriginDispYPos->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxSpawnOriginDispYPos->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxSpawnOriginDispYPos->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxSpawnOriginDispYPos->GAlign.left = true;
	SXParticlesEditor::CheckBoxSpawnOriginDispYPos->GAlign.top = true;
	SXParticlesEditor::CheckBoxSpawnOriginDispYNeg = SXGUICrCheckBox("y-", 230, 60, 30, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxSpawnOriginDispYNeg->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxSpawnOriginDispYNeg->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxSpawnOriginDispYNeg->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxSpawnOriginDispYNeg->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxSpawnOriginDispYNeg->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxSpawnOriginDispYNeg->GAlign.left = true;
	SXParticlesEditor::CheckBoxSpawnOriginDispYNeg->GAlign.top = true;
	SXParticlesEditor::CheckBoxSpawnOriginDispZPos = SXGUICrCheckBox("z+", 270, 60, 30, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxSpawnOriginDispZPos->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxSpawnOriginDispZPos->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxSpawnOriginDispZPos->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxSpawnOriginDispZPos->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxSpawnOriginDispZPos->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxSpawnOriginDispZPos->GAlign.left = true;
	SXParticlesEditor::CheckBoxSpawnOriginDispZPos->GAlign.top = true;
	SXParticlesEditor::CheckBoxSpawnOriginDispZNeg = SXGUICrCheckBox("z-", 320, 59, 30, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxSpawnOriginDispZNeg->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxSpawnOriginDispZNeg->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxSpawnOriginDispZNeg->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxSpawnOriginDispZNeg->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxSpawnOriginDispZNeg->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxSpawnOriginDispZNeg->GAlign.left = true;
	SXParticlesEditor::CheckBoxSpawnOriginDispZNeg->GAlign.top = true;
	SXParticlesEditor::StaticSpawnNextTime = SXGUICrStatic("SpawnNextTime:", 5, 90, 80, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSpawnNextTime->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSpawnNextTime->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSpawnNextTime->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSpawnNextTime->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSpawnNextTime->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSpawnNextTime->GAlign.left = true;
	SXParticlesEditor::StaticSpawnNextTime->GAlign.top = true;
	SXParticlesEditor::EditSpawnNextTime = SXGUICrEdit("0", 90, 90, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditSpawnNextTime->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditSpawnNextTime->SetColorText(0, 0, 0);
	SXParticlesEditor::EditSpawnNextTime->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditSpawnNextTime->SetTransparentTextBk(true);
	SXParticlesEditor::EditSpawnNextTime->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditSpawnNextTime->GAlign.left = true;
	SXParticlesEditor::EditSpawnNextTime->GAlign.top = true;
	SXParticlesEditor::EditSpawnNextTime->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditSpawnNextTime->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticSpawnNextTimeDisp = SXGUICrStatic("SpawnNextTimeDisp:", 175, 90, 105, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticSpawnNextTimeDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticSpawnNextTimeDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticSpawnNextTimeDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticSpawnNextTimeDisp->SetTransparentTextBk(true);
	SXParticlesEditor::StaticSpawnNextTimeDisp->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticSpawnNextTimeDisp->GAlign.left = true;
	SXParticlesEditor::StaticSpawnNextTimeDisp->GAlign.top = true;
	SXParticlesEditor::EditSpawnNextTimeDisp = SXGUICrEdit("0", 280, 90, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditSpawnNextTimeDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditSpawnNextTimeDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::EditSpawnNextTimeDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditSpawnNextTimeDisp->SetTransparentTextBk(true);
	SXParticlesEditor::EditSpawnNextTimeDisp->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditSpawnNextTimeDisp->GAlign.left = true;
	SXParticlesEditor::EditSpawnNextTimeDisp->GAlign.top = true;
	SXParticlesEditor::EditSpawnNextTimeDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditSpawnNextTimeDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	//}

	//tex
	//{
	SXParticlesEditor::StaticTexture = SXGUICrStatic("Texture:", 5, 10, 50, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticTexture->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticTexture->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticTexture->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticTexture->SetTransparentTextBk(true);
	SXParticlesEditor::StaticTexture->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticTexture->GAlign.left = true;
	SXParticlesEditor::StaticTexture->GAlign.top = true;
	SXParticlesEditor::EditTexture = SXGUICrEdit("0", 60, 10, 290, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditTexture->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditTexture->SetColorText(0, 0, 0);
	SXParticlesEditor::EditTexture->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditTexture->SetTransparentTextBk(true);
	SXParticlesEditor::EditTexture->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditTexture->GAlign.left = true;
	SXParticlesEditor::EditTexture->GAlign.top = true;
	SXParticlesEditor::EditTexture->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditTexture->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);


	SXParticlesEditor::ButtonTextureSel = SXGUICrButton("...", 355, 10, 25, 15, 0, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::ButtonTextureSel->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::ButtonTextureSel->GAlign.left = true;
	SXParticlesEditor::ButtonTextureSel->GAlign.top = true;
	SXParticlesEditor::ButtonTextureSel->AddHandler(SXParticlesEditor_ButtonTextureSel_Click, WM_LBUTTONUP);

	SXParticlesEditor::StaticAnimTexCountCadrsX = SXGUICrStatic("AnimTexCountCadrsX:", 5, 35, 110, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticAnimTexCountCadrsX->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticAnimTexCountCadrsX->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticAnimTexCountCadrsX->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticAnimTexCountCadrsX->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAnimTexCountCadrsX->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticAnimTexCountCadrsX->GAlign.left = true;
	SXParticlesEditor::StaticAnimTexCountCadrsX->GAlign.top = true;
	SXParticlesEditor::StaticAnimTexCountCadrsY = SXGUICrStatic("AnimTexCountCadrsY:", 200, 35, 110, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticAnimTexCountCadrsY->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticAnimTexCountCadrsY->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticAnimTexCountCadrsY->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticAnimTexCountCadrsY->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAnimTexCountCadrsY->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticAnimTexCountCadrsY->GAlign.left = true;
	SXParticlesEditor::StaticAnimTexCountCadrsY->GAlign.top = true;
	SXParticlesEditor::EditAnimTexCountCadrsX = SXGUICrEdit("0", 115, 35, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditAnimTexCountCadrsX->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditAnimTexCountCadrsX->SetColorText(0, 0, 0);
	SXParticlesEditor::EditAnimTexCountCadrsX->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditAnimTexCountCadrsX->SetTransparentTextBk(true);
	SXParticlesEditor::EditAnimTexCountCadrsX->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditAnimTexCountCadrsX->GAlign.left = true;
	SXParticlesEditor::EditAnimTexCountCadrsX->GAlign.top = true;
	SXParticlesEditor::EditAnimTexCountCadrsX->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditAnimTexCountCadrsX->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::EditAnimTexCountCadrsY = SXGUICrEdit("0", 310, 35, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditAnimTexCountCadrsY->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditAnimTexCountCadrsY->SetColorText(0, 0, 0);
	SXParticlesEditor::EditAnimTexCountCadrsY->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditAnimTexCountCadrsY->SetTransparentTextBk(true);
	SXParticlesEditor::EditAnimTexCountCadrsY->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditAnimTexCountCadrsY->GAlign.left = true;
	SXParticlesEditor::EditAnimTexCountCadrsY->GAlign.top = true;
	SXParticlesEditor::EditAnimTexCountCadrsY->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditAnimTexCountCadrsY->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticAnimTexRate = SXGUICrStatic("AnimTexRate:", 5, 55, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticAnimTexRate->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticAnimTexRate->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticAnimTexRate->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticAnimTexRate->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAnimTexRate->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticAnimTexRate->GAlign.left = true;
	SXParticlesEditor::StaticAnimTexRate->GAlign.top = true;
	SXParticlesEditor::EditAnimTexRate = SXGUICrEdit("0", 115, 55, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditAnimTexRate->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditAnimTexRate->SetColorText(0, 0, 0);
	SXParticlesEditor::EditAnimTexRate->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditAnimTexRate->SetTransparentTextBk(true);
	SXParticlesEditor::EditAnimTexRate->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditAnimTexRate->GAlign.left = true;
	SXParticlesEditor::EditAnimTexRate->GAlign.top = true;
	SXParticlesEditor::EditAnimTexRate->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditAnimTexRate->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticAnimTexRateDisp = SXGUICrStatic("AnimTexRateDisp:", 200, 55, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticAnimTexRateDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticAnimTexRateDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticAnimTexRateDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticAnimTexRateDisp->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAnimTexRateDisp->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticAnimTexRateDisp->GAlign.left = true;
	SXParticlesEditor::StaticAnimTexRateDisp->GAlign.top = true;
	SXParticlesEditor::EditAnimTexRateDisp = SXGUICrEdit("0", 310, 55, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditAnimTexRateDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditAnimTexRateDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::EditAnimTexRateDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditAnimTexRateDisp->SetTransparentTextBk(true);
	SXParticlesEditor::EditAnimTexRateDisp->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditAnimTexRateDisp->GAlign.left = true;
	SXParticlesEditor::EditAnimTexRateDisp->GAlign.top = true;
	SXParticlesEditor::EditAnimTexRateDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditAnimTexRateDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticAnimTexStartCadr = SXGUICrStatic("AnimTexStartCadr:", 5, 75, 100, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticAnimTexStartCadr->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticAnimTexStartCadr->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticAnimTexStartCadr->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticAnimTexStartCadr->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAnimTexStartCadr->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticAnimTexStartCadr->GAlign.left = true;
	SXParticlesEditor::StaticAnimTexStartCadr->GAlign.top = true;
	SXParticlesEditor::EditAnimTexStartCadr = SXGUICrEdit("0", 115, 75, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditAnimTexStartCadr->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditAnimTexStartCadr->SetColorText(0, 0, 0);
	SXParticlesEditor::EditAnimTexStartCadr->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditAnimTexStartCadr->SetTransparentTextBk(true);
	SXParticlesEditor::EditAnimTexStartCadr->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditAnimTexStartCadr->GAlign.left = true;
	SXParticlesEditor::EditAnimTexStartCadr->GAlign.top = true;
	SXParticlesEditor::EditAnimTexStartCadr->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditAnimTexStartCadr->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticAnimTexStartCadrDisp = SXGUICrStatic("AnimTexStartCadrDisp:", 200, 75, 110, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticAnimTexStartCadrDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticAnimTexStartCadrDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticAnimTexStartCadrDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticAnimTexStartCadrDisp->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAnimTexStartCadrDisp->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticAnimTexStartCadrDisp->GAlign.left = true;
	SXParticlesEditor::StaticAnimTexStartCadrDisp->GAlign.top = true;
	SXParticlesEditor::EditAnimTexStartCadrDisp = SXGUICrEdit("0", 310, 75, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditAnimTexStartCadrDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditAnimTexStartCadrDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::EditAnimTexStartCadrDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditAnimTexStartCadrDisp->SetTransparentTextBk(true);
	SXParticlesEditor::EditAnimTexStartCadrDisp->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditAnimTexStartCadrDisp->GAlign.left = true;
	SXParticlesEditor::EditAnimTexStartCadrDisp->GAlign.top = true;
	SXParticlesEditor::EditAnimTexStartCadrDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditAnimTexStartCadrDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	//}

	//velocity/acceleration
	//{
	SXParticlesEditor::StaticVelocity = SXGUICrStatic("Velocity:", 5, 15, 50, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticVelocity->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticVelocity->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticVelocity->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticVelocity->SetTransparentTextBk(true);
	SXParticlesEditor::StaticVelocity->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticVelocity->GAlign.left = true;
	SXParticlesEditor::StaticVelocity->GAlign.top = true;
	SXParticlesEditor::StaticVelocityX = SXGUICrStatic("x:", 80, 15, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticVelocityX->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticVelocityX->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticVelocityX->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticVelocityX->SetTransparentTextBk(true);
	SXParticlesEditor::StaticVelocityX->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticVelocityX->GAlign.left = true;
	SXParticlesEditor::StaticVelocityX->GAlign.top = true;
	SXParticlesEditor::EditVelocityX = SXGUICrEdit("0", 90, 15, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditVelocityX->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditVelocityX->SetColorText(0, 0, 0);
	SXParticlesEditor::EditVelocityX->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditVelocityX->SetTransparentTextBk(true);
	SXParticlesEditor::EditVelocityX->SetColorBrush(250, 250, 250);
	SXParticlesEditor::EditVelocityX->GAlign.left = true;
	SXParticlesEditor::EditVelocityX->GAlign.top = true;
	SXParticlesEditor::EditVelocityX->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditVelocityX->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticVelocityY = SXGUICrStatic("y:", 170, 15, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticVelocityY->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticVelocityY->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticVelocityY->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticVelocityY->SetTransparentTextBk(true);
	SXParticlesEditor::StaticVelocityY->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticVelocityY->GAlign.left = true;
	SXParticlesEditor::StaticVelocityY->GAlign.top = true;
	SXParticlesEditor::EditVelocityY = SXGUICrEdit("0", 180, 15, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditVelocityY->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditVelocityY->SetColorText(0, 0, 0);
	SXParticlesEditor::EditVelocityY->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditVelocityY->SetTransparentTextBk(true);
	SXParticlesEditor::EditVelocityY->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditVelocityY->GAlign.left = true;
	SXParticlesEditor::EditVelocityY->GAlign.top = true;
	SXParticlesEditor::EditVelocityY->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditVelocityY->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::CheckBoxVelocityDispXNeg = SXGUICrCheckBox("XDispNeg", 80, 35, 80, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxVelocityDispXNeg->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxVelocityDispXNeg->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxVelocityDispXNeg->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxVelocityDispXNeg->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxVelocityDispXNeg->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxVelocityDispXNeg->GAlign.left = true;
	SXParticlesEditor::CheckBoxVelocityDispXNeg->GAlign.top = true;
	SXParticlesEditor::StaticVelocityZ = SXGUICrStatic("z:", 260, 15, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticVelocityZ->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticVelocityZ->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticVelocityZ->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticVelocityZ->SetTransparentTextBk(true);
	SXParticlesEditor::StaticVelocityZ->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticVelocityZ->GAlign.left = true;
	SXParticlesEditor::StaticVelocityZ->GAlign.top = true;
	SXParticlesEditor::EditVelocityZ = SXGUICrEdit("0", 270, 15, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditVelocityZ->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditVelocityZ->SetColorText(0, 0, 0);
	SXParticlesEditor::EditVelocityZ->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditVelocityZ->SetTransparentTextBk(true);
	SXParticlesEditor::EditVelocityZ->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditVelocityZ->GAlign.left = true;
	SXParticlesEditor::EditVelocityZ->GAlign.top = true;
	SXParticlesEditor::EditVelocityZ->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditVelocityZ->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticVelocityDisp = SXGUICrStatic("Dispersion:", 355, 15, 60, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticVelocityDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticVelocityDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticVelocityDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticVelocityDisp->SetTransparentTextBk(true);
	SXParticlesEditor::StaticVelocityDisp->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticVelocityDisp->GAlign.left = true;
	SXParticlesEditor::StaticVelocityDisp->GAlign.top = true;
	SXParticlesEditor::EditVelocityDisp = SXGUICrEdit("0", 420, 15, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditVelocityDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditVelocityDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::EditVelocityDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditVelocityDisp->SetTransparentTextBk(true);
	SXParticlesEditor::EditVelocityDisp->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditVelocityDisp->GAlign.left = true;
	SXParticlesEditor::EditVelocityDisp->GAlign.top = true;
	SXParticlesEditor::EditVelocityDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditVelocityDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::CheckBoxVelocityDispYNeg = SXGUICrCheckBox("YDispNeg", 170, 35, 80, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxVelocityDispYNeg->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxVelocityDispYNeg->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxVelocityDispYNeg->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxVelocityDispYNeg->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxVelocityDispYNeg->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxVelocityDispYNeg->GAlign.left = true;
	SXParticlesEditor::CheckBoxVelocityDispYNeg->GAlign.top = true;
	SXParticlesEditor::CheckBoxVelocityDispZNeg = SXGUICrCheckBox("ZDispNeg", 260, 35, 80, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxVelocityDispZNeg->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxVelocityDispZNeg->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxVelocityDispZNeg->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxVelocityDispZNeg->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxVelocityDispZNeg->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxVelocityDispZNeg->GAlign.left = true;
	SXParticlesEditor::CheckBoxVelocityDispZNeg->GAlign.top = true;
	SXParticlesEditor::StaticAcceleration = SXGUICrStatic("Acceleration:", 5, 65, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticAcceleration->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticAcceleration->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticAcceleration->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticAcceleration->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAcceleration->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticAcceleration->GAlign.left = true;
	SXParticlesEditor::StaticAcceleration->GAlign.top = true;
	SXParticlesEditor::StaticAccelerationX = SXGUICrStatic("x:", 80, 65, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticAccelerationX->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticAccelerationX->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticAccelerationX->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticAccelerationX->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAccelerationX->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticAccelerationX->GAlign.left = true;
	SXParticlesEditor::StaticAccelerationX->GAlign.top = true;
	SXParticlesEditor::EditAccelerationX = SXGUICrEdit("0", 90, 65, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditAccelerationX->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditAccelerationX->SetColorText(0, 0, 0);
	SXParticlesEditor::EditAccelerationX->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditAccelerationX->SetTransparentTextBk(true);
	SXParticlesEditor::EditAccelerationX->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditAccelerationX->GAlign.left = true;
	SXParticlesEditor::EditAccelerationX->GAlign.top = true;
	SXParticlesEditor::EditAccelerationX->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditAccelerationX->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticAccelerationY = SXGUICrStatic("y:", 170, 65, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticAccelerationY->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticAccelerationY->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticAccelerationY->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticAccelerationY->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAccelerationY->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticAccelerationY->GAlign.left = true;
	SXParticlesEditor::StaticAccelerationY->GAlign.top = true;
	SXParticlesEditor::EditAccelerationY = SXGUICrEdit("0", 180, 65, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditAccelerationY->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditAccelerationY->SetColorText(0, 0, 0);
	SXParticlesEditor::EditAccelerationY->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditAccelerationY->SetTransparentTextBk(true);
	SXParticlesEditor::EditAccelerationY->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditAccelerationY->GAlign.left = true;
	SXParticlesEditor::EditAccelerationY->GAlign.top = true;
	SXParticlesEditor::EditAccelerationY->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditAccelerationY->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticAccelerationZ = SXGUICrStatic("z:", 260, 65, 10, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticAccelerationZ->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticAccelerationZ->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticAccelerationZ->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticAccelerationZ->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAccelerationZ->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticAccelerationZ->GAlign.left = true;
	SXParticlesEditor::StaticAccelerationZ->GAlign.top = true;
	SXParticlesEditor::EditAccelerationZ = SXGUICrEdit("0", 270, 65, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditAccelerationZ->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditAccelerationZ->SetColorText(0, 0, 0);
	SXParticlesEditor::EditAccelerationZ->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditAccelerationZ->SetTransparentTextBk(true);
	SXParticlesEditor::EditAccelerationZ->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditAccelerationZ->GAlign.left = true;
	SXParticlesEditor::EditAccelerationZ->GAlign.top = true;
	SXParticlesEditor::EditAccelerationZ->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditAccelerationZ->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::StaticAccelerationDisp = SXGUICrStatic("Dispersion:", 355, 65, 60, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::StaticAccelerationDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::StaticAccelerationDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::StaticAccelerationDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::StaticAccelerationDisp->SetTransparentTextBk(true);
	SXParticlesEditor::StaticAccelerationDisp->SetColorBrush(220, 220, 220);
	SXParticlesEditor::StaticAccelerationDisp->GAlign.left = true;
	SXParticlesEditor::StaticAccelerationDisp->GAlign.top = true;
	SXParticlesEditor::EditAccelerationDisp = SXGUICrEdit("0", 420, 65, 70, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0);
	SXParticlesEditor::EditAccelerationDisp->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::EditAccelerationDisp->SetColorText(0, 0, 0);
	SXParticlesEditor::EditAccelerationDisp->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::EditAccelerationDisp->SetTransparentTextBk(true);
	SXParticlesEditor::EditAccelerationDisp->SetColorBrush(255, 255, 255);
	SXParticlesEditor::EditAccelerationDisp->GAlign.left = true;
	SXParticlesEditor::EditAccelerationDisp->GAlign.top = true;
	SXParticlesEditor::EditAccelerationDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KEYDOWN, VK_RETURN, 1, 0, 0, 0);
	SXParticlesEditor::EditAccelerationDisp->AddHandler(SXParticlesEditor_Edits_Enter, WM_KILLFOCUS);

	SXParticlesEditor::CheckBoxAccelerationDispXNeg = SXGUICrCheckBox("XDispNeg", 80, 85, 80, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxAccelerationDispXNeg->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxAccelerationDispXNeg->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxAccelerationDispXNeg->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxAccelerationDispXNeg->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxAccelerationDispXNeg->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxAccelerationDispXNeg->GAlign.left = true;
	SXParticlesEditor::CheckBoxAccelerationDispXNeg->GAlign.top = true;
	SXParticlesEditor::CheckBoxAccelerationDispYNeg = SXGUICrCheckBox("YDispNeg", 170, 85, 80, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxAccelerationDispYNeg->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxAccelerationDispYNeg->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxAccelerationDispYNeg->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxAccelerationDispYNeg->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxAccelerationDispYNeg->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxAccelerationDispYNeg->GAlign.left = true;
	SXParticlesEditor::CheckBoxAccelerationDispYNeg->GAlign.top = true;
	SXParticlesEditor::CheckBoxAccelerationDispZNeg = SXGUICrCheckBox("ZDispNeg", 260, 85, 80, 15, SXParticlesEditor::GroupBoxData2->GetHWND(), 0, 0, false);
	SXParticlesEditor::CheckBoxAccelerationDispZNeg->SetFont("MS Shell Dlg", -11, 0, 400, 0, 0, 0);
	SXParticlesEditor::CheckBoxAccelerationDispZNeg->SetColorText(0, 0, 0);
	SXParticlesEditor::CheckBoxAccelerationDispZNeg->SetColorTextBk(255, 255, 255);
	SXParticlesEditor::CheckBoxAccelerationDispZNeg->SetTransparentTextBk(true);
	SXParticlesEditor::CheckBoxAccelerationDispZNeg->SetColorBrush(220, 220, 220);
	SXParticlesEditor::CheckBoxAccelerationDispZNeg->GAlign.left = true;
	SXParticlesEditor::CheckBoxAccelerationDispZNeg->GAlign.top = true;
	//}
}

void SXParticlesEditor::DeleteAllElements()
{
	mem_release(SXParticlesEditor::WindowRender);
	mem_release(SXParticlesEditor::ToolBar1);
	mem_release(SXParticlesEditor::ListBoxEffects);
	mem_release(SXParticlesEditor::ListBoxEmitters);
	mem_release(SXParticlesEditor::StaticEffects);
	mem_release(SXParticlesEditor::ButtonEffectsCreate);
	mem_release(SXParticlesEditor::StaticEmitters);
	//mem_release(SXParticlesEditor::ButtonEffectsEdit);
	mem_release(SXParticlesEditor::ButtonEffectsDelete);
	mem_release(SXParticlesEditor::ButtonEmittersCreate);
	mem_release(SXParticlesEditor::ButtonEmittersBasis);
	mem_release(SXParticlesEditor::ButtonEmittersDelete);
	mem_release(SXParticlesEditor::ButtonBase);
	mem_release(SXParticlesEditor::ButtonTextureAnimTex);
	mem_release(SXParticlesEditor::ButtonSpawn);
	mem_release(SXParticlesEditor::ButtonBound);
	mem_release(SXParticlesEditor::ButtonCharacters);
	mem_release(SXParticlesEditor::ButtonVelocityAcceleration);
	mem_release(SXParticlesEditor::StaticEffectsCount);
	mem_release(SXParticlesEditor::StaticEmittersCount);

	mem_release(SXParticlesEditor::StaticName);
	mem_release(SXParticlesEditor::EditName);
	mem_release(SXParticlesEditor::ButtonEmitterCreate);
	mem_release(SXParticlesEditor::StaticCount);
	mem_release(SXParticlesEditor::EditCount);
	mem_release(StaticColorCoef);
	mem_release(EditColorCoef);
	mem_release(SXParticlesEditor::StaticReCreateCount);
	mem_release(SXParticlesEditor::EditReCreateCount);
	mem_release(SXParticlesEditor::StaticSoftCoef);
	mem_release(SXParticlesEditor::EditSoftCoef);
	mem_release(SXParticlesEditor::StaticRefractionCoef);
	mem_release(SXParticlesEditor::EditRefractionCoef);
	mem_release(SXParticlesEditor::StaticTransparencyCoef);
	mem_release(SXParticlesEditor::EditTransparencyCoef);
	mem_release(SXParticlesEditor::CheckBoxLighting);
	mem_release(SXParticlesEditor::StaticFigureType);
	mem_release(SXParticlesEditor::ComboBoxFigureType);
	mem_release(SXParticlesEditor::StaticFigureCountQuads);
	mem_release(SXParticlesEditor::EditFigureCountQuads);
	mem_release(SXParticlesEditor::CheckBoxFigureRotRand);
	mem_release(SXParticlesEditor::CheckBoxFigureTapX);
	mem_release(SXParticlesEditor::CheckBoxFigureTapY);
	mem_release(SXParticlesEditor::CheckBoxFigureTapZ);
	mem_release(StaticAlphaBlendType);
	mem_release(ComboBoxAlphaBlendType);
	mem_release(SXParticlesEditor::StaticTimeLife);
	mem_release(SXParticlesEditor::EditTimeLife);
	mem_release(SXParticlesEditor::StaticTimeLifeDisp);
	mem_release(SXParticlesEditor::EditTimeLifeDisp);
	mem_release(SXParticlesEditor::StaticAlphaAgeDepend);
	mem_release(SXParticlesEditor::ComboBoxAlphaDependAge);
	mem_release(SXParticlesEditor::StaticSize);
	mem_release(SXParticlesEditor::StaticSizeX);
	mem_release(SXParticlesEditor::EditSizeX);
	mem_release(SXParticlesEditor::StaticSizeY);
	mem_release(SXParticlesEditor::EditSizeY);
	mem_release(SXParticlesEditor::StaticSizeDisp);
	mem_release(SXParticlesEditor::EditSizeDisp);
	mem_release(SXParticlesEditor::StaticSizeDependAge);
	mem_release(SXParticlesEditor::ComboBoxSizeDependAge);
	mem_release(SXParticlesEditor::CheckBoxCollisionDelete);

	mem_release(SXParticlesEditor::StaticBoundType);
	mem_release(SXParticlesEditor::ComboBoxBoundType);
	mem_release(SXParticlesEditor::StaticBoundVec1);
	mem_release(SXParticlesEditor::StaticBoundVec1X);
	mem_release(SXParticlesEditor::EditBoundVec1X);
	mem_release(SXParticlesEditor::StaticBoundVec1Y);
	mem_release(SXParticlesEditor::EditBoundVec1Y);
	mem_release(SXParticlesEditor::StaticBoundVec1Z);
	mem_release(SXParticlesEditor::EditBoundVec1Z);
	mem_release(SXParticlesEditor::StaticBoundVec1W);
	mem_release(SXParticlesEditor::EditBoundVec1W);
	mem_release(SXParticlesEditor::StaticBoundVec2);
	mem_release(SXParticlesEditor::StaticBoundVec2X);
	mem_release(SXParticlesEditor::EditBoundVec2X);
	mem_release(SXParticlesEditor::StaticBoundVec2Y);
	mem_release(SXParticlesEditor::EditBoundVec2Y);
	mem_release(SXParticlesEditor::StaticBoundVec2Z);
	mem_release(SXParticlesEditor::EditBoundVec2Z);
	mem_release(SXParticlesEditor::StaticBoundVec2W);
	mem_release(SXParticlesEditor::EditBoundVec2W);
	
	mem_release(SXParticlesEditor::CheckBoxCircle);
	mem_release(SXParticlesEditor::StaticCircleAxis);
	mem_release(SXParticlesEditor::ComboBoxCircleAxis);
	mem_release(SXParticlesEditor::StaticCircleAngle);
	mem_release(SXParticlesEditor::EditCircleAngle);
	mem_release(SXParticlesEditor::StaticCircleAngleDisp);
	mem_release(SXParticlesEditor::EditCircleAngleDisp);
	mem_release(SXParticlesEditor::CheckBoxRotate);
	mem_release(SXParticlesEditor::StaticRotateAngle);
	mem_release(SXParticlesEditor::EditRotateAngle);
	mem_release(SXParticlesEditor::StaticRotateAngleDisp);
	mem_release(SXParticlesEditor::CheckBoxCircleAngleDispNeg);
	mem_release(SXParticlesEditor::EditRotateAngleDisp);
	mem_release(SXParticlesEditor::CheckBoxRotateAngleDispNeg);
	mem_release(SXParticlesEditor::CheckBoxDeviation);
	mem_release(SXParticlesEditor::StaticDeviationType);
	mem_release(SXParticlesEditor::ComboBoxDeviationType);
	mem_release(SXParticlesEditor::StaticDeviationAmplitude);
	mem_release(SXParticlesEditor::StaticDeviationCoefAngle);
	mem_release(SXParticlesEditor::EditDeviationAmplitude);
	mem_release(SXParticlesEditor::EditDeviationCoefAngle);
	mem_release(SXParticlesEditor::StaticDeviationAxis);
	mem_release(SXParticlesEditor::ComboBoxDeviationAxis);
	mem_release(SXParticlesEditor::StaticDeviationCountDelayMls);
	mem_release(SXParticlesEditor::EditDeviationCountDelayMls);
	mem_release(SXParticlesEditor::StaticDeviationCoefAngleDisp);
	mem_release(SXParticlesEditor::EditDeviationCoefAngleDisp);
	mem_release(SXParticlesEditor::CheckBoxDeviationCoefAngleDispNeg);
	mem_release(SXParticlesEditor::CheckBoxDeviationTapX);
	mem_release(SXParticlesEditor::CheckBoxDeviationTapY);
	mem_release(SXParticlesEditor::CheckBoxDeviationTapZ);

	mem_release(SXParticlesEditor::StaticSpawnPosType);
	mem_release(SXParticlesEditor::ComboBoxSpawnPosType);
	mem_release(SXParticlesEditor::StaticSpawnOrigin);
	mem_release(SXParticlesEditor::StaticSpawnOriginX);
	mem_release(SXParticlesEditor::EditSpawnOriginX);
	mem_release(SXParticlesEditor::StaticSpawnOriginY);
	mem_release(SXParticlesEditor::EditSpawnOriginY);
	mem_release(SXParticlesEditor::StaticSpawnOriginZ);
	mem_release(SXParticlesEditor::EditSpawnOriginZ);
	mem_release(SXParticlesEditor::StaticSpawnOriginDisp);
	mem_release(SXParticlesEditor::EditSpawnOriginDisp);
	mem_release(SXParticlesEditor::CheckBoxSpawnOriginDispXPos);
	mem_release(SXParticlesEditor::CheckBoxSpawnOriginDispXNeg);
	mem_release(SXParticlesEditor::CheckBoxSpawnOriginDispYPos);
	mem_release(SXParticlesEditor::CheckBoxSpawnOriginDispYNeg);
	mem_release(SXParticlesEditor::CheckBoxSpawnOriginDispZPos);
	mem_release(SXParticlesEditor::CheckBoxSpawnOriginDispZNeg);
	mem_release(SXParticlesEditor::StaticSpawnNextTime);
	mem_release(SXParticlesEditor::EditSpawnNextTime);
	mem_release(SXParticlesEditor::StaticSpawnNextTimeDisp);
	mem_release(SXParticlesEditor::EditSpawnNextTimeDisp);

	mem_release(SXParticlesEditor::StaticTexture);
	mem_release(SXParticlesEditor::EditTexture);
	mem_release(SXParticlesEditor::ButtonTextureSel);
	mem_release(SXParticlesEditor::StaticAnimTexCountCadrsX);
	mem_release(SXParticlesEditor::StaticAnimTexCountCadrsY);
	mem_release(SXParticlesEditor::EditAnimTexCountCadrsX);
	mem_release(SXParticlesEditor::EditAnimTexCountCadrsY);
	mem_release(SXParticlesEditor::StaticAnimTexRate);
	mem_release(SXParticlesEditor::EditAnimTexRate);
	mem_release(SXParticlesEditor::StaticAnimTexRateDisp);
	mem_release(SXParticlesEditor::EditAnimTexRateDisp);
	mem_release(SXParticlesEditor::StaticAnimTexStartCadr);
	mem_release(SXParticlesEditor::EditAnimTexStartCadr);
	mem_release(SXParticlesEditor::StaticAnimTexStartCadrDisp);
	mem_release(SXParticlesEditor::EditAnimTexStartCadrDisp);

	mem_release(SXParticlesEditor::StaticVelocity);
	mem_release(SXParticlesEditor::StaticVelocityX);
	mem_release(SXParticlesEditor::EditVelocityX);
	mem_release(SXParticlesEditor::StaticVelocityY);
	mem_release(SXParticlesEditor::EditVelocityY);
	mem_release(SXParticlesEditor::CheckBoxVelocityDispXNeg);
	mem_release(SXParticlesEditor::StaticVelocityZ);
	mem_release(SXParticlesEditor::EditVelocityZ);
	mem_release(SXParticlesEditor::StaticVelocityDisp);
	mem_release(SXParticlesEditor::EditVelocityDisp);
	mem_release(SXParticlesEditor::CheckBoxVelocityDispYNeg);
	mem_release(SXParticlesEditor::CheckBoxVelocityDispZNeg);
	mem_release(SXParticlesEditor::StaticAcceleration);
	mem_release(SXParticlesEditor::StaticAccelerationX);
	mem_release(SXParticlesEditor::EditAccelerationX);
	mem_release(SXParticlesEditor::StaticAccelerationY);
	mem_release(SXParticlesEditor::EditAccelerationY);
	mem_release(SXParticlesEditor::StaticAccelerationZ);
	mem_release(SXParticlesEditor::EditAccelerationZ);
	mem_release(SXParticlesEditor::StaticAccelerationDisp);
	mem_release(SXParticlesEditor::EditAccelerationDisp);
	mem_release(SXParticlesEditor::CheckBoxAccelerationDispXNeg);
	mem_release(SXParticlesEditor::CheckBoxAccelerationDispYNeg);
	mem_release(SXParticlesEditor::CheckBoxAccelerationDispZNeg);

	mem_release(SXParticlesEditor::JobWindow);
}

//##########################################################################

void SXParticlesEditor::ParticlesEditorUpdate(DWORD timeDelta)
{
	bool whyplay = false;
	for (int i = 0; i < SPE_EffectCountGet(); ++i)
	{
		if (SPE_EffectEnableGet(SPE_EffectIdOfKey(i)))
		{
			SXParticlesEditor::CheckBoxTBPlay->SetCheck(true);
			SXParticlesEditor::CheckBoxTBPause->SetCheck(false);
			SXParticlesEditor::CheckBoxTBStop->SetCheck(false);
			whyplay = true;
			break;
		}
	}

	if (!whyplay)
	{
		SXParticlesEditor::CheckBoxTBPlay->SetCheck(false);
		SXParticlesEditor::CheckBoxTBPause->SetCheck(false);
		SXParticlesEditor::CheckBoxTBStop->SetCheck(true);
	}

	int emitters_count = 0;
	int emitters_all_count = 0;
	int particles_life_count = 0;
	int particles_all_count = 0;

	if (SXParticlesEditor::SelEffID >= 0)
	{
		emitters_all_count = SPE_EmitterSCountGet(SXParticlesEditor::SelEffID);
		if (SXParticlesEditor::SelEmitterID < 0)
		{
			for (int k = 0; k < SPE_EmitterSCountGet(SXParticlesEditor::SelEffID); ++k)
			{
				if (SPE_EmitterEnableGet(SXParticlesEditor::SelEffID, k))
					++emitters_count;

				particles_all_count += SPE_EmitterCountGet(SXParticlesEditor::SelEffID, k);
				particles_life_count += SPE_EmitterCountLifeGet(SXParticlesEditor::SelEffID, k);
			}
		}

		if (SXParticlesEditor::SelEmitterID >= 0)
		{
			emitters_count = SPE_EmitterEnableGet(SXParticlesEditor::SelEffID, SXParticlesEditor::SelEmitterID);
			particles_all_count += SPE_EmitterCountGet(SXParticlesEditor::SelEffID, SXParticlesEditor::SelEmitterID);
			particles_life_count += SPE_EmitterCountLifeGet(SXParticlesEditor::SelEffID, SXParticlesEditor::SelEmitterID);
		}
	}

	char ttext[256];

	sprintf(ttext, "Playing emitters: %d/%d", emitters_all_count, emitters_count);
	SXParticlesEditor::StatusBar1->SetTextParts(0, ttext);

	sprintf(ttext, "Living particles: %d/%d", particles_all_count, particles_life_count);
	SXParticlesEditor::StatusBar1->SetTextParts(1, ttext);


	IDirect3DDevice9 *pDXdevice = SGCore_GetDXDevice();

	pDXdevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	if (SXParticlesEditor::canRenderBound && SXParticlesEditor::SelEffID != -1 && SXParticlesEditor::SelEmitterID != -1 && SPE_EmitterGet(SXParticlesEditor::SelEffID, SXParticlesEditor::SelEmitterID, BoundType) != PARTICLESTYPE_BOUND_NONE)
	{
		pDXdevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		pDXdevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);

		ParticlesData* pdata = SPE_EmitterGetData(SXParticlesEditor::SelEffID, SXParticlesEditor::SelEmitterID);
		pDXdevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		if (pdata->BoundType == PARTICLESTYPE_BOUND_BOX)
		{
			pDXdevice->SetTransform(D3DTS_WORLD, &(D3DXMATRIX)(SMMatrixScaling(float3(pdata->BoundVec2 - pdata->BoundVec1)) * SMMatrixTranslation(float3(pdata->BoundVec2 + pdata->BoundVec1)*0.5f)));
			SXParticlesEditor::FigureBox->DrawSubset(0);
		}
		else if (pdata->BoundType == PARTICLESTYPE_BOUND_SPHERE)
		{
			pDXdevice->SetTransform(D3DTS_WORLD, &(D3DXMATRIX)(SMMatrixScaling(pdata->BoundVec1.w, pdata->BoundVec1.w, pdata->BoundVec1.w) * SMMatrixTranslation(float3(pdata->BoundVec1))));
			SXParticlesEditor::FigureSphere->DrawSubset(0);
		}
		else if (pdata->BoundType == PARTICLESTYPE_BOUND_CONE)
		{
			if (SXParticlesEditor::FigureConeParam.x != pdata->BoundVec2.w || SXParticlesEditor::FigureConeParam.y != pdata->BoundVec1.w || SXParticlesEditor::FigureConeParam.z != pdata->BoundVec2.y - pdata->BoundVec1.y)
			{
				SXParticlesEditor::FigureConeParam.x = pdata->BoundVec2.w;
				SXParticlesEditor::FigureConeParam.y = pdata->BoundVec1.w;
				SXParticlesEditor::FigureConeParam.z = pdata->BoundVec2.y - pdata->BoundVec1.y;

				SGCore_FCreateCone(SXParticlesEditor::FigureConeParam.x, SXParticlesEditor::FigureConeParam.y, SXParticlesEditor::FigureConeParam.z, &SXParticlesEditor::FigureCone, 20);
			}

			pDXdevice->SetTransform(D3DTS_WORLD, &(D3DXMATRIX)SMMatrixTranslation(pdata->BoundVec1.x, pdata->BoundVec2.y, pdata->BoundVec1.z));
			SXParticlesEditor::FigureCone->DrawSubset(0);
		}

		pDXdevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		pDXdevice->SetTransform(D3DTS_WORLD, &(D3DXMATRIX)SMMatrixIdentity());
	}
}

//##########################################################################

void SXParticlesEditor::PEcreateData()
{
	D3DXCreateBox(SGCore_GetDXDevice(), 1, 1, 1, &SXParticlesEditor::FigureBox, 0);
	D3DXCreateSphere(SGCore_GetDXDevice(), 1, 20, 20, &SXParticlesEditor::FigureSphere, 0);

	SXParticlesEditor::FigureConeParam.x = 1;
	SXParticlesEditor::FigureConeParam.y = 0.1;
	SXParticlesEditor::FigureConeParam.z = 1;

	SGCore_FCreateCone(SXParticlesEditor::FigureConeParam.x, SXParticlesEditor::FigureConeParam.y, SXParticlesEditor::FigureConeParam.z, &SXParticlesEditor::FigureCone, 20);
}

void SXParticlesEditor::PEdeleteData()
{
	mem_release(SXParticlesEditor::FigureBox);
	mem_release(SXParticlesEditor::FigureSphere);
}
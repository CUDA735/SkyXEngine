#ifndef __RENDERABLE_H
#define __RENDERABLE_H

#include <xcommon/IXRenderable.h>

class CRenderable: public IXRenderable
{
	friend class CEditorObject;

public:
	//! ���������� �������������� ������ �������
	X_RENDER_STAGE getStages();

	//! ���������� ��������� ������� ������ ������. ��� ������ ����� - ��� ������ ����� ������
	UINT getPriorityForStage(X_RENDER_STAGE stage);

	//! ��������� ��������� �������� �������� ������ � ������ ���������. ���� pVisibility == NULL - �������� ���
	void renderStage(X_RENDER_STAGE stage, IXRenderableVisibility *pVisibility);

	void startup(IGXContext *pDevice, IXMaterialSystem *pMaterialSystem);
	void shutdown();

	//! ������� ����� ������ �������� ��������� ��� �������
	void newVisData(IXRenderableVisibility **ppVisibility);

	IXMaterialSystem *getMaterialSystem();
protected:
	IGXContext *m_pDevice = NULL;
	IXMaterialSystem *m_pMaterialSystem = NULL;
};

#endif

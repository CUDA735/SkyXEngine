#ifndef __DYNAMICMODEL_H
#define __DYNAMICMODEL_H

#include <xcommon/resource/IXModel.h>
#include "DynamicModelShared.h"

class CDynamicModel: public IXDynamicModel
{
public:
	CDynamicModel(CDynamicModelProvider *pProvider, CDynamicModelShared *pShared);
	~CDynamicModel();

	bool XMETHODCALLTYPE isEnabled() const override;
	void XMETHODCALLTYPE enable(bool yesNo) override;

	IXAnimatedModel * XMETHODCALLTYPE asAnimatedModel() override;
	IXDynamicModel * XMETHODCALLTYPE asDynamicModel() override;
	IXStaticModel * XMETHODCALLTYPE asStaticModel() override;


	float3 XMETHODCALLTYPE getPosition() const override;
	void XMETHODCALLTYPE setPosition(const float3 &vPos) override;

	SMQuaternion XMETHODCALLTYPE getOrientation() const override;
	void XMETHODCALLTYPE setOrientation(const SMQuaternion &qRot) override;

	UINT XMETHODCALLTYPE getSkin() const override;
	void XMETHODCALLTYPE setSkin(UINT uSkin) override;

	float3 XMETHODCALLTYPE getLocalBoundMin() const override;
	float3 XMETHODCALLTYPE getLocalBoundMax() const override;

	float4 XMETHODCALLTYPE getColor() const override;
	void XMETHODCALLTYPE setColor(const float4 &vColor) override;

	UINT XMETHODCALLTYPE getPhysboxCount(UINT uPartIndex = 0) const override;
	const IModelPhysbox * XMETHODCALLTYPE getPhysBox(UINT id, UINT uPartIndex = 0) const override;
	const IXResourceModel * XMETHODCALLTYPE getResource(UINT uIndex = 0) override;

	void render(UINT uLod);

protected:
	CDynamicModelProvider *m_pProvider;
	CDynamicModelShared *m_pShared;
	IGXContext *m_pDevice;

	float3_t m_vPosition;
	SMQuaternion m_qRotation;
	UINT m_uSkin = 0;
	float4_t m_vColor{1.0f, 1.0f, 1.0f, 1.0f};
	bool m_isEnabled = true;

};

#endif
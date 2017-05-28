#ifndef _ANIMATED_H_
#define _ANIMATED_H_


#include "ModelFile.h"

#include <common/assotiativearray.h>
#include <common/array.h>
#include <common/string.h>


#ifdef _SERVER
#	define IDirect3DDevice9 void
#else
#	define D3D_DEBUG_INFO
#	include <d3d9.h>
#	include <d3dx9.h>
#	pragma comment(lib, "d3dx9.lib")
#endif

#include "sxanim.h"

void Report(int level, const char* format, ...);

class Animation;
class AnimationManager;
class ISXBound;

class ModelFile
{
	friend class Animation;
	friend class Editor;
	friend class AnimationManager;
public:
	ModelFile(const char * name, AnimationManager * pMgr);
	~ModelFile();

	SX_ALIGNED_OP_MEM;

	bool Save(const char * name);
#ifndef _SERVER
	void Render(SMMATRIX * mWorld, UINT nSkin, UINT nLod=0);
#endif

	void BuildMeshBuffers();

	const ModelSequence * GetSequence(UINT id) const;
	const ModelSequence * GetSequence(const char * name) const;
	const ModelBoneController * GetController(UINT id) const;
	UINT GetBoneCount() const;
	UINT GetSequenceCount() const;
	UINT GetControllersCount() const;

	UINT GetBoneID(const char * name);
	void GetBoneName(UINT id, char * name, int len) const;

	ModelMatrial ** m_iMaterials;
	ModelLoD * m_pLods;
	//SkyXEngine::Graphics::ThreeD::Bound BoundVol;

	const ModelHitbox * GetHitbox(const char * name) const;
	const ModelHitbox * GetHitbox(uint32_t id) const;
	uint32_t GetHitboxCount() const;
	void AddHitbox(const ModelHitbox * hb);
	void DelHitbox(const char * name);
	void DelHitbox(uint32_t id);

	void LoadParts();

	const ISXBound * GetBound() const;
	
protected:

	MBERR AppendBones(const ModelFile * mdl, char * root=NULL);
	//void BuildHitboxes();
	void Load(const char * name);

	ModelHeader m_hdr;
	ModelHeader2 m_hdr2;
#ifndef _SERVER
	IDirect3DIndexBuffer9 ** m_ppIndexBuffer;
	IDirect3DVertexBuffer9 ** m_ppVertexBuffer;
#endif

	const ModelFile ** m_pDeps;

	ModelActivity * pActivities;

	ModelBoneName * m_pBones;
	ModelBone * m_pBonesBindPoseInv;

	ModelBoneController * m_pControllers;

	ModelSequence * m_pSequences;

	ModelHitbox * m_pHitboxes;

	ModelPart * m_pParts;

	//AssotiativeArray<String, ModelBoneController> m_mfBoneControllers;
	//AssotiativeArray<String, UINT> m_mSeqNames;

	char m_szFileName[MODEL_MAX_FILE];

	

	bool m_bAssemblied;
	bool m_bLoaded;
	bool m_bInitPosInvSet;

	AnimationManager * m_pMgr;

	bool m_bIsTemp;

	ISXBound * m_pBoundBox;


};

class Animation: public IAnimPlayer
{
	friend class AnimationManager;
public:
	Animation(AnimationManager * pMgr);
	~Animation();

	SX_ALIGNED_OP_MEM

	void Advance(unsigned long int dt);

#ifndef _SERVER
	void Render();
#endif

	void SetModel(const char * file);

	void Play(const char * name, UINT iFadeTime = 0, UINT slot = 0); // name: Animation name; changeTime: time to fade to this animation from previous
	void Stop(UINT slot = 0);
	void Resume(UINT slot = 0);

	void SetProgress(float progress, UINT slot = 0);
	void SetAdvance(bool set, UINT slot = 0);

	void StartActivity(const String & name, UINT iFadeTime = 0, UINT slot = 0);

	void SetBoneController(const String & name, float value, MODEL_BONE_CTL what);

	SMMATRIX GetBoneTransform(UINT id);
	UINT GetBone(const char * str);
	UINT GetBoneCount() const;
	void GetBoneName(UINT id, char * name, int len) const;

	inline bool PlayingAnimations();
	inline bool PlayingAnimations(const char* name);
	void StopAll();


	int GetActiveSkin();
	void SetSkin(int n);

	void SetPos(const float3 & pos);
	float3 GetPos();

	void SetOrient(const SMQuaternion & pos);
	SMQuaternion GetOrient();


	SMMATRIX GetWorldTM();

	AnimStateCB SetCallback(AnimStateCB cb);
	AnimProgressCB SetProgressCB(AnimProgressCB cb);

	ModelSequence const * GetCurAnim(int slot);

	ModelFile * m_pMdl;

	void SyncAnims();

	const ModelFile * AddModel(const char * mdl, UINT flags = MI_ALL, char * name = "No name");
	void AddModel(const ModelFile * mdl, UINT flags = MI_ALL, char * name="No name");
	int AddModel(ModelPart * mp);
	void DelModel(ModelPart * mp);
	void Assembly();
	ModelPart * GetPart(UINT idx);
	UINT GetPartCount();

	const ISXBound * GetBound() const;

	void SwapBoneBuffs();

	//static void AssemblyMdl(ModelFile * pOut, const Array<ModelPart*> & mMdls);
protected:

	void DownloadData();

	void FillBoneMatrix();

	void UpdateControllers();

	float3 jcenter2,jcenter;
	float jradius;
	bool m_bIsAnimationPlaying[BLEND_MAX];
	bool m_bNewAnimPlayed[BLEND_MAX];

	UINT m_iAnimFrameCount[BLEND_MAX];
	int m_iCurrentFrame[BLEND_MAX];

	ModelBoneShader * m_pBoneMatrix;
	ModelBoneShader * m_pBoneMatrixRender;

	UINT m_iFadeTime[BLEND_MAX];
	UINT m_iFadeCurTime[BLEND_MAX];
	bool m_bInFade[BLEND_MAX];
	bool m_bDoAdvance[BLEND_MAX];

	float3_t m_vPosition;
	SMQuaternion m_vOrientation;

	unsigned long int m_iCurTime;

	UINT m_iBoneCount;


	ModelBone * m_CurrentBones[BLEND_MAX];
	ModelBone * m_FinalBones;
	ModelBone * m_LastFrameBones[BLEND_MAX];
	UINT m_iPlayingAnim[BLEND_MAX];

	ModelBoneCrontrollerValue * m_pBoneControllers;
	ModelBoneCrontrollerValue * m_mfBoneControllerValues;

	AssotiativeArray<String, UINT> m_mSeqIds;
	AssotiativeArray<String, UINT> m_mfBoneControllers;

	bool m_bBoneMatrixReFilled;

	int ctlCount;

	int m_iCurrentSkin;

	UINT myId;

	bool m_bVisible;
	bool m_bRenderForShadow;
	int t[BLEND_MAX];

	AnimationManager * m_pMgr;

	AnimStateCB m_pfnCallBack;
	AnimProgressCB m_pfnProgressCB;


	Array<ModelPart*> m_mMdls;
	MemAlloc<ModelPart, 8> m_aMdls;

	Array<bool> m_vIsVisibleFor;

private:
	void AppendMesh(ModelLoDSubset * to, ModelLoDSubset * from, Array<int> & bone_relink);
};

class AnimationManager
{
public:
	AnimationManager(IDirect3DDevice9 * dev);
	~AnimationManager();
	const ModelFile * LoadModel(const char * name, bool newInst = false);
	void UnloadModel(const ModelFile * mdl);

	UINT Register(Animation * pAnim);
	void UnRegister(UINT id);

	void Render(ID for_id=-1);
	void Update(int thread = 0);
	void Sync();

	void SetVertexDeclaration(MODEL_VERTEX_TYPE nDecl);

	UINT GetMaterial(const char * mat);

	void ComputeVis(const ISXFrustum * frustum, const float3 * viewpos, ID id_arr);

	ID GetNextVisId();
	void FreeVisID(ID id);

	void SetThreadNum(int num);

protected:
	friend class ModelFile;
	friend class Animation;
	AssotiativeArray<String, ModelFile*> m_pModels;
	void InitVertexDeclarations();

	IDirect3DVertexDeclaration9 * pVertexDeclaration[MVT_SIZE];

	Array<Animation*> m_pAnimatedList;

	IDirect3DDevice9 * m_pd3dDevice;

	Array<ID> m_vFreeVisIDs;
	ID m_iVisID;

	int m_iThreadNum;
};


#endif

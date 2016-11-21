

//��������� ������������� ��������������
struct GreenDataVertex
{
	float3_t Position;	//�������
	float3_t TexCoord;	//x - ����� �������,y - ������� �� ��� y, z - 
};

//�������� ������ �������� ���������� ������
struct Segment
{
	Segment();
	~Segment();

	DWORD SortId[8];

	SX_ALIGNED_OP_MEM
	
	Segment* SplitMeshes[8]; //������ �� 4/8 ������ ������� �������

	//��� ���������
	DWORD** ArrPoly;	//��������� ������ �� ���������� ��������, ��������� ������ - ��� �������� ��� ������ ���������
	//DWORD** ArrSerialNum;
	DWORD* CountPoly;	//������ � ����������� ��������� �� ������ ���������
	DWORD* NumberGroup;	//������ � �������� �������� ������� �����������
	int* TypeMaterial;//������ � ������ ���������� ��������
	DWORD CountSubSet;	//���������� ��������
	DWORD CountAllPoly;	//����� ���������� ���������

	//��� ��������������
	GreenDataVertex* GreenData;
	
	Bound BoundVolumeSys;	//����������� �������������� ����� ��� ������������ �������
	Bound BoundVolumeP;		//���������� �������������� �����
	
	//����� ��?
	float DistForCamera;
	float DistFor;
	bool IsRenderForCamera;
	bool IsRenderFor;

	DWORD ID;	//������������� �����
	DWORD SID;	//���������� ����� ����� �� ������� ���������� ������
	DWORD WSID;
	DWORD** ArrSerialNum;
	ID3DXMesh* BoundBox;	//�������������� �������������� (���)
	bool BFNonEnd;//����� �� ����� ����� ������ ����?
};

//������� ������
//!!! �����������
class SegmentationModel : public Model
{
public:
	SegmentationModel();
	~SegmentationModel();

	SX_ALIGNED_OP_MEM

	void Segmentation(
						int type,		//��� ������� ������, 4 - quad, 8 - octo
						DWORD count_poly_in_segment	//����������� ���������� ��������� � ��������
						);

	void GPURender(
					Segment** arrsplits,	//������ � ����������
					DWORD count,			//���������� ������ �������
					bool iscomdistlod,		//���� �������� �� ������ ���
					bool render_alpha,		//�������� �� ����������� �������
					bool ismaterial,		//�������� �� ��������
					bool is_old_render,		//������������ ������ ������, ��� ��������� ������� �������
					bool is_one_dip,		//�������� �� ����� ��������, ����� ��� �����
					bool render_forward,	//�������� �� ��� �������� ������� �������� �� ����
					bool is_camera,
					DWORD tex_selected=-1); //iscomdistlod - ���� ������� ���� ��������� ���� �� ����� �� �������� ��� (true), false - ������ ������������ �����������

	bool IsVisible(Core::ControllMoving::Frustum* frustum);	//����� �� ������ ��������
	void CPUFillingArrIndeces(
								Core::ControllMoving::Frustum* frustum,		//������� ��������� � ������� �������
								Segment** arrsplits,	//������ (������������, ������ �� ���������� SplitsIDs) ������� ����������� ����������� �� �������� �������
								DWORD *count,			//���������� �������� ���������
								float3* viewpos,			//�� ����� �� ������ ���������� ������ �� ��������� �� �������
								bool is_camera//true � ������ ������ �� �� �������, false ������� � ����� ������
								);
	
	inline DWORD GetCountSplits();		//���������� ����� ���������� �������
	inline DWORD GetCountSplitsRender();//���������� ���������� ������� ������� ��������
	void GetAllValidSegments(Segment* insplit,Segment** arrsplits,DWORD* count);

	//����������� ����������� pos � �������, ���������� ������ ����������� �� ��� y � ������ ���������� y � pos
	void GetIntersectedRayY(float3* pos,Segment** arrsplits,DWORD *count,Segment* comsegment);
	void GetIntersected(const float3* pos, Segment** arrsplits, DWORD *count, Segment* comsegment, float additionalRadius);
	void GetIntersected22(float3* pos,Segment** arrsplits,DWORD *count,Segment* comsegment);

	void GetIntersectedQuad(float3_t* max,float3_t* min,Segment** arrsplits,DWORD *count,Segment* comsegment);

	float DistForLod;	//��������� �� ������ ��� ������� �������� ���, ��������� �� ������� �����
	inline bool IsLoadLod();
	bool CollisionRain;

	void GetPartFromBeam(const float3* pos, const float3 * dir, Segment** arrsplits, DWORD *count, Segment* comsegment);

	void SetSound(const char* path,float mindist,float dist);
	void GetSound(char* path);

	/*char SounsPath[1024];
	float MinDistForSound;
	float DistForSound;*/
	SkyXEngine::Sound::SoundObject* MeshSound;

//protected:
	bool* ArrSerialNum;		//��������� �� ������ ����� ��������� ��� ���, ������������� �� SID
	bool* IsVisibleGroup;	//������, ������ ���� �������� ���������� ����� �� ���������
	Segment* ArrSegments;	//��� ��������
	DWORD SplitsIDs;		//����� ���������� ���� ���������
	DWORD SplitsIDsRender;	//���������� �������� ���������
	
	bool IsCurrentRenderLod;	//����� ��������� ���������� ����� ��� �������� ��� ������ ������?

	DWORD** RTCPUArrIndicesPtrs;//������[���������][�������]
	DWORD* RTCountDrawPoly;		//������[���������] - ������� ��������� ���������� � ������ ������

	IDirect3DIndexBuffer9* IndexBuffer;	//��������� ����� ������� ����������� ������ ��� ����� ���� ������� �� ���������

	int CountSplitsSys;			//������� �������, 0 - ���������, 4-������ �������, 8-���� �������
	DWORD CountPolyInSegment;	//���������� ���������� ��������� � ��������

	float3* ArrMeshVertex;		//������ ���� ������ ������ (������ �������)
	float* ArrMeshVertexRadius;
	float3* ArrMeshVertexCenter;

	void EditVolume(Segment* SplitingMesh);	//������������ ���� ����� �����, ��� ������ ������� ������ �� ����
	
	void SetSplitID(Segment* SplitingMesh);	//��������� id �� �����
	void CycleSegmentation(Segment* SplitingMesh);	//��������� �������� ������� ������
	void SecondSeparated(Segment* SplitingMesh);
	void ComRecArrIndeces(Core::ControllMoving::Frustum* frustum,Segment** arrsplits,DWORD *count,Segment* comsegment,bool is_camera,float3* viewpos);

	float3 jcenter,jcenter2;
	float jradius;
	float jdist;

	float3 jmin,jmax;
	float3 jmin2,jmax2;
};


///////////////
//��������� ���������� ����������� ����������� ���������� � �������� ������
struct InfoRenderSegments
{
	InfoRenderSegments(){Arr=0;Count=0;CountCom=0;};
	~InfoRenderSegments(){};
	Segment** Arr;	//������ �������� � ���� ��������� �� �������� REALTIME
	DWORD Count;	//������ Arr 
	DWORD CountCom;	//������� ��������� �������� � Arr	REALTIME
};

class ManagerStaticModel
{
public:
	ManagerStaticModel();
	~ManagerStaticModel();

	void OnLostDevice();
	void OnResetDevice();

	SX_ALIGNED_OP_MEM

	void Clear();

	void Add(	
				const char* name,			//��� ������
				const char* path,			//���� �� ������
				int type_segmentation,		//��� �����������
				DWORD count_poly_in_segment,//����������� ���������� ��������� � ��������
				const char* lod,			//���� �� ������ � �����
				float dist_for_lod,			//��������� �� ����
				float3* pos,				//�������
				float3* rot,				//�������
				bool is_open				//�������� �� ������? ��� ����������? ������? � �� ���� �������� � ����� �����??
				);

	DWORD AddFrustum();

	void AllCom(Core::ControllMoving::Frustum* frustum,DWORD id,bool is_com_not_open,float3* viewpos);
	void AllRender(DWORD id,DWORD timeDelta,int render_alpha,bool ismaterial,bool is_com_not_open,bool is_one_dip,bool render_forward);

	inline bool GetOpen(DWORD id);			//���������� ���������� ������
	inline void SetOpen(DWORD id,bool is_open);	//������������� ���������� ��� ������

	void AllComForCamera(float3* campos);
	void RenderForCamera(DWORD timeDelta,bool render_alpha,bool ismaterial,bool is_old_render,bool render_forward);

	inline DWORD GetCountPoly(DWORD id);	//���������� ���������� ��������� ������

	

	//��������� ��������� ����� ������
	inline void GetName(DWORD id,char* str);
	inline void SetName(DWORD id,const char* str);

	//��������� ������� �������/��������
	void GetMatPosition(DWORD id,float3* pos);
	void GetMatRotation(DWORD id,float3* rot);

	//��������� ������� �������/��������
	void SetMatPosition(DWORD id,float3* pos);
	void SetMatRotation(DWORD id,float3* rot);

	//������� ������, ���������� �������� ����� ��������� �������� � ����� ��������
	void ComMatrixTrans(DWORD id);

	DWORD GetCount();		//���������� ����������� �������
	void Delete(DWORD id);	//������� ������
	bool GetIntersectedRayY(DWORD id,float3* pos);	//����� ����������� �� ���� � ������� �� ������ ������� pos,pos->y ���� ������������
	bool GetIntersectedRayYRain(float3* pos);
	bool GetIntersectedRayYRainBB(float3* pos);
	bool GetIntersected(float3* pos);
	void GetIntersected22(float3* pos);
	void GetIntersected33(float3* pos);

	void GetAIQuad(float3_t* max,float3_t* min,AIQuad** quad);

	inline DWORD GetSelected();				//���������� id ��������� ������, ��� -1
	inline void SetSelected(DWORD id);		//�������� ������

	inline int GetSysSpliting(DWORD id);
	inline DWORD GetCountPolyInSplit(DWORD id);

	inline void GetModelPath(DWORD id,char* mpath);
	inline void GetLodPath(DWORD id,char* mpath);
	bool TraceBeam(const float3 & start, const float3 & dir, float3 * _res,DWORD* idmesh,int* type_mat,BOOL useEndPos);
	bool TraceBeamY(const float3 & start, const float3 & dir, float3 * _res,DWORD* idmesh);

	Array<DWORD> ArrayWSIDs;

	DWORD NumSelModel;	//id ���������� ������
	
	Array<SegmentationModel*> Arr;				//������ ���� �������
	Array<bool> ArrIsSelected;
	Array<InfoRenderSegments*> ArrComForCamera;	//���������� � ��������� ��� ������� ��� ������
	Array<Array<InfoRenderSegments*>> ArrFrustums;	//������ ��������� � ����� � ��������� ��� �������
	Array<InfoRenderSegments*> ArrCollision;		//������ � ����� � ��������� ��� �������

	D3DXVECTOR3 jpos;
	D3DXVECTOR3 jvevyp;
	D3DXVECTOR3 jvevyn;
	float3 jvec0,jvec1,jvec2;
};
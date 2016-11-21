

class Green
{
public:
	Green();
	~Green();

	void OnLostDevice();
	void OnResetDevice();

	SX_ALIGNED_OP_MEM

	void Init(DWORD id_model,const char* path_mask,float count_max);
	void LoadOne(const char* path);
	void Load(const char* path,int lod);
	void LoadBinMask(const char* path);
	void Segmentation(DWORD count_object_in_split);

	void GPURender(Segment** arrsplits,DWORD count,int lod,bool ismaterial,bool is_camera,int how_shader=0,float3* lightpos=0,bool is_selected=false);

	void CPUFillingArrIndeces(
		Core::ControllMoving::Frustum* frustum,		//������� ��������� � ������� �������
		Segment** arrsplits,	//������ (������������, ����� �� ���������� SplitsIDs) ������� ����������� ����������� �� �������� �������
		DWORD *count,bool is_camera
		);

	inline DWORD GetCountSplits(){return SplitsIDs;}
	inline DWORD GetCountSplitsRender(){return SplitsIDsRender;}

//protected:
	bool IsOrder;
	bool IsGrass;	//����� �� ���?
	IDirect3DVertexBuffer9* TransVertBuf;	//����� ������ � ��������������� ��������������
	DWORD CountGrassInVert;					//���������� ������ � ������ TransVertBuf
	Segment* ArrSegments;
	DWORD CountObjectInSegment;
	Graphics::ThreeD::DataStaticModel* DataLod[3];
	DWORD* ArrIDTex;
	DWORD* ArrMaterials;
	DWORD IDMaterailFreeRenderGreenColor;
	DWORD IDMaterailFreeRenderGreenShadowDirectPSSM;
	DWORD IDMaterailFreeRenderGReenShadowCube;
	DWORD AllCountPoly[3];
	DWORD AllCountVertex[3];
	char Paths[3][1024];	//���� ��� ������� ����
	DWORD IDTexMask;
	DWORD IDMeshIn;

	DWORD RTCountDrawObj;

	DWORD AllCountGreen;	//������� ����� ������������� ��������
	float CountMaxInPixel;	//������������ ��������� �� ���� ������� ��� ��������� �� ��������
	GreenDataVertex* AllTrans;//

	float3 BBMax,BBMin;

	DWORD SplitsIDs;
	DWORD SplitsIDsRender;

	void SetSplitID(Segment* SplitingMesh);	//��������� id �� �����
	void CycleSegmentation(Segment* SplitingMesh);
	void SecondSeparated(Segment* SplitingMesh);
	void ComRecArrIndeces(Core::ControllMoving::Frustum* frustum,Segment** arrsplits,DWORD *count,Segment* comsegment,bool is_camera);

	float3 jcenter;
	float jradius;
	float jdist;

	float3 jmin,jmax;
};

////////////////

class ManagerGreen
{
public:
	ManagerGreen();
	~ManagerGreen();

	void OnLostDevice();
	void OnResetDevice();

	SX_ALIGNED_OP_MEM

	void Clear();

	void AddOne(const char* path);

	void Add(	const char* path,
	DWORD count_object_in_segment,
	const char* lod1,
	const char* lod2,
	const char* path_bin_mask);

	void Gen(	DWORD id_model,
				float count_max,
				const char* path,
				DWORD count_object_in_segment,
				const char* lod1,
				const char* lod2,
				const char* path_mask
				);

	DWORD AddFrustum();

	//����� �������� ��������� �� ������� frustum, comgrass - ������������ �����?
	void AllCom(Core::ControllMoving::Frustum* frustum,DWORD id,bool comgrass);
	//����� ������, ismaterial - �������� �� � ����������, comgrass - �������� �� �����
	void AllRender(DWORD id,DWORD timeDelta,bool ismaterial,bool comgrass,int lod,int how_shader=0,float3* lightpos=0);

	void AllComForCamera(float3* campos);
	void RenderForCamera(DWORD timeDelta);

	inline DWORD GetCount();
	void Delete(DWORD id);

	DWORD GetAllCountObjectGen();
	DWORD GetAllCountSplits();
	DWORD GetAllCountRenderSplits();

	inline DWORD GetSelected();
	inline void SetSelected(DWORD id);

	inline DWORD GetMeshIn(DWORD id);

	inline bool GetSelectedMesh();
	inline void SetSelectedMesh(bool is_sel);

	inline DWORD GetTexMask(DWORD id);

	inline void GetLodPath(DWORD id,char* text,int type);
	inline DWORD GetCountObjectInSplit(DWORD id);
	inline DWORD IsLods(DWORD id);

	inline DWORD GetCountGreen(DWORD id);

	inline void GetPosTrans(DWORD id,GreenDataVertex* data);
//private:
	DWORD NumSelModel;
	bool IsSelectedMesh;
	Array<Green*> Arr;
	Array<InfoRenderSegments*> ArrComForCamera;
	Array<Array<InfoRenderSegments*>> ArrFrustums;
};
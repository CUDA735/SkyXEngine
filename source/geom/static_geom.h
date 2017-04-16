
/*
!!!!
GDataBuff
��� ���������� ����� ������, ������� ��� ������������� ���� ������
*/
#ifndef __static_geom
#define __static_geom

//#include <handler_dx_func.cpp>
#include <common\\string.cpp>
#include <common\array.h>
#include <common\\string_api.cpp>
//������������ ���������� ��������� � �������
//��� ������������ ���������� ��������� �� ���� ���������
#define STATIC_GEOM_MAX_POLY_IN_GROUP 400000

#define STATIC_PRECOND_ARRCOMFOR_ERR_ID(id_arr) \
if (!(id_arr < ArrComFor.size()))\
{\
	reportf(REPORT_MSG_LEVEL_ERROR, "%s - static: unresolved id '%d' for array of compute visible", gen_msg_location, id_arr); \
}

#define STATIC_PRECOND_ARRCOMFOR_ERR_ID_MODEL(id_model, retval) \
if (!(id_model < AllModels.size() && AllModels[id_model]))\
{\
	reportf(REPORT_MSG_LEVEL_ERROR, "%s - static: unresolved id '%d' for array of models", gen_msg_location, id_model); \
	return retval;\
}

#define STATIC_PRECOND_ERR_ID_GROUP(id_model,id_group, ret_val) \
if (!(id_model < AllModels.size() && AllModels[id_model] && id_group < AllModels[id_model]->SubSet.size()))\
{\
	reportf(REPORT_MSG_LEVEL_ERROR, "%s - static: unresolved id '%d' for array of group in model '%d'", gen_msg_location, id_group, id_model); \
	return ret_val; \
}

//���� �������
#define STATIC_COUNT_TYPE_SEGMENTATION_QUAD 4
#define STATIC_COUNT_TYPE_SEGMENTATION_OCTO 8

#define STATIC_DIFFERENCE_SIDES_FOR_OCTO 0.3	//����������� ������� ����� ��������� ��� ���� �������
#define STATIC_MIN_ALLVOLUME_FOR_SEGMENTATION 20//����������� ����� ����� ������ ��� �������
#define STATIC_MIN_POLYGONS_FOR_SEGMENTATION 5000//����������� ���������� ��������� � ������ ��� �������
#define STATIC_MIN_COUNT_POLY 500	//����������� ���������� ��������� � ������
#define STATIC_MAX_COUNT_POLY 1000	//������������ ���������� ��������� � ������

#define STATIC_DEFAULT_RESERVE_COM 512	//���������� ��� ���������

class StaticGeom
{
public:

	static bool UseSortFrontToBackSplits;
	static bool UseSortFrontToBackModels;
	static IDirect3DDevice9* DXDevice;
	static char StdPath[1024];
	static float DistForLod;

	StaticGeom();
	~StaticGeom();

	SX_ALIGNED_OP_MEM
	
	//�������, ����� ������
	struct Segment
	{
		Segment();
		~Segment();

		Segment* Splits[STATIC_COUNT_TYPE_SEGMENTATION_OCTO]; //������ �� 4/8 ������ ������� �������

		//��� ���������
		uint32_t** ArrPoly;	//��������� ������ �� ���������� ��������, ��������� ������ - ��� �������� ��� ������ ���������
		uint32_t* CountPoly;	//������ � ����������� ��������� �� ������ ���������
		uint32_t* NumberGroup;	//������ � �������� �������� � ��������� ������
		uint32_t* NumberGroupModel;//������ � �������� �������� � ��������� ������
		uint32_t CountSubSet;	//���������� ��������
		uint32_t CountAllPoly;	//����� ���������� ���������

		ISXBound* BoundVolumeSys;	//����������� �������������� ����� ��� ������������ �������
		ISXBound* BoundVolumeP;		//���������� �������������� �����

		float DistForCamera;

		DWORD ID;	//������������� �����
		DWORD SID;	//���������� ����� ����� �� ������� ���������� ������

		//ID3DXMesh* BoundBox;	//�������������� �������������� (���)
		bool BFNonEnd;//����� �� ����� ����� ������ ����?
	};

	

	//������, ������� ���� ������
	struct Model
	{
		Model();
		~Model();

		SX_ALIGNED_OP_MEM

		struct Lod
		{
			Lod();
			~Lod();

			int SortGroup;
			char PathName[1024];
			ISXDataStaticModel* model;
			Array<ID> IDsTexs;
			ISXBound* BoundVolume;
		};

		struct GDataBuff
		{
			int32_t idgroup;//id ��������� � ��������� ������
			int32_t idbuff;	//id ������ (� ���������) � ������� ������� ������ ��������� ������
			int32_t IndexStart;
			int32_t IndexCount;
			int32_t VertexStart;
			int32_t VertexCount;

			D3DXPLANE Plane;
			float3_t Max;
			float3_t Min;
			float3_t Center;
		};

		
		float3 Position;
		float3 Rotation;
		float3 Scale;

		float3 OldPosition;
		float3 OldRotation;
		float3 OldScale;

		char Name[64];
		char PathName[1024];
		int32_t CountPoly;

		Lod Lod0;

		bool IsRenderLod;

		Array<GDataBuff> SubSet;	//�������� ������ ��������� ������
		Array<float> GroupDist;
		Array<ID> IDTex;
		Segment* ArrSplits;	//������ � ����������	
		ID SplitsIDs;	//����� ���������� ���������/�������
		ID SplitsIDsRender;	//���������� ���������� ���������
	};


	//��������� ������
	struct Group
	{
		Group();
		~Group();

		/*struct VertexBuff
		{
			VertexBuff();
			~VertexBuff();

			float3_t* arr;
			long count;
		};*/

		bool IsRenderSingly;
		int SortGroup;//���/���/���� ���������, ��� ������������ �������
		String name;//��� ��������
		ID idtex;	//������������� ��������
		long AllCountVertex;	//����� ���������� ������
		long AllCountIndex;		//����� ���������� ��������
		Array<int32_t, 4> CountVertex;	//���������� ������ � �������
		Array<int32_t, 4> CountIndex;	//���������� �������� � �������
		Array<Array<Model*>> ArrModels;
		Array<IDirect3DVertexBuffer9*, 4> VertexBuffer;
		//Array<VertexBuff*, 4> VertexBufferOrigin;
	};

	//��������� ���������� ����������� ����������� ���������� � �������� ������
	struct InfoRenderSegments
	{
		InfoRenderSegments();
		~InfoRenderSegments();
		Segment** Arr;	//������ �������� � ���� ��������� �� �������� REALTIME
		DWORD Count;	//������ Arr 
		DWORD CountCom;	//������� ��������� �������� � Arr	REALTIME
	};

	struct IRSData
	{
		IRSData();
		~IRSData();
		Array<Segment*, STATIC_DEFAULT_RESERVE_COM> queue;
		Array<InfoRenderSegments*> arr;
	};

	void OnLostDevice();
	void OnResetDevice();

	void Clear();
	void Save(const char* path);
	void Load(const char* path);

	void SortGroup(float3* viewpos, int sort_mtl);
	
	inline long GetCountModel();

	void CPUFillingArrIndeces(ISXFrustum* frustum, float3* viewpos, ID id_arr = 0);
	bool GetIntersectedRayY(float3* pos);
	
	void GPURender(DWORD timeDelta, int sort_mtl, ID id_arr = 0, ID exclude_model_id = -1, ID exclude_group_id = -1, bool is_sorted = false);
	ID AddModel(const char* path, const char* lod1, const char* name);
	void DelModel(ID id);

	inline void GetMinMax(float3* min,float3* max);

	ID AddArrForCom();
	void DelArrForCom(ID id_arr);

	char* GetModelName(ID id);
	const char* GetModelPathName(ID id);
	long GetModelCountPoly(ID id);

	float3* GetModelPosition(ID id);
	float3* GetModelRotation(ID id);
	float3* GetModelScale(ID id);

	const char* GetModelLodPath(ID id);
	void SetModelLodPath(ID id, const char* path);

	void ApplyTransform(ID id);

	ID GetModelCountGroups(ID id);
	ID GetModelGroupIDMat(ID id, ID group);
	void GetModelGroupCenter(ID id, ID group, float3_t* center);
	void GetModelGroupMin(ID id, ID group, float3_t* min);
	void GetModelGroupMax(ID id, ID group, float3_t* max);
	void GetModelGroupPlane(ID id, ID group, D3DXPLANE* plane);

	void GetArrBuffsGeom(float3_t*** arr_vertex, int32_t** arr_count_vertex, uint32_t*** arr_index, int32_t** arr_count_index, int32_t* count_models);
	/*
	(*arr_vertex)[num_model][num_vertex] - ������� ������
	(*arr_count_vertex)[num_model] - ���������� ������ ��� ������
	(*arr_index)[num_model][num_vertex] - ������� ������
	(*arr_count_index)[num_model] - ���������� �������� ��� ������
	(*count_model); ���������� �������
	*/

protected:

	struct InfoGroup
	{
		ID model;
		ID group;
		ID g_group;
		float dist;
		int count;
	};
	Array<InfoGroup*> DistGroup;
	Array<IRSData*> ArrComFor; //���������� � ��������� ��� �������
	void AddModelInArrCom(ID id_model);
	void DelModelInArrCom(ID id_model);

	float4x4 WorldMat;
	float4x4 RotationMat;
	void ApplyTransformLod(ID id);

	ISXBound* BoundVolume;

	void GetIntersectedRayY2(float3* pos, Segment** arrsplits, DWORD *count, Segment* comsegment, ID curr_splits_ids_render);

	void SaveSplit(Segment* Split, FILE* file, Array<Segment*> * queue);
	void LoadSplit(Segment** Split, FILE* file, Array<Segment**> * queue);

	void PreSegmentation(Model* mesh, ISXDataStaticModel* model);	//���������������� ���� �����������
	void Segmentation(Segment* Split, Model* mesh, ISXDataStaticModel* model, long CountSplitsSys, long CountPolyInSegment, Array<Segment*> * queue);	//����������� ������
	void CycleSegmentation(Segment* Split, Model* mesh, ISXDataStaticModel* model, long CountSplitsSys, long CountPolyInSegment);	//����������� ����� �����������
	void EditVolume(Model* mesh, Segment* Split);
	void SetSplitID(Segment* Split, ID* SplitsIDs, ID* SplitsIDsRender);	//��������� ������� ����� ��������������, �������� ������ ������
	void SetSplitID2(Segment* Split, ID* SplitsIDs, ID* SplitsIDsRender, Array<Segment*>* queue);
	void ComRecArrIndeces(ISXFrustum* frustum, Segment** arrsplits, DWORD *count, Segment* comsegment, float3* viewpos, Array<Segment*, STATIC_DEFAULT_RESERVE_COM>* queue, ID curr_splits_ids_render);

	//������� ������, ������������ ������ � �������
	//{{
	float3* ArrMeshVertex;
	long CountVertex;

	D3DXVECTOR3 jpos;
	D3DXVECTOR3 jvevyp;
	D3DXVECTOR3 jvevyn;
	float3 jvec0, jvec1, jvec2;

	//}}

	//������� �������� � �������� �������� RTCPUArrIndicesPtrs � RTCountDrawPoly
	//��� ���������� ����� ������
	void DelArrIndexPtr();
	void InitArrIndexPtr();

	uint32_t*** RTCPUArrIndicesPtrs;	//������ ��� �������� ���� �������� ������� ����� ���������� �� ������ ������
	uint32_t** RTCountDrawPoly;			//������ ��� �������� �������� ��� ������� �� �������� RTCPUArrIndicesPtrs
	uint32_t*** RTCountDrawPolyModel;	//������ ��� �������� ���������� �������� ��������� ��� ������ ��������� ��� ������ ������
	uint32_t*** RTBeginIndexModel;		//������ ��� �������� ������ �������� ��� ������ ��������� ��� ������ ������

	Array<Model*> AllModels;	//������ �������
	Array<Group*> AllGroups;	//������ ��������
	//IDirect3DVertexDeclaration9* VertexDeclarationStatic;

	long SizeRenderIndexBuffer;	//������ � ��������� RenderIndexBuffer
	IDirect3DIndexBuffer9* RenderIndexBuffer;	//��������� �����, ������������ � ���������� � ���������� ��� ������� ������	
};

bool StaticGeom::UseSortFrontToBackSplits = true;
bool StaticGeom::UseSortFrontToBackModels = true;
IDirect3DDevice9* StaticGeom::DXDevice = 0;
char StaticGeom::StdPath[1024];
//sprintf(StaticGeom::StdPath, "");
float StaticGeom::DistForLod = 200.f;

#endif
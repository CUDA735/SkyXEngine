
#ifndef __static_geom
#define __static_geom

#include <handler_dx_func.cpp>
#include <string\\string.cpp>
#include <core\array.h>
#include <common\\string_api.cpp>
//������������ ���������� ��������� � �������
//��� ������������ ���������� ��������� �� ���� ���������
#define STATIC_GEOM_MAX_POLY_IN_GROUP 256000

#define STATIC_PRECOND_ARRCOMFOR_ERR_ID(id_arr) \
if (!(id_arr < ArrComFor.size()))\
{\
	reportf(REPORT_MSG_LEVEL_ERROR, "static: unresolved id '%d' for array of compute visible", id_arr); \
}

#define STATIC_PRECOND_ARRCOMFOR_ERR_ID_MODEL(id_model) \
if (!(id_model < AllModels.size() && AllModels[id_model]))\
{\
	reportf(REPORT_MSG_LEVEL_ERROR, "static: unresolved id '%d' for array of models", id_model); \
}

#define STATIC_COUNT_TYPE_SEGMENTATION_QUAD 4
#define STATIC_COUNT_TYPE_SEGMENTATION_OCTO 8
#define STATIC_DIFFERENCE_SIDES_FOR_OCTO 0.3
#define STATIC_MIN_ALLVOLUME_FOR_SEGMENTATION 20
#define STATIC_MIN_POLYGONS_FOR_SEGMENTATION 5000
#define STATIC_MIN_COUNT_POLY 500
#define STATIC_MAX_COUNT_POLY 1000
#define STATIC_DEFAULT_RESERVE_COM 512

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
		SX_ALIGNED_OP_MEM

		Model();
		~Model();

		struct Lod
		{
			Lod();
			~Lod();
			char PathName[1024];
			ISXDataStaticModel* model;
			Array<DWORD> IDsTexs;
			ISXBound* BoundVolume;
		};

		struct GDataBuff
		{
			int32_t idgroup;	//id ��������� � ��������� ������
			int32_t idbuff;	//id ������ (� ���������) � ������� ������� ������ ��������� ������

			int32_t IndexStart;
			int32_t IndexCount;
			int32_t VertexStart;
			int32_t VertexCount;
		};

		char Name[64];
		char PathName[1024];
		int32_t CountPoly;
		float3 Position;
		float3 Rotation;
		float3 Scale;

		float3 OldPosition;
		float3 OldRotation;
		float3 OldScale;

		Lod Lod0;

		bool IsRenderLod;

		Array<GDataBuff> SubSet;	//�������� ������ ��������� ������
		Segment* ArrSplits;	//������ � ����������	
		long SplitsIDs;	//����� ���������� ���������/�������
		long SplitsIDsRender;	//���������� ���������� ���������
	};

	//��������� ������
	struct Group
	{
		Group();
		~Group();

		struct VertexBuff
		{
			VertexBuff();
			~VertexBuff();

			float3_t* arr;
			long count;
		};

		String name;	//��� ��������
		DWORD idtex;	//������������� ��������
		long AllCountVertex;	//����� ���������� ������
		long AllCountIndex;		//����� ���������� ��������
		Array<int32_t, 4> CountVertex;	//���������� ������ � �������
		Array<int32_t, 4> CountIndex;	//���������� �������� � �������
		Array<Array<Model*>> ArrModels;
		Array<IDirect3DVertexBuffer9*, 4> VertexBuffer;
		Array<VertexBuff*, 4> VertexBufferOrigin;
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

	void Clear();
	void Save(const char* path);
	void Load(const char* path);
	
	inline long GetCountModel();

	void CPUFillingArrIndeces(ISXFrustum* frustum,float3* viewpos,long id_arr = 0);
	bool GetIntersectedRayY(float3* pos);
	
	void GPURender(DWORD timeDelta,long id_arr = 0);
	long AddModel(const char* path,const char* lod1,const char* name);
	void DelModel(long id);

	inline void GetMinMax(float3* min,float3* max);

	long AddArrForCom();
	void DelArrForCom(long id_arr);

	char* GetModelName(long id);
	const char* GetModelPathName(long id);
	long GetModelCountPoly(long id);

	float3* GetModelPosition(long id);
	float3* GetModelRotation(long id);
	float3* GetModelScale(long id);

	const char* GetModelLodPath(long id);
	void SetModelLodPath(long id,const char* path);

	void ApplyTransform(long id);

	void GetArrBuffsGeom(float3_t*** arr_vertex, int32_t** arr_count_vertex, uint32_t*** arr_index, int32_t** arr_count_index, int32_t* count_models);
	/*
	(*arr_vertex)[num_model][num_vertex] - ������� ������
	(*arr_count_vertex)[num_model] - ���������� ������ ��� ������
	(*arr_index)[num_model][num_vertex] - ������� ������
	(*arr_count_index)[num_model] - ���������� �������� ��� ������
	(*count_model); ���������� �������
	*/

protected:

	Array<IRSData*> ArrComFor; //���������� � ��������� ��� �������
	void AddModelInArrCom(long id_model);
	void DelModelInArrCom(long id_model);

	float4x4 WorldMat;
	void ApplyTransformLod(long id);

	ISXBound* BoundVolume;

	void GetIntersectedRayY2(float3* pos, Segment** arrsplits, DWORD *count, Segment* comsegment, DWORD curr_splits_ids_render);

	void SaveSplit(Segment* Split, FILE* file, Array<Segment*> * queue);
	void LoadSplit(Segment** Split, FILE* file, Array<Segment**> * queue);

	void PreSegmentation(Model* mesh, ISXDataStaticModel* model);	//���������������� ���� �����������
	void Segmentation(Segment* Split, Model* mesh, ISXDataStaticModel* model, long CountSplitsSys, long CountPolyInSegment, Array<Segment*> * queue);	//����������� ������
	void CycleSegmentation(Segment* Split, Model* mesh, ISXDataStaticModel* model, long CountSplitsSys, long CountPolyInSegment);	//����������� ����� �����������
	void EditVolume(Model* mesh, Segment* Split);
	void SetSplitID(Segment* Split, long* SplitsIDs, long* SplitsIDsRender);	//��������� ������� ����� ��������������, �������� ������ ������
	void SetSplitID2(Segment* Split, long* SplitsIDs, long* SplitsIDsRender, Array<Segment*>* queue);
	void ComRecArrIndeces(ISXFrustum* frustum, Segment** arrsplits, DWORD *count, Segment* comsegment, float3* viewpos, Array<Segment*, STATIC_DEFAULT_RESERVE_COM>* queue, DWORD curr_splits_ids_render);

	//void UpdateArrMeshVertex2(long count_vertex, vertex_static* arrvertex);
	//������� ������, ������������ ������ � �������
	//{{
	float3* ArrMeshVertex;
	long CountVertex;
	/*float3* ArrMeshVertex2;
	long AllCountVertex2;*/

	D3DXVECTOR3 jpos;
	D3DXVECTOR3 jvevyp;
	D3DXVECTOR3 jvevyn;
	float3 jvec0, jvec1, jvec2;

	//}}

	//������� �������� � �������� �������� RTCPUArrIndicesPtrs � RTCountDrawPoly
	//��� ���������� ����� ������
	void DelArrIndexPtr();
	void InitArrIndexPtr();

	uint32_t*** RTCPUArrIndicesPtrs;//������ ��� �������� ���� �������� ������� ����� ���������� �� ������ ������
	uint32_t** RTCountDrawPoly;	//������ ��� �������� �������� ��� ������� �� �������� RTCPUArrIndicesPtrs

	Array<Model*> AllModels;	//������ �������
	Array<Group*> AllGroups;		//������ ��������
	IDirect3DVertexDeclaration9* VertexDeclarationStatic;

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
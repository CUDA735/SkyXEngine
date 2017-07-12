
//#include <physics/sxphysics.h>
#include <common/array.h>
#include <common/memalloc.h>

#define AIGRID_QUAD_PRECOND(id,retval)  if (id < 0 || ArrQuads.size() <= id) {reportf(REPORT_MSG_LEVEL_ERROR, " %s - unresolved index '%d' of quad, sxaigrid", gen_msg_location, id); return retval;}

#define toint100(fnum) (int32_t)((fnum + 0.0001f) * 100)

//long �������� �������, float3 * 100
struct int3
{
	int3(){ this->x = this->y = this->z = 0; }
	int3(long _x, long _y, long _z){ this->x = _x; this->y = _y; this->z = _z; }
	int32_t x,y,z;
};

//��������� ����������� ������� �� �� �����
struct AIQuad
{
	AIQuad()
	{
		axisx = axisy = 0;
		IsClose = false;
		Id = -1;
			for(int i=0;i<8;++i)
				Arr[i] = -1;

		IdSplit = 0;
	}

	//����������� �� ����
	//���� ����� 0 �� � ����� ������������, ����� ��� 1 �� ������������� �����������, ����� -1 �� �������������, 2 - ���� ���
	char axisx;
	char axisy;

	//��������� ������ ��� �����
	inline void SetNeighbor(int key,ID id)
	{
		Arr[key] = id;

			if(key == 1)
			{
					if(axisy == -1)
						axisy = 0;
					else if(axisy == 2)
						axisy = 1;
			}

			if(key == 6)
			{
					if(axisy == 1)
						axisy = 0;
					else if(axisy == 2)
						axisy = -1;
			}

			if(key == 3)
			{
					if(axisx == 1)
						axisx = 0;
					else if(axisx == 2)
						axisx = -1;
			}

			if(key == 4)
			{
					if(axisx == -1)
						axisx = 0;
					else if(axisx == 2)
						axisx = 1;
			}
	}

	float3_t pos;		//������� �����
	bool IsClose;		//�������� �� ����
	ID Arr[8];			//id �������
	ID Id;				//�������������-���� ��� ��������� � �������
	uint16_t IdSplit;	//������������� ������ � �������� ���������� ������ ���� (� ������ ���� ����� �� �������)
};

//�������������� ����� ��� ������
struct BoundAIQuad
{
	BoundAIQuad(){}
	~BoundAIQuad(){}

	float3_t min,max;
	int3 lmin, lmax;
	Array<ID> ArrIdsQuads;
};

//��������� ��������� �������� �� �����
struct CostAIQuad
{
	CostAIQuad()
	{
		F=G=H=0;
	}

	uint32_t F,G,H;
};

struct AIQuadVertexData
{
	AIQuadVertexData(){}
	AIQuadVertexData(float px,float py,float pz,float tcx,float tcy)
	{
		pos.x = px;
		pos.y = py;
		pos.z = pz;

		tc.x = tcx;
		tc.y = tcy;
	}
	float3_t pos;
	float2_t tc;
};

//
struct AIQuadVertexDataInst
{
	float3_t pos;
	float4_t tex;
	uint32_t color;
};


class AIGrid
{
public:
	AIGrid();
	~AIGrid();

	void GraphicsInit();//������������� ����������� ������, ���� ����
	void Clear();		//������� ���� ������

	//����������/��������
	void GridSave(const char* path);
	void GridLoad(const char* path);
	
	//�������������� �����
	//{
	inline void BBCreate(const float3* center, const float3* param);	//������� �������������� ����� �� ����������
	inline bool BBIsCreated() const;									//������ �� �������������� �����
	
	//���������/��������� ���������
	inline void BBSetDimensions(const float3* dim);						
	inline void BBGetDimensions(float3* dim) const;

	//���������/��������� �������
	inline void BBSetPos(const float3* pos);
	inline void BBGetPos(float3* pos) const;

	inline void BBCreateFinish();	//���������� �������� ��������������� ������, ����� �������� �������� �����-���� ��� ������ ����� ����������
	inline bool BBIsCreatedFinish() const;
	//}

	//�����
	//{
	//���������/����������� ��������� �����
	inline void QuadSetState(ID id, AIQUAD_STATE state);
	inline AIQUAD_STATE QuadGetState(ID id) const;
	
	//���������/����������� ������� �� ��� Y ��� �����
	inline void QuadSetPosY(ID id, float posy);
	inline float QuadGetPosY(ID id) const;

	ID QuadAdd(const float3* pos);					//���������� ����� � �������
	bool QuadDelete(ID id);							//�������� ����� �� ��� id
	
	void QuadSelect(ID id, bool consider_prev);		//���������� ����� � ������ ���������, id - ������������� �����, ���� -1 �� ������� ������, consider_prev - ��������� �� ���������� ����������, ���� ��� �� ������� ������ � ���������� ����, ���� �� �� ���������� ������
	inline void QuadSelectedAddPosY(float posy);	//���������� � ������� �� ��� Y ��� ���������� ������
	void QuadSelectedDelete();						//�������� ���������� ������
	
	inline bool QuadIsFree(ID id, int radius);		//�������� �� ���� id � ������� radius (radius - ���������� ������ ������ ���������� � id, 1 - ������ ������ ���������, 2 - ������ ��� �������� � �.�.)
	ID QuadGetNear(const float3* pos, bool isfree = false, int raius = 1);	//���������� id ���������� ����� (���� isfree == true �� ���� ������ ���������) � �������� ����������� radius
	inline ID QuadGet(const float3* pos, bool isnear_or_permissible) const;	//�������� id ����� �� �������, isnear_or_permissible - ����� ������� ����, ��� ����� ������� � �������� ���������� ������� ��������� �����?
	//}

	//�����
	//{
	void GridGenerate();											//������� ���������, �� ����� �������� ����� ���������� ��� �� �����
	void GridClear();
	ID GridTraceBeam(const float3* start, const float3* dir) const;	//����������� ���� � �������� ��� ����������� � ����� ���� ������ �����
	void GridTestValidation();										//���� ���������������� ����� � ���������� ��������� ��������
	inline UINT GridGetCountSplits();										//
	inline void GridSetMarkSplits(bool mark);						//��������� �������
	inline bool GridGetMarkSplits();								//���������� ��������� ��������� �������
	inline UINT GridGetCountQuads();								//���������� ���������� ������ � �����
	bool GridFindPath(ID beginq, ID endq);							//����� ����, (beginq,beginq]
	inline UINT GridGetSizePath();									//������ ���������� ���� � ���������� ���������
	inline bool GridGetPath(ID * pmem, UINT count);					//������ ���������� ���� � ��� ���������� ������

	inline void GridSetColorArr(const ID * pmem, DWORD color, UINT count);
	inline void GridSetNullColor();
	//}

	//����������
	//{
	void GraphPointGenerate();					//�������������� ��������� ����������� � ������� �������������� ������
	inline UINT GraphPointGetCount();			//���������� ���������� �����������
	inline void GraphPointClear();				//������� ������ �����������
	inline void GraphPointAdd(ID id);			//���������� ���������� (id - ������������� ����� �����)
	inline void GraphPointDelete(ID id);		//�������� ���������� (id - ������������� ����� �����)
	ID GraphPointGetNear(ID beginq, ID endq);	//����� �������� �������� ���������� ����� ��������� � �������� ������ ����������
	//}
	
	//�����
	//{
	void RenderQuads(const ISXFrustum * frustum, const float3 * viewpos, float dist);	//��������� �����
	void RenderGraphPoints(const float3 * viewpos, float dist);							//��������� �����������
	void RenderBB();			//��������� �������������� �������
	//}
	
protected:

	bool UseGraphics;	//������������ �� �������

	IDirect3DDevice9* DXDevice;
	IDirect3DVertexDeclaration9* AIQuadDecl;
	ID Tex_AIGrid;
	ID IDVS;
	ID IDPS;
	ID Tex_BB;

	MemAlloc<AIQuad> AllocAIQuad;			//���������� ������ ��� ������
	MemAlloc<BoundAIQuad> AllocBoundAIQuad;	//���������� ������ ��� �������

	Array<uint32_t,1000> ArrColor;		//������ ����� ��� ������� ����� ����� (�� id �����)
	Array<uint32_t> ArrSplitsColor;		//������ ����� ��� ������� ������ (���� ����� �� �������)
	Array<int3, 1000> ArrLongCoordQuads;//������ long �������� ��������� ��� ������� ����� (�� id �����)
	Array<AIQuad*, 1000> ArrQuads;		//������ ������� ������ (���������� ����� � ���� id)
	Array<AIQuad*, 1000> ArrQuadsCheck;	//������ ������ �� �������� (������������ ��� ���������)
	Array<AIQUAD_STATE> ArrState;		//������ ��������� ��� ������� ����� (�� id �����)
	Array<bool> ArrPreCondFreeState;	//������ ��������� �������� ��������� ��� ������� ����� (�� id �����)

	Array<BoundAIQuad*> ArrBound;		//������ �������������� ������� ��� ��������� �����
	Array<ID> ArrGraphPointsIDs;		//������ ������������� ������, ��� ����� �� ��� � ������� �����, ������� ���� ������� ������� ����� ���
	Array<int32_t> ArrCostGPIDs;		//������ �� ����������� ����������� �� ������������� ������

	Array<ID, 1000> ArrTestSplitsIDs;	//������ id ������ ������� �� ��������� ��� ����� ����������� �����
	Array<bool> ArrCloseIDs;			//�������� ������ (�� id �����)
	Array<ID> ArrOpenIDs;				//�������� ������, ArrIDsInOpen[id �����]
	Array<ID> ArrIDsInOpen;				//�������� ����� � �������� ������, �� id �����
	Array<ID> ArrParentIDs;				//������ ��������� (�� id �����)
	Array<CostAIQuad> ArrCostQuads;		//������ ���������� �������� �� ������� ����� (�� id �����)
	Array<ID> ArrPathIDs;				//������ � id ������ ��������� ����

	Array<ID> ArrSelected;				//������ ���������� � ������ ������ ������

	bool IsMarkSplits;		//true - �������� ������ ������ �����
	int NumLastKeyOpenList;	//��������� ������ ��������� ������, ������ ���� ������ ��� ����, �� �� ������� �� ������� �������
	ID CountInitOpen2;		//����� ���������� ����������� ����� � �������� ������
	uint16_t CountSplits;	//���������� ������� �����

	//������ ���, ��������� �� ������ hardware instancing
	IDirect3DVertexBuffer9* VertexQuad;
	IDirect3DIndexBuffer9*  IndexQuad;
	IDirect3DVertexBuffer9* TransVertBuf;
	ID3DXMesh* BoundBox;

	//�������� ��������������� ������
	float3_t Max, Min;
	

	inline ID GraphPointGetKey(ID id);			//�������� �� ���� � id �����������
	inline bool IsFreeQuad2(ID id, int radius);	//����������� ������� �������� ����������� �����

	inline bool QuadSelectedExists(ID id);					//������� �� ���� � id
	inline bool QuadSelectedExistsNeightborDirect(ID id);	//���� �� � ����� � id ����� �� ������� ����������� ������� ������ �������

	void CorrectPosXZ(float3* pos);				//��������� ������� ��� ����� ���������� ����� (�� xz)
	inline bool IsValidIdInArrQuads(ID id);		//�������� �� ���� � ��������� id
	void QuadDeleteInvalidAll();				//������� ��� ���������� ����� (��� �� ������� �� �����-�� �������� ��������� ��������� ��� �� ����� ������� �����������)
	void QuadDelete2(ID id);					//�������� ���������� � ����� �� ���� ��������� ���������� (� ���������� ���� ��������������� ������� ���� ����� ����)

	void PhyNavigate(AIQuad* quad);	//���������� ���������  �����
	inline bool AIGridCompareHeight(ID id1, ID id2);				//��������� �� ������� ����� �������� ������� ������ � ���������� �������
	void ReCreateBuffs();											//������������ �������
	void DefInitBuffs(ID id);										//��������� �������� �� ��������� ��� ����� id

	inline void AddUniqQuadArrag(const AIQuad* aq);					//���������� ����� � ���������� ����� � ������ ��� ������� � int3
	inline void AddUniqQuadArrag2(const AIQuad* aq, ID idbb);		//���������� ����� � ��������� ����� � ������ ��� ������� � int3
	void GenQuad(AIQuad* aq);										//��������� ������� ����� �� ������ ������������ � ������ ������� �����
	void ComputeNeighbor(ID id);									//������� � ���������� ������� ��� �����
	inline bool IsUniqQuadArrag(AIQuad* aq, ID * idquad, ID * idbb);//�������� �� ���� ����������
	void SplitBB(int x,int y,int z);								//������� ������������ ��������������� ������ �� ����� ������ �����

	//pathfind
	inline bool IsOpen(ID id);				//��������� �� ���� � �������� ������
	inline int CalcHCost(ID id, ID endid);	//������� H ���������, ������������ ���� �� � ����
	inline int CalcH2Cost(ID id1, ID id2);	//������� H ���������, ������� ���������� ����� ������� * 100
	inline ID AddInOpenList(ID id);			//�������� ���� � �������� ������
};


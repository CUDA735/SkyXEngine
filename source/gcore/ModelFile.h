#ifndef _ModelFile_H_
#define _ModelFile_H_

#define SX_MODEL_VERSION_OLD 6
#define SX_MODEL_VERSION 7
#define SX_MODEL_MAGICK 30510779525321540

#define MODEL_MAX_NAME 32
#define MODEL_BONE_MAX_NAME 32
#define MODEL_CTRL_MAX_BONES 64

struct model_vertex
{

};

struct vertex_static: public model_vertex
{
	float3_t Pos;
	float2_t Tex;
	float3_t Norm;
};

struct vertex_static_ex: public model_vertex
{
	float3_t Pos;
	float2_t Tex;
	float3_t Norm;
	float3_t Tangent;
	float3_t Binorm;
};

struct vertex_animated: public model_vertex
{
	float3_t Pos;
	float2_t Tex;
	float3_t Norm;
	byte BoneIndices[4];
	float4_t BoneWeights;
};

struct vertex_animated_ex: public model_vertex
{
	float3_t Pos;
	float2_t Tex;
	float3_t Norm;
	float3_t Tangent;
	float3_t Binorm;
	byte BoneIndices[4];
	float4_t BoneWeights;
};

enum MODEL_VERTEX_TYPE
{
	MVT_STATIC = 0,
	MVT_STATIC_EX,
	MVT_DYNAMIC,
	MVT_DYNAMIC_EX,

	//count
	MVT_SIZE
};

enum MODEL_FLAG
{
	MODEL_FLAG_COMPILED = 0x001, // is a full model file
	MODEL_FLAG_SOURCED = 0x002, // is a part of the model file

	MODEL_FLAG_SOURCE_ANIMATION = 0x004,
	MODEL_FLAG_SOURCE_MESH = 0x008,
	// MODEL_FLAG_SOURCE_LOD_MESH = 0x010,
	// MODEL_FLAG_SOURCE_PHYSBOX = 0x020,
	MODEL_FLAG_ANIMATED = 0x040,
	MODEL_FLAG_PHYSIC = 0x080,
	MODEL_FLAG_STATIC = 0x100,
	MODEL_FLAG_HAS_BONES = 0x200,
	MODEL_FLAG_HAS_GIBS = 0x400,
	MODEL_FLAG_HAS_PHYSBOX = 0x800,
	MODEL_FLAG_HAS_HITBOXES = 0x1000,
	MODEL_FLAG_HAS_TANGENT_BINORM = 0x2000, // should never been defined
	MODEL_FLAG_NEW_STYLE_DEPS = 0x4000
};

enum MODEL_PT_TOPOLOGY
{
	MDLPT_TRIANGLELIST = 0,
	MDLPT_TRIANGLESTRIP = 1,
	MDLPT_TRIANGLEFAN = 2,

	MDLPT_FORCE_DWORD = 0x7fffffff, /* force 32-bit size enum */
};

struct ModelHeader
{
	uint64_t Magick;
	uint32_t iVersion; // ������ �����
	uint32_t iFlags; // �����
	uint32_t iSkinCount; // ���������� ������ � ������
	uint32_t iMaterialCount; // ���������� ��������
	uint64_t iMaterialsOffset; // �������� �� ����� ������ ����������
	uint32_t iLODcount; // ���������� �����
	uint64_t iLODoffset; // �������� �� ����� �����
	uint32_t iBoneCount; // ���������� ������ � �������
	uint64_t iBonesOffset; // �������� �� ����� ������
	uint32_t iAnimationCount; // ���������� �������� � �����
	uint64_t iAnimationsOffset; // �������� �� ����� ��������
	uint64_t iSecondHeaderOffset; // �������� �� ������� ���������
};

struct ModelHeader2
{
	uint32_t iControllersCount; // ���������� ������������
	uint64_t iControllersOffset; // �������� �� ����� ������������
	uint32_t iDepsCount; // ���������� ���������� ������
	uint64_t iDependensiesOffset; // �������� �� ����� ���������� ������

	uint32_t iBoneTableCount; // ���������� ������ � ������� ������
	uint64_t iBoneTableOffset; // �������� �� ������� ������
	uint32_t iActivitiesTableCount; // ���������� ������� � ������� �����������
	uint64_t iActivitiesTableOffset; // �������� �� ������� �����������

	uint64_t iPhysicsDataOffset; // �������� �� ����� ���������� ������

	MODEL_PT_TOPOLOGY topology; // ������������ ��������� ����������

	uint32_t iHitboxCount; // ���������� ���������
	uint64_t iHitboxesOffset; // �������� �� ����� ���������

	uint64_t iBboxInfoOffset; // �������� �� ����� ���������� �� �������������� ������

	uint64_t iThirdHeaderOffset; // �������� �� �������� ���������
};


struct ModelLoDSubset
{
	unsigned int iMaterialID;
	unsigned int iVectexCount;
	unsigned int iIndexCount;
	model_vertex * pVertices;
	UINT * pIndices;
	UINT iStartIndex;
	UINT iStartVertex;
};

struct ModelLoD
{
	unsigned int iSubMeshCount;
	ModelLoDSubset * pSubLODmeshes;
	ModelLoD():pSubLODmeshes(NULL), iSubMeshCount(0)
	{
	};
};// typedef SXmodelLODheader;
#define MODEL_LOD_STRUCT_SIZE sizeof(unsigned int)

struct ModelMatrial
{
	UINT iMat;
	char szName[MODEL_MAX_NAME];
};

#endif

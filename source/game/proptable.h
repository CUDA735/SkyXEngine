#ifndef _PROPTABLE_H_
#define _PROPTABLE_H_

#include <common/SXmath.h>

class SXbaseEntity;

//! ���� ����� ������
enum PDF_TYPE
{
	PDF_NONE,
	PDF_INT,
	PDF_FLOAT,
	PDF_VECTOR,
	PDF_BOOL,
	PDF_STRING,
	PDF_ANGLES,
	PDF_ENTITY,
	PDF_PARENT,
	PDF_FLAGS,

	PDF_FLAG,

	PDF_OUTPUT
};

//! ���� ���������� �����
enum PDE_TYPE
{
	PDE_NONE = 0,
	PDE_TEXTFIELD,
	PDE_COMBOBOX,
	PDE_FILEFIELD,
	PDE_FLAGS
};

enum PDF_FLAG
{
	PDFF_NONE       = 0x00,
	PDFF_NOEXPORT   = 0x01, //!< �� �������������� ���� � ����
	PDFF_NOEDIT     = 0x02, //!< �� ���������� ���� � ���������
	PDFF_INPUT      = 0x04, //!< ���� �����
	PDFF_OUTPUT     = 0x08, //!< ���� ������
};

enum ENT_FLAG
{
	EF_NONE           = 0x0000,
	EF_EXPORT         = 0x0001,
	EF_LEVEL          = 0x0002,

	EF_LAST           = 0x8000
};

typedef int SXbaseEntity::*fieldtype;

struct editor_kv
{
	const char * key;
	const char * value;
};

struct prop_editor_t
{
	PDE_TYPE type;
	void * pData;
};


struct inputdata_t
{
	SXbaseEntity *pInflictor; //!< ��������� ��������� (��������� ��� ������� ���������)
	SXbaseEntity *pActivator; //!< ���������������� ���������
	PDF_TYPE type; //!< ��� ���������
	union
	{
		int i;
		bool b;
		float f;
		const char * str;
	}
	parameter;
	float3_t v3Parameter;
};

typedef void(SXbaseEntity::*input_func)(inputdata_t * pInputData);

struct propdata_t
{
	propdata_t():
		pField(NULL),
		type(PDF_NONE),
		flags(0),
		szKey(NULL),
		szEdName(NULL),
		editor({})
	{}
	propdata_t(fieldtype f, PDF_TYPE t, int fl, const char *key, const char *edname, prop_editor_t ed):
		pField(f),
		type(t),
		flags(fl),
		szKey(key),
		szEdName(edname),
		editor(ed)
	{}
	propdata_t(input_func d, PDF_TYPE t, int fl, const char *key, const char *edname, prop_editor_t ed):
		fnInput(d),
		type(t),
		flags(fl),
		szKey(key),
		szEdName(edname),
		editor(ed)
	{}
	union
	{
		fieldtype pField;
		input_func fnInput;
	};
	PDF_TYPE type;
	int flags;
	const char * szKey;
	const char * szEdName;
	prop_editor_t editor;
};


struct input_t
{
	input_func fnInput;
	SXbaseEntity *pTarget;
	inputdata_t data;
};

struct named_output_t
{
	named_output_t():
		iOutCount(0),
		pOutputs(NULL)
	{
	}

	float fDelay;
	const char *szTargetName;
	const char *szTargetInput;
	const char *szTargetData;

	int iOutCount;
	input_t *pOutputs;
};

struct output_t
{
	output_t():
		iOutCount(0),
		pOutputs(NULL),
		pData(NULL),
		bDirty(false)
	{
	}
	void fire(SXbaseEntity *pInflictor, SXbaseEntity *pActivator);

	bool bDirty;
	int iOutCount;
	named_output_t * pOutputs;
	void * pData;
};

#define FIRE_OUTPUT(output, inflictor) (output).fire((inflictor), this)

struct proptable_t
{
	propdata_t * pData;
	int numFields;
	proptable_t * pBaseProptable;
};

#define ED_COMBO_MAXELS 256

prop_editor_t _GetEditorCombobox(int start, ...);
prop_editor_t _GetEditorFilefield(int start, ...);

#define DECLARE_PROPTABLE() \
	\
	friend class EntityFactoryMap; \
	friend class EntityFactory<ThisClass>; \
	static proptable_t m_pPropTable; \
	\
protected:\
	static void InitPropData(); \
	virtual proptable_t * GetPropTable(); \
	static proptable_t * SGetPropTable(); \
	static void ReleasePropData();\
public:\
	virtual propdata_t * GetField(const char * name);\
private:

#define _BEGIN_PROPTABLE(cls, bclpt) \
proptable_t cls::m_pPropTable = {0,0,0}; \
void cls::ReleasePropData()\
{\
	for(int i = 0; i < m_pPropTable.numFields; ++i)\
	{\
		mem_delete_a(m_pPropTable.pData[i].editor.pData); \
	}\
}\
proptable_t * cls::SGetPropTable()\
{\
	if(!m_pPropTable.numFields)\
		InitPropData();\
	return(&m_pPropTable);\
}\
\
proptable_t * cls::GetPropTable()\
{\
	if(!m_pPropTable.numFields)\
		InitPropData(); \
	return(&m_pPropTable); \
}\
propdata_t * cls::GetField(const char * name)\
{\
	proptable_t * pt = GetPropTable();\
	while(pt)\
	{\
		for(int i = 0; i < pt->numFields; ++i)\
		{\
			if(pt->pData[i].szKey && !strcmp(pt->pData[i].szKey, name))\
			{\
				return(&pt->pData[i]);\
			}\
		}\
		pt = pt->pBaseProptable;\
	}\
	return(NULL);\
}\
void cls::InitPropData() \
{ \
	bclpt \
	typedef cls DataClass; \
	static propdata_t pData[] = {propdata_t()

#define BEGIN_PROPTABLE(cls) \
	_BEGIN_PROPTABLE(cls, m_pPropTable.pBaseProptable = BaseClass::SGetPropTable();)

#define BEGIN_PROPTABLE_NOBASE(cls) \
	_BEGIN_PROPTABLE(cls, m_pPropTable.pBaseProptable = NULL;)

#define END_PROPTABLE() \
	}; \
	if(ARRAYSIZE(pData) > 1) \
	{\
		m_pPropTable.pData = &pData[1]; \
		m_pPropTable.numFields = ARRAYSIZE(pData) - 1; \
	} \
	else \
	{ \
		m_pPropTable.pData = pData; \
		m_pPropTable.numFields = 1; \
	} \
} 

#define DECLARE_TRIVIAL_CONSTRUCTOR() ThisClass(EntityManager * pMgr):BaseClass(pMgr){}
#define DECLARE_CONSTRUCTOR() ThisClass(EntityManager * pMgr);

const char * GetEmptyString();

#define EDITOR_NONE {PDE_NONE, NULL}}
#define EDITOR_TEXTFIELD {PDE_TEXTFIELD, NULL}}

#define EDITOR_COMBOBOX _GetEditorCombobox(0
#define COMBO_OPTION(name, value) , name, value
#define EDITOR_COMBO_END() , NULL)}

#define EDITOR_FILEFIELD _GetEditorFilefield(0
#define FILE_OPTION(name, value) , name, value
#define EDITOR_FILE_END() , NULL)}


#define DEFINE_FIELD_STRING(field, flags, keyname, edname, editor) , {(fieldtype)&DataClass::field, PDF_STRING, flags, keyname, edname, editor
#define DEFINE_FIELD_VECTOR(field, flags, keyname, edname, editor) , {(fieldtype)&DataClass::field, PDF_VECTOR, flags, keyname, edname, editor
#define DEFINE_FIELD_ANGLES(field, flags, keyname, edname, editor) , {(fieldtype)&DataClass::field, PDF_ANGLES, flags, keyname, edname, editor
#define DEFINE_FIELD_INT(field, flags, keyname, edname, editor)    , {(fieldtype)&DataClass::field, PDF_INT,    flags, keyname, edname, editor
#define DEFINE_FIELD_FLOAT(field, flags, keyname, edname, editor)  , {(fieldtype)&DataClass::field, PDF_FLOAT,  flags, keyname, edname, editor
#define DEFINE_FIELD_BOOL(field, flags, keyname, edname, editor)   , {(fieldtype)&DataClass::field, PDF_BOOL,   flags, keyname, edname, editor
#define DEFINE_FIELD_ENTITY(field, flags, keyname, edname, editor) , {(fieldtype)&DataClass::field, PDF_ENTITY, flags, keyname, edname, editor
#define DEFINE_FIELD_PARENT(field, flags, keyname, edname, editor) , {(fieldtype)&DataClass::field, PDF_PARENT, flags, keyname, edname, editor
#define DEFINE_FIELD_FLAGS(field, flags, keyname, edname, editor)  , {(fieldtype)&DataClass::field, PDF_FLAGS,  flags, keyname, edname, editor

#define DEFINE_INPUT(method, keyname, edname, argtype) , {(input_func)&DataClass::method, argtype, PDFF_NOEDIT | PDFF_INPUT, keyname, edname, EDITOR_NONE
#define DEFINE_OUTPUT(field, keyname, edname) , {(fieldtype)&DataClass::field, PDF_OUTPUT, PDFF_NOEDIT | PDFF_OUTPUT, keyname, edname, EDITOR_NONE

#define DEFINE_FLAG(value, edname) , {(fieldtype)NULL, PDF_FLAG, value, NULL, edname, {PDE_FLAGS, NULL}}

#endif

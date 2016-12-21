
#define S4G_MAX_LEN_TYPE_NAME 64
#define S4G_MAX_LEN_VAR_NAME 64
#define S4G_MAX_LEN_STR_IN_FILE 1024

#define mem_delete(data) delete data;data = 0;
#define mem_delete_a(data) delete[] data;data = 0;

#include <core\MemAlloc.h>
#include <s4g\array.h>
#include <s4g\stack.h>
#include <s4g\aatable.h>


#define S4G_MAX_CALL 200	//������������ ���������� ������� (����������� � ���������)
#define S4G_GLOBAL_NM "_g"	//��������� � ������� � ����������� ������������ ����
#define S4G_MARG "args"
#define S4G_RESERVE_STACK_EXE 10000
#define S4G_ADD_MEM_CONTEXTS 16

#define S4G_RESERVE_VALUE 10000
#define S4G_RESERVE_VALUE_MEM 10000

#define S4G_RESERVE_DATA 10000
#define S4G_RESERVE_DATA_MEM 10000

#define S4G_RESERVE_CONTEXTS 100
#define S4G_RESERVE_CONTEXTS_MEM 100

#define S4G_RESERVE_INT_MEM 10000
#define S4G_RESERVE_UINT_MEM 10000
#define S4G_RESERVE_FLOAT_MEM 10000
#define S4G_RESERVE_BOOL_MEM 10000
#define S4G_RESERVE_STRING_MEM 10000
#define S4G_RESERVE_SFUNC_MEM 10000
#define S4G_RESERVE_TABLE_MEM 10000

#define S4G_NOTICE 0
#define S4G_WARNING 1
#define S4G_ERROR 2

//��� ������� ������ ���������� � ��������� ������
typedef void(*s4g_report_func) (int level, const char* name_ss, const char* format, ...);

//������������� ����
#define s4g_int long
#define s4g_uint unsigned long
#define s4g_float float
#define s4g_bool short int

extern class s4g_main;
extern class s4g_vm;
//��� ��(++) �������
typedef int(*s4g_c_function) (s4g_main* vm);

//��� ���� ������ ������� ����� ���� ������������ � ��������
enum s4g_type
{
	t_none = -1,
	t_null = 0,
	t_table = 1,
	t_string = 2,
	t_float = 3,
	t_int = 4,
	t_uint = 5,
	t_bool = 6,
	t_user_data = 7, //unsupported
	t_cfunc = 8,	
	t_sfunc = 9,
	t_nnull = 10,	//����� 0, ����������� � ��������� � ������� �������
};

//��������� ������������� �����
const char s4g_str_type[][S4G_MAX_LEN_TYPE_NAME] = {
"none",
"null",
"table",
"string",
"float",
"int",
"uint",
"bool",
"user_data",
"cfunc",
"sfunc",
"nnull"
};

extern class s4g_arr_lex;
extern class s4g_preprocessor;
extern struct s4g_node;
extern struct s4g_builder_syntax_tree;
extern class s4g_compiler;

extern class s4g_table;
extern class s4g_value;
extern struct s4g_command;
extern struct s4g_s_function;
extern struct s4g_context;
extern class s4g_gc;

#define S4G_PRE_COND(retval) if (s4gm == 0){s4g_report(2, "!!!", "script system is not init, api function [%s]",__FUNCTION__);	return retval;}

//������ �������������
struct s4g_main
{
	s4g_main(const char* _name);
	s4g_arr_lex* arr_lex;	//����������� ����������
	s4g_node* gnode;		//����������� ���
	s4g_builder_syntax_tree* bst;	//��������� ���
	Stack<s4g_command>* commands;	//������ � ���� �����
	s4g_compiler* compiler;			//����������
	s4g_vm* vmachine;				//����������� ������
	s4g_gc* gc;						//������� ������
	char strerror[1024];			//��������� �� ������
	char name[S4G_MAX_LEN_VAR_NAME];
};

//������������� ������
struct s4g_data
{
	s4g_data();
	~s4g_data();
	void* data;	//��������� �� �������� ������
	int ref;	//���������� ����������� ���������� �� ��� ������
	s4g_type type;	//��� �������� � data
	int typedata;	//��� ������ ��� �������� ������, 0 - ������� ���� ����, 1 - ������ �������
};

//����������
struct s4g_value
{
	s4g_value(/*long lexid = -1*/);
	~s4g_value();
	
	bool isdelete;	//����� �� ������� ����������
	int typedata;	//��� ������ ��� �������� ������, 0 - ������� ���� ����, 1 - ������ �������
	//long nlexid;	//������������� ������� ������� ������������� �������� ����������
	long iddata;	//������������� s4g_data �� ������� ������������ ��������� ������
	long idvar;		//������������� ���� ���������� � ������� ����������� ��������� ������
};

//�������
class s4g_table
{
public:
	s4g_table();
	~s4g_table()
	{
		for (int i = 0; i < arr_value.GetSize(); i++)
		{
			arr_value[i]->isdelete = true;
		}
	}

	inline s4g_value* getn(DWORD key);		//�������� ���������� �� ����������� ������
	inline s4g_value* gets(const char* str);	//�������� ���������� �� ������
	inline bool is_exists_s(const char* str);	//���������� �� ���������� � ������ ������
	inline bool is_exists_n(DWORD key);	//���������� �� ���������� �� ���������� �����

	inline long is_exists_s2(const char* str,s4g_value** tval);	//���������� �� ���������� � ������ ������
	inline bool is_exists_n2(DWORD key, s4g_value** tval);	//���������� �� ���������� �� ���������� �����

	inline void add_val_s(const char* name, s4g_value* val/*, long lexid*/);	//�������� ���������� � ��������� �� ��� � ������� �������
	inline void add_val_n(long num, s4g_value* val/*, long lexid*/);			//�������� ���������� �� �����
	inline void add_val(s4g_value* val/*, long lexid*/);						//�������� ���������� � ����� �������

	inline long size();						//������ ������� � ���������
	inline const char* get_name_id(long id);//�������� ��� �� id

	inline void reserve(int count_elem);

protected:
	AATable<s4g_value> arr_value;
};



//������� ������
class s4g_gc
{
public:
	s4g_gc();

#define def_cr_val_null(tval) \
	tval = MemValue.Alloc(); \
	tval->typedata = typedata; \
	stack_push(arrvar,tval); \
	tval->idvar = arrvar.count_obj; \
	s4g_data* tdata = MemData.Alloc(); \
	tdata->typedata = typedata; \
	tval->iddata = arrdata.count_obj; \
	stack_push(arrdata,tdata);

	//�������� ����������
	inline s4g_value* cr_val_null();
	inline s4g_value* cr_val_table_null();
	inline s4g_value* cr_val_int(s4g_int num);
	inline s4g_value* cr_val_uint(s4g_uint num);
	inline s4g_value* cr_val_float(s4g_float num);
	inline s4g_value* cr_val_bool(s4g_bool bf);
	inline s4g_value* cr_val_str(const char* str);
	inline s4g_value* cr_val_table(s4g_table* tt);
	inline s4g_value* cr_val_s_func(s4g_s_function* func);
	inline s4g_value* cr_val_c_func(s4g_c_function func);
	inline s4g_value* cr_val(int _type, const char* _val);	//������� ���������� �� _val � ����� _type
	inline s4g_value* cr_val_nn();	//������� ����� 0 (��� ������� ����: -123 ����� 0-123)

	inline void c_val(s4g_value* dest, s4g_value* src, bool incr = true);	//��������� dest ������ �� src
	inline void set_td_data(s4g_value* val, int td);	//��������� ������ �� ������� ��������� ��������� ��� ��� ��������

	//�������� �������� �� ���������
	inline s4g_int get_int(s4g_value* val);
	inline s4g_uint get_uint(s4g_value* val);
	inline s4g_float get_float(s4g_value* val);
	inline const char* get_str(s4g_value* val);
	inline s4g_table* get_table(s4g_value* val);
	inline s4g_s_function* get_s_func(s4g_value* val);
	inline s4g_c_function get_c_func(s4g_value* val);
	inline s4g_bool get_bool(s4g_value* val);

	inline s4g_type get_type(s4g_value* val);	//�������� ��� ����������

	//������ � �����������
	inline void add_mem_contexts();
	inline long add_new_context(s4g_table** tt);	//������� � �������� ����� ��������, ���������� id ���������, � � tt ���������� ��������� �� �������
	inline long add_context(s4g_table* tt);			//�������� �������� ���������� �� �������, ���������� id ������������ ���������
	inline void activate_prev(long lastidctx);		//���������� ���������� ��������� �� lastidctx (��� �������� ���� �������� ��� ������ deactivate_prev)
	inline long deactivate_prev();					//�������������� ��� ���������� ���������, ���������� ����� ��������� ������� ������������� ���������
	inline void del_context(long id);				//�������� �������� ��� �������� � ��� ������ ������ ������ ��� � ����
	inline void remove_context(long id);			//�������� �������� ��� �� ������ � ��� ������ ������� ������ �������� �� �� ��� ������
	inline void set_ctx_for_del(s4g_context* ctx);	//�������� �������� ��� ��������

	//���������� �� ���������� � ������ str �� ���� ���������� ����������
	//���� �� �� ���������� id ��������� � ������� �������, � val ���������� ��������� �� ����������
	inline long ctx_is_exists_s(const char* str, s4g_value** val);	
	
	//��������� ������ ������
	void clear();

	int typedata;	//��� ����������� ������, 0 - ���� ������ �� ����� �� ������, 1 - �� �������
	//������ � �������� ������� ������ ������� �� ���������, ������ � ����������� ������� ������� ������ ���������� ��������

protected:
	
	Stack<s4g_value*, S4G_RESERVE_VALUE> arrvar;	//������ ����������
	Stack<s4g_data*, S4G_RESERVE_DATA> arrdata;	//������ ������
	Stack<s4g_context*, 1024> oldarrcontexts;	//������ ���������� ������� ��� ���� ���������� � ��������� � ��������
	Stack<s4g_context*, S4G_RESERVE_CONTEXTS> arrcurrcontexts;//������ ������������ � ������ ������ ����������
	long curr_num_top_ctx = 0;
	
	MemAlloc<s4g_value, S4G_RESERVE_VALUE_MEM> MemValue;
	MemAlloc<s4g_data, S4G_RESERVE_DATA_MEM> MemData;

	MemAlloc<s4g_context, S4G_RESERVE_CONTEXTS_MEM> MemCtx;

	MemAlloc<s4g_int, S4G_RESERVE_INT_MEM> MemInt;
	MemAlloc<s4g_uint, S4G_RESERVE_UINT_MEM> MemUInt;
	MemAlloc<s4g_float, S4G_RESERVE_FLOAT_MEM> MemFloat;
	MemAlloc<s4g_bool, S4G_RESERVE_BOOL_MEM> MemBool;
	MemAlloc<String, S4G_RESERVE_STRING_MEM> MemString;
	MemAlloc<s4g_s_function, S4G_RESERVE_SFUNC_MEM> MemSFunc;
	MemAlloc<s4g_table, S4G_RESERVE_TABLE_MEM> MemTable;
};

//��� �������
struct s4g_s_function
{
	s4g_s_function(){ externs = 0; ismarg = false; countstack = -1; }
	~s4g_s_function(){ mem_delete(externs); }
	s4g_table* externs;	//����������� ���������� � ����������� ���������
	Stack<String> externs_strs;	//����� ���������� ��� ����������� �� ����������� ���������
	Stack<String> args;	//����� ����������
	Stack<s4g_command> commands; //�����
	bool ismarg; //��������� �� ������� �������� ���������� ����������?
	int countstack;
};

//�������� ���������� � ���� ��� ���������� �������� ����������
struct s4g_context
{
	s4g_context(){ table = 0; valid = false; }
	~s4g_context() {}
	s4g_table* table;	//������� � �����������
	bool valid;			//������� �� �������� � ������ ������?
	//��� ����� � ����� ����� ���������� �������, ���������� ��������� ��� ���������� ���������, ����� ��������� ������������
};

//////
//���������� ��������� ������������� ���� tt � str_type
void s4g_get_str_type(s4g_type tt, char* str_type);

s4g_main* s4g_init(const char* name);//�������������� ���������� �������
void s4g_kill(s4g_main* s4gm);//��������� ������ ���������� �������
int s4g_load_file(s4g_main* s4gm, const char* file);//��������� ������ �� �����

void s4g_set_rf(s4g_report_func rf);

//�������� ������ ������, mls - ���������� ����� ������� ����� �������� �������, ���� 0 �� ������� ���� �����
//���������� ���������� ���������� ������
int s4g_call_gc(s4g_main* s4gm,DWORD mls=0);

//������� ��� ������� �� ������� ����� ��������
void s4g_spush_table_null(s4g_main* s4gm,int count_elem);
void s4g_spush_c_func(s4g_main* s4gm, s4g_c_function func);
void s4g_spush_int(s4g_main* s4gm, s4g_int num);
void s4g_spush_uint(s4g_main* s4gm, s4g_uint num);
void s4g_spush_float(s4g_main* s4gm, s4g_float num);
void s4g_spush_str(s4g_main* s4gm, const char* str);
void s4g_spush_bool(s4g_main* s4gm, s4g_bool bf);
void s4g_spush_null(s4g_main* s4gm);
void s4g_spush_precall(s4g_main* s4gm);

//������� ���������� � ������������ ����
//����� ���������� ������� ����������� ����������� �������� � ������� �����
void s4g_sstore_g(s4g_main* s4gm, const char* name); //� ���������� ������������, name ��� ������� ����� ��������� �������� �� ������� �����
void s4g_sstore(s4g_main* s4gm, int index, const char* name);// index � ����� ������ ���� �������, name ��� ����������, � �������� ������� � ������� �����
//table(stack[index])[name] = stack[-1];

//�������� ��������
//����� ���������, ������� ����� �� ������� ����� ���������� ��������
void s4g_sget_g(s4g_main* s4gm, const char* name);	//�� �����������, name - ��� ���������� �������� ������� �����
void s4g_sget(s4g_main* s4gm, int index, const char* name);// index � ����� ������ ���� �������, name ��� ����������
//stack.push(table(stack[index])[name]);

//�������� �� �������� ���������� � ����� �� ������ index �����? 0 ���, 1 ��
int s4g_sis_int(s4g_main* s4gm, int index);
int s4g_sis_uint(s4g_main* s4gm, int index);
int s4g_sis_float(s4g_main* s4gm, int index);
int s4g_sis_str(s4g_main* s4gm, int index);
int s4g_sis_bool(s4g_main* s4gm, int index);
int s4g_sis_c_func(s4g_main* s4gm, int index);
int s4g_sis_s_func(s4g_main* s4gm, int index);
int s4g_sis_table(s4g_main* s4gm, int index);
int s4g_sis_null(s4g_main* s4gm, int index);

//���������� ��� �������� ���������� �� ������ � ����� index
s4g_type s4g_sget_type(s4g_main* s4gm, int index);

//���������� ����������� � ������������ ���� �������� ��������� �� ������ index � �����
s4g_int s4g_sget_int(s4g_main* s4gm, int index);
s4g_uint s4g_sget_uint(s4g_main* s4gm, int index);
s4g_float s4g_sget_float(s4g_main* s4gm, int index);
s4g_bool s4g_sget_bool(s4g_main* s4gm, int index);
const char* s4g_sget_str(s4g_main* s4gm, int index);
s4g_c_function s4g_sget_cfunc(s4g_main* s4gm, int index);

void s4g_spop(s4g_main* s4gm,int count);//����������� �� ����� count ��������
int s4g_sgettop(s4g_main* s4gm);	//���������� ��������� � �����, � ������ ����� ������� �����

//����� �������, narg - ���������� ����������
//������� � ���� ������� ���� ���������� �������, ����� ��������� ���� ���� � ������ ����� ��� �������
//���� narg == 0 � s4g_gettop - narg � ����� �� ������� �� ������
void s4g_call(s4g_main* s4gm, bool call_func = false);

int s4g_cfcount_arg(s4g_main* s4gm);	//���������� ���������� ������� ���� �������� �������

//�������������� ���������� ������� � ����� � �� �����������
//���� narg == 1 �� ������ ������� ������ ������ �������� � ��� �����
s4g_int s4g_cfget_int(s4g_main* s4gm, int narg);
s4g_uint s4g_cfget_uint(s4g_main* s4gm, int narg);
s4g_float s4g_cfget_float(s4g_main* s4gm, int narg);
s4g_bool s4g_cfget_bool(s4g_main* s4gm, int narg);
const char* s4g_cfget_str(s4g_main* s4gm, int narg);
s4g_c_function s4g_cfget_cfunc(s4g_main* s4gm, int narg);

int s4g_cfis_int(s4g_main* s4gm, int narg);
int s4g_cfis_uint(s4g_main* s4gm, int narg);
int s4g_cfis_float(s4g_main* s4gm, int narg);
int s4g_cfis_bool(s4g_main* s4gm, int narg);
int s4g_cfis_str(s4g_main* s4gm, int narg);
int s4g_cfis_cfunc(s4g_main* s4gm, int narg);

#ifndef s4g_h
#define s4g_h

#include <s4g\s4g_conf.h>
#include <core\MemAlloc.h>
#include <s4g\array.h>
#include <s4g\s4g_stack.h>
#include <s4g\aatable.h>


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
	t_pdata = 7, 
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
"pointer_data",
"cfunc",
"sfunc",
"nnull"
};

extern class s4g_arr_lex;
extern struct s4g_node;
extern struct s4g_builder_syntax_tree;
extern class s4g_compiler;

extern class s4g_table;
extern class s4g_value;
extern struct s4g_command;
extern struct s4g_s_function;
extern struct s4g_context;
extern class s4g_gc;
extern class s4g_vm;

#define S4G_COND_TYPE1(val,retval) if (!val){s4g_report(2, "!!!", "value is not init, api function [%s]",__FUNCTION__);	return retval;}
#define S4G_COND_TYPE2(val,retval) if (!val->pdata){s4g_report(2, "!!!", "value is has not data, api function [%s]",__FUNCTION__);	return retval;}
#define S4G_COND_TYPE_12(val,retval) S4G_COND_TYPE1(val,retval) S4G_COND_TYPE2(val,retval)

//������ �������������
struct s4g_main
{
	s4g_main(const char* _name);
	s4g_arr_lex* arr_lex;	//����������� ����������
	s4g_node* gnode;		//����������� ���
	s4g_builder_syntax_tree* bst;	//��������� ���
	s4g_stack<s4g_command>* commands;	//������ � ���� �����
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
	long iddata;	//���� �� �������� ����� ��������� � ������� arrdata � ����� ��� ���������
};

//����������
struct s4g_value
{
	s4g_value();
	~s4g_value();
	
	bool isdelete;	//����� �� ������� ����������
	int typedata;	//��� ������ ��� �������� ������, 0 - ������� ���� ����, 1 - ������ �������
	long iddata;	//������������� s4g_data �� ������� ������������ ��������� ������
	long idvar;		//������������� ���� ���������� � ������� ����������� ��������� ������
	char name[S4G_MAX_LEN_VAR_NAME];
	//������ ��� ����������� �������������!!!
	s4g_data* pdata;
};

//�������
class s4g_table
{
public:
	s4g_table();
	~s4g_table();

	inline void clear();	//�������� �������

	inline s4g_value* getn(long key);			//�������� ���������� �� ����������� ������
	inline s4g_value* gets(const char* str);	//�������� ���������� �� ������
	inline int is_exists_s(const char* str);	//���������� �� ���������� � ������ ������
	inline bool is_exists_n(long key);			//���������� �� ���������� �� ���������� �����

	inline long is_exists_s2(const char* str,s4g_value** tval);	//���������� �� ���������� � ������ ������
	inline bool is_exists_n2(long key, s4g_value** tval);	//���������� �� ���������� �� ���������� �����

	inline long get_key(const char* name);

	inline void add_val_s(const char* name, s4g_value* val);	//�������� ���������� � ��������� �� ��� � ������� �������
	inline void add_val_n(long num, s4g_value* val);			//�������� ���������� �� �����
	inline void add_val(s4g_value* val);						//�������� ���������� � ����� �������

	inline long size();						//������ ������� � ���������
	inline const char* get_name_id(long id);//�������� ��� �� id

	inline void reserve(int count_elem);

protected:
	struct table_desc
	{
		char Name[S4G_MAX_LEN_VAR_NAME];
		s4g_value* Value;
	};
	long count_obj;
	Array<table_desc*> Arr;
	MemAlloc<table_desc, 16> Mem;
};



//������� ������
class s4g_gc
{
public:
	s4g_gc();

#define def_cr_val_null(tval,tdata,name) \
	tval = MemValue.Alloc(); \
	tval->typedata = typedata; \
	if (name)\
		strcpy(tval->name, name);\
	else\
		strcpy(tval->name, "#");\
	arrvar.push(tval); \
	tval->idvar = arrvar.count_obj; \
	tdata = MemData.Alloc(); \
	tdata->typedata = typedata; \
	tval->iddata = arrdata.count_obj; \
	tdata->iddata = arrdata.count_obj; \
	tval->pdata = tdata; \
	arrdata.push(tdata);

	//�������� ����������
	inline s4g_value* cr_val_null(const char* name=0);
	inline s4g_value* cr_val_pdata(s4g_pdata pdata,const char* name = 0);
	inline s4g_value* cr_val_table_null(const char* name = 0);
	inline s4g_value* cr_val_int(s4g_int num, const char* name = 0);
	inline s4g_value* cr_val_uint(s4g_uint num, const char* name = 0);
	inline s4g_value* cr_val_float(s4g_float num, const char* name = 0);
	inline s4g_value* cr_val_bool(s4g_bool bf, const char* name = 0);
	inline s4g_value* cr_val_str(const char* str, const char* name = 0);
	inline s4g_value* cr_val_table(s4g_table* tt, const char* name = 0);
	inline s4g_value* cr_val_s_func(const char* name = 0);
	inline s4g_value* cr_val_s_func(s4g_s_function* func, const char* name = 0);
	inline s4g_value* cr_val_c_func(s4g_c_function func, const char* name = 0);
	inline s4g_value* cr_val(int _type, const char* _val, const char* name = 0);	//������� ���������� �� _val � ����� _type
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
	inline s4g_pdata get_pdata(s4g_value* val);

	inline s4g_type get_type(s4g_value* val);	//�������� ��� ����������

	//������ � �����������
	inline void add_mem_contexts();
	inline long add_new_context(s4g_table** tt);	//������� � �������� ����� ��������, ���������� id ���������, � � tt ���������� ��������� �� �������
	inline long add_context(s4g_table* tt);			//�������� �������� ���������� �� �������, ���������� id ������������ ���������
	inline void activate_prev(long lastidctx);		//���������� ���������� ��������� �� lastidctx (��� �������� ���� �������� ��� ������ deactivate_prev)
	inline long deactivate_prev();					//�������������� ��� ���������� ���������, ���������� ����� ��������� ������� ������������� ���������
	inline void del_top_context(bool clear);				//�������� �������� ��� �������� � ��� ������ ������ ������ ��� � ����
	inline void clear_context(long id);
	inline void remove_context(long id);			//�������� �������� ��� �� ������ � ��� ������ ������� ������ �������� �� �� ��� ������
	inline void set_ctx_for_del(s4g_context* ctx);	//�������� �������� ��� ��������

	//���������� �� ���������� � ������ str �� ���� ���������� ����������
	//���� �� �� ���������� id ��������� � ������� �������, � val ���������� ��������� �� ����������
	inline long ctx_is_exists_s(const char* str, s4g_value** val);	
	
	//��������� ������ ������
	void clear(DWORD mls);
	inline void begin_of_const_data();
	inline void end_of_const_data();

	int typedata;	//��� ����������� ������, 0 - ���� ������ �� ����� �� ������, 1 - �� �������
	//������ � �������� ������� ������ ������� �� ���������, ������ � ����������� ������� ������� ������ ���������� ��������

protected:
	
	s4g_stack<s4g_value*, S4G_RESERVE_VALUE> arrvar;	//������ ����������
	s4g_stack<s4g_data*, S4G_RESERVE_DATA> arrdata;	//������ ������
	s4g_stack<s4g_context*, 1024> delarrcontexts;	//������ ���������� ������� ��� ���� ���������� � ��������� � ��������
	s4g_stack<s4g_context*, S4G_RESERVE_CONTEXTS> arrcurrcontexts;//������ ������������ � ������ ������ ����������
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

	long count_nd_data;
	long count_nd_value;
};

//��� �������
struct s4g_s_function
{
	s4g_s_function(){ externs = 0; ismarg = false; main_extern = 0; marg_val = 0; margtable = 0; }
	~s4g_s_function(){ /*mem_delete(externs);*/ }
	s4g_value* externs_val;
	s4g_table* externs;	//����������� ���������� � ����������� ���������
	s4g_stack<String> externs_strs;	//����� ���������� ��� ����������� �� ����������� ���������
	int main_extern;
	s4g_stack<String> args;	//����� ����������
	s4g_stack<s4g_command> commands; //�����
	bool ismarg; //��������� �� ������� �������� ���������� ����������?
	s4g_value* marg_val;
	s4g_table* margtable;	//����������� ���������� � ����������� ���������
};

//�������� ���������� � ���� ��� ���������� �������� ����������
struct s4g_context
{
	s4g_context(){ table = 0; valid = false; oldtable = 0; }
	~s4g_context() {}
	s4g_table* table;	//������� � �����������
	s4g_table* oldtable;	//������� � �����������
	bool valid;			//������� �� �������� � ������ ������?
	//��� ����� � ����� ����� ���������� �������, ���������� ��������� ��� ���������� ���������, ����� ��������� ������������
};

//////

#endif
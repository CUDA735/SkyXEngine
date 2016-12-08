
#define S4G_MAX_LEN_VAR_NAME 64
#define S4G_MAX_LEN_STR_IN_FILE 1024

#define mem_delete(data) delete data;data = 0;
#define mem_delete_a(data) delete[] data;data = 0;

#include <s4g\array.h>
#include <s4g\stack.h>
#include <s4g\aatable.h>

#define S4G_MAX_CALL 200	//������������ ���������� ������� (���������� � ���������)
#define S4G_GLOBAL_NM "_g"	//��������� � ������� � ����������� ������������ ����
#define S4G_MARG "args"

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
	t_null = 0,
	t_table = 1,
	t_string = 2,
	t_float = 3,
	t_int = 4,
	t_uint = 5,
	t_bool = 6,
	t_user_data = 7, //unsupported
	t_cfunc = 8,	//unsupported
	t_sfunc = 9,
	t_nn = 10,
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


//������ ������������
struct s4g_main
{
	s4g_main();
	s4g_arr_lex* arr_lex;	//����������� ����������
	s4g_node* gnode;		//����������� ���
	s4g_builder_syntax_tree* bst;	//��������� ���
	Stack<s4g_command>* commands;	//������ � ���� �����
	s4g_compiler* compiler;			//����������
	s4g_vm* vmachine;				//����������� ������
	s4g_gc* gc;						//������� ������
	char strerror[1024];			//��������� �� ������
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
	s4g_value(long lexid = -1);
	~s4g_value();
	
	bool isdelete;	//����� �� ������� ����������
	int typedata;	//��� ������ ��� �������� ������, 0 - ������� ���� ����, 1 - ������ �������
	long nlexid;	//������������� ������� ������� ������������� �������� ����������
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

	inline void add_val_s(const char* name, s4g_value* val, long lexid);	//�������� ���������� � ��������� �� ��� � ������� �������
	inline void add_val_n(long num, s4g_value* val, long lexid);			//�������� ���������� �� �����
	inline void add_val(s4g_value* val, long lexid);						//�������� ���������� � ����� �������

	inline long size();						//������ ������� � ���������
	inline const char* get_name_id(long id);//�������� ��� �� id

protected:
	AATable<s4g_value> arr_value;
};

//������� ������
class s4g_gc
{
public:
	s4g_gc();

	//�������� ����������
	inline s4g_value* cr_val_null(long lexid);
	inline s4g_value* cr_val_table_null(long lexid);
	inline s4g_value* cr_val_int(s4g_int num, long lexid);
	inline s4g_value* cr_val_uint(s4g_uint num, long lexid);
	inline s4g_value* cr_val_float(s4g_float num, long lexid);
	inline s4g_value* cr_val_bool(s4g_bool bf, long lexid);
	inline s4g_value* cr_val_str(const char* str, long lexid);
	inline s4g_value* cr_val_table(s4g_table* tt, long lexid);
	inline s4g_value* cr_val_s_func(s4g_s_function* func, long lexid);
	inline s4g_value* cr_val_c_func(s4g_c_function func, long lexid);
	inline s4g_value* cr_val(int _type, const char* _val, long lexid);	//������� ���������� �� _val � ����� _type
	inline s4g_value* cr_val_nn(long lexid);	//������� ����� 0 (��� ������� ����: -123 ����� 0-123)

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
	inline long GetNewIDVal();	//�������� ��������� ���� ��� ������ ����������, ���� ��� ��������� ���� �� ������� -1
	inline long GetNewIDData();	//�������� ��������� ���� ��� ������ ��������, ���� ��� ��������� ���� �� ������� -1
	Array<s4g_value*> arrvar;	//������ ����������
	Array<s4g_data*> arrdata;	//������ ������
	Array<s4g_context*> oldarrcontexts;	//������ ���������� ������� ��� ���� ���������� � ��������� � ��������
	Array<s4g_context*> arrcurrcontexts;//������ ������������ � ������ ������ ����������
};

//��� �������
struct s4g_s_function
{
	s4g_s_function(){ externs = 0; ismarg = false; }
	~s4g_s_function(){ mem_delete(externs); }
	s4g_table* externs;	//����������� ���������� � ����������� ���������
	Stack<String> externs_strs;	//����� ���������� ��� ����������� �� ����������� ���������
	Stack<String> args;	//����� ����������
	Stack<s4g_command> commands; //�����
	bool ismarg; //��������� �� ������� �������� ���������� ����������?
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

s4g_main* s4g_init();

void s4g_push_c_func(s4g_main* sm,s4g_c_function func);
void s4g_store_g(s4g_main* sm, const char* name, s4g_c_function func);

int s4g_load_file(s4g_main* s4gm,const char* file);
//int s4g_call(s4g_machine* sm,int narg,int result);

#ifndef s4g_h
#define s4g_h

extern "C"
{

#include "string.cpp"
#include <limits.h>

#define S4G_VERSION "0.9"
#define S4G_COPYRIGHT "Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017"
#define S4G_SITE "s4g.su"

//����� ������������ ������� ����� � ���������� ������ ������������� ��������� �� ����
//��� �������� � dll ���������� �������� S4G_BUILD_DLL � S4G_DLL
//��� ������� �� dll ���������� �������� S4G_BUILD_DLL � S4G_EXE
#if defined(S4G_BUILD_DLL)
	#if defined(S4G_EXE)
	#define S4G_API __declspec (dllimport)
	#elif defined(S4G_DLL)
	#define S4G_API  __declspec (dllexport)
	#endif
#else
#define S4G_API extern
#endif

//��� ���� ������ ������� ����� ���� ������������ � ��������
enum s4g_type
{
	t_none = -1,
	t_null = 0,		//������ ��������
	t_table = 1,	//������� (������������� ������)
	t_string = 2,	//��������� �������� (���������������� ������)
	t_float = 3,	//����� � ��������� �������
	t_int = 4,		//�������� ����� ���������� �����
	t_uint = 5,		//�������� ����� ���������� �����
	t_bool = 6,		//���������� ��������
	t_pdata = 7,	//��������� �� ���������������� ������
	t_cfunc = 8,	//�(++) �������
	t_sfunc = 9,	//���������� �������
	t_nnull = 10,	//����� 0, ����������� � ��������� � ������� �������
};

struct s4g_main;	//������ �������������� ����� �(++) � ���������
struct s4g_value;	//����������-��������
struct s4g_table;	//�������

#define S4G_CREATE_VAR "S4G_CREATE_VAR"

//const
#define S4G_MAX_LEN_TYPE_NAME 64	//������������ ����� ����� ����
#define S4G_MAX_LEN_VAR_NAME 64		//������������ ����� ����� ����������
#define S4G_MAX_LEN_STR_IN_FILE 1024//������������ ����� ������������ �����

#define S4G_MAX_CALL 1000	//������������ ���������� ������� (����������� � ���������)
#define S4G_MAX_ENCLOSURE 100	//������������ ���������� ��������� ������
#define S4G_GLOBAL_NM "_g"	//��������� � ������� � ����������� ������������ ����
#define S4G_MARG "args"		//������� ��� ��������� � ���������� � ������ ���� ������� ��������� �������������� ���������� ����������

//����� ��������� - ���������������� ������ ��� ����� ��������� ������������ ��������
//������ ������ ��������� - ������ ���������� ������ ��� �������� ����� ���������
//(��� ���� ��������): �� ��� �� ���������� ����� ������������� �������������� ������ � ����� ���������� ����������� �������

#define S4G_RESERVE_STACK_EXE 1000	//������ ��������� ��� ����� ����������

#define S4G_RESERVE_VALUE 10000		//������ ��������� ��� ����������
#define S4G_RESERVE_VALUE_MEM 10000	//������ ������ ��������� ��� ����������

#define S4G_RESERVE_DATA 10000		//������ ��������� ��� ������
#define S4G_RESERVE_DATA_MEM 10000	//������ ������ ��������� ��� ������

#define S4G_RESERVE_CONTEXTS 100	//������ ��������� ��� ����������
#define S4G_ADD_MEM_CONTEXTS 16		//���������� ����������� ���������� �� ������ ������ ��������
#define S4G_RESERVE_CONTEXTS_MEM 100//������ ������ ��������� ��� ����������

#define S4G_RESERVE_STRING_MEM 1000	//������ ������ ��������� ��� �����

#define S4G_RESERVE_SFUNC_MEM 1000	//������ ������ ��������� ��� ���������� �������

#define S4G_RESERVE_TABLE_MEM 1000	//������ ������ ��������� ��� ������
#define S4G_RESERVE_TABLE_ELEM 16	//�� ������� ��������� ����� ��������������� ����� � ��������

//������ ���������
#define S4G_NOTICE 0	//�����������
#define S4G_WARNING 1	//��������������
#define S4G_ERROR 2		//������

//�������������� ����� ��������� ��� ����� ������ ������� (��� �������)
#define s4g_breakpoint _asm { int 3 }

//������������� ����
#define s4g_int long
#define s4g_uint unsigned long
#define s4g_float float
#define s4g_bool short int
#define s4g_pdata void*

//��� ��(++) �������
//���� ������� ���������� �������� ������ ���� �� ������ ��������� ������ � ������ ��������� ���������� ����
//��� ��������� �������� (>0) �� ����� ������
typedef int(*s4g_c_function) (s4g_main* vm);

//��� ������� ������ ���������� � ��������� ������
typedef void(*s4g_report_func) (s4g_main* s4gm, int level, const char* name_ss, const char* format, ...);

//����������� ������� ������ ��������� (��������� ����������� api)
void s4g_report(s4g_main* s4gm, int level, const char* name_ss, const char* format, ...)
{
#if defined(_WINDOWS)
	AllocConsole();
	freopen("CONOUT$", "wt", stdout);
#endif
	char buf[4096];
	va_list va;
	va_start(va, format);
	vsprintf_s(buf, sizeof(buf), format, va);
	va_end(va);

	if (level == 0)
		fprintf(stdout, "s4g %s notice: %s\n", name_ss, buf);
	else if (level == 1)
		fprintf(stdout, "s4g %s warning: %s\n", name_ss, buf);
	else
	{
		fprintf(stdout, "s4g %s error: %s\n", name_ss, buf);
		Sleep(50000);
		exit(1);
	}
}

s4g_report_func s4g_rf = s4g_report;

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

/////

#define S4G_NM_GLOBAL INT_MIN	//���������� ������������ ����
#define S4G_NM_SYS INT_MIN+1		//��������/��������� ����������� ����
//���������� ����������� ���� �������� �� ��������� ���������� ������ ����� _g (��� ��������� � S4G_GLOBAL_NM), � ���������� ��� ������� �������� � ����
//��������/��������� ����������� ���� �������� �������� ��� ����� ���������, ������� � ���� ������� ����������� ����� �������������� ��� ��� ���������� ��� ������� ������������� ������ ��������

//���������� ��������� ������������� ���� tt � str_type
S4G_API const char* s4g_get_str_type(s4g_type tt, char* str_type = 0);

S4G_API s4g_main* s4g_init(const char* name);//�������������� ���������� �������
S4G_API void s4g_kill(s4g_main* s4gm);//��������� ������ ���������� �������
S4G_API int s4g_load_file(s4g_main* s4gm, const char* file);//��������� ������ �� �����
S4G_API int s4g_load_str(s4g_main* s4gm, const char* str);//��������� ������ �� ������

S4G_API void s4g_set_rf(s4g_report_func rf);	//���������� ����� ������� ������ ���������
S4G_API void s4g_gen_msg(s4g_main* s4gm, int level, const char* format, ...);	//������������ ���������

//�������� ������ ������, ���������� ���������� ���������� ������
S4G_API int s4g_call_gc(s4g_main* s4gm);

/*
�(++) => stack
*/

//������� ��� ������� �� ������� ����� ��������
S4G_API void s4g_spush_table_null(s4g_main* s4gm, int count_elem);
S4G_API void s4g_spush_c_func(s4g_main* s4gm, s4g_c_function func);
S4G_API void s4g_spush_int(s4g_main* s4gm, s4g_int num);
S4G_API void s4g_spush_uint(s4g_main* s4gm, s4g_uint num);
S4G_API void s4g_spush_float(s4g_main* s4gm, s4g_float num);
S4G_API void s4g_spush_str(s4g_main* s4gm, const char* str);
S4G_API void s4g_spush_bool(s4g_main* s4gm, s4g_bool bf);
S4G_API void s4g_spush_pdata(s4g_main* s4gm, s4g_pdata pdata);
S4G_API void s4g_spush_null(s4g_main* s4gm);
S4G_API void s4g_spush_precall(s4g_main* s4gm);
S4G_API void s4g_spush_value(s4g_main* s4gm, s4g_value* val);

/*
stack => script
*/

//������� ���������� � ������������ ����
//����� ���������� ������� ����������� ����������� �������� � ������� �����
S4G_API void s4g_sstore(s4g_main* s4gm, int index, const char* name);
//index � ����� ������ ���� �������, ���� S4G_NM_GLOBAL ���� ���� ��������� � ���������� ������������, ���� S4G_NM_SYS ���� � ��������/���������
//name ��� ����������, � �������� ������� � ������� �����
//table(stack[index])[name] = stack[-1];

//�������� ��������
//����� ���������, ������� ����� �� ������� ����� ���������� ��������
S4G_API void s4g_sget(s4g_main* s4gm, int index, const char* name);
//index � ����� ������ ���� �������, ���� S4G_NM_GLOBAL ���� ������� �� ����������� ������������, ���� S4G_NM_SYS ���� �� ���������/����������
//name ��� ����������, � �������� ������� � ������� �����
//stack.push(table(stack[index])[name]);

/*
stack => C(++)
*/

//�������� �� �������� ���������� � ����� �� ������ index �����? 0 ���, 1 ��
S4G_API int s4g_sis_int(s4g_main* s4gm, int index);
S4G_API int s4g_sis_uint(s4g_main* s4gm, int index);
S4G_API int s4g_sis_float(s4g_main* s4gm, int index);
S4G_API int s4g_sis_str(s4g_main* s4gm, int index);
S4G_API int s4g_sis_bool(s4g_main* s4gm, int index);
S4G_API int s4g_sis_c_func(s4g_main* s4gm, int index);
S4G_API int s4g_sis_s_func(s4g_main* s4gm, int index);
S4G_API int s4g_sis_table(s4g_main* s4gm, int index);
S4G_API int s4g_sis_pdata(s4g_main* s4gm, int index);
S4G_API int s4g_sis_null(s4g_main* s4gm, int index);

//���������� ��� �������� ���������� �� ������ � ����� index
S4G_API s4g_type s4g_sget_type(s4g_main* s4gm, int index);

//���������� ����������� � ������������ ���� �������� ��������� �� ������ index � �����
S4G_API s4g_int s4g_sget_int(s4g_main* s4gm, int index);
S4G_API s4g_uint s4g_sget_uint(s4g_main* s4gm, int index);
S4G_API s4g_float s4g_sget_float(s4g_main* s4gm, int index);
S4G_API s4g_bool s4g_sget_bool(s4g_main* s4gm, int index);
S4G_API const char* s4g_sget_str(s4g_main* s4gm, int index);
S4G_API s4g_c_function s4g_sget_cfunc(s4g_main* s4gm, int index);
S4G_API s4g_pdata s4g_sget_pdata(s4g_main* s4gm, int index);

S4G_API void s4g_spop(s4g_main* s4gm, int count);	//����������� �� ����� count ��������
S4G_API int s4g_sgettop(s4g_main* s4gm);			//���������� ��������� � �����, � ������ ����� ������� �����


//����� �������/���������� �������
//������� � ���� ������� ���� ���������� �������, ����� ��������� ���� ���� � ������ ����� s4g_call
S4G_API void s4g_call(s4g_main* s4gm, bool call_func = false);

/*
script => C(++) function
*/

S4G_API int s4g_cfcount_arg(s4g_main* s4gm);				//���������� ���������� ������� ���� �������� �������
S4G_API s4g_value* s4g_cfget_arg(s4g_main* s4gm, int narg);	//���������� s4g_value �������� ���������

//�������������� ��������� ������� � ����� � �� �����������
//���� narg == 1 �� ������ ������� ������ ������ �������� � ��� �����
S4G_API s4g_int s4g_cfget_int(s4g_main* s4gm, int narg);
S4G_API s4g_uint s4g_cfget_uint(s4g_main* s4gm, int narg);
S4G_API s4g_float s4g_cfget_float(s4g_main* s4gm, int narg);
S4G_API s4g_bool s4g_cfget_bool(s4g_main* s4gm, int narg);
S4G_API const char* s4g_cfget_str(s4g_main* s4gm, int narg);
S4G_API s4g_c_function s4g_cfget_cfunc(s4g_main* s4gm, int narg);
S4G_API s4g_pdata s4g_cfget_pdata(s4g_main* s4gm, int narg);

//�������� �� �������� ��������� ������� �� ������ narg (��������� � 1) �����? 0 ���, 1 ��
S4G_API int s4g_cfis_null(s4g_main* s4gm, int narg);
S4G_API int s4g_cfis_int(s4g_main* s4gm, int narg);
S4G_API int s4g_cfis_uint(s4g_main* s4gm, int narg);
S4G_API int s4g_cfis_float(s4g_main* s4gm, int narg);
S4G_API int s4g_cfis_bool(s4g_main* s4gm, int narg);
S4G_API int s4g_cfis_str(s4g_main* s4gm, int narg);
S4G_API int s4g_cfis_table(s4g_main* s4gm, int narg);
S4G_API int s4g_cfis_cfunc(s4g_main* s4gm, int narg);
S4G_API int s4g_cfis_pdata(s4g_main* s4gm, int narg);

S4G_API s4g_type s4g_cfget_type(s4g_main* s4gm, int narg);	//���������� ��� ���������
S4G_API const char* s4g_cfget_str_type(s4g_main* s4gm, int narg, char* str = 0);//���������� ��������� � ������������ ���� ���������


//DEBUG

S4G_API const char* s4g_value_name(s4g_value* value);			//���������� ��� ����������
S4G_API long s4g_table_size(s4g_table* ttable);					//���������� ������ �������
S4G_API s4g_value* s4g_table_get(s4g_table* ttable, long key);	//���������� s4g_value* ������� ������������� � ������� �� ����� key, ���� ����, ����� 0

S4G_API const char* s4g_stack_trace(s4g_main* s4gm);	//���������� ������ � ������� ���������� ����������� ����� �������

S4G_API const char* s4g_dbg_get_curr_file(s4g_main* s4gm, char* str = 0);	//���������� ���� �� ����� ������� ������� ����������� � ������ ������ (���� str �� ���������� � ����)
S4G_API long s4g_dbg_get_curr_str(s4g_main* s4gm, char* str = 0);			//���������� ����� ������ ����� ������� ������� ����������� � ������ ������ (���� str �� ���������� � ����)
S4G_API const char* s4g_dbg_get_curr_func(s4g_main* s4gm, char* str = 0);	//���������� ������� ������� ����������� � ������ ������ (���� str �� ���������� � ����)


//Pre Process

S4G_API bool s4g_pp_is_def(s4g_main* s4gm, const char* name_def);
S4G_API void s4g_pp_def(s4g_main* s4gm, const char* def_str);
S4G_API void s4g_pp_undef(s4g_main* s4gm, const char* name_def);
S4G_API void s4g_pp_add_inc_path(s4g_main* s4gm, const char* path);
}
#endif
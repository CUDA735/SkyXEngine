
#ifndef s4g_api_h
#define s4g_api_h

//���������� ��������� ������������� ���� tt � str_type
extern void s4g_get_str_type(s4g_type tt, char* str_type);

s4g_main* s4g_init(const char* name);//�������������� ���������� �������
void s4g_kill(s4g_main* s4gm);//��������� ������ ���������� �������
int s4g_load_file(s4g_main* s4gm, const char* file);//��������� ������ �� �����
int s4g_load_str(s4g_main* s4gm, const char* str);//��������� ������ �� ������

void s4g_set_rf(s4g_report_func rf);

//�������� ������ ������, mls - ���������� ����� ������� ����� �������� �������, ���� 0 �� ������� ���� �����
//���������� ���������� ���������� ������
int s4g_call_gc(s4g_main* s4gm, DWORD mls = 0);

//������� ��� ������� �� ������� ����� ��������
void s4g_spush_table_null(s4g_main* s4gm, int count_elem);
void s4g_spush_c_func(s4g_main* s4gm, s4g_c_function func);
void s4g_spush_int(s4g_main* s4gm, s4g_int num);
void s4g_spush_uint(s4g_main* s4gm, s4g_uint num);
void s4g_spush_float(s4g_main* s4gm, s4g_float num);
void s4g_spush_str(s4g_main* s4gm, const char* str);
void s4g_spush_bool(s4g_main* s4gm, s4g_bool bf);
void s4g_spush_pdata(s4g_main* s4gm, s4g_pdata pdata);
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
int s4g_sis_pdata(s4g_main* s4gm, int index);
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
s4g_pdata s4g_sget_pdata(s4g_main* s4gm, int index);

void s4g_spop(s4g_main* s4gm, int count);//����������� �� ����� count ��������
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

#endif
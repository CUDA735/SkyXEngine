
#pragma once

enum s4g_vm_command
{
	mc_halt = -1,	//���������� ������� ����������
	mc_fetch,		//�������� �� ������� ����� �������� ����������
	mc_fetch_get,	//�������� �������� �� �������, ���� ���������� ������� ��� mc_fetch
	mc_store,		//��������� � ���������� �������� � ������� �����
	mc_push,		//�������� �� ������� �����
	mc_pop,			//������� �������� � ������� �����
	mc_add,
	mc_sub,
	mc_mul,
	mc_div,
	mc_new_table,	//������� �������
	mc_add_in_table,//�������� � �������
	mc_call,		//����� �������
};

#include <s4g\s4g_compiler.h>

class s4g_vm
{
public:
	s4g_vm(){ vgvars = new s4g_value(); vgvars->init_table(&gvars); }

	int run(Stack<s4g_command>* commands,s4g_table* vars);

	//
	inline void com_fetch(s4g_value* val);
	inline void com_fetch_get(s4g_value* val);
	inline void com_store();
	inline void com_add_in_table();
	inline void com_call(s4g_value* val);
	inline void com_new_table();
	//

	s4g_table gvars;	//���������� ������������ ���� _g
	s4g_value* vgvars;	//���������� �������� � ���� ���������� ������������ ����
	s4g_table* curr_vars;	//������� ������������� ������������ ����, ��� ����������� ������� �� ������������ ���� �������
	Stack<s4g_value*> execute;	//���� ���������� ������

	bool cfetchget;		//���� �� ���������� ������� ���� fetch ���� fetch_get
	bool cfetchgetarg;	//���� �� ���������� ������� fetch_get � ���������� ��� ���
};


#pragma once

enum s4g_vm_command
{
	mc_halt = -1,	//���������� ������� ����������
	mc_fetch,		//�������� �� ������� ����� �������� ����������
	mc_fetch_cr,	//������� � �������� �� ������� ����� �������� ����������
	mc_fetch_get,	//�������� �������� �� �������, ���� ���������� ������� ��� mc_fetch
	mc_fetch_get_cr,//������� �������� � �������, ���� ���������� ������� ��� mc_fetch
	mc_store,		//��������� � ���������� (-1 �� ��������� � ������� �����) �������� � ������� �����
	mc_end,			//��� ����������������, ��������� ����� ����� ���������� �� ������
	mc_mstore,		//������������������
	mc_push,		//�������� �� ������� �����
	mc_pop,			//������� �������� � ������� �����
	mc_add,			//-1 + 0
	mc_sub,			//-1 - 0
	mc_mul,			//-1 * 0
	mc_div,			//-1 / 0
	mc_new_table,	//������� ������� � �������� �� ������� �����
	mc_add_in_table,//�������� � ������� ������� ����� �� �������
	mc_call,		//����� �������
};

#include <s4g\s4g_compiler.h>

//��������� ����������� ����������� ���������� ��������� ��� ������ ������� � ���������� ��� ���������� �������
struct s4g_call_data
{
	s4g_call_data()
	{
		coms = 0;
		vars = 0;
		cfetchget = cfetchgetarg = false;
		cfetchpushstore = 0;
		id_curr_com = lastidctx = idnewctx = idexternctx = -1;
		namef = "";
	}

	s4g_call_data(
		Stack<s4g_command>* _coms, 
		s4g_table* _vars, 
		bool _cfetchget, 
		bool _cfetchgetarg, 
		int _cfetchpushstore, 
		long _id_curr_com, 
		long _lastidctx, 
		long _idnewctx,
		long _idexternctx,
		const char* _namef)
	{
		coms = _coms;
		vars = _vars;
		cfetchget = _cfetchget;
		cfetchgetarg = _cfetchgetarg;
		cfetchpushstore = _cfetchgetarg;
		id_curr_com = _id_curr_com;
		lastidctx = _lastidctx;
		idnewctx = _idnewctx;
		idexternctx = _idexternctx;
		namef = _namef;
	}

	Stack<s4g_command>* coms;	//������� ����������
	s4g_table* vars;			//������� � ����������� (���������)
	bool cfetchget;				
	bool cfetchgetarg;	
	int cfetchpushstore;
	long id_curr_com;
	long lastidctx;
	long idnewctx;
	long idexternctx;

	String namef;	// ��� ������� ������� ��������� � �������������� ���������� �������� ��������
};

class s4g_vm
{
public:
	s4g_vm(s4g_gc* _gc)
	{ 
		gc = _gc;  
		gc->add_new_context(&gvars); 
		vgvars = gc->cr_val_table(gvars, -2); 
		strerror[0] = 0; error = 0;
		cfetchpushstore = 0;
		curr_vars = 0;
	}

	int run(Stack<s4g_command>* commands,s4g_table* vars);

	//������� ��� ���������� ���� ����
	inline int com_fetch(s4g_value* val, bool is_cr);
	inline int com_fetch_get(s4g_value* val, bool is_cr);
	inline int com_store();
	inline int com_mstore(s4g_value* arg, int val_end);
	inline int com_add_in_table();
	inline int com_call(s4g_value* val);
	inline int com_new_table(s4g_value* val);

	inline int com_retprev(long* pc);	//���������� ���������� ��������� ������, � ������ ����� ������� ���������� ��� ���� �������

	inline int com_add();
	inline int com_sub();
	inline int com_mul();
	inline int com_div();
	//

	Stack<s4g_command>* curr_comm;
	long id_curr_com;

	s4g_table* gvars;	//���������� ������������ ���� _g
	s4g_value* vgvars;	//���������� �������� � ���� ���������� ������������ ����
	s4g_table* curr_vars;	//������� ������������� ������������ ����, ��� ����������� ������� �� ������������ ���� �������
	Stack<s4g_value*> execute;	//���� ���������� ������

	int error;	//���� �� ������? -1 ����, ��������� ��� � �����
	char strerror[1024];	//������ ������

	s4g_arr_lex* arr_lex;
	s4g_gc* gc;
	s4g_main* s4gm;
	
	bool cfetchget;		//���� �� ���������� ������� ���� fetch ���� fetch_get
	bool cfetchgetarg;	//���� �� ���������� ������� fetch_get � ���������� ��� ���
	int cfetchpushstore;//���������� ��������� fetch push store, ���� �� �� ������ = 3, ����� ��� com_store

	Stack<s4g_call_data> callstack;	//���� ������� � ����������� ���������� ����������
};

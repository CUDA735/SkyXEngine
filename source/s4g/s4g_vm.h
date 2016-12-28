
#ifndef s4g_vm_h
#define s4g_vm_h



enum s4g_vm_command
{
	mc_halt = 0,	//���������� ������� ����������
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
	mc_precall,		//��������� � ��� ��� ������ ����� ������� �������, �������� � ������ ��������� ������� ������ �����
	mc_call,		//����� �������
};

#define S4G_VM_OP_ARIF_ERROR_TYPE1 \
	s4g_lexeme* tmplexs = this->arr_lex->get(curr_comm->get(id_curr_com).lexid - 1);\
	error = -1;\
	char strtype[12];\
	s4g_get_str_type(ttype1, strtype);\
	sprintf(this->strerror, "[%s]:%d - attempt to perform arithmetic on arg #1 '%s' (a '%s' value)", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str, strtype);\
	return;

#define S4G_VM_OP_ARIF_ERROR_TYPE2 \
	s4g_lexeme* tmplexs = this->arr_lex->get(curr_comm->get(id_curr_com-1).lexid); \
	error = -1; \
	char strtype[12]; \
	s4g_get_str_type(ttype2, strtype); \
	sprintf(this->strerror, "[%s]:%d - attempt to perform arithmetic on arg #2 '%s' (a '%s' value)", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str, strtype); \
	return;

#define S4G_VM_OP_ARIF_ERROR_UNSUN_UNRES \
	s4g_lexeme* tmplexs = this->arr_lex->get(curr_comm->get(id_curr_com - 1).lexid); \
	error = -1; \
	char strtype[12]; \
	s4g_get_str_type(ttype2, strtype); \
	sprintf(this->strerror, "[%s]:%d - '%s' unary symbol is unresolved to '%s' type", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str, strtype); \
	return;


#include <s4g\s4g_compiler.h>

//��������� ����������� ����������� ���������� ��������� ��� ������ ������� � ���������� ��� ���������� �������
struct s4g_call_data
{
	s4g_call_data()
	{
		coms = 0;
		vars = 0;
		cfetchget = 3;
		cfetchgetarg = false;
		cfetchpushstore = 0;
		id_curr_com = lastidctx = idnewctx = idexternctx = -1;
		namef[0] = 0;
	}

	s4g_call_data(
		s4g_stack<s4g_command>* _coms,
		s4g_table* _vars, 
		int _cfetchget,
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
		if (_namef)
			strcpy(namef,_namef);
	}

	s4g_stack<s4g_command>* coms;	//������� ����������
	s4g_table* vars;			//������� � ����������� (���������)
	int cfetchget;				
	bool cfetchgetarg;	
	int cfetchpushstore;
	long id_curr_com;
	long lastidctx;
	long idnewctx;
	long idexternctx;

	char namef[S4G_MAX_LEN_VAR_NAME];	// ��� ������� ������� ��������� � �������������� ���������� �������� ��������
};

class s4g_vm
{
public:
	
	s4g_vm(s4g_gc* _gc)
	{ 
		gc = _gc; 
		gc->add_new_context(&gvars); 
		vgvars = gc->cr_val_table(gvars); 
		strerror[0] = 0; error = 0;
		cfetchpushstore = 0;
		curr_vars = 0;
		runexe = false;

		arropf[mc_halt] = &s4g_vm::com_halt;
		arropf[mc_fetch_get] = &s4g_vm::com_fetch_get;
		arropf[mc_fetch_get_cr] = &s4g_vm::com_fetch_get;
		arropf[mc_fetch] = &s4g_vm::com_fetch;
		arropf[mc_fetch_cr] = &s4g_vm::com_fetch;
		arropf[mc_store] = &s4g_vm::com_store;
		arropf[mc_end] = &s4g_vm::com_end;
		arropf[mc_mstore] = &s4g_vm::com_mstore;

		arropf[mc_new_table] = &s4g_vm::com_new_table;
		arropf[mc_add_in_table] = &s4g_vm::com_add_in_table;
		arropf[mc_push] = &s4g_vm::com_push;
		arropf[mc_pop] = &s4g_vm::com_pop;
		arropf[mc_precall] = &s4g_vm::com_precall;
		arropf[mc_call] = &s4g_vm::com_call;
		
		arropf[mc_add] = &s4g_vm::com_add;
		arropf[mc_sub] = &s4g_vm::com_sub;
		arropf[mc_mul] = &s4g_vm::com_mul;
		arropf[mc_div] = &s4g_vm::com_div;

		for (int i = 0; i < S4G_MAX_CALL; i++)
		{
			callstack.push(new s4g_call_data());
			int qwert = 0;
		}

		callstack.init_size(0);
	}

	int run(s4g_stack<s4g_command>* commands, s4g_table* vars);

	//������� ��� ���������� ���� ����
	inline void com_fetch();
	inline void com_fetch_get();
	inline void com_store();
	inline void com_end();
	inline void com_mstore();
	inline void com_add_in_table();
	inline void com_precall();
	inline void com_call();
	inline void com_new_table();

	inline void com_retprev();	//���������� ���������� ��������� ������, � ������ ����� ������� ���������� ��� ���� �������

	inline void com_add();
	inline void com_sub();
	inline void com_mul();
	inline void com_div();

	inline void com_halt();
	inline void com_push();
	inline void com_pop();
	//

	typedef void(s4g_vm::*opfunc) ();
	opfunc arropf[18];

	const char* get_curr_file(char* str=0);
	long get_curr_str(char* str = 0);
	const char* get_curr_func(char* str = 0);

	String strstacktrace;
	const char* stack_trace();

	s4g_stack<s4g_command>* curr_comm;
	long id_curr_com;

	s4g_table* gvars;	//���������� ������������ ���� _g
	s4g_value* vgvars;	//���������� �������� � ���� ���������� ������������ ����
	s4g_table* curr_vars;	//������� ������������� ������������ ����, ��� ����������� ������� �� ������������ ���� �������
	s4g_stack<s4g_value*, S4G_RESERVE_STACK_EXE> execute;	//���� ���������� ������

	int error;	//���� �� ������? -1 ����, ��������� ��� � �����
	char strerror[1024];	//������ ������

	s4g_arr_lex* arr_lex;
	s4g_gc* gc;
	s4g_main* s4gm;

	s4g_vm_command oldop;
	s4g_vm_command op;
	s4g_value* arg;
	long val_end;		//
	bool runexe;		//����� �� ��������� ��� (��������� �������������)
	s4g_stack<s4g_value*, 64> stackarg;

	int cfetchget;		//���� �� ���������� ������� ���� fetch ���� fetch_get
	bool cfetchgetarg;	//���� �� ���������� ������� fetch_get � ���������� ��� ���
	int cfetchpushstore;//��������� �� ��������� fetch push store, ���� �� �� ������ = 3, ����� ��� com_store

	s4g_stack_register<int, S4G_MAX_CALL+1> sr;//���� ���������, ������ ������ ����� ���������� �� ������ ���������� �������� � �������
	s4g_stack<s4g_call_data*> callstack;	//���� ������� � ����������� ���������� ����������
};

#endif

extern "C"
{

//��������� �������
enum s4g_state_parse
{
	sp_local = 1,	//��������/���������� ��������� ����������
	sp_var,			//��������/���������� ����������
	sp_gvar,		//��������/���������� ����������
	sp_const,		//
	sp_string,		//
	sp_function,	//�������� �������
	sp_return,		//����������� ��������
	sp_table,		//�������� �������
	sp_table_gn,	//��������� � �������� ������� table.elem
	sp_table_gs,	//��������� � �������� ������� table["elem"]
	sp_op,			//��������� ������
	sp_op_arg,		//��������� ������ ��� �������
	sp_op_arif,		//��������� + - * /
	sp_op_r,		//������������
};

struct s4g_state_name
{
	s4g_state_name(){}
	s4g_state_name(int st,const char* na,long strn){state = st;strcpy(name,na);str = strn;}
	int state;
	char name[1024];
	long str;
};

class s4g_sp
{
public:
	s4g_sp(){}

	inline void set(int state)
	{
		ArrState.clear();
		ArrState.push_back(state);
	}

	inline void add(int state)
	{
			if(!exists(state))
			{
				ArrState.push_back(state);
			}
	}

	inline bool exists(int state)
	{
			for(int i=0;i<ArrState.size();i++)
			{
					if(ArrState[i] == state)
						return true;
			}
		return false;
	}

	inline void clear()
	{
		ArrState.clear();
	}

protected:
	Array<int> ArrState;
};

struct s4g_operator_desc
{
	char c;
	int prioritet;
};

//��������� �������� ( ) [ ] { }
struct s4g_sym_o_desc
{
	s4g_sym_o_desc(){}
	s4g_sym_o_desc(char _cb,char _ce,bool iscf,long _numstrb){cb = _cb;ce = _ce;numstrb = _numstrb;is_call_f=iscf;}
	char cb,ce;		//��� �������
	bool is_call_f;
	long numstrb,numstre;	//����� ������ �� ������� �� ����������
};

//��������� ������ ������ ����� ��� function name(args) end; if(condition) end;
struct s4g_block_desc
{
	s4g_block_desc(){}
	s4g_block_desc(const char* _str,long _numstrb){sprintf(str,"%s",_str);numstrb = _numstrb;}
	char str[64];
	long numstrb;
};

//struct 

int s4g_parse_str_is_exists(const char* str);
inline bool s4g_is_char_str(const char sym);
inline bool s4g_is_char_num_or_point(const char sym);
inline bool s4g_is_char_num(const char sym);
inline bool s4g_is_char_point(const char sym);
inline bool s4g_is_char_arif(const char sym);
inline bool s4g_is_char_arif_pm(const char sym);
inline void s4g_scan_string(const char* sstr,char* dstr);
inline void s4g_scan_litstring(const char* sstr,char* dstr);
inline int s4g_scan_num(const char* sstr,char* dstr);

//������ ��������� � �������� ������� ���� testtable["x"]
void s4g_parse_g_e_t(char* str);

void s4g_output_error(const char* format,...);

int s4g_parse_file(const char* file);
int s4g_parse_str(const char* str);

}
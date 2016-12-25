
#ifndef s4g_parser_h
#define s4g_parser_h

#define S4G_MAX_LEN_KEY_WORD_DEF 9
#define S4G_MAX_LEN_SYM 4

const char s4g_key_words[][S4G_MAX_LEN_KEY_WORD_DEF] = {
"null",		//0
"function",	//1
"end",		//2
"return",	//3
"extern",	//4
"if",		//
"and",		//
"or",		//
"then",		//
"elseif",	//
"else",		//
"for",		//
"while",	//
"do",		//

};

const char s4g_key_bool[][S4G_MAX_LEN_KEY_WORD_DEF] = {
"true",
"false"
};

const char s4g_key_preproc[][S4G_MAX_LEN_KEY_WORD_DEF] = {
"include",
"define",
"undef",
"if",
"ifdef",
"defined",
"elif",
"else",
"end",
};

const char s4g_key_setcompiler[][S4G_MAX_LEN_KEY_WORD_DEF] = {
"ginf",
"crd"
};

const char s4g_key_syms_del[][S4G_MAX_LEN_SYM] = {
";",//����������� ��������
","	//����������� ����������
};

const char s4g_key_syms_group[][S4G_MAX_LEN_SYM] = {
"(",//������ �����������/������ �������
")"//����� �����������/������ �������
};

const char s4g_key_syms_table_create[][S4G_MAX_LEN_SYM] = {
"{","}",//������ ����� �������� �������
};

const char s4g_key_syms_table_op[][S4G_MAX_LEN_SYM] = {
"[","]",//������ ����� ��������� � �������� ������� �� ������
"."		//��������� � �������� ������� �� �����
};

const char s4g_key_syms_logic[][S4G_MAX_LEN_SYM] = {
"!","==","!=",">","<",">=","<="
};

const char s4g_key_syms_assign[][S4G_MAX_LEN_SYM] = {
"="
};

const char s4g_key_syms_create[][S4G_MAX_LEN_SYM] = {
"$"
};

const char s4g_key_syms_marg[][S4G_MAX_LEN_SYM] = {
"..."
};

const char s4g_key_syms_arif[][S4G_MAX_LEN_SYM] = {
"+","-","*","/"
};

const char s4g_key_syms_arif_assign[][S4G_MAX_LEN_SYM] = {
"++","--","+=","-=","*=","/="
};

//������������ �����������
const char s4g_key_syms_comment_os[][S4G_MAX_LEN_SYM] = {
"//"
};

//������������� �����������
const char s4g_key_syms_comment_ms[][S4G_MAX_LEN_SYM] = {
"/*",	//������
"*/"	//�����
};

//������ � ������������ ��������
const int s4g_prioritet_op[] = {
10,// ()
20,// + -
30,// * /
};

//������������ ����� ����������� ������
enum s4g_lexeme_type
{
	word_user,		//���������������� �����
	word_user_cr,	//����������� ���������������� �����
	word_null,		//������ ��� null
	word_string,	//������
	word_string_cr,	//��������� ������
	word_float,		//����� � ��������� �������
	word_int,		//����� �������� �����
	word_uint,		//����� ����������� �����
	word_int_cr,	//��������� ����� �������� �����
	word_uint_cr,	//��������� ����� ����������� �����
	word_bool,		//���������� ��������
	word_key,		//�������� ����� �����
	word_prep,		//����� �������������
	marg,			//���������� ���������� ����������
	sym_delimiter,	//������ �����������
	sym_logic,		//������ ������
	sym_assign,		//������ ����������
	sym_arif,		//�������������� ������
	sym_arif_assign,//�������������� ������ � ����������
	sym_group,		//������ ����������� ()
	sym_table_create,	//������ �������� �������
	sym_table_elem,		//������ ��������� � �������� �������
};

//�������
struct s4g_lexeme
{
	s4g_lexeme(){}
	s4g_lexeme(const char* _str, long _numstr, int _type, int _id, int _idfile){ strcpy(str, _str); numstr = _numstr, type = _type; id = _id; fileid = _idfile; }
	char str[S4G_MAX_LEN_TYPE_NAME];	//��������� ������������� �������
	long numstr;	//����� ������ �� ������� ��������� �������
	int type;		//��� �������
	int id;			//���������� ����� ������� �� ������� ���� � �������� ��� ���������
	int fileid;		//���������� ����� �����
};

//���� �����
enum s4g_type_op
{
	_begin,	//������ ���������
	_empty,	//����� ���, ���������� ����� �����
	
	_expr,	//���������
	_var,	//����������
	_crvar,	//����������� ����������

	//���� ���������� � ���� �������� � ������
	_null,_float, _int, _int_cr, _uint, _uint_cr, _bool,  _string, _string_cr, 
	_function,
	_numnull, //����� 0 ��� ��������� ���� -123 = 0-123

	_arg, _marg, //��� �������� ���������
	_set,	//������������
	_sett,	//������������ � �������
	_get,	//��������� ����������
	_get_cr,//�������� � ��������� ���������� 
	_call,	//����� �������
	_add,//+
	_sub,//-
	_mul,//*
	_div,///
	_group_b,//(
	_group_e,//)
	_return,		//����������� ��������
	_create_table,	//�������� �������
	_add_in_table,	//���������� � �������
};

//���������� ����������� ��������
int s4g_get_priority(s4g_type_op op)
{
		if(op == _add || op == _sub)
			return s4g_prioritet_op[1];
		else if(op == _mul || op == _div)
			return s4g_prioritet_op[2];
		else if(op == _group_b || op == _group_e)
			return s4g_prioritet_op[0];
		else
			return -1;
}

//���, �������� ������ � ����������� �������������� ������
struct s4g_node
{
	s4g_node()
	{
		type = _begin; value = 0; op1 = op2 = op3 = 0; lexid = -1;
	}
	s4g_node(s4g_type_op _type, long _lexid = -1, s4g_value* _value = 0, s4g_node* _op1 = 0, s4g_node* _op2 = 0, s4g_node* _op3 = 0){ type = _type; lexid = _lexid; value = _value; op1 = _op1; op2 = _op2; op3 = _op3; }
	s4g_type_op type;	//��� ����
	long lexid;
	s4g_value* value;	//�������� ���� ����

	//���������� ���� ��� �����������
	s4g_node* op1;	
	s4g_node* op2;
	s4g_node* op3;
};
//type == _expr:
	//op1 - ���������, 
	//op2 �� ��� ������� �� ���������� ��� �����������

//type == _call:
	//op1 - _var
	//op2 - ������ � ��� ������������ ���� ��� ����� �����������
	//op3 - _arg
		//op1 - ��������
		//op2 - _empty
			//op1 - _ ��������
				//op2 - _empty
					//...

//type == _function:
	//op1 - _arg ������ ��������:
		//value
		//op1 - ��������� _arg
			//...
	//op2 - ���� �������

//type == _set:
	//op1 - ���� �����������
	//op2 - �� ��� �����������

//type == _var
	//op1 - _get ���� ���������� �� ������ ���� ��������� � �������� �������
		//op1 - _string/_number/_crvar
		//op2 - empty
			//op1 - _get
				//...
	//op2 - _var/_crvar - ���� ���������� ��� �� ������ � ��� ���� ������������ ����� ������� ���������� ������� ��� ������� ����� �����������
	//op3 - _var/value/operation - ���� ���������� ��� ������ � ��� ���� ����� �� �������������� �������� ��� ���������
		//...

//type == _create_table
	//���� op1 - _sett
		//���� ����� ��� � _set (_sett �������� ��� ������������ � �������)
	//���� op1 - _add_in_table
		//op1 - �� ��� ��������� � �������
		//op2 - _empty
			//op1 - _add_in_table
			//...
	//op2 - _empty
		//op1 - _sett
		//op2 - _empty
			//...


//�������� �� ������������� ������� ...
inline int s4g_is_syms_arif(const char* sstr,char* dstr);		//�������������� ������� �� s4g_key_syms_arif
inline int s4g_is_syms_arif_assign(const char* sstr,char* dstr);//�������������� ������� � �������������� �� s4g_key_syms_arif_assign
inline int s4g_is_syms_logic(const char* sstr,char* dstr);		//���������� �������� �� s4g_key_syms_logic
inline bool s4g_is_comment_os(const char* sstr);				//������������ ������������
inline bool s4g_is_comment_ms_b(const char* sstr);				//������� �������������� �����������
inline bool s4g_is_comment_ms_e(const char* sstr);				//������ �������������� �����������
inline int s4g_is_boolean(const char* sstr,char* dstr);			//���������� ��������
inline bool s4g_is_null(const char* sstr);						//������ ���������
inline int s4g_is_delimiter(const char* sstr,char* dstr);		//������������
inline int s4g_is_assign(const char* sstr,char* dstr);			//�������������
inline int s4g_is_table_create(const char* sstr,char* dstr);	//�������� �������� �������
inline int s4g_is_table_elem(const char* sstr,char* dstr);		//�������� ��������� � �������� �������
inline int s4g_is_syms_group(const char* sstr,char* dstr);		//�������� �����������/������ �������
//inline int s4g_is_marg(const char* sstr, char* dstr);		//�������� �����������/������ �������

//�������� �� ������� ����� ...
inline bool s4g_is_char_str(const char sym);				//�������
inline bool s4g_is_char_num_or_point(const char sym);		//������ ���� ������
inline bool s4g_is_char_num(const char sym);				//������
inline bool s4g_is_char_point(const char sym);				//������
inline bool s4g_is_char_arif(const char sym);				//�������������� �������� + - * /
inline bool s4g_is_char_arif_pm(const char sym);			//�������������� �������� + - 

//���������� �� ������ ...
inline void s4g_scan_string(const char* sstr,char* dstr);				//����� ���������� �� ���� � ����
inline void s4g_scan_litstring(const char* sstr,char* dstr);			//���������������� ������ ������������ � ��������������� "
inline int s4g_scan_num(const char* sstr,char* dstr);					//�����

inline int s4g_is_key_word(const char* str);	//�������� �� ����� ��������
inline int s4g_is_key_word_pp(const char* str);	//�������� �� ����� �������� �� �������������

//�������� �������������
struct s4g_def_lex_arg
{
	s4g_def_lex_arg(){}
	s4g_def_lex_arg(s4g_lexeme* _l,int _a){lexeme = _l;num_arg = _a;}
	s4g_lexeme* lexeme;
	int num_arg;
};

//������� �������������, ����� ���� ��� ���������� ��� � ��������
struct s4g_define
{
	char name[64];
	Array<String> arg;
	Array<s4g_def_lex_arg> lexs;
};

//����������� ����������
class s4g_arr_lex
{
public:
	s4g_arr_lex();
	int read(const char* file_str,bool isfile=true);
	int gen_lexs(const char* str,Array<s4g_lexeme*>* arr_lexs,bool is_def);
	s4g_lexeme* get(DWORD num);
	DWORD get_curr_num();
	DWORD get_count();
	void set_curr_num(DWORD num);
	s4g_lexeme* get_curr();
	s4g_lexeme* get_next();
	s4g_lexeme* get_prev();
	s4g_lexeme* r_get_lexeme(const char* str,long* curr_pos,long* curr_num_str);

	char strerror[1024];
//protected:
	Array<s4g_lexeme*> ArrLexs;
	AATable<s4g_define> ArrDefines;
	Array<String> ArrFiles;
	Array<String> ArrPathForFiles;
	int curr_id_file;// = ArrFiles.size()-1;
	long curr_num;
	MemAlloc<s4g_lexeme> LexPool;
};

#define bst_iferr(cond,text,...) if(cond) {this->status = -1; sprintf(this->error, text, ...); return 0;)
#define bst_cond_er(bst) if(bst->status != 0) return 0;
#define bst_cond_eof(lexeme) if(!lexeme && !isender) {\
status = 1;\
tmplexs = arr_lex->get_prev();\
sprintf(error,"[%s]:%d - unexpected end of file",arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr);\
return 0; \
}

#define curr_lexid arr_lex->get_curr_num()

#define lex_get_curr(tmplex) { tmplex = arr_lex->get_curr(); bst_cond_eof(tmplex);}
#define lex_get_next(tmplex) { tmplex = arr_lex->get_next(); bst_cond_eof(tmplex);}
#define lex_get_prev(tmplex) { tmplex = arr_lex->get_prev(); bst_cond_eof(tmplex);}

#define lex_get_curr0(tmplex) tmplex = arr_lex->get_curr(); bst_cond_eof(tmplex);
#define lex_get_next0(tmplex) tmplex = arr_lex->get_next(); bst_cond_eof(tmplex);
#define lex_get_prev0(tmplex) tmplex = arr_lex->get_prev(); bst_cond_eof(tmplex);


//��������� ������������ ��������������� ������
struct s4g_builder_syntax_tree
{
s4g_builder_syntax_tree(){ status = 0; error[0] = 0; overend = 0; overge = 0; listread = true; readcall = true; isender = true; }

s4g_node* s4g_gen_tree();	//��������� ��� � ������� ������ ���

s4g_node* s4g_gen_statement();//���������� ������� ����������
s4g_node* s4g_get_ret_vals();		//���������� ������������ ��������
s4g_node* s4g_get_arg_call_func();	//���������� ���������� ��� ������ �������
s4g_node* s4g_get_function_def_head();	//���������� ���������� ��� �������� �������
s4g_node* s4g_get_term();	//���������� ������
s4g_node* s4g_get_op();		//���������� ��������
s4g_node* s4g_get_expr();	//���������� ���������
s4g_node* s4g_get_table();	//���������� ����������� ����������� �������

bool isender;	//���� ������ ������ ���������� �� ����� �� ��������� ����������?
bool listread;	//����� �� �� ��������� ������ ���������/�������� ��� ��� ��� ����������� (�� ���� false)?
bool readcall;	//����� �� �� ��������� ����� �������, ��� ������ ����������� ���������� ������� (�� ���� false)?
int overend;	//���� 0 ������ ��� � �����, ���� ����� 0 �� ������ ���, ���� ������ 0 �� ������ �� ���� ���� � ���������� abs(overend)
int overge;		//������������� �� ������� ��� ��������� ����� ������� � ���� ���������� ��������� ������ ������ ����������� ������ �� ��� ����������� ������ (���� ��������������)
int status;		//������� ������, 0 - ��� ����, ��� ������ ��� ������
char error[1024];//������ � ��������� ������

s4g_arr_lex* arr_lex;
s4g_gc* gc;
};

#endif
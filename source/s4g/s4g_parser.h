
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
"if",		//5
"and",		//6 ///<?
"or",		//7 ///<?
"then",		//8 ///<?
"elseif",	//9 ///<?
"else",		//10
"for",		//11
"while",	//12
"do",		//13
};

enum S4GLKW
{
	S4GLKW_NULL = 0,
	S4GLKW_FUNCTION,
	S4GLKW_END,
	S4GLKW_RETURN,
	S4GLKW_EXTERN,
	S4GLKW_IF,
	S4GLKW_AND,
	S4GLKW_OR,
	S4GLKW_THEN,
	S4GLKW_ELSEIF,
	S4GLKW_ELSE,
	S4GLKW_FOR,
	S4GLKW_WHILE,
	S4GLKW_DO
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
"line"
};

enum S4GLPP
{
	S4GLPP_USER = -1,
	S4GLPP_INCLUDE = 0,
	S4GLPP_DEFINE,
	S4GLPP_UNDEF,
	S4GLPP_IF,
	S4GLPP_IFDEF,
	S4GLPP_DEFINED,
	S4GLPP_ELIF,
	S4GLPP_ELSE,
	S4GLPP_END,
	S4GLPP_LINE
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
	"emt"
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
	"+",
	"-", 
	"*", 
	"/", 
	"%",
	"&&", 
	"||", 
	"^", 
	"~", 
	">>",
	"<<", 
	"!==",
	"==", 
	"!=",
	">=",
	"<=",
	">", 
	"<", 
	"!",
	"===", 
	"&", 
	"|"
};

enum S4GLAO
{
	S4GLAO_ADD = 0,
	S4GLAO_SUB,
	S4GLAO_MUL,
	S4GLAO_DIV,
	S4GLAO_MOD,
	S4GLAO_LOG_AND,
	S4GLAO_LOG_OR,
	S4GLAO_BIT_XOR,
	S4GLAO_BIT_NOT,
	S4GLAO_BIT_SHIFTR,
	S4GLAO_BIT_SHIFTL,
	S4GLAO_LOG_NEQT,
	S4GLAO_LOG_EQ,
	S4GLAO_LOG_NEQ,
	S4GLAO_LOG_GE,
	S4GLAO_LOG_LE,
	S4GLAO_LOG_GT,
	S4GLAO_LOG_LT,
	S4GLAO_LOG_NOT,
	S4GLAO_LOG_EQT,
	S4GLAO_BIT_AND,
	S4GLAO_BIT_OR
};

const char s4g_key_syms_arif_assign[][S4G_MAX_LEN_SYM] = {
"++","--","+=","-=","*=","/="
,"%=",">>=","<<=","&=","|=","^="
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
30,// * / %
19,// << >>
18,// < <= > >=
17,//== !=
16,//&
15,//^
14,//|
13,//&&
12,//||
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
	s4g_lexeme(const char* _str, long _numstr, s4g_lexeme_type _type, int _id, int _idfile)
	{
		strcpy(str, _str); numstr = _numstr, type = _type; id = _id; fileid = _idfile;
	}
	char str[S4G_MAX_LEN_TYPE_NAME];	//��������� ������������� �������
	long numstr;	//����� ������ �� ������� ��������� �������
	s4g_lexeme_type type;		//��� �������
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

	_if,
	_while,
	_for,

	_mod,
	_bit_and,
	_bit_or,
	_bit_xor,
	_bit_not,
	_bit_shiftr,
	_bit_shiftl,

	_log_not,
	_log_eq,
	_log_neq,
	_log_gt,
	_log_lt,
	_log_ge,
	_log_le,
	_log_neqt,
	_log_eqt,
	_log_and,
	_log_or
};

const s4g_type_op s4g_aop_map[] = {
	_add, //S4GLAO_ADD = 0,
	_sub, //S4GLAO_SUB,
	_mul, //S4GLAO_MUL,
	_div, //S4GLAO_DIV,
	_mod, //S4GLAO_MOD,
	_log_and, //S4GLAO_LOG_AND,
	_log_or, //S4GLAO_LOG_OR,
	_bit_xor, //S4GLAO_BIT_XOR,
	_bit_not, //S4GLAO_BIT_NOT,
	_bit_shiftr, //S4GLAO_BIT_SHIFTR,
	_bit_shiftl, //S4GLAO_BIT_SHIFTL,
	_log_neqt, //S4GLAO_LOG_NEQT,
	_log_eq, //S4GLAO_LOG_EQ,
	_log_neq, //S4GLAO_LOG_NEQ,
	_log_ge, //S4GLAO_LOG_GE,
	_log_le, //S4GLAO_LOG_LE,
	_log_gt, //S4GLAO_LOG_GT,
	_log_lt, //S4GLAO_LOG_LT,
	_log_not, //S4GLAO_LOG_NOT,
	_log_eqt, //S4GLAO_LOG_EQT,
	_bit_and, //S4GLAO_BIT_AND,
	_bit_or, //S4GLAO_BIT_OR,
};

//���������� ����������� ��������
int s4g_get_priority(s4g_type_op op)
{
	switch(op)
	{
	case _bit_not:
		return 32;

	case _log_not:
		return 31;

	case _mul: 
	case _div: 
	case _mod:
		return 30;

	case _add:
	case _sub:
		return 20;

	case _bit_shiftr:
	case _bit_shiftl:
		return 19;

	case _log_gt:
	case _log_ge:
	case _log_lt:
	case _log_le:
		return 18;

	case _log_eq:
	case _log_eqt:
	case _log_neq:
	case _log_neqt:
		return 17;

	case _bit_and:
		return 16;

	case _bit_xor:
		return 15;

	case _bit_or:
		return 14;

	case _log_and:
		return 13;

	case _log_or:
		return 12;

	case _group_b: 
	case _group_e:
		return 10;

	default:
		return -1;
	}
}

//���, �������� ������ � ����������� �������������� ������
struct s4g_node
{
	s4g_node(s4g_type_op _type = _begin, long _lexid = -1, s4g_value* _value = 0, s4g_node* _op1 = 0, s4g_node* _op2 = 0, s4g_node* _op3 = 0)
	{
		type = _type; lexid = _lexid; value = _value; op1 = _op1; op2 = _op2; op3 = _op3;
	}
	s4g_type_op type;	//��� ����
	long lexid;
	s4g_value* value;	//�������� ���� ����

	//���������� ���� ��� �����������
	s4g_node* op1;	
	s4g_node* op2;
	s4g_node* op3;

#if defined(_DEBUG)
	String Dump()
	{
		String out = "{type:'";
		out += TypeStr(type);
		out += "'";

		out += ",value:";
		if(value)
		{
			out += "{name:'";
			out += value->name;
			out += "',value:'";
			switch(value->pdata->type)
			{
			case t_none:
				out += "t_none";
				break;
			case t_null:
				out += "t_null";
				break;
			case t_table:
				out += "t_table";
				break;
			case t_string:
				out += *(char**)(value->pdata->data);
				break;
			case t_float:
				out += *(float*)(value->pdata->data);
				break;
			case t_int:
				out += *(int*)(value->pdata->data);
				break;
			case t_uint:
				out += (DWORD)*(unsigned*)(value->pdata->data);
				break;
			case t_bool:
				out += *(bool*)(value->pdata->data);
				break;
			case t_pdata:
				out += "t_pdata";
				break;
			case t_cfunc:
				out += "t_cfunc";
				break;
			case t_sfunc:
				out += "t_sfunc";
				break;
			case t_nnull:
				out += "0";
				break;
			}
			out += "'}";
		}
		else
		{
			out += "null";
		}

		out += ",op1:";
		if(op1)
		{
			out += op1->Dump();
		}
		else
		{
			out += "null";
		}

		out += ",op2:";
		if(op2)
		{
			out += op2->Dump();
		}
		else
		{
			out += "null";
		}

		out += ",op3:";
		if(op3)
		{
			out += op3->Dump();
		}
		else
		{
			out += "null";
		}
		out += "}";
		return(out);
	}
	const char * TypeStr(s4g_type_op t)
	{
		switch(t)
		{
		case _begin:return("_begin");
		case _empty:return("_empty");
		case _expr:return("_expr");
		case _var:return("_var");
		case _crvar:return("_crvar");
		case _null:return("_null");
		case _float:return("_float");
		case _int:return("_int");
		case _int_cr:return("_int_cr");
		case _uint:return("_uint");
		case _uint_cr:return("_uint_cr");
		case _string:return("_string");
		case _string_cr:return("_string_cr");
		case _function:return("_function");
		case _numnull:return("_numnull");
		case _arg:return("_arg");
		case _marg:return("_marg");
		case _set:return("_set");
		case _sett:return("_sett");
		case _get:return("_get");
		case _get_cr:return("_get_cr");
		case _call:return("_call");
		case _add:return("_add");
		case _sub:return("_sub");
		case _mul:return("_mul");
		case _div:return("_div");
		case _group_b:return("_group_b");
		case _group_e:return("_group_e");
		case _return:return("_return");
		case _create_table:return("_create_table");
		case _add_in_table:return("_add_in_table");
		case _if:return("_if");
		case _while:return("_while");
		case _for:return("_for"); 
		case _mod:return("_mod");
		case _bit_and:return("_bit_and");
		case _bit_or:return("_bit_or");
		case _bit_xor:return("_bit_xor");
		case _bit_not:return("_bit_not");
		case _bit_shiftr:return("_bit_shiftr");
		case _bit_shiftl:return("_bit_shiftl");
		case _log_not:return("_log_not");
		case _log_eq:return("_log_eq");
		case _log_neq:return("_log_neq");
		case _log_gt:return("_log_gt");
		case _log_lt:return("_log_lt");
		case _log_ge:return("_log_ge");
		case _log_le:return("_log_le");
		case _log_neqt:return("_log_neqt");
		case _log_eqt:return("_log_eqt");
		case _log_and:return("_log_and");
		case _log_or:return("_log_or");
		default:return("UNKNOWN");
		}
	}
#endif
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
	Array<String> ArrFiles;
	Array<String> ArrPathForFiles;
	int curr_id_file;// = ArrFiles.size()-1;
	long curr_num;
	MemAlloc<s4g_lexeme> LexPool;
	bool iscreatevar;
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
	s4g_builder_syntax_tree(){status = 0; error[0] = 0; overend = 0; overge = 0; listread = true; readcall = true; isender = true; dowhile = 0;}

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
	int dowhile;    //���-�� �������� do
	char error[1024];//������ � ��������� ������

	s4g_arr_lex* arr_lex;
	s4g_gc* gc;
	MemAlloc<s4g_node> NodePool;
};

#endif
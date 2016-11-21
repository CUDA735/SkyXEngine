
extern "C"
{

#define S4G_MAX_LEN_KEY_WORD_DEF 9
#define S4G_MAX_LEN_SYM 3

const char s4g_key_words[][S4G_MAX_LEN_KEY_WORD_DEF] = {
"null",
"function",
"var",
"global",
"return",
"if",
"and",
"or",
"then",
"elseif",
"else",
"for",
"while",
"do",
"end"
};

const char s4g_key_bool[][S4G_MAX_LEN_KEY_WORD_DEF] = {
"true",
"false"
};

const char s4g_key_preproc[][S4G_MAX_LEN_KEY_WORD_DEF] = {
"include",
"define",
"undef"
"if",
"ifdef",
"defined",
"elif",
"else",
"end",
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

enum s4g_lexeme_type
{
	word_user,	//���������������� �����
	word_null,	//������ ��� null
	word_string,//������
	word_float,	//����� � ��������� �������
	word_int,	//����� �����
	word_bool,	//����������� ��������
	word_key,	//�������� ����� �����
	word_prep,	//����� �������������
	sym_delimiter,	//������ �����������
	sym_logic,		//������ ������
	sym_assign,		//������ ����������
	sym_arif,		//�������������� ������
	sym_arif_assign,//�������������� ������ � ����������
	sym_group,
	sym_table_create,	//������ �������� �������
	sym_table_elem,		//������ ��������� � �������� �������
};

struct s4g_lexeme
{
	s4g_lexeme(){}
	s4g_lexeme(const char* _str,long _numstr,int _type,int _id){strcpy(str,_str);numstr = _numstr,type = _type;id = _id;}
	char str[64];	//��������� ������������� �������
	long numstr;	//����� ������ �� ������� ��������� �������
	int type;		//��� �������
	int id;			//���������� ����� ������� �� ������� ���� � �������� ��� ���������
};

enum s4g_type_
{
	_if,_var,_add,_return,
};

struct s4g_value
{
	int type;
	void* value;
};

struct s4g_node
{
	int type;
	s4g_value* value;
	s4g_node* op1;
	s4g_node* op2;
	s4g_node* op3;
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

//�������� �� ������� ����� ...
inline bool s4g_is_char_str(const char sym);				//�������
inline bool s4g_is_char_num_or_point(const char sym);		//������ ���� ������
inline bool s4g_is_char_num(const char sym);				//������
inline bool s4g_is_char_point(const char sym);				//������
inline bool s4g_is_char_arif(const char sym);				//�������������� �������� + - * /
inline bool s4g_is_char_arif_pm(const char sym);			//�������������� �������� + - 

//���������� �� ������ ...
inline void s4g_scan_string(const char* sstr,char* dstr);				//����� ���������� �� ���� � ����
inline void s4g_scan_list_string(const char* sstr,char dstr[64][64]);	//
inline void s4g_scan_litstring(const char* sstr,char* dstr);			//���������������� ������ ������������ � ��������������� "
inline int s4g_scan_num(const char* sstr,char* dstr);					//�����


inline int s4g_is_key_word(const char* str);	//�������� �� ����� ��������
inline int s4g_is_key_word_pp(const char* str);	//�������� �� ����� �������� �� �������������


void s4g_output_error(const char* format,...);

class s4g_arr_lex
{
public:
	s4g_arr_lex();
	void read(const char* file,String AllFile);
	DWORD add(const char* _str,long _numstr,int _type,int _id);
	s4g_lexeme* get(DWORD num);
	DWORD get_curr_num();
	void set_curr_num(DWORD num);
	s4g_lexeme* get_curr();
	s4g_lexeme* get_next();

protected:
	Array<s4g_lexeme> ArrLexs;
	DWORD curr_num;
};

int s4g_parse_file(const char* file);
int s4g_parse_str(const char* str);
int s4g_gen_tree(s4g_node* tree);

}
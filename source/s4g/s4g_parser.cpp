
#include "s4g_parser.h"

#include "s4g_vm.cpp"
#include "s4g_compiler.cpp"
#include "s4g_lexer.cpp"
#include "s4g_preprocessor.cpp"

//��������� ���������� ������
s4g_node* s4g_builder_syntax_tree::s4g_gen_statement()
{
	//��������� ���
	s4g_node* node = NodePool.Alloc(s4g_type_op::_begin, -1, (s4g_value*)0);
	s4g_stack<s4g_statement> arrnode;	//������ ���������� ������� ���� ����������
	arrnode.push(s4g_statement(node, &(node->op1)));
	s4g_node* oldroot = 0;	//���������� �������� ��������� ���������� (�� ������ ����� �������)
	long countinn = 0;		//���������� �������� ��������� � ������� ���������� ���������� oldroot
	bool isread = true;
	
	while (isread)
	{
		//���� ��� ������ ��� ������� � � ���� ����� ���������� ���������� oldroot
		if (countinn > 1)
			oldroot = 0;	//�������� ����������� ��������

		s4g_lexeme* lex_get_curr0(tmplexs);

		//���� ������� �� ������� ������ ������ ����� ������� ���������
		if (tmplexs == 0)
			break;

		//���� ��� ������� ��� �������� ����� �����
		if (tmplexs->type == word_key)
		{
			//������������ /return
			if (tmplexs->id == S4GLKW_RETURN)
			{
				bool oldisender = isender;
				isender = false;
				lex_get_next0(tmplexs);

				//op1 - ������������ ���������
				//��������� ���������
				s4g_node* tmpnode = NodePool.Alloc(_return, curr_lexid, (s4g_value*)0, s4g_get_expr(false));

				//������������ ������ �� ��������
				*(arrnode[arrnode.count_obj - 1].node) = tmpnode;

				lex_get_curr0(tmplexs);
				bst_cond_er(this);
				isender = oldisender;

				//���� ����� ��������� ��� ������� ��������� �������� ;
				if (!((tmplexs->type == sym_delimiter && tmplexs->id == 0) || (tmpnode->op1 && tmpnode->op1->type == _set && tmpnode->op1->op2 && tmpnode->op1->op2->type == _function)))	//error
				{
					status = -1;
					sprintf(this->error, "[%s]:%d - ';' expected but found '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
					return 0;
				}
				lex_get_next0(tmplexs);
				
				//��������� �� �����������, �� ���� �� �� ��� ����� �����
				arrnode[arrnode.count_obj - 1].node = &((*arrnode[arrnode.count_obj - 1].node)->op3);
			}
			//���������� ������� /function
			else if (tmplexs->id == S4GLKW_FUNCTION)
			{
				long funclexid = curr_lexid;
				bool oldisender = isender;
				isender = false;

				s4g_node* name_func = 0;
				lex_get_next0(tmplexs);

				//���� ��� ������� ����������� ���������������� �����
				if (tmplexs->type == word_user_cr)
				{
					//������, ��������� �������� �� ����
					status = -1;
					sprintf(this->error, "[%s]:%d - function provides for the creation of a new variable, it's too much [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, s4g_key_syms_create[0]);
					return 0;
				}
				//���� ��� ������� ���������������� �����
				else if (tmplexs->type == word_user)
				{
					readcall = false;	//��������� ������ �������
					name_func = s4g_get_term();	//��������� ��� �������
					name_func->type = _crvar;	//��������� �� �������� ������ �����
					readcall = true;	//��������� ��������� ������ �������
				}
				//����� � ��� �����-�� ������ ���, ������������
				else //error
				{
					status = -1;
					sprintf(this->error, "[%s]:%d - unresolved word for name function [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
					return 0;
				}

				lex_get_curr0(tmplexs);
				bst_cond_er(this);

				//���� ������� ��� ����������� ������
				if (tmplexs->type == sym_group && tmplexs->id == 0)
				{
					lex_get_next(tmplexs);
				}
				//����� ������, ��� ��� ���� ��� �� ��������� �������
				else //error
				{
					status = -1;
					sprintf(this->error, "[%s]:%d - '(' expected, but got [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
					return 0;
				}

				//��������� ��������� ������� (������ ������ ����������)
				s4g_node* head_func = s4g_get_function_def_head();
				
				lex_get_curr0(tmplexs);
				bst_cond_er(this);

				//��������� ������ �����
				s4g_begin_read_block();
				
				lex_get_curr0(tmplexs);
				bst_cond_er(this);

				//op1 - ��� �������, ��� �������
				//op2 - ���� ������� ��� ����������
				s4g_node* nfunc = NodePool.Alloc(_function, funclexid, (s4g_value*)0, head_func);

				s4g_node* nfuncexpr = NodePool.Alloc(_expr, funclexid, (s4g_value*)0, 
										NodePool.Alloc(_set, funclexid, (s4g_value*)0, name_func, nfunc), 
										NodePool.Alloc(_empty, curr_lexid, (s4g_value*)0));

				//�������� ������
				*arrnode[arrnode.count_obj - 1].node = nfuncexpr;
				arrnode[arrnode.count_obj - 1].node = &((*arrnode[arrnode.count_obj - 1].node)->op2->op1);

				//��������� ����� ����������, �������� ����� �������
				arrnode.push(s4g_statement(nfunc, &(nfunc->op2)));

				isender = oldisender;
			}
			//������� if
			else if (tmplexs->id == S4GLKW_IF)
			{
				bool oldisender = isender;
				isender = false;
				
				lex_get_next0(tmplexs);
				//���� ������� ������� �� (
				if (tmplexs->type != sym_group || tmplexs->id != 0)
				{
					//������� ������ ��� ��� ���� ���-�� ������������� �������
					status = -1;
					sprintf(this->error, "[%s]:%d - '(' expected but found '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
					return(0);
				}

				lex_get_next0(tmplexs);
				--overge;
				//��������� �������
				s4g_node* tmpnode = NodePool.Alloc(_if, curr_lexid, (s4g_value*)0, s4g_get_expr(false));
				
				lex_get_curr0(tmplexs);
				bst_cond_er(this);

				isender = oldisender;
				//���� ����� ������� �� )
				if (tmplexs->type != sym_group || tmplexs->id != 1)
				{
					//������� ������, ��� ����������� ������� �� �������
					status = -1;
					sprintf(this->error, "[%s]:%d - ')' expected but found '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
					return(0);
				}

				lex_get_next0(tmplexs);
				//������ ������ �����
				s4g_begin_read_block();
				
				lex_get_curr(tmplexs);
				bst_cond_er(this);

				s4g_node* tmpnode2 = NodePool.Alloc(_block, curr_lexid, (s4g_value*)0, tmpnode);

				//���� ������� ����������� �� ������ �� ���� ������ �� ����� else
				if (arrnode[arrnode.count_obj - 1].root->ud == 10)
				{
					//������ ���������� �������� ��� if � ��� ����� ��� ����������,
					//����� ����� ������������� ��������
					arrnode[arrnode.count_obj - 2].root = tmpnode2;

					arrnode[arrnode.count_obj - 1].root = tmpnode2;
					*arrnode[arrnode.count_obj - 1].node = tmpnode2;
					arrnode[arrnode.count_obj - 1].node = &(tmpnode2->op1->op2);

					//arrnode.push_back(s4g_statement(tmpnode2, &(tmpnode2->op1->op2)));
				}
				else
				{
					//����� ���������� ��� ��� ����� �������, � ������ �����, � ������ � ����� ����������
					//���������� ���� ���������, � ���� ����� � ��� ��� ���������

					//���������� ��� �����, � ��������� �� ��� ����� (op3 - ��������� ����� ���� ����)
					arrnode[arrnode.count_obj - 1].root = tmpnode2;
					*arrnode[arrnode.count_obj - 1].node = tmpnode2;
					arrnode[arrnode.count_obj - 1].node = &(tmpnode2->op3);

					arrnode.push_back(s4g_statement(tmpnode2, &(tmpnode2->op1->op2)));
				}

				
			}
			//����� ������� else
			else if (tmplexs->id == S4GLKW_ELSE)
			{
				oldroot = arrnode.get(arrnode.count_obj - 1).root;
				//���� ���������� (���� � ���������� ��������) ������������ ��� ��� ������ �������
				if (oldroot && oldroot->type == _block && oldroot->op1->type == _if)
				{
					//���� ����� else ��� ���� ������ ���-�� �� �� ...
					//������ �� ������ ���������, �� �� ������ ������ �������
					if (oldroot->op1->op3)
					{
						status = -1;
						sprintf(this->error, "[%s]:%d - branch conditions already, fix error", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
						return(0);
					}

					lex_get_next0(tmplexs);

					//���������� �������� �� ������ ����� ��������������� ���� ������� �� ��������������� �������
					int isblock;
					if (tmplexs->type == word_key && tmplexs->id == S4GLKW_IF)
						isblock = 0;	//������� ���� �������
					else
						isblock = s4g_begin_read_block();	//���, ����� else

					lex_get_curr0(tmplexs);

					if (isblock)
					{
						//����� else
						//��������� � �������� �������� (�� �� if � �������� ��������� ������ �����) ������ ��l (op3) ������� � ���� else
						oldroot->op1->op3 = NodePool.Alloc(_block, curr_lexid, (s4g_value*)0);
						//��������� ����� ����������, �������� ����� ���� ����� (�� ������ �� ��������, ����� ��� ��� ������ ����)
						//� ����� ����� ���� �����
						arrnode.push_back(s4g_statement(oldroot->op1->op3, &(oldroot->op1->op3->op1)));
					}
					else
					{
						//����� else if ������ �����, �� ������ ����� �����
						//s4g_statement tmpn = arrnode[arrnode.count_obj - 1];
						oldroot->ud = 10;	//�������� ��� �� ���� ����������� � ���� if
						//���������� ����� ����������, �������� ������� �������� (�� �� _block->op1 == _if)
						//����� ���������� ����� ������� � _if ����
						arrnode.push_back(s4g_statement(oldroot, &(oldroot->op1->op3)));
					}
				}
				//����� ������, ����� else �� ��������� � �������
				else
				{
					status = -1;
					sprintf(this->error, "[%s]:%d - 'else' not found previous condition", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
					return(0);
				}
			}
			//���� while
			else if (tmplexs->id == S4GLKW_WHILE)
			{
				if (dowhile > 0) // ��� ���������� ��� do
				{
					--dowhile;
				}
				else // ��� ������� while
				{
					--dowhile;
					bool oldisender = isender;
					isender = false;
					
					lex_get_next0(tmplexs);
					if (tmplexs->type != sym_group || tmplexs->id != 0)
					{
						status = -1;
						sprintf(this->error, "[%s]:%d - '(' expected but found '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
						return(0);
					}

					//��������� �������
					s4g_node* tmpnode = NodePool.Alloc(_while, curr_lexid, (s4g_value*)0, s4g_get_expr(false));	
					lex_get_prev(tmplexs);
					bst_cond_er(this);

					isender = oldisender;
					if (tmplexs->type != sym_group || tmplexs->id != 1)
					{
						status = -1;
						sprintf(this->error, "[%s]:%d - ')' expected but found '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
						return(0);
					}
					lex_get_next0(tmplexs);
					//tmpnode->op2 = s4g_read_block(); //s4g_gen_statement();	//� ��������� �� ��� while
					s4g_begin_read_block();
					lex_get_curr0(tmplexs);
					bst_cond_er(this);


					//tmpnode = NodePool.Alloc(_block, curr_lexid, (s4g_value*)0, tmpnode, one ? NodePool.Alloc(_empty, curr_lexid, (s4g_value*)0) : s4g_gen_statement());
					s4g_node* tmpnode2 = NodePool.Alloc(_block, curr_lexid, (s4g_value*)0, tmpnode);
					//���������� � ��������� ���, ��� while � ����� �� ��������� �� ��������� ��� ������� ����� ������������ ����
					/**arrnode[arrnode.size() - 1] = tmpnode2;
					arrnode[arrnode.size() - 1] = &(tmpnode2->op2);

					//���������� ���� while, ������� ����� ������ �������
					arrnode.push_back(&(tmpnode->op2));*/

					*arrnode[arrnode.count_obj - 1].node = tmpnode2;
					arrnode[arrnode.count_obj - 1].node = &(tmpnode2->op2);

					//���������� ���� while, ������� ����� ������ �������
					arrnode.push(s4g_statement(tmpnode2, &(tmpnode->op2)));

					++dowhile;
				}
			}
			else if (tmplexs->id == S4GLKW_FOR)
			{
				bool oldisender = isender;
				isender = false;

				lex_get_next0(tmplexs);
				//���� ����� ����� for � ��� �� (
				if (tmplexs->type != sym_group || tmplexs->id != 0)
				{
					//������, ��� ������ ���� �����������
					status = -1;
					sprintf(this->error, "[%s]:%d - '(' expected but found '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
					return(0);
				}

				lex_get_next0(tmplexs);
				//��������� ������ ���� � ���������� (�������������)
				s4g_node* expt_init = NodePool.Alloc(_expr, curr_lexid, (s4g_value*)0, s4g_get_expr(false), NodePool.Alloc(_empty));

				//�������� � ��� ������ ��������� ����� ,
				//{
				if (expt_init)
				{
					s4g_node* tmpnode_expt_init = expt_init->op2;
					while (tmpnode_expt_init)	//���� ��������� ��������� �������
					{
						lex_get_curr0(tmplexs);
						//���� ��������� ,
						if ((tmplexs->type == sym_delimiter && tmplexs->id == 1))
						{
							lex_get_next(tmplexs);	//������ ������ ������
						}
						//����� ���� ��������� ;
						else if (tmplexs->type == sym_delimiter && tmplexs->id == 0)
							break;	//��������� ���� ��� ��� ��� ��� ������ ���� ���������

						tmpnode_expt_init->op1 = NodePool.Alloc(_expr, curr_lexid, (s4g_value*)0, s4g_get_expr(false), NodePool.Alloc(_empty));

						//���� �� �� ������ ��������� ���������, �� �� ����� �������� ��� � ��� ���� ����� ���� �������
						if (!(tmpnode_expt_init->op1->op1))
							break;	//������������� ����

						tmpnode_expt_init = tmpnode_expt_init->op1->op2;
						bst_cond_er(this);
					}
				}
				//}

				lex_get_curr0(tmplexs);
				bst_cond_er(this);

				//���� ������ �� ������� ;
				if (!(tmplexs->type == sym_delimiter && tmplexs->id == 0))	//error
				{
					status = -1;
					sprintf(this->error, "[%s]:%d - ';' expected but found '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
					return 0;
				}

				lex_get_next0(tmplexs);

				//��������� ������� ���������� �����
				s4g_node* expt_cond = 0;
				//������ ���� ������� � ��� ������, �� ���� ����� �� ������� ;
				if (tmplexs->type == sym_delimiter && tmplexs->id == 0)
				{
					//����������������� ���������� �������� ����������
					expt_cond = NodePool.Alloc(_bool, curr_lexid, gc->cr_val_bool(true, 0, S4G_GC_TYPE_DATA_SYS));
				}
				//����� � ��� ��� ���������
				else
				{
					expt_cond = s4g_get_expr(false);	//������ ���������

					lex_get_curr0(tmplexs);
					bst_cond_er(this);

					//���� ������� ������� �� ;
					if (!(tmplexs->type == sym_delimiter && tmplexs->id == 0))	//error
					{
						status = -1;
						sprintf(this->error, "[%s]:%d - ';' expected but found '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
						return 0;
					}
				}

				lex_get_next0(tmplexs);
				--overge;

				s4g_node* expt_step = 0;	//�������� ������ ����, ��� ����� ���� ��� � ��� �����
				//���� ������� ������� �� )
				if (!(tmplexs->type == sym_group && tmplexs->id == 1))
				{
					//��������� ������ ���� ���������
					expt_step = NodePool.Alloc(_expr, curr_lexid, (s4g_value*)0, s4g_get_expr(false), NodePool.Alloc(_empty));
					lex_get_curr0(tmplexs);
					bst_cond_er(this);

					//���� ������� ������� ���������, �� �������� � ��� ������ ��������� ... �����������
					//{
					if (expt_step)
					{
						s4g_node* tmpnode_expt_step = expt_step->op2;

						while (tmpnode_expt_step)	//���� ������� ������� ��������� ���������
						{
							lex_get_curr0(tmplexs);

							//���� ������� ������� ,
							if ((tmplexs->type == sym_delimiter && tmplexs->id == 1))
							{
								lex_get_next(tmplexs);	//������ ������ ������
							}
							//����� ���� ������� ������� )
							else if (tmplexs->type == sym_group && tmplexs->id == 1)
							{
								break;	//��������� ����
							}

							tmpnode_expt_step->op1 = NodePool.Alloc(_expr, curr_lexid, (s4g_value*)0, s4g_get_expr(false), NodePool.Alloc(_empty));

							//���� �� �� ������ ��������� ���������, �� �� ����� �������� ��� � ��� ���� ����� ���� �������
							if (!(tmpnode_expt_step->op1->op1))
								break;	//������������� ����

							tmpnode_expt_step = tmpnode_expt_step->op1->op2;
							lex_get_curr0(tmplexs);
							bst_cond_er(this);
						}
					}
					//}
				}
				else
					++overge;

				lex_get_curr0(tmplexs);
				bst_cond_er(this);

				//���� ������� ������ �� )
				if (tmplexs->type != sym_group || tmplexs->id != 1)
				{
					//������� ������ ��� ��� ���� ��� �� ������� for
					status = -1;
					sprintf(this->error, "[%s]:%d - ')' expected but found '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
					return(0);
				}

				lex_get_next0(tmplexs);
				isender = oldisender;

				//��������� ������ �����
				s4g_begin_read_block();

				lex_get_curr0(tmplexs);
				bst_cond_er(this);

				//op1 - _block
				//op1->op1 - �������������
				//op2 - _for
				//op2->op1 - ������� ����������
				//op2->op2 - ���� ����������
				//op2->op3 - ���� ���������, ����������� ����� ������ ��������
				s4g_node* tmpnode = NodePool.Alloc(_block, curr_lexid, (s4g_value*)0, expt_init,
					NodePool.Alloc(_for, curr_lexid, (s4g_value*)0, expt_cond, (s4g_node*)0, expt_step)
					);

				//�������� ��� ��� � _empty ���, ��� ��� �� ������� ��� � ���� ���
				s4g_node* tmpnode2 = NodePool.Alloc(_empty, curr_lexid, (s4g_value*)0, tmpnode);
				
				//������������ ������ �� ��������� ������
				*arrnode[arrnode.count_obj - 1].node = tmpnode2;
				arrnode[arrnode.count_obj - 1].node = &(tmpnode2->op2);

				//���������� ���� for, ������� ����� ������ �������, ��������� ���������� ���� ����� for
				arrnode.push_back(s4g_statement(tmpnode, &(tmpnode->op2->op2)));

			}
			else if (tmplexs->id == S4GLKW_DO)
			{
				++dowhile;
			}
			//�������� break ��������� �����
			else if (tmplexs->id == S4GLKW_BREAK)
			{
				lex_get_next0(tmplexs);
				//����� ����� ������ ���� ������� ; ���� ��� �� ���
				if (tmplexs->type != sym_delimiter || tmplexs->id != 0)
				{
					//������� ������
					status = -1;
					sprintf(this->error, "[%s]:%d - ';' expected but found '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
					return(0);
				}
				//������ ������ �� ��������� �������
				*arrnode[arrnode.count_obj - 1].node = NodePool.Alloc(_break, curr_lexid, (s4g_value*)0);
				arrnode[arrnode.count_obj - 1].node = &((*arrnode[arrnode.count_obj - 1].node)->op1);
			}
			//�������� continue
			else if (tmplexs->id == S4GLKW_CONTINUE)
			{
				lex_get_next0(tmplexs);
				//����� ����� ������ ���� ������� ; ���� ��� �� ���
				if (tmplexs->type != sym_delimiter || tmplexs->id != 0)
				{
					//������� ������
					status = -1;
					sprintf(this->error, "[%s]:%d - ';' expected but found '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
					return(0);
				}
				//������ ������ �� ��������� �������
				*arrnode[arrnode.count_obj - 1].node = NodePool.Alloc(_continue, curr_lexid, (s4g_value*)0);
				arrnode[arrnode.count_obj - 1].node = &((*arrnode[arrnode.count_obj - 1].node)->op1);
			}
		}
		//�����������
		else if (tmplexs->type == sym_delimiter)
		{
			//����������� ��������
			if (tmplexs->id == 0)
			{
				lex_get_next0(tmplexs);
				if (tmplexs)
				{
					s4g_node* tmpn = arrnode[arrnode.count_obj - 1].root;

					//��������� ����� ������ (empty) ��� � ��� �� ��������� �� ���������, ������� ����� ������������ ����
					*arrnode[arrnode.count_obj - 1].node = NodePool.Alloc(_empty, curr_lexid, (s4g_value*)0);
					arrnode[arrnode.count_obj - 1].node = &((*arrnode[arrnode.count_obj - 1].node)->op1);
				}
			}
		}
		//���� ������ ��������� �������, ���� ��������� �����
		else if (tmplexs->type == sym_table_create && tmplexs->id == 1)
		{
			this->overend++;	//�������������� ���������� ����� ��������� ���������
			//���� �� �� ������ ��� �� ����� ������ �� ����� ������
			if (this->overend > 0)
			{
				//������� ������
				status = -1;
				sprintf(this->error, "[%s]:%d - not found operation for end", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
				return 0;
			}

			lex_get_next0(tmplexs);

			//�������� ������������ ���, � ������ ��� ��� �������
			oldroot = arrnode[arrnode.count_obj - 1].root;

			//���� ����������� ��� ���� �� ��� � ������� � �������� ���� ����� else
			/*if (oldroot && oldroot->type == _block && oldroot->op1 && oldroot->op1->type == _if && oldroot->op1->op3)
			{
				//������ �� ��� ���������� ���� ���, ���� ��� ���� ���������
				--(arrnode.count_obj);
				oldroot = arrnode[arrnode.count_obj - 1].root;
			}*/

			//���� �������� ������������� ...
			/*if (oldroot && oldroot->ud == 10)
			{
				--(arrnode.count_obj);
				oldroot = arrnode[arrnode.count_obj - 1].root;
			}*/
			
			countinn = 0;

			s4g_statement tmpn = arrnode[arrnode.count_obj - 1];
			//������� �� ������� ��������� ���, ��� ��� ������ � ���� �� � ������
			--(arrnode.count_obj);
		}
		//���� � ��� ������ ������ �������, ������ � ��� ������ �����
		else if (tmplexs->type == sym_table_create && tmplexs->id == 0)
		{
			//������������� ���������� ��������� �� ������ �����
			s4g_begin_read_block();

			//� ��������� ��� ���������� �����
			(*arrnode[arrnode.count_obj - 1].node) = NodePool.Alloc(_empty, curr_lexid, (s4g_value*)0, NodePool.Alloc(_block, curr_lexid, (s4g_value*)0));
			
			//��������� ����� ���, ������� ���� ���� �����, �������� ����, ��� - ���� �����
			arrnode.push(s4g_statement((*arrnode[arrnode.count_obj - 1].node), &((*arrnode[arrnode.count_obj - 1].node)->op1->op1)));
			//������������� ��� ����� ���� ��� �� �������� ������ ���� ����� ��������� �� ��������� ��� ������� ����� ������������ ���� ����
			arrnode[arrnode.count_obj - 2].node = &((*arrnode[arrnode.count_obj - 2].node)->op2);
		}
		//����� ��������� ���������
		else
		{
			bool oldisender = isender;
			isender = false;
			s4g_node* tmpnode = NodePool.Alloc(_expr, curr_lexid, (s4g_value*)0, s4g_get_expr());

			lex_get_curr0(tmplexs);
			bst_cond_er(this);
			isender = oldisender;

			//���� ����� ��������� ��� ������� ��������� �������� ;
			if (!((tmplexs->type == sym_delimiter && tmplexs->id == 0) || (tmpnode->op1 && tmpnode->op1->type == _set && tmpnode->op1->op2 && tmpnode->op1->op2->type == _function)))	//error
			{
				status = -1;
				sprintf(this->error, "[%s]:%d - ';' expected but found '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
				return 0;
			}
			//����� ���� ��� ���������
			else
			{
				//���������� ����������� ����
				tmpnode->op2 = NodePool.Alloc(_empty, curr_lexid, (s4g_value*)0);

				//��������� ������
				*arrnode[arrnode.count_obj - 1].node = tmpnode;
				arrnode[arrnode.size() - 1].node = &((tmpnode)->op2->op1);

				//���� ���������� ���� ���������� ���������� �������� �������
				if (tmpnode && tmpnode->op1->type == _set && tmpnode->op1->op2->type == _function)
				{
					//������ ����
					s4g_begin_read_block();
					bst_cond_er(this);
					lex_get_curr0(tmplexs);
					//���������� ����� ����������, �������� _expr, ��� - ���� �������
					arrnode.push_back(s4g_statement(tmpnode,&(tmpnode->op1->op2->op2)));
				}
				else
				{
					lex_get_next0(tmplexs);
				}
			}
		}

		++countinn;	//��������� ���������� �������� � ������� ���������� ����������� ��������
	}
	return node;
}

int s4g_builder_syntax_tree::s4g_begin_read_block()
{
	s4g_lexeme* lex_get_curr0(tmplexs);
	if (tmplexs && tmplexs->type == sym_table_create && tmplexs->id == 0)
	{
		overend--;
		lex_get_next(tmplexs);
		return 1;
	}
	else if (tmplexs)
	{
		status = -1;
		sprintf(this->error, "[%s]:%d - expected begin block, but got %s", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
		return 0;
	}
	else
	{
		status = -1;
		sprintf(this->error, "[%s]:%d - unexpected end of file", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
		return 0;
	}
}

int s4g_builder_syntax_tree::s4g_end_read_block()
{
	s4g_lexeme* lex_get_curr0(tmplexs);
	if (tmplexs && tmplexs->type == sym_table_create && tmplexs->id == 0)
	{
		overend--;
		lex_get_next(tmplexs);
		return 1;
	}
	else if (tmplexs)
	{
		status = -1;
		sprintf(this->error, "[%s]:%d - expected end block, but got %s", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
		return 0;
	}
	else
	{
		status = -1;
		sprintf(this->error, "[%s]:%d - unexpected end of file", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
		return 0;
	}
}

s4g_node* s4g_builder_syntax_tree::s4g_get_term()
{
	s4g_lexeme* lex_get_curr0(tmplexs);
	bst_cond_eof(tmplexs);
	//���� ��� ������� ���������������� �����
	if (tmplexs->type == word_user)
	{
		//������� ��� ���� - ���������� �� ���������
		s4g_node* node = NodePool.Alloc(_var, curr_lexid, gc->cr_val(t_string, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS));
		s4g_node* tmpnode = node;
		bool isnext = true;

		//�������� ���� �������� - � �� ��������� �� ��� � �������� �������
		while (1)
		{
			lex_get_next0(tmplexs);
			//���� ������� ��������� � ���������� �� ������� .
			if (tmplexs->type == sym_table_elem && tmplexs->id == 2)
			{
				lex_get_next0(tmplexs);
				if (tmplexs->type == word_user)
				{
					tmpnode->op1 = NodePool.Alloc(_get, curr_lexid, (s4g_value*)0, NodePool.Alloc(_string, curr_lexid, gc->cr_val(t_string, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS)), NodePool.Alloc(_empty, curr_lexid));
					tmpnode = tmpnode->op1->op2;
				}
				
				else if (tmplexs->type == word_user_cr)
				{
					tmpnode->op1 = NodePool.Alloc(_get_cr, curr_lexid, (s4g_value*)0, NodePool.Alloc(_string, curr_lexid, gc->cr_val(t_string, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS)), NodePool.Alloc(_empty, curr_lexid));
					tmpnode = tmpnode->op1->op2;
				}
				else
				{
					lex_get_prev0(tmplexs);
					break;
				}
			}
			//����� ���� ������� ��������� � ���������� �� ������� [
			else if ((tmplexs->type == sym_table_elem && tmplexs->id == 0) || (tmplexs->type == sym_table_elem && tmplexs->id == 3))
			{
				int isnumelem = 0;

				//���� � ��� ������ ����� �������� ��������
				if (tmplexs->type == sym_table_elem && tmplexs->id == 3)
				{
					lex_get_next0(tmplexs);
					//���� ��������� ������� ��� �� ���������� �� ������� [
					if (!(tmplexs->type == sym_table_elem && tmplexs->id == 0))
					{
						//error
						status = -1;
						sprintf(this->error, "[%s]:%d - expected '[' after ':', but got %s", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
						return 0;
					}
					else
					{
						isnumelem = 1;
					}
				}
				lex_get_next0(tmplexs);

				//���� � ��� ���������� � ����� ������� []
				if (tmplexs->type == sym_table_elem && tmplexs->id == 1)
				{
					tmpnode->op1 = NodePool.Alloc(_append_table, curr_lexid);
					break;
				}

				tmpnode->op1 = NodePool.Alloc(_get, curr_lexid, (s4g_value*)isnumelem, s4g_get_expr(), NodePool.Alloc(_empty, curr_lexid));
				tmpnode = tmpnode->op1->op2;

				lex_get_curr0(tmplexs);
				//���� ��������� ������ �� ���������� �� ����������� ������ � ������� ]
				if (!(tmplexs->type == sym_table_elem && tmplexs->id == 1))
				{
					status = -1;
					sprintf(this->error, "[%s]:%d - none end for access in table", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
					return 0;
				}
			}
			//���� ���� ��� ���������� � ��������� ������ ��� ����������� ������
			else if (readcall && tmplexs->type == sym_group && tmplexs->id == 0)
			{
				//�� � ��� ����� �������
				long funccallidlex = curr_lexid;
				lex_get_next0(tmplexs);
				overge--;
				//��������� ��� ��������� ����������
				s4g_node* args = s4g_get_arg_call_func();

				bst_cond_er(this);
				lex_get_curr0(tmplexs);
				
				//op1 - ��� �������
				//op2 - ���������
				return NodePool.Alloc(_call, funccallidlex, (s4g_value*)0, node, (s4g_node*)args, (s4g_node*)0);
			}
			//����� � ��� ��� ��������� � ��������� �������
			else
			{
				//���������� � ���������� ������� � ������������ ����
				isnext = false;
				lex_get_prev0(tmplexs);
				break;
			}
		}

		lex_get_next0(tmplexs);
		return node;
	}
	//���� ���������������� �����, ����� ���� ����������
	else if (tmplexs->type == word_user_cr)
	{
		s4g_node* node = NodePool.Alloc(_crvar, curr_lexid, gc->cr_val(t_string, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS));
		lex_get_next0(tmplexs);
		return node;
	}
	//���� ��� ������� ������ ��������
	else if (tmplexs->type == word_null)
	{
		s4g_node* node = NodePool.Alloc(_null, curr_lexid, gc->cr_val_null(0, S4G_GC_TYPE_VAR_SYS));
		lex_get_next0(tmplexs);
		return node;
	}
	//���� ��� ������� ������
	else if (tmplexs->type == word_string)
	{
		s4g_node* node = NodePool.Alloc(_string, curr_lexid, gc->cr_val(t_string, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS));
		lex_get_next0(tmplexs);
		return node;
	}
	else if (tmplexs->type == word_string_cr)
	{
		s4g_node* node = NodePool.Alloc(_string_cr, curr_lexid, gc->cr_val(t_string, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS));
		lex_get_next0(tmplexs);
		return node;
	}
	//���� ��� ������� ����� � ��������� �������
	else if (tmplexs->type == word_float)
	{
		s4g_node* node = NodePool.Alloc(_float, curr_lexid, gc->cr_val(t_float, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS));
		lex_get_next0(tmplexs);
		return node;
	}
	//���� ��� ������� ������������� ��������
	else if (tmplexs->type == word_int)
	{
		s4g_node* node = NodePool.Alloc(_int, curr_lexid, gc->cr_val(t_int, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS));
		lex_get_next0(tmplexs);
		return node;
	}
	//���� ��� ������� �������� ������ �����
	else if (tmplexs->type == word_int_cr)
	{
		s4g_node* node = NodePool.Alloc(_int_cr, curr_lexid, gc->cr_val(t_int, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS));
		lex_get_next0(tmplexs);
		return node;
	}
	//���� ��� ������� ����������� ����� �����
	else if (tmplexs->type == word_uint)
	{
		s4g_node* node = NodePool.Alloc(_uint, curr_lexid, gc->cr_val(t_uint, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS));
		lex_get_next0(tmplexs);
		return node;
	}
	//���� ��� ������� ���������� ��������
	else if (tmplexs->type == word_bool)
	{
		s4g_node* node = NodePool.Alloc(_bool, curr_lexid, gc->cr_val(t_bool, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS));
		lex_get_next0(tmplexs);
		return node;
	}
	else
		return 0;
}

s4g_node* s4g_builder_syntax_tree::s4g_get_op()
{
	s4g_lexeme* lex_get_curr0(tmplexs);

	s4g_stack<s4g_node*> stack_var;
	s4g_stack<s4g_node*> stack_op;

	s4g_node* node = 0;
	s4g_node* tmpnode = 0;

	bool done = false;
	bool donable = tmplexs->type == sym_group && tmplexs->id == 0;

	int pareth = 0;
	int how_type_next = -4;	//-3 - sym_arif_assign ++ , -2 - sym_arif_assign -- , -1 - sym_arif, 0 - sym_group (, 1 - sym_group ), 2 - �����
	while (1)
	{
		lex_get_curr0(tmplexs);
		if (!tmplexs)
		{
			lex_get_prev0(tmplexs);
			break;
		}
		bst_cond_eof(tmplexs);

		//���� ��� ������� ������� �������������� ���� ��� ������
		if (tmplexs->type == sym_arif || tmplexs->type == sym_group)
		{
			if (how_type_next == -3 || how_type_next == -2)
			{
				status = -1;
				sprintf(this->error, "[%s]:%d - unexpected sequence arifmetic assignation and arifmetic operation", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
				return 0;
			}

			//���������� ��� �������� ����
			int tmptypeop = -1;

			//���� ������� ������ �������������� ��������
			if (tmplexs->type == sym_arif)
			{
				//���� ���������� ��� ��� �������������� ���������
				if (how_type_next == -1)	//error
				{
					if (!(
						tmplexs->id == S4GLAO_BIT_NOT
						|| tmplexs->id == S4GLAO_LOG_NOT
						))
					{
						status = -1;
						sprintf(this->error, "[%s]:%d - Invalid sequence of arithmetic operations one after the other", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
						return 0;
					}
					else
					{
						//��������� ������������� ����� 0
						stack_var.push(NodePool.Alloc(_numnull, curr_lexid, gc->cr_val(t_nnull, 0, 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS)));
					}
				}

				//���� �� ������ ������ ������������� ���������
				if (how_type_next == -4)
				{
					//� ������ �������������� ���������� ��������� �� -
					if (!(
						tmplexs->id == S4GLAO_SUB
						|| tmplexs->id == S4GLAO_BIT_NOT
						|| tmplexs->id == S4GLAO_LOG_NOT
						))	//error
					{
						status = -1;
						sprintf(this->error, "[%s]:%d - illegal inderection", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
						return 0;
					}
					//�����
					else/* if(tmplexs->id == S4GLAO_SUB)*/
					{
						//��������� ������������� ����� 0
						stack_var.push(NodePool.Alloc(_numnull, curr_lexid, gc->cr_val(t_nnull, 0, 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS)));
					}
				}

				//���� ���������� ���� ����������� ������
				if (how_type_next == 0)
				{
					//� ��������� �������������� �������� �� -
					if (!(
						tmplexs->id == S4GLAO_SUB
						|| tmplexs->id == S4GLAO_BIT_NOT
						|| tmplexs->id == S4GLAO_LOG_NOT
						))	//error
					{
						status = -1;
						sprintf(this->error, "[%s]:%d - illegal inderection", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
						return 0;
					}
					//�����
					else/* if(tmplexs->id == S4GLAO_SUB)*/
					{
						//��������� ������������� ����� 0
						stack_var.push(NodePool.Alloc(_numnull, curr_lexid, gc->cr_val(t_nnull, 0, 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS)));
					}
				}

				tmptypeop = s4g_aop_map[tmplexs->id];

				//�������� ��� ��� �������������� ������
				how_type_next = -1;
			}
			//����� ���� ������� ������ ����������� (������)
			else if (tmplexs->type == sym_group)
			{
				//���� �����������
				if (tmplexs->id == 0)
				{
					tmptypeop = _group_b;
					++pareth;
					how_type_next = 0;
				}
				//���� ������ ����������� ������
				else if (tmplexs->id == 1)
				{
					--pareth;
					//���� �� ������ ������
					if (how_type_next == -4)
					{
						status = -1;
						sprintf(this->error, "[%s]:%d - unresolved begin for expression [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
						return 0;
					}
					//� ��������� ������ �������������� ��������
					if (how_type_next == -1)	//error
					{
						status = -1;
						sprintf(this->error, "[%s]:%d - unresolved end for expression", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
						return 0;
					}
					tmptypeop = _group_e;
					how_type_next = 1;
					if (pareth == 0 && donable)
					{
						done = true;
					}
				}
			}

			//���� ���������� ��� �������� ���� �� �������� ����������� ������� ��� �����
			if (tmptypeop != -1)
			{
				//���� ��� ����������� ������
				if (tmptypeop == _group_e)
				{
					//���� � ����� �������� ����� ����
					if (stack_op.count() > 0)
					{
						if (stack_op.get(stack_op.count() - 1)->type == _group_b && stack_var.count() == 0)
						{
							status = -1;
							sprintf(this->error, "[%s]:%d - unresolved  null expression ()", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
							return 0;
						}
						bool is_find_gb = false;//������� �� ����������� ������
						//������ ����������� �� ����� �������� ��� ������ �� ������ ����������� ������
						while (stack_op.count() > 0)
						{
							//���� ��������� �������� � ����� ����������� ������ ���� ����� �������
							if (stack_op.get(stack_op.count() - 1)->type == _group_b)
							{
								//����������� �� �� ����� � ��������� ����
								stack_op.pop(1);
								is_find_gb = true;
								break;
							}
							else
							{
								s4g_node* qwert = stack_op.get(stack_op.count() - 1);
								stack_var.push(qwert);
								stack_op.pop(1);
							}
						}

						//���� �� ���� ������� ����������� ������ �� ������ � ��� ������
						if (!is_find_gb)	//error
						{
							overge++;
							//���� ����� �� ����� ������ �� ����� ����������� ������ �� ������ ��� ����� ������
							if (overge > 0) //error
							{
								status = -1;
								sprintf(this->error, "[%s]:%d - excess ')'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
								return 0;
							}
							//����� ������� ���� ������ �� �����
							//lex_get_prev0(tmplexs);
							break;
						}
					}
					//���� ���� ���� � � ��� ����������� ������
					else
					{
						overge++;
						//���� ����� �� ����� ������ �� ����� ����������� ������ �� ������ ��� ����� ������
						if (overge > 0) //error
						{
							status = -1;
							sprintf(this->error, "[%s]:%d - excess ')'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
							return 0;
						}
						//����� ������� ���� ������ �� �����
						//lex_get_prev0(tmplexs);
						break;
					}
				}
				//���� � ����� ����� ���� ���� �������� ���������� ������
				else if (stack_op.count() > 0 || tmptypeop == _group_b)
				{
					//���� ����������� ������
					if (tmptypeop == _group_b)
					{
						//������ ����������
						stack_op.push(NodePool.Alloc((s4g_type_op)tmptypeop, curr_lexid));
					}
					//����� ���� ��������� �������� ��������� ������ ���� ����� ���������� ����������� ���������
					else if (s4g_get_priority((s4g_type_op)tmptypeop) <= s4g_get_priority(stack_op.get(stack_op.count() - 1)->type))
					{
						//����������� ���������� �������� � �������� � ���� ����������
						s4g_node* qwert = stack_op.get(stack_op.count() - 1);
						stack_var.push(qwert/*stack_op.get(stack_op.count())*/);
						stack_op.pop(1);
						//�������� � ���� ���������� ������� ��������
						stack_op.push(NodePool.Alloc((s4g_type_op)tmptypeop, curr_lexid));
					}
					//����� ... �� ������� ���
					else
					{
						//��������
						stack_op.push(NodePool.Alloc((s4g_type_op)tmptypeop, curr_lexid));
					}
				}
				//����� ���� ���� � � ��� �����-�� ��������
				else
					stack_op.push(NodePool.Alloc((s4g_type_op)tmptypeop, curr_lexid));
			}
			//����� � ��� �������������� ��������
			else
			{
				//lex_get_prev0(tmplexs);
				break;
			}
			lex_get_next(tmplexs);
		}
		//����� ���� ������� ������� ����
		else if ((tmpnode = s4g_get_term()) != 0)
		{
			bst_cond_er(this);
			//���� ����������� ��� ��� ������ �� ������ � ��� ���� 2 ����� ������
			if (how_type_next == 2)	//error
			{
				status = -1;
				sprintf(this->error, "[%s]:%d - Invalid sequence of terms to each other", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
				return 0;
			}
			//����� � ��� ��� ���������/���������
			else if (how_type_next == -3 || how_type_next == -2)
			{
				//!!!���� �������� ����, �����������
				//���� �������� � ���� ����������, �������� ������ ��� �������:
				//� ���������� (_var)
				//� ���� ������� (_get)
				s4g_node* tmpnode2 = tmpnode;
				if (tmpnode2->op1 && tmpnode2->op1->type == _get)
					tmpnode2 = tmpnode2->op1;
				while (tmpnode2->op2 && tmpnode2->op2->op1 && tmpnode2->op2->op1->type == _get)
				{
					tmpnode2 = tmpnode2->op2->op1;
				}
				if (tmpnode == tmpnode2)
					tmpnode2->type = (how_type_next == -3 ? _var_preincr : _var_predecr);
				else
					tmpnode2->type = (how_type_next == -3 ? _get_preincr : _get_predecr);
			}

			/*//���� ���������� �������� ���� ����������� ������ � ����� �� ������� ����� �������
			if (how_type_next == 0 && tmpnode->type == _call)
			{
				lex_get_curr(tmplexs);
				//���� ������� ������� ��� ����������� ������
				if (tmplexs->type == sym_group && tmplexs->id == 1)
				{
					//���� ���������� ��������� ������ ����
					if (stack_op.count_obj > 0)
					{
						//���� ��������� ������� ��� ����������� ������
						s4g_node* tmptmpnode = stack_op.get(-1);
						if (tmptmpnode->type == _group_b)
						{
							tmpnode->value = (s4g_value*)1;
							lex_get_next(tmplexs);
							stack_op.pop(1);
						}
					}
				}
			}*/

			//�������� ��� � ��� ���� �����
			how_type_next = 2;
			stack_var.push(tmpnode);
		}
		//���� ������� ������� ��������� � �������� ������������
		else if (tmplexs->type == sym_arif_assign)
		{
			//���� ���������� �������� ���� ������������� �� ������
			if (how_type_next == -1 && !(tmplexs->id == 0 || tmplexs->id == 1))
			{
				status = -1;
				sprintf(this->error, "[%s]:%d - unexpected sequence arifmetic operation and arifmetic assignation", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
				return 0;
			}

			//���� ���������� ���� ����������� ���� ����������� �� ������
			//����������: ���� ���� ������ � ���������� ����������/����������
			//++var || var++ - �������� ���������
			if (how_type_next == -3 || how_type_next == -2)
			{
				status = -1;
				sprintf(this->error, "[%s]:%d - expected 'number', but got '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
				return 0;
			}

			//���� ���������� �������� ���� ������ (����������) � ������ � ��� ��������� ���� ���������
			if (how_type_next == 2 && (tmplexs->id == 0 || tmplexs->id == 1))
			{
				//���� �������� � ���� ����������, �������� ������ ��� �������:
				//� ���������� (_var)
				//� ���� ������� (_get)
				s4g_node* tmpnode = stack_var.get(-1);
				s4g_node* tmpnode2 = tmpnode;
				if (tmpnode2->op1 && tmpnode2->op1->type == _get)
					tmpnode2 = tmpnode2->op1;

				//������ ������ �� ����� � ���, ����� ����� �������� ����� � ���� ���������
				//������, ������� �� ��� ����� ����������������/����������������
				while (tmpnode2->op2 && tmpnode2->op2->op1 && tmpnode2->op2->op1->type == _get)
				{
					tmpnode2 = tmpnode2->op2->op1;
				}

				//���� ��������� ��������� ���� � ���� ������� ����� �������, �� ������ �� ������ � �� ������
				//� ������ ��� ������ ��� �������� ��������� � ����������
				if (tmpnode == tmpnode2)
					tmpnode2->type = (tmplexs->id == 0 ? _var_postincr : _var_postdecr);
				else //����� �������� ����������� � ���� �������
					tmpnode2->type = (tmplexs->id == 0 ? _get_postincr : _get_postdecr);

				how_type_next = 2;
			}
			else
			{
				//???
				if (tmplexs->id == 0)
					how_type_next = -3;
				else if (tmplexs->id == 1)
					how_type_next = -2;
				else
				{
					status = -1;
					sprintf(this->error, "[%s]:%d - unknown sequence of arithmetic assignation '%s'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
					return 0;
				}
			}

			lex_get_next(tmplexs);
		}
		//����� � ��� �� �������� � �� ����
		else
		{
			//��������� ����
			break;
		}
		if (done)
		{
			break;
		}
	}

	//���� ��������� �������� ��������� �������������� ��������
	if (how_type_next == -1)	//error
	{
		lex_get_prev0(tmplexs);
		status = -1;
		sprintf(this->error, "[%s]:%d - invalid end for expression", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
		return 0;
	}

	//���� ���� �������� �� ���������
	if (stack_op.count() > 0)
	{
		//������ ����������� ��� �� ����� �������� 
		//� ���������� ��� ��� �������� � ����������
		for (int i = 0; i<stack_op.count(); i++)
		{
			s4g_node* tmtm = stack_op.get((stack_op.count() - i) - 1);

			//���� � ��� ����������� ����������� ������ �� ������ �� �� �� �������
			if (tmtm->type == _group_b)	//error
			{
				status = -1;
				sprintf(this->error, "[%s]:%d - no ')'", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
				return 0;
			}
			stack_var.push(tmtm);
		}

	}

	//���� ���������� ��������� ������ ������ ���� �� ���������� ������ ��������� � �������� ���
	if (stack_var.count() > 0)
	{
		node = stack_var.get(0);

		tmpnode = node;
		for (int i = 1; i<stack_var.count(); i++)
		{
			//s4g_node* tmtm22= stack_var.get(i);

			tmpnode->op3 = stack_var.get(i);//����������� ������ ���, ��� � ������ ���� ����� ���� ��������� � ��������� �������, � �� ������ ��������� ��� ������ �������!!!
			tmpnode = tmpnode->op3;
		}
	}

	return node;
}

s4g_node* s4g_builder_syntax_tree::s4g_get_function_def_head()
{
	s4g_lexeme* lex_get_curr0(tmplexs);
	s4g_node* node = NodePool.Alloc(_arg, curr_lexid);
	s4g_node* tmpnode = node;
	s4g_node* tmpnode2 = 0;
	Array<String> arrarg;

	while (1)
	{
		lex_get_curr0(tmplexs);

		//���� ��� ������� ����������� ������
		if (tmplexs->type == sym_group && tmplexs->id == 1)
		{
			lex_get_next(tmplexs);
			break;
		}
		//���� ��� ������� �� ����������� ������
		else if (!(tmplexs->type == sym_delimiter && tmplexs->id == 1))
		{
			//���� ��� ������� ���������������� �����
			if (tmplexs->type == word_user)
			{
				//��������� �������� �� ������������
				for (int i = 0; i<arrarg.size(); i++)
				{
					String str = arrarg[i];
					if (arrarg[i] == tmplexs->str)
					{
						this->status = -1;
						sprintf(this->error, "[%s]:%d - non unic argument [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
						return 0;
					}
				}

				//���� �� ��� �� ���� ������ ����
				if (node->value == 0)
				{
					tmpnode->value = gc->cr_val(t_string, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS);
				}
				else
				{
					tmpnode->op1 = NodePool.Alloc(_arg, curr_lexid, gc->cr_val(t_string, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS));
					tmpnode = tmpnode->op1;
				}

				arrarg.push_back(tmplexs->str);
				lex_get_next0(tmplexs);

				if ((tmplexs->type == sym_delimiter && tmplexs->id == 1))
				{
					lex_get_next(tmplexs);
				}
				else if (!(tmplexs->type == sym_group && tmplexs->id == 1))
				{
					this->status = -1;
					sprintf(this->error, "[%s]:%d - no separate arguments", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
					return 0;
				}
			}
			else if (tmplexs->type == marg)
			{
				tmpnode->op1 = NodePool.Alloc(_marg, curr_lexid);
				lex_get_next0(tmplexs);
				if (!(tmplexs->type == sym_group && tmplexs->id == 1))
				{
					this->status = -1;
					sprintf(this->error, "[%s]:%d - expected ')' but got %s", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
					return 0;
				}
				lex_get_next0(tmplexs);
				break;
			}
			//����� � ��� �� ���������������� �����
			else //error
			{
				this->status = -1;
				sprintf(this->error, "[%s]:%d - unresolved type for argument [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
				return 0;
			}
		}
		//����� � ��� ������� ������ ���
		else //error
		{
			this->status = -1;
			sprintf(this->error, "[%s]:%d - unresolved definition for argument [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
			return 0;
		}
	}
	return node;
}

s4g_node* s4g_builder_syntax_tree::s4g_get_table()
{
	s4g_lexeme* lex_get_curr0(tmplexs);
	s4g_node* node = NodePool.Alloc(_create_table, curr_lexid, gc->cr_val_null(0, S4G_GC_TYPE_VAR_SYS));
	s4g_node* tmpnode = node;
	int type_last = -1;

	while (1)
	{
		lex_get_curr0(tmplexs);
		if (type_last == 1 && !(tmplexs->type == sym_delimiter && tmplexs->id == 1) && !(tmplexs->type == sym_table_create && tmplexs->id == 1))
		{
			this->status = -1;
			sprintf(this->error, "[%s]:%d - expected delimiter arg but got [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
			return 0;
		}
		//���� ������ ��������� ������� }
		if (tmplexs->type == sym_table_create && tmplexs->id == 1)
		{
			if (type_last == 0)
			{
				this->status = -1;
				sprintf(this->error, "[%s]:%d - expected arg but got end definition of the table", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
				return 0;
			}
			lex_get_next(tmplexs);
			break;
		}
		//���� �� �������
		else if (!(tmplexs->type == sym_delimiter && tmplexs->id == 1))
		{
			s4g_node* tmpnode2 = s4g_get_expr(false);

			lex_get_curr0(tmplexs);
			bst_cond_er(this);

			if (tmpnode2->type != _set || (!tmpnode2->op1 && tmpnode2->op2 && tmpnode2->op2->type == _create_table))
			{
				if (!tmpnode2->op1 && tmpnode2->op2 && tmpnode2->op2->type == _create_table)
				{
					tmpnode2 = tmpnode2->op2;
				}
				tmpnode->op1 = NodePool.Alloc(_add_in_table, curr_lexid, (s4g_value*)0, tmpnode2, NodePool.Alloc(_empty, curr_lexid));
				tmpnode = tmpnode->op1->op2;
			}
			else
			{
				tmpnode2->type = _sett;
				tmpnode->op1 = tmpnode2;
				tmpnode->op2 = NodePool.Alloc(_empty, curr_lexid);
				tmpnode = tmpnode->op2;
			}
			type_last = 1;
		}
		else if ((tmplexs->type == sym_delimiter && tmplexs->id == 1))
		{
			if (type_last == 0)
			{
				this->status = -1;
				sprintf(this->error, "[%s]:%d - expected double delimiter ','", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
				return 0;
			}
			lex_get_next(tmplexs);
			type_last = 0;
		}
	}

	return node;
}

s4g_node* s4g_builder_syntax_tree::s4g_get_arg_call_func()
{
	s4g_lexeme* lex_get_curr0(tmplexs);
	s4g_node* node = NodePool.Alloc(_arg);
	s4g_node* tmpnode = node;
	s4g_node* tmpnode2 = 0;
	int type_last = -1;

	while (1)
	{
		lex_get_curr0(tmplexs);
		if (type_last == 1 && !(tmplexs->type == sym_delimiter && tmplexs->id == 1) && !(tmplexs->type == sym_group && tmplexs->id == 1))
		{
			this->status = -1;
			sprintf(this->error, "[%s]:%d - expected delimiter arg but got [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
			return 0;
		}
		//���� ������� ������ ����������� ������
		if (tmplexs->type == sym_group && tmplexs->id == 1)
		{
			if (type_last == 0)
			{
				this->status = -1;
				sprintf(this->error, "[%s]:%d - expected arg but got end call of function", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
				return 0;
			}
			lex_get_next0(tmplexs);
			break;
		}
		else if (!(tmplexs->type == sym_delimiter && tmplexs->id == 1))
		{
			tmpnode2 = s4g_get_expr();
			bst_cond_er(this);
			tmpnode->op1 = tmpnode2;//new s4g_node(_expr,0,tmpnode2,new s4g_node(_empty));
			tmpnode->op2 = NodePool.Alloc(_empty, curr_lexid);
			tmpnode = tmpnode->op2;
			type_last = 1;
		}
		else if ((tmplexs->type == sym_delimiter && tmplexs->id == 1))
		{
			if (type_last == 0)
			{
				this->status = -1;
				sprintf(this->error, "[%s]:%d - expected double delimiter ','", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
				return 0;
			}
			type_last = 0;
			lex_get_next(tmplexs);
		}

	}
	return node;
}

s4g_node* s4g_builder_syntax_tree::s4g_get_expr(bool isfull)
{
	s4g_lexeme* lex_get_curr0(tmplexs);

	//��������� ��������
	s4g_node* node = s4g_get_op();

	lex_get_curr0(tmplexs);

	if (node == 0)
	{
		//���� ������ �������� �������
		if (tmplexs->type == sym_table_create && tmplexs->id == 0)
		{
			//���� � ��� �� ������ ������������ ���������, ������ ������� ��������� ������
			/*if (!isfull)
			{
				//������� ������
				status = -1;
				sprintf(this->error, "[%s]:%d - unresolved create table", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
				return 0;
			}*/

			bst_cond_er(this);
			lex_get_next(tmplexs);
			return NodePool.Alloc(_set, curr_lexid, (s4g_value*)0, node, s4g_get_table());
		}
		else 
			return 0;
	}

	//���� ��� �������� ���� ���������� � ��������� ������� ����������
	if ((node->type == _var || node->type == _crvar) && tmplexs->type == sym_assign)
	{
		//���� ������ ��� ����������, �� ������ �� ������� ���������
		if (node->op3)
		{
			//� ��� �� ���������, ����������� ����� ������ ����������!!!
			this->status = -1;
			sprintf(this->error, "[%s]:%d - unresolved assignation", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
			return 0;
		}

		lex_get_next0(tmplexs);

		//���� ������ �������� �������
		if (tmplexs->type == sym_table_create && tmplexs->id == 0)
		{
			//���� � ��� �� ������ ������������ ���������, ������ ������� ��������� ������
			/*if (!isfull)
			{
				//������� ������
				status = -1;
				sprintf(this->error, "[%s]:%d - unresolved create table", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
				return 0;
			}*/
			lex_get_next(tmplexs);
			//������� ��� � �������� ���������� �������
			return NodePool.Alloc(_set, curr_lexid, (s4g_value*)0, node, s4g_get_table());
		}
		//����� ���� ������ �������
		else if (tmplexs->type == word_key && tmplexs->id == 1)
		{
			//���� � ��� �� ������ ������������ ���������, ������ ������� ��������� ������
			if (!isfull)
			{
				//������� ������
				status = -1;
				sprintf(this->error, "[%s]:%d - unresolved create function", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
				return 0;
			}

			long cfunclexid = curr_lexid;
			//��������� ��� ���� ��� �������
			s4g_node* name_func = node;	

			lex_get_next0(tmplexs);
			bst_cond_eof(tmplexs);

			//���� ������� ��� ����������� ������
			if (tmplexs->type == sym_group && tmplexs->id == 0)
				lex_get_next(tmplexs)
			else //����� ������, ��� ��� ���� ���-��������������� ���������
			{
				status = -1;
				sprintf(this->error, "[%s]:%d - expected '(' but got [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
				return 0;
			}

			//��� ��������� �������
			s4g_node* head_func = s4g_get_function_def_head();
			bst_cond_er(this);
			lex_get_curr0(tmplexs);

			//�������� � ��� ���� ������ ������� �� ������ ����� �� ���������� ����������� ����
			//������ ����� ���� �����������, ������ ������� ���������� ...
			//{
			s4g_node* extern_data = 0;
			s4g_node* tmped = 0;
			s4g_stack<String> tmparrnames;
			//���� ������� ������� ��� �������� ����� extern
			if (tmplexs->type == word_key && tmplexs->id == 4)
			{
				//��� ��������� �������
				//-1 - ������ ������ ����, �������
				//0 - ������� ,
				//1 - ����������
				int type_last = -1;
				while (true)
				{
					lex_get_next0(tmplexs);
					s4g_node* tmpop = 0;
					//���� ���������� ��� ������� ���������� � ������� ��� �� ������� (,) � �� ����� � ������� (;)
					if (type_last == 1 && !(tmplexs->type == sym_delimiter && tmplexs->id == 1) && !(tmplexs->type == sym_delimiter && tmplexs->id == 0))
					{
						//�������������� ������
						this->status = -1;
						sprintf(this->error, "[%s]:%d - ',' expected delimiter extern data but got [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
						return 0;
					}
					//���� ���������� ������� ���� ���� ������� ���� ������� � ������� ������� ��� ����������
					else if ((type_last == 0 || type_last == -1) && tmplexs->type == word_user)
					{
						for (int i = 0; i < tmparrnames.count_obj; ++i)
						{
							if (tmparrnames[i] == tmplexs->str)
							{
								this->status = -1;
								sprintf(this->error, "[%s]:%d - not unic variable [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str.c_str());
								return 0;
							}
						}
						tmparrnames.push(tmplexs->str);
						//������� ��� � ����������
						tmpop = NodePool.Alloc(_var, curr_lexid, gc->cr_val(t_string, tmplexs->str.c_str(), 0, S4G_GC_TYPE_VAR_SYS, S4G_GC_TYPE_DATA_SYS));
						type_last = 1;	//�������� � ����
						
						//���� ��� ��������������� ������ � ������������
						if (extern_data)
						{
							tmped->op1 = tmpop;
							tmped = tmped->op1;
						}
						//����� ��� �� ��������������� ������ � ������������
						else
						{
							//��������������
							extern_data = tmpop;
							tmped = extern_data;
						}
					}
					//���� ���������� ������� ���� ���������������� ������ (����������) � ������� ������� ,
					else if (type_last == 1 && tmplexs->type == sym_delimiter && tmplexs->id == 1)
					{
						type_last = 0;	//�������� �� ����
					}
					//���� ������� ������� ;
					else if (tmplexs->type == sym_delimiter && tmplexs->id == 0)
					{
						//����� ��������� ������� � ��������� ����
						lex_get_next0(tmplexs);
						break;
					}
				}
			}
			//}

			bst_cond_er(this);
			lex_get_curr0(tmplexs);

			//op1 - ��� �������
			//op2 - ����, ������� ��� �� ��������
			//op3 - �������������� ������ �� ���������� ����������
			s4g_node* nfunc = NodePool.Alloc(_function, cfunclexid, (s4g_value*)0, head_func, (s4g_node*)0, extern_data);
			return NodePool.Alloc(_set, cfunclexid - 1, (s4g_value*)0, name_func, nfunc);
		}
	
		//���� �� ����� ��������� �� ������ ������ ����� �� ��������� ������� ���������
		return NodePool.Alloc(_set, curr_lexid, (s4g_value*)0, node, s4g_get_expr(isfull));
	}
	return node;
}

s4g_node* s4g_builder_syntax_tree::s4g_gen_tree()
{
	status = 0; error[0] = 0;
	s4g_node* tmpnode = 0;
	arr_lex->set_curr_num(0);
	tmpnode = s4g_gen_statement();

	return tmpnode;
}
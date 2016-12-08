
#pragma once
#include <s4g\s4g_parser.h>

#include <s4g\s4g_vm.cpp>
#include <s4g\s4g_compiler.cpp>
#include <s4g\s4g_lexer.cpp>


///////////////

s4g_node* s4g_builder_syntax_tree::s4g_gen_statement()
{
	 s4g_lexeme* lex_get_curr0(tmplexs);
	
		//���� ������� �� ������� ������ ������ ����� ������� ���������
		if(tmplexs == 0)
		{
			return 0;
		}
	s4g_node* node=0;

		//���� ��� ������� ��� �������� ����� �����
		if(tmplexs->type == word_key)
		{
				//������������ /return
				if(tmplexs->id == 3)
				{
					bool oldisender = isender;
					isender = false;
					lex_get_next0(tmplexs);
					listread = false;
					s4g_node* tmpnode = s4g_get_ret_vals();	//��������� ������������ ���������
					bst_cond_er(this);
					listread = true;
					isender = oldisender;
					tmpnode->op3 = s4g_gen_statement();	//� ��������� �� ��� ����� return
					bst_cond_er(this);
					return tmpnode;
				}
				//���������� ������� /function
				else if(tmplexs->id == 1)
				{
					bool oldisender = isender;
					isender = false;
					s4g_lexeme* sfunclex = tmplexs;
					s4g_node* name_func = 0;
					lex_get_next0(tmplexs);

						//���� ��� ������� ���������������� �����
						if(tmplexs->type == word_user_cr)
						{
							status = -1;
							sprintf(this->error, "[%s]:%d - function provides for the creation of a new variable, it's too much [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, s4g_key_syms_create[0]);
							return 0;
						}
						else if (tmplexs->type == word_user)
						{
							readcall = false;
							name_func = s4g_get_term();
							name_func->type = _crvar;
							readcall = true;
						}
						else //error
						{
							status = -1;
							sprintf(this->error,"[%s]:%d - unresolved word for name function [%s]",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr,tmplexs->str);
							return 0;
						}

					lex_get_curr0(tmplexs);
					bst_cond_er(this);
						//���� ������� ��� ����������� ������
						if(tmplexs->type == sym_group && tmplexs->id == 0)
							lex_get_next(tmplexs)
						else //error
						{
							status = -1;
							sprintf(this->error,"[%s]:%d - unresolved word for name function [%s]",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr,tmplexs->str);
							return 0;
						}

					s4g_node* head_func = s4g_get_function_def_head();
					bst_cond_er(this);
					this->overend--;
					
					s4g_node* body_func = s4g_gen_statement();
					
					bst_cond_er(this);
					lex_get_curr0(tmplexs);
						//���� ������� ������� �� �������� ���������� �������� end
						if(!(arr_lex->get_curr_num() < arr_lex->get_count() && tmplexs->type == word_key && tmplexs->id == 2)) //error
						{
							status = -1;
							sprintf(this->error,"[%s]:%d - not found end for funcion",this->arr_lex->ArrFiles[sfunclex->fileid],sfunclex->numstr);
							return 0;
						}
					lex_get_next0(tmplexs);
					s4g_node* nfunc = new s4g_node(_function,0,head_func,body_func);
					isender = oldisender;
					return new s4g_node(_expr,0,new s4g_node(_set,0,name_func,nfunc),new s4g_node(_empty,0,s4g_gen_statement()));
				}
				//����� /end
				else if(tmplexs->id == 2)
				{
					this->overend++;
						//���� �� �� ������ ��� �� ����� ������ �� ����� ������
						if(this->overend > 0)
						{
							status = -1;
							sprintf(this->error,"[%s]:%d - not found operation for end",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr);
						}
					return 0;
				}
		}
		//�����������
		else if(tmplexs->type == sym_delimiter)
		{
				//����������� ��������
				if(tmplexs->id == 0)
				{
					lex_get_next0(tmplexs);
						if (tmplexs)
							return new s4g_node(_empty,0,s4g_gen_statement());
				}
		}
		//����� � ��������� ���������
		else
		{
			bool oldisender = isender;
			isender = false;
			node = new s4g_node(_expr,0,s4g_get_expr());
			lex_get_curr0(tmplexs);
			bst_cond_er(this);
			isender = oldisender;
				//���� ����� ��������� ��� ������� ��������� �������� ;
				if(!(tmplexs->type == sym_delimiter && tmplexs->id == 0))	//error
				{
						if(status == 0)
						{
							status = -1;
							sprintf(this->error,"[%s]:%d - none end for expression",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr);
						}
					return 0;
				}
				else
				{
					lex_get_next0(tmplexs);
					if (tmplexs)
					{
						node->op2 = new s4g_node(_empty, 0, s4g_gen_statement());
						bst_cond_er(this);
					}
				}
		}
	
	return node;
}

s4g_node* s4g_builder_syntax_tree::s4g_get_term()
{
	s4g_lexeme* lex_get_curr0(tmplexs);
	bst_cond_eof(tmplexs);
		//���� ��� ������� ���������������� �����
		if(tmplexs->type == word_user)
		{
			//������� ��� ���� - ���������� �� ���������
			s4g_node* node = new s4g_node(_var, gc->cr_val(t_string, tmplexs->str, curr_lexid));
			s4g_node* tmpnode = node;
			bool isnext = true;
			//lex_get_next0(tmplexs);
			//�������� ���� �������� - � �� ��������� �� ��� � �������� �������
				while(1)
				{
					lex_get_next0(tmplexs);
						//���� ������� ��������� � ���������� �� ������� .
						if(tmplexs->type == sym_table_elem && tmplexs->id == 2)
						{
							lex_get_next0(tmplexs);
								if(tmplexs->type == word_user)
								{
									tmpnode->op1 = new s4g_node(_get, 0, new s4g_node(_string, gc->cr_val(t_string, tmplexs->str, curr_lexid)), new s4g_node(_empty));
									tmpnode = tmpnode->op1->op2;
									//lex_get_next0(tmplexs);
								}
								else if (tmplexs->type == word_user_cr)
								{
									tmpnode->op1 = new s4g_node(_get_cr, 0, new s4g_node(_string, gc->cr_val(t_string, tmplexs->str, curr_lexid)), new s4g_node(_empty));
									tmpnode = tmpnode->op1->op2;
									//lex_get_next0(tmplexs);
								}
								else
								{
									arr_lex->get_prev();
									break;
								}
						}
						//����� ���� ������� ��������� � ���������� �� ������� [
						else if(tmplexs->type == sym_table_elem && tmplexs->id == 0)
						{
							lex_get_next0(tmplexs);
							tmpnode->op1 = new s4g_node(_get,0,s4g_get_expr(),new s4g_node(_empty));
							tmpnode = tmpnode->op1->op2;

							lex_get_curr0(tmplexs);
								//���� ��������� ������ �� ���������� �� ����������� ������ � ������� ]
								if(!(tmplexs->type == sym_table_elem && tmplexs->id == 1))
								{
									status = -1;
									sprintf(this->error,"[%s]:%d - none end for access in table",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr);
									return 0;
								}
						}
						//���� ���� ��� ���������� � ��������� ������ ��� ����������� ������
						else if (readcall && tmplexs->type == sym_group && tmplexs->id == 0)
						{
							//�� � ��� ����� �������
							lex_get_next0(tmplexs);
							bst_cond_eof(tmplexs);
							overge--;
							bool oldlistread = listread;
							listread = false;
							s4g_node* args = s4g_get_arg_call_func();
							listread = oldlistread;
							bst_cond_er(this);
							lex_get_curr0(tmplexs);
							//lex_get_prev0(tmplexs);
							return new s4g_node(_call, 0, node, 0, args);
						}
						//����� � ��� ��� ��������� � ��������� �������
						else 
						{
							//���������� � ���������� ������� � ������������ ����
							isnext = false;
							arr_lex->get_prev();
							break;
						}
				}

			lex_get_next0(tmplexs);
			return node;
		}
		else if (tmplexs->type == word_user_cr)
		{
			lex_get_next0(tmplexs);
			return new s4g_node(_crvar, gc->cr_val(t_string, tmplexs->str, curr_lexid - 1));
		}
		//���� ��� ������� ������ ��������
		else if(tmplexs->type == word_null)
		{
			lex_get_next0(tmplexs);
			return new s4g_node(_null, gc->cr_val_null(curr_lexid - 1));
		}
		//���� ��� ������� ������
		else if(tmplexs->type == word_string)
		{
			lex_get_next0(tmplexs);
			return new s4g_node(_string, gc->cr_val(t_string, tmplexs->str, curr_lexid - 1));
		}
		else if (tmplexs->type == word_string_cr)
		{
			lex_get_next0(tmplexs);
			return new s4g_node(_string_cr, gc->cr_val(t_string, tmplexs->str, curr_lexid - 1));
		}
		//���� ��� ������� ����� � ��������� �������
		else if(tmplexs->type == word_float)
		{
			lex_get_next0(tmplexs);
			return new s4g_node(_float, gc->cr_val(t_float, tmplexs->str, curr_lexid - 1));
		}
		//���� ��� ������� ������������� ��������
		else if(tmplexs->type == word_int)
		{
			lex_get_next0(tmplexs);
			return new s4g_node(_int, gc->cr_val(t_int, tmplexs->str, curr_lexid - 1));
		}
		else if (tmplexs->type == word_int_cr)
		{
			lex_get_next0(tmplexs);
			return new s4g_node(_int_cr, gc->cr_val(t_int, tmplexs->str, curr_lexid - 1));
		}
		else if (tmplexs->type == word_bool)
		{
			lex_get_next0(tmplexs);
			return new s4g_node(_bool, gc->cr_val(_bool, tmplexs->str, curr_lexid - 1));
		}
		else
			return 0;
}

s4g_node* s4g_builder_syntax_tree::s4g_get_op()
{
	s4g_lexeme* lex_get_curr0(tmplexs);
	Stack<s4g_node*> stack_var;
	Stack<s4g_node*> stack_op;
	s4g_node* node = 0;
	s4g_node* tmpnode = 0;
	s4g_node* tmpnode2 = 0;
	s4g_node* tmpnode3 = 0;
	String strt;
	bool locallistread = true; //���� ������ ��������� �������������� �������� �� ��������� ���������� ����� ����������
	long curr_num_lex = arr_lex->get_curr_num();
	int how_type_next = -2;	//-1 - sym_arif, 0 - sym_group (, 1 - sym_group ), 2 - �����
		while(1)
		{
			lex_get_curr0(tmplexs);
			if (!tmplexs)
			{
				arr_lex->get_prev();
				break;
			}
			bst_cond_eof(tmplexs);
			curr_num_lex = arr_lex->get_curr_num();
				//���� ��� ������� ������� �������������� ���� ��� ������
				if(tmplexs->type == sym_arif || tmplexs->type == sym_group)
				{
					locallistread = false;
					//���������� ��� �������� ����
					int tmptypeop = -1;
						if(tmplexs->type == sym_arif)
						{
								//���� ���������� ��� ��� �������������� ���������
								if(how_type_next == -1)	//error
								{
									status = -1;
									sprintf(this->error,"[%s]:%d - Invalid sequence of arithmetic operations one after the other",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr);
									return 0;
								}

								//���� �� ������ ������ ������������� ���������
								if(how_type_next == -2)
								{
										//� ������ �������������� ���������� ��������� �� -
										if(tmplexs->id != 1)	//error
										{
											status = -1;
											sprintf(this->error,"[%s]:%d - illegal inderection",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr);
											return 0;
										}
										//�����
										else
										{
											//��������� ������������� ����� 0
											stack_var.push(new s4g_node(_numnull, gc->cr_val(t_nn, 0, curr_lexid)));
										}
								}

								//���� ���������� ���� ����������� ������
								if(how_type_next == 0)
								{
										//� ��������� �������������� �������� �� -
										if(tmplexs->id != 1)	//error
										{
											status = -1;
											sprintf(this->error,"[%s]:%d - illegal inderection",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr);
											return 0;
										}
										//�����
										else 
										{
											//��������� ������������� ����� 0
											stack_var.push(new s4g_node(_numnull, gc->cr_val(t_nn, 0, curr_lexid)));
										}
								}

								if(tmplexs->id == 0)
									tmptypeop = _add;
								else if(tmplexs->id == 1)
									tmptypeop = _sub;
								else if(tmplexs->id == 2)
									tmptypeop = _mul;
								else if(tmplexs->id == 3)
									tmptypeop = _div;

							how_type_next = -1;
						}
						else if(tmplexs->type == sym_group)
						{
								if(tmplexs->id == 0)
								{
									tmptypeop = _group_b;
									how_type_next = 0;
								}
								//���� ������ ����������� ������
								else if(tmplexs->id == 1)
								{
										if (how_type_next == -2)
										{
											status = -1;
											sprintf(this->error, "[%s]:%d - unresolved begin for expression [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
											return 0;
										}
										//� ��������� ������ �������������� ��������
										if(how_type_next == -1)	//error
										{
											status = -1;
											sprintf(this->error,"[%s]:%d - unresolved end for expression",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr);
											return 0;
										}
									tmptypeop = _group_e;
									how_type_next = 1;
								}
						}

						//���� ���������� ��� �������� ���� �� �������� ����������� ������� ��� �����
						if(tmptypeop != -1)
						{
								//���� ��� ����������� ������
								if(tmptypeop == _group_e)
								{
										//���� � ����� �������� ����� ����
										if(stack_op.count() > 0)
										{
												if (stack_op.get(stack_op.count())->type == _group_b)
												{
													status = -1;
													sprintf(this->error, "[%s]:%d - unresolved  null expression ()", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr);
													return 0;
												}
											bool is_find_gb = false;//������� �� ����������� ������
												//������ ����������� �� ����� �������� ��� ������ �� ������ ����������� ������
												while(stack_op.count() > 0)
												{
														//���� ��������� �������� � ����� ����������� ������
														if(stack_op.get(stack_op.count())->type == _group_b)
														{
															//����������� �� �� ����� � ��������� ����
															stack_op.pop(1);
															is_find_gb = true;
															break;
														}
														else
														{
															s4g_node* qwert = stack_op.get(stack_op.count());
															stack_var.push(qwert);
															stack_op.pop(1);
														}
												}

												//���� �� ���� ������� ����������� ������ �� ������ � ��� ������
												if(!is_find_gb)	//error
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
													//arr_lex->get_prev();
													break;
												}
										}
										//���� ���� ���� � � ��� ����������� ������
										else
										{
											overge++;
												//���� ����� �� ����� ������ �� ����� ����������� ������ �� ������ ��� ����� ������
												if(overge > 0) //error
												{
													status = -1;
													sprintf(this->error,"[%s]:%d - excess ')'",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr);
													return 0;
												}
											//����� ������� ���� ������ �� �����
											//arr_lex->get_prev();
											break;
										}
								}
								//���� � ����� ����� ���� ���� �������� ���������� ������
								else if(stack_op.count() > 0 || tmptypeop == _group_b)
								{
										if(tmptypeop == _group_b)
										{
											stack_op.push(new s4g_node((s4g_type_op)tmptypeop));
										}
										else if(s4g_get_priority((s4g_type_op)tmptypeop) <= s4g_get_priority(stack_op.get(stack_op.count())->type))
										{
											//�����������
											s4g_node* qwert = stack_op.get(stack_op.count());
											stack_var.push(qwert/*stack_op.get(stack_op.count())*/);
											stack_op.pop(1);
											stack_op.push(new s4g_node((s4g_type_op)tmptypeop));
										}
										else
										{
											//��������
											stack_op.push(new s4g_node((s4g_type_op)tmptypeop));
										}
								}
								//����� ���� ���� � � ��� �����-�� ��������
								else
									stack_op.push(new s4g_node((s4g_type_op)tmptypeop));
						}
						//����� � ��� �������������� ��������
						else
						{
							//arr_lex->get_prev();
							break;
						}
					lex_get_next0(tmplexs);
				}
				//����� ���� ������� ������� ����
				else if((tmpnode = s4g_get_term()) != 0)
				{
					bst_cond_er(this);
						//���� ����������� ��� ��� ������ �� ������ � ��� ���� 2 ����� ������
						if(how_type_next == 2)	//error
						{
							status = -1;
							sprintf(this->error,"[%s]:%d - Invalid sequence of terms to each other",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr);
							return 0;
						}
					
					stack_var.push(tmpnode);
					how_type_next = 2;
				}
				//����� � ��� �� �������� � �� ����
				else
				{
					//��������� ����
					//arr_lex->get_prev();
					break;
				}
		}

		//���� ��������� �������� ��������� �������������� ��������
		if(how_type_next == -1)	//error
		{
			lex_get_prev0(tmplexs);
			status = -1;
			sprintf(this->error,"[%s]:%d - invalid end for expression",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr);
			return 0;
		}

		//���� ���� �������� �� ���������
		if(stack_op.count() > 0)
		{
				//������ ����������� ��� �� ����� �������� 
				//� ���������� ��� ��� �������� � ����������
				for(int i=0;i<stack_op.count();i++)
				{
					s4g_node* tmtm = stack_op.get(stack_op.count()-i);
					
						//���� � ��� ����������� ����������� ������ �� ������ �� �� �� �������
						if(tmtm->type == _group_b)	//error
						{
							status = -1;
							sprintf(this->error,"[%s]:%d - no ')'",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr);
							return 0;
						}
					stack_var.push(tmtm);
				}
			
		}
	
		//���� ���������� ��������� ������ ������ ���� �� ���������� ������ ��������� � �������� ���
		if(stack_var.count() > 0)
		{
			node = stack_var.get(1);
		}

		//���� ������� ������� ����� ������ ����� �� ������ ����� � ��� ����� �� ���������
		//���������������� � ����� ������
		if(stack_var.count() > 1)
		{
			s4g_node* tmtm = stack_var.get(2);
			node->op3 = stack_var.get(2);	//����������� ������ ���, ��� � ������ ���� ����� ���� ��������� � ��������� �������, � �� ������ ��������� ��� ������ �������!!!
			tmpnode = node->op3;
		}

		for(int i=1;i<stack_var.count();i++)
		{
			s4g_node* tmtm = stack_var.get(i+1);
			tmpnode->op3 = stack_var.get(i+1);//����������� ������ ���, ��� � ������ ���� ����� ���� ��������� � ��������� �������, � �� ������ ��������� ��� ������ �������!!!
			tmpnode = tmpnode->op3;
		}

	return node;
}	

s4g_node* s4g_builder_syntax_tree::s4g_get_function_def_head()
{
	s4g_lexeme* lex_get_curr0(tmplexs);
	s4g_node* node = new s4g_node(_arg);
	s4g_node* tmpnode = node;
	s4g_node* tmpnode2 = 0;
	Array<String> arrarg;
		
		while(1)
		{
			lex_get_curr0(tmplexs);
				
				//���� ��� ������� ����������� ������
				if(tmplexs->type == sym_group && tmplexs->id == 1)
				{
					lex_get_next0(tmplexs);
					break;
				}
				//���� ��� ������� �� ����������� ������
				else if(!(tmplexs->type == sym_delimiter && tmplexs->id == 1))
				{
						//���� ��� ������� ���������������� �����
						if(tmplexs->type == word_user)
						{
								//��������� �������� �� ������������
								for(int i=0;i<arrarg.size();i++)
								{
									String str = arrarg[i];
										if(arrarg[i] == tmplexs->str)
										{
											this->status = -1;
											sprintf(this->error,"[%s]:%d - non unic argument [%s]",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr,tmplexs->str);
											return 0;
										}
								}

								//���� �� ��� �� ���� ������ ����
								if(node->value == 0)
								{
									tmpnode->value = gc->cr_val(t_string, tmplexs->str, curr_lexid);
								}
								else
								{
									tmpnode->op1 = new s4g_node(_arg, gc->cr_val(t_string, tmplexs->str, curr_lexid));
									tmpnode = tmpnode->op1;
								}

							arrarg.push_back(tmplexs->str);
							lex_get_next0(tmplexs);

								if((tmplexs->type == sym_delimiter && tmplexs->id == 1))
								{
									lex_get_next0(tmplexs);
								}
								else if(!(tmplexs->type == sym_group && tmplexs->id == 1))
								{
									this->status = -1;
									sprintf(this->error,"[%s]:%d - no separate arguments",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr);
									return 0;
								}
						}
						else if (tmplexs->type == marg)
						{
							tmpnode->op1 = new s4g_node(_marg);
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
							sprintf(this->error,"[%s]:%d - unresolved type for argument [%s]",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr,tmplexs->str);
							return 0;
						}
				}
				//����� � ��� ������� ������ ���
				else //error
				{
					this->status = -1;
					sprintf(this->error,"[%s]:%d - unresolved definition for argument [%s]",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr,tmplexs->str);
					return 0;
				}
		}
	return node;
}

s4g_node* s4g_builder_syntax_tree::s4g_get_table()
{
	s4g_lexeme* lex_get_curr0(tmplexs);
	s4g_node* node = new s4g_node(_create_table, gc->cr_val_null(curr_lexid));
	s4g_node* tmpnode = node;
	int type_last = -1;
	listread = false;
		while(1)
		{
			lex_get_curr0(tmplexs);
				if (type_last == 1 && !(tmplexs->type == sym_delimiter && tmplexs->id == 1) && !(tmplexs->type == sym_table_create && tmplexs->id == 1))
				{
					this->status = -1;
					sprintf(this->error, "[%s]:%d - expected delimiter arg but got [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
					return 0;
				}
				//���� ������ ��������� ������� }
				if(tmplexs->type == sym_table_create && tmplexs->id == 1)
				{
						if (type_last == 0)
						{
							this->status = -1;
							sprintf(this->error, "[%s]:%d - expected arg but got end definition of the table", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
							return 0;
						}
					lex_get_next0(tmplexs);
					break;
				}
				//���� �� �������
				else if(!(tmplexs->type == sym_delimiter && tmplexs->id == 1))
				{
					s4g_node* tmpnode2 = s4g_get_expr();
					lex_get_curr0(tmplexs);
					bst_cond_er(this);
						if(tmpnode2->type != _set)
						{
							tmpnode->op1 = new s4g_node(_add_in_table,0,tmpnode2,new s4g_node(_empty));
							tmpnode = tmpnode->op1->op2;
						}
						else
						{
							tmpnode2->type = _sett;
							tmpnode->op1 = tmpnode2;
							tmpnode->op2 = new s4g_node(_empty);
							tmpnode = tmpnode->op2;
						}
					type_last = 1;
				}
				else if((tmplexs->type == sym_delimiter && tmplexs->id == 1))
				{
						if (type_last == 0)
						{
							this->status = -1;
							sprintf(this->error, "[%s]:%d - expected double delimiter ','", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
							return 0;
						}
					lex_get_next0(tmplexs);
					type_last = 0;
				}
		}
	listread = true;
	return node;
}

s4g_node* s4g_builder_syntax_tree::s4g_get_ret_vals()
{
	s4g_lexeme* lex_get_curr0(tmplexs);
	s4g_node* node = new s4g_node(_return);
	s4g_node* tmpnode = node;
	s4g_node* tmpnode2 = 0;
		while(1)
		{
			lex_get_curr0(tmplexs);
				if(!(tmplexs->type == sym_delimiter && tmplexs->id == 1) && 
					!(tmplexs->type == sym_delimiter && tmplexs->id == 0) &&
					!(tmplexs->type == word_key && tmplexs->id == 2))
				{
					tmpnode2 = s4g_get_expr();
					bst_cond_er(this);
					tmpnode->op1 = tmpnode2;//new s4g_node(_expr,0,tmpnode2,new s4g_node(_empty));
					tmpnode->op2 = new s4g_node(_empty);
					tmpnode = tmpnode->op2;
					lex_get_curr0(tmplexs);
						if(tmplexs->type == sym_delimiter && tmplexs->id == 0)
						{
							break;
						}
						else
							lex_get_next0(tmplexs);
				}
				else if((tmplexs->type == sym_delimiter && tmplexs->id == 1))
				{
					lex_get_next0(tmplexs);
				}
				else 
					break;
		}
	return node;
}

s4g_node* s4g_builder_syntax_tree::s4g_get_arg_call_func()
{
	s4g_lexeme* lex_get_curr0(tmplexs);
	s4g_node* node = new s4g_node(_arg);
	s4g_node* tmpnode = node;
	s4g_node* tmpnode2 = 0;
	int type_last = -1;
	//int curr_num_lex = arr_lex->get_curr_num();
		while(1)
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
				else if(!(tmplexs->type == sym_delimiter && tmplexs->id == 1))
				{
					tmpnode2 = s4g_get_expr();
					bst_cond_er(this);
					tmpnode->op1 = tmpnode2;//new s4g_node(_expr,0,tmpnode2,new s4g_node(_empty));
					tmpnode->op2 = new s4g_node(_empty);
					tmpnode = tmpnode->op2;
					type_last = 1;
				}
				else if((tmplexs->type == sym_delimiter && tmplexs->id == 1))
				{
						if (type_last == 0)
						{
							this->status = -1;
							sprintf(this->error, "[%s]:%d - expected double delimiter ','", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
							return 0;
						}
					type_last = 0;
					lex_get_next0(tmplexs);
				}

		}
	return node;
}

s4g_node* s4g_builder_syntax_tree::s4g_get_expr()
{
	s4g_lexeme* lex_get_curr0(tmplexs);

		//���� ������� ����� - �������� �������
		if(tmplexs->type == sym_table_create && tmplexs->id == 0)
		{
			lex_get_next0(tmplexs);
			s4g_node* tmpnode = s4g_get_table();
			bst_cond_er(this);
			return tmpnode;
		}
	s4g_node* node = s4g_get_op();
	s4g_node* tmpnode = 0;
	s4g_node* tmpnode2 = 0;
	lex_get_curr0(tmplexs);

	if (node == 0)
		return 0;

		if (listread && tmplexs && tmplexs->type == sym_delimiter && tmplexs->id == 1)
		{
			//long curr_num_lex = arr_lex->get_curr_num();
			lex_get_next0(tmplexs);
			bst_cond_eof(tmplexs);

			tmpnode = node;
			listread = false;
				while ((tmpnode2 = s4g_get_op()) != 0)
				{
					tmpnode->op2 = tmpnode2;
					tmpnode = tmpnode->op2;

					lex_get_curr0(tmplexs);

						if (tmplexs && (tmplexs->type == sym_delimiter && tmplexs->id == 1))
							lex_get_next(tmplexs)
						else if (!tmplexs || !(tmplexs->type == sym_delimiter && tmplexs->id == 1))
						{
							listread = true;
						}
				}
			bst_cond_er(this);
			listread = true;
		}
		
		
		//���� ��� �������� ���� ���������� � ��������� ������� ����������
		if ((node->type == _var || node->type == _crvar) && tmplexs->type == sym_assign)
		{
			lex_get_next0(tmplexs);
				//���� ������ �������� �������
				if(tmplexs->type == sym_table_create && tmplexs->id == 0)
				{
					lex_get_next0(tmplexs);
					//������� ��� � �������� ���������� �������
					return new s4g_node(_set, 0, node, s4g_get_table());
				}
				//���� ������ �������� ����� "�������"
				else if(tmplexs->type == word_key && tmplexs->id == 1)
				{
					s4g_lexeme* sfunclex = tmplexs;
					s4g_node* name_func = node;

					lex_get_next0(tmplexs);
					bst_cond_eof(tmplexs);
						//���� ������� ��� ����������� ������
						if(tmplexs->type == sym_group && tmplexs->id == 0)
							lex_get_next(tmplexs)
						else //error
						{
							status = -1;
							sprintf(this->error,"[%s]:%d - expected [%s] but got [%s]",this->arr_lex->ArrFiles[tmplexs->fileid],tmplexs->numstr,s4g_key_syms_group[0],tmplexs->str);
							return 0;
						}

					s4g_node* head_func = s4g_get_function_def_head();
					bst_cond_er(this);
					lex_get_curr0(tmplexs);
					s4g_node* extern_data = 0;
					s4g_node* tmped = 0;
					if (tmplexs->type == word_key && tmplexs->id == 4)
					{
						int type_last = -1;
						while (true)
						{
							lex_get_next0(tmplexs);
							s4g_node* tmpop = 0;
							if (type_last == 1 && !(tmplexs->type == sym_delimiter && tmplexs->id == 1) && !(tmplexs->type == sym_delimiter && tmplexs->id == 0))
							{
								this->status = -1;
								sprintf(this->error, "[%s]:%d - expected delimiter arg but got [%s]", this->arr_lex->ArrFiles[tmplexs->fileid], tmplexs->numstr, tmplexs->str);
								return 0;
							}
							else if ((type_last == 0 || type_last == -1) && tmplexs->type == word_user)
							{
								tmpop = new s4g_node(_var, gc->cr_val(t_string, tmplexs->str, curr_lexid));
								type_last = 1;
								if (extern_data)
								{
									tmped->op1 = tmpop;
									tmped = tmped->op1;
								}
								else
								{
									extern_data = tmpop;
									tmped = extern_data;
								}
							}
							else if (type_last == 1 && tmplexs->type == sym_delimiter && tmplexs->id == 1)
							{
								type_last = 0;
							}
							else if (tmplexs->type == sym_delimiter && tmplexs->id == 0)
							{
								lex_get_next0(tmplexs);
								break;
							}
							//extern_data
						}
					}
					//arr_lex->get_prev();
					this->overend--;
					s4g_node* body_func = s4g_gen_statement();
					bst_cond_er(this);
					lex_get_curr0(tmplexs);
					bst_cond_eof(tmplexs);
						//���� ������� ������� �� �������� ���������� �������� end
						if(!(arr_lex->get_curr_num() < arr_lex->get_count() && tmplexs->type == word_key && tmplexs->id == 2)) //error
						{
							status = -1;
							sprintf(this->error,"[%s]:%d - not found end for funcion",this->arr_lex->ArrFiles[sfunclex->fileid],sfunclex->numstr);
							return 0;
						}
					lex_get_next0(tmplexs);
					s4g_node* nfunc = new s4g_node(_function, 0, head_func, body_func, extern_data);
					return new s4g_node(_set, 0, name_func, nfunc);
				}
			return new s4g_node(_set,0,node,s4g_get_expr());
		}
	return node;
}

s4g_node* s4g_builder_syntax_tree::s4g_gen_tree()
{
	status = 0;error[0]=0;
	s4g_node* tmpnode = 0;
	arr_lex->set_curr_num(0);
	tmpnode = new s4g_node(s4g_type_op::_begin,0,s4g_gen_statement());

	return tmpnode;
}
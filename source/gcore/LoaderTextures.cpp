
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#include "LoaderTextures.h"

LoaderTextures::LoaderTextures()
{
	CurrFirstFree = -1;
}

LoaderTextures::~LoaderTextures()
{
	for (int i = 0; i < ArrTextures.size(); i++)
	{
		mem_delete(ArrTextures[i]);
	}
	ArrTextures.clear();

	for (int i = 0; i < Arr.size(); i++)
	{
		mem_delete(Arr[i]);
	}
	Arr.clear();
}

bool LoaderTextures::FileExists(const char* name)
{
	char tmppath[SXGC_LOADTEX_MAX_SIZE_FULLPATH];
	char tmp_path[SXGC_LOADTEX_MAX_SIZE_DIR];
	char tmp_name[SXGC_LOADTEX_MAX_SIZE_NAME];
	
	bool IsTruePath = false;
	//�������� ��� �������� � �����
	for (int i = 0; i<strlen(name); i++)
	{
		if (name[i] == '_')
		{
			memcpy(tmp_path, name, sizeof(char)*i);
			tmp_path[i] = 0;
			sprintf(tmp_name, "%s", name + i + 1);
			IsTruePath = true;
			break;
		}
	}

	if (!IsTruePath)
	{
		LibReport(REPORT_MSG_LEVEL_ERROR, "%s - wrong texture name [%s]!!!", GEN_MSG_LOCATION, name);
		return false;
	}

	sprintf(tmppath, "%s%s\\%s", Core_RStringGet(G_RI_STRING_PATH_GS_SHADERS), tmp_path, name);
	return FileExistsFile(tmppath);
}

void LoaderTextures::ClearLoaded()
{
	int tmpcountdel = 0;
	for (int i = 0; i < Arr.size(); ++i)
	{
		for (int k = 0; k < Arr[i]->ArrTex.size(); ++k)
		{
			if (Arr[i]->ArrTex[k]->type == LOAD_TEXTURE_TYPE_LOAD)
			{
				mem_release_del(ArrTextures[Arr[i]->ArrTex[k]->id]->tex);
				++tmpcountdel;
				if (CurrFirstFree > Arr[i]->ArrTex[k]->id)
					CurrFirstFree = Arr[i]->ArrTex[k]->id;

				mem_delete(Arr[i]->ArrTex[k]);
				Arr[i]->ArrTex.erase(k);
				--k;
			}
		}
	}

	int qwert = 0;
}

void LoaderTextures::Delete(ID id)
{
	if (!(id < ArrTextures.size() && id >= 0))
		return;

	if (ArrTextures[id]->tex == 0)
		return;

	mem_release_del(ArrTextures[id]->tex);

	if (CurrFirstFree > id)
		CurrFirstFree = id;

	TLPath* tmpp = Arr[ArrTextures[id]->IDDir];

	for (int i = 0; i < tmpp->ArrTex.size(); ++i)
	{
		if (tmpp->ArrTex[i] && tmpp->ArrTex[i]->id == id)
		{
			mem_delete(tmpp->ArrTex[i]);
			tmpp->ArrTex.erase(i);
			break;
		}
	}
}

ID LoaderTextures::AddName(const char* name, LOAD_TEXTURE_TYPE type, ID* iddir, ID* idname)
{
	char tmp_path[SXGC_LOADTEX_MAX_SIZE_DIR];//�����
	char tmp_name[SXGC_LOADTEX_MAX_SIZE_NAME];//���� ��� ������� � �����������
	ID id = -1;
	bool IsTruePath = false;
		//�������� ��� �������� � �����
		for(int i=0;i<strlen(name);i++)
		{
				if(name[i] == '_')
				{
					memcpy(tmp_path,name,sizeof(char)*i);
					tmp_path[i] = 0;
					sprintf(tmp_name,"%s",name+i+1);
					IsTruePath = true;
					break;
				}
		}

		if(!IsTruePath)
		{
			LibReport(REPORT_MSG_LEVEL_ERROR, "%s - wrong texture name [%s]!!!", GEN_MSG_LOCATION, name);
		}

	int tmpkey = -1;	//���������� � ������� ������ ���� �� ������� � ������� ����������
	
	for (int i = 0; i<Arr.size(); i++)
	{
		if(strcmp(Arr[i]->Path.c_str(),tmp_path) == 0)
		{
			tmpkey = i;
			break;
		}
	}

		//���� �� �� ����� ���������� ������ ���� �������� ...
		if(tmpkey == -1)
		{
			tmpkey = Arr.size();
			Arr.push_back(new TLPath());
			Arr[tmpkey]->Path = tmp_path;
		}

	bool isunic = true;
	
		//��������� �������� �� ��� ��� ��������
		for(int i=0;i<Arr[tmpkey]->ArrTex.size();i++)
		{
				if(strcmp(Arr[tmpkey]->ArrTex[i]->name.c_str(),tmp_name) == 0)
				{
					isunic = false;
					id = Arr[tmpkey]->ArrTex[i]->id;
					if (idname)
						*idname = i;
					break;
				}
		}

		if (iddir)
			*iddir = tmpkey;

		//���� ���������� �� ����������
		if(isunic)
		{
			if (CurrFirstFree + 1 == ArrTextures.size())
			{
				ArrTextures.push_back(new TexAndName());
				CurrFirstFree = id = ArrTextures.size() - 1;
			}
			else
			{
				if (CurrFirstFree < 0 || ArrTextures[CurrFirstFree] != 0)
				{
					if (CurrFirstFree < 0)
						CurrFirstFree = 0;

					for (int i = CurrFirstFree; i < ArrTextures.size(); ++i)
					{
						if (ArrTextures[i] == 0)
						{
							CurrFirstFree = i;
							break;
						}
					}
				}

				id = CurrFirstFree;
				++CurrFirstFree;
			}

			//���� ��� �������� ���������������
			if (type == LOAD_TEXTURE_TYPE_SELF)
				type = LOAD_TEXTURE_TYPE_LOAD;

			Arr[tmpkey]->ArrTex.push_back(new TLPath::TLTex(id, tmp_name, type));

			if (idname)
				*idname = Arr[tmpkey]->ArrTex.size() - 1;

			ArrTextures[id]->name = name;
			ArrTextures[id]->IDDir = tmpkey;
			
			if (type != LOAD_TEXTURE_TYPE_CUSTOM)
				ArrIDsLoad.push_back(id);
		}

	return id;
}

ID LoaderTextures::GetID(const char* name)
{
	char tmp_path[SXGC_LOADTEX_MAX_SIZE_DIR];//�����
	char tmp_name[SXGC_LOADTEX_MAX_SIZE_NAME];//���� ��� �������� � �����������
	ID id = -1;
		//�������� ��� �������� � �����
		for(int i=0;i<strlen(name);i++)
		{
				if(name[i] == '_')
				{
					memcpy(tmp_path,name,sizeof(char)*i);
					tmp_path[i] = 0;
					sprintf(tmp_name,"%s",name+i+1);
					break;
				}
		}

		for (int i = 0; i<Arr.size(); i++)
		{
				if(strcmp(Arr[i]->Path.c_str(),tmp_path) == 0)
				{
						for(int k=0;k<Arr[i]->ArrTex.size();k++)
						{
								if(strcmp(Arr[i]->ArrTex[k]->name.c_str(),tmp_name) == 0)
								{
									id = Arr[i]->ArrTex[k]->id;
									i = Arr.size();
									break;
								}
						}
				}
		}
	return id;
}

void LoaderTextures::GetName(ID id, char* name)
{
		if(id < ArrTextures.size())
		{
			String tmpname = ArrTextures[id]->name;
			sprintf(name,"%s",tmpname.c_str());
		}
}

ID LoaderTextures::Create(const char* name, IDirect3DTexture9* tex)
{
	ID tmpkey, tmpKeyName;
	ID id = this->AddName(name, LOAD_TEXTURE_TYPE_CUSTOM, &tmpkey, &tmpKeyName);
	ArrTextures[id]->tex = tex;
	return id;
}

void LoaderTextures::Update(ID id)
{
	if(id < ArrTextures.size())
	{
		Update(ArrTextures[id]->name.c_str(), LOAD_TEXTURE_TYPE_SELF);
	}
}

ID LoaderTextures::Update(const char* name, LOAD_TEXTURE_TYPE type)
{
	ID tmpkey, tmpKeyName;
	ID id = AddName(name, type, &tmpkey, &tmpKeyName);

	//LibReport(0,"update texture [%s] ...",name);

	char tmpPath[SXGC_LOADTEX_MAX_SIZE_FULLPATH];
	sprintf(tmpPath, "%s%s%s%s%s%s", Core_RStringGet(G_RI_STRING_PATH_GS_TEXTURES), Arr[tmpkey]->Path.c_str(), "\\", Arr[tmpkey]->Path.c_str(), "_", Arr[tmpkey]->ArrTex[tmpKeyName]->name.c_str());
	IDirect3DTexture9* tex=0;
		if(FAILED(D3DXCreateTextureFromFileEx(
			g_pDXDevice,
											tmpPath,
											D3DX_DEFAULT,
											D3DX_DEFAULT,
											SXGC_LOADTEX_COUNT_MIPMAP,
											0,
											SXGC_LOADTEX_FORMAT_TEX,
											D3DPOOL_MANAGED, 
											D3DX_FILTER_BOX, 
											D3DX_FILTER_BOX,  0, 0, 0, &tex
											)
			)
		)
		{
			LibReport(REPORT_MSG_LEVEL_ERROR, "%s - not found texture [%s]", GEN_MSG_LOCATION, tmpPath);
		}
		else
		{
			ArrTextures[Arr[tmpkey]->ArrTex[tmpKeyName]->id]->tex = tex;
			//LibReport(0, "is ok\n");
		}
	
	return id;
}

void LoaderTextures::LoadTextures()
{
	if (ArrIDsLoad.size() <= 0)
		return;
	LibReport(REPORT_MSG_LEVEL_NOTICE, "load textures ...\n");

	char tmpPath[SXGC_LOADTEX_MAX_SIZE_FULLPATH];
	ID tmpiddir;
	int iCountLoaded = 0;
	for (int i = 0; i<ArrIDsLoad.size(); i++)
	{
		tmpiddir = ArrTextures[ArrIDsLoad[i]]->IDDir;
		TLPath* tmpdir = Arr[tmpiddir];
		sprintf(tmpPath, "%s%s%s%s", Core_RStringGet(G_RI_STRING_PATH_GS_TEXTURES), Arr[tmpiddir]->Path.c_str(), "\\", ArrTextures[ArrIDsLoad[i]]->name.c_str());
		IDirect3DTexture9* tex = 0;
		
		if (FAILED(D3DXCreateTextureFromFileEx(
			g_pDXDevice,
			tmpPath,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			SXGC_LOADTEX_COUNT_MIPMAP,
			0,
			SXGC_LOADTEX_FORMAT_TEX,
			D3DPOOL_MANAGED,
			D3DX_FILTER_BOX,
			D3DX_FILTER_BOX, 0, 0, 0, &tex
			)))
		{
			ArrTextures[ArrIDsLoad[i]]->tex = 0;
			LibReport(REPORT_MSG_LEVEL_WARNING, "  not found [%s]\n", ArrTextures[ArrIDsLoad[i]]->name.c_str());
		}
		else
		{
			ArrTextures[ArrIDsLoad[i]]->tex = tex;
			LibReport(REPORT_MSG_LEVEL_NOTICE, "  texture id [%d], [%s]\n", ArrIDsLoad[i], ArrTextures[ArrIDsLoad[i]]->name.c_str());
			++iCountLoaded;
		}
	}

	ArrIDsLoad.clear();
	LibReport(REPORT_MSG_LEVEL_NOTICE, "all loaded textures [%d]\n", ArrTextures.size());
}

IDirect3DTexture9* LoaderTextures::GetTexture(ID id)
{
		if(id < ArrTextures.size())
		{
			/*IDirect3DTexture9* tex = ArrTextures[id]->tex;
			if (tex == 0)
				int qwert = 0;*/
			return ArrTextures[id]->tex;
		}
		else 
			return 0;
}
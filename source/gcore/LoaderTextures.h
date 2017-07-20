
#ifndef LOADER_TEXTURES_H
#define LOADER_TEXTURES_H

#pragma once

class LoaderTextures
{
public:
	LoaderTextures();
	~LoaderTextures();

	bool FileExists(const char* name);

	void ClearLoaded();

	void Delete(ID id);	//������� �������� id

	ID AddName(const char* name, LoadTexType type, ID* iddir = 0, ID* idname = 0);	//��������� ��� ��������, ������ �������� �� ��� ID (��������� � �������)
	ID GetID(const char* name);		//�������� id �� �����
	void GetName(ID id, char* name);//�������� ��� �� id

	ID Create(const char* name, IDirect3DTexture9* tex);	//������� ����� ��� �������� tex
	ID Update(const char* name, LoadTexType type);			//������������� �������� name
	void Update(ID id);

	void LoadTextures();	//�������� ���� ������� ������������ � �������

	IDirect3DTexture9* GetTexture(ID id);//�������� �������� �� id

	inline void SetStdPath(const char* path){ StdPath = path; }
	inline void GetStdPath(char* path){ if (path)strcpy(path, StdPath.c_str()); }
private:

	//��������� ����������� ����� � ��� �������� � ���, � ������ ���� id ��� �������
	struct TLPath
	{
		TLPath(){}
		~TLPath()
		{
			for (int i = 0; i < ArrTex.size(); ++i)
			{
				mem_delete(ArrTex[i]);
			}
		}

		String Path;	//��� �����

		struct TLTex
		{
			TLTex(){ id = -1; type = LoadTexType::ltt_load; }
			TLTex(ID _id, const char* _name, LoadTexType _type){ id = _id; name = _name; type = _type; }
			
			ID id;
			String name;
			LoadTexType type;
		};
		
		Array<TLTex*> ArrTex;
	};

	struct TexAndName
	{
		TexAndName(){ tex = 0; IDDir = -1; }
		~TexAndName(){ mem_release(tex); }
		String name;
		IDirect3DTexture9* tex;
		ID IDDir;
		
	};

	String StdPath;
	Array<TLPath*> Arr;
	int CurrFirstFree;

	Array<TexAndName*> ArrTextures;
	Array<ID> ArrIDsLoad;
};

#endif
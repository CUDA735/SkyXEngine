
#ifndef LOADER_TEXTURES_H
#define LOADER_TEXTURES_H

#pragma once
//��������� ����������� ����� � ��� �������� � ���, � ������ ���� id ���� �������
struct TLPath
{
	TLPath()
	{
		Path[0] = 0;
	}
	
	char Path[256];//��� �����
	Array<ID> ArrID;		//�������������
	Array<char*> ArrNames;	//������ � ������� ������� ������� ��������� � ������ �����
};

class LoaderTextures
{
public:
	LoaderTextures();
	~LoaderTextures();

	ID AddName(const char* name);	//��������� ��� ��������, ������ �������� �� ��� ID (��������� � �������)
	ID GetID(const char* name);		//�������� id �� �����
	void GetName(ID id, char* name);	//�������� ��� �� id

	ID Create(const char* name, IDirect3DTexture9* tex);	//������� ����� ��� �������� tex
	ID Update(const char* name);		//������������� �������� name (��������� � �������)
	void Update(ID id);

	void LoadTextures();	//�������� ���� ������� ������������ � �������

	IDirect3DTexture9* GetTexture(ID id);//�������� �������� �� id

	inline void SetStdPath(const char* path){ strcpy(StdPath, path); }
	inline void GetStdPath(char* path){ if (path)strcpy(path, StdPath); }
//private:
	char StdPath[1024];
	TLPath Arr[256];
	int CountArr;
	int CountIDs;
	int CountIDsOld;

	Array<char*> ArrNames;
	Array<IDirect3DTexture9*> ArrTextures;
};

#endif
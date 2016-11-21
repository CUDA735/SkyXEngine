
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
	Array<DWORD> ArrID;		//�������������
	Array<char*> ArrNames;	//������ � ������� ������� ������� ��������� � ������ �����
};

class LoaderTextures
{
public:
	LoaderTextures();
	~LoaderTextures();

	DWORD AddName(const char* name);	//��������� ��� ��������, ������ �������� �� ��� ID (��������� � �������)
	DWORD GetID(const char* name);		//�������� id �� �����
	void GetName(DWORD id,char* name);	//�������� ��� �� id

	DWORD Create(const char* name,IDirect3DTexture9* tex);	//������� ����� ��� �������� tex
	DWORD Update(const char* name);		//������������� �������� name (��������� � �������)
	void Update(DWORD id);

	void LoadTextures();	//�������� ���� ������� ������������ � �������

	IDirect3DTexture9* GetTexture(DWORD id);//�������� �������� �� id

	inline void SetStdPath(const char* path){ strcpy(StdPath, path); }
	inline void GetStdPath(char* path){ if (path)strcpy(path, StdPath); }
//private:
	char StdPath[1024];
	TLPath Arr[256];
	DWORD CountArr;
	DWORD CountIDs;
	DWORD CountIDsOld;

	Array<char*> ArrNames;
	Array<IDirect3DTexture9*> ArrTextures;
};

#endif
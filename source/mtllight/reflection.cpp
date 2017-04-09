
#include <mtllight\\reflection.h>

Reflection::Reflection()
{
	IsComNow = true;
	SurfaceReflect = 0;
	TextureReflect = 0;
	TextureCubeReflect = 0;
	SurfaceZBuffer = 0;
	BackBuffer = 0;
	LastSurfaceZBuffer = 0;
	ZNear = 0.0f;
	CountUpdate = 0;

	for (int i = 0; i < 6; ++i)
	{
		//IDArr[i] = -1;
		ReflectFrustum[i] = 0;
		CubeReflectSurface[i] = 0;
	}
}

Reflection::~Reflection()
{
	for (int i = 0; i < 6; ++i)
	{
		mem_release_del(ReflectFrustum[i]);
	}

	mem_release_del(BackBuffer);
	mem_release_del(SurfaceZBuffer);
	mem_release_del(LastSurfaceZBuffer);
	mem_release_del(TextureReflect);
	mem_release_del(SurfaceReflect);

	for (int i = 0; i < 6; i++)
	{
		mem_release_del(CubeReflectSurface[i]);
	}

	mem_release_del(TextureCubeReflect);
}

void Reflection::SetIDArr(ID id, int cube, ID idarr)
{
	if (!(cube >= 0 && cube < 6))
		return;

	if (id >= IDArr.size())
	{
		ID* tmparr = new ID[6];
		for (int i = 0; i < 6; ++i)
			tmparr[i] = -1;
		IDArr[id] = tmparr;
	}

	IDArr[id][cube] = idarr;
}

inline int Reflection::GetCountIDArrs()
{
	return IDArr.size();
}

inline ID Reflection::GetIDArr(ID id, int cube)
{
	if (!(cube >= 0 && cube < 6))
		return -1;

	if (id < 0 || !(cube >= 0 && cube < 6) || !(id < IDArr.size()))
		return -2;

	return IDArr[id][cube];
}

void Reflection::OnLostDevice()
{
	mem_release_del(TextureReflect);
	mem_release_del(TextureCubeReflect);
	mem_release_del(SurfaceZBuffer);

	mem_release_del(SurfaceReflect);

	mem_release_del(CubeReflectSurface[0]);
	mem_release_del(CubeReflectSurface[1]);
	mem_release_del(CubeReflectSurface[2]);
	mem_release_del(CubeReflectSurface[3]);
	mem_release_del(CubeReflectSurface[4]);
	mem_release_del(CubeReflectSurface[5]);
}

void Reflection::OnResetDevice()
{
	if (TypeRef == MtlTypeReflect::mtr_plane)
	{
		D3DXCreateTexture(MLSet::DXDevice, MLSet::SizeTexReflection.x, MLSet::SizeTexReflection.y, 0, D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &TextureReflect);
		MLSet::DXDevice->CreateDepthStencilSurface(MLSet::SizeTexReflection.x, MLSet::SizeTexReflection.y, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, TRUE, &SurfaceZBuffer, NULL);
	}
	else if (TypeRef == MtlTypeReflect::mtr_cube_static || TypeRef == MtlTypeReflect::mtr_cube_dynamic)
	{
		D3DXCreateTexture(MLSet::DXDevice, MLSet::SizeTexReflection.x, MLSet::SizeTexReflection.x, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &TextureReflect);
		D3DXCreateCubeTexture(MLSet::DXDevice, MLSet::SizeTexReflection.x, 0, D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &TextureCubeReflect);
		//MLSet::DXDevice->CreateCubeTexture(MLSet::SizeTexReflection.x, 0, D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &TextureCubeReflect, NULL);
		MLSet::DXDevice->CreateDepthStencilSurface(MLSet::SizeTexReflection.x, MLSet::SizeTexReflection.x, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, TRUE, &SurfaceZBuffer, NULL);
		//TextureCubeReflect->SetAutoGenFilterType(D3DTEXF_LINEAR);
	}

	CountUpdate = 0;
}

void Reflection::Init(MtlTypeReflect howref)
{
	TypeRef = howref;
	if (TypeRef == MtlTypeReflect::mtr_plane)
	{
		if (!ReflectFrustum[0])
			ReflectFrustum[0] = SGCore_CrFrustum();

		if (!TextureReflect)
			D3DXCreateTexture(MLSet::DXDevice, MLSet::SizeTexReflection.x, MLSet::SizeTexReflection.y, 0, D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &TextureReflect);

		if (!SurfaceZBuffer)
			MLSet::DXDevice->CreateDepthStencilSurface(MLSet::SizeTexReflection.x, MLSet::SizeTexReflection.y, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, TRUE, &SurfaceZBuffer, NULL);
	
	}
	else if (TypeRef == MtlTypeReflect::mtr_cube_static || TypeRef == MtlTypeReflect::mtr_cube_dynamic)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (!ReflectFrustum[i])
				ReflectFrustum[i] = SGCore_CrFrustum();
		}

		D3DXCreateTexture(MLSet::DXDevice, MLSet::SizeTexReflection.x, MLSet::SizeTexReflection.x, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &TextureReflect);

		if (!TextureCubeReflect)
			D3DXCreateCubeTexture(MLSet::DXDevice, MLSet::SizeTexReflection.x, 0, D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP, D3DFMT_R5G6B5, D3DPOOL_DEFAULT, &TextureCubeReflect);
			//MLSet::DXDevice->CreateCubeTexture(MLSet::SizeTexReflection.x, 0, D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &TextureCubeReflect, NULL);
		
		if (!SurfaceZBuffer)
			MLSet::DXDevice->CreateDepthStencilSurface(MLSet::SizeTexReflection.x, MLSet::SizeTexReflection.x, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, TRUE, &SurfaceZBuffer, NULL);
	
	}
	else
	{

	}
	

	CubeReflectSurface[0] = 0;
	CubeReflectSurface[1] = 0;
	CubeReflectSurface[2] = 0;
	CubeReflectSurface[3] = 0;
	CubeReflectSurface[4] = 0;
	CubeReflectSurface[5] = 0;

	CountUpdate = 0;
}

void Reflection::PreRenderRefPlane(float4x4* world)
{
	float4x4 viewmat;
	Core_RMatrixGet(G_RI_MATRIX_VIEW, &viewmat);

	float4x4 tmpworld;
	tmpworld = *world;
	tmpworld._41 = tmpworld._42 = tmpworld._43 = tmpworld._14 = tmpworld._24 = tmpworld._34 = 0;
	tmpworld._44 = 1.f;

	D3DXMATRIX matReflect, matView;
	/*D3DXPLANE tmpplane;
	D3DXPlaneTransform(&tmpplane, &Plane, &((D3DXMATRIX)tmpworld));*/
	D3DXMatrixReflect(&matReflect, &Plane);
	
	viewmat = float4x4(matReflect) * viewmat;
	/**/
	

	float determ = 0;
	float4x4 invviewmat = SMMatrixInverse(&determ, viewmat);
	float3 tmppos = float3(viewmat._41, viewmat._42-0.1, viewmat._43);
	float nearp = SMVector3Distance(Position, tmppos);
	//MLSet::RefMProjPlane = SMMatrixPerspectiveFovLH(MLSet::ProjFov, MLSet::ProjRatio, nearp, MTl_REF_PROJ_FAR);

	


	//float3 pointplane = (GData::ConstCurrCamPos + ((GData::NearFar.y - 1.f) * GData::ConstCurrCamDir));
	//Position.y -= tmppos.y;
	D3DXPlaneFromPointNormal(
		&Plane2,
		&((D3DXVECTOR3)Position),
		&D3DXVECTOR3(0,1,0));

	tmpworld = SMMatrixTranslation(Position);
	float4x4 wmat = (viewmat*MLSet::RefMProjPlane);

	//float determ = 0;
	wmat = SMMatrixTranspose(wmat);
	wmat = SMMatrixInverse(&determ, wmat);

	D3DXPlaneTransform(&Plane2, &Plane2, &(wmat.operator D3DXMATRIX()));

	MLSet::DXDevice->SetRenderState(D3DRS_CLIPPLANEENABLE, FALSE);
	MLSet::DXDevice->SetClipPlane(1, Plane2);
	MLSet::DXDevice->SetRenderState(D3DRS_CLIPPLANEENABLE, D3DCLIPPLANE1);

	viewmat._12 = -viewmat._12;
	viewmat._22 = -viewmat._22;
	viewmat._32 = -viewmat._32;
	viewmat._42 = -viewmat._42;

	Core_RMatrixGet(G_RI_MATRIX_VIEW, &OldMatView);
	Core_RMatrixGet(G_RI_MATRIX_PROJECTION, &OldMatProj);
	Core_RMatrixGet(G_RI_MATRIX_VIEWPROJ, &OldMatViewProj);

	Core_RMatrixSet(G_RI_MATRIX_VIEW, &viewmat);
	Core_RMatrixSet(G_RI_MATRIX_PROJECTION, &MLSet::RefMProjPlane);
	Core_RMatrixSet(G_RI_MATRIX_VIEWPROJ, &(viewmat * MLSet::RefMProjPlane));

	ReflectFrustum[0]->Update(&viewmat, &(MLSet::RefMProjPlane));

	MLSet::DXDevice->GetRenderTarget(0, &BackBuffer);

	mem_release_del(SurfaceReflect);
	TextureReflect->GetSurfaceLevel(0, &SurfaceReflect);
	MLSet::DXDevice->SetRenderTarget(0, SurfaceReflect);
	MLSet::DXDevice->GetDepthStencilSurface(&LastSurfaceZBuffer);
	MLSet::DXDevice->SetDepthStencilSurface(SurfaceZBuffer);
	MLSet::DXDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0L);
}

void Reflection::PostRenderRefPlane()
{
	Core_RMatrixSet(G_RI_MATRIX_VIEW, &OldMatView);
	Core_RMatrixSet(G_RI_MATRIX_PROJECTION, &OldMatProj);
	Core_RMatrixSet(G_RI_MATRIX_VIEWPROJ, &OldMatViewProj);

	MLSet::DXDevice->SetRenderState(D3DRS_CLIPPLANEENABLE, FALSE);

	MLSet::DXDevice->SetRenderTarget(0, BackBuffer);
	MLSet::DXDevice->SetDepthStencilSurface(LastSurfaceZBuffer);

	if (GetAsyncKeyState(VK_NUMPAD9))
	{
		char tmpstr[256];
		sprintf(tmpstr, "C:\\1\\reflectionreflection.png");
		D3DXSaveSurfaceToFile(tmpstr, D3DXIFF_JPG, SurfaceReflect, NULL, 0);
	}

	mem_release_del(BackBuffer);
	mem_release_del(LastSurfaceZBuffer);
}

inline IDirect3DTexture9* Reflection::GetRefPlaneTex()
{
	return TextureReflect;
}

////////////////////////

void Reflection::SetMinMax(float3_t* min, float3_t* max)
{
	//���� ����� ������� ���������� �� ������ ������ ���� �������� ���������, ���� ��� ���� �����������
	if (PosMax.x != max->x || PosMax.y != max->y || PosMax.z != max->z || PosMin.x != min->x || PosMin.y != min->y || PosMin.z != min->z)
		CountUpdate = 0;

	PosMax = *max;
	PosMin = *min;
}

void Reflection::BeginRenderRefCube()
{
	Core_RMatrixGet(G_RI_MATRIX_VIEW, &OldMatView);
	Core_RMatrixGet(G_RI_MATRIX_PROJECTION, &OldMatProj);
	Core_RMatrixGet(G_RI_MATRIX_VIEWPROJ, &OldMatViewProj);

	MLSet::DXDevice->GetRenderTarget(0, &BackBuffer);
	MLSet::DXDevice->GetDepthStencilSurface(&LastSurfaceZBuffer);
	MLSet::DXDevice->SetDepthStencilSurface(SurfaceZBuffer);
}

void Reflection::PreRenderRefCube(int cube, float4x4* world)
{
	MLSet::DXDevice->SetTransform(D3DTS_PROJECTION, &((D3DXMATRIX)MLSet::RefMProjCube));

	PositionReflect = SMVector3Transform(Position, *world);

	MatrixView = SMMatrixLookAtLH(
		PositionReflect,
		((MLSet::OrientedCube[cube] + PositionReflect)),
		MLSet::UpVectorsCube[cube]);

	MLSet::DXDevice->SetTransform(D3DTS_VIEW, &MatrixView.operator D3DXMATRIX());

	MLSet::DXDevice->SetTransform(D3DTS_WORLD1, &((D3DXMATRIX)(MatrixView * MLSet::RefMProjCube)));

	ReflectFrustum[cube]->Update(&float4x4(MatrixView), &MLSet::RefMProjCube);

	mem_release_del(SurfaceReflect);
	TextureReflect->GetSurfaceLevel(0, &SurfaceReflect);
	MLSet::DXDevice->SetRenderTarget(0, SurfaceReflect);

	MLSet::DXDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1, 0);
}

void Reflection::PostRenderRefCube(int cube)
{
	LPDIRECT3DSURFACE9 BackBuf;

	mem_release_del(CubeReflectSurface[cube]);

	TextureCubeReflect->GetCubeMapSurface((D3DCUBEMAP_FACES)cube, 0, &CubeReflectSurface[cube]);
	MLSet::DXDevice->SetRenderTarget(0, CubeReflectSurface[cube]);
	MLSet::DXDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 255, 255, 255), 1, 0);

	SGCore_ShaderBind(ShaderType::st_vertex, MLSet::IDsShaders::VS::ScreenOut);
	SGCore_ShaderBind(ShaderType::st_pixel, MLSet::IDsShaders::PS::ScreenOut);

	MLSet::DXDevice->SetTexture(0, TextureReflect);
	SGCore_ScreenQuadDraw();

	SGCore_ShaderUnBind();


	/*if(GetAsyncKeyState(VK_NUMPAD5))
	{
		char tmpstr[1024];
		sprintf(tmpstr,"C:\\1\\reflectioncube_%d.bmp",cube);
		D3DXSaveSurfaceToFile(tmpstr, D3DXIFF_PNG, CubeReflectSurface[cube], NULL, 0);
	}*/
	mem_release(SurfaceReflect);
	mem_release_del(CubeReflectSurface[cube]);
}

void Reflection::EndRenderRefCube(float3_t* viewpos)
{
	Core_RMatrixSet(G_RI_MATRIX_VIEW, &OldMatView);
	Core_RMatrixSet(G_RI_MATRIX_PROJECTION, &OldMatProj);
	Core_RMatrixSet(G_RI_MATRIX_VIEWPROJ, &OldMatViewProj);

	MLSet::DXDevice->SetRenderTarget(0, BackBuffer);
	MLSet::DXDevice->SetDepthStencilSurface(LastSurfaceZBuffer);
	mem_release_del(LastSurfaceZBuffer);
	mem_release_del(BackBuffer);

	UpdateCountUpdate(viewpos);
}

bool Reflection::UpdateCountUpdate(float3_t* viewpos)
{
	if (!viewpos)
		return false;

	if (TypeRef == MtlTypeReflect::mtr_cube_static)
	{
		if (CountUpdate < MTL_REF_UPDATE_MAX_COUNT_FOR_STATIC)
		{
			++(CountUpdate);
			return true;
		}
		else
			return false;
	}

	float dist = SMVector3Distance(PositionReflect, (*viewpos)) - SMVector3Length((PosMax - PosMin) *0.5f);
	if (dist < MTL_REF_UPDATE_L0_DIST)
		CountUpdate = -1;
	else if (dist < MTL_REF_UPDATE_L1_DIST && dist > MTL_REF_UPDATE_L0_DIST)
	{
		if (CountUpdate > 1)
			CountUpdate = -1;
	}
	else if (dist < MTL_REF_UPDATE_L2_DIST && dist > MTL_REF_UPDATE_L1_DIST)
	{
		if (CountUpdate > 2)
			CountUpdate = -1;
	}
	else if (dist > MTL_REF_UPDATE_L2_DIST)
	{
		CountUpdate = 4;
	}

	++CountUpdate;

	return (CountUpdate == 0);
}

bool Reflection::AllowedRender()
{
	if (TypeRef == MtlTypeReflect::mtr_cube_static)
	{
		if (CountUpdate <= MTL_REF_UPDATE_MAX_COUNT_FOR_STATIC)
		{
			++(CountUpdate);
			return true;
		}
		else
			return false;
	}

	return (CountUpdate == 0);
}

void Reflection::NullingCountUpdate()
{
	CountUpdate = 0;
}

inline IDirect3DCubeTexture9* Reflection::GetRefCubeTex()
{
	return TextureCubeReflect;
}

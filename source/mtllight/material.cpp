
#include <mtllight\\material.h>
#include <mtllight\\reflection.cpp>

Materials::Materials()
{
	CurrFirstFree = -1;
	CountTimeDelta = 0;
	IsForceblyAlphaTest = false;
	SGCore_ShaderLoad(ShaderType::st_vertex, "mtrlgeom_base.vs", "mtrlgeom_base", ShaderCheckDouble::scd_path);
	SGCore_ShaderLoad(ShaderType::st_pixel, "mtrlgeom_base.ps", "mtrlgeom_base", ShaderCheckDouble::scd_path);

	SGCore_ShaderLoad(ShaderType::st_vertex, "mtrlgreen_base_tree.vs", "mtrlgreen_base_tree", ShaderCheckDouble::scd_path);
	SGCore_ShaderLoad(ShaderType::st_vertex, "mtrlgreen_base_grass.vs", "mtrlgreen_base_grass", ShaderCheckDouble::scd_path);
	SGCore_ShaderLoad(ShaderType::st_pixel, "mtrlgreen_base.ps", "mtrlgreen_base", ShaderCheckDouble::scd_path);

	SGCore_ShaderLoad(ShaderType::st_pixel, "mtrlgeom_light.ps", "mtrlgeom_light", ShaderCheckDouble::scd_path);

	SGCore_ShaderLoad(ShaderType::st_vertex, "mtrlskin_base.vs", "mtrlskin_base", ShaderCheckDouble::scd_path);
	SGCore_ShaderLoad(ShaderType::st_pixel, "mtrlskin_base.ps", "mtrlskin_base", ShaderCheckDouble::scd_path);

	IsIncrCountSurf = false;
	CurrIdSurf = 0;

	UnitMaterial* tmpumtl = new UnitMaterial();
	Material* tmpMtlDefaultLight = new Material();
	AddMaterial(tmpMtlDefaultLight);
	tmpumtl->mtl = tmpMtlDefaultLight;
	sprintf(tmpMtlDefaultLight->Name, "%s_%s", MTL_VIRTUAL_DIR_STD_MTL, "light");
	tmpMtlDefaultLight->PreShaderVS = SGCore_ShaderGetID(ShaderType::st_vertex, "mtrlgeom_base");
	tmpMtlDefaultLight->PreShaderPS = SGCore_ShaderGetID(ShaderType::st_pixel, "mtrlgeom_light");

	tmpMtlDefaultLight->MainTexture = -1;
	tmpMtlDefaultLight->VS.IsTransWorldViewProjection = true;

	MtrlDefLight = AddUnitMaterial(tmpumtl);
	AddName(tmpMtlDefaultLight->Name, MtrlDefLight);



	tmpumtl = new UnitMaterial();
	tmpMtlDefaultLight = new Material();
	AddMaterial(tmpMtlDefaultLight);
	tmpumtl->mtl = tmpMtlDefaultLight;
	sprintf(tmpMtlDefaultLight->Name, "%s_%s", MTL_VIRTUAL_DIR_STD_MTL, "base");
	tmpumtl->mtl->PreShaderVS = SGCore_ShaderGetID(ShaderType::st_vertex, "mtrlgeom_base");
	tmpumtl->mtl->PreShaderPS = SGCore_ShaderGetID(ShaderType::st_pixel, "mtrlgeom_base");
	tmpumtl->mtl->VS.IsTransWorld = true;

	tmpumtl->mtl->MainTexture = -1;
	tmpumtl->mtl->VS.IsTransWorldViewProjection = true;

	MtrlDefStatic = AddUnitMaterial(tmpumtl);
	AddName(tmpumtl->mtl->Name, MtrlDefStatic);


	tmpumtl = new UnitMaterial();
	tmpMtlDefaultLight = new Material();
	AddMaterial(tmpMtlDefaultLight);
	tmpumtl->mtl = tmpMtlDefaultLight;
	sprintf(tmpMtlDefaultLight->Name, "%s_%s", MTL_VIRTUAL_DIR_STD_MTL, "tree");
	tmpumtl->mtl->PreShaderVS = SGCore_ShaderGetID(ShaderType::st_vertex, "mtrlgreen_base_tree");
	tmpumtl->mtl->PreShaderPS = SGCore_ShaderGetID(ShaderType::st_pixel, "mtrlgreen_base");

	tmpumtl->mtl->MainTexture = -1;
	tmpumtl->mtl->VS.IsTransWorldViewProjection = true;

	MtrlDefTree = AddUnitMaterial(tmpumtl);
	AddName(tmpumtl->mtl->Name, MtrlDefTree);


	tmpumtl = new UnitMaterial();
	tmpMtlDefaultLight = new Material();
	AddMaterial(tmpMtlDefaultLight);
	tmpumtl->mtl = tmpMtlDefaultLight;
	sprintf(tmpMtlDefaultLight->Name, "%s_%s", MTL_VIRTUAL_DIR_STD_MTL, "grass");
	tmpumtl->mtl->PreShaderVS = SGCore_ShaderGetID(ShaderType::st_vertex, "mtrlgreen_base_grass");
	tmpumtl->mtl->PreShaderPS = SGCore_ShaderGetID(ShaderType::st_pixel, "mtrlgreen_base");

	tmpumtl->mtl->MainTexture = -1;
	tmpumtl->mtl->VS.IsTransWorldViewProjection = true;

	MtrlDefGrass = AddUnitMaterial(tmpumtl);
	AddName(tmpumtl->mtl->Name, MtrlDefGrass);


	/*tmpumtl = new UnitMaterial();
	tmpMtlDefaultLight = new Material();
	tmpumtl->mtl = tmpMtlDefaultLight;
	sprintf(tmpMtlDefaultLight->Name, "%s", "mtrldef_skin");
	tmpumtl->mtl->PreShaderVS = SGCore_ShaderGetID(0, "mtrlskin_base");
	tmpumtl->mtl->PreShaderPS = SGCore_ShaderGetID(1, "mtrlskin_base");
	tmpumtl->mtl->VS.IsTransWorld = true;

	tmpumtl->mtl->MainTexture = -1;
	tmpumtl->mtl->VS.IsTransWorldViewProjection = true;

	ArrMaterials.push_back(tmpumtl);
	AddName(tmpumtl->mtl->Name, ArrMaterials.size() - 1);
	MtrlDefSkin = ArrMaterials.size() - 1;*/

	BeginNonDef = ArrMaterials.size();
}

Materials::~Materials()
{
	for (int i = 0; i < ArrHMtls.size(); ++i)
	{
		for (int k = 0; k < ArrHMtls[i]->ArrTex.size(); ++k)
		{
			mem_delete(ArrHMtls[i]->ArrTex[k]);
		}

		mem_delete(ArrHMtls[i]);
	}

	for (int i = 0; i < ArrMaterials.size(); ++i)
	{
		mem_delete(ArrMaterials[i]);
	}

	for (int i = 0; i < ArrMtrls.size(); ++i)
	{
		mem_delete(ArrMtrls[i]);
	}
}

Materials::Material::Material()
{
	Name[0] = 0;
	TransVSDataInPS = false;
	TransPSDataInVS = false;

	IsDelete = false;

	IsUnlit = false;
	IsAlphaTest = false;
	PhysicsMaterial = MtlPhysicType::mpt_concrete;

	Type = MtlTypeModel::tms_static;

	MainTexture - 1;
	PreShaderVS - 1;
	PreShaderPS - 1;
}

void Materials::Material::Nulling()
{
	Name[0] = 0;
	TransVSDataInPS = false;
	TransPSDataInVS = false;
	IsDelete = false;
	IsUnlit = false;
	IsAlphaTest = false;
	PhysicsMaterial = MtlPhysicType::mpt_concrete;

	Type = MtlTypeModel::tms_static;

	MainTexture-1;
	PreShaderVS-1;
	PreShaderPS-1;
	
	MicroDetail = MaterialMaskPM();
	LightParam = MaterialLightParam();

	VS = MaterialDataShader();
	PS = MaterialDataShader();
}

Materials::Material::~Material()
{
	if (MainTexture >= 0)
		SGCore_LoadTexDelete(MainTexture);

	if (LightParam.ParamTex >= 0)
		SGCore_LoadTexDelete(LightParam.ParamTex);

	if (LightParam.ParamTexHand >= 0)
		SGCore_LoadTexDelete(LightParam.ParamTexHand);

	if (MicroDetail.Mask >= 0)
		SGCore_LoadTexDelete(MicroDetail.Mask);

	for (int i = 0; i < 4; ++i)
	{
		if (MicroDetail.ArrDeatail[i] >= 0)
			SGCore_LoadTexDelete(MicroDetail.ArrDeatail[i]);

		if (MicroDetail.ArrMicroDiffuse[i] >= 0)
			SGCore_LoadTexDelete(MicroDetail.ArrMicroDiffuse[i]);
	}
}

Materials::Material::MaterialDataShader::MaterialDataShader()
{
	IsTransWorld = false;
	IsTransView = false;
	IsTransProjection = false;
	IsTransWorldView = false;
	IsTransWorldViewProjection = false;
	IsTransPosCam = false;
	IsTransTimeDelta = false;
	IsTransUserData = false;
	IsTransWinSize = false;
	Param = float4(0, 0, 0, 0);
};

Materials::Material::MaterialDataShader::~MaterialDataShader()
{

};

Materials::Material::MaterialLightParam::MaterialLightParam()
{
	ParamTex = -1;
	ParamTexHand = -1;

	RoughnessValue = 0.f;
	F0Value = 0.f;
	TypeRefraction = MtlTypeTransparency::mtt_none;

	TypeReflect = MtlTypeReflect::mtr_none;
	IsTextureParam = true;
}

Materials::Material::MaterialLightParam::~MaterialLightParam()
{

}

Materials::Material::MaterialMaskPM::MaterialMaskPM()
{
	Mask = -1;
	ArrDeatail[0] = -1;
	ArrDeatail[1] = -1;
	ArrDeatail[2] = -1;
	ArrDeatail[3] = -1;

	ArrMicroDiffuse[0] = -1;
	ArrMicroDiffuse[1] = -1;
	ArrMicroDiffuse[2] = -1;
	ArrMicroDiffuse[3] = -1;
}

Materials::Material::MaterialMaskPM::~MaterialMaskPM()
{

}

Materials::UnitMaterial::UnitMaterial()
{
	mtl = 0;
	Reflect = 0;
}

Materials::UnitMaterial::~UnitMaterial()
{
	mtl->IsDelete = true;
	Reflect = 0;
	//mem_delete(Reflect);
}

/////

int Materials::DelRefCount()
{
	return ArrDelRefMtrls.size();
}

ID Materials::DelRefGetIDArr(ID key, ID inid, int cube)
{
	if (!(key >= 0 && key < ArrDelRefMtrls.size()))
		return -1;

	return ArrDelRefMtrls[key]->GetIDArr(inid, cube);
}

void Materials::DelRefAllDel()
{
	for (int i = 0; i < ArrDelRefMtrls.size(); ++i)
	{
		mem_delete(ArrDelRefMtrls[i]);
	}

	ArrDelRefMtrls.clear();
}

void Materials::Clear(bool clear_del)
{
	int tmpcountdel = 0;
	
	for (int i = 0; i < ArrHMtls.size(); ++i)
	{
		if (strcmp(ArrHMtls[i]->Path.c_str(), MTL_VIRTUAL_DIR_STD_MTL) != 0)
		{
			for (int k = 0; k < ArrHMtls[i]->ArrTex.size(); ++k)
			{
				mem_delete(ArrHMtls[i]->ArrTex[k]);
				ArrHMtls[i]->ArrTex.erase(k);
				--k;
				++tmpcountdel;
			}

			if (ArrHMtls.size() <= 0)
			{
				mem_delete(ArrHMtls[i]);
				ArrHMtls.erase(i);
				--i;
			}
		}
	}

	tmpcountdel = 0;

	for (int i = BeginNonDef; i < ArrMaterials.size(); ++i)
	{
		//если есть отражения, то записываем в очередь на удаление
		if (ArrMaterials[i]->Reflect)
			ArrDelRefMtrls.push_back(ArrMaterials[i]->Reflect);

		mem_delete(ArrMaterials[i]);
		++tmpcountdel;
	}

	CurrFirstFree = BeginNonDef;

	tmpcountdel = 0;

	for (int i = 0; i < ArrMtrls.size(); ++i)
	{
		if (ArrMtrls[i]->IsDelete)
		{
			mem_delete(ArrMtrls[i]);
			ArrMtrls.erase(i);
			--i;
			++tmpcountdel;
		}
	}

	if (clear_del)
		DelRefAllDel();
}

void Materials::OnLostDevice()
{
	for (long i = 0; i < ArrMaterials.size(); ++i)
	{
		if (ArrMaterials[i] && ArrMaterials[i]->Reflect)
			ArrMaterials[i]->Reflect->OnLostDevice();
	}
}

void Materials::OnResetDevice()
{
	for (long i = 0; i < ArrMaterials.size(); ++i)
	{
		if (ArrMaterials[i] && ArrMaterials[i]->Reflect)
			ArrMaterials[i]->Reflect->OnResetDevice();
	}
}

////

ID Materials::GetStdMtl(MtlTypeModel type_model)
{
	if (type_model == MtlTypeModel::tms_static)
	{
		return MtrlDefStatic;
	}
	else if (type_model == MtlTypeModel::tms_grass)
	{
		return MtrlDefGrass;
	}
	else if (type_model == MtlTypeModel::tms_tree)
	{
		return MtrlDefTree;
	}
	else if (type_model == MtlTypeModel::tms_skin)
	{
		return MtrlDefSkin;
	}
}

MtlTypeModel Materials::GetTypeModel(ID id)
{
	MTL_PRE_COND_ID(id, MtlTypeModel::tms_static);
	return ArrMaterials[id]->mtl->Type;
}

void Materials::SetTypeModel(ID id, MtlTypeModel type_model)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->Type = type_model;
}

bool Materials::MtlGetUsingAlphaTest(ID id)
{
	MTL_PRE_COND_ID(id, false);
	return ArrMaterials[id]->mtl->IsAlphaTest;
}

void Materials::MtlSetUsingAlphaTest(ID id, bool is_using)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->IsAlphaTest = is_using;
}

MtlTypeReflect Materials::MtlTypeReflection(ID id)
{
	MTL_PRE_COND_ID(id, MtlTypeReflect::mtr_none);
	return ArrMaterials[id]->mtl->LightParam.TypeReflect;
}


///////

void Materials::MtlRefSetIDArr(ID id, ID inid, int cube, ID idarr)
{
	MTL_REF_PRE_COND_ID(id);
	ArrMaterials[id]->Reflect->SetIDArr(inid, cube, idarr);
}

ID Materials::MtlRefGetIDArr(ID id, ID inid, int cube)
{
	MTL_REF_PRE_COND_ID(id,- 1);
	return ArrMaterials[id]->Reflect->GetIDArr(inid, cube);
}

/*void Materials::MtlRefSetPlane(ID id, D3DXPLANE* plane)
{
	MTL_REF_PRE_COND_ID(id);
	ArrMaterials[id]->Reflect->Plane = *plane;
}*/

/*void Materials::MtlRefSetCenter(ID id, float3_t* center)
{
	MTL_REF_PRE_COND_ID(id);
	ArrMaterials[id]->Reflect->Position = *center;
}*/

void Materials::MtlRefPreRenderPlane(ID id, D3DXPLANE* plane)
{
	MTL_REF_PRE_COND_ID(id);
	ArrMaterials[id]->Reflect->PreRenderRefPlane(plane);
}

ISXFrustum* Materials::MtlRefGetfrustum(ID id, int cube)
{
	MTL_REF_PRE_COND_ID(id,0);
	if (cube == 0 || (cube > 0 && (ArrMaterials[id]->Reflect->GetTypeReflect() == MtlTypeReflect::mtr_cube_static || ArrMaterials[id]->Reflect->GetTypeReflect() == MtlTypeReflect::mtr_cube_dynamic)))
		return ArrMaterials[id]->Reflect->ReflectFrustum[cube];
	return 0;
}

void Materials::MtlRefPostRenderPlane(ID id)
{
	MTL_REF_PRE_COND_ID(id);
	ArrMaterials[id]->Reflect->PostRenderRefPlane();
}

IDirect3DTexture9* Materials::MtlRefPlaneGetTex(ID id)
{
 	MTL_REF_PRE_COND_ID(id,0);
	return ArrMaterials[id]->Reflect->GetRefPlaneTex();
}


void Materials::MtlRefSetMinMax(ID id, float3_t* min, float3_t* max)
{
	MTL_REF_PRE_COND_ID(id);
	ArrMaterials[id]->Reflect->SetMinMax(min,max);
}

bool Materials::MtlRefIsAllowedRender(ID  id)
{
	MTL_REF_PRE_COND_ID(id,false);
	if (ArrMaterials[id]->Reflect)
		return ArrMaterials[id]->Reflect->AllowedRender();

	return false;
}


void Materials::MtlRefCubeBeginRender(ID id, float3_t* center)
{
	MTL_REF_PRE_COND_ID(id);
	ArrMaterials[id]->Reflect->BeginRenderRefCube(center);
}

void Materials::MtlRefCubePreRender(ID id, int cube, float4x4* world)
{
	MTL_REF_PRE_COND_ID(id);
	ArrMaterials[id]->Reflect->PreRenderRefCube(cube, world);
}

void Materials::MtlRefCubePostRender(ID id, int cube)
{
	MTL_REF_PRE_COND_ID(id);
	ArrMaterials[id]->Reflect->PostRenderRefCube(cube);
}

void Materials::MtlRefCubeEndRender(ID id, float3_t* viewpos)
{
	MTL_REF_PRE_COND_ID(id);
	ArrMaterials[id]->Reflect->EndRenderRefCube(viewpos);
}

bool Materials::MtlRefUpdateCountUpdate( ID id, float3_t* viewpos)
{
	MTL_REF_PRE_COND_ID(id,false);
	return ArrMaterials[id]->Reflect->UpdateCountUpdate(viewpos);
}

void Materials::MtlRefNullingCountUpdate(ID id)
{
	MTL_REF_PRE_COND_ID(id);
	ArrMaterials[id]->Reflect->NullingCountUpdate();
}

IDirect3DCubeTexture9* Materials::RefCubeGetTex(ID id)
{
	MTL_REF_PRE_COND_ID(id,0);
	return ArrMaterials[id]->Reflect->GetRefCubeTex();
}


///////

void Materials::MtlSetPhysicMaterial(ID id, MtlPhysicType type)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->PhysicsMaterial = type;
}

MtlPhysicType Materials::MtlGetPhysicMaterial(ID id)
{
	MTL_PRE_COND_ID(id, (MtlPhysicType )-1);
	return ArrMaterials[id]->mtl->PhysicsMaterial;
}

void Materials::MtlSetTexture(ID id, const char* path_tex)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->MainTexture = SGCore_LoadTexAddName(path_tex, LoadTexType::ltt_load);
}

void Materials::MtlGetTexture(ID id, char* name)
{
	MTL_PRE_COND_ID(id);

	if (name && ArrMaterials[id]->mtl->MainTexture >= 0)
		SGCore_LoadTexGetName(ArrMaterials[id]->mtl->MainTexture, name);
}

void Materials::MtlSetVS(ID id, const char* path_vs)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->PreShaderVS = SGCore_ShaderLoad(ShaderType::st_vertex, path_vs, path_vs, ShaderCheckDouble::scd_path);
}

void Materials::MtlGetVS(ID id, char* name)
{
	MTL_PRE_COND_ID(id);
	SGCore_ShaderGetPath(ShaderType::st_vertex, ArrMaterials[id]->mtl->PreShaderVS, name);
}

void Materials::MtlSetPS(ID id, const char* path_ps)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->PreShaderPS = SGCore_ShaderLoad(ShaderType::st_pixel, path_ps, path_ps, ShaderCheckDouble::scd_path);
}

void Materials::MtlGetPS(ID id, char* name)
{
	MTL_PRE_COND_ID(id);
	SGCore_ShaderGetPath(ShaderType::st_pixel, ArrMaterials[id]->mtl->PreShaderPS, name);
}




void Materials::MtlSetLighting(ID id, bool is_lighting)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->IsUnlit = !is_lighting;
}

bool Materials::MtlGetLighting(ID id)
{
	MTL_PRE_COND_ID(id,false);
	return !ArrMaterials[id]->mtl->IsUnlit;
}


void Materials::MtlSetIsTextureLighting(ID id, bool is_tex_lighting)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->LightParam.IsTextureParam = is_tex_lighting;
}

bool Materials::MtlGetIsTextureLighting(ID id)
{
	MTL_PRE_COND_ID(id,false);
	return ArrMaterials[id]->mtl->LightParam.IsTextureParam;
}


void Materials::MtlSetTextureLighting(ID id, const char* path_tex)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->LightParam.ParamTex = SGCore_LoadTexAddName(path_tex, LoadTexType::ltt_load);
}

void Materials::MtlGetTextureLighting(ID id, char* path_tex)
{
	MTL_PRE_COND_ID(id);
	if (path_tex && ArrMaterials[id]->mtl->LightParam.ParamTex >= 0)
	{
		SGCore_LoadTexGetName(ArrMaterials[id]->mtl->LightParam.ParamTex, path_tex);
		if (path_tex[0] == MTL_VIRTUAL_DIR_HAND_MTL)
			path_tex[0] = 0;
	}
	else if (path_tex)
		path_tex[0] = 0;
}


void Materials::MtlSetRoughness(ID id, float roughness)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->LightParam.RoughnessValue = roughness;
}

float Materials::MtlGetRoughness(ID id)
{
	MTL_PRE_COND_ID(id,-1);
	return ArrMaterials[id]->mtl->LightParam.RoughnessValue;
}


void Materials::MtlSetF0(ID id, float f0)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->LightParam.F0Value = f0;
}

float Materials::MtlGetF0(ID id)
{
	MTL_PRE_COND_ID(id,-1);
	return ArrMaterials[id]->mtl->LightParam.F0Value;
}


void Materials::MtlSetTypeTransparency(ID id, MtlTypeTransparency type)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->LightParam.TypeRefraction = type;
}

MtlTypeTransparency Materials::MtlGetTypeTransparency(ID id)
{
	MTL_PRE_COND_ID(id, MtlTypeTransparency::mtt_none);
	return ArrMaterials[id]->mtl->LightParam.TypeRefraction;
}


void Materials::MtlSetTypeReflection(ID id, MtlTypeReflect type)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->LightParam.TypeReflect = type;

	if (ArrMaterials[id]->mtl->LightParam.TypeReflect != MtlTypeReflect::mtr_none)
	{
		if (!ArrMaterials[id]->Reflect)
			ArrMaterials[id]->Reflect = new Reflection();

		ArrMaterials[id]->Reflect->Init(ArrMaterials[id]->mtl->LightParam.TypeReflect);
	}
}

MtlTypeReflect Materials::MtlGetTypeReflection(ID id)
{
	MTL_PRE_COND_ID(id, MtlTypeReflect::mtr_none);
	return ArrMaterials[id]->mtl->LightParam.TypeReflect;
}




void Materials::MtlSetMaskTex(ID id, const char* path_tex)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->MicroDetail.Mask = SGCore_LoadTexAddName(path_tex, LoadTexType::ltt_load);
}

void Materials::MtlGetMaskTex(ID id, char* path_tex)
{
	MTL_PRE_COND_ID(id);
	if (path_tex && ArrMaterials[id]->mtl->MicroDetail.Mask >= 0)
		SGCore_LoadTexGetName(ArrMaterials[id]->mtl->MicroDetail.Mask, path_tex);
	else if (path_tex)
		path_tex[0] = 0;
}

void Materials::MtlSetMRTex(ID id, int channel, const char* path_tex)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->MicroDetail.ArrMicroDiffuse[channel] = SGCore_LoadTexAddName(path_tex, LoadTexType::ltt_load);
}

void Materials::MtlGetMRTex(ID id, int channel, char* path_tex)
{
	MTL_PRE_COND_ID(id);
	if (path_tex && ArrMaterials[id]->mtl->MicroDetail.ArrMicroDiffuse[channel] >= 0)
		SGCore_LoadTexGetName(ArrMaterials[id]->mtl->MicroDetail.ArrMicroDiffuse[channel], path_tex);
	else if (path_tex)
		path_tex[0] = 0;
}


void Materials::MtlSetDTex(ID id, int channel, const char* path_tex)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->MicroDetail.ArrDeatail[channel] = SGCore_LoadTexAddName(path_tex, LoadTexType::ltt_load);
}

void Materials::MtlGetDTex(ID id, int channel, char* path_tex)
{
	MTL_PRE_COND_ID(id);
	if (path_tex && ArrMaterials[id]->mtl->MicroDetail.ArrDeatail[channel] >= 0)
		SGCore_LoadTexGetName(ArrMaterials[id]->mtl->MicroDetail.ArrDeatail[channel], path_tex);
	else if (path_tex)
		path_tex[0] = 0;
}



void Materials::MtlSetSTDVS(ID id, MtlTransShaderStd type, bool is_send)
{
	MTL_PRE_COND_ID(id);
	if (type == MtlTransShaderStd::mtss_mat_w)
		ArrMaterials[id]->mtl->VS.IsTransWorld = is_send;
	else if (type == MtlTransShaderStd::mtss_mat_v)
		ArrMaterials[id]->mtl->VS.IsTransView = is_send;
	else if (type == MtlTransShaderStd::mtss_mat_p)
		ArrMaterials[id]->mtl->VS.IsTransProjection = is_send;
	else if (type == MtlTransShaderStd::mtss_mat_wv)
		ArrMaterials[id]->mtl->VS.IsTransWorldView = is_send;
	else if (type == MtlTransShaderStd::mtss_mat_wvp)
		ArrMaterials[id]->mtl->VS.IsTransWorldViewProjection = is_send;

	else if (type == MtlTransShaderStd::mtss_campos)
		ArrMaterials[id]->mtl->VS.IsTransPosCam = is_send;
	else if (type == MtlTransShaderStd::mtss_timedelta)
		ArrMaterials[id]->mtl->VS.IsTransTimeDelta = is_send;

	else if (type == MtlTransShaderStd::mtss_ud)
		ArrMaterials[id]->mtl->VS.IsTransUserData = is_send;

	else if (type == MtlTransShaderStd::mtss_winsize)
		ArrMaterials[id]->mtl->VS.IsTransWinSize = is_send;
}

bool Materials::MtlGetSTDVS(ID id, MtlTransShaderStd type)
{
	MTL_PRE_COND_ID(id,false);
	if (type == MtlTransShaderStd::mtss_mat_w)
		return ArrMaterials[id]->mtl->VS.IsTransWorld;
	else if (type == MtlTransShaderStd::mtss_mat_v)
		return ArrMaterials[id]->mtl->VS.IsTransView;
	else if (type == MtlTransShaderStd::mtss_mat_p)
		return ArrMaterials[id]->mtl->VS.IsTransProjection;
	else if (type == MtlTransShaderStd::mtss_mat_wv)
		return ArrMaterials[id]->mtl->VS.IsTransWorldView;
	else if (type == MtlTransShaderStd::mtss_mat_wvp)
		return ArrMaterials[id]->mtl->VS.IsTransWorldViewProjection;

	else if (type == MtlTransShaderStd::mtss_campos)
		return ArrMaterials[id]->mtl->VS.IsTransPosCam;
	else if (type == MtlTransShaderStd::mtss_timedelta)
		return ArrMaterials[id]->mtl->VS.IsTransTimeDelta;

	else if (type == MtlTransShaderStd::mtss_ud)
		return ArrMaterials[id]->mtl->VS.IsTransUserData;

	else if (type == MtlTransShaderStd::mtss_winsize)
		return ArrMaterials[id]->mtl->VS.IsTransWinSize;
}

void Materials::MtlSetSTDPS(ID id, MtlTransShaderStd type, bool is_send)
{
	MTL_PRE_COND_ID(id);
	if (type == MtlTransShaderStd::mtss_mat_w)
		ArrMaterials[id]->mtl->PS.IsTransWorld = is_send;
	else if (type == MtlTransShaderStd::mtss_mat_v)
		ArrMaterials[id]->mtl->PS.IsTransView = is_send;
	else if (type == MtlTransShaderStd::mtss_mat_p)
		ArrMaterials[id]->mtl->PS.IsTransProjection = is_send;
	else if (type == MtlTransShaderStd::mtss_mat_wv)
		ArrMaterials[id]->mtl->PS.IsTransWorldView = is_send;
	else if (type == MtlTransShaderStd::mtss_mat_wvp)
		ArrMaterials[id]->mtl->PS.IsTransWorldViewProjection = is_send;

	else if (type == MtlTransShaderStd::mtss_campos)
		ArrMaterials[id]->mtl->PS.IsTransPosCam = is_send;
	else if (type == MtlTransShaderStd::mtss_timedelta)
		ArrMaterials[id]->mtl->PS.IsTransTimeDelta = is_send;

	else if (type == MtlTransShaderStd::mtss_ud)
		ArrMaterials[id]->mtl->PS.IsTransUserData = is_send;

	else if (type == MtlTransShaderStd::mtss_winsize)
		ArrMaterials[id]->mtl->PS.IsTransWinSize = is_send;
}

bool Materials::MtlGetSTDPS(ID id, MtlTransShaderStd type)
{
	MTL_PRE_COND_ID(id,false);
	if (type == MtlTransShaderStd::mtss_mat_w)
		return ArrMaterials[id]->mtl->PS.IsTransWorld;
	else if (type == MtlTransShaderStd::mtss_mat_v)
		return ArrMaterials[id]->mtl->PS.IsTransView;
	else if (type == MtlTransShaderStd::mtss_mat_p)
		return ArrMaterials[id]->mtl->PS.IsTransProjection;
	else if (type == MtlTransShaderStd::mtss_mat_wv)
		return ArrMaterials[id]->mtl->PS.IsTransWorldView;
	else if (type == MtlTransShaderStd::mtss_mat_wvp)
		return ArrMaterials[id]->mtl->PS.IsTransWorldViewProjection;

	else if (type == MtlTransShaderStd::mtss_campos)
		return ArrMaterials[id]->mtl->PS.IsTransPosCam;
	else if (type == MtlTransShaderStd::mtss_timedelta)
		return ArrMaterials[id]->mtl->PS.IsTransTimeDelta;

	else if (type == MtlTransShaderStd::mtss_ud)
		return ArrMaterials[id]->mtl->PS.IsTransUserData;

	else if (type == MtlTransShaderStd::mtss_winsize)
		return ArrMaterials[id]->mtl->PS.IsTransWinSize;
}


void Materials::MtlSetUDVS(ID id, int component, float val)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->VS.Param[component] = val;
}

float Materials::MtlGetUDVS(ID id, int component)
{
	MTL_PRE_COND_ID(id,-1);
	return ArrMaterials[id]->mtl->VS.Param[component];
}

void Materials::MtlSetUDVS_InPS(ID id, bool is_send_ps)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->TransVSDataInPS = is_send_ps;
}

bool Materials::MtlGetUDVS_InPS(ID id)
{
	MTL_PRE_COND_ID(id,false);
	return ArrMaterials[id]->mtl->TransVSDataInPS;
}


void Materials::MtlSetUDPS(ID id, int component, float val)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->PS.Param[component] = val;
}

float Materials::MtlGetUDPS(ID id, int component)
{
	MTL_PRE_COND_ID(id,-1);
	return ArrMaterials[id]->mtl->PS.Param[component];
}

void Materials::MtlSetUDPS_InPS(ID id, bool is_send_vs)
{
	MTL_PRE_COND_ID(id);
	ArrMaterials[id]->mtl->TransPSDataInVS = is_send_vs;
}

bool Materials::MtlGetUDPS_InPS(ID id)
{
	MTL_PRE_COND_ID(id,false);
	return ArrMaterials[id]->mtl->TransPSDataInVS;
}


///////

ID Materials::IsExists(const char* name)
{
	char tmp_path[MTL_MAX_SIZE_DIR];//папка
	char tmp_name[MTL_MAX_SIZE_NAME];//само имя текстыр с расширением
	long id = -1;
	bool IsTruePath = false;
	//обрезаем имя текстуры и папку
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
		return -2;
		//reportf(-1, "%s - wrong texture name [%s]!!!", gen_msg_location, name);
	}

	long tmpkey = -1;	//переменная в которой храним ключ от массива в который записываем
	for (long i = 0; i<ArrHMtls.size(); ++i)
	{
		//TLPath* tmptlpath = ArrHMtls[i];
		if (ArrHMtls[i] && strcmp(ArrHMtls[i]->Path.c_str(), tmp_path) == 0)
		{
			tmpkey = i;
			break;
		}
	}

	//если мы не нашли совпадений значит путь уникален ...
	if (tmpkey == -1)
	{
		return -1;
	}

	//проверяем записано ли уже имя текстуры
	for (int i = 0; i<ArrHMtls[tmpkey]->ArrTex.size(); i++)
	{
		if (strcmp(ArrHMtls[tmpkey]->ArrTex[i]->name.c_str(), tmp_name) == 0)
		{
			id = ArrHMtls[tmpkey]->ArrTex[i]->id;
			break;
		}
	}

	return id;
}

ID Materials::AddUnitMaterial(UnitMaterial* umtl)
{
	ID tmpid = -1;
	if (CurrFirstFree + 1 == ArrMaterials.size())
	{
		ArrMaterials.push_back(umtl);
		CurrFirstFree = tmpid = ArrMaterials.size() - 1;
	}
	else
	{
		if (CurrFirstFree < 0 || ArrMaterials[CurrFirstFree] != 0)
		{
			if (CurrFirstFree < 0)
				CurrFirstFree = 0;

			for (int i = CurrFirstFree; i < ArrMaterials.size(); ++i)
			{
				if (ArrMaterials[i] == 0)
				{
					CurrFirstFree = i;
					break;
				}
			}
		}

		ArrMaterials[CurrFirstFree] = umtl;
		tmpid = CurrFirstFree;
		++CurrFirstFree;
	}

	return tmpid;
}

ID Materials::AddMaterial(Material* mtl)
{
	ArrMtrls.push_back(mtl);
	return ArrMtrls.size() - 1;
}

void Materials::AddName(const char* name, ID id)
{
	char tmp_path[MTL_MAX_SIZE_DIR];//папка
	char tmp_name[MTL_MAX_SIZE_NAME];//само имя текстыр с расширением

	bool IsTruePath = false;
	//обрезаем имя текстуры и папку
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

	long tmpkey = -1;	//переменная в которой храним ключ от массива в который записываем
	for (long i = 0; i<ArrHMtls.size(); ++i)
	{
		if (ArrHMtls[i] && strcmp(ArrHMtls[i]->Path.c_str(), tmp_path) == 0)
		{
			tmpkey = i;
			break;
		}
	}

	//если мы не нашли совпадений значит путь уникален ...
	if (tmpkey == -1)
	{
		tmpkey = ArrHMtls.size();
		TLPath* tmpntlp = new TLPath();
		ArrHMtls.push_back(tmpntlp);
		ArrHMtls[tmpkey]->Path = tmp_path;
	}

	ArrHMtls[tmpkey]->ArrTex.push_back(new TLPath::TLTex(id, tmp_name));
	//ArrHMtls[tmpkey]->ArrTex.push_back(tmp_name);
	//ArrHMtls[tmpkey]->ArrID.push_back(id);
}

bool Materials::LoadMtl(const char* name, Material** mtl)
{
	char* ArrRGBA[4] = { "r", "g", "b", "a" };

	char tmpNameMtl[256];
	char tmpVS[256];
	char tmpPS[256];

	char tmpMask[256];
	char tmpMicroDiff[4][256];
	char tmpDetail[4][256];

	char tmpParamLigth[256];

	char tmp_path[256];//папка
	char tmp_name[256];//само им¤ текстыр с расширением

	bool IsTruePath = false;
	//обрезаем им¤ текстуры и папку
	for (long k = 0; k< strlen(name); k++)
	{
		if (name[k] == '_')
		{
			memcpy(tmp_path, name, sizeof(char)*k);
			tmp_path[k] = 0;
			sprintf(tmp_name, "%s", name + k + 1);
			IsTruePath = true;
			break;
		}
	}

	char path[1024];

	for (DWORD k = 0; k<strlen(name); k++)
	{
		if (name[k] == '.')
		{
			sprintf(tmp_name, "%s", name);
			tmp_name[k] = 0;
			IsTruePath = true;
			break;
		}
	}

	Material* tmpMtl = *mtl;

	sprintf(path, "%s%s\\%s.mtl", MLSet::StdPathMaterial, tmp_path, tmp_name);
	if (Core_0FileExists(path))
	{
		ISXLConfig* config = Core_OpLConfig(path);

		//если в конфиге указана текстура то берем ее
		if (config->KeyExists(tmp_name, "texture"))
			tmpMtl->MainTexture = SGCore_LoadTexAddName(config->GetKey(tmp_name, "texture"), LoadTexType::ltt_load);
		else //если нет то тогда берем имя материала, может быть он имя текстуры, иначе будет -1
			tmpMtl->MainTexture = SGCore_LoadTexAddName(name, LoadTexType::ltt_load);

		sprintf(tmpMtl->Name, "%s", tmp_name);

		tmpVS[0] = 0;
		if (config->KeyExists(tmp_name, "vs"))
			sprintf(tmpVS, "%s", config->GetKey(tmp_name, "vs"));

		tmpPS[0] = 0;
		if (config->KeyExists(tmp_name, "ps"))
			sprintf(tmpPS, "%s", config->GetKey(tmp_name, "ps"));


		if (config->KeyExists(tmp_name, "is_unlit"))
			tmpMtl->IsUnlit = String(config->GetKey(tmp_name, "is_unlit")).ToBool();
		else
			tmpMtl->IsUnlit = false;

		if (config->KeyExists(tmp_name, "type"))
			tmpMtl->Type = (MtlTypeModel)String(config->GetKey(tmp_name, "type")).ToInt();
		else
			tmpMtl->Type = MtlTypeModel::tms_default;

		if (config->KeyExists(tmp_name, "physmaterial"))
			tmpMtl->PhysicsMaterial = (MtlPhysicType)String(config->GetKey(tmp_name, "physmaterial")).ToInt();
		else
			tmpMtl->PhysicsMaterial = MtlPhysicType::mpt_default;


		if (def_str_validate(tmpVS))
			tmpMtl->PreShaderVS = SGCore_ShaderLoad(ShaderType::st_vertex, tmpVS, "main", ShaderCheckDouble::scd_path);
		else
			tmpMtl->PreShaderVS = SGCore_ShaderGetID(ShaderType::st_vertex, "mtrlgeom_base");

		if (def_str_validate(tmpPS))
			tmpMtl->PreShaderPS = SGCore_ShaderLoad(ShaderType::st_pixel, tmpPS, "main", ShaderCheckDouble::scd_path);
		else
			tmpMtl->PreShaderPS = SGCore_ShaderGetID(ShaderType::st_pixel, "mtrlgeom_base");

		sprintf(tmpMicroDiff[0], "%s", config->GetKey(tmp_name, "mirco_diff_r"));

		if (tmpMicroDiff[0][0] != '0' && tmpMicroDiff[0][0] != 0)
			tmpMtl->MicroDetail.ArrMicroDiffuse[0] = SGCore_LoadTexAddName(tmpMicroDiff[0], LoadTexType::ltt_load);
		else
			tmpMtl->MicroDetail.ArrMicroDiffuse[0] = -1;

		sprintf(tmpMicroDiff[1], "%s", config->GetKey(tmp_name, "mirco_diff_g"));
		if (tmpMicroDiff[1][0] != '0' && tmpMicroDiff[1][0] != 0)
			tmpMtl->MicroDetail.ArrMicroDiffuse[1] = SGCore_LoadTexAddName(tmpMicroDiff[1], LoadTexType::ltt_load);
		else
			tmpMtl->MicroDetail.ArrMicroDiffuse[1] = -1;

		sprintf(tmpMicroDiff[2], "%s", config->GetKey(tmp_name, "mirco_diff_b"));
		if (tmpMicroDiff[2][0] != '0' && tmpMicroDiff[2][0] != 0)
			tmpMtl->MicroDetail.ArrMicroDiffuse[2] = SGCore_LoadTexAddName(tmpMicroDiff[2], LoadTexType::ltt_load);
		else
			tmpMtl->MicroDetail.ArrMicroDiffuse[2] = -1;

		sprintf(tmpMicroDiff[3], "%s", config->GetKey(tmp_name, "mirco_diff_a"));
		if (tmpMicroDiff[3][0] != '0' && tmpMicroDiff[3][0] != 0)
			tmpMtl->MicroDetail.ArrMicroDiffuse[3] = SGCore_LoadTexAddName(tmpMicroDiff[3], LoadTexType::ltt_load);
		else
			tmpMtl->MicroDetail.ArrMicroDiffuse[3] = -1;



		sprintf(tmpDetail[0], "%s", config->GetKey(tmp_name, "detail_r"));
		if (tmpDetail[0][0] != '0' && tmpMicroDiff[0][0] != 0)
			tmpMtl->MicroDetail.ArrDeatail[0] = SGCore_LoadTexAddName(tmpDetail[0], LoadTexType::ltt_load);
		else
			tmpMtl->MicroDetail.ArrDeatail[0] = -1;

		sprintf(tmpDetail[1], "%s", config->GetKey(tmp_name, "detail_g"));
		if (tmpDetail[1][0] != '0' && tmpMicroDiff[1][0] != 0)
			tmpMtl->MicroDetail.ArrDeatail[1] = SGCore_LoadTexAddName(tmpDetail[1], LoadTexType::ltt_load);
		else
			tmpMtl->MicroDetail.ArrDeatail[1] = -1;

		sprintf(tmpDetail[2], "%s", config->GetKey(tmp_name, "detail_b"));
		if (tmpDetail[2][0] != '0' && tmpMicroDiff[2][0] != 0)
			tmpMtl->MicroDetail.ArrDeatail[2] = SGCore_LoadTexAddName(tmpDetail[2], LoadTexType::ltt_load);
		else
			tmpMtl->MicroDetail.ArrDeatail[2] = -1;

		sprintf(tmpDetail[3], "%s", config->GetKey(tmp_name, "detail_a"));
		if (tmpDetail[3][0] != '0' && tmpMicroDiff[3][0] != 0)
			tmpMtl->MicroDetail.ArrDeatail[3] = SGCore_LoadTexAddName(tmpDetail[3], LoadTexType::ltt_load);
		else
			tmpMtl->MicroDetail.ArrDeatail[3] = -1;


		sprintf(tmpMask, "%s", config->GetKey(tmp_name, "mask"));
		if (tmpMask[0] != '0' && tmpMask[0] != 0)
			tmpMtl->MicroDetail.Mask = SGCore_LoadTexAddName(tmpMask, LoadTexType::ltt_load);
		else
			tmpMtl->MicroDetail.Mask = -1;


		tmpMtl->LightParam.RoughnessValue = MTL_LIGHTING_DEFAULT_ROUGHNESS;
		tmpMtl->LightParam.F0Value = MTL_LIGHTING_DEFAULT_F0;

		if (config->KeyExists(tmp_name, "roughness"))
			tmpMtl->LightParam.RoughnessValue = String(config->GetKey(tmp_name, "roughness")).ToDouble();

		if (config->KeyExists(tmp_name, "f0"))
			tmpMtl->LightParam.F0Value = String(config->GetKey(tmp_name, "f0")).ToDouble();

		tmpMtl->LightParam.ParamTexHand = CreateTexParamLighting(tmpMtl->LightParam.RoughnessValue, tmpMtl->LightParam.F0Value);

		//говорим что не установлено использовать ли текстуру или нет
		int istexparam = -1;

		//если есть ключ использования текстуры то грузим
		if (config->KeyExists(tmp_name, "is_texture_param"))
			istexparam = String(config->GetKey(tmp_name, "is_texture_param")).ToBool();

		tmpParamLigth[0] = 0;
		if (config->KeyExists(tmp_name, "param_ligth"))
			sprintf(tmpParamLigth, "%s", config->GetKey(tmp_name, "param_ligth"));

		//если текстура с параметрами освещения была определена
		if (tmpParamLigth[0] != '0' && tmpParamLigth[0] != 0)
		{
			tmpMtl->LightParam.ParamTex = SGCore_LoadTexAddName(tmpParamLigth, LoadTexType::ltt_load);
			//если использование параметров освещения из текстуры не было определено
			if (istexparam == -1)
				tmpMtl->LightParam.IsTextureParam = true;
			else
				tmpMtl->LightParam.IsTextureParam = istexparam;
		}
		//если использование параметров освещения из текстуры не было определено
		else if (istexparam == -1)
		{
			tmpMtl->LightParam.IsTextureParam = false;
		}
		

		if (config->KeyExists(tmp_name, "refraction"))
			tmpMtl->LightParam.TypeRefraction = (MtlTypeTransparency)String(config->GetKey(tmp_name, "refraction")).ToInt();
		else
			tmpMtl->LightParam.TypeRefraction = MtlTypeTransparency::mtt_none;


		tmpMtl->VS.IsTransWorld = tmpMtl->VS.IsTransView = tmpMtl->VS.IsTransProjection = 
			tmpMtl->VS.IsTransWorldView = tmpMtl->VS.IsTransWorldViewProjection = tmpMtl->VS.IsTransPosCam = 
			tmpMtl->VS.IsTransTimeDelta = tmpMtl->VS.IsTransWinSize = tmpMtl->VS.IsTransUserData = false;

		if (config->KeyExists(tmp_name, "vs_world"))
			tmpMtl->VS.IsTransWorld = String(config->GetKey(tmp_name, "vs_world")).ToInt();

		if (config->KeyExists(tmp_name, "vs_view"))
			tmpMtl->VS.IsTransView = String(config->GetKey(tmp_name, "vs_view")).ToInt();

		if (config->KeyExists(tmp_name, "vs_projection"))
			tmpMtl->VS.IsTransProjection = String(config->GetKey(tmp_name, "vs_projection")).ToInt();

		if (config->KeyExists(tmp_name, "vs_worldview"))
			tmpMtl->VS.IsTransWorldView = String(config->GetKey(tmp_name, "vs_worldview")).ToInt();

		if (config->KeyExists(tmp_name, "vs_worldviewprojection"))
			tmpMtl->VS.IsTransWorldViewProjection = String(config->GetKey(tmp_name, "vs_worldviewprojection")).ToInt();

		if (config->KeyExists(tmp_name, "vs_poscam"))
			tmpMtl->VS.IsTransPosCam = String(config->GetKey(tmp_name, "vs_poscam")).ToInt();

		if (config->KeyExists(tmp_name, "vs_timedelta"))
			tmpMtl->VS.IsTransTimeDelta = String(config->GetKey(tmp_name, "vs_timedelta")).ToInt();

		if (config->KeyExists(tmp_name, "vs_winsize"))
			tmpMtl->VS.IsTransWinSize = String(config->GetKey(tmp_name, "vs_winsize")).ToInt();

		if (config->KeyExists(tmp_name, "vs_userdata"))
			tmpMtl->VS.IsTransUserData = String(config->GetKey(tmp_name, "vs_userdata")).ToInt();


		tmpMtl->VS.Param = float4(0, 0, 0, 0);
		if (config->KeyExists(tmp_name, "vs_userdata_value_x"))
			tmpMtl->VS.Param.x = String(config->GetKey(tmp_name, "vs_userdata_value_x")).ToDouble();

		if (config->KeyExists(tmp_name, "vs_userdata_value_y"))
			tmpMtl->VS.Param.y = String(config->GetKey(tmp_name, "vs_userdata_value_y")).ToDouble();

		if (config->KeyExists(tmp_name, "vs_userdata_value_z"))
			tmpMtl->VS.Param.z = String(config->GetKey(tmp_name, "vs_userdata_value_z")).ToDouble();

		if (config->KeyExists(tmp_name, "vs_userdata_value_w"))
			tmpMtl->VS.Param.w = String(config->GetKey(tmp_name, "vs_userdata_value_w")).ToDouble();

		if (config->KeyExists(tmp_name, "vs_userdata_trans_in_ps"))
			tmpMtl->TransVSDataInPS = String(config->GetKey(tmp_name, "vs_userdata_trans_in_ps")).ToBool();
		else
			tmpMtl->TransVSDataInPS = false;


		tmpMtl->PS.IsTransWorld = tmpMtl->PS.IsTransView = tmpMtl->PS.IsTransProjection =
			tmpMtl->PS.IsTransWorldView = tmpMtl->PS.IsTransWorldViewProjection = tmpMtl->PS.IsTransPosCam =
			tmpMtl->PS.IsTransTimeDelta = tmpMtl->PS.IsTransWinSize = tmpMtl->PS.IsTransUserData = false;

		if (config->KeyExists(tmp_name, "ps_world"))
			tmpMtl->PS.IsTransWorld = String(config->GetKey(tmp_name, "ps_world")).ToInt();

		if (config->KeyExists(tmp_name, "ps_view"))
			tmpMtl->PS.IsTransView = String(config->GetKey(tmp_name, "ps_view")).ToInt();

		if (config->KeyExists(tmp_name, "ps_projection"))
			tmpMtl->PS.IsTransProjection = String(config->GetKey(tmp_name, "ps_projection")).ToInt();

		if (config->KeyExists(tmp_name, "ps_worldview"))
			tmpMtl->PS.IsTransWorldView = String(config->GetKey(tmp_name, "ps_worldview")).ToInt();

		if (config->KeyExists(tmp_name, "ps_worldviewprojection"))
			tmpMtl->PS.IsTransWorldViewProjection = String(config->GetKey(tmp_name, "ps_worldviewprojection")).ToInt();

		if (config->KeyExists(tmp_name, "ps_poscam"))
			tmpMtl->PS.IsTransPosCam = String(config->GetKey(tmp_name, "ps_poscam")).ToInt();

		if (config->KeyExists(tmp_name, "ps_timedelta"))
			tmpMtl->PS.IsTransTimeDelta = String(config->GetKey(tmp_name, "ps_timedelta")).ToInt();

		if (config->KeyExists(tmp_name, "ps_winsize"))
			tmpMtl->PS.IsTransWinSize = String(config->GetKey(tmp_name, "ps_winsize")).ToInt();

		if (config->KeyExists(tmp_name, "ps_userdata"))
			tmpMtl->PS.IsTransUserData = String(config->GetKey(tmp_name, "ps_userdata")).ToInt();

		tmpMtl->PS.Param = float4(0, 0, 0, 0);

		if (config->KeyExists(tmp_name, "ps_userdata_value_x"))
			tmpMtl->PS.Param.x = String(config->GetKey(tmp_name, "ps_userdata_value_x")).ToDouble();

		if (config->KeyExists(tmp_name, "ps_userdata_value_y"))
			tmpMtl->PS.Param.y = String(config->GetKey(tmp_name, "ps_userdata_value_y")).ToDouble();

		if (config->KeyExists(tmp_name, "ps_userdata_value_z"))
			tmpMtl->PS.Param.z = String(config->GetKey(tmp_name, "ps_userdata_value_z")).ToDouble();

		if (config->KeyExists(tmp_name, "ps_userdata_value_w"))
			tmpMtl->PS.Param.w = String(config->GetKey(tmp_name, "ps_userdata_value_w")).ToDouble();

		if (config->KeyExists(tmp_name, "ps_userdata_trans_in_vs"))
			tmpMtl->TransPSDataInVS = String(config->GetKey(tmp_name, "ps_userdata_trans_in_vs")).ToBool();

		if (config->KeyExists(tmp_name, "type_reflect"))
			tmpMtl->LightParam.TypeReflect = (MtlTypeReflect)String(config->GetKey(tmp_name, "type_reflect")).ToInt();

		if (config->KeyExists(tmp_name, "alpha_test"))
			tmpMtl->IsAlphaTest = String(config->GetKey(tmp_name, "alpha_test")).ToBool();
		else
			tmpMtl->IsAlphaTest = false;

		return true;
	}

	return false;
}

ID Materials::CreateTexParamLighting(float roughness, float f0)
{
	IDirect3DTexture9* TexMaterial;
	MLSet::DXDevice->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &TexMaterial, NULL);
	D3DLOCKED_RECT LockedRect;
	uint32_t tmpColor = D3DCOLOR_ARGB(0, DWORD(roughness*255.f), DWORD(f0*255.f), 0);

	TexMaterial->LockRect(0, &LockedRect, 0, 0);

	uint32_t* tmpOldColor = (uint32_t*)LockedRect.pBits + 0 * LockedRect.Pitch + 0 * sizeof(uint32_t);
	memcpy(tmpOldColor, &tmpColor, sizeof(uint32_t));

	TexMaterial->UnlockRect(0);

	SGCore_LoadTexLoadTextures();

	char nametex[64];
	sprintf(nametex, "%c_%d_%d_%d", MTL_VIRTUAL_DIR_HAND_MTL, ArrMaterials.size(), rand() % 9999, rand() % 9999);

	return SGCore_LoadTexCreate(nametex, TexMaterial);
}

void Materials::CreateMtl(const char* name, Material** mtl, MtlTypeModel type)
{
	Material* tmpMtl = *mtl;
	new(tmpMtl)Material*;
	//если такого материала не существует, то мы должны были задать примерный тип материала
	tmpMtl->Type = type;
	//обычна¤ геометри¤
	if (type == MtlTypeModel::tms_static)
	{
		tmpMtl->PreShaderVS = SGCore_ShaderGetID(ShaderType::st_vertex, "mtrlgeom_base");
		tmpMtl->PreShaderPS = SGCore_ShaderGetID(ShaderType::st_pixel, "mtrlgeom_base");
		tmpMtl->VS.IsTransWorld = true;
	}
	//деревь¤
	else if (type == MtlTypeModel::tms_tree)
	{
		tmpMtl->PreShaderVS = SGCore_ShaderGetID(ShaderType::st_vertex, "mtrlgreen_base_tree");
		tmpMtl->PreShaderPS = SGCore_ShaderGetID(ShaderType::st_pixel, "mtrlgreen_base");
		//tmpMtl->RenderStates.IsAlphaTest = true;
	}
	//трава
	else if (type == MtlTypeModel::tms_grass)
	{
		tmpMtl->PreShaderVS = SGCore_ShaderGetID(ShaderType::st_vertex, "mtrlgreen_base_grass");
		tmpMtl->PreShaderPS = SGCore_ShaderGetID(ShaderType::st_pixel, "mtrlgreen_base");
		//tmpMtl->RenderStates.IsAlphaTest = true;
	}
	//анимационная модель
	else if (type == MtlTypeModel::tms_skin)
	{
		tmpMtl->PreShaderVS = SGCore_ShaderGetID(ShaderType::st_vertex, "mtrlskin_base");
		tmpMtl->PreShaderPS = SGCore_ShaderGetID(ShaderType::st_pixel, "mtrlskin_base");
		tmpMtl->VS.IsTransWorld = true;
	}
	//источник света
	/*else if (type == MTL_LIGHT)
	{
	tmpMtl->PreShaderVS = SGCore_ShaderGetID(0, "mtrlgeom_base");
	tmpMtl->PreShaderPS = SGCore_ShaderGetID(1, "mtrlgeom_light");
	tmpMtl->IsForwardRender = true;
	tmpMtl->PS.IsTransUserData = true;
	tmpMtl->PS.Param = float4(0, 0, 0, 0);
	}*/

	tmpMtl->MainTexture = SGCore_LoadTexAddName(name, LoadTexType::ltt_load);
	tmpMtl->VS.IsTransWorldViewProjection = true;

	tmpMtl->LightParam.RoughnessValue = MTL_LIGHTING_DEFAULT_ROUGHNESS;
	tmpMtl->LightParam.F0Value = MTL_LIGHTING_DEFAULT_F0;

	tmpMtl->LightParam.ParamTex = -1;
	tmpMtl->LightParam.ParamTexHand = CreateTexParamLighting(tmpMtl->LightParam.RoughnessValue, tmpMtl->LightParam.F0Value);

	//char path[1024];
	char tmp_name[256];
	bool IsTruePath = false;

	for (DWORD k = 0; k<strlen(name); k++)
	{
		if (name[k] == '.')
		{
			sprintf(tmp_name, "%s", name);
			tmp_name[k] = 0;
			IsTruePath = true;
			break;
		}
	}

	sprintf(tmpMtl->Name, "%s", tmp_name);
}

ID Materials::MtlLoad(const char* name, MtlTypeModel type)
{
	ID IsLoad = IsExists(name);

	if (IsLoad >= 0)
	{
		UnitMaterial* tmpumtl = new UnitMaterial();
		tmpumtl->mtl = ArrMaterials[IsLoad]->mtl;

		if (ArrMaterials[IsLoad]->Reflect){
			UnitMaterial* tmpmtl = ArrMaterials[IsLoad];
			tmpumtl->Reflect = new Reflection();
			tmpumtl->Reflect->Init(ArrMaterials[IsLoad]->Reflect->TypeRef);
		}

		return AddUnitMaterial(tmpumtl);
	}
	else
	{
		UnitMaterial* tmpumtl = new UnitMaterial();
		tmpumtl->mtl = new Material();
		AddMaterial(tmpumtl->mtl);
		if (!LoadMtl(name, &(tmpumtl->mtl)))
		{
			CreateMtl(name, &(tmpumtl->mtl), type);
		}
		else
		{
			if (tmpumtl->mtl->LightParam.TypeReflect != MtlTypeReflect::mtr_none)
			{
				tmpumtl->Reflect = new Reflection();
				tmpumtl->Reflect->Init(tmpumtl->mtl->LightParam.TypeReflect);
			}
		}

		ID tmpid = AddUnitMaterial(tmpumtl);

		AddName(name, tmpid);
		return tmpid;
	}
}

void Materials::MtlReLoad(ID id, const char* name)
{
	MTL_PRE_COND_ID(id);
	UnitMaterial* tmpumtl = ArrMaterials[id];
	char tmpname[1024];
	if (name == 0)
		sprintf(tmpname, "%s.dds", tmpumtl->mtl->Name);
	else
		sprintf(tmpname, "%s", name);
	
	tmpumtl->mtl->Nulling();
	if(!LoadMtl(tmpname, &(tmpumtl->mtl)))
	{
		CreateMtl(name, &(tmpumtl->mtl), tmpumtl->mtl->Type);
	}
	else
	{
		if (tmpumtl->mtl->LightParam.TypeReflect != MtlTypeReflect::mtr_none)
		{
			tmpumtl->Reflect = new Reflection();
			tmpumtl->Reflect->Init(tmpumtl->mtl->LightParam.TypeReflect);
		}
	}
}

void Materials::MtlSave(ID id)
{
	MTL_PRE_COND_ID(id);

	char tmp_path[256];//папка
	char tmp_name[256];//само им¤ текстыр с расширением
	bool IsTruePath = false;
	char tmppath[1024];
	char* ArrRGBA[4] = { "r", "g", "b", "a" };

	Material* mtrl = ArrMaterials[id]->mtl;

	IsTruePath = false;
	//обрезаем им¤ текстуры и папку
	for (DWORD k = 0; k<strlen(mtrl->Name); k++)
	{
		if (mtrl->Name[k] == '_')
		{
			memcpy(tmp_path, mtrl->Name, sizeof(char)*k);
			tmp_path[k] = 0;
			sprintf(tmp_name, "%s", mtrl->Name + k + 1);
			IsTruePath = true;
			break;
		}
	}

	for (DWORD k = 0; k<strlen(mtrl->Name); k++)
	{
		if (mtrl->Name[k] == '.')
		{
			sprintf(tmp_name, "%s", mtrl->Name);
			tmp_name[k] = 0;
			IsTruePath = true;
			break;
		}
	}

	tmppath[0] = 0;
	_mkdir(MLSet::StdPathMaterial);
	sprintf(tmppath, "%s%s\\", MLSet::StdPathMaterial, tmp_path);
	_mkdir(tmppath);
	sprintf(tmppath, "%s%s.mtl", tmppath, mtrl->Name);
	FILE* file = 0;
	file = fopen(tmppath, "w");

	fprintf(file, "[%s]\n", mtrl->Name);

	char tmpPathVS[1024];
	char tmpPathPS[1024];

	char tmpPathVSName[1024];
	char tmpPathPSName[1024];

	char tmpPathMaskName[1024];

	SGCore_ShaderGetPath(ShaderType::st_vertex, mtrl->PreShaderVS, tmpPathVSName);
	SGCore_ShaderGetPath(ShaderType::st_pixel, mtrl->PreShaderPS, tmpPathPSName);

	fprintf(file, "type = %d\n", mtrl->Type);
	fprintf(file, "is_inlit = %d\n", mtrl->IsUnlit);
	fprintf(file, "%s%d%s", "physmaterial = ", mtrl->PhysicsMaterial, "\n");

	fprintf(file, "%s%s%s", "vs = ", tmpPathVSName, "\n");
	fprintf(file, "%s%s%s", "ps = ", tmpPathPSName, "\n");

	fprintf(file, "%s%d%s", "alpha_test = ", mtrl->IsAlphaTest, "\n");

	char namebasetex[256];
	namebasetex[0] = '0';
	namebasetex[1] = '\0';
	SGCore_LoadTexGetName(mtrl->MainTexture, namebasetex);
	fprintf(file, "%s%s%s", "texture = ", namebasetex, "\n");

	if (mtrl->MicroDetail.Mask == -1)
	{
		tmpPathMaskName[0] = '0';
		tmpPathMaskName[1] = 0;
	}
	else
		SGCore_LoadTexGetName(mtrl->MicroDetail.Mask, tmpPathMaskName);

	fprintf(file, "%s%s%s", "mask = ", tmpPathMaskName, "\n");

	for (int k = 0; k<4; k++)
	{
		if (mtrl->MicroDetail.ArrMicroDiffuse[k] == -1)
		{
			tmpPathMaskName[0] = '0';
			tmpPathMaskName[1] = 0;
		}
		else
			SGCore_LoadTexGetName(mtrl->MicroDetail.ArrMicroDiffuse[k], tmpPathMaskName);

		fprintf(file, "mirco_diff_%s = %s\n", ArrRGBA[k], tmpPathMaskName);
	}

	for (int k = 0; k<4; k++)
	{
		if (mtrl->MicroDetail.ArrDeatail[k] == -1)
		{
			tmpPathMaskName[0] = '0';
			tmpPathMaskName[1] = 0;
		}
		else
			SGCore_LoadTexGetName(mtrl->MicroDetail.ArrDeatail[k], tmpPathMaskName);

		fprintf(file, "detail_%s = %s\n", ArrRGBA[k], tmpPathMaskName);
	}

	if (mtrl->LightParam.ParamTex == -1)
	{
		tmpPathMaskName[0] = '0';
		tmpPathMaskName[1] = 0;
	}
	else
		SGCore_LoadTexGetName(mtrl->LightParam.ParamTex, tmpPathMaskName);

	if (tmpPathMaskName[0] == MTL_VIRTUAL_DIR_HAND_MTL)
		sprintf(tmpPathMaskName,"0");
	else
		fprintf(file, "is_texture_param = %d\n", mtrl->LightParam.IsTextureParam);

	fprintf(file, "param_ligth = %s\n", tmpPathMaskName);

	fprintf(file, "roughness = %f\n", mtrl->LightParam.RoughnessValue);
	fprintf(file, "f0 = %f\n", mtrl->LightParam.F0Value);

	fprintf(file, "refraction = %d\n", mtrl->LightParam.TypeRefraction);

	fprintf(file, "vs_world = %d\n", mtrl->VS.IsTransWorld);
	fprintf(file, "vs_view = %d\n", mtrl->VS.IsTransView);
	fprintf(file, "vs_projection = %d\n", mtrl->VS.IsTransProjection);
	fprintf(file, "vs_worldview = %d\n", mtrl->VS.IsTransWorldView);
	fprintf(file, "vs_worldviewprojection = %d\n", mtrl->VS.IsTransWorldViewProjection);

	fprintf(file, "vs_poscam = %d\n", mtrl->VS.IsTransPosCam);
	fprintf(file, "vs_timedelta = %d\n", mtrl->VS.IsTransTimeDelta);
	fprintf(file, "vs_winsize = %d\n", mtrl->VS.IsTransWinSize);
	fprintf(file, "vs_userdata = %d\n", mtrl->VS.IsTransUserData);
	fprintf(file, "vs_userdata_value_x = %f\nvs_userdata_value_y = %f\nvs_userdata_value_z = %f\nvs_userdata_value_w = %f\n", mtrl->VS.Param.x, mtrl->VS.Param.y, mtrl->VS.Param.z, mtrl->VS.Param.w);
	fprintf(file, "vs_userdata_trans_in_ps = %d\n", mtrl->TransVSDataInPS);

	fprintf(file, "ps_world = %d\n", mtrl->PS.IsTransWorld);
	fprintf(file, "ps_view = %d\n", mtrl->PS.IsTransView);
	fprintf(file, "ps_projection = %d\n", mtrl->PS.IsTransProjection);
	fprintf(file, "ps_worldview = %d\n", mtrl->PS.IsTransWorldView);
	fprintf(file, "ps_worldviewprojection = %d\n", mtrl->PS.IsTransWorldViewProjection);

	fprintf(file, "ps_poscam = %d\n", mtrl->PS.IsTransPosCam);
	fprintf(file, "ps_timedelta = %d\n", mtrl->PS.IsTransTimeDelta);
	fprintf(file, "ps_winsize = %d\n", mtrl->PS.IsTransWinSize);
	fprintf(file, "ps_userdata = %d\n", mtrl->PS.IsTransUserData);
	fprintf(file, "ps_userdata_value_x = %f\nps_userdata_value_y = %f\nps_userdata_value_z = %f\nps_userdata_value_w = %f\n", mtrl->PS.Param.x, mtrl->PS.Param.y, mtrl->PS.Param.z, mtrl->PS.Param.w);
	fprintf(file, "ps_userdata_trans_in_vs = %d\n", mtrl->TransPSDataInVS);

	fprintf(file, "type_reflect = %d\n", mtrl->LightParam.TypeReflect);

	fprintf(file, "\n");
	fclose(file);
}

void Materials::Update(DWORD timeDelta)
{
	CurrTimeDelta = timeDelta;
	CountTimeDelta += timeDelta;
}

void Materials::SetMainTexture(ID slot, ID id)
{
	if (id >= 0 && id < ArrMaterials.size() && ArrMaterials[id]->mtl->MainTexture != -1)
		MLSet::DXDevice->SetTexture(slot, SGCore_LoadTexGetTex(ArrMaterials[id]->mtl->MainTexture));
	else
		MLSet::DXDevice->SetTexture(slot, 0);
}

ID Materials::GetID(const char* name)
{
	for (long i = 0; i<ArrMaterials.size(); i++)
	{
		if (strcmp(ArrMaterials[i]->mtl->Name, name) == 0)
			return i;
	}
	return -1;
}

inline long Materials::GetCount()
{
	return ArrMaterials.size();
}

inline void Materials::SetForceblyAlphaTest(bool isat)
{
	IsForceblyAlphaTest = isat;
	if (!isat)
		MLSet::DXDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

inline bool Materials::GetForceblyAlphaTest()
{
	return IsForceblyAlphaTest;
}

inline void Materials::SetIsIncrCountSurf(bool bf)
{
	IsIncrCountSurf = bf;
}

inline bool Materials::GetIsIncrCountSurf()
{
	return IsIncrCountSurf;
}

inline void Materials::NullingCurrCountSurf()
{
	CurrIdSurf = 0;
}

inline int Materials::GetCurrCountSurf()
{
	return CurrIdSurf;
}

inline void Materials::SetCurrCountSurf(int count)
{
	CurrIdSurf = count;
}

void Materials::RenderStd(MtlTypeModel type, float4x4* world, ID slot, ID id_mtl)
{
	//может быть случай когда текстура в которую сейчас рисуем еще стоит в текстурных слотах
	//из-за этого может быть необъяснимое поводенеие и как результат непонятные артефакты в самой текстуре в которую сейчас рисуем
	//поэтому нужно обнулить слот в котором возможно была текстура
	//такое явление может быть в случае когда в кадре только один материал который отражает
	MLSet::DXDevice->SetTexture(MTL_TEX_R_REFLECTION, 0);

	if (id_mtl >= 0 && id_mtl < ArrMaterials.size())
		this->SetMainTexture(slot, id_mtl);

	if (type == MtlTypeModel::tms_static)
	{
		SGCore_ShaderBind(ShaderType::st_vertex, MLSet::IDsShaders::VS::StdGeom);

		float4x4 wmat = (world ? (*world) : SMMatrixIdentity());
		float4x4 wvpmat;
		Core_RMatrixGet(G_RI_MATRIX_VIEWPROJ, &wvpmat);
		wvpmat = SMMatrixTranspose(wmat * wvpmat);
		wmat = SMMatrixTranspose(wmat);

		SGCore_ShaderSetVRF(ShaderType::st_vertex, MLSet::IDsShaders::VS::StdGeom, "WorldViewProjection", &wvpmat);
		SGCore_ShaderSetVRF(ShaderType::st_vertex, MLSet::IDsShaders::VS::StdGeom, "World", &wmat);

		if (Core_RBoolGet(G_RI_BOOL_CLIPPLANE0))
		{
			SGCore_ShaderBind(ShaderType::st_pixel, MLSet::IDsShaders::PS::StdGeomCP);

			float3 tmpnormal, tmppoint;

			Core_RFloat3Get(G_RI_FLOAT3_CLIPPLANE0_NORMAL, &tmpnormal);
			Core_RFloat3Get(G_RI_FLOAT3_CLIPPLANE0_POINT, &tmppoint);

			SGCore_ShaderSetVRF(ShaderType::st_pixel, MLSet::IDsShaders::PS::StdGeomCP, "PlaneNormal", &tmpnormal);
			SGCore_ShaderSetVRF(ShaderType::st_pixel, MLSet::IDsShaders::PS::StdGeomCP, "PlanePoint", &tmppoint);
		}
		else
			SGCore_ShaderBind(ShaderType::st_pixel, MLSet::IDsShaders::PS::StdGeom);
	}
	else if (type == MtlTypeModel::tms_grass || type == MtlTypeModel::tms_tree)
	{
		ID tmpvs = (type == MtlTypeModel::tms_grass ? MLSet::IDsShaders::VS::StdGrass : MLSet::IDsShaders::VS::StdTree);
		SGCore_ShaderBind(ShaderType::st_vertex, tmpvs);

		float4x4 wmat = (world ? (*world) : SMMatrixIdentity());
		float4x4 wvpmat;
		Core_RMatrixGet(G_RI_MATRIX_VIEWPROJ, &wvpmat);
		wvpmat = SMMatrixTranspose(wmat * wvpmat);
		wmat = SMMatrixTranspose(wmat);

		SGCore_ShaderSetVRF(ShaderType::st_vertex, tmpvs, "WorldViewProjection", &wvpmat);
		SGCore_ShaderSetVRF(ShaderType::st_vertex, tmpvs, "World", &wmat);

		if (Core_RBoolGet(G_RI_BOOL_CLIPPLANE0))
		{
			SGCore_ShaderBind(ShaderType::st_pixel, MLSet::IDsShaders::PS::StdGreenCP);

			float3 tmpnormal, tmppoint;

			Core_RFloat3Get(G_RI_FLOAT3_CLIPPLANE0_NORMAL, &tmpnormal);
			Core_RFloat3Get(G_RI_FLOAT3_CLIPPLANE0_POINT, &tmppoint);

			SGCore_ShaderSetVRF(ShaderType::st_pixel, MLSet::IDsShaders::PS::StdGreenCP, "PlaneNormal", &tmpnormal);
			SGCore_ShaderSetVRF(ShaderType::st_pixel, MLSet::IDsShaders::PS::StdGreenCP, "PlanePoint", &tmppoint);
		}
		else
			SGCore_ShaderBind(ShaderType::st_pixel, MLSet::IDsShaders::PS::StdGreen);
	}
	else if (type == MtlTypeModel::tms_skin)
	{
		SGCore_ShaderBind(ShaderType::st_vertex, MLSet::IDsShaders::VS::StdSkin);

		float4x4 wmat = (world ? (*world) : SMMatrixIdentity());
		float4x4 wvpmat;
		Core_RMatrixGet(G_RI_MATRIX_VIEWPROJ, &wvpmat);
		wvpmat = SMMatrixTranspose(wmat * wvpmat);
		wmat = SMMatrixTranspose(wmat);

		SGCore_ShaderSetVRF(ShaderType::st_vertex, MLSet::IDsShaders::VS::StdSkin, "WorldViewProjection", &wvpmat);
		SGCore_ShaderSetVRF(ShaderType::st_vertex, MLSet::IDsShaders::VS::StdSkin, "World", &wmat);

		if (Core_RBoolGet(G_RI_BOOL_CLIPPLANE0))
		{
			SGCore_ShaderBind(ShaderType::st_pixel, MLSet::IDsShaders::PS::StdSkinCP);

			float3 tmpnormal, tmppoint;

			Core_RFloat3Get(G_RI_FLOAT3_CLIPPLANE0_NORMAL, &tmpnormal);
			Core_RFloat3Get(G_RI_FLOAT3_CLIPPLANE0_POINT, &tmppoint);

			SGCore_ShaderSetVRF(ShaderType::st_pixel, MLSet::IDsShaders::PS::StdSkinCP, "PlaneNormal", &tmpnormal);
			SGCore_ShaderSetVRF(ShaderType::st_pixel, MLSet::IDsShaders::PS::StdSkinCP, "PlanePoint", &tmppoint);
		}
		else
			SGCore_ShaderBind(ShaderType::st_pixel, MLSet::IDsShaders::PS::StdSkin);
	}
}

void Materials::Render(ID id, float4x4* world)
{
	MTL_PRE_COND_ID(id);

	if (!world)
		world = &(SMMatrixIdentity());

	Material* tmpmaterial = ArrMaterials[id]->mtl;

	//если есть то устанавливаем текстуру материала
	if (tmpmaterial->MainTexture != -1)
		MLSet::DXDevice->SetTexture(MTL_TEX_R_MAIN, SGCore_LoadTexGetTex(tmpmaterial->MainTexture));

	//если нет отражени¤ то отправл¤ем 0
	if (tmpmaterial->LightParam.TypeReflect == 0)
		MLSet::DXDevice->SetTexture(MTL_TEX_R_REFLECTION, 0);
	else
	{
		if (ArrMaterials[id]->Reflect->TypeRef == MtlTypeReflect::mtr_plane)
			MLSet::DXDevice->SetTexture(MTL_TEX_R_REFLECTION, ArrMaterials[id]->Reflect->GetRefPlaneTex());
		else if (ArrMaterials[id]->Reflect->TypeRef == MtlTypeReflect::mtr_cube_static || ArrMaterials[id]->Reflect->TypeRef == MtlTypeReflect::mtr_cube_dynamic)
			MLSet::DXDevice->SetTexture(MTL_TEX_R_REFLECTION, ArrMaterials[id]->Reflect->GetRefCubeTex());
	}

	MLSet::DXDevice->SetTexture(MTL_TEX_R_CURR_DEPTH, SGCore_RTGetTexture(MLSet::IDsRenderTargets::DepthScene0));

	//если есть рефаркци¤, а она идет вторым проходом, то отправл¤ем, иначе посылаем 0
	/*if (tmpmaterial->LightParam.TypeRefraction)
		MLSet::DXDevice->SetTexture(MTL_TEX_R_REFRACTION, SGCore_RTGetTexture(SML_DSGetRT_ID(DS_RT_SCENE_LIGHT_COM_REF)));
	else
		MLSet::DXDevice->SetTexture(MTL_TEX_R_REFRACTION, 0);*/

	if (tmpmaterial->MicroDetail.Mask != -1)
		MLSet::DXDevice->SetTexture(MTL_TEX_R_MASK, SGCore_LoadTexGetTex(tmpmaterial->MicroDetail.Mask));

	for (int k = 0; k<4; k++)
	{
		if (tmpmaterial->MicroDetail.ArrDeatail[k] != -1)
			MLSet::DXDevice->SetTexture(MTL_TEX_R_DETAIL + k, SGCore_LoadTexGetTex(tmpmaterial->MicroDetail.ArrDeatail[k]));
		else
			MLSet::DXDevice->SetTexture(MTL_TEX_R_DETAIL + k, 0);

		if (tmpmaterial->MicroDetail.ArrMicroDiffuse[k] != -1)
			MLSet::DXDevice->SetTexture(MTL_TEX_R_MICRO + k, SGCore_LoadTexGetTex(tmpmaterial->MicroDetail.ArrMicroDiffuse[k]));
		else
			MLSet::DXDevice->SetTexture(MTL_TEX_R_MICRO + k, 0);
	}

	//если есть текстура с параметрами освещени¤ и установлено что берем параметры из текстуры, то отправл¤ем текстуру с параметрами
	if (tmpmaterial->LightParam.ParamTex != -1 && tmpmaterial->LightParam.IsTextureParam)
	{
		MLSet::DXDevice->SetTexture(MTL_TEX_R_PARAM_LIGHT, SGCore_LoadTexGetTex(tmpmaterial->LightParam.ParamTex));
	}
	//иначе если берем параметры из ... редактора
	else if (!tmpmaterial->LightParam.IsTextureParam)
	{
		if (tmpmaterial->LightParam.OldRoughnessValue != tmpmaterial->LightParam.RoughnessValue || tmpmaterial->LightParam.OldF0Value != tmpmaterial->LightParam.F0Value)
		{
			//блокируем текстуру 1х1 котора¤ есть параметры освещени¤, и запсиываем туда то что настроили
			D3DLOCKED_RECT LockedRect;
			IDirect3DTexture9* ParamLightModelTex = SGCore_LoadTexGetTex(tmpmaterial->LightParam.ParamTexHand);
			ParamLightModelTex->LockRect(0, &LockedRect, 0, 0);
			DWORD *param = (DWORD*)LockedRect.pBits;
			//DWORD param = D3DCOLOR_ARGB(0,0,0,0);
			param[0] = D3DCOLOR_ARGB(0, DWORD(tmpmaterial->LightParam.RoughnessValue*255.f), DWORD(tmpmaterial->LightParam.F0Value*255.f), 0);
			ParamLightModelTex->UnlockRect(0);

			tmpmaterial->LightParam.OldRoughnessValue = tmpmaterial->LightParam.RoughnessValue;
			tmpmaterial->LightParam.OldF0Value = tmpmaterial->LightParam.F0Value;
		}

		MLSet::DXDevice->SetTexture(MTL_TEX_R_PARAM_LIGHT, SGCore_LoadTexGetTex(tmpmaterial->LightParam.ParamTexHand));
	}
	else
		MLSet::DXDevice->SetTexture(MTL_TEX_R_PARAM_LIGHT, SGCore_LoadTexGetTex(MLSet::IDsTexs::NullMaterial));


	if (tmpmaterial->PreShaderVS != -1)
		SGCore_ShaderBind(ShaderType::st_vertex, tmpmaterial->PreShaderVS);

	if (tmpmaterial->PreShaderPS != -1)
		SGCore_ShaderBind(ShaderType::st_pixel, tmpmaterial->PreShaderPS);

	if (tmpmaterial->VS.IsTransWorld || tmpmaterial->PS.IsTransWorld || tmpmaterial->VS.IsTransWorldView || tmpmaterial->PS.IsTransWorldView || tmpmaterial->VS.IsTransWorldViewProjection || tmpmaterial->PS.IsTransWorldViewProjection)
		worldtrans = SMMatrixTranspose(*world);

	if (tmpmaterial->VS.IsTransWorldView || tmpmaterial->PS.IsTransWorldView || tmpmaterial->VS.IsTransWorldViewProjection || tmpmaterial->PS.IsTransWorldViewProjection)
	{
		float4x4 view;
		Core_RMatrixGet(G_RI_MATRIX_VIEW, &view);
		//MLSet::DXDevice->GetTransform(D3DTS_VIEW, &tmpView);
		//view = float4x4(tmpView);
		viewtrans = SMMatrixTranspose(view);

		float4x4 proj;
		Core_RMatrixGet(G_RI_MATRIX_PROJECTION, &proj);
		//MLSet::DXDevice->GetTransform(D3DTS_PROJECTION, &tmpProjection);
		//proj = float4x4(tmpProjection);
		projtrans = SMMatrixTranspose(proj);
	}

	if (tmpmaterial->VS.IsTransWorld)
		SGCore_ShaderSetVRF(ShaderType::st_vertex, tmpmaterial->PreShaderVS, "World", &worldtrans);

	if (tmpmaterial->PS.IsTransWorld)
		SGCore_ShaderSetVRF(ShaderType::st_pixel, tmpmaterial->PreShaderPS, "World", &worldtrans);

	if (tmpmaterial->VS.IsTransView)
		SGCore_ShaderSetVRF(ShaderType::st_vertex, tmpmaterial->PreShaderVS, "View", &viewtrans);

	if (tmpmaterial->PS.IsTransView)
		SGCore_ShaderSetVRF(ShaderType::st_pixel, tmpmaterial->PreShaderPS, "View", &viewtrans);

	if (tmpmaterial->VS.IsTransProjection)
		SGCore_ShaderSetVRF(ShaderType::st_vertex, tmpmaterial->PreShaderVS, "Projection", &projtrans);

	if (tmpmaterial->PS.IsTransProjection)
		SGCore_ShaderSetVRF(ShaderType::st_pixel, tmpmaterial->PreShaderPS, "Projection", &projtrans);


	if (tmpmaterial->VS.IsTransWorldView || tmpmaterial->PS.IsTransWorldView)
	{
		float4x4 wv = viewtrans * worldtrans;

		if (tmpmaterial->VS.IsTransWorldView)
			SGCore_ShaderSetVRF(ShaderType::st_vertex, tmpmaterial->PreShaderVS, "WorldView", &wv);

		if (tmpmaterial->PS.IsTransWorldView)
			SGCore_ShaderSetVRF(ShaderType::st_pixel, tmpmaterial->PreShaderPS, "WorldView", &wv);
	}

	if (tmpmaterial->VS.IsTransWorldViewProjection || tmpmaterial->PS.IsTransWorldViewProjection)
	{
		float4x4 tmpVP;
		Core_RMatrixGet(G_RI_MATRIX_VIEWPROJ, &tmpVP);
		//MLSet::DXDevice->GetTransform(D3DTS_WORLD1, &tmpVP);

		float4x4 wvp = (*world) * tmpVP;
		wvp = SMMatrixTranspose(wvp);

		if (tmpmaterial->VS.IsTransWorldViewProjection)
			SGCore_ShaderSetVRF(ShaderType::st_vertex, tmpmaterial->PreShaderVS, "WorldViewProjection", &wvp);

		if (tmpmaterial->PS.IsTransWorldViewProjection)
			SGCore_ShaderSetVRF(ShaderType::st_pixel, tmpmaterial->PreShaderPS, "WorldViewProjection", &wvp);
	}

	if (tmpmaterial->VS.IsTransPosCam || tmpmaterial->PS.IsTransPosCam)
	{
		if (tmpmaterial->VS.IsTransPosCam)
			SGCore_ShaderSetVRF(ShaderType::st_vertex, tmpmaterial->PreShaderVS, "PosCam", &MLSet::ConstCurrCamPos);

		if (tmpmaterial->PS.IsTransPosCam)
			SGCore_ShaderSetVRF(ShaderType::st_pixel, tmpmaterial->PreShaderPS, "PosCam", &MLSet::ConstCurrCamPos);
	}


	if (tmpmaterial->VS.IsTransUserData)
		SGCore_ShaderSetVRF(ShaderType::st_vertex, tmpmaterial->PreShaderVS, "Param", &(tmpmaterial->VS.Param));

	if (tmpmaterial->TransVSDataInPS)
		SGCore_ShaderSetVRF(ShaderType::st_pixel, tmpmaterial->PreShaderPS, "ParamVS", &(tmpmaterial->VS.Param));

	if (tmpmaterial->PS.IsTransUserData)
		SGCore_ShaderSetVRF(ShaderType::st_pixel, tmpmaterial->PreShaderPS, "Param", &(tmpmaterial->PS.Param));

	if (tmpmaterial->TransPSDataInVS)
		SGCore_ShaderSetVRF(ShaderType::st_vertex, tmpmaterial->PreShaderVS, "ParamPS", &(tmpmaterial->PS.Param));

	if (tmpmaterial->VS.IsTransTimeDelta)
		SGCore_ShaderSetVRF(ShaderType::st_vertex, tmpmaterial->PreShaderVS, "TimeDelta", &float2(CountTimeDelta, float(CurrTimeDelta) * 0.001f));

	if (tmpmaterial->PS.IsTransTimeDelta)
		SGCore_ShaderSetVRF(ShaderType::st_pixel, tmpmaterial->PreShaderPS, "TimeDelta", &float2(CountTimeDelta, float(CurrTimeDelta) * 0.001f));

	if (tmpmaterial->VS.IsTransWinSize)
		SGCore_ShaderSetVRF(ShaderType::st_vertex, tmpmaterial->PreShaderVS, "WinSize", &MLSet::WinSize);

	if (tmpmaterial->PS.IsTransWinSize)
		SGCore_ShaderSetVRF(ShaderType::st_pixel, tmpmaterial->PreShaderPS, "WinSize", &MLSet::WinSize);

	//если материалом назначен альфа тест и не включен принудительный
	if (tmpmaterial->IsAlphaTest && !IsForceblyAlphaTest)
	{
		MLSet::DXDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		MLSet::DXDevice->SetRenderState(D3DRS_ALPHAREF, MTL_ALPHATEST_FREE_VALUE);
		MLSet::DXDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	}
	//если не включен принудительный альфа тест
	else if (!IsForceblyAlphaTest)
	{
		MLSet::DXDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
	//иначе включен принудительный альфа тест
	else
	{
		MLSet::DXDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		MLSet::DXDevice->SetRenderState(D3DRS_ALPHAREF, MTL_ALPHATEST_FORCEBLY_VALUE);
		MLSet::DXDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	}

	

	//почти во всех пиксельных шейдерах материалов есть данна¤ NearFar, необходима¤ д¤л записи глубины
	if (tmpmaterial->PreShaderPS != -1)
	{	
		//освещаемый ли тип материала или нет? Ппрозрачный освещаемый?
		//0,0.33,0.66,1
		float zz;
		if (tmpmaterial->IsUnlit)
		{
			if (tmpmaterial->LightParam.TypeRefraction == MtlTypeTransparency::mtt_none)
				zz = 0.0;
			else
				zz = 0.66;
		}
		else
		{
			if (tmpmaterial->LightParam.TypeRefraction == MtlTypeTransparency::mtt_none)
				zz = 0.33;
			else
				zz = 1;
		}

		if (tmpmaterial->LightParam.TypeRefraction == mtt_alpha_lighting)
			++(CurrIdSurf);

		SGCore_ShaderSetVRF(ShaderType::st_pixel, tmpmaterial->PreShaderPS, "NearFarIsUnlit", &float4_t(MLSet::NearFar.x, MLSet::NearFar.y, zz, float(CurrIdSurf)/255.f));
	}
}

void Materials::RenderLight(float4_t* color, float4x4* world)
{
	MTL_PRE_COND_ID(MtrlDefLight);

	ArrMaterials[MtrlDefLight]->mtl->PS.Param = *color;
	Render(MtrlDefLight, world);
	ArrMaterials[MtrlDefLight]->mtl->PS.Param = float4(0, 0, 0, 0);
}
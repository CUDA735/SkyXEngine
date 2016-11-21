
//��������� ��� ���������
float4x4 ConstPDMatrixIdentity = SMMatrixIdentity();

float3 ConstPDRot_1 = float3(ConstPDMatrixIdentity._11,ConstPDMatrixIdentity._12,ConstPDMatrixIdentity._13);
float3 ConstPDRot_2 = float3(ConstPDMatrixIdentity._21,ConstPDMatrixIdentity._22,ConstPDMatrixIdentity._23);
float3 ConstPDRot_3 = float3(ConstPDMatrixIdentity._31,ConstPDMatrixIdentity._32,ConstPDMatrixIdentity._33);

//��������� ����������� �������
struct CommonParticle
{
	SX_ALIGNED_OP_MEM

	CommonParticle()
	{
		Age = 0;
		TimeLife = 0;
		RateMls = 0;
		CurrentMls = 0;
		CurrentCadr = 0;
		IsAlifeAlpha = 0;
		this->IsAlife = false;
		AnimSizeCadrAndBias = float4(1,1,0,0);
		AlphaDispersion = 0.f;

		Ambient = float4(1,1,1,1);

		float4x4 matidentity = SMMatrixIdentity();

		rot_1 = float3(matidentity._11,matidentity._12,matidentity._13);
		rot_2 = float3(matidentity._21,matidentity._22,matidentity._23);
		rot_3 = float3(matidentity._31,matidentity._32,matidentity._33);
	}

	float3 CreatePos;
	float3 Pos;		//�������
	DWORD Age;		//������� ������� � �����
	DWORD TimeLife;	//����� ����� ������� � �����

	float4 Ambient;

	float4 Size;
	float4 AnimSizeCadrAndBias;

	WORD CurrentCadr;
	DWORD RateMls;
	DWORD CurrentMls;

	float3 rot_1;
	float3 rot_2;
	float3 rot_3;

	float3 DeviationVector;

	float3 Velocity;		//��������
	float3 Acceleration;	//���������
	
	float IsAlifeAlpha;
	float AlphaDispersion;

	bool IsAlife;
};

//�������� ������������� ������� � �������
struct CommonParticleDecl
{
	CommonParticleDecl(float posx,float posy,float posz,float texx,float texy)
	{
		pos.x = posx;
		pos.y = posy;
		pos.z = posz;

		tex.x = texx;
		tex.y = texy;
	}

	float3_t pos;
	float2_t tex;
};

//������������� ������� ��� ����������� � �������
struct CommonParticleDecl2
{
	float3_t pos;
	float4_t tex;
	float2_t size;
	float alpha;

	float3_t rot_1;
	float3_t rot_2;
	float3_t rot_3;

	float4_t lighting;
};

class EffParticles
{
public:

	EffParticles();
	~EffParticles();

	SX_ALIGNED_OP_MEM

	void Create(int count_particles);
	void ReInitArrParticles(int count_particles);
	void ReRun();
	void CreateParticles();
	inline void ReCreateParticles(WORD id);
	void Compute();
	void ComputeLighting();
	void Render(DWORD timeDelta,float4x4* worldmat,float4x4* matrot,float4x4* matpos);

	///////////////////
	//��������� �������������� �������
	void SetBoundSphere(float3* center,float radius);
	void SetBoundBox(float3* center,float data_x,float data_y,float data_z);
	//��������� ������� ������ ������� �� ������� ��������������� ������
	BYTE ComOutBound;	//0 - �� ������������, 1 - �����, 2 - �������������, 3 - �����
	Graphics::ThreeD::Bound BoundVolume;

	inline void SetBoundCone(float3* begin,float3* end,float begin_r,float end_r);
	inline bool IsPointInCone(float3* point);
	float3 BeginCone;
	float3 EndCone;
	float BeginRadiusCone;
	float EndRadiusCone;

	//��� �������� ��������
	//0 - � ��������� �����
	//1 - ����������� ��������� �����
	//� ������� � �������������� ������� �� ����� ������
	BYTE HowSpawn;

	//�������� ���������� �������� ������ � ����
	//��� �������������� �������
	bool BindCreateXNeg;
	bool BindCreateXPos;
	bool BindCreateYNeg;
	bool BindCreateYPos;
	bool BindCreateZNeg;
	bool BindCreateZPos;

	//���������� ���������� ������� ����� ������� ����� ���������� ��������� �������
	//0 - ������� ��� �����
	void SetTimeSpawn(WORD ttime,WORD dispersion_time);
	WORD TimeSpawn;
	WORD DistTimeSpawn;

	//����� ����������
	//����������� ������ ���� ����� ������ ���� ����� ������
	inline void SetOutOrigin(float3* origin,bool is_rand=false,float dispersion=0);
	float3 Origin;		//����� �� ������� ���� �������
	bool IsRandOrigin;	//��������� ������� �������
	float DispersionOfOrigin;
	/////////////////////


	///////
	bool IsSoft;			//������ �� �������
	float SoftCoef;			
	bool IsRefraction;		//������� ���������� ������������
	float RefractionCoef;
	bool IsLighting;		//���������� �� �������
	float LightingCoefAmbient;
	float LightingCoefIntens;
	///////

	///////
	//�� ����� ��� ����� ������� �������
	//rot_how == 0 �� ��� �� angle ��������� ���, == 1 �������� ���������, == 2 ���������� ��������� �� angle
	inline void SetRotateMarkX(int rot_how,float angle=0);
	inline void SetRotateMarkY(int rot_how,float angle=0);
	inline void SetRotateMarkZ(int rot_how,float angle=0);
	inline void SetRotateMarkBillboard(bool is_billboard);

	int RotXHow;
	int RotYHow;
	int RotZHow;
	float RotAngleX;
	float RotAngleY;
	float RotAngleZ;

	float OldRotAngleX;
	float OldRotAngleY;
	float OldRotAngleZ;

	bool IsBillboard;
	//////
	
	//��� ��� ��������� � ������� ������������� ��������
	void SetAnimTexData(DWORD idtex,WORD count_cadrs_x,WORD count_cadrs_y,WORD rate,WORD dispersion=0,WORD start_cadr=0,WORD disp_of_cadr=0);
	void UpdateAnimTex(WORD idparticle,DWORD tmptime);
	float2 AnimTexSize;	//������ ��������
	float4 AnimSizeCadr;//������ ������ �����, xy - � ��������, zw - � ���������� ����������� � ������� ��������
	//���������� ������ �� ����
	WORD CountCadrsX;
	WORD CountCadrsY;

	WORD RateAnimTex;			//������� ����������
	WORD DispersionOfRate;		//������� ������� ����������
	WORD StartCadr;				//��������� ����
	WORD DispersionOfStartCadr;	//������� ��� ���������� �����
	/////////////////

	

	//����� ����� ������
	//time_life == 0 ����� ������� ����� ��� �����, ����� ��� ����� � ����������
	//is_dead_out_bound ������� �� ������� ���� �� �������������� ����� ��������
	//is_rand �������� ���������� ����� ����� ������ �� ������ time_life � ��������� � +-dispersion
	inline void SetTimeLife(DWORD time_life,bool is_rand=false,DWORD dispersion=0);
	DWORD TimeLife;
	DWORD TimeLifeDispersion;
	///////////////

	////////////////////////////////////////////

	//����������� ������������  ������ �� ��������
	inline void SetDependAlphaAge(int depend,float alpha_disp=0,WORD alpha_display=0);
	float AlphaDispersion;		//��������� ������� �����
	WORD AlphaDisplay;
	int IsDependenceAlphaAge;	//������� �� ����� ���������� ������� �� �� ��������, 0 - ���, 1, ��������� ��� ������, -1 - ��� ������ ��� ������
	/////////////

	//������ ������
	inline void SetSize(float2* size,bool is_rand=false,float dispersion=0,int depend=0);
	float2 SizeParticle;
	float DispersionOfSize;	//������� ��� ������� ������

	int IsDependenceSizeAge;	//������� �� ����� ���������� ������� �� �� ��������, 0 - ���, 1, ��������� ��� ������, -1 - ��� ������ ��� ������
	///////////

	//��������
	inline void SetVelocity(float3* velocity,int is_rand,bool is_x_neg=true,bool is_y_neg=true,bool is_z_neg=true,float dispersion=0);
	float3 Velocity;
	int RandOfVelocity;
	float DispersionOfVelocity;

	bool IsXNegVelocity;
	bool IsYNegVelocity;
	bool IsZNegVelocity;
	/////

	//���������
	inline void SetAcceleration(float3* acc,int is_rand,bool is_x_neg=true,bool is_y_neg=true,bool is_z_neg=true,float dispersion=0);
	float3 Acceleration;
	int RandOfAcceleration;
	float DispersionOfAcceleration;

	//����� �� ���� ������������� ���������?
	bool IsXNegAcceleration;
	bool IsYNegAcceleration;
	bool IsZNegAcceleration;
	/////


	//
	inline void SetCharacterCircle(bool character_circle,float angle=0,int is_rand=0,float disp_angle=0);
	bool CharacterCircle;
	float AngleCircle;
	int RandCircle;
	float DispersionOfCircle;
	///////////

	//
	inline void SetCharacterRotate(bool character_rotate,float angle=0,int is_rand=0,float disp_angle=0);
	bool CharacterRotate;
	float AngleRotate;
	int RandRotate;
	float DispersionOfRotate;
	float AngleRotateZ;
	/////////

	//
	//amplitude - ���������, ����� ���� ������������
	//coef_angle - ���������� �� ������� ����� ������� ����
	//tap_ - ������������� �� ����������, false - ���, true - �� ������������
	//motion_axis - �� ����� ��� ����� �������� ��������
	//delay - ��� ��������, 0 - ���������,1 - ����� ���, 2 - ��������
	//count_delay - ����� �������� � ������� ��������
	inline void SetCharacterMotion(
									bool character_motion,
									float amplitude=0,
									float coef_angle=0,
									bool tap_x=0,
									bool tap_y=0,
									bool tap_z=0,
									int motion_axis=0,
									int is_rand=0,
									float disp=0,
									int delay=0,
									DWORD count_delay=1000);
	bool CharacterMotion;
	float AmplitudeMotion;
	float CoefAngleMotion;
	DWORD CountDelayMls;
	DWORD CountDelayMls2;
	int RandMotion;
	float DispersionOfMotion;
	int DelayMotion;
	int AxisMotion;

	bool TapMotionX;
	bool TapMotionY;
	bool TapMotionZ;
	/////////


//protected:
	DWORD IDTex;		//id ��������, ����� �� ��� �������� �������� ������������
	DWORD OldTime;		//������� ����� � �������� �������� ���������
	DWORD TimeNextSpawnParticle;	//����� ������ �������� ��������
	long CountReCreate;	//������� ����������� ������, ������� ������, ���� 0 �� �� ����������� ������
	long CountReCreate2;//������� ����������

	char Name[256];

	DWORD CountLifeParticle;	//���������� ����� ������
	bool IsAlife;				//���� �� ���? ���� false � ���� �������� ������

	CommonParticle* Arr;
	int Count;

	IDirect3DVertexBuffer9* TransVertBuf;

	IDirect3DVertexBuffer9* VertexBuff;
	IDirect3DIndexBuffer9* IndexBuff;
};

////////////////


class EffEffect
{
public:
	EffEffect();
	EffEffect(EffEffect& eff);
	~EffEffect();

	SX_ALIGNED_OP_MEM

	inline DWORD GetCount();
	void Delete(DWORD id);

	inline void SetSound(const char* path);
	inline void GetSound(char* path);
	inline void SetSoundRMin(float rmin);
	inline void SetSoundRMax(float rmin);

	inline float GetSoundRMin();
	inline float GetSoundRMax();

	void Compute();
	void Render(DWORD timeDelta);

	inline bool Enable(){return IsEnable;};
	inline void Enable(bool isenable);

	inline void SetPosition(float3* pos);
	inline void SetDirection(float3* dir);
	inline void SetRotation(float3* rot);
	
	inline void GetPosition(float3* pos);
	inline void GetDirection(float3* dir);
	inline void GetRotation(float3* rot);

	//����������� � ������� �� ���������, pos ������ ������������ ��� ����� ������������� �������, ���� 0 - ���� ������� ����
	inline void SetBindPosAdrVector(float3* pos);
	//��������� �������� ������� �������
	inline void SetBindBasePosAdrVector(float3* pos);
	inline float3* GetBindPosAdrVector();

	//
	inline void SetBindDirAdrVector(float3* dir);
	inline void SetBindBaseDirAdrVector(float3* dir);

	//inline void SetSound(const char* path,);

	inline bool IsVisible(Core::ControllMoving::Frustum* frustum);
	bool IsComVisible;
	void ComAllBound();

	float3 Position,Direction,Rotation;
	float4x4 MatTranslation;
	float4x4 MatRotate;
	float4x4 MatTransform;

	float3* BindPos;
	float3 BindBasePos;

	float DistForCamera;
	bool IsRenderForCamera;

	ID3DXMesh* MeshBound;
	void SetLight(float4* color,float dist,bool is_shadow);
	void DeleteLight();
	void EnableLight(bool is_enable);
	DWORD IDLight;
	DWORD ID;
	bool IsActive;
	char NameEffect[256];
	char Name[256];
	bool IsEnable;
	Array<EffParticles*> Arr;
	Graphics::ThreeD::Bound BoundVolume;

	DWORD IDSound;
};

///////////////

class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	bool TraceBeam(const float3 & start, const float3 & dir, float3 * _res,DWORD* idlight);

	inline DWORD GetCountParticles();
	void DeleteParticles(DWORD id);

	inline DWORD GetCountEffects();
	void DeleteEffects(DWORD id);

	void Compute();
	void ComVisible();
	void Render(DWORD timeDelta);
	void RenderVolume();

	Array<EffEffect*> ArrEffects;
	Array<EffEffect*> ArrParticles;
};

//

#define MAXPART_RAIN 5000
#define SIZEPART_RAIN_X 0.008f
#define SIZEPART_RAIN_Y 0.3f
#define TIMERAINSNDUPDATE 500

struct VertexEffectRain
{
	float3_t pos;
	float2_t tex;
};

class EffectRain
{
public:

	SX_ALIGNED_OP_MEM

	EffectRain();
	~EffectRain();
	void Init();

	void Update(DWORD timeDelta);
	void Render();

	inline void SetDensity(int density);
	inline int GetDensity();

	inline void SetSound(const char* path);

	float3_t Color;

protected:

	inline void ReCreate(int key);

	int Density;		//��������� � ��������� �� 0 �� 100
	float RotAng;		//���� �������� �� ��� y

	float PercentAudibility;	//������� ����������, �������� ��� � �������

	int CurAudibility;	//������� ���������� � ��
	int OldAudibility;	//������� ���������� � ��

	int CountIntersectBB;	//�������, ������� ������ ���� ���������� ��� ������

	float4x4 RotMatrix;	//������� �������� 
	int CountLife;		//���������� ����� ������

	float3_t BMax,BMin;	//�������������� �����

	DWORD IDSound;
	DWORD TimeCountCreate;	//������� ������� ��� �������� ����� ������

	DWORD TimeComAudibility;	//������� ������� ��� ���������� ����������
	DWORD CountLifeAudibility;

	float3 Position[MAXPART_RAIN];
	float PositionY[MAXPART_RAIN];
	bool IsLife[MAXPART_RAIN];

	Array<String> ArrPathSounds;
	Array<DWORD> ArrIDSounds;

	IDirect3DVertexBuffer9* TransVertBuf;

	IDirect3DVertexBuffer9* VertexBuff;
	IDirect3DIndexBuffer9* IndexBuff;
};
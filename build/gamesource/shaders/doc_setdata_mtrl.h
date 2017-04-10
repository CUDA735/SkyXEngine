
vs:
float4x4 World;
float4x4 View;
float4x4 Projection;

float4x4 WorldView; //����� ��� ��������� � ���������� ��������

float4x4 WorldViewProjection;

float4 CameraPosition;

float2 TimeDelta;
//x - ��������� ����� � ������ �������
//y - ��������� ����� ������� � ���������� �����
float4 Param;
float2 NearFar; //������� � ������� ��������� ���������

ps:
float4x4 World;
float4x4 View;
float4x4 Projection;

float2 TimeDelta;
//x - ��������� ����� � ������ �������
//y - ��������� ����� ������� � ���������� �����

float4 CameraPosition;

float4 Param;
float2 NearFar; //������� � ������� ��������� ���������

sampler2D ColorSampler:register(s0);	//�������� � �������� ������

sampler2D MaskSampler:register(s1);		//����� ��� �����������/������������

//4 ��������� ��������
sampler2D DetailRSampler:register(s2);
sampler2D DetailGSampler:register(s3);
sampler2D DetailBSampler:register(s4);
sampler2D DetailASampler:register(s5);

//4 �������������� ��������
sampler2D MDRSampler:register(s6);
sampler2D MDGSampler:register(s7);
sampler2D MDBSampler:register(s8);
sampler2D MDASampler:register(s9);

sampler2D RF0SSIsSampler:register(s10);	//��������� ��� ���������
//r - roughness - �������������
//g - f0 - ������������� ����������� �����������
//b - soft specular - �������� ��������� ���������
//a - intens specular - ������������� ���������

sampler2D/samplerCUBE ReflectionSampler:register(s12);	//���������
sampler2D RefractionSampler:register(s13);				//�����������
sampler2D DepthLinearSampler:register(s14);				//�������� �������

#ifndef __sxsound
#define __sxsound

#include <gdefines.h>
#include <sxmath.h>

#define SOUND_PATH_MAX_LEN 1024
#define SOUND_MIN_SIZE_STREAM 1024*64 //���������� ��������� ������ ������ ��� ���������������

#define SOUND_TP_BYTES	0//�����
#define SOUND_TP_SEC	1//�������
#define SOUND_TP_MLS	2//�����

#define SOUND_TV_DB		3//��������
#define SOUND_TV_PCT	4//��������

#define SOUND_MAX_SOUNDS 65535//����������� �������� ���������� ������������������ �������� ��������

#define SOUND_STREAM		0//��������� ��������
#define SOUND_STATIC		1//��������� ��������

#define SOUND_EFFECT_ON		1			//��������� �������
#define SOUND_EFFECT_OFF	0			//���������� �������
#define SOUND_EFFECT_INVALID_KEY	-1	//������, ������������ �������� ����� (� ������� ��� ��������� bool �������� �������)

//������� �������� ������
#define SOUND_NON_FORMAT	-2	//�� ��������� ������
#define SOUND_WAV_FORMAT	0	//wav ������
#define SOUND_OGG_FORMAT	1	//ogg ������

//��������� ������ ���� ��������� ������
#define SOUND_OK			0//�������� ������� ���������
#define SOUND_CORE_ERR_FAILED_INIT		-3//�� ������� ���������� �������� ����������
#define SOUND_CORE_ERR_FAILED_CL		-4//������ ������������ ������ ����������
#define SOUND_CORE_ERR_FAILED_PRIM_BUF	-5//������ �������� ���������� ��������� �������
#define SOUND_CORE_ERR_FAILED_SET_FORMAT -6//�� ������� ���������� ������ ���������� �������

#define SOUND_ERR_OPEN			-7	//������ ��������, ������� ����� �� ����������
#define SOUND_ERR_FORMAT		-8	//����������� ������ �����
#define SOUND_ERR_HEADER		-9	//������ ��������� �����
#define SOUND_ERR_CREATE_SB		-10	//������ �������� ���������� ��������� �������
#define SOUND_ERR_UNCPECIFIED	-11	//������������ ������

//������ ��������� �������
#define SOUND_ERR_CONTROLUNAVAIL	-12	//������ ������� � ���������� ��������, ���� ���������� ������ �������� ��� ��������
#define SOUND_ERR_GENERIC			-13	//�������������� ������ � ���������� Direct Sound
#define SOUND_ERR_INVALIDCALL		-14	//������������ ����� �������
#define SOUND_ERR_INVALIDPARAM		-15	//�������� �������� ������� � ���������� �������
#define SOUND_ERR_PRIOLEVELNEEDED	-16	//�� ���������� ������������ �����
#define SOUND_ERR_NOINTERFACE		-17	//����������� ��������� ����������
#define SOUND_ERR_EFFECT_NON_SETUP	-18	//�� ������� ���������� ������
#define SOUND_ERR_NULL_BUFFER		-19	//�� ��������������� ������, �������� �� ������

#define SOUND_ERR_OGG_DECODING	-20	//������ �������������
#define SOUND_ERR_LOCK			-21	//������ ������������
#define SOUND_ERR_SIZING		-22	//������ �����������/�������� �������

//�������� �������� � ������� ��������
#define SOUND_EFFECT_GARGLE		0
#define SOUND_EFFECT_CHORUS		1
#define SOUND_EFFECT_FLANDER	2
#define SOUND_EFFECT_ECHO		3
#define SOUND_EFFECT_DISTORTION	4
#define SOUND_EFFECT_COMPRESSOR	5
#define SOUND_EFFECT_PARAMEQ	6
#define SOUND_EFFECT_I3DL2REVERB	7
#define SOUND_EFFECT_WAVESREVERB	8

/////////////////

SX_LIB_API long SSound_0GetVersion(); //���������� ������ ����
SX_LIB_API void SSound_Dbg_Set(report_func rf); //��������� ������ � ���
SX_LIB_API void SSound_0Create(const char* name, HWND hwnd, bool is_unic = true); //�������� ������� �����

SX_LIB_API void SSound_AllUpdate(float3* campos,float3* camdir); //���������� ���� �������� ������

SX_LIB_API DWORD SSound_Create2d(const char *file, bool looping = 0, int streaming = 0, DWORD size_stream = 0); //�������� 2� �����
SX_LIB_API DWORD SSound_Create3d(const char *file, bool looping, int streaming, DWORD size_stream, 
	float max_dist, float damping = 1, float shift_pan = 0.1f);//�������� 3� �����

SX_LIB_API void SSound_Play(DWORD id); //������������� ���� � ������� �������
SX_LIB_API void SSound_Stop(DWORD id); //���������� ����

//���������
SX_LIB_API void SSound_SetVolume(DWORD id, long volume, int type = SOUND_TV_DB);
SX_LIB_API long SSound_GetVolume(DWORD id, int type = SOUND_TV_DB);

//������� ������� ���������������
SX_LIB_API void SSound_SetCurrentPos(DWORD id, DWORD pos, int	type = SOUND_TP_BYTES);
SX_LIB_API DWORD SSound_GetCurrentPos(DWORD id, int type = SOUND_TP_BYTES);

//�������� ����� ����� �����
SX_LIB_API void SSound_SetPan(DWORD id, long value, int type = SOUND_TV_DB);
SX_LIB_API long SSound_GetPan(DWORD id, int type = SOUND_TV_DB);

SX_LIB_API void SSound_SetFrequency(DWORD id, long value); //���������� ������� �����
SX_LIB_API DWORD SSound_GetFrequency(DWORD id); //�������� ������� �����
SX_LIB_API DWORD SSound_GetFrequencyOriginal(DWORD id); //�������� ������������ ������� �����

SX_LIB_API bool SSound_Playing(DWORD id); //���������������� �� ����

//������� ��������������� �� ����
SX_LIB_API int SSound_EffectIsOn(DWORD id, int effect);				//������� �� ������ 
SX_LIB_API int SSound_EffectOnOff(DWORD id, int effect, int switch_);	//��������/��������� ������

SX_LIB_API int SSound_SetEffectGargle(DWORD id, DWORD RateHz, DWORD WaveShape);
SX_LIB_API int SSound_SetEffectChorus(DWORD id, float	WetDryMix, float Depth, float Feedback, float Frequency, long Waveform, float Delay, long Phase);
SX_LIB_API int SSound_SetEffectFlanger(DWORD id, float	WetDryMix, float Depth, float Feedback, float Frequency, long Waveform, float Delay, long Phase);
SX_LIB_API int SSound_SetEffectEcho(DWORD id, float	WetDryMix, float Feedback, float LeftDelay, float RightDelay, long PanDelay);
SX_LIB_API int SSound_SetEffectDistortion(DWORD id, float	Gain, float Edge, float PostEQCenterFrequency, float PostEQBandwidth, float PreLowpassCutoff);
SX_LIB_API int SSound_SetEffectCompressor(DWORD id, float	Gain, float Attack, float Release, float Threshold, float Ratio, float Predelay);
SX_LIB_API int SSound_SetEffectParameq(DWORD id, float	Center, float Bandwidth, float Gain);
SX_LIB_API int SSound_SetEffectI3DL2Reverb(DWORD id,
	long Room, long RoomHF, float RoomRolloffFactor, float DecayTime, float DecayHFRatio, long Reflections,
	float ReflectionsDelay, long Reverb, float ReverbDelay, float Diffusion, float Density, float HFReference
	);
SX_LIB_API int SSound_SetEffectWavesReverb(DWORD id, float InGain, float ReverbMix, float ReverbTime, float HighFreqRTRatio);

SX_LIB_API float SSound_GetCountSec(DWORD id); //����� � ��������
SX_LIB_API DWORD SSound_GetBytesPerSec(DWORD id); //���� � �������
SX_LIB_API DWORD SSound_GetSize(DWORD id); //������ � ������ ����� ������
SX_LIB_API void SSound_GetPathFile(DWORD id, char* path); //���� �� ��������� �����

//������������ ��������� �� ������� ���� ��� �� ������
SX_LIB_API float SSound_GetMaxDist(DWORD id);
SX_LIB_API void SSound_SetMaxDist(DWORD id, float value);

SX_LIB_API void SSound_SetPos(DWORD id, float3* pos); //���������� 3� ������� � ���� ��� ��������������� �����

#endif
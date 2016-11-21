
#ifndef SOUND_ENGINE_H
#define SOUND_ENGINE_H

#pragma once

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dsound.lib")

#if defined(_DEBUG)
#pragma comment(lib, "libogg_static_d.lib")
#pragma comment(lib, "libvorbis_static_d.lib")
#pragma comment(lib, "libvorbisfile_static_d.lib")
#elif
#pragma comment(lib, "libogg_static.lib")
#pragma comment(lib, "libvorbis_static.lib")
#pragma comment(lib, "libvorbisfile_static.lib")
#endif

#include <mmsystem.h>
#include <dsound.h>

#include <libvorbis\include\vorbis\codec.h>
#include <libvorbis\include\vorbis\vorbisfile.h>
	
#include <sound\\sxCallBackOgg.cpp>

//��������� ��� �������� wav �����
struct WaveHeader 
{
	char	RiffSig[4];
	long	WaveformChunkSize;
	char	WaveSig[4];
	char	FormatSig[4];
	long	FormatChunkSize;
	short	FormatTag;
	short	Channels;
	long	SampleRate;
	long	BytesPerSec;
	short	BlockAlign;
	short	BitsPerSample;
	char	DataSig[4];
	long	DataSize;
};

//����� ��������� ��� ���� �������� ��������
struct SoundCommonObject
{
	DWORD	DataSize;		//������ PCM ������
	const char*	Path;		//���� �� ����� �� ������
	float	CountSec;		//������������ ����� � ��������

	int		CountChannels;	//������
	long	SampleRate;		//rate
	int		BitsPerSample;	//�������� ������
	long	BytesPerSec;	//���������� ���� � ������
};

struct SoundLoadDataObject
{
	SoundLoadDataObject()
	{
		DSBuffer		= 0;
		File			= 0;
		InfoObject		= new SoundCommonObject();
		HowFormatFile	= -1;
		VorbisFile		= 0;
	}

	IDirectSoundBuffer8*	DSBuffer;		//��������� �������� ������
	FILE*					File;			//�����
	SoundCommonObject*		InfoObject;		//���������� � ����������� �������� �����
	int						HowFormatFile;	//������, 0 - wave, 1 - ogg, -1 - ����������� ������, ��� ��������� ������ � ��������� �� ����������������
	OggVorbis_File*			VorbisFile;		//���� HowFormatFile == 1, �� ����, ���� ��������� ogg
};


//�������� ������
class SXSoundObject
{
public:

	SX_ALIGNED_OP_MEM

	SXSoundObject(){}
	//SXSoundObject(const char *file,bool looping,int streaming,DWORD size_stream);	//�������� 2d �����
	//SXSoundObject(const char *file,bool looping,int streaming,DWORD size_stream,float max_dist,float damping,float shift_pan);	//�������� 3d �����

	long Load(const char *file, bool looping, int streaming, DWORD size_stream);	//�������� 2d �����
	long Load(const char *file, bool looping, int streaming, DWORD size_stream, float max_dist, float damping, float shift_pan);
	inline void	Play();		//���������
	inline void	Stop();		//����������
	void	Update(float3* campos = 0, float3* camdir = 0);	//���������� ������������ ������
	void	Update3d(float3 *CamPos,float3 *CamLook);

	//������� ������� ������������
	void	SetCurrentPos(DWORD	pos,int	type=SOUND_TP_BYTES);
	inline DWORD	GetCurrentPos(int type=SOUND_TP_BYTES);

	//���������
	inline void	SetVolume		(long volume,int type=SOUND_TV_DB);
	inline long	GetVolume		(int type = SOUND_TV_DB);	

	//���������������� ����� ����������
	inline void	SetPan			(long value,int type=SOUND_TV_DB);	
	inline long	GetPan			(int type = SOUND_TV_DB);

	//�������
	inline void	SetFrequency	(long value);	
	inline DWORD	GetFrequency	();
	inline DWORD	GetFrequencyOriginal();

	inline bool	Playing();	//������������� �� ����

	int		EffectIsOn(int effect);					//������� �� ������ 
	int		EffectOnOff(int effect,int switch_);	//��������/��������� ������

	//��������� ��������
	int SetEffectGargle	(DWORD RateHz,DWORD WaveShape);
	int SetEffectChorus		(float	WetDryMix,	float Depth,	float Feedback,				float Frequency,		long Waveform,	float Delay,long Phase);
	int SetEffectFlanger	(float	WetDryMix,	float Depth,	float Feedback,				float Frequency,		long Waveform,	float Delay,long Phase);
	int SetEffectEcho		(float	WetDryMix,	float Feedback,	float LeftDelay,			float RightDelay,		long PanDelay);
	int SetEffectDistortion	(float	Gain,		float Edge,		float PostEQCenterFrequency,float PostEQBandwidth,	float PreLowpassCutoff);
	int SetEffectCompressor	(float	Gain,		float Attack,	float Release,				float Threshold,		float Ratio,	float Predelay);
	int SetEffectParameq	(float	Center,		float Bandwidth,float Gain);

	int SetEffectI3DL2Reverb	(	
									long Room,long RoomHF,float RoomRolloffFactor,float DecayTime,float DecayHFRatio,long Reflections,
									float ReflectionsDelay,long Reverb,float ReverbDelay,float Diffusion,float Density,float HFReference
								);
	int SetEffectWavesReverb(float InGain,float ReverbMix,float ReverbTime,float HighFreqRTRatio);

	//��������� ��������� �����
	inline float GetCountSec();	//����� � ��������
	inline DWORD GetBytesPerSec();	//���� � �������
	inline DWORD GetSize();		//������ � ������ PCM ������
	inline void GetPathFile(char* path);	//���� �� ��������� �����
	inline DWORD GetID();

	inline float GetMinDist();
	inline void SetMinDist(float value);

	inline float GetMaxDist();
	inline void SetMaxDist(float value);

	~SXSoundObject();

	float3 Position;	//������� ��������� �����
	float Damping;		//����� ��������� ��� ��������� �� ����, �.�. count_volume = volume - dist * Damping %
	float ShiftPan;		//��������� ���������������� �����, �� ������� ����� ������ ���� ��� ��������� ������ � ��������� �����
	//��� ����� � ������� ��� ������ ������� � ���������������� ��� ���������

	int Looping;//����������� ��������������?

private:

	DWORD LastPos;
	int State;
	DWORD BeginFrec;
	int LoadStatic(const char *file,int format);			
	int LoadDynamicWAV(const char *file,DWORD size_stream);
	int LoadDynamicOGG(const char *file,DWORD size_stream);
	void ReLoadSplit(DWORD Pos, DWORD Size);	//������������ ����� ������

	//float MinDist;	//������ � ������� ���� ��������� �� 100%
	float MaxDist;
	
	DWORD	MaxSize;		//������ ������ � ������

	long VolumeSound;

	SoundLoadDataObject* DataObject;
	
	//������� ������� ������
	DWORD	SizeSplit1;	
	DWORD	SizeSplit2;
	DWORD	SizeSplit3;

	char File[SOUND_PATH_MAX_LEN];

	//�������� ��� ������ ������� �� ������ ����� � �����������
	bool BF1;
	bool BF2;
	bool BF3;
	bool BF4;

	bool	IsStarting;		//��������������� ������ ��������? (��� ������)
	bool	IsStreaming;	//���� ��������������� ��������?
	bool	Is3d;
	DWORD	ID;

	WORD	ActiveSplit;	//�������� �����
	DWORD	HowRePlay;		//������� ��� ��� ��������� ������������ �����
	DWORD	CountRePlayEnd;	//������� ��� ����� ��������� ������������� ����� ���� ����� �� �����

	bool IsInitEffect[9];

	DSFXGargle		SXGargle;
	DSFXChorus		SXChorus;
	DSFXFlanger		SXFlanger;
	DSFXEcho		SXEcho;
	DSFXDistortion	SXDistortion;
	DSFXCompressor	SXCompressor;
	DSFXParamEq		SXParamEq;
	DSFXI3DL2Reverb	SXI3DL2Reverb;
	DSFXWavesReverb	SXWavesReverb;

	void	InitEffectBool();
	void	ReInitEffect();
	int		PrecondInitEffect(HRESULT hr);
	GUID	GetGuidEffect(int effect);
};

//����� ������������� � ������������ ����������
class SXMainSound
{
public:
	SXMainSound	(const char* name);
	long Init(HWND hwnd);
	void SetStdPath(const char* path);
	void GetStdPath(char* path);
	~SXMainSound		();
	void	Update(float3* campos, float3* camdir);
	DWORD	AddSoundObject		(SXSoundObject *Obj);
	inline SXSoundObject* GetSoundObject(DWORD id);
	void	DeleteSoundObject	(DWORD num);

	DWORD	GetCountPlaySounds();
	DWORD	GetCountLoadSounds();
	
	DWORD	GetCountKey();
	char StdPath[CORE_NAME_MAX_LEN];
private:
	char Name[CORE_NAME_MAX_LEN];
	
	//��� ������� ��������� ������
	SXSoundObject *ArrSounds[SOUND_MAX_SOUNDS];	//������ �� ����� ��������� ���������

	IDirectSound8*		DeviceSound;				//�������� ����������
	IDirectSoundBuffer*	DSPrimary;					//��������� �����
	DWORD				CountKeyInArr;				//���������� ������ � ������� �������
	DWORD				CountPlaySounds;			//���������� ������������� ������
	DWORD				CountLoadSounds;			//���������� ����������� ������ (� ������ ��� ��������������� ��� � �������������)
};

//�������������� ������������ ���� ��� ���������� ������
namespace SoundControl
{
	////////////////////////////////////////////
	inline void ComMsg(int msg,const char* file="",const char* fileerror=__FILE__,int strerror=__LINE__);
	bool LoadSoundDataWAV(IDirectSoundBuffer8 *DSBuffer,long LockPos,FILE* data,long Size,DWORD	flag);	//���������� ������
	int LoadWAV(const char *FileName,SoundLoadDataObject** DataObject);									//�������� wav �����

	WaveHeader*	GetHdrWav(FILE *fp); //���������� ����������� ��������� WaveHeader

	int LoadSoundDataOGG(OggVorbis_File* VorbisFile,IDirectSoundBuffer8 *DSBuffer,DWORD LockPos,DWORD Size,DWORD flag);//���������� ������
	int LoadOGG	(const char	*FileName,SoundLoadDataObject** DataObject);												//�������� ogg �����

	IDirectSoundBuffer8* CreateSoundBufferStream (WaveHeader *Hdr,DWORD size);	//�������� ���������� ������ ������������� �������
	IDirectSoundBuffer8* CreateSoundBuffer (WaveHeader	*Hdr);					//�������� ���������� ������
	
	int HowFormat(const char* file);	//���������� ������ �����
};

#endif
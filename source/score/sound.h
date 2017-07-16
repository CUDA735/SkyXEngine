
#ifndef __sound_h
#define __sound_h

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "libogg_static.lib")
#pragma comment(lib, "libvorbis_static.lib")
#pragma comment(lib, "libvorbisfile_static.lib")
#include <mmsystem.h>
#include <dsound.h>
#include <stdint.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#include <score/CallBackOgg.cpp>
#include <common/aastring.h>

struct AAStringNR : public AAString
{
	__forceinline AAStringNR(const char * str)
	{
		tmpName = str;
		Name[0] = 0;
	}

	__forceinline AAStringNR()
	{
		tmpName = NULL;
		Name[0] = 0;
	}

	__forceinline bool operator==(const AAStringNR & str) const
	{
		return(stricmp(tmpName ? tmpName : Name, str.tmpName ? str.tmpName : str.Name) == 0);
	}
};

#include <common/array.h>
#include <common/assotiativearray.h>

#define SOUND_PRECOND(id, retval) \
if (id >= ArrSounds.size() || !(ArrSounds[id]))\
		{reportf(REPORT_MSG_LEVEL_ERROR, "%s - sxsound - unresolved address to sound %d", gen_msg_location, id); return retval; }

inline long SOUND_3D_COM_VOLUME(const float3 & snd_pos, const float3 & view_pos, const float snd_distaudible)
{
	long vol = (SMVector3Distance(snd_pos, view_pos) / snd_distaudible) * (-10000);

	if (vol > 0)
		vol = 0;

	if (vol < -10000)
		vol = -10000;

	return vol;
}

inline long SOUND_3D_COM_PAN(const float3 & snd_pos, const float3 & view_pos, const float3 & view_dir, const float snd_distaudible, const float snd_shiftpan)
{
	float dist = SMVector3Distance(snd_pos, view_pos);
	float3 vec = view_pos + view_dir;

	float str = (snd_pos.x - view_pos.x)*(snd_pos.z - vec.z) - (snd_pos.z - view_pos.z)*(snd_pos.x - vec.x);
	return ((str * (dist / snd_distaudible)) * snd_shiftpan * (-10000));
}

//структура для загрузки wave файла
struct SoundWaveHeader
{
	char	RiffSig[4];
	int32_t	ChunkSize;
	char	Sig[4];
	char	FormatSig[4];
	int32_t	FormatChunkSize;
	int16_t	FormatTag;
	int16_t	Channels;
	int32_t	SampleRate;
	int32_t	BytesPerSec;
	int16_t	BlockAlign;
	int16_t	BitsPerSample;
	char	DataSig[4];
	int32_t	DataSize;
};


class MainSound
{
public:
	MainSound();
	~MainSound();

	SX_ALIGNED_OP_MEM

	void Clear();

	void Init(HWND hwnd);

	inline void StdPathSet(const char* path);
	inline void StdPathGet(char* path);

	struct Sound
	{
		Sound();
		~Sound();
		SX_ALIGNED_OP_MEM

		char RPath[SOUND_MAX_SIZE_PATH];
		ID Id;
		bool IsInst;
		FILE* StreamFile;
		IDirectSoundBuffer8* DSBuffer;	//звуковой буфер
		OggVorbis_File* VorbisFile;		//поток для декодирования ogg

		struct SIData
		{
			SIData(){ sbuffer = 0; busy = false; }
			SIData(IDirectSoundBuffer8* _sbuffer, float3_t* _pos, bool _busy)
			{
				sbuffer = _sbuffer; if (_pos) pos = *_pos; busy = _busy;
			}
			~SIData()
			{
				mem_release(sbuffer);
			}

			IDirectSoundBuffer8* sbuffer;
			float3_t pos;
			bool busy;
		};

		Array<SIData> DataInstances;

		SoundFileFormat Format;		//формат файла
		DWORD SizeFull;				//полный размер в байтах (для wav исключая заголовочную структуру)
		
		float3 Position;	//позиция источника звука
		//float Damping;	//сброс громкости при отдалении на метр, т.е. count_volume = volume - dist * Damping %
		
		//изменение позиционирования звука, на сколько будет смещен звук при поворотах камеры к источнику звука
		//чем ближе к объекту тем меньше разница в позиционировании при поворотах
		float ShiftPan;		

		SoundObjState State;
		DWORD FrecOrigin;	//оригинальная частота

		float DistAudible;	

		DWORD StreamSize;//размер потока в байтах
		int LengthSec;
		int ChannelsCount;
		int RateSample;
		int BitsPerSample;
		DWORD BytesPerSec;
		long Volume;	

		//размеры сплитов потока
		DWORD Split1Size;
		DWORD Split2Size;
		DWORD Split3Size;

		//заглушки для работы апдейта на каждый сплит в отдельности
		bool BF1;
		bool BF2;
		bool BF3;
		bool BF4;

		bool IsLooping;		//зацикливать воспроизведние?
		bool IsStarting;	//воспроизведение только началось? (для потока)
		bool Is3d;

		short SplitActive;	//активный сплит
		int RePlayCount;	//сколько раз был полностью перезагружен поток
		int	RePlayEndCount;	//сколько раз нужно полностью перезагрузить поток чтоб дойти до конца
	};

	ID SoundCreate2d(const char *file, bool looping = false, DWORD size_stream = 0);
	ID SoundCreate3d(const char *file, bool looping, DWORD size_stream, float dist, float shift_pan = 0.1f);

	ID SoundCreate2dInst(const char *file, bool looping = false, DWORD size_stream = 0);
	ID SoundCreate3dInst(const char *file, bool looping, DWORD size_stream, float dist, float shift_pan = 0.1f);

	ID SoundFind2dInst(const char * file);
	ID SoundFind3dInst(const char * file);

	void SoundInstancePlay2d(ID id, int volume=100, int pan = 0);
	void SoundInstancePlay3d(ID id, float3* pos);

	inline bool SoundIsInit(ID id);
	inline void SoundDelete(ID id);

	inline void	SoundPlay(ID id, int looping=-1);	//проиграть
	inline void	SoundPause(ID id);					//приостановить
	inline void	SoundStop(ID id);					//остановить

	inline void SoundStateSet(ID id, SoundObjState state);
	inline SoundObjState SoundStateGet(ID id);

	//текащая позиция проигрывания
	void SoundPosCurrSet(ID id, DWORD pos, int type = SOUND_POS_BYTES);
	inline DWORD SoundPosCurrGet(ID id, int type = SOUND_POS_BYTES);

	//громкость
	inline void SoundVolumeSet(ID id, long volume, int type = SOUND_VOL_PCT);
	inline long SoundVolumeGet(ID id, int type = SOUND_VOL_PCT);

	//позиционирование между динамиками
	inline void SoundPanSet(ID id, long value, int type = SOUND_VOL_PCT);
	inline long SoundPanGet(ID id, int type = SOUND_VOL_PCT);

	//частота
	inline void SoundFreqCurrSet(ID id, DWORD value);
	inline DWORD SoundFreqCurrGet(ID id);
	inline DWORD SoundFreqOriginGet(ID id);

	inline void SoundPosWSet(ID id, float3* pos);
	inline void SoundPosWGet(ID id, float3* pos);

	inline int SoundLengthSecGet(ID id);		//длина в секундах
	inline DWORD SoundBytesPerSecGet(ID id);	//байт в секунде
	inline DWORD SoundSizeGet(ID id);			//размер в байтах PCM данных
	inline void SoundFileGet(ID id, char* path);//путь до звукового файла

	inline float SoundDistAudibleGet(ID id);
	inline void SoundDistAudibleSet(ID id, float value);

	void Update(float3* viewpos, float3* viewdir);

	SoundFileFormat FileFormat(const char* file);

	inline int SoundsPlayCountGet();
	inline int SoundsLoadCountGet();

private:

	void Load(Sound* snd, const char* fpath, SoundFileFormat fmt);

	void LoadWAV(Sound* snd, const char* fpath);
	void LoadOGG(Sound* snd, const char* fpath);
	IDirectSoundBuffer8* SoundBufferCreate(SoundWaveHeader* hdr);
	void SoundDataWAVLoad(IDirectSoundBuffer8* DSBuffer, long LockPos, FILE* data, long Size, DWORD flag = 0);
	void SoundDataOGGLoad(OggVorbis_File* VorbisFile, IDirectSoundBuffer8 *DSBuffer, long LockPos, long Size, DWORD flag);

	void ReLoadSplit(ID id, DWORD Pos, DWORD Size);

	ID AddSound(Sound* snd);

	Array<Sound*> ArrSounds;	//массив со всеми звуковыми объектами
	AssotiativeArray<AAStringNR, ID, false, 16> AArr2dInst;
	AssotiativeArray<AAStringNR, ID, false, 16> AArr3dInst;
	
	char StdPath[SOUND_MAX_SIZE_STDPATH];

	IDirectSound8* DeviceSound;		//звуковое устройство
	IDirectSoundBuffer* DSPrimary;	//первичный буфер
	int SoundsPlayCount;			//количество проигрываемых звуков
	int SoundsLoadCount;			//количество загруженных звуков (с учетом как проигрывающихся так и простаивающих)

	float3 OldViewPos;
	float3 OldViewDir;
};

#endif
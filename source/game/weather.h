
#ifndef __weather_h
#define __weather_h

//��������� ����� � 
class WeatherRndSnd
{
public:
	WeatherRndSnd();
	~WeatherRndSnd();

	void Clear();
	void ResetOld();
	void AddSound(const char* path);
	void SetParamPlayVolume(int bvol, int evol);
	void SetParamPlayPeriod(DWORD bper, DWORD eper);

	void Update();

	void Play();
	void Pause();
	inline bool IsPlaying();

protected:

	bool Playing;

	DWORD NextPlay;
	
	int BVolume, EVolume;
	DWORD BPeriod, EPeriod;

	Array<ID> CurrentSndIDs;
	ID CurrPlay;

	struct Snd
	{
		Snd(){ id = -1; }
		Snd(const char* _path, ID _id){ path = _path; id = _id; }
		String path;
		ID id;
	};

	Array<Snd> ArrSnd;
};

//#############################################################################

#define WEATHER_CONFIG_SECTION_KEY(name_key, key, file, section) \
{ \
	if (!name_key || strlen(name_key) != 2 || !isdigit(name_key[0]) || !isdigit(name_key[1])) \
		reportf(REPORT_MSG_LEVEL_ERROR,"%s - unresolved name of key '%s' \nfile '%s' \nsection '%s'",gen_msg_location, key, file, section); \
}
#define WEATHER_CONFIG_LACKS_COMPONENT(component, file, section, key) if(!component) {reportf(REPORT_MSG_LEVEL_ERROR,"%s - lacks component in key '%s' \nfile '%s' \nsection '%s'",gen_msg_location, key, file, section);}
#define WEATHER_CONFIG_LACKS_KEY(key, file, section) {reportf(REPORT_MSG_LEVEL_ERROR,"%s - lacks key '%s' \nfile '%s' \nsection '%s'",gen_msg_location, key, file, section);}

class Weather
{
public:
	Weather();
	~Weather();

	struct DataSection
	{
		char sky_tex[64];
		float sky_rotation;
		float4_t sky_color;

		char clouds_tex[64];
		float clouds_rotate;
		float clouds_transparency;
		float clouds_speed;
		float4_t clouds_color;

		char sun_tex[64];
		float2_t sun_pos;
		float3_t sun_color;

		float ffar;

		float rain_density;
		float4_t rain_color;

		bool thunderbolt;
		DWORD thunder_period;

		float3_t fog_color;
		float fog_density;

		struct SndRnd
		{
			SndRnd(){ period_b = period_e = 0; volume_b = volume_e = 0; }
			Array<String> arr_path;
			DWORD period_b, period_e;
			int volume_b, volume_e;
		};

		SndRnd Snds;
	};

	struct TimeSection
	{
		TimeSection(){ time = 0; section[0] = 0; }
		TimeSection(int _time, const char* sect){ time = _time; if (sect) strcpy(section, sect); }

		int time;
		char section[CONFIG_SECTION_MAX_LEN];
		DataSection Data;
	};

	void Load(const char* file);
	void SndPlay();
	void SndPause();
	inline bool SndIsPlaying();
	void Update();
	float GetCurrRainDensity();

protected:

	bool Playing;

	void UpdateRainSound();
	
	Array<TimeSection> ArrTimeSection;
	int OldSection;			//���������� ����� ������ ������
	int CurrSection;		//���������� ����� ������� ������
	DWORD OldTimeMlsec;		//����� ��� ������� ��������� ���������� ������ (� ������� ���)
	DWORD CurrTimeMlsec;	//����� ��� ������� ��������� ���������� ������ (�����)
	bool HasUpdate;			//��������� �� ������������ ������ ����� ��������
	WeatherRndSnd RndSnd;	//��������� ����� ������

	ID EffIDRain;			//������ �����
	ID EffThunderbolt;		//������ ������
	ID SndRain;				//���� �����
	ID SndThunder;			//���� �����
	ID LightThunderbolt;	//���� �� ������

	DWORD TimeBoltLast;		//����� ���������� �����
	DWORD TimeBoltNext;		//��������� ����� ��������� �����
	DWORD TimeBoltLight;	//����� ��������� ����� �� ������

	float LevelMaxY;		//������������ ������ ������

	//���������� ��� ��������� ������
	float3_t BoltMin, BoltMax;

	float3* ArrTrackPos;		//���������� ������ ��� ������ ������� ��������� ������� �������� ����
	int CountArrTrackPos;		//���������� ��������� � ArrTrackPos
	DWORD TimeRainVolSndLast;	//���������� ����� ��������� ��������� �����

	float RainVolume;		//��������� ����� [0,1]
};

#endif
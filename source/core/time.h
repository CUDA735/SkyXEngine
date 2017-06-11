
#ifndef __time_h
#define __time_h

#include <chrono>

typedef std::chrono::system_clock::time_point time_point;

#define TIMEMANAGER_PRECOND_ID(id,stdval) \
if (!(id >= 0 && id < ArrTimes.size()))\
{reportf(REPORT_MSG_LEVEL_ERROR, "%s - time manager: unresolved index of access '%d'", gen_msg_location, id); return stdval; }

class TimeManager
{
public:

	TimeManager();
	~TimeManager();

	struct Time
	{
		Time();
		~Time();

		time_point tp;
		int64_t time_total;		//����� ��������� ����� � ������� �������
		long double delta_fraction;
		int64_t unixtime_curr;	//������� ����� � unix
		int64_t unixtime_start;
		float speed;
		bool working;
	};

	void Update();

	ID TimeAdd();

	inline void TimeSpeedSet(ID id, float speed);
	inline float TimeSpeedGet(ID id);

	inline void TimeWorkingSet(ID id, bool working);
	inline bool TimeWorkingGet(ID id);

	inline void TimeUnixStartSet(ID id, int64_t start_time);
	inline int64_t TimeUnixStartGet(ID id);
	inline int64_t TimeUnixCurrGet(ID id);

	inline int64_t TimeTotalMcsGet(ID id);
	inline int64_t TimeTotalMcsGetU(ID id);

protected:
	Array<Time*> ArrTimes;
};

#endif
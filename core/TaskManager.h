#ifndef _SXTaskManager_H_
#define _SXTaskManager_H_

#include <memory>
#include <thread>
#include <algorithm>
#include <atomic>
#include <core\concurrent_queue.h>
#include <core\task.h>
#include <core\eventchannel.h>

#if defined(_WINDOWS)
// ��� ������ ��� ����, ����� ������ ��� ������ � ����������
const DWORD MS_VC_EXCEPTION = 0x406D1388;
#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
	DWORD dwType; // Must be 0x1000.
	const char * szName; // Pointer to name (in user addr space).
	DWORD dwThreadID; // Thread ID (-1=caller thread).
	DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)
#endif


// ��������, ��� ������������� ������ ���� ������� ���� �� ���� ������� ������!
class SXTaskManager
{
public:
	typedef std::shared_ptr<SXTask> TaskPtr;
	typedef ConcurrentQueue<TaskPtr> TaskList;

	struct StopEvent
	{
	};

	SXTaskManager(unsigned int numThreads = 0); //< ���������� ������� �������, 0 ��� ���������������
	~SXTaskManager();

	void  addTask(TaskPtr task); //< ��������� ������ � �����������
	void  add(THREAD_UPDATE_FUNCTION func, DWORD flag = CoreTF_SINGLETHREADED_REPEATING); //< ��������� ������ � �����������

	void start(); //< ��������� ���������� ������������
	void stop(); //< ������������� ���

	void handle(const StopEvent&);
	void handle(const SXTask::TaskCompleted& tc);

private:
	void worker();
	void execute(TaskPtr task);
	void synchronize();

	std::list<std::thread*> mThreads;
	unsigned int mNumThreads;

	bool mRunning;

	TaskList mTaskList[2];
	TaskList mBackgroundTasks;
	TaskList mSyncTasks;
	TaskList mOnSyncTasks;

	unsigned int mReadList;
	unsigned int mWriteList;

	typedef std::mutex Mutex;
	typedef std::condition_variable Condition;
	typedef std::lock_guard<Mutex> ScopedLock;

	mutable Mutex mSyncMutex;
	Condition mCondition;
	int mNumTasksToWaitFor;
};

#endif

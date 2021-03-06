#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "Memory.h"
#include "DeadLockProfiler.h"
#include "SocketUtils.h"
#include "SendBuffer.h"
#include "GlobalQueue.h"
#include "JobTimer.h"
#include "Timer.h"
#include "ConsoleLog.h"

namespace FrokEngine
{
	ThreadManager* GThreadManager = nullptr;
	Memory* GMemory = nullptr;
	SendBufferManager* GSendBufferManager = nullptr;
	GlobalQueue* GGlobalQueue = nullptr;
	JobTimer* GJobTimer = nullptr;

	DeadLockProfiler* GDeadLockProfiler = nullptr;
	Timer* GTimer = nullptr;
	ConsoleLog* GConsoleLogger = nullptr;

	class CoreGlobal
	{
	public:
		CoreGlobal()
		{
			GThreadManager = new ThreadManager();
			GMemory = new Memory();
			GSendBufferManager = new SendBufferManager();
			GGlobalQueue = new GlobalQueue();
			GJobTimer = new JobTimer();

			GDeadLockProfiler = new DeadLockProfiler();
			GTimer = new Timer();
			GConsoleLogger = new ConsoleLog();

			SocketUtils::Init();
		}

		~CoreGlobal()
		{
			delete GThreadManager;
			delete GMemory;
			delete GSendBufferManager;
			delete GGlobalQueue;
			delete GJobTimer;
			delete GDeadLockProfiler;
			delete GTimer;
			delete GConsoleLogger;
			SocketUtils::Clear();
		}
	} GCoreGlobal;
}
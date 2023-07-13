#pragma once
#ifndef __THREAD_POOL_TO_LUA__
#define __THREAD_POOL_TO_LUA__

#include <map>
#include <thread>

#include "ThreadChild.h"

using ThreadChildPtr = std::shared_ptr<ThreadChild>;

class ThreadPool final
{
public:
	static ThreadPool* getInstance();

public:
	ThreadChildPtr getChildById(numberT);
	numberT getNewChild();
	bool findChildById(numberT);
	bool removeChildById(numberT);

private:
	bool init();
	void onDestory();

private:
	static ThreadPool* m_instance;

	std::map<numberT, ThreadChildPtr> m_id_child;
private:
	class Gc 
	{ 
	public:
		~Gc();
	};
};

#endif


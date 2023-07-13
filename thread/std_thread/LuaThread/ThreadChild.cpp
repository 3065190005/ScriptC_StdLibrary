#include "ThreadChild.h"
#include <functional>
#include <Windows.h>

#pragma optimize( "", off )

ThreadChild::ThreadChild():
	m_state(Thread_State::unknow)
{
	auto bind = std::bind(&ThreadChild::thread_func, this);
	auto task = std::packaged_task<bool()>(bind);

	m_task = std::move(task);
	m_future = m_task.get_future();
}

ThreadChild::~ThreadChild()
{
	kill();
}



bool ThreadChild::open(std::string path)
{
	bool ret = false;
	if (m_state != Thread_State::unknow)
		return ret;
	
	std::ifstream fin(path);
	if (fin) 
	{
		m_lua.file(path.c_str());
		m_state = Thread_State::start;
		ret = true;
	}

	return ret;
}


bool ThreadChild::set(std::string name, auto_c param)
{
	bool ret = false;
	if (m_state != Thread_State::start)
		return ret;

	ret = m_lua.varSet(param, name.c_str());
	return ret;
}

auto_c ThreadChild::get(std::string name)
{
	auto_c ret;
	if (m_state != Thread_State::stop)
		return ret;

	ret = m_lua.varGet(name.c_str());
	return ret;
}

ThreadChild::Thread_State ThreadChild::state()
{
	return m_state;
}

bool ThreadChild::run()
{
	bool ret = false;
	if (m_state != Thread_State::start)
		return ret;

	std::thread thread(std::move(m_task));

	m_state = Thread_State::callback;
	m_thread = std::move(thread);

	while (m_state == Thread_State::callback) {}

	ret = true;
	return ret;
}

bool ThreadChild::join()
{
	bool ret = false;
	if (!m_thread.joinable())
		return ret;

	m_thread.join();

	ret = true;
	return ret;
}

bool ThreadChild::detach()
{
	bool ret = false;
	if (!m_thread.joinable())
		return ret;

	m_thread.detach();

	ret = true;
	return ret;
}

bool ThreadChild::wait()
{
	if (m_state != Thread_State::runing)
		return false;
	
	m_future.get();
	return true;
}


bool ThreadChild::stop()
{
	bool ret = false;

	auto id = m_thread.native_handle();
	if (m_state != Thread_State::runing)
		return ret;
	
	if (id == 0)
		return ret;

	SuspendThread(id);

	m_state = Thread_State::wait;
	ret = true;
	return ret;
}

bool ThreadChild::resume()
{
	bool ret = false;
	auto id = m_thread.native_handle();

	if (m_state != Thread_State::wait)
		return ret;

	if (id == 0)
		return ret;

	ResumeThread(id);

	m_state = Thread_State::runing;
	ret = true;
	return ret;
}

bool ThreadChild::kill()
{
	bool ret = false;
	auto id = m_thread.native_handle();

	if (m_state != Thread_State::wait && m_state != Thread_State::runing)
		return ret;

	if (id == 0)
		return ret;

	TerminateThread(id, -1);

	m_thread.join();
	m_state = Thread_State::stop;
	ret = true;
	return ret;
}

bool ThreadChild::reset()
{
	bool ret = false;
	if (m_state != Thread_State::stop)
		return ret;

	kill();

	auto bind = std::bind(&ThreadChild::thread_func, this);
	auto task = std::packaged_task<bool()>(bind);

	m_task = std::move(task);
	m_future = m_task.get_future();
	m_state = Thread_State::unknow;

	ret = true;
	return ret;
}

bool ThreadChild::thread_func(ThreadChild* ptr)
{
	ptr->m_state = Thread_State::runing;
	ptr->m_lua.run();
	ptr->m_state = Thread_State::stop;
	return true;
}

#pragma optimize( "", on )
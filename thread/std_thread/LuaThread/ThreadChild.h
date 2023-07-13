#pragma once
#ifndef __THREAD_CHILD_TO_LUA__
#define __THREAD_CHILD_TO_LUA__

#include <thread>
#include <future>
#include <string>
#include <fstream>

#include "../Public/AutoObject/LetManager.h"
#include "../Public/AutoObject/LetObject.h"
#include "LuaClass.h"

using namespace Cervice::Obj;

class LuaClass;

class ThreadChild
{
public:
	enum class Thread_State
	{
		unknow	= 0,		// δ֪
		start	= 2,		// ����
		runing	= 3,		// ��������
		wait	= 4,		// ����ͣ
		stop	= 5,		// �ѽ���
		callback = 10,		// �ȴ��̸߳�ֵ
	};

public:
	ThreadChild();
	~ThreadChild();

public:

	/*******************************
	* ��ָ��lua�ļ�
	* path �� �ļ�·��
	* ��ȡ�ɹ�����true ʧ�ܷ��� false
	********************************/
	bool open(std::string path);

	/*******************************
	* ����ȫ�ֱ���
	* name  �� ������
	* param :  ����ֵ
	* ���óɹ�����true ʧ�ܷ��� false
	********************************/
	bool set(std::string name, auto_c param);

	/*******************************
	* ��ȡȫ�ֱ���
	* name  �� ������
	* ��ȡ����auto_c
	********************************/
	auto_c get(std::string name);

	/*******************************
	* ��ȡ��ǰ�߳�״̬
	********************************/
	Thread_State state();

	/*******************************
	* �߳̿�ʼ����
	********************************/
	bool run();

	/*******************************
	* �����߳�
	* ���гɹ�����true ʧ�ܷ��� false
	********************************/
	bool join();

	/*******************************
	* �����߳�
	* ���гɹ�����true ʧ�ܷ��� false
	********************************/
	bool detach();

	/*******************************
	* �ȴ��߳�ֱ������
	********************************/
	bool wait();

	/*******************************
	* ��ͣ�߳�
	********************************/
	bool __stdcall stop();

	/*******************************
	* �ָ��߳�
	********************************/
	bool __stdcall resume();
	
	/*******************************
	* ɱ���߳�
	********************************/
	bool __stdcall kill();

	/*******************************
	* �����߳�״̬
	* �ɹ�����true , ʧ�ܷ���false
	********************************/
	bool reset();

private:
	static bool thread_func(ThreadChild * ptr);

private:
	std::packaged_task<bool()> m_task;
	std::future<bool> m_future;
	std::thread m_thread;
	std::thread::native_handle_type m_id;

	LuaClass m_lua;
	Thread_State m_state;

};


#endif


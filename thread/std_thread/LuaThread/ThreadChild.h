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
		unknow	= 0,		// 未知
		start	= 2,		// 运行
		runing	= 3,		// 正在运行
		wait	= 4,		// 已暂停
		stop	= 5,		// 已结束
		callback = 10,		// 等待线程赋值
	};

public:
	ThreadChild();
	~ThreadChild();

public:

	/*******************************
	* 打开指定lua文件
	* path ： 文件路径
	* 读取成功返回true 失败返回 false
	********************************/
	bool open(std::string path);

	/*******************************
	* 设置全局变量
	* name  ： 变量名
	* param :  变量值
	* 设置成功返回true 失败返回 false
	********************************/
	bool set(std::string name, auto_c param);

	/*******************************
	* 获取全局变量
	* name  ： 变量名
	* 获取返回auto_c
	********************************/
	auto_c get(std::string name);

	/*******************************
	* 获取当前线程状态
	********************************/
	Thread_State state();

	/*******************************
	* 线程开始运行
	********************************/
	bool run();

	/*******************************
	* 连接线程
	* 运行成功返回true 失败返回 false
	********************************/
	bool join();

	/*******************************
	* 分离线程
	* 运行成功返回true 失败返回 false
	********************************/
	bool detach();

	/*******************************
	* 等待线程直到结束
	********************************/
	bool wait();

	/*******************************
	* 暂停线程
	********************************/
	bool __stdcall stop();

	/*******************************
	* 恢复线程
	********************************/
	bool __stdcall resume();
	
	/*******************************
	* 杀死线程
	********************************/
	bool __stdcall kill();

	/*******************************
	* 重置线程状态
	* 成功返回true , 失败返回false
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


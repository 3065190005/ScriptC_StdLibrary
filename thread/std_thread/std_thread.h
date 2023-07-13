#pragma once
#ifndef __CERVER_STD_STD_THREAD__
#define __CERVER_STD_STD_THREAD__

#define Fname(var) void __system__thread__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"



namespace Cervice {
	namespace Obj {
		// thread_create		 创建lua线程		：成功返回按钮id，否则返回null
		EXPORTDLL(thread_create);

		// thread_set			设置全局变量		：成功返回true，否则返回null
		EXPORTDLL(thread_set);

		// thread_get			获取全局变量		：成功返回变量值，否则返回null
		EXPORTDLL(thread_get);

		// thread_run			运行线程			：成功返回true，否则返回null
		EXPORTDLL(thread_run);

		// thread_state			获取线程状态		：成功返回状态，否则返回null
		EXPORTDLL(thread_state);

		// thread_wait			等待线程结束		：成功返回true，否则返回null
		EXPORTDLL(thread_wait);

		// thread_stop			挂起线程		：成功返回true，否则返回null
		EXPORTDLL(thread_stop);		// 有几率造成死锁

		// thread_resume		恢复线程		：成功返回true，否则返回null
		EXPORTDLL(thread_resume);	// 有几率造成死锁

		// thread_kill		    杀死线程		：成功返回true，否则返回null
		EXPORTDLL(thread_kill);		// 有几率造成死锁

		// thread_join		    结合线程		：成功返回true，否则返回null
		EXPORTDLL(thread_join);

		// thread_detach		分离线程		：成功返回true，否则返回null
		EXPORTDLL(thread_detach);

		// thread_clear			清理无效线程		：成功返回true，否则返回null
		EXPORTDLL(thread_clear);
	}
}

#endif

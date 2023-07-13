#pragma once
#ifndef __CERVER_STD_STD_THREAD__
#define __CERVER_STD_STD_THREAD__

#define Fname(var) void __system__thread__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"



namespace Cervice {
	namespace Obj {
		// thread_create		 ����lua�߳�		���ɹ����ذ�ťid�����򷵻�null
		EXPORTDLL(thread_create);

		// thread_set			����ȫ�ֱ���		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_set);

		// thread_get			��ȡȫ�ֱ���		���ɹ����ر���ֵ�����򷵻�null
		EXPORTDLL(thread_get);

		// thread_run			�����߳�			���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_run);

		// thread_state			��ȡ�߳�״̬		���ɹ�����״̬�����򷵻�null
		EXPORTDLL(thread_state);

		// thread_wait			�ȴ��߳̽���		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_wait);

		// thread_stop			�����߳�		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_stop);		// �м����������

		// thread_resume		�ָ��߳�		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_resume);	// �м����������

		// thread_kill		    ɱ���߳�		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_kill);		// �м����������

		// thread_join		    ����߳�		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_join);

		// thread_detach		�����߳�		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_detach);

		// thread_clear			������Ч�߳�		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_clear);
	}
}

#endif

#pragma once
#ifndef _CERVER_STD_STD_WINDOW_
#define _CERVER_STD_STD_WINDOW_

#define Fname(var) void __system__fltk_window__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

namespace Cervice {
	namespace Obj {
		// msgbox		 �����Ի���		���ɹ����ذ�ťid�����򷵻�false
		EXPORTDLL(msgBox);

		// edgeBox		 ���������		���ɹ����������ı������򷵻�false
		EXPORTDLL(editBox);


		// bowserBox	 ����ѡ���		: �ɹ�����·�������򷵻�false
		EXPORTDLL(bowserBox);


		// htmlBox		 ����html����	: �ɹ�����true�����򷵻�false
		EXPORTDLL(htmlBox);


		// urlBox		 ����url����	: �ɹ�����true�����򷵻�false
		EXPORTDLL(urlBox);


		// hideControl    ���ؿ���̨		: �ɹ��򷵻�true�����򷵻�false
		EXPORTDLL(hideControl);


		// showControl    ��ʾ����̨		: �ɹ��򷵻�true�����򷵻�false
		EXPORTDLL(showControl);

	}
}


#endif
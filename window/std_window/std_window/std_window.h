#pragma once
#ifndef _CERVER_STD_STD_IO_
#define _CERVER_STD_STD_IO_

#define Fname(var) void __system__fltk_window__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

namespace Cervice {
	namespace Obj {
		// ��ʾMessageBox
		EXPORTDLL(msgBox);

		// hideControl    ���ؿ���̨		: �ɹ��򷵻�true�����򷵻�false
		EXPORTDLL(hideControl);


		// showControl    ��ʾ����̨		: �ɹ��򷵻�true�����򷵻�false
		EXPORTDLL(showControl);

	}
}


#endif
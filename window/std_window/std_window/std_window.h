#pragma once
#ifndef _CERVER_STD_STD_IO_
#define _CERVER_STD_STD_IO_

#define Fname(var) void __system__fltk_window__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

namespace Cervice {
	namespace Obj {
		// 显示MessageBox
		EXPORTDLL(msgBox);

		// hideControl    隐藏控制台		: 成功则返回true，否则返回false
		EXPORTDLL(hideControl);


		// showControl    显示控制台		: 成功则返回true，否则返回false
		EXPORTDLL(showControl);

	}
}


#endif
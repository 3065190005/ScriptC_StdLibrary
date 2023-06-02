#pragma once
#ifndef _CERVER_STD_STD_WINDOW_
#define _CERVER_STD_STD_WINDOW_

#define Fname(var) void __system__fltk_window__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

namespace Cervice {
	namespace Obj {
		// msgbox		 创建对话框		：成功返回按钮id，否则返回false
		EXPORTDLL(msgBox);

		// edgeBox		 创建输入框		：成功返回输入文本，否则返回false
		EXPORTDLL(editBox);


		// bowserBox	 创建选择框		: 成功返回路径，否则返回false
		EXPORTDLL(bowserBox);


		// htmlBox		 创建html窗口	: 成功返回true，否则返回false
		EXPORTDLL(htmlBox);


		// urlBox		 创建url窗口	: 成功返回true，否则返回false
		EXPORTDLL(urlBox);


		// hideControl    隐藏控制台		: 成功则返回true，否则返回false
		EXPORTDLL(hideControl);


		// showControl    显示控制台		: 成功则返回true，否则返回false
		EXPORTDLL(showControl);

	}
}


#endif
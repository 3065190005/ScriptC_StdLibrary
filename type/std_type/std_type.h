#pragma once
#ifndef __CERVER_STD_STD_TYPE__
#define __CERVER_STD_STD_TYPE__

#define Fname(var) void __system__type__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

namespace Cervice {
	namespace Obj {
		// isAlpha    检测字符串是否纯字母		: 是则返回true，否则返回false
		EXPORTDLL(isAlpha);
		// isAlnum	  检测字符串是否纯数字		: 是则返回true，否则返回false
		EXPORTDLL(isAlnum);
		// hasBlank	  检测字符串是否含有空格		: 是则返回true，否则返回false
		EXPORTDLL(hasBlank);
		// isBlank	  检测字符串是否纯空格		: 是则返回true，否则返回false
		EXPORTDLL(isBlank);
		// hasCntrl	  检测字符串是否含有控制符		: 是则返回true，否则返回false
		EXPORTDLL(hasCntrl);
		// isCntrl	  检测字符串是否全控制符		：是则返回true，否则返回false
		EXPORTDLL(isCntrl);
		// isLower	  检测字符串是否全小写		: 是则返回true，否则返回false
		EXPORTDLL(isLower);
		// isUpper	  检测字符串是否全大写		：是则返回true，否则返回false
		EXPORTDLL(isUpper);
	}
}


// isAlpha    检测字符串是否纯字母		: 是则返回true，否则返回false
// isAlnum	  检测字符串是否纯数字		: 是则返回true，否则返回false
// hasBlank	  检测字符串是否含有空格		: 是则返回true，否则返回false
// isBlank	  检测字符串是否纯空格		: 是则返回true，否则返回false
// hasCntrl	  检测字符串是否含有控制符		: 是则返回true，否则返回false
// isCntrl	  检测字符串是否全控制符		：是则返回true，否则返回false
// isLower	  检测字符串是否全小写		: 是则返回true，否则返回false
// isUpper	  检测字符串是否全大写		：是则返回true，否则返回false

#endif


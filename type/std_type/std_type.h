#pragma once
#ifndef __CERVER_STD_STD_TYPE__
#define __CERVER_STD_STD_TYPE__

#define Fname(var) void __system__type__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

namespace ScriptC {
	namespace Obj {
		using namespace AutoMem::Obj;


	}
}


// isAlpha    ����ַ����Ƿ���ĸ		: ���򷵻�true�����򷵻�false
// isAlnum	  ����ַ����Ƿ�����		: ���򷵻�true�����򷵻�false
// hasBlank	  ����ַ����Ƿ��пո�		: ���򷵻�true�����򷵻�false
// isBlank	  ����ַ����Ƿ񴿿ո�		: ���򷵻�true�����򷵻�false
// hasCntrl	  ����ַ����Ƿ��п��Ʒ�		: ���򷵻�true�����򷵻�false
// isCntrl	  ����ַ����Ƿ�ȫ���Ʒ�		�����򷵻�true�����򷵻�false
// isLower	  ����ַ����Ƿ�ȫСд		: ���򷵻�true�����򷵻�false
// isUpper	  ����ַ����Ƿ�ȫ��д		�����򷵻�true�����򷵻�false

#endif


#pragma once
#ifndef __CERVER_STD_STD_TIME__
#define __CERVER_STD_STD_TIME__

#define Fname(var) void __system__time__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"


namespace ScriptC {
	namespace Obj {
		using namespace AutoMem::Obj;

		// time		获得时间戳（秒 : （void） -> 返回数字时间戳，否则返回null
		EXPORTDLL(time);

		// timeAsM	获得时间戳（毫秒 : （void） -> 返回数字时间戳，否则返回null
		EXPORTDLL(timeAsM);

		// clock	获得程序运行时间（秒 : （void） -> 返回数字时间，否则返回null
		EXPORTDLL(clock);

		// clockAsM	获得程序运行时间（毫秒 : （void） -> 返回数字时间，否则返回null
		EXPORTDLL(clockAsM);

		// cast 将秒转换成某个时间 (6年，5月，4日，3时，2分，1秒 0毫秒 : 源数字，类型 -> 转换成功返回数字，否则返回null
		EXPORTDLL(cast);

		// castAsM 将毫秒转换成某个时间 (6年，5月，4日，3时，2分，1秒 0毫秒 : 源数字，类型 -> 转换成功返回数字，否则返回null
		EXPORTDLL(castAsM);

		// join 创建一个计时器 : (void) -> 设置成功返回数字计时器Id，否则返回null
		EXPORTDLL(join);

		// start 继续一个计时器 ： 数字计时器id -> 继续成功返回true,否则返回false
		EXPORTDLL(start);

		// pause 暂停一个计时器 ： 数字计时器id -> 暂停成功返回true,否则返回false
		EXPORTDLL(pause);

		// over 获取一个计时器 ： 数字计时器id -> 成功返回计数秒，否则返回null
		EXPORTDLL(over);

		// overAsM 获取一个计时器 ： 数字计时器id -> 成功返回计数毫秒，否则返回null
		EXPORTDLL(overAsM);

		// date 获取系统日期 ： (void) -> 成功返回日期字符串，否则返回null
		EXPORTDLL(date);

		// dateAsM 获取系统日期 (毫秒 ： (void) -> 成功返回日期字符串，否则返回null
		EXPORTDLL(dateAsM);

		// toDate 将秒时间戳转换成日期 ： 数字秒时间戳 -> 成功返回日期字符串，否则返回null
		EXPORTDLL(toDate);
		
		// toDateAsM 将毫秒时间戳转换成日期 ： 数字毫秒时间戳 -> 成功返回日期字符串，否则返回null
		EXPORTDLL(toDateAsM);
	}
}

#endif


#pragma once
#ifndef __CERVER_STD_STD_OS__
#define __CERVER_STD_STD_OS__

#define Fname(var) void __system__os__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

/*
* 参考 stdlib.h 头文件内容
* https://blog.csdn.net/Chnyac/article/details/82745298
*/

namespace Cervice {
	namespace Obj {
		
		// abort	终止程序 : (void) -> (void)
		EXPORTDLL(abort);

		// exit		退出程序	: 退出码 -> (void)
		EXPORTDLL(exit);

		// str		转换字符串 : 参数 -> 成功返回字符串，失败返回null
		EXPORTDLL(str);

		// number	转换数字 : 参数 -> 成功返回数字，失败返回null
		EXPORTDLL(number);

		// bool		转换布尔 : 参数 -> 成功返回布尔值，失败返回null
		EXPORTDLL(bool);

		// type		返回参数类型 : 参数 -> 返回指定变量类型
		EXPORTDLL(type);

		// hex      获取16进制 : 参数 -> 成功返回number，失败返回null
		EXPORTDLL(hex);

		// oct		获取8进制  : 参数 -> 成功返回number, 失败返回null
		EXPORTDLL(oct);
		
		// bit		获取2进制  : 参数 -> 成功返回number, 失败返回null
		EXPORTDLL(bin);

		// getenv	获取环境 : 环境名字 -> 成功返回环境内容字符串，失败返回null
		EXPORTDLL(getenv);

		// putenv   创建修改删除环境变量 : 名称 , 参数 -> 成功返回true 失败返回false
		EXPORTDLL(putenv);
		
		// system	系统命令 : 命令 -> 执行成功返回true 失败返回false
		EXPORTDLL(system);

		// sleep    睡眠命令 ：数字 -> 成功返回睡眠时间 , 失败返回null
		EXPORTDLL(sleep);

		// argv		获取启动参数 : (void) -> 返回数组
		EXPORTDLL(argv);

		// -- 隐藏 设置命令行参数和数量
		extern "C" _declspec(dllimport)
			void __system___setArgv__(void* param, void* count);
	}
}

#endif
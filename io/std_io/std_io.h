#pragma once
#ifndef _CERVER_STD_STD_IO_
#define _CERVER_STD_STD_IO_

#define Fname(var) void __system__io__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

/* 
* 参考 stdio.h 头文件内容
* https://blog.csdn.net/weiyuanzhuo/article/details/52291206
*/

namespace Cervice {
	namespace Obj {
	
	// 文件访问
		// fopen  打开文件 : 文件名 打开方式 -> 成功返回文件Id 失败返回false
		EXPORTDLL(fopen);

		// fclose 关闭文件 : 文件ID -> 成功返回true 失败返回false
		EXPORTDLL(fclose);

	// 二进制输入/输出
		// fread  文件读取 : 文件ID 大小(小于-2 剩余全部 等于-1 剩余最近行) -> 成功返回读取内容 失败返回false
		EXPORTDLL(fread);

		// fwrite 文件写入 : 文件ID 内容 大小(小于0 全部) -> 成功返回输入字节数 失败返回false
		EXPORTDLL(fwrite);

	// 文件定位
		// ftell 当前文件位置 : 文件ID -> 成功返回位置 失败返回false
		EXPORTDLL(ftell);

		// fseek 移动文件位置 : 文件ID 位置 偏移 -> 成功返回true 失败返回false
		EXPORTDLL(fseek);

	// 错误处理
		// errset 设置错误号  : 内容 -> (void)
		EXPORTDLL(errset);
		
		// errget 获取错误号  : (void) -> 有返回内容字符串，否则返回false
		EXPORTDLL(errget);

	// 文件操作
		// tmpfile 临时文件		: (void) -> 成功返回id 失败返回false
		EXPORTDLL(tmpfile);

		// frename 文件重命名	: 原文件名 目标文件名 -> 成功返回true 失败返回false
		EXPORTDLL(frename);

		// fremove 文件删除		: 文件名 -> 删除返回true 否则返回false
		EXPORTDLL(fremove);
		
		// fcreate 文件创建		: 文件名 -> 创建返回true 否则返回false
		EXPORTDLL(fcreate);

		// fexist  文件存在		: 文件名 -> 存在返回true 否则返回false
		EXPORTDLL(fexist);

	// 标准输入/输出
		// print 标准输出 : 可变类型和数量 -> (void)
		EXPORTDLL(print);

		// input 标准输入 : (void) -> 标准输入返回值
		EXPORTDLL(input);

	}
}

#endif
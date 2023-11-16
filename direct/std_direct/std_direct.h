#pragma once
#ifndef __CERVER_STD_STD_ARRAY__
#define __CERVER_STD_STD_ARRAY__

#define Fname(var) void __system__direct__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"
#include "Public/AutoObject/LetArrayMotion.h"

/*
* 参考 python path 处理
* https://zhuanlan.zhihu.com/p/351605959
*/

namespace ScriptC {
	namespace Obj {

		using namespace AutoMem::Obj;

		// chdir		改变当前工作目录		：字符串 -> 成功true，否则返回错误码
		EXPORTDLL(chdir);

		// getcwd		返回当前工作目录		：void -> 成功字符串，否则返回null
		EXPORTDLL(getcwd);

		// listdir		返回指定的文件夹包含的文件或文件夹的名字的列表。		：字符串 -> 成功数组，否则返回错误码
		EXPORTDLL(listdir);

		// chmod  设置目录或文件权限	: 字符串 | 数字 -> 成功返回true，否则返回错误码
		EXPORTDLL(chmod);

		// makedirs		递归创建目录。		：字符串 -> 成功返回true，否则返回错误码
		EXPORTDLL(makedirs);

		// mkdir		创建目录。		：字符串 -> 成功true，否则返回错误码
		EXPORTDLL(mkdir);

		// removedirs		递归删除目录。		：字符串 -> 成功true，否则返回错误码
		EXPORTDLL(removedirs);

		// rmdir		删除目录。		：字符串 -> 成功true，否则返回错误码
		EXPORTDLL(rmdir);

		// rename		重命名目录名。		：字符串 | 字符串 -> 成功true，否则返回错误码
		EXPORTDLL(rename);

		// stat 		 方法用于在给定的路径上执行一个系统 stat 的调用		：字符串 -> 成功数组，否则返回错误码
		EXPORTDLL(stat);

		// abspath 		 返回绝对路径	：字符串 -> 成功字符串，否则返回错误码
		EXPORTDLL(abspath);

		// relative 	返回相对路径	：字符串 -> 成功字符串，否则返回错误码
		EXPORTDLL(relative);

		// basename 		 返回文件名	：字符串 -> 成功字符串，否则返回错误码
		EXPORTDLL(basename);

		// commonprefix 		 返回多个路径中，所有共有的最长的路径	：数组 -> 成功字符串，否则返回null
		EXPORTDLL(commonprefix);

		// dirname 		 返回文件路径	：字符串 -> 成功字符串，否则返回错误码
		EXPORTDLL(dirname);

		// exists 		 路径是否存在	：字符串 -> 成功true，否则返回false
		EXPORTDLL(exists);

		// expand 		根据环境变量的值替换%字符串%值	：字符串 -> 成功字符串，否则返回错误码
		EXPORTDLL(expand);

		// getatime 		返回最近访问时间	：字符串 -> 成功数字，否则返回错误码
		EXPORTDLL(getatime);

		// getmtime 		返回最近文件修改时间	：字符串 -> 成功数字，否则返回错误码
		EXPORTDLL(getmtime);

		// getctime 		返回文件创建时间	：字符串 -> 成功数字，否则返回错误码
		EXPORTDLL(getctime);

		// getsize 		返回文件大小	：字符串 -> 成功数字，否则返回错误码
		EXPORTDLL(getsize);

		// isabs 			判断是否为绝对路径	：字符串 -> 成功true，否则返回false
		EXPORTDLL(isabs);

		// isfile 			判断路径是否为文件	：字符串 -> 成功true，否则返回false
		EXPORTDLL(isfile);

		// isdir 			判断路径是否为目录	：字符串 -> 成功true，否则返回false
		EXPORTDLL(isdir);

		// normcase 		将路径字符串的大写和正斜杠转换	：字符串 -> 成功字符串，否则返回错误码
		EXPORTDLL(normcase);

		// normpath 		规范路径字符串形式	：字符串 -> 成功字符串，否则返回错误码
		EXPORTDLL(normpath);

		// info 		获得相对信息	：字符串 -> 成功数组，否则返回错误码
		EXPORTDLL(info);

		// samefile 		判断目录或文件是否相同 ：字符串|字符串 -> 成功返回数字，否则返回错误码
		EXPORTDLL(samefile);
	}
}

#endif
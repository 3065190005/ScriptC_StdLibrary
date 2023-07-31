#pragma once
#ifndef __CERVER_STD_STD_STRING__
#define __CERVER_STD_STD_STRING__

#define Fname(var) void __system__str__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

/*
* 参考 python string 处理
* https://www.w3school.com.cn/python/python_ref_string.asp
* 参考 string.h 头文件
* https://www.runoob.com/cprogramming/c-standard-library-string-h.html
*/

namespace ScriptC {
	namespace Obj {
		using namespace AutoMem::Obj;
		// split	拆分字符串 : 源字符串，分隔符 -> 拆分成功返回数组，否则返回null
		EXPORTDLL(split);

		// cut      分割指定字符串 : 源字符串，分隔符 -> 拆分成功返回数组，否则返回null
		EXPORTDLL(cut);

		// sub      剪切指定字符串 : 目标字符串，开始位置，个数(-1剩余全部) -> 剪切成功返回字符串，否则返回null
		EXPORTDLL(sub);

		// replace  替换指定内容 : 字符串，源内容，替换内容，替换次数(-1全部) -> 替换成功返回替换后的字符串，否则返回null
		EXPORTDLL(replace);

		// at		获取字符串下标 : 字符串，下标 -> 返回指定下标字符，失败返回null
		EXPORTDLL(at);

		// erase    删除指定字符串 : 字符串，下标，长度 -> 返回删除后的字符串，失败返回null
		EXPORTDLL(erase);

		// insert   在某个位置插入字符串 : 字符串，下标，内容 -> 返回插入后总字符串，失败返回null
		EXPORTDLL(insert);

		// lens		获取字符串总长度 : 字符串 -> 返回字符串长度,失败返回null
		EXPORTDLL(lens);

		// reverse  字符串反转	: 字符串 -> 返回翻转后的字符串，失败返回null
		EXPORTDLL(reverse);

		// fill  字符串填充	： 字符串，位置，长度，内容 -> 返回填充后的总字符串，失败返回null
		EXPORTDLL(fill);

		// lower	将字符串转换为大写 : 字符串 -> 返回转换字符串，失败返回null
		EXPORTDLL(lower);

		// upper	将字符串转换为大写 : 字符串 -> 返回转换字符串，失败返回null
		EXPORTDLL(upper);

		// tirm     删除头尾空白符 : 字符串 -> 返回处理后的字符串，失败返回null
		EXPORTDLL(tirm);

		// up      将首字母大写 : 字符串 -> 返回处理后的字符串，失败返回null
		EXPORTDLL(up);

		// low     将首字母小写 : 字符串 -> 返回处理后的字符串，失败返回null
		EXPORTDLL(low);

		// count   返回字符串出现的次数 : 字符串，目标 -> 返回目标出现次数，失败返回null
		EXPORTDLL(count);

		// find_all        正向查找全部下标		: 字符串，内容 -> 查找成功返回数组，失败返回null
		EXPORTDLL(find_all);

		// find_first      正向查找第一个下标		：字符串，内容 -> 查找成功返回数字，失败返回null
		EXPORTDLL(find_first);

		// find_N          正向查找N个下标		：字符串，内容，次数 -> 查找成功返回数组，失败返回null
		EXPORTDLL(find_N);

		// find_not_all    正向查找全部not下标	：字符串，内容 -> 查找成功返回二维数组，失败返回null
		EXPORTDLL(find_not_all);
		
		// find_not_first  正向查找第一个not下标	: 字符串，内容 -> 查找成功返回数组，失败返回null
		EXPORTDLL(find_not_first);

		// find_not_N      正向查找N个not下标		: 字符串，内容，次数 -> 查找成功返回二维数组，失败返回null
		EXPORTDLL(find_not_N);

		// rfind_frist		 反向查找第一个下标		:	字符串，内容 -> 成功返回数字，失败返回null
		EXPORTDLL(rfind_first);

		// rfind_N			 反向查找N个下标			:	字符串，内容，次数 -> 成功返回数组，失败返回null
		EXPORTDLL(rfind_N);

		// rfind_not_first	 反向查找第一个not下标	:	字符串，内容	-> 成功返回数组，失败返回null
		EXPORTDLL(rfind_not_first);

		// rfind_not_N		 反向查找N个not下标		:	字符串，内容，次数 -> 成功返回二维数组，失败返回null
		EXPORTDLL(rfind_not_N);
	}
}

#endif
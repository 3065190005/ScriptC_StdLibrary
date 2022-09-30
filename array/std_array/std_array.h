#pragma once
#ifndef __CERVER_STD_STD_ARRAY__
#define __CERVER_STD_STD_ARRAY__

#define Fname(var) void __system__vec__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"
#include "Public/AutoObject/LetArrayMotion.h"

/*
* 参考 python list 处理
* https://zhuanlan.zhihu.com/p/351605959
*/

namespace Cervice {
	namespace Obj {
		// size		返回数组总个数		：数组 -> 成功返回个数，否则返回null
		EXPORTDLL(size);

		// cmp		比较两个数组			：数组1，数组2 -> 成功对比结果返回数字，否则返回null (相等返回0,1大返回数组-11，否则返回1)
		EXPORTDLL(cmp);

		// max		返回列表最大值		：数组 -> 成功返回最大值，否则返回null
		EXPORTDLL(max);

		// min		返回列表最小元素		：数组 -> 成功返回最小值，否则返回null
		EXPORTDLL(min);

		// append	在末尾添加元素		：数组，任意 -> 成功返回添加后的数组，否则返回null
		EXPORTDLL(append);
		
		// count	检测某个元素的个数	：数组，任意 -> 成功返回个数，否则返回null
		EXPORTDLL(count);
		
		// extend	在末尾添加			：数组，任意 -> 成功返回添加后的新数组，否则返回null
		EXPORTDLL(extend);
		
		// back		返回最后一个元素		：数组 -> 成功返回末尾元素，否则返回null
		EXPORTDLL(back);
		
		// front	返回第一个元素		：数组 -> 成功返回开头元素，否则返回null
		EXPORTDLL(front);
		
		// index	查找指定元素第一次位置：数组，任意 -> 成功查找返回下标，否则返回null
		EXPORTDLL(index);

		// insert	将指定内容插入指定位置：数组，下标，任意 -> 成功返回插入后的新数组，否则返回null
		EXPORTDLL(insert);
		
		// pop		删除数组指定内容		：数组，下标	-> 成功返回删除后的新数组，否则返回null
		EXPORTDLL(pop);
		
		// remove	移除数组指定的第一个值：数组，任意 -> 成功返回移除后的新数组，否则返回null
		EXPORTDLL(remove);

		// reverse	反序					：数组	-> 成功返回新数组，否则返回null
		EXPORTDLL(reverse);
		
		// range	范围					：数字1，数组2 -> 成功返回基于数组1和数字2范围区间的数组，否则返回null
		EXPORTDLL(range);
		
		// childs	返回数组所有下标		：数组 -> 成功将该数组的所有下标作为数组返回，失败返回null
		EXPORTDLL(childs);
	}
}

#endif
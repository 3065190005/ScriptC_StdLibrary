#pragma once
#ifndef __CERVER_STD_STD_ARRAY__
#define __CERVER_STD_STD_ARRAY__

#define Fname(var) void __system__vec__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"
#include "Public/AutoObject/LetArrayMotion.h"

/*
* �ο� python list ����
* https://zhuanlan.zhihu.com/p/351605959
*/

namespace Cervice {
	namespace Obj {
		// size		���������ܸ���		������ -> �ɹ����ظ��������򷵻�null
		EXPORTDLL(size);

		// cmp		�Ƚ���������			������1������2 -> �ɹ��ԱȽ���������֣����򷵻�null (��ȷ���0,1�󷵻�����-11�����򷵻�1)
		EXPORTDLL(cmp);

		// max		�����б����ֵ		������ -> �ɹ��������ֵ�����򷵻�null
		EXPORTDLL(max);

		// min		�����б���СԪ��		������ -> �ɹ�������Сֵ�����򷵻�null
		EXPORTDLL(min);

		// append	��ĩβ���Ԫ��		�����飬���� -> �ɹ�������Ӻ�����飬���򷵻�null
		EXPORTDLL(append);
		
		// count	���ĳ��Ԫ�صĸ���	�����飬���� -> �ɹ����ظ��������򷵻�null
		EXPORTDLL(count);
		
		// extend	��ĩβ���			�����飬���� -> �ɹ�������Ӻ�������飬���򷵻�null
		EXPORTDLL(extend);
		
		// back		�������һ��Ԫ��		������ -> �ɹ�����ĩβԪ�أ����򷵻�null
		EXPORTDLL(back);
		
		// front	���ص�һ��Ԫ��		������ -> �ɹ����ؿ�ͷԪ�أ����򷵻�null
		EXPORTDLL(front);
		
		// index	����ָ��Ԫ�ص�һ��λ�ã����飬���� -> �ɹ����ҷ����±꣬���򷵻�null
		EXPORTDLL(index);

		// insert	��ָ�����ݲ���ָ��λ�ã����飬�±꣬���� -> �ɹ����ز����������飬���򷵻�null
		EXPORTDLL(insert);
		
		// pop		ɾ������ָ������		�����飬�±�	-> �ɹ�����ɾ����������飬���򷵻�null
		EXPORTDLL(pop);
		
		// remove	�Ƴ�����ָ���ĵ�һ��ֵ�����飬���� -> �ɹ������Ƴ���������飬���򷵻�null
		EXPORTDLL(remove);

		// reverse	����					������	-> �ɹ����������飬���򷵻�null
		EXPORTDLL(reverse);
		
		// range	��Χ					������1������2 -> �ɹ����ػ�������1������2��Χ��������飬���򷵻�null
		EXPORTDLL(range);
		
		// childs	�������������±�		������ -> �ɹ���������������±���Ϊ���鷵�أ�ʧ�ܷ���null
		EXPORTDLL(childs);
	}
}

#endif
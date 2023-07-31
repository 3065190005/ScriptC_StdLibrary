#pragma once
#ifndef __CERVER_STD_STD_STRING__
#define __CERVER_STD_STD_STRING__

#define Fname(var) void __system__str__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

/*
* �ο� python string ����
* https://www.w3school.com.cn/python/python_ref_string.asp
* �ο� string.h ͷ�ļ�
* https://www.runoob.com/cprogramming/c-standard-library-string-h.html
*/

namespace ScriptC {
	namespace Obj {
		using namespace AutoMem::Obj;
		// split	����ַ��� : Դ�ַ������ָ��� -> ��ֳɹ��������飬���򷵻�null
		EXPORTDLL(split);

		// cut      �ָ�ָ���ַ��� : Դ�ַ������ָ��� -> ��ֳɹ��������飬���򷵻�null
		EXPORTDLL(cut);

		// sub      ����ָ���ַ��� : Ŀ���ַ�������ʼλ�ã�����(-1ʣ��ȫ��) -> ���гɹ������ַ��������򷵻�null
		EXPORTDLL(sub);

		// replace  �滻ָ������ : �ַ�����Դ���ݣ��滻���ݣ��滻����(-1ȫ��) -> �滻�ɹ������滻����ַ��������򷵻�null
		EXPORTDLL(replace);

		// at		��ȡ�ַ����±� : �ַ������±� -> ����ָ���±��ַ���ʧ�ܷ���null
		EXPORTDLL(at);

		// erase    ɾ��ָ���ַ��� : �ַ������±꣬���� -> ����ɾ������ַ�����ʧ�ܷ���null
		EXPORTDLL(erase);

		// insert   ��ĳ��λ�ò����ַ��� : �ַ������±꣬���� -> ���ز�������ַ�����ʧ�ܷ���null
		EXPORTDLL(insert);

		// lens		��ȡ�ַ����ܳ��� : �ַ��� -> �����ַ�������,ʧ�ܷ���null
		EXPORTDLL(lens);

		// reverse  �ַ�����ת	: �ַ��� -> ���ط�ת����ַ�����ʧ�ܷ���null
		EXPORTDLL(reverse);

		// fill  �ַ������	�� �ַ�����λ�ã����ȣ����� -> ������������ַ�����ʧ�ܷ���null
		EXPORTDLL(fill);

		// lower	���ַ���ת��Ϊ��д : �ַ��� -> ����ת���ַ�����ʧ�ܷ���null
		EXPORTDLL(lower);

		// upper	���ַ���ת��Ϊ��д : �ַ��� -> ����ת���ַ�����ʧ�ܷ���null
		EXPORTDLL(upper);

		// tirm     ɾ��ͷβ�հ׷� : �ַ��� -> ���ش������ַ�����ʧ�ܷ���null
		EXPORTDLL(tirm);

		// up      ������ĸ��д : �ַ��� -> ���ش������ַ�����ʧ�ܷ���null
		EXPORTDLL(up);

		// low     ������ĸСд : �ַ��� -> ���ش������ַ�����ʧ�ܷ���null
		EXPORTDLL(low);

		// count   �����ַ������ֵĴ��� : �ַ�����Ŀ�� -> ����Ŀ����ִ�����ʧ�ܷ���null
		EXPORTDLL(count);

		// find_all        �������ȫ���±�		: �ַ��������� -> ���ҳɹ��������飬ʧ�ܷ���null
		EXPORTDLL(find_all);

		// find_first      ������ҵ�һ���±�		���ַ��������� -> ���ҳɹ��������֣�ʧ�ܷ���null
		EXPORTDLL(find_first);

		// find_N          �������N���±�		���ַ��������ݣ����� -> ���ҳɹ��������飬ʧ�ܷ���null
		EXPORTDLL(find_N);

		// find_not_all    �������ȫ��not�±�	���ַ��������� -> ���ҳɹ����ض�ά���飬ʧ�ܷ���null
		EXPORTDLL(find_not_all);
		
		// find_not_first  ������ҵ�һ��not�±�	: �ַ��������� -> ���ҳɹ��������飬ʧ�ܷ���null
		EXPORTDLL(find_not_first);

		// find_not_N      �������N��not�±�		: �ַ��������ݣ����� -> ���ҳɹ����ض�ά���飬ʧ�ܷ���null
		EXPORTDLL(find_not_N);

		// rfind_frist		 ������ҵ�һ���±�		:	�ַ��������� -> �ɹ��������֣�ʧ�ܷ���null
		EXPORTDLL(rfind_first);

		// rfind_N			 �������N���±�			:	�ַ��������ݣ����� -> �ɹ��������飬ʧ�ܷ���null
		EXPORTDLL(rfind_N);

		// rfind_not_first	 ������ҵ�һ��not�±�	:	�ַ���������	-> �ɹ��������飬ʧ�ܷ���null
		EXPORTDLL(rfind_not_first);

		// rfind_not_N		 �������N��not�±�		:	�ַ��������ݣ����� -> �ɹ����ض�ά���飬ʧ�ܷ���null
		EXPORTDLL(rfind_not_N);
	}
}

#endif
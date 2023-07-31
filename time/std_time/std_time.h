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

		// time		���ʱ������� : ��void�� -> ��������ʱ��������򷵻�null
		EXPORTDLL(time);

		// timeAsM	���ʱ��������� : ��void�� -> ��������ʱ��������򷵻�null
		EXPORTDLL(timeAsM);

		// clock	��ó�������ʱ�䣨�� : ��void�� -> ��������ʱ�䣬���򷵻�null
		EXPORTDLL(clock);

		// clockAsM	��ó�������ʱ�䣨���� : ��void�� -> ��������ʱ�䣬���򷵻�null
		EXPORTDLL(clockAsM);

		// cast ����ת����ĳ��ʱ�� (6�꣬5�£�4�գ�3ʱ��2�֣�1�� 0���� : Դ���֣����� -> ת���ɹ��������֣����򷵻�null
		EXPORTDLL(cast);

		// castAsM ������ת����ĳ��ʱ�� (6�꣬5�£�4�գ�3ʱ��2�֣�1�� 0���� : Դ���֣����� -> ת���ɹ��������֣����򷵻�null
		EXPORTDLL(castAsM);

		// join ����һ����ʱ�� : (void) -> ���óɹ��������ּ�ʱ��Id�����򷵻�null
		EXPORTDLL(join);

		// start ����һ����ʱ�� �� ���ּ�ʱ��id -> �����ɹ�����true,���򷵻�false
		EXPORTDLL(start);

		// pause ��ͣһ����ʱ�� �� ���ּ�ʱ��id -> ��ͣ�ɹ�����true,���򷵻�false
		EXPORTDLL(pause);

		// over ��ȡһ����ʱ�� �� ���ּ�ʱ��id -> �ɹ����ؼ����룬���򷵻�null
		EXPORTDLL(over);

		// overAsM ��ȡһ����ʱ�� �� ���ּ�ʱ��id -> �ɹ����ؼ������룬���򷵻�null
		EXPORTDLL(overAsM);

		// date ��ȡϵͳ���� �� (void) -> �ɹ����������ַ��������򷵻�null
		EXPORTDLL(date);

		// dateAsM ��ȡϵͳ���� (���� �� (void) -> �ɹ����������ַ��������򷵻�null
		EXPORTDLL(dateAsM);

		// toDate ����ʱ���ת�������� �� ������ʱ��� -> �ɹ����������ַ��������򷵻�null
		EXPORTDLL(toDate);
		
		// toDateAsM ������ʱ���ת�������� �� ���ֺ���ʱ��� -> �ɹ����������ַ��������򷵻�null
		EXPORTDLL(toDateAsM);
	}
}

#endif


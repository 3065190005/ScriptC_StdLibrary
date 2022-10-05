#pragma once
#ifndef __CERVER_STD_STD_OS__
#define __CERVER_STD_STD_OS__

#define Fname(var) void __system__os__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

/*
* �ο� stdlib.h ͷ�ļ�����
* https://blog.csdn.net/Chnyac/article/details/82745298
*/

namespace Cervice {
	namespace Obj {
		
		// abort	��ֹ���� : (void) -> (void)
		EXPORTDLL(abort);

		// exit		�˳�����	: �˳��� -> (void)
		EXPORTDLL(exit);

		// str		ת���ַ��� : ���� -> �ɹ������ַ�����ʧ�ܷ���null
		EXPORTDLL(str);

		// number	ת������ : ���� -> �ɹ��������֣�ʧ�ܷ���null
		EXPORTDLL(number);

		// bool		ת������ : ���� -> �ɹ����ز���ֵ��ʧ�ܷ���null
		EXPORTDLL(bool);

		// type		���ز������� : ���� -> ����ָ����������
		EXPORTDLL(type);

		// hex      ��ȡ16���� : ���� -> �ɹ�����number��ʧ�ܷ���null
		EXPORTDLL(hex);

		// oct		��ȡ8����  : ���� -> �ɹ�����number, ʧ�ܷ���null
		EXPORTDLL(oct);
		
		// bit		��ȡ2����  : ���� -> �ɹ�����number, ʧ�ܷ���null
		EXPORTDLL(bin);

		// getenv	��ȡ���� : �������� -> �ɹ����ػ��������ַ�����ʧ�ܷ���null
		EXPORTDLL(getenv);

		// putenv   �����޸�ɾ���������� : ���� , ���� -> �ɹ�����true ʧ�ܷ���false
		EXPORTDLL(putenv);
		
		// system	ϵͳ���� : ���� -> ִ�гɹ�����true ʧ�ܷ���false
		EXPORTDLL(system);

		// sleep    ˯������ ������ -> �ɹ�����˯��ʱ�� , ʧ�ܷ���null
		EXPORTDLL(sleep);

		// argv		��ȡ�������� : (void) -> ��������
		EXPORTDLL(argv);

		// -- ���� ���������в���������
		extern "C" _declspec(dllimport)
			void __system___setArgv__(void* param, void* count);
	}
}

#endif
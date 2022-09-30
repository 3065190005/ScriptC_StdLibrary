#pragma once
#ifndef _CERVER_STD_STD_IO_
#define _CERVER_STD_STD_IO_

#define Fname(var) void __system__io__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

/* 
* �ο� stdio.h ͷ�ļ�����
* https://blog.csdn.net/weiyuanzhuo/article/details/52291206
*/

namespace Cervice {
	namespace Obj {
	
	// �ļ�����
		// fopen  ���ļ� : �ļ��� �򿪷�ʽ -> �ɹ������ļ�Id ʧ�ܷ���false
		EXPORTDLL(fopen);

		// fclose �ر��ļ� : �ļ�ID -> �ɹ�����true ʧ�ܷ���false
		EXPORTDLL(fclose);

	// ����������/���
		// fread  �ļ���ȡ : �ļ�ID ��С(С��-2 ʣ��ȫ�� ����-1 ʣ�������) -> �ɹ����ض�ȡ���� ʧ�ܷ���false
		EXPORTDLL(fread);

		// fwrite �ļ�д�� : �ļ�ID ���� ��С(С��0 ȫ��) -> �ɹ����������ֽ��� ʧ�ܷ���false
		EXPORTDLL(fwrite);

	// �ļ���λ
		// ftell ��ǰ�ļ�λ�� : �ļ�ID -> �ɹ�����λ�� ʧ�ܷ���false
		EXPORTDLL(ftell);

		// fseek �ƶ��ļ�λ�� : �ļ�ID λ�� ƫ�� -> �ɹ�����true ʧ�ܷ���false
		EXPORTDLL(fseek);

	// ������
		// errset ���ô����  : ���� -> (void)
		EXPORTDLL(errset);
		
		// errget ��ȡ�����  : (void) -> �з��������ַ��������򷵻�false
		EXPORTDLL(errget);

	// �ļ�����
		// tmpfile ��ʱ�ļ�		: (void) -> �ɹ�����id ʧ�ܷ���false
		EXPORTDLL(tmpfile);

		// frename �ļ�������	: ԭ�ļ��� Ŀ���ļ��� -> �ɹ�����true ʧ�ܷ���false
		EXPORTDLL(frename);

		// fremove �ļ�ɾ��		: �ļ��� -> ɾ������true ���򷵻�false
		EXPORTDLL(fremove);
		
		// fcreate �ļ�����		: �ļ��� -> ��������true ���򷵻�false
		EXPORTDLL(fcreate);

		// fexist  �ļ�����		: �ļ��� -> ���ڷ���true ���򷵻�false
		EXPORTDLL(fexist);

	// ��׼����/���
		// print ��׼��� : �ɱ����ͺ����� -> (void)
		EXPORTDLL(print);

		// input ��׼���� : (void) -> ��׼���뷵��ֵ
		EXPORTDLL(input);

	}
}

#endif
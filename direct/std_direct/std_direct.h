#pragma once
#ifndef __CERVER_STD_STD_ARRAY__
#define __CERVER_STD_STD_ARRAY__

#define Fname(var) void __system__direct__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"
#include "Public/AutoObject/LetArrayMotion.h"

/*
* �ο� python path ����
* https://zhuanlan.zhihu.com/p/351605959
*/

namespace ScriptC {
	namespace Obj {

		using namespace AutoMem::Obj;

		// chdir		�ı䵱ǰ����Ŀ¼		���ַ��� -> �ɹ�true�����򷵻ش�����
		EXPORTDLL(chdir);

		// getcwd		���ص�ǰ����Ŀ¼		��void -> �ɹ��ַ��������򷵻�null
		EXPORTDLL(getcwd);

		// listdir		����ָ�����ļ��а������ļ����ļ��е����ֵ��б�		���ַ��� -> �ɹ����飬���򷵻ش�����
		EXPORTDLL(listdir);

		// chmod  ����Ŀ¼���ļ�Ȩ��	: �ַ��� | ���� -> �ɹ�����true�����򷵻ش�����
		EXPORTDLL(chmod);

		// makedirs		�ݹ鴴��Ŀ¼��		���ַ��� -> �ɹ�����true�����򷵻ش�����
		EXPORTDLL(makedirs);

		// mkdir		����Ŀ¼��		���ַ��� -> �ɹ�true�����򷵻ش�����
		EXPORTDLL(mkdir);

		// removedirs		�ݹ�ɾ��Ŀ¼��		���ַ��� -> �ɹ�true�����򷵻ش�����
		EXPORTDLL(removedirs);

		// rmdir		ɾ��Ŀ¼��		���ַ��� -> �ɹ�true�����򷵻ش�����
		EXPORTDLL(rmdir);

		// rename		������Ŀ¼����		���ַ��� | �ַ��� -> �ɹ�true�����򷵻ش�����
		EXPORTDLL(rename);

		// stat 		 ���������ڸ�����·����ִ��һ��ϵͳ stat �ĵ���		���ַ��� -> �ɹ����飬���򷵻ش�����
		EXPORTDLL(stat);

		// abspath 		 ���ؾ���·��	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(abspath);

		// relative 	�������·��	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(relative);

		// basename 		 �����ļ���	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(basename);

		// commonprefix 		 ���ض��·���У����й��е����·��	������ -> �ɹ��ַ��������򷵻�null
		EXPORTDLL(commonprefix);

		// dirname 		 �����ļ�·��	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(dirname);

		// exists 		 ·���Ƿ����	���ַ��� -> �ɹ�true�����򷵻�false
		EXPORTDLL(exists);

		// expand 		���ݻ���������ֵ�滻%�ַ���%ֵ	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(expand);

		// getatime 		�����������ʱ��	���ַ��� -> �ɹ����֣����򷵻ش�����
		EXPORTDLL(getatime);

		// getmtime 		��������ļ��޸�ʱ��	���ַ��� -> �ɹ����֣����򷵻ش�����
		EXPORTDLL(getmtime);

		// getctime 		�����ļ�����ʱ��	���ַ��� -> �ɹ����֣����򷵻ش�����
		EXPORTDLL(getctime);

		// getsize 		�����ļ���С	���ַ��� -> �ɹ����֣����򷵻ش�����
		EXPORTDLL(getsize);

		// isabs 			�ж��Ƿ�Ϊ����·��	���ַ��� -> �ɹ�true�����򷵻�false
		EXPORTDLL(isabs);

		// isfile 			�ж�·���Ƿ�Ϊ�ļ�	���ַ��� -> �ɹ�true�����򷵻�false
		EXPORTDLL(isfile);

		// isdir 			�ж�·���Ƿ�ΪĿ¼	���ַ��� -> �ɹ�true�����򷵻�false
		EXPORTDLL(isdir);

		// normcase 		��·���ַ����Ĵ�д����б��ת��	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(normcase);

		// normpath 		�淶·���ַ�����ʽ	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(normpath);

		// info 		��������Ϣ	���ַ��� -> �ɹ����飬���򷵻ش�����
		EXPORTDLL(info);

		// samefile 		�ж�Ŀ¼���ļ��Ƿ���ͬ ���ַ���|�ַ��� -> �ɹ��������֣����򷵻ش�����
		EXPORTDLL(samefile);
	}
}

#endif
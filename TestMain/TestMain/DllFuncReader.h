#pragma once
#ifndef _CERVER_DLL_DLLFUNCREADER_
#define _CERVER_DLL_DLLFUNCREADER_

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <unordered_map>

#include "LetObject/LetManager.h"
#include "LetObject/LetObject.h"

namespace Cervice {
	namespace Obj {

		using funcPtr = void (*)(void*, void*);

		class DllFuncReader
		{
		public:
			static DllFuncReader* getInstance();
		private:
			DllFuncReader() {};
			~DllFuncReader() {};

		private:
			static DllFuncReader* m_instance; // ����

		public:
			static int m_hasInit;		// �Ƿ��ʼ��
			static std::string m_Libs;	// dlls����Ŀ¼
			static std::unordered_map<std::string, HINSTANCE> m_GlobalHandle;	// dll�ļ����Ͷ�Ӧʵ��ָ��
			static std::unordered_map<std::string, HINSTANCE> m_FuncTables;		// �������Ͷ�Ӧ��������dllʵ��ָ��


		protected:
			bool loadLib();				// ��������dll
			void releasedLib();			// ж��dll

		public:
			funcPtr getFuncFromDll(std::string _func_name);							// ��dll��ȡ����ָ��
			void callFunc(funcPtr func, std::vector<auto_c>* param, auto_c* ret);	// ���ú���ָ��

		private:
			// single gc
			class dllGc {
			public:
				~dllGc();
			};
		};
	}
}

#endif


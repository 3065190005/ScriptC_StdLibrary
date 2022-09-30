#pragma once
#ifndef _CERVER_LETMANAGER__
#define _CERVER_LETMANAGER__

#include "letMacro.h"
#include <list>

namespace Cervice {
	namespace Obj {

		class LetManager
		{
		public:
			enum class bType
			{
				None = 0,
				Static = 1,
				Dynamic = 2
			};

			typedef struct _block	// �ڴ��
			{
				char* ptr = nullptr;				// ��
				size_t ref = 0;						// ����
				size_t lens = 0;					// ����
				bool isArray = false;				// �Ƿ�����
				std::list<_block*>::iterator iter;	// ָ������
			}Block;

			static std::list<Block*>::iterator void_ptr; // ��nullptr

		public: // ���캯��
			LetManager();
			~LetManager();

		public: // ��̬����
			static LetManager* getInstance();	// ��ȡ����

		public: // ���ú���
			Block* malloc_L(bool type);		// ��ȡ��
			void free_L(Block**);			// ���տ�
			void realloc_L(Block**, size_t);	// ���·���

		private: // �ڲ�����
			bool initialize();		// ��ʼ��
			void destory();			// ����

			bool joinMemery();		// �ڴ�����

		protected:
		class Gc { public:~Gc(); };		// �ڴ����GC

		private: // ����
			bool m_init_success;				// �ɹ���ʼ��
			static LetManager* m_instance;		// ��̬

			size_t m_free_count;				// �������
			size_t m_malloc_count;				// ���ÿ���
			std::list<Block*> m_Free_Blocks;	// �����
			std::list<Block*> m_Malloc_Blocks;	// ��ʹ��

			size_t m_free_count_d;					// ������� Dymanic
			size_t m_malloc_count_d;				// ���ÿ��� Dymanic
			std::list<Block*> m_Free_Blocks_D;		// ����� Dymanic
			std::list<Block*> m_Malloc_Blocks_D;	// ��ʹ�� Dymanic
		};

		using Block = struct LetManager::Block;
		using Ptr = std::list<Block*>::iterator;
		using rPtr = std::list<Block*>::reverse_iterator;

	}
}

#endif
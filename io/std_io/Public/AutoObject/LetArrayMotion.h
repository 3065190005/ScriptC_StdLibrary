#pragma once
#ifndef _CERVER_LETARRAYMOTION__
#define _CERVER_LETARRAYMOTION__

#include "LetManager.h"
#include "LetObject.h"

#include <optional>
#include <variant>

namespace Cervice {
	namespace Obj {

		/**********
		* ���������
		* ��֧��ԭ�����������ʶ��ָ��
		***********/
		class LetArrayMotion
		{
		public:

		/**********************
		* �ַ����Ա�  
		* cmp1 == cmp2 -> 0
		* cmp1 > cmp2 -> -1
		* cmp1 < cmp2 -> 1
		* error -> 2
		**********************/
		public: 
			static numberT ArrayCmp(LetObject* cmp1, LetObject* cmp2);
		private:
			static numberT cmpNum(LetObject*, LetObject*);
			static numberT cmpStr(LetObject*, LetObject*);

		/**********************
		* �����ַ������ֵ
		* �ɹ��������ֵ�����򷵻�null
		**********************/
		public: 
			static LetObject ArrayMax(LetObject*);

		/**********************
		* �����ַ�����Сֵ
		* �ɹ�������Сֵ�����򷵻�null
		**********************/
		public:
			static LetObject ArrayMin(LetObject*);

		/**********************
		* ĩβ���Ԫ��
		* �ɹ�����true�����򷵻�false
		**********************/
		public:
			static bool ArrayAppend(LetObject*,LetObject*);

			template<typename... Ts>
			static bool ArrayAppends(LetObject* var, LetObject* va1, Ts... args);
			static bool ArrayAppends(LetObject* var) { return true; };

		/**********************
		* ���Ԫ�س��ִ���
		* �ɹ����ش��������򷵻�-1
		**********************/
		public:
			static numberT ArrayCount(LetObject*, LetObject*);

		/**********************
		* ��Ŀ��չ����ӵ�����ĩβ
		* �ɹ�����true�����򷵻�false
		**********************/
		public:
			static bool ArrayExtend(LetObject*, LetObject*);

		/**********************
		* �����������һ��Ԫ��
		* �ɹ�����Ԫ��
		**********************/
		public:
			static std::optional<LetObject> ArrayBack(LetObject*);

		/**********************
		* ���������һ��Ԫ��
		* �ɹ�����Ԫ��
		**********************/
		public:
			static std::optional<LetObject> ArrayFront(LetObject*);


		/**********************
		* ����ָ����һ�������Ϊ��
		* �ɹ������±�
		**********************/
		public:
			static std::optional<std::variant<numberT,std::string>> 
				ArrayIndex(LetObject*,LetObject*);

		/**********************
		* ��ָ���±���洫����Ԫ��
		* �ɹ�����true�����򷵻�false
		**********************/
		public:
			static bool ArrayInsert(LetObject*, numberT,LetObject*);
		private:
			static bool ArrayInsertNum(LetObject*, numberT, LetObject*);

		/**********************
		* ɾ��ָ���±�Ԫ��
		* �ɹ�����true�����򷵻�false
		**********************/
		public:
			static bool ArrayPop(LetObject* var, std::variant<numberT, std::string> index);

		/**********************
		* ɾ��ָ���ĵ�һ��ֵ
		* �ɹ�����true�����򷵻�false
		**********************/
		public:
			static bool ArrayRemove(LetObject* var, LetObject* tar);

		/**********************
		* ��������Ԫ��
		* �ɹ�����true�����򷵻�false
		**********************/
		public:
			static bool ArrayReverse(LetObject* var);

		/**********************
		* ��������Ԫ��
		* �ɹ�����true�����򷵻�false
		**********************/
		public:
			static LetObject ArrayRange(numberT , numberT);

		/**********************
		* �����������±귵��
		* �ɹ��������飬���򷵻�null
		**********************/
		public:
			static LetObject ArrayChilds(LetObject*);

		};


		#include "LetArrayMotion.tpp"
	}
}

#endif


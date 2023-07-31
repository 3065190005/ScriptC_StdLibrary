#include "std_array.h"
#include "QuickLib/quicklib.h"

#define Fname(var) void __system__vec__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllexport) Fname(var)
#define RESULT(var) auto_c*var = (auto_c*)ret; *var = auto_c(false,false)
#define PARAMS(var) std::vector<auto_c>* var = (std::vector<auto_c>*)param
#define PTR(var) (*var)

#include <algorithm>
#include <optional>
#include <variant>

namespace {
	class Funcs {
	public:
		template<typename T>
		static T getParam(std::vector<T>* param);

		template<typename T, typename ... Args>
		static void getParams(std::vector<T>* params, T* pam, Args ...pams);
	};


	template<typename T>
	T Funcs::getParam(std::vector<T>* param)
	{
		T ret;
		ret = param->back();
		param->pop_back();
		return ret;
	}

	template<typename T, typename ... Args>
	void Funcs::getParams(std::vector<T>* params, T* pam, Args ...pams)
	{
		auto call = [&](std::vector<T>* param) {
			T ret;
			ret = param->back();
			param->pop_back();
			return ret;
		};

		(*pam) = call(params);
		(((*pams) = call(params)), ...);
	}
}

namespace ScriptC {
	namespace Obj {

		using namespace AutoMem::Obj;

		EXPORTDLL(size) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params,&value1);
			if (value1.getType() != LetObject::ObjT::array)
			{
				return;
			}

			numberT count = static_cast<numberT>(value1.getNumArray().size() + value1.getStrArray().size());
			PTR(rets) << count;
			return;
		}

		EXPORTDLL(cmp) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1,value2;
			Funcs::getParams<LetObject>(params, &value2,&value1);
			if (value1.getType() != LetObject::ObjT::array||
				value2.getType() != LetObject::ObjT::array)
			{
				return;
			}

			numberT count = LetArrayMotion::ArrayCmp(&value1, &value2);
			if (count == 2) {
				return;
			}

			PTR(rets) << count;

			return;
		}

		EXPORTDLL(max) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::array)
			{
				return;
			}

			auto_c maxVal = LetArrayMotion::ArrayMax(&value1);
			PTR(rets) = maxVal;
			return;
		}

		EXPORTDLL(min) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::array)
			{
				return;
			}

			auto_c maxVal = LetArrayMotion::ArrayMin(&value1);
			PTR(rets) = maxVal;
			return;
		}

		// append	在末尾添加元素		：数组，任意 -> 成功返回添加后的数组，否则返回null
		EXPORTDLL(append) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1,value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);
			if (value1.getType() != LetObject::ObjT::array)
			{
				return;
			}

			bool bol = LetArrayMotion::ArrayAppend(&value1, &value2);
			if (!bol) return;
			PTR(rets) = value1;
			return;
		}

		// count	检测某个元素的个数	：数组，任意 -> 成功返回个数，否则返回null
		EXPORTDLL(count) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);
			if (value1.getType() != LetObject::ObjT::array)
			{
				return;
			}

			numberT bol = LetArrayMotion::ArrayCount(&value1, &value2);
			if (bol == -1) return;
			PTR(rets) << bol;
			return;
		}

		// extend	在末尾添加			：数组，任意 -> 成功返回添加后的新数组，否则返回null
		EXPORTDLL(extend) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);
			if (value1.getType() != LetObject::ObjT::array)
			{
				return;
			}

			bool bol = LetArrayMotion::ArrayExtend(&value1, &value2);
			if (!bol) return;
			PTR(rets) = value1;
			return;
		}

		// back		返回最后一个元素		：数组 -> 成功返回末尾元素，否则返回null
		EXPORTDLL(back) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::array)
			{
				return;
			}

			auto has = LetArrayMotion::ArrayBack(&value1);
			if (!has.has_value()) return;
			PTR(rets) = *has;
			return;
		}

		// front	返回第一个元素		：数组 -> 成功返回开头元素，否则返回null
		EXPORTDLL(front) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::array)
			{
				return;
			}

			auto has = LetArrayMotion::ArrayFront(&value1);
			if (!has.has_value()) return;
			PTR(rets) = *has;
			return;
		}

		// index	查找指定元素第一次位置：数组，任意 -> 成功查找返回下标，否则返回null
		EXPORTDLL(index) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);
			if (value1.getType() != LetObject::ObjT::array)
			{
				return;
			}

			auto has = LetArrayMotion::ArrayIndex(&value1, &value2);
			if (!has.has_value()) return;

			if (has->index() == 0) {
				PTR(rets) << std::get<numberT>(*has);
			}
			else {
				PTR(rets) << std::get<std::string>(*has);
			}
			return;
		}

		// insert	将指定内容插入指定位置：数组，下标，任意 -> 成功返回插入后的新数组，否则返回null
		EXPORTDLL(insert) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2 ,value3;
			Funcs::getParams<LetObject>(params,&value3,&value2, &value1);
			if (value1.getType() != LetObject::ObjT::array||
				value2.getType() != LetObject::ObjT::number)
			{
				return;
			}

			numberT index;
			value2 >> index;
			auto has = LetArrayMotion::ArrayInsert(&value1, index, &value3);
			if (!has) return;

			PTR(rets) = value1;

			return;
		}

		// pop		删除数组指定内容		：数组，下标	-> 成功返回删除后的新数组，否则返回null
		EXPORTDLL(pop) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);
			if (value1.getType() != LetObject::ObjT::array ||
				(value2.getType() != LetObject::ObjT::number &&
				value2.getType() != LetObject::ObjT::string))
			{
				return;
			}

			bool has = false;
			if (value2.getType() == LetObject::ObjT::number) {
				numberT index;
				value2 >> index;
				has = LetArrayMotion::ArrayPop(&value1, index);
			}
			else{
				std::string index;
				value2 >> index;
				has = LetArrayMotion::ArrayPop(&value1, index);
			}
			if (!has) return;

			PTR(rets) = value1;

			return;
		}


		EXPORTDLL(remove) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);
			if (value1.getType() != LetObject::ObjT::array)
			{
				return;
			}

			bool has = false;
			has = LetArrayMotion::ArrayRemove(&value1, &value2);
			if (!has) return;

			PTR(rets) = value1;
		}

		EXPORTDLL(reverse) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::array)
			{
				return;
			}

			bool has = false;
			has = LetArrayMotion::ArrayReverse(&value1);
			if (!has) return;

			PTR(rets) = value1;
		}

		EXPORTDLL(range) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1,value2;
			Funcs::getParams<LetObject>(params, &value2,&value1);
			if (value1.getType() != LetObject::ObjT::number||
				value2.getType() != LetObject::ObjT::number)
			{
				return;
			}

			numberT num1, num2;
			value1 >> num1;
			value2 >> num2;
			auto_c rang = LetArrayMotion::ArrayRange(num1, num2);
			if (rang.getType() == LetObject::ObjT::null) {
				return;
			}

			PTR(rets) = rang;
		}

		EXPORTDLL(childs) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::array)
			{
				return;
			}

			auto_c has;
			has = LetArrayMotion::ArrayChilds(&value1);
			PTR(rets) = has;
		}
	}
}
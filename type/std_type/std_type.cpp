#include "std_type.h"
#include "QuickLib/quicklib.h"

#define Fname(var) void __system__type__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllexport) Fname(var)
#define RESULT(var) auto_c*var = (auto_c*)ret; *var = auto_c(false,false)
#define PARAMS(var) std::vector<auto_c>* var = (std::vector<auto_c>*)param
#define PTR(var) (*var)

#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>


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

namespace Cervice {
	namespace Obj {
		// isAlpha    检测字符串是否纯字母		: 是则返回true，否则返回false
		EXPORTDLL(isAlpha) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << false;
				return;
			}
			std::string track;
			value1 >> track;

			for (auto& i : track) {
				if (!isalpha(i)) {
					PTR(rets) << false;
					return;
				}
			}

			PTR(rets) << true;
			return;
		}

		// isAlnum	  检测字符串是否纯数字		: 是则返回true，否则返回false
		EXPORTDLL(isAlnum) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << false;
				return;
			}

			std::string track;
			value1 >> track;

			for (auto& i : track) {
				if (!isalnum(i)) {
					PTR(rets) << false;
					return;
				}
			}

			PTR(rets) << true;
			return;
		}
		
		// hasBlank	  检测字符串是否含有空格		: 是则返回true，否则返回false
		EXPORTDLL(hasBlank) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << false;
				return;
			}

			std::string track;
			value1 >> track;

			for (auto& i : track) {
				if (isblank(i)) {
					PTR(rets) << true;
					return;
				}
			}

			PTR(rets) << false;
			return;
		}
		
		// isBlank	  检测字符串是否纯空格		: 是则返回true，否则返回false
		EXPORTDLL(isBlank) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << false;
				return;
			}

			std::string track;
			value1 >> track;

			for (auto& i : track) {
				if (!isblank(i)) {
					PTR(rets) << false;
					return;
				}
			}

			PTR(rets) << true;
			return;
		}
		
		// hasCntrl	  检测字符串是否含有控制符		: 是则返回true，否则返回false
		EXPORTDLL(hasCntrl) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << false;
				return;
			}

			std::string track;
			value1 >> track;

			for (auto& i : track) {
				if (iscntrl(i)) {
					PTR(rets) << true;
					return;
				}
			}

			PTR(rets) << false;
			return;
		}
		
		// isCntrl	  检测字符串是否全控制符		：是则返回true，否则返回false
		EXPORTDLL(isCntrl) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << false;
				return;
			}

			std::string track;
			value1 >> track;

			for (auto& i : track) {
				if (!iscntrl(i)) {
					PTR(rets) << false;
					return;
				}
			}

			PTR(rets) << true;
			return;
		}
		// isLower	  检测字符串是否全小写		: 是则返回true，否则返回false
		EXPORTDLL(isLower) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << false;
				return;
			}

			std::string track;
			value1 >> track;

			for (auto& i : track) {
				if (!islower(i)) {
					PTR(rets) << false;
					return;
				}
			}

			PTR(rets) << true;

			return;
		}
		// isUpper	  检测字符串是否全大写		：是则返回true，否则返回false
		EXPORTDLL(isUpper) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << false;
				return;
			}

			std::string track;
			value1 >> track;

			for (auto& i : track) {
				if (!isupper(i)) {
					PTR(rets) << false;
					return;
				}
			}

			PTR(rets) << true;

			return;
		}
	}
}
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
		// isAlpha    ����ַ����Ƿ���ĸ		: ���򷵻�true�����򷵻�false
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

		// isAlnum	  ����ַ����Ƿ�����		: ���򷵻�true�����򷵻�false
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
		
		// hasBlank	  ����ַ����Ƿ��пո�		: ���򷵻�true�����򷵻�false
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
		
		// isBlank	  ����ַ����Ƿ񴿿ո�		: ���򷵻�true�����򷵻�false
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
		
		// hasCntrl	  ����ַ����Ƿ��п��Ʒ�		: ���򷵻�true�����򷵻�false
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
		
		// isCntrl	  ����ַ����Ƿ�ȫ���Ʒ�		�����򷵻�true�����򷵻�false
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
		// isLower	  ����ַ����Ƿ�ȫСд		: ���򷵻�true�����򷵻�false
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
		// isUpper	  ����ַ����Ƿ�ȫ��д		�����򷵻�true�����򷵻�false
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
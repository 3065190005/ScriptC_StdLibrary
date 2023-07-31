#include "std_string.h"
#include "QuickLib/quicklib.h"

#define Fname(var) void __system__str__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllexport) Fname(var)
#define RESULT(var) auto_c*var = (auto_c*)ret; *var = auto_c(false,false)
#define PARAMS(var) std::vector<auto_c>* var = (std::vector<auto_c>*)param
#define PTR(var) (*var)

#include <algorithm>

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

	template<typename T,typename ... Args>
	void Funcs::getParams(std::vector<T>* params ,T* pam , Args ...pams)
	{
		auto call = [&](std::vector<T>* param) {
			T ret;
			ret = param->back();
			param->pop_back();
			return ret;
		};

		(*pam) = call(params);
		(((*pams) = call(params)),...);
	}
}


namespace ScriptC {
	namespace Obj {
		using namespace AutoMem::Obj;

		EXPORTDLL(split) {
			PARAMS(params);
			RESULT(rets);

			auto value2 = Funcs::getParam<LetObject>(params);
			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);
			std::string va2 = LetObject::cast<std::string>(value2);
			auto vecS = kstring::stringSplit(va1, va2);
			for (auto i = 0; i < vecS.size(); i ++) {
				PTR(rets)[i] << vecS.at(i);
			}

			return;
		}

		EXPORTDLL(cut) {
			PARAMS(params);
			RESULT(rets);

			auto value2 = Funcs::getParam<LetObject>(params);
			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);
			std::string va2 = LetObject::cast<std::string>(value2);

			auto opt = kstring::cutString(va1, va2);
			if (opt.has_value()) {
				PTR(rets)[0] << opt->first;
				PTR(rets)[1] << opt->second;
			}

			return;
		}

		EXPORTDLL(sub) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2, value3;
			Funcs::getParams<LetObject>(params, &value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::number ||
				value3.getType() != LetObject::ObjT::number )
			{
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);
			numberT va2 = LetObject::cast<numberT>(value2);
			numberT va3 = LetObject::cast<numberT>(value3);

			if (va2 > va1.length()) {
				return;
			}

			if (va3 <= 0)
				va1 = va1.substr(va2);
			else
				va1 = va1.substr(va2, va3);

			PTR(rets) << va1;

			return;
		}

		EXPORTDLL(replace) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2, value3,value4;
			Funcs::getParams<LetObject>(params, &value4, &value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string ||
				value3.getType() != LetObject::ObjT::string ||
				value4.getType() != LetObject::ObjT::number )
			{
				return;
			}

			numberT va4;
			std::string va1, va2, va3;
			va1 = LetObject::cast<std::string>(value1);
			va2 = LetObject::cast<std::string>(value2);
			va3 = LetObject::cast<std::string>(value3);
			va4 = LetObject::cast<numberT>(value4);

			va1 = kstring::StringReplace(va1, va2, va3, va4);

			PTR(rets) << va1;
			return;
		}

		EXPORTDLL(at) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::number )
			{
				return;
			}

			std::string va1;
			numberT va2;
			va1 = LetObject::cast<std::string>(value1);
			va2 = LetObject::cast<numberT>(value2);

			if (va1.length() < va2) {
				return;
			}

			PTR(rets) << va1.substr(va2, 1);
			return;
		}

		EXPORTDLL(erase) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2, value3;
			Funcs::getParams<LetObject>(params, &value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::number ||
				value3.getType() != LetObject::ObjT::number)
			{
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);
			numberT va2 = LetObject::cast<numberT>(value2);
			numberT va3 = LetObject::cast<numberT>(value3);

			if (va2 > va1.length()) {
				return;
			}

			if (va3 <= 0 || va2+va3 >= va1.length()) {
				va1 = va1.substr(0, va2);
			}
			else {
				std::string first = va1.substr(0, va2);
				std::string second = va1.substr(va2 + va3);
				va1 = first + second;
			}

			PTR(rets) << va1;
		}

		EXPORTDLL(insert) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2, value3;
			Funcs::getParams<LetObject>(params, &value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::number ||
				value3.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);
			numberT va2 = LetObject::cast<numberT>(value2);
			std::string va3 = LetObject::cast<std::string>(value3);

			if (va2 > va1.length()) {
				return;
			}
			else {
				va1.insert(va2, va3);
			}

			PTR(rets) << va1;
		}

		EXPORTDLL(lens) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::string){
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);
			
			PTR(rets) << (numberT)va1.length();
		}

		EXPORTDLL(reverse) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::string) {
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);

			std::reverse(va1.begin(), va1.end());
			PTR(rets) << va1;
		}

		EXPORTDLL(fill) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2, value3,value4;
			Funcs::getParams<LetObject>(params, &value4, &value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::number ||
				value3.getType() != LetObject::ObjT::number ||
				value4.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);
			numberT va2 = LetObject::cast<numberT>(value2);
			numberT va3 = LetObject::cast<numberT>(value3);
			std::string va4 = LetObject::cast<std::string>(value4);

			if (va2 > va1.length()) {
				return;
			}
			else {
				numberT len, lens,pos;
				std::string space = va1;
				pos = va2;
				lens = va3;
				len = va4.length();
				while (lens >= len) {
					space.insert(pos, va4);
					lens -= len;
					pos += len;
				}

				if (lens != 0) {
					space.insert(pos, va4.substr(0,lens));
				}

				va1 = space;
			}

			PTR(rets) << va1;
		}

		EXPORTDLL(lower) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::string) {
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);

			va1 = kstring::StringToLower(va1);
			PTR(rets) << va1;
		}

		EXPORTDLL(upper) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::string) {
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);

			va1 = kstring::StringToUpper(va1);
			PTR(rets) << va1;
		}

		EXPORTDLL(tirm) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::string) {
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);

			va1 = kstring::StringTirm(va1);
			PTR(rets) << va1;
		}

		EXPORTDLL(up) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::string) {
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);

			if (va1.length() > 0) {
				if (va1[0] >= 'a' && va1[0] <= 'z') {
					va1[0] -= ' ';
				}
			}

			PTR(rets) << va1;
		}

		EXPORTDLL(low) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::string) {
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);

			if (va1.length() > 0) {
				if (va1[0] >= 'A' && va1[0] <= 'Z') {
					va1[0] += ' ';
				}
			}

			PTR(rets) << va1;
		}

		EXPORTDLL(count) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string va1,va2;
			va1 = LetObject::cast<std::string>(value1);
			va2 = LetObject::cast<std::string>(value2);

			auto cnt = kstring::StringCount(va1, va2);
			PTR(rets) << static_cast<numberT>(cnt);

			return;
		}

		EXPORTDLL(find_all) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string va1, va2;
			va1 = LetObject::cast<std::string>(value1);
			va2 = LetObject::cast<std::string>(value2);

			numberT index = 0;
			auto VecN = kstring::StringFindIndex(va1, va2, -1);
			if (VecN.empty()) {
				return;
			}

			for (auto i = 0; i < VecN.size(); i++) {
				PTR(rets)[i] << static_cast<numberT>(VecN.at(i));
			}

			return;
		}

		EXPORTDLL(find_first) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string va1, va2;
			va1 = LetObject::cast<std::string>(value1);
			va2 = LetObject::cast<std::string>(value2);

			numberT index = 0;
			auto VecN = kstring::StringFindIndex(va1, va2, 1);
			if (VecN.empty()) {
				return;
			}

			PTR(rets) << static_cast<numberT>(VecN.at(0));

			return;
		}

		EXPORTDLL(find_N) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2,value3;
			Funcs::getParams<LetObject>(params,&value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string ||
				value3.getType() != LetObject::ObjT::number)
			{
				return;
			}

			numberT va3 = 0;
			std::string va1, va2;
			va1 = LetObject::cast<std::string>(value1);
			va2 = LetObject::cast<std::string>(value2);
			va3 = LetObject::cast<numberT>(value3);

			numberT index = 0;
			auto VecN = kstring::StringFindIndex(va1, va2, static_cast<size_t>(va3));
			if (VecN.empty()) {
				return;
			}

			for (auto i = 0; i < VecN.size(); i++) {
				PTR(rets)[i] << static_cast<numberT>(VecN.at(i));
			}

			return;
		}

		EXPORTDLL(find_not_all) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string va1, va2;
			va1 = LetObject::cast<std::string>(value1);
			va2 = LetObject::cast<std::string>(value2);

			numberT index = 0;
			auto VecN = kstring::StringNotFindIndex(va1, va2, -1);
			if (VecN.empty()) {
				return;
			}

			for (auto i = 0; i < VecN.size(); i++) {
				PTR(rets)[i][0] << static_cast<numberT>(VecN.at(i).first);
				PTR(rets)[i][1] << VecN.at(i).second;
			}

			return;
		}

		EXPORTDLL(find_not_first) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string va1, va2;
			va1 = LetObject::cast<std::string>(value1);
			va2 = LetObject::cast<std::string>(value2);

			numberT index = 0;
			auto VecN = kstring::StringNotFindIndex(va1, va2, 1);
			if (VecN.empty()) {
				return;
			}
			
			PTR(rets)[0] << static_cast<numberT>(VecN.at(0).first);
			PTR(rets)[1] << VecN.at(0).second;

			return;
		}

		EXPORTDLL(find_not_N) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2, value3;
			Funcs::getParams<LetObject>(params, &value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string ||
				value3.getType() != LetObject::ObjT::number)
			{
				return;
			}

			numberT va3 = 0;
			std::string va1, va2;
			va1 = LetObject::cast<std::string>(value1);
			va2 = LetObject::cast<std::string>(value2);
			va3 = LetObject::cast<numberT>(value3);

			numberT index = 0;
			auto VecN = kstring::StringNotFindIndex(va1, va2, static_cast<size_t>(va3));
			if (VecN.empty()) {
				return;
			}

			for (auto i = 0; i < VecN.size(); i++) {
				PTR(rets)[i][0] << static_cast<numberT>(VecN.at(i).first);
				PTR(rets)[i][1] << VecN.at(i).second;
			}

			return;
		}

		EXPORTDLL(rfind_first) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string va1, va2;
			va1 = LetObject::cast<std::string>(value1);
			va2 = LetObject::cast<std::string>(value2);

			numberT index = 0;
			auto VecN = kstring::StringrFindIndex(va1, va2, 1);
			if (VecN.empty()) {
				return;
			}

			PTR(rets) << static_cast<numberT>(VecN.at(0));

			return;
		}

		EXPORTDLL(rfind_N) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2, value3;
			Funcs::getParams<LetObject>(params, &value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string ||
				value3.getType() != LetObject::ObjT::number)
			{
				return;
			}

			numberT va3 = 0;
			std::string va1, va2;
			va1 = LetObject::cast<std::string>(value1);
			va2 = LetObject::cast<std::string>(value2);
			va3 = LetObject::cast<numberT>(value3);

			numberT index = 0;
			auto VecN = kstring::StringrFindIndex(va1, va2, static_cast<size_t>(va3));
			if (VecN.empty()) {
				return;
			}

			for (auto i = 0; i < VecN.size(); i++) {
				PTR(rets)[i] << static_cast<numberT>(VecN.at(i));
			}

			return;
		}

		EXPORTDLL(rfind_not_first) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string va1, va2;
			va1 = LetObject::cast<std::string>(value1);
			va2 = LetObject::cast<std::string>(value2);

			numberT index = 0;
			auto VecN = kstring::StringNotrFindIndex(va1, va2, 1);
			if (VecN.empty()) {
				return;
			}

			PTR(rets)[0] << static_cast<numberT>(VecN.at(0).first);
			PTR(rets)[1] << VecN.at(0).second;

			return;
		}

		EXPORTDLL(rfind_not_N) {
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2, value3;
			Funcs::getParams<LetObject>(params, &value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string ||
				value3.getType() != LetObject::ObjT::number)
			{
				return;
			}

			numberT va3 = 0;
			std::string va1, va2;
			va1 = LetObject::cast<std::string>(value1);
			va2 = LetObject::cast<std::string>(value2);
			va3 = LetObject::cast<numberT>(value3);

			numberT index = 0;
			auto VecN = kstring::StringNotrFindIndex(va1, va2, static_cast<size_t>(va3));
			if (VecN.empty()) {
				return;
			}

			for (auto i = 0; i < VecN.size(); i++) {
				PTR(rets)[i][0] << static_cast<numberT>(VecN.at(i).first);
				PTR(rets)[i][1] << VecN.at(i).second;
			}

			return;
		}
	}
}
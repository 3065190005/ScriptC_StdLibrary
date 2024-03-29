#include "std_os.h"
#include "QuickLib/quicklib.h"

#include <vector>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define Fname(var) void __system__os__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllexport) Fname(var)
#define RESULT(var) auto_c*var = (auto_c*)ret; *var = auto_c()
#define PARAMS(var) std::vector<auto_c>* var = (std::vector<auto_c>*)param
#define PTR(var) (*var)

#include <algorithm>

namespace {
	class Funcs {
	public:
		template<typename T>
		static T getParam(std::vector<T>* param);
	};


	template<typename T>
	inline T Funcs::getParam(std::vector<T>* param)
	{
		T ret;
		ret = param->back();
		param->pop_back();
		return ret;
	}
}

namespace {
	static char** global_argv;
	static size_t global_argc = 0;
}

namespace ScriptC {
	namespace Obj {
		using namespace AutoMem::Obj;

		EXPORTDLL(abort)
		{
			PARAMS(params);
			RESULT(rets);

			::abort();

			return;
		}

		EXPORTDLL(exit)
		{
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				throw("Vm : function exit need ��number��");
			}
			numberT code = 0;
			value1 >> code;
			exit(static_cast<int>(code));

			return;
		}

		EXPORTDLL(str)
		{
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() == LetObject::ObjT::string) {
				PTR(rets) = value1;
				return;
			}

			switch (value1.getType())
			{
			case LetObject::ObjT::boolean:
			{
				bool bolean = LetObject::cast<bool>(value1);
				PTR(rets) << (bolean == true ? "true" : "false");
				return;
			}
			case LetObject::ObjT::number:
			{
				numberT numb = LetObject::cast<numberT>(value1);
				std::string stri = std::to_string(numb);
				PTR(rets) << stri;
				return;
			}
			default:
				{
					LetTools tools;
					throw("Vm : function str unable to convert ��" + tools.ObjTToStr(value1.getType()) + "��");
					return;
					break;
				}
			}
		}

		EXPORTDLL(number)
		{
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() == LetObject::ObjT::number) {
				PTR(rets) = value1;
				return;
			}

			switch (value1.getType())
			{
			case LetObject::ObjT::boolean:
			{
				bool ret = LetObject::cast<bool>(value1);
				PTR(rets) << (ret == true ? 1 : 0);
				return;
			}
			case LetObject::ObjT::string:
			{
				bool has = true;
				std::string ret = LetObject::cast<std::string>(value1);
				numberT numb = kstring::stringTo<numberT>(ret, &has);
				if (has) {
					PTR(rets) << numb;
				}
				return;
			}
			default:
			{
				LetTools tools;
				throw("Vm : function number unable to convert ��" + tools.ObjTToStr(value1.getType()) + "��");
				return;
				break;
			}
			}
		}

		EXPORTDLL(bool)
		{
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() == LetObject::ObjT::boolean) {
				PTR(rets) = value1;
				return;
			}

			switch (value1.getType())
			{
			case LetObject::ObjT::number:
			{
				numberT numb = LetObject::cast<numberT>(value1);
				bool bol = numb != 0.0 ? true : false;
				PTR(rets) << bol;
				return;
			}
			case LetObject::ObjT::string:
			{
				bool has = false;
				std::string ret = LetObject::cast<std::string>(value1);
				ret = kstring::StringToLower(ret);
				if (!ret.empty() && ret == "true") {
					has = true;
				}

				PTR(rets) << has;
				return;
			}
			default:
			{
				LetTools tools;
				throw("Vm : function bool unable to convert ��" + tools.ObjTToStr(value1.getType()) + "��");
				return;
				break;
			}
			}
		}

		EXPORTDLL(type)
		{
			PARAMS(params);
			RESULT(rets);

			std::string str = "";
			auto value1 = Funcs::getParam<LetObject>(params);

			switch (value1.getType())
			{
			case AutoMem::Obj::LetObject::ObjT::null:
				str = "null";
				break;
			case AutoMem::Obj::LetObject::ObjT::undef:
				str = "undef";
				break;
			case AutoMem::Obj::LetObject::ObjT::boolean:
				str = "boolean";
				break;
			case AutoMem::Obj::LetObject::ObjT::number:
				str = "number";
				break;
			case AutoMem::Obj::LetObject::ObjT::string:
				str = "string";
				break;
			case AutoMem::Obj::LetObject::ObjT::array:
				if ((value1.getAttribute() & (int)NatureType::cls))
					str = "interface";
				else
					str = "array";
				break;
			default:
			{
				LetTools tools;
				throw("Vm : function type unknown type of ��" + tools.ObjTToStr(value1.getType()) + "��");
				return;
				break;
			}
			}

			PTR(rets) << str;
			return;
		}

		EXPORTDLL(hex) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string) {
				throw("Vm : function hex need ��string��");
			}

			auto isNumb = [&](char chr) { if (chr >= '0' && chr <= '9') return true; return false; };
			auto isChar = [&](char chr) { if (chr >= 'A' && chr <= 'F') return true; return false; };

			numberT numb = 0;
			std::string numbstr = LetObject::cast<std::string>(value1);
			numbstr = kstring::StringToUpper(numbstr);
			if (numbstr.size() >= 3 && numbstr[0] == '0' && numbstr[1] == 'X') {
				numbstr = numbstr.substr(2);
				for (auto i = numbstr.begin(); i != numbstr.end(); i++) {
					char chr = *i;
					if (numb != 0) numb *= 0x10;
					if (isNumb(chr)) {
						numb += (numberT)chr - 0x30;
						continue;
					}
					else if (isChar(chr)) {
						numb += (numberT)chr - 0x37;
						continue;
					}
					throw("Vm : function hex string needs to be in the range of ��0 - F��");
					return;
				}
			}
			else {
				throw("Vm : function hex needs to start with the ��0x�� string");
			}

			PTR(rets) << numb;
		}

		EXPORTDLL(oct) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string) {
				throw("Vm : function oct need ��string��");
			}

			auto isNumb = [&](char chr) { if (chr >= '0' && chr <= '7') return true; return false; };

			numberT numb = 0;
			std::string numbstr = LetObject::cast<std::string>(value1);
			numbstr = kstring::StringToUpper(numbstr);
			if (numbstr.size() >= 3 && numbstr[0] == '0' && numbstr[1] == 'O') {
				numbstr = numbstr.substr(2);
				for (auto i = numbstr.begin(); i != numbstr.end(); i++) {
					char chr = *i;
					if (numb != 0) numb *= 8;
					if (isNumb(chr)) {
						numb += (numberT)chr - 0x30;
						continue;
					}
					throw("Vm : function oct string needs to be in the range of ��0 - 7��");
					return;
				}
			}
			else {
				throw("Vm : function oct needs to start with the ��0O�� string");
				return;
			}

			PTR(rets) << numb;
		}

		EXPORTDLL(bin) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string) {
				throw("Vm : function bin need ��string��");
			}

			auto isNumb = [&](char chr) { if (chr >= '0' && chr <= '1') return true; return false; };

			numberT numb = 0;
			std::string numbstr = LetObject::cast<std::string>(value1);
			numbstr = kstring::StringToUpper(numbstr);
			if (numbstr.size() >= 3 && numbstr[0] == '0' && numbstr[1] == 'B') {
				numbstr = numbstr.substr(2);
				for (auto i = numbstr.begin(); i != numbstr.end(); i++) {
					char chr = *i;
					if (numb != 0) numb *= 2;
					if (isNumb(chr)) {
						numb += (numberT)chr - 0x30;
						continue;
					}

					throw("Vm : function bin string must be a number ��0 or 1��");
					return;
				}
			}
			else {
				throw("Vm : function bin needs to start with the ��0B�� string");
			}

			PTR(rets) << numb;
		}

		EXPORTDLL(getenv) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string) {
				throw("Vm : function getenv need ��string��");
			}
			char pathTxt[10240] = { 0 };
			char* ptr_pathTxt = pathTxt;
			std::string path = LetObject::cast<std::string>(value1);
			std::string getPath;
			size_t requiredSize;
			::getenv_s(&requiredSize, NULL, 0, path.c_str());
			if (requiredSize == 0)
				return;

			if (requiredSize >= 10240) {
				ptr_pathTxt = new char[requiredSize + 1]{ 0 };
			}

			::getenv_s(&requiredSize, ptr_pathTxt, requiredSize, path.c_str());
			getPath.append(ptr_pathTxt);
			if (ptr_pathTxt != pathTxt) {
				delete[] ptr_pathTxt;
			}

			PTR(rets) << getPath;
			return;
		}

		EXPORTDLL(putenv) {
			PARAMS(params);
			RESULT(rets);

			auto value2 = Funcs::getParam<LetObject>(params);
			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string) {
				throw("Vm : function putenv need ��string, string��");
			}

			std::string name = LetObject::cast<std::string>(value1);
			std::string txt = LetObject::cast<std::string>(value2);
			errno_t code = ::_putenv_s(name.c_str(), txt.c_str());
			if (code == 0)
				PTR(rets) << true;
			else
				PTR(rets) << false;
			return;
		}

		EXPORTDLL(system) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string) {
				throw("Vm : function system need ��string��");
			}

			std::string commands = LetObject::cast<std::string>(value1);
			errno_t code = ::system(commands.c_str());
			if (code == 0)
				PTR(rets) << true;
			else
				PTR(rets) << false;

			return;
		}

		EXPORTDLL(sleep) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				throw("Vm : function sleep need ��number��");
			}

			numberT commands = LetObject::cast<numberT>(value1);
			::Sleep(commands);
			
			PTR(rets) = value1;
			return;
		}

		EXPORTDLL(argv) {
			PARAMS(params);
			RESULT(rets);

			for (auto i = 0; i < global_argc; i++) {
				PTR(rets)[i] << global_argv[i];
			}

			return;
		}

		extern "C" _declspec(dllexport)
			void __system___setArgv__(void* param, void* count) {
			global_argv = (char**)param;
			global_argc = *(int *)count;
			
			return;
		}
	}
}

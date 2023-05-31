#include "std_window.h"
#include "QuickLib/quicklib.h"
#include <graphics.h>		// ���� EasyX ��ͼ��ͷ�ļ�
#include <conio.h>

#define Fname(var) void __system__fltk_window__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllexport) Fname(var)
#define RESULT(var) auto_c*var = (auto_c*)ret; *var = auto_c(false,false)
#define PARAMS(var) std::vector<auto_c>* var = (std::vector<auto_c>*)param
#define PTR(var) (*var)

#include "main/fltk_pack/windowS.h"


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

// ��ڴ�

namespace Cervice {
	namespace Obj {
		EXPORTDLL(msgBox) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			auto value2 = Funcs::getParam<LetObject>(params);
			auto value3 = Funcs::getParam<LetObject>(params);;

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string||
				value3.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << false;
				return;
			}

			std::string Txt,Title;
			value3 >> Txt;
			value2 >> Title;
			numberT type;
			value1 >> type;

			PTR(rets) << MessageBoxA(NULL, Txt.c_str(), Title.c_str(), (UINT)type);
			return;
		}

		// hideControl    ���ؿ���̨		: �ɹ��򷵻�true�����򷵻�false
		EXPORTDLL(hideControl)
		{
			PARAMS(params);
			RESULT(rets);

			HWND hwnd = GetForegroundWindow();
			if (!hwnd) {
				PTR(rets) << false;
				return;
			}
			ShowWindow(hwnd, SW_HIDE);

			PTR(rets) << true;
			return;
		}


		// showControl    ��ʾ����̨		: �ɹ��򷵻�true�����򷵻�false
		EXPORTDLL(showControl)
		{
			PARAMS(params);
			RESULT(rets);

			HWND hwnd = GetForegroundWindow();
			if (!hwnd) {
				PTR(rets) << false;
				return;
			}
			ShowWindow(hwnd, SW_SHOW);

			PTR(rets) << true;
			return;
		}
	}
}
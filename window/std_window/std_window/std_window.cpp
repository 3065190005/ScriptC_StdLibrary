#include "std_window.h"
#include "QuickLib/quicklib.h"
#include <windows.h>
#include "Shlobj.h"

#include "webbowser.h"
#include "webview2.h"

#define Fname(var) void __system__fltk_window__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllexport) Fname(var)
#define RESULT(var) auto_c*var = (auto_c*)ret; *var = auto_c(false,false)
#define PARAMS(var) std::vector<auto_c>* var = (std::vector<auto_c>*)param
#define PTR(var) (*var)


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

	HWND control_hwnd = NULL;
}


std::string window_bowserBox() {
	std::string ret;
	char szBuffer[MAX_PATH] = { 0 };   //存放选择文件的路径 
	BROWSEINFOA bi;
	ZeroMemory(&bi, sizeof(BROWSEINFOA));
	bi.hwndOwner = NULL;
	bi.pszDisplayName = szBuffer;
	bi.lpszTitle = "从下面选择文件或文件夹:";   //_T()是在头文件tchar.h下的一个宏定义。 
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	LPITEMIDLIST idl = SHBrowseForFolderA(&bi);   //开始选择文件或文件夹
	if (NULL == idl)
	{
		return ret;
	}
	SHGetPathFromIDListA(idl, szBuffer);	//获取完整路径，否则szBuffer只会存储当前选择的文件或文件夹名称
	ret = szBuffer;

	return ret;
}



HWND hwndInput;
char text_buffer[809600];
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
std::string window_InputBox(std::string title,std::string txt) {
	HINSTANCE hInstance = GetModuleHandle(0);

	static TCHAR szAppName[] = L"editBox";
	HWND        hwnd;
	MSG            msg;
	WNDCLASS    wndclass;

	wndclass.lpfnWndProc = WndProc;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.hInstance = hInstance;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClass(&wndclass))
	{
		auto error = GetLastError();
		return "";
	}

	wchar_t m_wchar[255];
	int len = MultiByteToWideChar(CP_ACP, 0, title.c_str(), 254, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, title.c_str(), 254, m_wchar, len);
	m_wchar[254] = '\0';
	
	hwnd = CreateWindow(szAppName, L"ScriptC", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		640, 480,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	SetWindowTextA(hwndInput, txt.c_str());
	ZeroMemory(text_buffer, 809600);

	while (GetMessageA(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnregisterClass(szAppName, hInstance);

	hwndInput = NULL;
	std::string ret;
	ret = text_buffer;
	return ret;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rect;

	static HFONT hFont;
	hFont = CreateFont(
		-16, 8, 0, 100, FW_EXTRALIGHT, false, false, false,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, TEXT("verifyImg")
	);

	switch (message)
	{
	case WM_CREATE:
		hwndInput = CreateWindow(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
			ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
			0, 0, 0, 0,
			hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

		SendMessage(
			hwndInput,  //欲设置字体的控件句柄
			WM_SETFONT,  //消息名（消息类型）
			(WPARAM)hFont,  //字体句柄
			NULL  //传空值即可
		);
		return 0;

	case WM_SIZE:
		GetClientRect(hwnd, &rect);
		MoveWindow(hwndInput, 0, 0, rect.right, rect.bottom, TRUE);
		return 0;

	case WM_DESTROY:
		GetWindowTextA(hwndInput, text_buffer, 809600);
		DeleteObject(hFont);//删除创建的字体
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

namespace Cervice {
	namespace Obj {
		EXPORTDLL(msgBox) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			auto value2 = Funcs::getParam<LetObject>(params);
			auto value3 = Funcs::getParam<LetObject>(params);

			if (value3.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string||
				value1.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << false;
				return;
			}

			std::string Txt,Title;
			value3 >> Title;
			value2 >> Txt;
			numberT type;
			value1 >> type;

			
			PTR(rets) << MessageBoxA(NULL, Txt.c_str(), Title.c_str(), (UINT)type);

			return;
		}


		EXPORTDLL(editBox) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			auto value2 = Funcs::getParam<LetObject>(params);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << false;
				return;
			}

			std::string Txt, Title;
			value1 >> Txt;
			value2 >> Title;

			PTR(rets) << window_InputBox(Title, Txt);
			return;
		}

		EXPORTDLL(bowserBox) {
			PARAMS(params);
			RESULT(rets);

			std::string path = window_bowserBox();
			if (path.empty()) {
				PTR(rets) << false;
				return;
			}

			PTR(rets) << path;
			return;
		}


		EXPORTDLL(htmlBox) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			auto value2 = Funcs::getParam<LetObject>(params);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << false;
				return;
			}

			std::string title,html;
			value2 >> title;
			value1 >> html;

			PTR(rets) << CXWebBrowser::CreateWithHtml(title,html);
			return;
		}


		EXPORTDLL(urlBox) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			auto value2 = Funcs::getParam<LetObject>(params);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << false;
				return;
			}

			std::string title, url;
			value2 >> title;
			value1 >> url;

			PTR(rets) << CXWebBrowser::CreateWithUrl(title, url);
			return;
		}




		// htmlView		 创建webview2 html窗口	: 成功返回true，否则返回false
		EXPORTDLL(htmlView)
		{
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			auto value2 = Funcs::getParam<LetObject>(params);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << false;
				return;
			}

			std::string title, html;
			value2 >> title;
			value1 >> html;

			PTR(rets) << webView2Creater::create_view_with_html(title, html);
			return;
		}


		// urlView		 创建webview2 url窗口	: 成功返回true，否则返回false
		EXPORTDLL(urlView)
		{
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			auto value2 = Funcs::getParam<LetObject>(params);

			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << false;
				return;
			}

			std::string title, url;
			value2 >> title;
			value1 >> url;

			PTR(rets) << webView2Creater::create_view_with_url(title, url);
			return;
		}


		// setWebStyle   设置样式	: 成功返回true，否则返回false
		EXPORTDLL(setWebBoxStyle)
		{
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);

			if (value1.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << false;
				return;
			}

			numberT style;
			value1 >> style;
			CXWebBrowser::window_style = (DWORD)style;

			PTR(rets) << true;
			return;
		}


		// getWebStyle   获取样式	: 成功返回numberT，否则返回false
		EXPORTDLL(getWebBoxStyle)
		{
			PARAMS(params);
			RESULT(rets);

			PTR(rets) << numberT(CXWebBrowser::window_style);
			return;
		}


		// setWebBoxSize  设置大小	: 成功返回true，否则返回false
		EXPORTDLL(setWebBoxSize)
		{
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			auto value2 = Funcs::getParam<LetObject>(params);
			auto value3 = Funcs::getParam<LetObject>(params);
			auto value4 = Funcs::getParam<LetObject>(params);

			if (value1.getType() != LetObject::ObjT::number||
				value2.getType() != LetObject::ObjT::number||
				value3.getType() != LetObject::ObjT::number||
				value4.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << false;
				return;
			}

			numberT left,top,right,bottom;
			value1 >> bottom;
			value2 >> right;
			value3 >> top;
			value4 >> left;

			CXWebBrowser::window_rect = { (LONG)left,(LONG)top,(LONG)right,(LONG)bottom };

			PTR(rets) << true;
			return;
		}


		// getWebBoxSize   获取大小	: 成功返回array，否则返回false
		EXPORTDLL(getWebBoxSize)
		{
			PARAMS(params);
			RESULT(rets);

			PTR(rets)[0] << (numberT)CXWebBrowser::window_rect.left;
			PTR(rets)[1] << (numberT)CXWebBrowser::window_rect.top;
			PTR(rets)[2] << (numberT)CXWebBrowser::window_rect.right;
			PTR(rets)[3] << (numberT)CXWebBrowser::window_rect.bottom;
			return;
		}


		// hideControl    隐藏控制台		: 成功则返回true，否则返回false
		EXPORTDLL(hideControl)
		{
			PARAMS(params);
			RESULT(rets);

			if(control_hwnd == NULL)
				control_hwnd = GetForegroundWindow();
			
			if (!control_hwnd) {
				PTR(rets) << false;
				return;
			}
			ShowWindow(control_hwnd, SW_HIDE);

			PTR(rets) << true;
			return;
		}


		// showControl    显示控制台		: 成功则返回true，否则返回false
		EXPORTDLL(showControl)
		{
			PARAMS(params);
			RESULT(rets);

			if (!control_hwnd) {
				PTR(rets) << false;
				return;
			}
			ShowWindow(control_hwnd, SW_SHOW);

			PTR(rets) << true;
			return;
		}
	}
}
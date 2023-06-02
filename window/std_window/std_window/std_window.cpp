#include "std_window.h"
#include "QuickLib/quicklib.h"
#include <windows.h>
#include "Shlobj.h"

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
}


std::string window_bowserBox() {
	std::string ret;
	char szBuffer[MAX_PATH] = { 0 };   //���ѡ���ļ���·�� 
	BROWSEINFOA bi;
	ZeroMemory(&bi, sizeof(BROWSEINFOA));
	bi.hwndOwner = NULL;
	bi.pszDisplayName = szBuffer;
	bi.lpszTitle = "������ѡ���ļ����ļ���:";   //_T()����ͷ�ļ�tchar.h�µ�һ���궨�塣 
	bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	LPITEMIDLIST idl = SHBrowseForFolderA(&bi);   //��ʼѡ���ļ����ļ���
	if (NULL == idl)
	{
		return ret;
	}
	SHGetPathFromIDListA(idl, szBuffer);	//��ȡ����·��������szBufferֻ��洢��ǰѡ����ļ����ļ�������
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

	if (!RegisterClass(&wndclass))
	{
		auto error = GetLastError();
		return "";
	}

	wchar_t m_wchar[255];
	int len = MultiByteToWideChar(CP_ACP, 0, title.c_str(), 254, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, title.c_str(), 254, m_wchar, len);
	m_wchar[254] = '\0';
	
	hwnd = CreateWindow(szAppName, L"123", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		640, 480,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, 1);
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
			hwndInput,  //����������Ŀؼ����
			WM_SETFONT,  //��Ϣ������Ϣ���ͣ�
			(WPARAM)hFont,  //������
			NULL  //����ֵ����
		);
		return 0;

	case WM_SIZE:
		GetClientRect(hwnd, &rect);
		MoveWindow(hwndInput, 0, 0, rect.right, rect.bottom, TRUE);
		return 0;

	case WM_DESTROY:
		GetWindowTextA(hwndInput, text_buffer, 809600);
		DeleteObject(hFont);//ɾ������������
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
#include "webview2.h"

wil::com_ptr<ICoreWebView2Controller> webView2Creater::webviewController;
wil::com_ptr<ICoreWebView2> webView2Creater::webview;

#include "webbowser.h"

namespace {
	wchar_t* custom_CharToWchar(const char* str)
	{
		if (str == 0)
		{
			return 0;
		}
		wchar_t* m_wchar;
		int len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
		m_wchar = new wchar_t[len + 1];
		MultiByteToWideChar(CP_ACP, 0, str, -1, m_wchar, len);
		m_wchar[len] = '\0';
		return m_wchar;
	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_SIZE:
			if (webView2Creater::webviewController != nullptr) {
				RECT bounds;
				GetClientRect(hWnd, &bounds);
				webView2Creater::webviewController->put_Bounds(bounds);
			};
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}

		return 0;
	}
}

bool webView2Creater::create_view_with_url(std::string title, std::string _url)
{
	WCHAR* title_L = custom_CharToWchar(title.c_str());
	WCHAR* html_L = custom_CharToWchar(_url.c_str());
	HINSTANCE hInstance = GetModuleHandle(0);
	WCHAR szWindowClass[] = { L"ScriptC.view" };
	int nCmdShow = SW_SHOW;

	WNDCLASS wcex;

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClass(&wcex))
	{
		return false;
	}

	HWND hWnd = CreateWindow(
		szWindowClass,
		title_L,
		CXWebBrowser::window_style,
		CXWebBrowser::window_rect.left,
		CXWebBrowser::window_rect.top,
		CXWebBrowser::window_rect.right,
		CXWebBrowser::window_rect.bottom,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		return false;
	}

	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);


	CreateCoreWebView2EnvironmentWithOptions(nullptr, L".\\data\\", nullptr,
		Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
			[hWnd, &html_L](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
				env->CreateCoreWebView2Controller(hWnd, Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
					[hWnd, &html_L](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
						if (controller != nullptr) {
							webviewController = controller;
							webviewController->get_CoreWebView2(&webview);
						}
						wil::com_ptr<ICoreWebView2Settings> settings;
						webview->get_Settings(&settings);
						settings->put_IsScriptEnabled(TRUE);
						settings->put_AreDefaultScriptDialogsEnabled(TRUE);
						settings->put_IsWebMessageEnabled(TRUE);
						settings->put_IsStatusBarEnabled(FALSE);    // 控制是否显示状态栏
						settings->put_AreHostObjectsAllowed(TRUE); // 是否可以使用主机对象
						settings->put_AreDevToolsEnabled(FALSE);	// 是否启用 DevTools
						

						RECT bounds;
						GetClientRect(hWnd, &bounds);
						webviewController->put_Bounds(bounds);

						// window.close callfunc
						webview->add_WindowCloseRequested(
							Callback<ICoreWebView2WindowCloseRequestedEventHandler>(
								[hWnd](ICoreWebView2* sender, IUnknown* args)
								{
									PostMessage(hWnd, WM_CLOSE, 0, 0);
									return S_OK;
								})
							.Get(),
									nullptr);

						webview->Navigate(html_L);

						return S_OK;

					}).Get());
				return S_OK;
			}).Get());

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnregisterClass(szWindowClass, hInstance);

	return true;
}


bool webView2Creater::create_view_with_html(std::string title, std::string _url)
{
	WCHAR* title_L = custom_CharToWchar(title.c_str());
	WCHAR* html_L = custom_CharToWchar(_url.c_str());
	HINSTANCE hInstance = GetModuleHandle(0);
	WCHAR szWindowClass[] = { L"ScriptC.view" };
	int nCmdShow = SW_SHOW;

	WNDCLASS wcex;

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClass(&wcex))
	{
		return false;
	}

	HWND hWnd = CreateWindow(
		szWindowClass,
		title_L,
		CXWebBrowser::window_style,
		CXWebBrowser::window_rect.left,
		CXWebBrowser::window_rect.top,
		CXWebBrowser::window_rect.right,
		CXWebBrowser::window_rect.bottom,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		return false;
	}

	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	CreateCoreWebView2EnvironmentWithOptions(nullptr, L".\\data\\", nullptr,
		Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
			[hWnd,&html_L](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
				env->CreateCoreWebView2Controller(hWnd, Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
					[hWnd, &html_L](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
						if (controller != nullptr) {
							webviewController = controller;
							webviewController->get_CoreWebView2(&webview);
						}
						wil::com_ptr<ICoreWebView2Settings> settings;
						webview->get_Settings(&settings);
						settings->put_IsScriptEnabled(TRUE);
						settings->put_AreDefaultScriptDialogsEnabled(TRUE);
						settings->put_IsWebMessageEnabled(TRUE);
						settings->put_IsStatusBarEnabled(FALSE);    // 控制是否显示状态栏
						settings->put_AreHostObjectsAllowed(TRUE); // 是否可以使用主机对象
						settings->put_AreDevToolsEnabled(FALSE);	// 是否启用 DevTools

						RECT bounds;
						GetClientRect(hWnd, &bounds);
						webviewController->put_Bounds(bounds);

						// window.close callfunc
						webview->add_WindowCloseRequested(
							Callback<ICoreWebView2WindowCloseRequestedEventHandler>(
								[hWnd](ICoreWebView2* sender, IUnknown* args)
								{
									PostMessage(hWnd, WM_CLOSE, 0, 0);
									return S_OK;
								})
							.Get(),
							nullptr);

						webview->NavigateToString(html_L);

						return S_OK;
					}).Get());
				return S_OK;
			}).Get());

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnregisterClass(szWindowClass, hInstance);

	return true;
}
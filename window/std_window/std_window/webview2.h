#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>

#include <wrl.h>
#include <wil/com.h>
#include <WebView2.h>


using namespace Microsoft::WRL;


class webView2Creater {
public:
	static wil::com_ptr<ICoreWebView2Controller> webviewController;
	static wil::com_ptr<ICoreWebView2> webview;

public:
	static bool create_view_with_url(std::string title, std::string _url);
	static bool create_view_with_html(std::string title, std::string _url);
};
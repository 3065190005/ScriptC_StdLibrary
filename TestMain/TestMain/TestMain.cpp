#include "DllFuncReader.h"
#include "QuickLib/quicklib.h"

#include <direct.h>

using namespace Cervice::Obj;

#define IoS "io__"
#define OsS "os__"
#define MathS "math__"
#define StrS "str__"
#define VecS "vec__"
#define TimS "time__"
#define TypS "type__"
#define WindowS "fltk_window__"

#define func(var,va2)( "__system__" va2 var "__")

template<typename... Args>
void s_call(std::string name, auto_c* ret, Args... Ts) {
    DllFuncReader* manager = DllFuncReader::getInstance();
    auto func = manager->getFuncFromDll(name.c_str());
    std::vector<auto_c> param;
    auto space = { (param.push_back(Ts),0)... };
    manager->callFunc(func, &param, ret);
}


int main(int args , char** argv)
{

    DllFuncReader* manager = DllFuncReader::getInstance();
    auto func = manager->getFuncFromDll("__system___setArgv__");
    manager->callFunc(func, (std::vector<auto_c>*)argv, (auto_c*)&args);

    auto_c param1, param2, param3,param4,param5,param6, param7, param8,param9,param10;
    auto_c ret1,ret2,ret3,ret4,ret5;

    param1 << (numberT)WS_OVERLAPPEDWINDOW;
    param2 << (numberT)15;
    param3 << (numberT)20;
    param4 << (numberT)640;
    param5 << (numberT)480;
    param6 << R"(<b>123</b>)";
    param7 << R"(<u>123</u>)";
    param8 << R"(
<div class="btn" onclick=search_func()> search</div>
<script>
    function search_func() {
        window.close();
    }
</script>
    )";

    s_call(func("htmlView", WindowS), &ret1, param6, param8);
    return 0;
}


/*
* 基础标准库
* std_io "io" 输入输出库                    √
* std_os "os" 系统库                     √
* std_math "math" 数学库                   √
* std_string "string" 字符串处理库        √
* std_array  "array"  数组处理库         √  
* std_time "time" 时间库               √                    
* std_type "type" 类型库               √
* 
* -- maybe
* 高级标准库
* std_window "window" 窗口库           √
* std_regex "regex" 正则库
* std_socket "socket" 网络库
* std_thread "thread" 线程库
* std_direct "direct" 目录库
*/


/*
* 
*/
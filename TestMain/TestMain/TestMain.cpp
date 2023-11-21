#include "DllFuncReader.h"
#include "QuickLib/quicklib.h"


using namespace AutoMem::Obj;
using namespace ScriptC::Obj;

#define IoS "io__"
#define OsS "os__"
#define MathS "math__"
#define StrS "str__"
#define ArrayS "array__"
#define TimS "time__"
#define TypS "type__"
#define WindowS "window__"
#define ThreadS "thread__"
#define SocketS "socket__"
#define DirectS "direct__"

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

    auto_c ret;
    ret << false;
    auto_c param1, param2, param3;

    LetTools tools;

    param1 << "%Desktop%";
    param2 << "msgbox";
    param3 << "title";
    s_call(func("hideConsole", WindowS), &ret, param1);
    s_call(func("showConsole", WindowS), &ret, param1);

    return 0;
}


/*
* 基础标准库
* std_io "io" 输入输出库                  √
* std_os "os" 系统库                      √
* std_math "math" 数学库                  √
* std_string "string" 字符串处理库         √
* std_array  "array"  数组处理库           √  
* std_time "time" 时间库                   √                    
* std_type "type" 类型库                   √
* 
* -- maybe
* 高级标准库
* std_window "window" 窗口库           √
* std_thread "thread" 线程库           √
* std_socket "socket" 网络库           √
* std_direct "direct" 目录库           √
* std_regex  "regex"  正则库
* std_random "random" 随机库
* 
* -- future
* 额外扩展库
* extend_win32com "win32com" Com库
* extend_json "json" Json库
* extend_nana "nana" GUI库
*/

// https://www.runoob.com/python/os-file-methods.html direct 目录库 的参考 将所有有关文件夹的操作函数全部写入

/*
* 
*/
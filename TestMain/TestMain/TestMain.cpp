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
    auto_c param1, param2, param3,param4;
    auto_c ret1,ret2,ret3,ret4,ret5;

    param1 << "abc defg";
    param2 << "123456";
    param3 << 10000;

    s_call(func("sleep", OsS), &ret1, param3);
    s_call(func("print", IoS), &ret2, ret1);

    return 0;
}


/*
* 基础标准库
* std_io "io" 输入输出库                    √
* std_os "os" 系统库                     √
* std_math "math" 数学库                   √
* std_string "string" 字符串处理库        √
* std_array  "array"  数组处理库         √  
* std_time "time" 时间库                    
* std_typeof "typeof" 类型库
* 
* -- maybe
* 高级标准库
* std_window "window" 窗口库
* std_regex "regex" 正则库
* std_socket "socket" 网络库
* std_thread "thread" 线程库
* std_direct "direct" 目录库
*/


/*
* 
*/
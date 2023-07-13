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
#define ThreadS "thread__"

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

    auto_c lua_file, name1, param1,name2,param2,name3, param3;
    auto_c thread_id,result,result_string,ret4,ret5;

    result_string << "result_string";

    name1 << "C_number";
    name2 << "C_string";
    name3 << "C_boolean";

    param1 << 111;
    param2 << "33aa";
    param3 << false;

    lua_file << "lua_file.lua";

    s_call(func("thread_create", ThreadS), &thread_id , lua_file);
    
    s_call(func("thread_set", ThreadS), &result, thread_id, name1, param1);
    s_call(func("thread_set", ThreadS), &result, thread_id, name2, param2);
    s_call(func("thread_set", ThreadS), &result, thread_id, name3, param3);


    s_call(func("thread_run", ThreadS), &result, thread_id);

    s_call(func("thread_stop", ThreadS), &result, thread_id);

    int i = 0;
    while (i < 1000)
    {
        std::cout << i++ << std::endl;
    }

    s_call(func("thread_resume", ThreadS), &result, thread_id);

    while (true)
    {
        s_call(func("thread_state", ThreadS), &result, thread_id);
        numberT state = LetObject::cast<numberT>(result);
        if (state == 5)
            break;
    }

    s_call(func("thread_get", ThreadS), &result, thread_id, result_string);


    s_call(func("thread_detach", ThreadS), &result, thread_id);
    s_call(func("thread_detach", ThreadS), &result, thread_id);
    s_call(func("thread_clear", ThreadS), &result, thread_id);
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
* std_thread "thread" 线程库           √
* std_direct "direct" 目录库
* std_regex "regex" 正则库
* std_socket "socket" 网络库
*/


/*
* 
*/
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
    auto_c param1, param2, param3;

    LetTools tools;

    param1 << "E:\\Virtual";
    s_call(func("chdir", DirectS), &ret, param1);
    s_call(func("getcwd", DirectS), &ret, param1);

    param1 << "E:\\Virtual";
    s_call(func("listdir", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << R"(note.txt)";
    param2 << 0400;
    s_call(func("chmod", DirectS), &ret, param1,param2);
    tools.print(ret);
    std::cout << std::endl;

    param1 << ".\\A\\B\\C";
    s_call(func("makedirs", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << ".\\A\\B\\C\\D\\";
    s_call(func("mkdir", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << ".\\E\\B";
    s_call(func("makedirs", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;


    param1 << ".\\A\\B\\C\\D\\";
    s_call(func("rmdir", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;


    param1 << ".\\A\\B\\C\\";
    s_call(func("removedirs", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;


    param1 << ".\\E\\B";
    param2 << ".\\F\\rename";
    s_call(func("rename", DirectS), &ret, param1, param2);
    tools.print(ret);
    std::cout << std::endl;


    param1 << ".\\DCDD.txt";
    s_call(func("stat", DirectS), &ret, param1);
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    for (auto& i : *ret.getStrArrayPtr())
    {
        std::cout << i.first << " : "; tools.print(i.second); std::cout << std::endl;
    }


    param1 << ".\\DCDD.txt";
    s_call(func("abspath", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << ".\\DCDD.txt";
    s_call(func("relative", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << ".\\DCDD.txt";
    s_call(func("basename", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    int index = 0;
    param1[0] << "Users/krunal/code/Desktop";
    param1[1] << "Users/krunal/krunal/Desktop/code";
    param1[2] << "Users/krunal/Desktop/datasets";
    param1[3] << "Users/krunal/AAA/Desktop/datasets";
    param1[4] << "Users/krunal/BBB/CCC/Desktop/SSSS";
    param1[6] << "Users/krunal/krunal/DDD/EEE/FFF/Desktop/SSSS";
    s_call(func("commonprefix", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << ".\\.\\A\\B\\C\\DCDD.txt";
    s_call(func("dirname", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << ".\\.\\E\\B\\";
    s_call(func("exists", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << "%userprofile%/desktop/";
    s_call(func("expand", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;


    param1 << "%userprofile%/desktop/";
    s_call(func("expand", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;


    param1 << "E:\\Virtual\\DCDD.txt";
    s_call(func("getatime", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << "E:\\Virtual\\DCDD.txt";
    s_call(func("getmtime", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << "E:\\Virtual\\DCDD.txt";
    s_call(func("getctime", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << "E:\\Virtual\\DCDD.txt";
    s_call(func("getsize", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << "E:\\Virtual\\DCDD.txt";
    s_call(func("isabs", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << "E:\\Virtual\\DCDD";
    s_call(func("isfile", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << "E:\\Virtual\\DCDD";
    s_call(func("isdir", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;


    param1 << "E:/Virtual\\DCDD//kkk";
    s_call(func("normcase", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << "a/./b/..";
    s_call(func("normpath", DirectS), &ret, param1);
    tools.print(ret);
    std::cout << std::endl;

    param1 << "E:\\Virtual\\F\\rename\\aaa.txt";
    s_call(func("info", DirectS), &ret, param1);
    for (auto& i : *ret.getStrArrayPtr())
    {
        std::cout << i.first << " : "; tools.print(i.second); std::cout << std::endl;
    }

    param1 << "a/./FE/..";
    param2 << "a/./..";
    s_call(func("samefile", DirectS), &ret, param2, param1);
    tools.print(ret);
    std::cout << std::endl;

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
* std_direct "direct" 目录库
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
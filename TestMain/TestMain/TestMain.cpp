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
#define DialogS "dialog__"
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

void OsTest()
{
	//// abort	终止程序 : (void) -> (void)
	//EXPORTDLL(abort);

	auto_c ret;
	auto_c param1, param2;

	// s_call(func("abort", OsS), &ret, param1);

	//// exit		退出程序	: 退出码 -> (void)
	//EXPORTDLL(exit);

	//param1 << 123;
	////param1 << "123";
	//s_call(func("exit", OsS), &ret, param1);

	//// str		转换字符串 : 参数 -> 成功返回字符串，失败返回null
	//EXPORTDLL(str);
	//param1 << 123456;
	//param1[0] << "can not convert";
	//s_call(func("str", OsS), &ret, param1);

	//// number	转换数字 : 参数 -> 成功返回数字，失败返回null
	//EXPORTDLL(number);
	//param1 << "123.456";
	//s_call(func("number", OsS), &ret, param1);

	//// bool		转换布尔 : 参数 -> 成功返回布尔值，失败返回null
	////EXPORTDLL(bool);
	//param1 << "123";
	//s_call(func("bool", OsS), &ret, param1);

	////// type		返回参数类型 : 参数 -> 返回指定变量类型
	////EXPORTDLL(type);
	//param1[456] << "array";
	//s_call(func("type", OsS), &ret, param1);

	//// hex      获取16进制 : 参数 -> 成功返回number，失败返回null
	//EXPORTDLL(hex);
	//param1 << "0x77";
	//param1 << 0x77;	// error throw
	//param1 << "077"; // error throw
	//s_call(func("hex", OsS), &ret, param1);

	//// oct		获取8进制  : 参数 -> 成功返回number, 失败返回null
	//EXPORTDLL(oct);
	//param1 << "0o236";
	////param1 << "0236"; // error throw
	////param1 << 123; // error throw
	//s_call(func("oct", OsS), &ret, param1);

	//// bit		获取2进制  : 参数 -> 成功返回number, 失败返回null
	//EXPORTDLL(bin);
	//param1 << "0b11010";
	//param1 << "011010"; // error throw
	//param1 << 123456; // error throw
	//param1 << "0x11230"; // error throw
	//s_call(func("bin", OsS), &ret, param1);

	//// putenv   创建修改删除环境变量 : 名称 , 参数 -> 成功返回true 失败返回false
	//EXPORTDLL(putenv);
	//param1 << "OsSTestPath";
	//param2 << "Change OsTestPath";
	//// param1 << 123456; // error throw
	//// param2[0] << "Change Error"; // error throw
	//s_call(func("putenv", OsS), &ret, param1, param2);

	////// getenv	获取环境 : 环境名字 -> 成功返回环境内容字符串，失败返回null
	////EXPORTDLL(getenv);
	//param1 << "OsSTestPath";
	////param1 << 123; // error throw
	//s_call(func("getenv", OsS), &ret, param1);

	//// system	系统命令 : 命令 -> 执行成功返回true 失败返回false
	//EXPORTDLL(system);
	//param1 << "pause";
	////param1 << 123; // error throw
	//s_call(func("system", OsS), &ret, param1);

	//// sleep    睡眠命令 ：数字 -> 成功返回睡眠时间 , 失败返回null
	//EXPORTDLL(sleep);
	//param1 << 2000;
	//// param1 << "2000"; // throw error
	//s_call(func("sleep", OsS), &ret, param1);

	//// argv		获取启动参数 : (void) -> 返回数组
	//EXPORTDLL(argv);

	s_call(func("argv", OsS), &ret, param1);
}

bool initConsoleArgv(int args, char** argv)
{
	DllFuncReader* manager = DllFuncReader::getInstance();
	auto func = manager->getFuncFromDll("__system___setArgv__");
	manager->callFunc(func, (std::vector<auto_c>*)argv, (auto_c*)&args);

	return true;
}

int main(int args , char** argv)
{
	initConsoleArgv(args, argv);
	auto_c param1, param2, param3, param4, param5, param6, param7;
    

	OsTest();

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
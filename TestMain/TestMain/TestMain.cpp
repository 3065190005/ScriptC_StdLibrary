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

#define func(func,dll)( "__system__" dll func "__")

template<typename... Args>
void s_call(std::string name, auto_c* ret, Args... Ts) {
    DllFuncReader* manager = DllFuncReader::getInstance();
    auto func = manager->getFuncFromDll(name.c_str());
    std::vector<auto_c> param;
    auto space = { (param.push_back(Ts),0)... };
    manager->callFunc(func, &param, ret);
}

void MathTest()
{
	auto_c ret;
	auto_c param1, param2;

	//// abs		返回绝对值 : 数字 -> 成功返回数字的绝对值，否则返回null
	//EXPORTDLL(abs);

	param1 << -123;
	//s_call(func("abs", MathS), &ret, param1);

	//// div		积分除法	  : 分子，分母 -> 成功返回 数组(商，余数)，否则返回null
	//EXPORTDLL(div);
	param1 << -123;
	param2 << -456;
	param1 << "-123";
	//param2 << "-456";
	//s_call(func("div", MathS), &ret, param1, param2);

	//// acos		返回参数的反余弦弧度		: 参数 -> 成功返回数字，否则返回null
	//EXPORTDLL(acos);
	param1 << 135;
	param1 << "-123";
	//s_call(func("acos", MathS), &ret, param1);

	//// asin		返回参数的正弦弧线弧度	: 参数 -> 成功返回数字，否则返回null
	//EXPORTDLL(asin);
	param1 << 135;
	param1 << "-123";
	//s_call(func("asin", MathS), &ret, param1);

	//// atan		返回参数的反正切值，以弧度为单位 : 参数 -> 成功返回数字， 否则返回null
	//EXPORTDLL(atan);
	param1 << 135;
	param1 << "-123";
	//s_call(func("atan", MathS), &ret, param1);

	//// atan2	返回参数1 / 参数2的以弧度为单位的反正切值，根据这两个值，以确定正确的象限上的标志	: 参数1，参数2 -> 成功返回数字，否则返回null
	//EXPORTDLL(atan2);
	param1 << 135;
	param2 << 456;
	//param2 << "456";
	param1 << "-123";
	//s_call(func("atan2", MathS), &ret, param1, param2);

	//// cos		返回的弧度角参数的余弦值	: 参数 -> 成功返回数字， 否则返回null
	//EXPORTDLL(cos);
	param1 << 135;
	param1 << "-123";
	//s_call(func("cos", MathS), &ret, param1);

	//// cosh		返回参数1的双曲余弦 : 参数 -> 成功返回数字，否则返回null
	//EXPORTDLL(cosh);
	param1 << 135;
	param1 << "-123";
	//s_call(func("cosh", MathS), &ret, param1);

	//// sin		返回一个弧度角参数1的正弦 : 参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(sin);
	param1 << 135;
	param1 << "-123";
	//s_call(func("sin", MathS), &ret, param1);

	//// sinh		返回参数1的双曲正弦	: 参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(sinh);
	param1 << 135;
	param1 << "-123";
	//s_call(func("sinh", MathS), &ret, param1);

	//// tanh		返回参数1的双曲正切  :  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(tanh);
	param1 << 135;
	param1 << "-123";
	//s_call(func("tanh", MathS), &ret, param1);

	//// exp		返回e值的第参数1次幂  :  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(exp);
	param1 << 135;
	param1 << "-123";
	//s_call(func("exp", MathS), &ret, param1);

	//// log		返回自然对数的参数1（基准 - e对数） :  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(log);
	param1 << 135;
	param1 << "-123";
	//s_call(func("log", MathS), &ret, param1);

	//// log10	返回参数1的常用对数（以10为底）	:  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(log10);
	param1 << 135;
	param1 << "-123";
	//s_call(func("log10", MathS), &ret, param1);

	//// pow		返回参数1的参数2次方	:  参数1 , 参数2 -> 成功返回数字，否则返回null
	//EXPORTDLL(pow);
	param1 << 2;
	param2 << 4;
	//param2 << "-4";
	param1 << "2";
	//s_call(func("pow", MathS), &ret, param1, param2);

	//// sqrt		返回参数1的平方根	  :  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(sqrt);
	param1 << 6;
	param1 << "6";
	//s_call(func("sqrt", MathS), &ret, param1);

	//// ceil		返回大于或等于参数1的最小整数值  :  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(ceil);
	param1 << 6;
	param1 << "6";
	//s_call(func("ceil", MathS), &ret, param1);

	//// floor	返回的最大整数值小于或等于参数1  :  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(floor);
	param1 << 6;
	param1 << "6";
	//s_call(func("floor", MathS), &ret, param1);

	//// frexp	返回值是尾数指向的整数指数是指数。得到的值是 x =参数1 * 2 ^ exponent	： 参数1  ->  成功返回数组，否则返回null
	//EXPORTDLL(frexp);
	param1 << 6;
	param1 << "6";
	//s_call(func("frexp", MathS), &ret, param1);

	//// ldexp	返回参数1乘以参数2指数的幂	： 参数1 , 参数2 -> 成功返回数字，否则返回null
	//EXPORTDLL(ldexp);
	param1 << 6;
	param1 << "6";
	param2 << 10;
	//param2 << "10";
	//s_call(func("ldexp", MathS), &ret, param1, param2);

	//// modf		返回参数1的小数与整数部分	:  参数1 -> 成功返回数组，否则返回null
	//EXPORTDLL(modf);
	param1 << 123.456;
	param1 << "123.456";
	//s_call(func("modf", MathS), &ret, param1);
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
	//param1 << "123";
	//s_call(func("exit", OsS), &ret, param1);

	//// str		转换字符串 : 参数 -> 成功返回字符串，失败返回null
	//EXPORTDLL(str);
	//param1 << 123456;
	//param1[0] << "can not convert";
	//s_call(func("str", OsS), &ret, param1);

	//// number	转换数字 : 参数 -> 成功返回数字，失败返回null
	//EXPORTDLL(number);
	param1 << "123.456";
	//s_call(func("number", OsS), &ret, param1);

	//// bool		转换布尔 : 参数 -> 成功返回布尔值，失败返回null
	////EXPORTDLL(bool);
	param1 << "123";
	//s_call(func("bool", OsS), &ret, param1);

	////// type		返回参数类型 : 参数 -> 返回指定变量类型
	////EXPORTDLL(type);
	//param1[456] << "array";
	//s_call(func("type", OsS), &ret, param1);

	//// hex      获取16进制 : 参数 -> 成功返回number，失败返回null
	//EXPORTDLL(hex);
	param1 << "0x77";
	//param1 << 0x77;	// error throw
	param1 << "077"; // error throw
	//s_call(func("hex", OsS), &ret, param1);

	//// oct		获取8进制  : 参数 -> 成功返回number, 失败返回null
	//EXPORTDLL(oct);
	param1 << "0o236";
	//param1 << "0236"; // error throw
	////param1 << 123; // error throw
	//s_call(func("oct", OsS), &ret, param1);

	//// bit		获取2进制  : 参数 -> 成功返回number, 失败返回null
	//EXPORTDLL(bin);
	param1 << "0b11010";
	param1 << "011010"; // error throw
	//param1 << 123456; // error throw
	param1 << "0x11230"; // error throw
	//s_call(func("bin", OsS), &ret, param1);

	//// putenv   创建修改删除环境变量 : 名称 , 参数 -> 成功返回true 失败返回false
	//EXPORTDLL(putenv);
	param1 << "OsSTestPath";
	//param2 << "Change OsTestPath";
	//param1 << 123456; // error throw
	//param2[0] << "Change Error"; // error throw
	//s_call(func("putenv", OsS), &ret, param1, param2);

	////// getenv	获取环境 : 环境名字 -> 成功返回环境内容字符串，失败返回null
	////EXPORTDLL(getenv);
	param1 << "OsSTestPath";
	////param1 << 123; // error throw
	//s_call(func("getenv", OsS), &ret, param1);

	//// system	系统命令 : 命令 -> 执行成功返回true 失败返回false
	//EXPORTDLL(system);
	param1 << "pause";
	////param1 << 123; // error throw
	//s_call(func("system", OsS), &ret, param1);

	//// sleep    睡眠命令 ：数字 -> 成功返回睡眠时间 , 失败返回null
	//EXPORTDLL(sleep);
	//param1 << 2000;
	param1 << "2000"; // throw error
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
    
	param1[0] << "EHllo Number";
	param1["Hello"] << 789456;
	param1["list"]["child"] << "This is Child";
	param1["list"]["parent"] << "This is Parent";
	param1["list"]["class"] << "This is class";

	s_call(func("print", IoS), &param2, param1);

	// OsTest();
	MathTest();

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
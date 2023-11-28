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

void ArrayTest()
{
	auto_c ret;
	auto_c param1, param2, param3, param4;


	//// size		返回数组总个数		：数组 -> 成功返回个数，否则返回null
	//EXPORTDLL(size);
	param1[0] << "This is 0";
	param1[1] << "This is 1";
	param1 << 123.456;
	s_call(func("size", ArrayS), &ret, param1);

	//// cmp		比较两个数组			：数组1，数组2 -> 成功对比结果返回数字，否则返回null (相等返回0,1大返回数组-11，否则返回1)
	//EXPORTDLL(cmp);
	param1[0] << "This is 0 Cmp";
	param1[1] << "This is 1 Cmp";

	param2[0] << "This is 0 Cmp";
	param2[1] << "This is 1 Cmp";
	param1 << 123.456;
	s_call(func("cmp", ArrayS), &ret, param1, param2);

	//// max		返回列表最大值		：数组 -> 成功返回最大值，否则返回null
	//EXPORTDLL(max);
	param1[0] << "This is 0 Max";
	param1[1] << "This is 1 Max";
	param1 << 123.456;
	s_call(func("max", ArrayS), &ret, param1);

	//// min		返回列表最小元素		：数组 -> 成功返回最小值，否则返回null
	//EXPORTDLL(min);
	param1[0] << "This is 0 Min";
	param1[1] << "This is 1 Min";
	param1 << 123.456;
	s_call(func("min", ArrayS), &ret, param1);

	//// append	在末尾添加元素		：数组，任意 -> 成功返回添加后的数组，否则返回null
	//EXPORTDLL(append);
	param1[0] << "This is 0 Append";
	param1[1] << "This is 1 Append";
	param2 << "This is 3 Append";
	param1 << 123.456;
	s_call(func("append", ArrayS), &ret, param1, param2);

	//// count	检测某个元素的个数	：数组，任意 -> 成功返回个数，否则返回null
	//EXPORTDLL(count);
	param1[0] << "This is 0 Count";
	param1[1] << "This is 1 Count";
	param1[2] << "Count Test";
	param1[3] << "Count Test";
	param2 << "Count Test";
	param1 << 123.456;
	s_call(func("count", ArrayS), &ret, param1, param2);

	//// extend	在末尾添加			：数组，任意 -> 成功返回添加后的新数组，否则返回null
	//EXPORTDLL(extend);
	param1[0] << "This is 0 Extend";
	param1[1] << "This is 1 Extend";
	param2 << "This is 3 Extend";
	param1 << 123.456;
	s_call(func("extend", ArrayS), &ret, param1, param2);

	//// back		返回最后一个元素		：数组 -> 成功返回末尾元素，否则返回null
	//EXPORTDLL(back);
	param1[0] << "This is 0 Back";
	param1[1] << "This is 1 Back";
	param1[2] << "This is 2 Back";
	param1 << 123.456;
	s_call(func("back", ArrayS), &ret, param1);

	//// front	返回第一个元素		：数组 -> 成功返回开头元素，否则返回null
	//EXPORTDLL(front);
	param1[0] << "This is 0 Front";
	param1[1] << "This is 1 Front";
	param1 << 123.456;
	s_call(func("front", ArrayS), &ret, param1);

	//// index	查找指定元素第一次位置：数组，任意 -> 成功查找返回下标，否则返回null
	//EXPORTDLL(index);
	param1[0] << "This is 0 Index";
	param1[1] << "This is 1 Index";
	param1[2] << "Index Test";
	param1[3] << "Index Test";
	param1 << 123.456;
	s_call(func("index", ArrayS), &ret, param1, param2);

	//// insert	将指定内容插入指定位置：数组，下标，任意 -> 成功返回插入后的新数组，否则返回null
	//EXPORTDLL(insert);
	param1[0] << "This is 0 Insert";
	param1[1] << "This is 1 Insert";
	param2 << 1;
	param3 << "Insert Value";
	param1 << 123.456;
	s_call(func("insert", ArrayS), &ret, param1, param2, param3);

	//// pop		删除数组指定内容		：数组，下标	-> 成功返回删除后的新数组，否则返回null
	//EXPORTDLL(pop);
	param1[0] << "This is 0 Pop";
	param1[1] << "This is 1 Pop";
	param1["Pop"] << "This is Pop Value";
	param2 << "Pop";
	param1 << 123.456;
	s_call(func("pop", ArrayS), &ret, param1, param2);

	//// remove	移除数组指定的第一个值：数组，任意 -> 成功返回移除后的新数组，否则返回null
	//EXPORTDLL(remove);
	param1[0] << "This is 0 Remove";
	param1[1] << "This is 1 Remove";
	param2 << "This is 1 Remove";
	param1 << 123.456;
	s_call(func("remove", ArrayS), &ret, param1, param2);

	//// reverse	反序					：数组	-> 成功返回新数组，否则返回null
	//EXPORTDLL(reverse);
	param1[0] << "This is 0 Reverse";
	param1[1] << "This is 1 Reverse";
	param1[2] << "This is 2 Reverse";
	param1 << 123.456;
	s_call(func("reverse", ArrayS), &ret, param1);

	//// range	范围					：数字1，数组2 -> 成功返回基于数组1和数字2范围区间的数组，否则返回null
	//EXPORTDLL(range);
	param1 << 0;
	param2 << 10;
	param1 << "123";
	s_call(func("range", ArrayS), &ret, param1, param2);

	//// childs	返回数组所有下标		：数组 -> 成功将该数组的所有下标作为数组返回，失败返回null
	//EXPORTDLL(childs);
	param1[0] << "This is 0 Childs";
	param1[1] << "This is 1 Childs";
	param1["Child_1"] << "This is Child_1 Childs";
	param1["Child_2"] << "This is Child_2 Childs";
	param1 << 123.456;
	s_call(func("childs", ArrayS), &ret, param1);
}

void StringTest()
{
	auto_c ret;
	auto_c param1, param2, param3, param4;

	//split	拆分字符串 : 源字符串，分隔符 -> 拆分成功返回数组，否则返回null
	//EXPORTDLL(split);
	param1 << 123.456;
	//param1 << "This is Split Test Txt";
	param2 << " ";
	
	s_call(func("split", StrS), &ret, param1, param2);

	//cut      分割指定字符串 : 源字符串，分隔符 -> 拆分成功返回数组，否则返回null
	//EXPORTDLL(cut);
	param1 << 123.456;
	//param1 << "Thisis CutTestTxt";
	param2 << " ";
	s_call(func("cut", StrS), &ret, param1, param2);

	//sub      剪切指定字符串 : 目标字符串，开始位置，个数(-1剩余全部) -> 剪切成功返回字符串，否则返回null
	//EXPORTDLL(sub);
	param1 << 123.456;
	//param1 << "This is sub Test Txt";
	param2 << 5;
	param3 << 6;
	s_call(func("sub", StrS), &ret, param1, param2, param3);

	//replace  替换指定内容 : 字符串，源内容，替换内容，替换次数(-1全部) -> 替换成功返回替换后的字符串，否则返回null
	//EXPORTDLL(replace);
	param1 << 123.456;
	//param1 << "This is replace Test Txt";
	param2 << "is";
	param3 << "not is";
	param4 << 1;
	s_call(func("replace", StrS), &ret, param1, param2, param3, param4);

	//at		获取字符串下标 : 字符串，下标 -> 返回指定下标字符，失败返回null
	//EXPORTDLL(at);
	param1 << 123.456;
	//param1 << "This is at Test Txt";
	param2 << 8;
	s_call(func("at", StrS), &ret, param1, param2);

	//erase    删除指定字符串 : 字符串，下标，长度 -> 返回删除后的字符串，失败返回null
	//EXPORTDLL(erase);
	param1 << 123.456;
	//param1 << "This is erase Test Txt";
	param2 << 3;
	param3 << 5;
	s_call(func("erase", StrS), &ret, param1, param2, param3);

	//insert   在某个位置插入字符串 : 字符串，下标，内容 -> 返回插入后总字符串，失败返回null
	//EXPORTDLL(insert);
	param1 << 123.456;
	//param1 << "This is insert Test Txt";
	param2 << 4;
	param3 << " Insert ";
	s_call(func("insert", StrS), &ret, param1, param2, param3);

	//fill  字符串填充	： 字符串，位置，长度，内容 -> 返回填充后的总字符串，失败返回null
	//EXPORTDLL(fill);
	param1 << 123.456;
	//param1 << "This is fill Test Txt";
	param2 << 5;
	param3 << 10;
	param4 << "A";
	s_call(func("fill", StrS), &ret, param1, param2, param3, param4);

	//count   返回字符串出现的次数 : 字符串，目标 -> 返回目标出现次数，失败返回null
	//EXPORTDLL(count);
	param1 << 123.456;
	//param1 << "This is count Test Txt";
	param2 << "T";
	s_call(func("count", StrS), &ret, param1, param2);

	//find_all        正向查找全部下标		: 字符串，内容 -> 查找成功返回数组，失败返回null
	//EXPORTDLL(find_all);
	param1 << 123.456;
	//param1 << "This is count Test Txt";
	param2 << "T";
	s_call(func("find_all", StrS), &ret, param1, param2);

	//find_first      正向查找第一个下标		：字符串，内容 -> 查找成功返回数字，失败返回null
	//EXPORTDLL(find_first);
	param1 << 123.456;
	//param1 << "This is count Test Txt";
	param2 << "T";
	s_call(func("find_first", StrS), &ret, param1, param2);

	//find_N          正向查找N个下标		：字符串，内容，次数 -> 查找成功返回数组，失败返回null
	//EXPORTDLL(find_N);
	param1 << 123.456;
	//param1 << "This is count Test Txt";
	param2 << "T";
	param3 << 2;
	s_call(func("find_N", StrS), &ret, param1, param2, param3);

	//find_not_all    正向查找全部not下标	：字符串，内容 -> 查找成功返回二维数组，失败返回null
	//EXPORTDLL(find_not_all);
	param1 << 123.456;
	//param1 << "This is count Test Txt";
	param2 << "T";
	s_call(func("find_not_all", StrS), &ret, param1, param2);

	//find_not_first  正向查找第一个not下标	: 字符串，内容 -> 查找成功返回数组，失败返回null
	//EXPORTDLL(find_not_first);
	param1 << 123.456;
	//param1 << "This is count Test Txt";
	param2 << "T";
	s_call(func("find_not_first", StrS), &ret, param1, param2);

	//find_not_N      正向查找N个not下标		: 字符串，内容，次数 -> 查找成功返回二维数组，失败返回null
	//EXPORTDLL(find_not_N);
	param1 << 123.456;
	//param1 << "This is count Test Txt";
	param2 << "T";
	param3 << 2;
	s_call(func("find_not_N", StrS), &ret, param1, param2, param3);

	//rfind_frist		 反向查找第一个下标		:	字符串，内容 -> 成功返回数字，失败返回null
	//EXPORTDLL(rfind_first);
	param1 << 123.456;
	//param1 << "This is count Test Txt";
	param2 << "T";
	s_call(func("rfind_first", StrS), &ret, param1, param2);

	//rfind_N			 反向查找N个下标			:	字符串，内容，次数 -> 成功返回数组，失败返回null
	//EXPORTDLL(rfind_N);
	param1 << 123.456;
	//param1 << "This is count Test Txt";
	param2 << "T";
	param3 << 2;
	s_call(func("rfind_N", StrS), &ret, param1, param2, param3);

	//rfind_not_first	 反向查找第一个not下标	:	字符串，内容	-> 成功返回数组，失败返回null
	//EXPORTDLL(rfind_not_first);
	param1 << 123.456;
	//param1 << "This is count Test Txt";
	param2 << "T";
	s_call(func("rfind_not_first", StrS), &ret, param1, param2);

	//rfind_not_N		 反向查找N个not下标		:	字符串，内容，次数 -> 成功返回二维数组，失败返回null
	//EXPORTDLL(rfind_not_N);
	param1 << 123.456;
	//param1 << "This is count Test Txt";
	param2 << "T";
	param3 << 2;
	s_call(func("rfind_not_N", StrS), &ret, param1, param2, param3);

	////reverse  字符串反转	: 字符串 -> 返回翻转后的字符串，失败返回null
	////EXPORTDLL(reverse);
	//param1 << 123.456;
	////param1 << "This is reverse Test Txt";
	//s_call(func("reverse", StrS), &ret, param1);

	////lens		获取字符串总长度 : 字符串 -> 返回字符串长度,失败返回null
	////EXPORTDLL(lens);
	//param1 << 123.456;
	////param1 << "This is lens Test Txt";
	//s_call(func("lens", StrS), &ret, param1);

	////lower	将字符串转换为大写 : 字符串 -> 返回转换字符串，失败返回null
	////EXPORTDLL(lower);
	//param1 << 123.456;
	////param1 << "This is lower Test Txt";
	//s_call(func("lower", StrS), &ret, param1);

	////upper	将字符串转换为大写 : 字符串 -> 返回转换字符串，失败返回null
	////EXPORTDLL(upper);
	//param1 << 123.456;
	////param1 << "This is upper Test Txt";
	//s_call(func("upper", StrS), &ret, param1);

	////tirm     删除头尾空白符 : 字符串 -> 返回处理后的字符串，失败返回null
	////EXPORTDLL(tirm);
	//param1 << 123.456;
	////param1 << "  This is tirm Test Txt  ";
	//s_call(func("tirm", StrS), &ret, param1);

	////up      将首字母大写 : 字符串 -> 返回处理后的字符串，失败返回null
	////EXPORTDLL(up);
	//param1 << 123.456;
	////param1 << "this is up Test Txt";
	//s_call(func("up", StrS), &ret, param1);

	////low     将首字母小写 : 字符串 -> 返回处理后的字符串，失败返回null
	////EXPORTDLL(low);
	//param1 << 123.456;
	////param1 << "This is low Test Txt";
	//s_call(func("low", StrS), &ret, param1);


	////isAlpha    检测字符串是否纯字母		: 是则返回true，否则返回false
	////EXPORTDLL(isAlpha);
	//param1 << 123.456;
	////param1 << "This is count Test Txt";
	//s_call(func("isAlpha", StrS), &ret, param1);

	////isAlnum	  检测字符串是否纯数字		: 是则返回true，否则返回false
	////EXPORTDLL(isAlnum);
	//param1 << 123.456;
	////param1 << "This is count Test Txt";
	//s_call(func("isAlnum", StrS), &ret, param1);

	////hasBlank	  检测字符串是否含有空格		: 是则返回true，否则返回false
	////EXPORTDLL(hasBlank);
	//param1 << 123.456;
	////param1 << "This is count Test Txt";
	//s_call(func("hasBlank", StrS), &ret, param1);

	////isBlank	  检测字符串是否纯空格		: 是则返回true，否则返回false
	////EXPORTDLL(isBlank);
	//param1 << 123.456;
	////param1 << "This is count Test Txt";
	//s_call(func("isBlank", StrS), &ret, param1);

	////hasCntrl	  检测字符串是否含有控制符		: 是则返回true，否则返回false
	////EXPORTDLL(hasCntrl);
	//param1 << 123.456;
	////param1 << "This is count Test Txt";
	//s_call(func("hasCntrl", StrS), &ret, param1);

	////isCntrl	  检测字符串是否全控制符		：是则返回true，否则返回false
	////EXPORTDLL(isCntrl);
	//param1 << 123.456;
	////param1 << "This is count Test Txt";
	//s_call(func("isCntrl", StrS), &ret, param1);

	////isLower	  检测字符串是否全小写		: 是则返回true，否则返回false
	////EXPORTDLL(isLower);
	//param1 << 123.456;
	////param1 << "This is count Test Txt";
	//s_call(func("isLower", StrS), &ret, param1);

	////isUpper	  检测字符串是否全大写		：是则返回true，否则返回false
	////EXPORTDLL(isUpper);
	//param1 << 123.456;
	////param1 << "This is count Test Txt";
	//s_call(func("isUpper", StrS), &ret, param1);
}

void MathTest()
{
	auto_c ret;
	auto_c param1, param2;

	//// abs		返回绝对值 : 数字 -> 成功返回数字的绝对值，否则返回null
	//EXPORTDLL(abs);

	param1 << 123.456;
	//param1 << -123;
	//s_call(func("abs", MathS), &ret, param1);

	//// div		积分除法	  : 分子，分母 -> 成功返回 数组(商，余数)，否则返回null
	//EXPORTDLL(div);
	param1 << 123.456;
	//param1 << -123;
	param2 << -456;
	param1 << 123.456;
	//param1 << "-123";
	//param2 << "-456";
	//s_call(func("div", MathS), &ret, param1, param2);

	//// acos		返回参数的反余弦弧度		: 参数 -> 成功返回数字，否则返回null
	//EXPORTDLL(acos);
	param1 << 123.456;
	//param1 << 135;
	param1 << 123.456;
	//param1 << "-123";
	//s_call(func("acos", MathS), &ret, param1);

	//// asin		返回参数的正弦弧线弧度	: 参数 -> 成功返回数字，否则返回null
	//EXPORTDLL(asin);
	param1 << 123.456;
	//param1 << 135;
	param1 << 123.456;
	//param1 << "-123";
	//s_call(func("asin", MathS), &ret, param1);

	//// atan		返回参数的反正切值，以弧度为单位 : 参数 -> 成功返回数字， 否则返回null
	//EXPORTDLL(atan);
	param1 << 123.456;
	//param1 << 135;
	param1 << 123.456;
	//param1 << "-123";
	//s_call(func("atan", MathS), &ret, param1);

	//// atan2	返回参数1 / 参数2的以弧度为单位的反正切值，根据这两个值，以确定正确的象限上的标志	: 参数1，参数2 -> 成功返回数字，否则返回null
	//EXPORTDLL(atan2);
	param1 << 123.456;
	//param1 << 135;
	param2 << 456;
	//param2 << "456";
	param1 << 123.456;
	//param1 << "-123";
	//s_call(func("atan2", MathS), &ret, param1, param2);

	//// cos		返回的弧度角参数的余弦值	: 参数 -> 成功返回数字， 否则返回null
	//EXPORTDLL(cos);
	param1 << 123.456;
	//param1 << 135;
	param1 << 123.456;
	//param1 << "-123";
	//s_call(func("cos", MathS), &ret, param1);

	//// cosh		返回参数1的双曲余弦 : 参数 -> 成功返回数字，否则返回null
	//EXPORTDLL(cosh);
	param1 << 123.456;
	//param1 << 135;
	param1 << 123.456;
	//param1 << "-123";
	//s_call(func("cosh", MathS), &ret, param1);

	//// sin		返回一个弧度角参数1的正弦 : 参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(sin);
	param1 << 123.456;
	//param1 << 135;
	param1 << 123.456;
	//param1 << "-123";
	//s_call(func("sin", MathS), &ret, param1);

	//// sinh		返回参数1的双曲正弦	: 参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(sinh);
	param1 << 123.456;
	//param1 << 135;
	param1 << 123.456;
	//param1 << "-123";
	//s_call(func("sinh", MathS), &ret, param1);

	//// tanh		返回参数1的双曲正切  :  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(tanh);
	param1 << 123.456;
	//param1 << 135;
	param1 << 123.456;
	//param1 << "-123";
	//s_call(func("tanh", MathS), &ret, param1);

	//// exp		返回e值的第参数1次幂  :  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(exp);
	param1 << 123.456;
	//param1 << 135;
	param1 << 123.456;
	//param1 << "-123";
	//s_call(func("exp", MathS), &ret, param1);

	//// log		返回自然对数的参数1（基准 - e对数） :  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(log);
	param1 << 123.456;
	//param1 << 135;
	param1 << 123.456;
	//param1 << "-123";
	//s_call(func("log", MathS), &ret, param1);

	//// log10	返回参数1的常用对数（以10为底）	:  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(log10);
	param1 << 123.456;
	//param1 << 135;
	param1 << 123.456;
	//param1 << "-123";
	//s_call(func("log10", MathS), &ret, param1);

	//// pow		返回参数1的参数2次方	:  参数1 , 参数2 -> 成功返回数字，否则返回null
	//EXPORTDLL(pow);
	param1 << 123.456;
	//param1 << 2;
	param2 << 4;
	//param2 << "-4";
	param1 << 123.456;
	//param1 << "2";
	//s_call(func("pow", MathS), &ret, param1, param2);

	//// sqrt		返回参数1的平方根	  :  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(sqrt);
	param1 << 123.456;
	//param1 << 6;
	param1 << 123.456;
	//param1 << "6";
	//s_call(func("sqrt", MathS), &ret, param1);

	//// ceil		返回大于或等于参数1的最小整数值  :  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(ceil);
	param1 << 123.456;
	//param1 << 6;
	param1 << 123.456;
	//param1 << "6";
	//s_call(func("ceil", MathS), &ret, param1);

	//// floor	返回的最大整数值小于或等于参数1  :  参数1  -> 成功返回数字，否则返回null
	//EXPORTDLL(floor);
	param1 << 123.456;
	//param1 << 6;
	param1 << 123.456;
	//param1 << "6";
	//s_call(func("floor", MathS), &ret, param1);

	//// frexp	返回值是尾数指向的整数指数是指数。得到的值是 x =参数1 * 2 ^ exponent	： 参数1  ->  成功返回数组，否则返回null
	//EXPORTDLL(frexp);
	param1 << 123.456;
	//param1 << 6;
	param1 << 123.456;
	//param1 << "6";
	//s_call(func("frexp", MathS), &ret, param1);

	//// ldexp	返回参数1乘以参数2指数的幂	： 参数1 , 参数2 -> 成功返回数字，否则返回null
	//EXPORTDLL(ldexp);
	param1 << 123.456;
	//param1 << 6;
	param1 << 123.456;
	//param1 << "6";
	param2 << 10;
	//param2 << "10";
	//s_call(func("ldexp", MathS), &ret, param1, param2);

	//// modf		返回参数1的小数与整数部分	:  参数1 -> 成功返回数组，否则返回null
	//EXPORTDLL(modf);
	param1 << 123.456;
	//param1 << 123.456;
	param1 << 123.456;
	//param1 << "123.456";
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

	//param1 << 123.456;
	//param1 << 123;
	//param1 << 123.456;
	//param1 << "123";
	//s_call(func("exit", OsS), &ret, param1);

	//// str		转换字符串 : 参数 -> 成功返回字符串，失败返回null
	//EXPORTDLL(str);
	//param1 << 123.456;
	//param1 << 123456;
	//param1[0] << "can not convert";
	//s_call(func("str", OsS), &ret, param1);

	//// number	转换数字 : 参数 -> 成功返回数字，失败返回null
	//EXPORTDLL(number);
	param1 << 123.456;
	//param1 << "123.456";
	//s_call(func("number", OsS), &ret, param1);

	//// bool		转换布尔 : 参数 -> 成功返回布尔值，失败返回null
	////EXPORTDLL(bool);
	param1 << 123.456;
	//param1 << "123";
	//s_call(func("bool", OsS), &ret, param1);

	////// type		返回参数类型 : 参数 -> 返回指定变量类型
	////EXPORTDLL(type);
	//param1[456] << "array";
	//s_call(func("type", OsS), &ret, param1);

	//// hex      获取16进制 : 参数 -> 成功返回number，失败返回null
	//EXPORTDLL(hex);
	param1 << 123.456;
	//param1 << "0x77";
	//param1 << 123.456;
	//param1 << 0x77;	// error throw
	param1 << 123.456;
	//param1 << "077"; // error throw
	//s_call(func("hex", OsS), &ret, param1);

	//// oct		获取8进制  : 参数 -> 成功返回number, 失败返回null
	//EXPORTDLL(oct);
	param1 << 123.456;
	//param1 << "0o236";
	//param1 << 123.456;
	//param1 << "0236"; // error throw
	////param1 << 123.456;
	//param1 << 123; // error throw
	//s_call(func("oct", OsS), &ret, param1);

	//// bit		获取2进制  : 参数 -> 成功返回number, 失败返回null
	//EXPORTDLL(bin);
	param1 << 123.456;
	//param1 << "0b11010";
	param1 << 123.456;
	//param1 << "011010"; // error throw
	//param1 << 123.456;
	//param1 << 123456; // error throw
	param1 << 123.456;
	//param1 << "0x11230"; // error throw
	//s_call(func("bin", OsS), &ret, param1);

	//// putenv   创建修改删除环境变量 : 名称 , 参数 -> 成功返回true 失败返回false
	//EXPORTDLL(putenv);
	param1 << 123.456;
	//param1 << "OsSTestPath";
	//param2 << "Change OsTestPath";
	//param1 << 123.456;
	//param1 << 123456; // error throw
	//param2[0] << "Change Error"; // error throw
	//s_call(func("putenv", OsS), &ret, param1, param2);

	////// getenv	获取环境 : 环境名字 -> 成功返回环境内容字符串，失败返回null
	////EXPORTDLL(getenv);
	param1 << 123.456;
	//param1 << "OsSTestPath";
	////param1 << 123.456;
	//param1 << 123; // error throw
	//s_call(func("getenv", OsS), &ret, param1);

	//// system	系统命令 : 命令 -> 执行成功返回true 失败返回false
	//EXPORTDLL(system);
	param1 << 123.456;
	//param1 << "pause";
	////param1 << 123.456;
	//param1 << 123; // error throw
	//s_call(func("system", OsS), &ret, param1);

	//// sleep    睡眠命令 ：数字 -> 成功返回睡眠时间 , 失败返回null
	//EXPORTDLL(sleep);
	//param1 << 123.456;
	//param1 << 2000;
	param1 << 123.456;
	//param1 << "2000"; // throw error
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
	auto_c rets, param1, param2, param3, param4, param5, param6, param7;
    
	param1[0] << "EHllo Number";
	param1["Hello"] << 789456;
	param1["list"]["child"] << "This is Child";
	param1["list"]["parent"] << "This is Parent";
	param1["list"]["class"] << "This is class";

	s_call(func("print", IoS), &rets, param2);

	// OsTest();
	// MathTest();
	// StringTest();
	ArrayTest();

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
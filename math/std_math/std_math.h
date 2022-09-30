#pragma once
#ifndef __CERVER_STD_STD_MATH__
#define __CERVER_STD_STD_MATH__

#define Fname(var) void __system__math__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

/*
* 参考 math.h 头文件内容
* https://blog.csdn.net/qq_42848319/article/details/121055852
*/

namespace Cervice {
	namespace Obj {
		// abs		返回绝对值 : 数字 -> 成功返回数字的绝对值，否则返回null
		EXPORTDLL(abs);

		// div		积分除法	  : 分子，分母 -> 成功返回 数组(商，余数)，否则返回null
		EXPORTDLL(div);

		// acos		返回参数的反余弦弧度		: 参数 -> 成功返回数字，否则返回null
		EXPORTDLL(acos);

		// asin		返回参数的正弦弧线弧度	: 参数 -> 成功返回数字，否则返回null
		EXPORTDLL(asin);
		
		// atan		返回参数的反正切值，以弧度为单位 : 参数 -> 成功返回数字， 否则返回null
		EXPORTDLL(atan);

		// atan2	返回参数1 / 参数2的以弧度为单位的反正切值，根据这两个值，以确定正确的象限上的标志	: 参数1，参数2 -> 成功返回数字，否则返回null
		EXPORTDLL(atan2);

		// cos		返回的弧度角参数的余弦值	: 参数 -> 成功返回数字， 否则返回null
		EXPORTDLL(cos);

		// cosh		返回参数1的双曲余弦 : 参数 -> 成功返回数字，否则返回null
		EXPORTDLL(cosh);

		// sin		返回一个弧度角参数1的正弦 : 参数1  -> 成功返回数字，否则返回null
		EXPORTDLL(sin);

		// sinh		返回参数1的双曲正弦	: 参数1  -> 成功返回数字，否则返回null
		EXPORTDLL(sinh);

		// tanh		返回参数1的双曲正切  :  参数1  -> 成功返回数字，否则返回null
		EXPORTDLL(tanh);

		// exp		返回e值的第参数1次幂  :  参数1  -> 成功返回数字，否则返回null
		EXPORTDLL(exp);

		// log		返回自然对数的参数1（基准 - e对数） :  参数1  -> 成功返回数字，否则返回null
		EXPORTDLL(log);

		// log10	返回参数1的常用对数（以10为底）	:  参数1  -> 成功返回数字，否则返回null
		EXPORTDLL(log10);

		// pow		返回参数1的参数2次方	:  参数1 , 参数2 -> 成功返回数字，否则返回null
		EXPORTDLL(pow);

		// sqrt		返回参数1的平方根	  :  参数1  -> 成功返回数字，否则返回null
		EXPORTDLL(sqrt);

		// ceil		返回大于或等于参数1的最小整数值  :  参数1  -> 成功返回数字，否则返回null
		EXPORTDLL(ceil);

		// floor	返回的最大整数值小于或等于参数1  :  参数1  -> 成功返回数字，否则返回null
		EXPORTDLL(floor);

		// frexp	返回值是尾数指向的整数指数是指数。得到的值是 x =参数1 * 2 ^ exponent	： 参数1  ->  成功返回数组，否则返回null
		EXPORTDLL(frexp);

		// ldexp	返回参数1乘以参数2指数的幂	： 参数1 , 参数2 -> 成功返回数字，否则返回null
		EXPORTDLL(ldexp);

		// modf		返回参数1的小数与整数部分	:  参数1 -> 成功返回数组，否则返回null
		EXPORTDLL(modf);
	}
}


#endif
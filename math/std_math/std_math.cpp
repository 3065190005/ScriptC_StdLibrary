#include "std_math.h"
#include "QuickLib/quicklib.h"

#define Fname(var) void __system__math__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllexport) Fname(var)
#define RESULT(var) auto_c*var = (auto_c*)ret; *var = auto_c(false,false)
#define PARAMS(var) std::vector<auto_c>* var = (std::vector<auto_c>*)param
#define PTR(var) (*var)

namespace {
	class Funcs {
	public:
		template<typename T>
		static T getParam(std::vector<T>* param);
	};


	template<typename T>
	inline T Funcs::getParam(std::vector<T>* param)
	{
		T ret;
		ret = param->back();
		param->pop_back();
		return ret;
	}
}

namespace Cervice {
	namespace Obj {

		EXPORTDLL(abs) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::fabsl(va1);

			return;
		}

		EXPORTDLL(div) {
			PARAMS(params);
			RESULT(rets);

			auto value2 = Funcs::getParam<LetObject>(params);
			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::number)
			{
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			numberT va2 = LetObject::cast<numberT>(value2);
			auto divt = ::ldiv(static_cast<long>(va1), static_cast<long>(va2));

			PTR(rets)[0] << static_cast<numberT>(divt.rem);
			PTR(rets)[1] << static_cast<numberT>(divt.quot);

			return;
		}


		EXPORTDLL(acos) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::acosl(va1);

			return;
		}


		EXPORTDLL(asin) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::asinl(va1);

			return;
		}


		EXPORTDLL(atan) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::atanl(va1);

			return;
		}


		EXPORTDLL(atan2) {
			PARAMS(params);
			RESULT(rets);

			auto value2 = Funcs::getParam<LetObject>(params);
			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number|| 
				value2.getType() != LetObject::ObjT::number) 
			{
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			numberT va2 = LetObject::cast<numberT>(value2);
			PTR(rets) << ::atan2l(va1, va2);

			return;
		}


		EXPORTDLL(cos) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::cosl(va1);

			return;
		}


		EXPORTDLL(cosh) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::coshl(va1);

			return;
		}


		EXPORTDLL(sin) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::sinl(va1);

			return;
		}


		EXPORTDLL(sinh) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::sinhl(va1);

			return;
		}


		EXPORTDLL(tanh) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::tanhl(va1);

			return;
		}


		EXPORTDLL(exp) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::expl(va1);

			return;
		}


		EXPORTDLL(log) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::logl(va1);

			return;
		}


		EXPORTDLL(log10) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::log10l(va1);

			return;
		}


		EXPORTDLL(pow) {
			PARAMS(params);
			RESULT(rets);

			auto value2 = Funcs::getParam<LetObject>(params);
			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number|| 
				value2.getType() != LetObject::ObjT::number)
			{
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			numberT va2 = LetObject::cast<numberT>(value2);
			PTR(rets) << ::powl(va1,va2);

			return;
		}


		EXPORTDLL(sqrt) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::sqrtl(va1);

			return;
		}


		EXPORTDLL(ceil) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::ceill(va1);

			return;
		}


		EXPORTDLL(floor) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			PTR(rets) << ::floorl(va1);

			return;
		}

		EXPORTDLL(frexp) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			int e;
			numberT ret1 = ::frexpl(va1,&e);

			PTR(rets)[0] << ret1;
			PTR(rets)[1] << e;

			return;
		}

		EXPORTDLL(ldexp) {
			PARAMS(params);
			RESULT(rets);

			auto value2 = Funcs::getParam<LetObject>(params);
			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::number)
			{
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			numberT va2 = LetObject::cast<numberT>(value2);
			PTR(rets) << ::ldexpl(va1, static_cast<int>(va2));

			return;
		}

		EXPORTDLL(modf) {
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			numberT ret2 = 0;
			numberT ret1 = modfl(va1,&ret2);

			PTR(rets)[0] << ret1;
			PTR(rets)[1] << ret2;

			return;
		}
	}
}
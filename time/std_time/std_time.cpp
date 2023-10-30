#include "std_time.h"
#include "QuickLib/quicklib.h"

#define Fname(var) void __system__time__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllexport) Fname(var)
#define RESULT(var) auto_c*var = (auto_c*)ret; *var = auto_c()
#define PARAMS(var) std::vector<auto_c>* var = (std::vector<auto_c>*)param
#define PTR(var) (*var)

#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

namespace {
	class Funcs {
	public:
		template<typename T>
		static T getParam(std::vector<T>* param);

		template<typename T, typename ... Args>
		static void getParams(std::vector<T>* params, T* pam, Args ...pams);
	};


	template<typename T>
	T Funcs::getParam(std::vector<T>* param)
	{
		T ret;
		ret = param->back();
		param->pop_back();
		return ret;
	}

	template<typename T, typename ... Args>
	void Funcs::getParams(std::vector<T>* params, T* pam, Args ...pams)
	{
		auto call = [&](std::vector<T>* param) {
			T ret;
			ret = param->back();
			param->pop_back();
			return ret;
		};

		(*pam) = call(params);
		(((*pams) = call(params)), ...);
	}

	class __timeGc {
	public:
		enum class ScheDuleState {
			Start,
			Pause,
		};

		struct ScheDuleData
		{
			long long int joint{};	// 加入时间
			long long int count{};	// 技术时间
			ScheDuleState state{};	// 当前状态
			long long int pause{};	// 暂停时间
			long long int lastT{};	// 上次暂停时间
		};
		static __timeGc* getInstance() {
			static __Gc gc;
			if (!m_instance) {
				m_instance = new __timeGc;
			}

			return m_instance;
		};

		std::unordered_map<unsigned int, ScheDuleData> m_Schedule;

		std::string getTimeString(bool bIncludeMS) {
			auto tNow = std::chrono::system_clock::now();
			//auto tmNow = std::chrono::system_clock::to_time_t(tNow);
			auto tSeconds = std::chrono::duration_cast<std::chrono::seconds>(tNow.time_since_epoch());
			auto secNow = tSeconds.count();
			tm tmNow;
			localtime_s(&tmNow, &secNow);
			std::ostringstream oss;
			oss << std::put_time(&tmNow, "%Y-%m-%d %H:%M:%S");
			if (bIncludeMS) {
				auto tMilli = std::chrono::duration_cast<std::chrono::milliseconds>(tNow.time_since_epoch());
				auto ms = tMilli - tSeconds;
				oss << ":" << std::setfill('0') << std::setw(3) << ms.count();
			}

			return oss.str();
		}

	private:
		static __timeGc* m_instance;
	private:
		__timeGc() {};
		~__timeGc() {};
	private:
		class __Gc {
		public:
			~__Gc(){
				if (m_instance) { delete m_instance; }
			}
		};
	};

	__timeGc* __timeGc::m_instance = nullptr;
}


namespace ScriptC {
	namespace Obj {
		using namespace AutoMem::Obj;

		// time		获得时间戳（秒 : （void） -> 返回数字时间戳，否则返回null
		EXPORTDLL(time) {
			PARAMS(params);
			RESULT(rets);
			namespace stdT = std::chrono;

			stdT::system_clock::time_point time_now = stdT::system_clock::now();
			stdT::seconds times = stdT::duration_cast<stdT::seconds>(time_now.time_since_epoch());
			
			PTR(rets) << times.count();
			return;
		}

		// timeAsM	获得时间戳（毫秒 : （void） -> 返回数字时间戳，否则返回null
		EXPORTDLL(timeAsM) {
			PARAMS(params);
			RESULT(rets);
			namespace stdT = std::chrono;

			stdT::system_clock::time_point time_now = stdT::system_clock::now();
			stdT::milliseconds times = stdT::duration_cast<stdT::milliseconds>(time_now.time_since_epoch());

			PTR(rets) << times.count();
			return;
		}

		// clock	获得程序运行时间（秒 : （void） -> 返回数字时间，否则返回null
		EXPORTDLL(clock) {
			PARAMS(params);
			RESULT(rets);
			clock_t times = ::clock();

			PTR(rets) << (long long)(times / 1000);
		}

		// clockAsM	获得程序运行时间（毫秒 : （void） -> 返回数字时间，否则返回null
		EXPORTDLL(clockAsM) {
			PARAMS(params);
			RESULT(rets);
			clock_t times = ::clock();

			PTR(rets) << (long long)times;
		}

		// cast 将秒转换成某个时间 : 源数字，类型 (6年，5月，4日，3时，2分，1秒 0毫秒 -> 转换成功返回数字，否则返回null
		EXPORTDLL(cast) {
			PARAMS(params);
			RESULT(rets);

			auto value2 = Funcs::getParam<LetObject>(params);
			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::number)
			{
				return;
			}

			numberT time_cast_type = 0;
			numberT time_sec = 0;
			
			value1 >> time_sec;
			value2 >> time_cast_type;

			if (time_cast_type < 1 && time_cast_type > 0) {
				return;
			}

			switch ((long)time_cast_type)
			{
			case 6: // 年
				time_sec = time_sec / 60 / 60 / 24 / 30 / 12;
				break;
			case 5: // 月
				time_sec = time_sec / 60 / 60 / 24 / 30;
				break;
			case 4: // 日
				time_sec = time_sec / 60 / 60 / 24;
				break;
			case 3: // 时
				time_sec = time_sec / 60 / 60;
				break;
			case 2: // 分
				time_sec = time_sec / 60;
				break;
			case 1: // 秒
				break;
			case 0: // 毫秒
				time_sec = time_sec * 1000;
				break;
			default:
				break;
			}
				

			PTR(rets) << time_sec;
			return;
		}

		// castAsM 将毫秒转换成某个时间 (6年，5月，4日，3时，2分，1秒 0毫秒 : 源数字，类型 -> 转换成功返回数字，否则返回null
		EXPORTDLL(castAsM) {
			PARAMS(params);
			RESULT(rets);

			auto value2 = Funcs::getParam<LetObject>(params);
			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::number)
			{
				return;
			}

			numberT time_cast_type = 0;
			numberT time_sec = 0;

			value1 >> time_sec;
			value2 >> time_cast_type;

			if (time_cast_type < 1 && time_cast_type > 0) {
				return;
			}

			switch ((long)time_cast_type)
			{
			case 6: // 年
				time_sec = time_sec / 1000 / 60 / 60 / 24 / 30 / 12;
				break;
			case 5: // 月
				time_sec = time_sec / 1000 / 60 / 60 / 24 / 30;
				break;
			case 4: // 日
				time_sec = time_sec / 1000 / 60 / 60 / 24;
				break;
			case 3: // 时
				time_sec = time_sec / 1000 / 60 / 60;
				break;
			case 2: // 分
				time_sec = time_sec / 1000 / 60;
				break;
			case 1: // 秒
				time_sec = time_sec / 1000;
				break;
			case 0: // 毫秒
				break;
			default:
				break;
			}


			PTR(rets) << time_sec;
			return;
		}

		// join 开始一个计时器 : (void) -> 设置成功返回数字计时器Id，否则返回null
		EXPORTDLL(join) {
			PARAMS(params);
			RESULT(rets);
			auto timeGc = __timeGc::getInstance();
			unsigned int id = 0;
			std::mt19937 rand;
			while (true) {
				id = rand();
				if (timeGc->m_Schedule.find(id) == timeGc->m_Schedule.end()) {
					__timeGc::ScheDuleData sche;
					auto epoch = std::chrono::steady_clock::now().time_since_epoch();
					sche.state = __timeGc::ScheDuleState::Start;
					sche.joint = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();
					timeGc->m_Schedule.insert({ id,sche });
					break;
				}
			}
	
			PTR(rets) << static_cast<numberT>(id);
		}

		// start 继续一个计时器 ： 数字计时器id -> 继续返回true,否则返回false
		EXPORTDLL(start) {
			PARAMS(params);
			RESULT(rets);
			auto timeGc = __timeGc::getInstance();

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				PTR(rets) << false;
				return;
			}

			numberT time_id = 0;
			value1 >> time_id;
			auto finder = timeGc->m_Schedule.find(time_id);
			if (finder == timeGc->m_Schedule.end()) {
				PTR(rets) << false;
				return;
			}

			auto Data = finder->second;

			if (Data.state == __timeGc::ScheDuleState::Start) {
				PTR(rets) << false;
				return;
			}

			std::chrono::steady_clock::time_point steady = std::chrono::steady_clock::now();
			long long int now_time_stamp = std::chrono::duration_cast<std::chrono::milliseconds>(steady.time_since_epoch()).count();

			Data.state = __timeGc::ScheDuleState::Start;
			Data.count = now_time_stamp - Data.joint;
			Data.pause += now_time_stamp - Data.lastT;

			finder->second = Data;

			PTR(rets) << true;
		}

		// pause 暂停一个计时器 ： 数字计时器id -> 暂停成功返回true,否则返回false
		EXPORTDLL(pause) {
			PARAMS(params);
			RESULT(rets);
			auto timeGc = __timeGc::getInstance();

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				PTR(rets) << false;
				return;
			}

			numberT time_id = 0;
			value1 >> time_id;
			auto finder = timeGc->m_Schedule.find(time_id);
			if (finder == timeGc->m_Schedule.end()) {
				PTR(rets) << false;
				return;
			}

			auto Data = finder->second;

			if (Data.state == __timeGc::ScheDuleState::Pause) {
				PTR(rets) << false;
				return;
			}

			std::chrono::steady_clock::time_point steady = std::chrono::steady_clock::now();
			long long int now_time_stamp = std::chrono::duration_cast<std::chrono::milliseconds>(steady.time_since_epoch()).count();

			Data.state = __timeGc::ScheDuleState::Pause;
			Data.count = now_time_stamp - Data.joint;
			Data.lastT = now_time_stamp;

			finder->second = Data;

			PTR(rets) << true;
		}

		// over 获取一个计时器 ： 数字计时器id -> 成功返回计数秒，否则返回null
		EXPORTDLL(over) {
			PARAMS(params);
			RESULT(rets);
			auto timeGc = __timeGc::getInstance();

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT time_id = 0;
			value1 >> time_id;
			auto finder = timeGc->m_Schedule.find(time_id);
			if (finder == timeGc->m_Schedule.end()) {
				return;
			}

			auto Data = finder->second;
			std::chrono::steady_clock::time_point steady = std::chrono::steady_clock::now();
			long long int now_time_stamp = std::chrono::duration_cast<std::chrono::milliseconds>(steady.time_since_epoch()).count();

			if (Data.state == __timeGc::ScheDuleState::Pause) {
				Data.pause += now_time_stamp - Data.lastT;
				Data.lastT = now_time_stamp;
			}
			else {
				Data.count = now_time_stamp - Data.joint;
			}

			finder->second = Data;

			long long int time_sec = Data.count - Data.pause;

			time_sec /= 1000;

			PTR(rets) << time_sec;
		}

		// overAsM 获取一个计时器 ： 数字计时器id -> 成功返回计数毫秒，否则返回null
		EXPORTDLL(overAsM) {
			PARAMS(params);
			RESULT(rets);
			auto timeGc = __timeGc::getInstance();

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				return;
			}

			numberT time_id = 0;
			value1 >> time_id;
			auto finder = timeGc->m_Schedule.find(time_id);
			if (finder == timeGc->m_Schedule.end()) {
				return;
			}

			auto Data = finder->second;
			std::chrono::steady_clock::time_point steady = std::chrono::steady_clock::now();
			long long int now_time_stamp = std::chrono::duration_cast<std::chrono::milliseconds>(steady.time_since_epoch()).count();

			if (Data.state == __timeGc::ScheDuleState::Pause) {
				Data.pause += now_time_stamp - Data.lastT;
				Data.lastT = now_time_stamp;
			}

			Data.count = now_time_stamp - Data.joint;

			finder->second = Data;

			long long int time_sec = Data.count - Data.pause;

			PTR(rets) << time_sec;
		}

		// date 获取系统日期 ： (void) -> 成功返回日期字符串，否则返回null
		EXPORTDLL(date) {
			PARAMS(params);
			RESULT(rets);
			auto timeGc = __timeGc::getInstance();
			std::string str = timeGc->getTimeString(false);

			PTR(rets) << str;
		}

		// dateAsM 获取系统日期 (毫秒 ： (void) -> 成功返回日期字符串，否则返回null
		EXPORTDLL(dateAsM) {
			PARAMS(params);
			RESULT(rets);
			auto timeGc = __timeGc::getInstance();
			std::string str = timeGc->getTimeString(true);

			PTR(rets) << str;
		}

		// toDate 将秒时间戳转换成日期 ： 数字秒时间戳 -> 成功返回日期字符串，否则返回null
		EXPORTDLL(toDate) {
			PARAMS(params);
			RESULT(rets);
			auto timeGc = __timeGc::getInstance();

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				PTR(rets) << false;
				return;
			}

			numberT time_sec = 0;
			value1 >> time_sec;
			if (time_sec < 0) { return; }

			char now[64];
			time_t tt;
			struct tm ttime;
			tt = static_cast<time_t>(time_sec);
			localtime_s(&ttime ,&tt);
			strftime(now, 64, "%Y-%m-%d %H:%M:%S", &ttime);
			PTR(rets) << now;
		}

		// toDateAsM 将毫秒时间戳转换成日期 ： 数字毫秒时间戳 -> 成功返回日期字符串，否则返回null
		EXPORTDLL(toDateAsM) {
			PARAMS(params);
			RESULT(rets);
			auto timeGc = __timeGc::getInstance();

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::number) {
				PTR(rets) << false;
				return;
			}

			numberT ms_num = 0;
			numberT time_sec = 0;
			value1 >> time_sec;

			if (time_sec < 0) { return; }

			ms_num = fmod(time_sec, 1000);
			time_sec /= 1000;

			char now[64];
			time_t tt;
			struct tm ttime;
			tt = static_cast<time_t>(time_sec);
			localtime_s(&ttime ,&tt);
			strftime(now, 64, "%Y-%m-%d %H:%M:%S", &ttime);
			std::string str;
			str = now;
			str += ":" + kstring::stringFrom<numberT>(ms_num);
			

			PTR(rets) << str;
		}
	}
}


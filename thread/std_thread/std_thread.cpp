#include "std_thread.h"
#include "QuickLib/quicklib.h"

#define Fname(var) void __system__thread__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllexport) Fname(var)
#define RESULT(var) auto_c*var = (auto_c*)ret; *var = auto_c(false,false)
#define PARAMS(var) std::vector<auto_c>* var = (std::vector<auto_c>*)param
#define PTR(var) (*var)

#include <algorithm>

#include "LuaThread/ThreadChild.h"
#include "LuaThread/ThreadPool.h"

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
}


namespace ScriptC {
	namespace Obj {
		using namespace AutoMem::Obj;

		// thread_create		 ����lua�߳�		���ɹ����ذ�ťid�����򷵻�null
		EXPORTDLL(thread_create)
		{
			PARAMS(params);
			RESULT(rets);

			auto value1 = Funcs::getParam<LetObject>(params);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			auto instance = ThreadPool::getInstance();
			auto child_id = instance->getNewChild();

			std::string path = LetObject::cast<std::string>(value1);
			auto child = instance->getChildById(child_id);
			bool success = child->open(path);

			if (success)
				PTR(rets) << child_id;
			else
				instance->removeChildById(child_id);

			return;
		}

		// thread_set			����ȫ�ֱ���		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_set)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2, value3;
			Funcs::getParams<LetObject>(params, &value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::string)
			{
				return;
			}


			numberT child_id = LetObject::cast<numberT>(value1);
			std::string param_name = LetObject::cast<std::string>(value2);
			auto instance = ThreadPool::getInstance();

			if (!instance->findChildById(child_id)) {
				return;
			}

			auto child = instance->getChildById(child_id);
			bool success = child->set(param_name, value3);

			if (success)
				PTR(rets) << true;

			return;

		}

		// thread_get			��ȡȫ�ֱ���		���ɹ����ر���ֵ�����򷵻�null
		EXPORTDLL(thread_get)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::string)
			{
				return;
			}


			numberT child_id = LetObject::cast<numberT>(value1);
			std::string param_name = LetObject::cast<std::string>(value2);
			auto instance = ThreadPool::getInstance();

			if (!instance->findChildById(child_id)) {
				return;
			}

			auto child = instance->getChildById(child_id);
			PTR(rets) = child->get(param_name);
			return;

		}

		// thread_run			�����߳�			���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_run)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::number)
			{
				return;
			}


			numberT child_id = LetObject::cast<numberT>(value1);
			auto instance = ThreadPool::getInstance();

			if (!instance->findChildById(child_id)) {
				return;
			}

			auto child = instance->getChildById(child_id);
			bool success = child->run();
			if (success)
				PTR(rets) << true;
			return;
		}

		// thread_state			��ȡ�߳�״̬		���ɹ�����״̬�����򷵻�null
		EXPORTDLL(thread_state)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::number)
			{
				return;
			}


			numberT child_id = LetObject::cast<numberT>(value1);
			auto instance = ThreadPool::getInstance();

			if (!instance->findChildById(child_id)) {
				return;
			}

			auto child = instance->getChildById(child_id);
			auto state = child->state();
			PTR(rets) << (long double)state;
			return;
		}

		// thread_wait			�ȴ��߳̽���		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_wait)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::number)
			{
				return;
			}


			numberT child_id = LetObject::cast<numberT>(value1);
			auto instance = ThreadPool::getInstance();

			if (!instance->findChildById(child_id)) {
				return;
			}

			auto child = instance->getChildById(child_id);
			bool success = child->wait();
			if (success)
				PTR(rets) << true;
			return;
		}

		// thread_stop			�����߳�		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_stop)		// ���鲻�� print������������
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::number)
			{
				return;
			}


			numberT child_id = LetObject::cast<numberT>(value1);
			auto instance = ThreadPool::getInstance();

			if (!instance->findChildById(child_id)) {
				return;
			}

			auto child = instance->getChildById(child_id);
			bool success = child->stop();
			if (success)
				PTR(rets) << true;
			return;
		}

		// thread_resume		�ָ��߳�		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_resume)	// ���鲻�� print������������
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::number)
			{
				return;
			}


			numberT child_id = LetObject::cast<numberT>(value1);
			auto instance = ThreadPool::getInstance();

			if (!instance->findChildById(child_id)) {
				return;
			}

			auto child = instance->getChildById(child_id);
			bool success = child->resume();
			if (success)
				PTR(rets) << true;
			return;
		}

		// thread_kill		    ɱ���߳�		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_kill)		// ���鲻�� print������������
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::number)
			{
				return;
			}


			numberT child_id = LetObject::cast<numberT>(value1);
			auto instance = ThreadPool::getInstance();

			if (!instance->findChildById(child_id)) {
				return;
			}

			auto child = instance->getChildById(child_id);
			bool success = child->kill();
			if (success)
				PTR(rets) << true;
			return;
		}

		// thread_join		    ����߳�		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_join)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::number)
			{
				return;
			}


			numberT child_id = LetObject::cast<numberT>(value1);
			auto instance = ThreadPool::getInstance();

			if (!instance->findChildById(child_id)) {
				return;
			}

			auto child = instance->getChildById(child_id);
			bool success = child->join();
			if (success)
				PTR(rets) << true;
			return;
		}

		// thread_detach		�����߳�		���ɹ�����true�����򷵻�null
		EXPORTDLL(thread_detach)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::number)
			{
				return;
			}


			numberT child_id = LetObject::cast<numberT>(value1);
			auto instance = ThreadPool::getInstance();

			if (!instance->findChildById(child_id)) {
				return;
			}

			auto child = instance->getChildById(child_id);
			bool success = child->detach();
			if (success)
				PTR(rets) << true;
			return;
		}

		EXPORTDLL(thread_clear)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::number)
			{
				return;
			}


			numberT child_id = LetObject::cast<numberT>(value1);
			auto instance = ThreadPool::getInstance();

			if (!instance->findChildById(child_id)) {
				return;
			}

			auto child = instance->getChildById(child_id);
			auto state = child->state();
			if (state == ThreadChild::Thread_State::stop) {
				instance->removeChildById(child_id);
				PTR(rets) << true;
			}
			return;
		}
	}
}
#include "ThreadPool.h"
#include <random>

ThreadPool* ThreadPool::m_instance = nullptr;

ThreadPool* ThreadPool::getInstance()
{
    static Gc _gc;
    if (m_instance == nullptr) {
        m_instance = new ThreadPool();
        if (!m_instance->init()) {
            delete m_instance;
            m_instance = nullptr;
        }
    }

    return m_instance;
}

ThreadChildPtr ThreadPool::getChildById(numberT id)
{
    auto find = m_id_child.find(id);
    if (find == m_id_child.end()) {
        ThreadChildPtr ptr(new ThreadChild);
        auto result = m_id_child.insert({ id,ptr });
        find = result.first;
    }

    return find->second;
}

numberT ThreadPool::getNewChild()
{
    std::default_random_engine e;
    e.seed(time(0));

    numberT ret_num = e();

    while (true) {
        if (m_id_child.find(ret_num) == m_id_child.end())
        {
            ThreadChildPtr ptr(new ThreadChild);
            m_id_child.insert({ ret_num,ptr });
            break;
        }
        ret_num = e();
    }

    

    return ret_num;
}

bool ThreadPool::findChildById(numberT id)
{
    if (m_id_child.find(id) == m_id_child.end())
        return false;

    return true;
}

bool ThreadPool::removeChildById(numberT id)
{
    auto iter = m_id_child.find(id);
    if (iter != m_id_child.end()) {
        m_id_child.erase(iter);
        return true;
    }
    return false;
}

// 初始化
bool ThreadPool::init()
{
    return true;
}

// 销毁
void ThreadPool::onDestory()
{
    m_id_child.clear();
}


// Gc回收
ThreadPool::Gc::~Gc()
{
    if (m_instance != nullptr) {
        m_instance->onDestory();
        delete m_instance;
        m_instance = nullptr;
    }
}

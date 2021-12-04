#ifndef __XTHREAD_POOL_HPP__
#define __XTHREAD_POOL_HPP__
#include "NocopyClass.hpp"
#include "thread_task.hpp"
#include <vector>
class worker_threads; // 前向声明
class XThreadPool : protected  NocopyClass
{
public:
    static XThreadPool* getInstance();
    void Init(int threadCount);             // 线程初始化
    void dispatch(thread_task* task);
private:
    int m_count = 0;                          // 线程数量
    int lastThread = -1;                     // 上一个线程
    std::vector<worker_threads*> threads;   //  线程池的线程
    ~XThreadPool(){}
};

#endif
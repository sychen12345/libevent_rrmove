#include "xthread_pool.hpp"
#include "worker_threads.hpp"
#include <glog/logging.h>
#include <chrono>
#include <thread>
//using namespace std;
XThreadPool* XThreadPool::getInstance()
{
    static XThreadPool p;
    return &p;
}
void XThreadPool::Init(int threadCount)
{
    this->m_count = threadCount;
    for (int i = 0; i < threadCount; i++)
    {
        worker_threads* t = new worker_threads();
        /*
            启动线程，并且赋予线程编号
        */
        t->start();
        t->set_pthread_id(i+1);
        threads.push_back(t);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void XThreadPool::dispatch(thread_task* task)
{
    // 取余轮询法分发线程
    if(!task) return;
    int tid = (lastThread+1)%this->m_count;
    lastThread = tid;
    worker_threads* work = threads[tid]; 
    VLOG(0)<<"signal threads"<<tid;
    work->add_task(task); // 把任务添加到任务链中
    work->activate(); // 激发线程
    
}

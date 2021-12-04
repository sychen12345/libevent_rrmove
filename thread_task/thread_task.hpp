#ifndef __THREAD_TASK_HPP__
#define __THREAD_TASK_HPP__
#include <list>
class thread_task
{
private:
    /* data */
public:
    thread_task(/* args */);
    ~thread_task();
     virtual bool Init()=0;   // 初始化任务
public:
    struct event_base *base;
    int sockfd = 0;
    int thread_id = 0;
    /*
    std::list<thread_task*> l_tasks; // 任务链
    std::mutex tasks_mutex;
    */
};
#endif
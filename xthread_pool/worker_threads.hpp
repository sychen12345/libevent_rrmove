#ifndef __WORKER_THREADS_HPP__
#define __WORKER_THREADS_HPP__
#include <mutex>
#include <list>
class thread_task;
class worker_threads
{
public:
    worker_threads();
    ~worker_threads();
    void set_pthread_id(int pthread_id);
    int get_pthread_id();
public:
    void start();
    void thread_Func();

    bool setup();                               // create pipe
    static void event_funcb(int fd, short, void *);
    void activate();
    void notify(int fd, short ev);              // signal thread
    void add_task(thread_task* tasks);
private:
    struct event_base* m_base;
    int notify_send_fd = 0;
    int t_id;
    std::list<thread_task*> m_tasks; // 任务链
    std::mutex m_tasks_mutex;
};


#endif
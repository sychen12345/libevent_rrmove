#include "worker_threads.hpp"
#include "events_base.hpp"
#include "events_config.hpp"
#include "thread_task.hpp"

#include "args_check.h"

#include <event2/event.h>
#include <glog/logging.h>

#include <thread>
worker_threads::worker_threads(/* args */)
{
}

worker_threads::~worker_threads()
{
}
void worker_threads::add_task(thread_task* tasks)
{

    if (!tasks)
        return;
    tasks->base = this->m_base;
    // 赋值不用互斥
    this->m_tasks_mutex.lock();
    this->m_tasks.push_back(tasks);
    this->m_tasks_mutex.unlock();
    VLOG(1)<<"Add the task to the task list";
    
}
void worker_threads::start()
{
    setup();
    std::thread th(&worker_threads::thread_Func,this);
    th.detach();
    // 创建线程，分离
}
void worker_threads::thread_Func()
{
    VLOG(0) << "create  "<<std::this_thread::get_id()<<"  "<<get_pthread_id();
    event_base_dispatch(m_base);
    event_base_free(m_base);
    VLOG(1) << "create  "<<std::this_thread::get_id()<<"  "<<get_pthread_id();

}
int worker_threads::get_pthread_id()
{
    return this->t_id;
}
void worker_threads::set_pthread_id(int id)
{
    this->t_id = id;
}
void worker_threads::activate()
{
    // 往管道里面写入
    int ret = write(this->notify_send_fd,"c",1);
    ERROR_CHECK(ret,-1,"write pipe");
}
void worker_threads::notify(evutil_socket_t fd, short which)
{
    char buf[2] = {0};
    int ret = read(fd,buf,2);
    if(ret <= 0)
    {
        VLOG(3)<<"pipe error"<<std::this_thread::get_id();
    }
    VLOG(1)<<"accept tcp "<<buf;
                                            // 从任务链里获取到任务
                                            // m_tasks_mutex.lock();
    if (this->m_tasks.empty())
    {
        VLOG(2)<<"get tasks error   "<<this->t_id;
        return ;
    }
    thread_task *work_task = nullptr;
                                            // 加锁，获取任务，先进先出
    m_tasks_mutex.lock();
    work_task = this->m_tasks.front();
    m_tasks.pop_front();
    m_tasks_mutex.unlock();
    work_task->Init();                      // 初始化buffer_event缓冲区
    
}
void worker_threads::event_funcb(evutil_socket_t fd, short which, void *arg)
{
                                // 激活线程任务的回调函数
    worker_threads* th =(worker_threads*)arg;
    th->notify(fd,which);
                                // 选择水平触发，只读一个字符即可
  
}
bool worker_threads::setup()
{
                                // 创建管道
    int pipes[2];
    if(pipe(pipes))
    {
         VLOG(3) <<"pipe failed";
         return false; 
    }
    notify_send_fd = pipes[1];  // 存入写端的文件描述符
    
    events_config config;
    config.set_event_config();
    auto p = config.get_event_config();
    this->m_base = event_base_new_with_config(p);

                                // 添加管道事件
    event *ev = event_new(m_base,pipes[0],EV_READ|EV_PERSIST,event_funcb,this);
    
    event_add(ev,0);
    
    if(!m_base)
    {
        VLOG(3) << "config thread no lock is error";
    }
    return true;
}
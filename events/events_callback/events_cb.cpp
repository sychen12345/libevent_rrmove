#include "events_cb.hpp"
#include "xthread_pool.hpp"
#include "xftp_server_cmd.hpp"

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <glog/logging.h>
void events_cb::listen_cb(struct evconnlistener * e, evutil_socket_t fd, sockaddr *addr, int socklen, void *arg)
{
    
    thread_task *task = new xftp_server_cmd();
    VLOG(0)<<"create task";
    // 一旦监听到事件的到来，就立刻分发任务
    task->sockfd = fd;
    XThreadPool::getInstance()->dispatch(task);

}
void events_cb::read_cb(struct bufferevent *buffer,void *arg)
{
    VLOG(0)<<"read_cb";
    char data[1024] ={0};
    for(;;)
    {
        int len = bufferevent_read(buffer,data,sizeof(data)-1);
        if (len<=0)
        {
            /* code */
            break;
        }
        VLOG(0)<<"recv client  = "<<data;
    }
}
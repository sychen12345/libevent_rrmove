#include "xftp_server_cmd.hpp"
#include "events_buffer_cb.hpp"
#include "events_cb.hpp"

#include <glog/logging.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <atomic>
#include <thread>
#include <list>
xftp_server_cmd::xftp_server_cmd(/* args */)
{
    base = NULL;
}

xftp_server_cmd::~xftp_server_cmd()
{
        
}
bool xftp_server_cmd::Init()
{
    VLOG(1)<<"xftp_server_cmd_init()"<<std::endl;
    bufferevent *buffer = bufferevent_socket_new(base,sockfd,BEV_OPT_CLOSE_ON_FREE); // 关闭关闭socket对象
    bufferevent_setcb(buffer,events_cb::read_cb,0,0,this);
    bufferevent_enable(buffer,EV_READ|EV_WRITE);
    // 设置缓冲区事件权限
    return true;
}

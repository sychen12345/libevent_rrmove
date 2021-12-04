#ifndef __EVENTS_CB_HPP__
#define __EVENTS_CB_HPP__
#include <event2/listener.h>
class events_cb
{
    public:
    static void listen_cb(struct evconnlistener * e, evutil_socket_t fd, sockaddr *addr, int socklen, void *arg);
    static void read_cb(struct bufferevent *,void *);
};
#endif
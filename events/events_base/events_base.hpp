#ifndef __EVENTS_BASE_HPP__
#define __EVENTS_BASE_HPP__
#include <event2/event.h>
#include <event2/listener.h>
#define PORT 5002
class event_bases
{
    public:
    event_bases();
    ~event_bases()
    {
        event_base_free(m_base);
        evconnlistener_free(m_ev);
    }
    int event_init();
    void event_run();
    private:
    event_base* m_base;
    sockaddr_in m_sin;
    evconnlistener *m_ev;
    
};
#endif
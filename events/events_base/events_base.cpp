#include "events_base.hpp"
#include "events_cb.hpp"
#include <glog/logging.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <string.h>
event_bases::event_bases()
{
    memset(&m_sin,0,sizeof(m_sin));
    m_sin.sin_family = AF_INET;
    m_sin.sin_port = htons(PORT);
}
int event_bases::event_init()
{
    
    m_base = event_base_new();
    if(m_base == NULL)
        return -1;
    m_ev = evconnlistener_new_bind(m_base,
    events_cb::listen_cb,
    m_base,
    LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE,
    10,
    (sockaddr*)&m_sin,
    sizeof(m_sin));
    if(m_ev == NULL)
        return -1;
    VLOG(0)<<"event_init over0";
    return 0;
}
void event_bases::event_run()
{
    event_base_dispatch(m_base);
}
#include "events_config.hpp"
#include <event2/event-config.h>
#include <event2/event.h>
events_config::events_config()
{
    m_ev_config = event_config_new();   
}
events_config::~events_config()
{
    event_config_free(m_ev_config);
}
void events_config::set_event_config()
{
    // 设置无锁配置
    event_config_set_flag(m_ev_config,EVENT_BASE_FLAG_NOLOCK);
}
event_config* events_config::get_event_config()
{
    return this->m_ev_config;
}
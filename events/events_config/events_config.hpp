#ifndef __EVENTS_CONFIG_HPP__
#define __EVENTS_CONFIG_HPP__

class events_config
{
    public:
    events_config();
    ~events_config();
    void set_event_config();
    struct event_config* get_event_config();
    private:
    struct event_config *m_ev_config;
};
#endif
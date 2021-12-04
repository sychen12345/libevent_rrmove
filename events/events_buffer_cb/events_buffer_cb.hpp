#ifndef __EVENTS_BUFFER_CB_HPP__
#define __EVENTS_BUFFER_CB_HPP__
class events_buffer_cb
{
private:
    /* data */
public:
    events_buffer_cb(/* args */);
    ~events_buffer_cb();
    static void buffer_read_cb(struct bufferevent *,void *);
};



#endif
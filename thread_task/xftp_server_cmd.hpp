#ifndef __XFTP_SERVER_CMD_HPP__
#define __XFTP_SERVER_CMD_HPP__
#include "thread_task.hpp"

class xftp_server_cmd : public thread_task 
{
private:
    /* data */
public:
    virtual bool Init();
    xftp_server_cmd(/* args */);
    ~xftp_server_cmd();
};


#endif
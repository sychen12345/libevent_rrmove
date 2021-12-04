#include <iostream>

#include "events_base.hpp"
#include "events_cb.hpp"


#include "xthread_pool.hpp"
#include "worker_threads.hpp"
#include "events_config.hpp"
#include "utils.h"
#include <signal.h>

#include <glog/logging.h>
void setLog()
{
    FLAGS_v = 2;
    FLAGS_logtostderr = false;
    FLAGS_log_dir = "/home/chen/cpp/cpp2/test9/log";
    FLAGS_max_log_size = 100;
}
int main(int argc,char** argv)
{
    FLAGS_alsologtostderr = 1;
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return 1;
    FLAGS_logtostderr = 1;
	  google::InitGoogleLogging(argv[0]);
    setLog();
    event_bases *base = new event_bases();
    
    auto threadpool = XThreadPool::getInstance();
    threadpool->Init(5);
    base->event_init();
    base->event_run();
    delete base;
    
}
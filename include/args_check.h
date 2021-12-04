#ifndef __ARGS_CHECK_H__
#define __ARGS_CHECK_H__
#define ERROR_CHECK(ret, retVal, funcName) { \
    if(ret == retVal) { \
        VLOG(3) << funcName; \
    } \
}
#endif
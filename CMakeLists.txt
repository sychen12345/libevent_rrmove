project(RRmove)
cmake_minimum_required(VERSION 3.1)
set(CMAKE_BUILD_TYPE "Debug")
add_compile_options(-std=c++17)
# Add the source in project root directory
aux_source_directory(. DIRSRCS)
find_package(glog 0.6.0 REQUIRED)
# Add header file include directories
include_directories(${PROJECT_SOURCE_DIR}/events/events_buffer_cb)
include_directories(${PROJECT_SOURCE_DIR}/events/events_base)
include_directories(${PROJECT_SOURCE_DIR}/events/events_config)
include_directories(${PROJECT_SOURCE_DIR}/events/events_callback)
include_directories(${PROJECT_SOURCE_DIR}/xthread_pool)
include_directories(${PROJECT_SOURCE_DIR}/include)
#include_directories(${PROJECT_SOURCE_DIR}/events_config)
include_directories(${PROJECT_SOURCE_DIR}/thread_task)


# Add block directories

#add_subdirectory(event_base)
#add_subdirectory(event_callback)
add_subdirectory(xthread_pool)
#add_subdirectory(events_config)
add_subdirectory(thread_task)
add_subdirectory(${PROJECT_SOURCE_DIR}/events/events_buffer_cb)
add_subdirectory(${PROJECT_SOURCE_DIR}/events/events_config)
add_subdirectory(${PROJECT_SOURCE_DIR}/events/events_base)
add_subdirectory(${PROJECT_SOURCE_DIR}/events/events_callback)
# Target
#set(${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${PROJECT_SOURCE_DIR})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) #设置可执行文件生产的位置
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build) #设置可执行文件生产的位置
add_executable(RRmove ${DIRSRCS})
# 编译的前后顺序也有一致性，A链接了B， main.cpp要先链接B，才能链接A，比如就出错

#target_link_libraries(RRmove glog::glog pthread crypto event event_pthreads hiredis mysqlclient xthread_pool event_base event_callback  pthread crypto events_config thread_task events_buffer_cb)
target_link_libraries(RRmove glog::glog pthread crypto event event_pthreads hiredis mysqlclient xthread_pool  pthread crypto events_buffer_cb events_base events_config events_callback thread_task)

# target_link_libraries(RRmove )
# 后写的目录要后加进去
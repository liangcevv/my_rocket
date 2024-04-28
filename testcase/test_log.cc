#include <pthread.h>


#include "rocket/common/log.h"
#include "rocket/common/config.h"

void* fun(void*){

    DEBUGLOG("debug this is thread log in %s","fun");
    INFOLOG("info this is thread log in %s","fun");
    return NULL;
}
int main(){

     rocket::Config::SetGlobalConfig("../conf/rocket.xml");
     rocket::Logger::InitGlobalLogger();

     pthread_t thread;
     pthread_create(&thread,NULL, &fun,NULL);
     DEBUGLOG("test debug log %s","ll");
    
     INFOLOG("test info log %s","ll");
     pthread_join(thread,NULL);
     // std::string formatted = rocket::formatString("Hello, %s! ", "world");
     // std::cout << formatted << std::endl;

     // std::string msg = (new rocket::LogEvent(rocket::LogLevel::Debug))->toString() ;
     // std::cout << msg << std::endl;
     // rocket::Logger::GetGlobalLogger()->pushLog(msg);  
     // rocket::Logger::GetGlobalLogger()->log();
     return 0;
}

// 这种情况可能是由于日志库中的互斥锁未正确管理导致的。
// 在多线程环境中，如果互斥锁的使用不正确，会导致竞争条件（Race Condition）,
// 从而出现不确定的行为，例如日志重复打印的情况
// ./test_log 
// Init log level [INFO]
// [INFO]  [24-04-23 23:56:10.644] [pid:11686 thread_id:11686][testcase/test_log.cc 22] test info log ll

// [INFO]  [24-04-23 23:56:10.644] [pid:11686 thread_id:11687][testcase/test_log.cc 10] info this is thread log in fun

// [INFO]  [24-04-23 23:56:10.644] [pid:11686 thread_id:11686][testcase/test_log.cc 22] test info log ll

// [INFO]  [24-04-23 23:56:10.644] [pid:11686 thread_id:11687][testcase/test_log.cc 10] info this is thread log in fun
#include <sys/time.h>
#include <string>
#include "rocket/common/log.h"
#include "rocket/common/util.h"
#include <sstream>





namespace rocket{

static Logger* g_loggger = NULL;

Logger* Logger::GetGlobalLogger()
{
        return g_loggger;
}

void Logger::InitGlobalLogger(){

    LogLevel global_log_level = StringToLevel( Config::GetGlobalConfig()->m_log_level);
    printf("Init log level [%s]\n",LogLevelToString(global_log_level).c_str() );
    g_loggger = new Logger(global_log_level);

}
std::string LogLevelToString(LogLevel level){
    switch (level)
    {
    case Debug:
        return "DEBUG";
    case Info:
        return "INFO";   
    case Error:
        return "ERROR";
    default:
        return "UNKONW";
        break;
    }
  }  

LogLevel StringToLevel(const std::string& log_level){
    if(log_level == "DEBUG"){
        return Debug;
    }else if(log_level == "INFO"){
         return Info;
    }else if(log_level == "ERROR"){
         return Error;
    }else {
        return Unkonwn;
    }
}
  

  std::string LogEvent::toString()
  {
    struct timeval now_time;

    gettimeofday(&now_time,nullptr);

    struct tm now_time_t;
    localtime_r(&(now_time.tv_sec),&now_time_t);

    char buf[128];
    strftime(&buf[0],128,"%y-%m-%d %H:%M:%S",&now_time_t);
    std::string time_str(buf);
    int ms = now_time.tv_usec / 1000;
    time_str = time_str + "." + std::to_string(ms);

    m_pid = getPid();
    m_thread_id = getThreadId();
  
   std::stringstream s_s;
   s_s << "[" << LogLevelToString(m_level) <<  "]\t"
       << "[" << time_str << "]\t"
       << "[pid:" << m_pid << " thread_id:" << m_thread_id << "]";
        
    return s_s.str();
 }
    
  
  void Logger::pushLog(const std::string& msg){

    //  ScopMutext<Mutex> lock(m_mutex);
    //  m_buffer.push(msg);
    //  lock.unlock();
     ScopMutext<Mutex> lock(m_mutex);
     m_buffer.push(msg);
     lock.unlock();
  }

  void Logger::log(){

    ScopMutext<Mutex> lock(m_mutex);
    std::queue<std::string > tmp ;
    m_buffer.swap(tmp);
    lock.unlock();

    while (!tmp.empty())
    {
        std::string msg = tmp.front();
        tmp.pop();
        printf("%s\n",msg.c_str());
    }
    

    
  }
// void Logger::log() {
//     ScopMutext<Mutex> lock(m_mutex);
//     std::queue<std::string> tmp = m_buffer;
   
//     lock.unlock();  // 释放锁，允许其他线程继续往缓冲区添加日志

//     // 一次性读取日志缓冲区中的所有日志信息
//     while (!tmp.empty()) {
//         std::string msg = tmp.front();
//         tmp.pop();
//         printf("%s\n",msg.c_str());
//     }
// }


}
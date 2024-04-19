#include <sys/time.h>
#include <string>
#include "rocket/common/log.h"
#include "rocket/common/util.h"
#include <sstream>





namespace rocket{

static Logger* g_loggger = NULL;

Logger* Logger::GetGlobalLogger()
{
    if(g_loggger){
        return g_loggger;
    }
    g_loggger = new Logger();
    return g_loggger;
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


  std::string LogEvent::toString()
  {
    struct timeval now_time;

    gettimeofday(&now_time,nullptr);

    struct tm now_time_t;
    localtime_r(&(now_time.tv_sec),&now_time_t);

    char buf[128];
    strftime(&buf[0],128,"%y-%m-&d %H:%M:%S",&now_time_t);
    std::string time_str(buf);
    int ms = now_time.tv_usec * 1000;
    time_str = time_str + "." + std::to_string(ms);

    m_pid = getPid();
    m_thread_id = getThreadId();

   std::stringstream s_s;
   s_s << "[" << LogLevelToString(m_level) <<  "]\t"
       << "[" << time_str << "]\t"
       << "[" << std::string(__FILE__) << ":" <<__LINE__ <<  "] [pid:" << m_pid << " thread_id:" << m_thread_id << "]\n";
        
    return s_s.str();

 }
    
  
  void Logger::pushLog(const std::string& msg){

    m_buffer.push(msg);

  }

  void Logger::log(){
    while (!m_buffer.empty())
    {
        std::string msg = m_buffer.front();
        m_buffer.pop();
        printf(msg.c_str());
    }

    
    
  }
}
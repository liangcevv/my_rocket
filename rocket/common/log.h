#ifndef ROCKET_COMMON_LOG_H
#define ROCKET_COMMON_LOG_H

#include <string>
#include <memory>
#include <stdio.h>
#include <queue>
#include <sstream>
#include "rocket/common/config.h"
#include "rocket/common/mutex.h"

#define DEBUGLOG(str, ...) \
  if ( rocket::Logger::GetGlobalLogger()->getLogLevel() <= rocket::Debug ) \
  {\
    rocket::Logger::GetGlobalLogger()->pushLog((new rocket::LogEvent(rocket::LogLevel::Debug))->toString() + "[" + std::string(__FILE__) + " " + std::to_string(__LINE__) + "] " + rocket::formatString(str,##__VA_ARGS__) + "\n");  \
    rocket::Logger::GetGlobalLogger()->log();\
  }

#define INFOLOG(str, ...) \
 if ( rocket::Logger::GetGlobalLogger()->getLogLevel() <= rocket::Info ) \
 {\
   rocket::Logger::GetGlobalLogger()->pushLog((new rocket::LogEvent(rocket::LogLevel::Info))->toString() +  "[" + std::string(__FILE__) + " " + std::to_string(__LINE__) + "] " + rocket::formatString(str,##__VA_ARGS__) + "\n");  \
   rocket::Logger::GetGlobalLogger()->log();\
 }


#define ERRORLOG(str, ...) \
if ( rocket::Logger::GetGlobalLogger()->getLogLevel() <= rocket::Error ) \
{\
  rocket::Logger::GetGlobalLogger()->pushLog((new rocket::LogEvent(rocket::LogLevel::Error))->toString() + "[" + std::string(__FILE__) + " " + std::to_string(__LINE__) + "] " + rocket::formatString(str,##__VA_ARGS__) + "\n");  \
  rocket::Logger::GetGlobalLogger()->log();\
}
namespace rocket{



template<typename... Args>
std::string formatString(const char* str,Args... args){

    int size = snprintf(nullptr, 0 , str, args...);

    std::string result;
    if(size > 0)
    {
        result.resize(size);
        //snprintf(&result[0],size,str,args...);   error.......
        snprintf(&result[0],size+1,str,args...);
    }

    return result;
    
}

enum LogLevel{
    Unkonwn = 0, 
    Debug = 1,
    Info = 2,
    Error = 3,
    
};

std::string LogLevelToString(LogLevel level);
LogLevel StringToLevel(const std::string& log_level);

class Logger{
public:

    typedef std::shared_ptr<Logger> s_ptr;

    Logger(LogLevel level) : m_set_level(level){}

    void pushLog(const std::string& msg);

    LogLevel getLogLevel() const{
        return m_set_level;
    }

 public:
    static Logger* GetGlobalLogger();
    static void InitGlobalLogger();
    void log();

private:
   LogLevel m_set_level;
   std::queue<std::string> m_buffer;

   Mutex m_mutex;

};

class LogEvent{
public:
    LogEvent(LogLevel level):m_level(level){}

    std::string getFileName() const{
        return m_file_name;
    }

    LogLevel getLogLevel() const{
        return m_level;
    }
    
    std::string toString();

private:
    std::string m_file_name;
    int32_t m_file_line;
    int32_t m_pid;
    int32_t m_thread_id;

    LogLevel m_level;
    Logger::s_ptr m_logger;
};



}

#endif
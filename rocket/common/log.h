#ifndef ROCKET_COMMON_LOG_H
#define ROCKET_COMMON_LOG_H

#include <string>
#include <memory>
#include <stdio.h>
#include <queue>
#include <sstream>


#define DEBUGLOG(str, ...) \
  std::string msg = (new rocket::LogEvent(rocket::LogLevel::Debug))->toString() + rocket::formatString(str,##__VA_ARGS__);\
  msg + "\n";\
  rocket::Logger::GetGlobalLogger()->pushLog(msg);  \
  rocket::Logger::GetGlobalLogger()->log();

namespace rocket{



template<typename... Args>
std::string formatString(const char* str,Args... args){

    int size = snprintf(nullptr, 0 , str, args...);

    std::string result;
    if(size > 0)
    {
        //snprintf(&result[0],size,str,args...);   error.......
        snprintf(&result[0],size+1,str,args...);
    }

    return result;
    
}

enum LogLevel{
    Debug = 1,
    Info = 2,
    Error = 3
};

std::string LogLevelToString(LogLevel level);

class Logger{
public:

    typedef std::shared_ptr<Logger> s_ptr;

    void pushLog(const std::string& msg);

 public:
    static Logger* GetGlobalLogger();

    void log();

private:
   LogLevel m_set_level;
   std::queue<std::string> m_buffer;

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
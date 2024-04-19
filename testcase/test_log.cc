#include "rocket/common/log.h"

int main(){

     DEBUGLOG("test log %s","ll");
    // std::string formatted = rocket::formatString("Hello, %s! ", "world");
    // std::cout << formatted << std::endl;
   
    // std::string msg = (new rocket::LogEvent(rocket::LogLevel::Debug))->toString() ;
    // std::cout << msg << std::endl;
    // rocket::Logger::GetGlobalLogger()->pushLog(msg);  
    // rocket::Logger::GetGlobalLogger()->log();

    return 0;
}
#include "logger.h"

#include <cstring>
#include <stdio.h>
#include <string.h>
#include <stdarg.h> //variadic argoument
#include <cerrno> //for strerror(errno)
#include <ctime> //for time

#include <fstream>
#include <filesystem> //for move file

bool init_logger() {
    //TODO: -create logging file
    //      -setup pseudoterminal
    
    //Name Log file 
    char nameLogFile[20] = "app.log";
    char nameOldLogFile[20] = "app.log.old";

    //Check existence of log file 
    std::ifstream file;
    file.open(nameLogFile);
    if (file){ 
        //file exist 
        //move file in a nameFile.old
        std::filesystem::rename(nameLogFile, nameOldLogFile);
        //std::remove(nameLogFile); ?????
    }
    file.close();

    return true;
}

void end_logger() {
    //TODO: clean-up logging file/ write entries 
}

void log_output(log_level level, const char* message, ...) {
    const char* level_name[6] = {"\033[31m[FATAL]:\033[0m ", "\033[91m[ERROR]:\033[0m ", "\033[33m[WARN]:\033[0m ", "\033[96m[INFO]:\033[0m ", "\033[95m[DEBUG]:\033[0m ", "\033[92m[TRACE]:\033[0m "};
    
    //add no color log output 
    //const char* level_name_base[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
    
    char out_message[32000];
    memset(out_message, 0, sizeof(out_message));

    //variadic argouments
    va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, 32000, message, arg_ptr);
    va_end(arg_ptr);
   
        //time 
    std::time_t now = time(&now);
    struct tm time = *localtime(&now);
    
    //print message 
    char print_message[32100];
    
    if(level < 2){
        sprintf(print_message, "\033[90m(%d:%d:%d)\033[0m %s%s: %s\n", time.tm_hour, time.tm_min, time.tm_sec,  level_name[level], out_message, std::strerror(errno)); //std::asctime(std::localtime(&now)),
    }else {
        sprintf(print_message, "\033[90m(%d:%d:%d)\033[0m %s%s\n", time.tm_hour, time.tm_min, time.tm_sec, level_name[level], out_message);
    }

    //TODO: custom print log into log file or pseudo terminal
    //printf("%s", print_message);
    
    //name log file (TODO: pass as paremetrer in some way, for different log file)
    char nameLogFile[20] = "app.log";
        
    //write to a file 
    std::ofstream file;
    file.open(nameLogFile, std::ios::out | std::ios::app);
    if(!file){
        //TODO: error message opening file 
        //cout << "Opening file failed" << endl;
    }
    file << print_message << std::endl;        
    //always open and close the log file???
    file.close();
    
}

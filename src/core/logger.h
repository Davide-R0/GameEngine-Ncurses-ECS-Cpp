#ifndef LOGGER_H
#define LOGGER_H

//cpp comments
//TODO:
//WARN:
//INFO:
//ERROR:


//enabling/disabling loggers
#define LOG_WARN_ENABLED    1    
#define LOG_INFO_ENABLED    1  
#define LOG_DEBUG_ENABLED   1
#define LOG_TRACE_ENABLED   1

typedef enum log_level{
    LOG_LEVEL_FATAL,
    LOG_LEVEL_ERROR,    
    LOG_LEVEL_WARN,    
    LOG_LEVEL_INFO,    
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_TRACE
} log_level;

bool init_logger();
void end_logger();

void log_output(log_level level, const char* message, ...);

//fatal level log 
#define GFATAL(message, ...) log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__); //__VA_ARGS__ replaced by the argoument in the macro and ## for optional variadic argoument (## (token pasting) operator)

//error level log 
#define GERROR(message, ...) log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);

#if LOG_WARN_ENABLED  == 1
#define GWARN(message, ...) log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
#define GWARN(message, ...) 
#endif 

#if LOG_INFO_ENABLED  == 1
#define GINFO(message, ...) log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
#define GINFO(message, ...) 
#endif 

#if LOG_DEBUG_ENABLED  == 1
#define GDEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
#define GDEBUG(message, ...) 
#endif 

#if LOG_TRACE_ENABLED  == 1
#define GTRACE(message, ...) log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
#define GTRACE(message, ...) 
#endif 


#endif

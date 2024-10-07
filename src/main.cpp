//#include <iostream>
//#include <ncurses.h>

#include "app.h"
#include "core/logger.h"

//#warning "aaaa"
//#error "aaaa"
    
int main (int argc, char** argv){
    
    //NOTE: initialization of logger before anyting else for all log info
    init_logger();

    app* Application = app::getInstance();
     
    Application->start();
        
    Application->end();
    
    delete Application;
    
    return 0;
}

//#include <iostream>
#include <ncurses.h>

#include "app.h"

#include "core/logger.h"

//not to include
//#include "entities/constant.h"
//#include "gameEng.h"
//#include "entities/entityMang.h"


int main (int argc, char** argv){
    //init logger
    //NOTE: initialization of logger before anyting else for all log info
    init_logger();

    app *Application = app::getInstance();
     
    Application->start();
        
    Application->end();

    
    return 0;
}

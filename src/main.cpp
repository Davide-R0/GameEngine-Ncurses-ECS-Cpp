#include "core/app.h"
#include "core/logger.h"

//#define NCURSES_WIDECHAR
//#warning "aaaa"
//#error "aaaa"

//for starting scene 
#include "battleshipGame/scenes/scMenu.h"
#include "scenes/sceneConstants.h"
#include "core/gameEngine.h"

int main (int argc, char** argv){
    
    //NOTE: initialization of logger before anyting else (for all log info)
    init_logger();

    app* Application = app::getInstance();
     
    Application->start();

    Application->getEngine()->changeScene(MENU, new scMenu());
    Application->getEngine()->run();
        
    Application->end();
    
    delete Application;
    
    return 0;
}

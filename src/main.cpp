#include <iostream>
#include <ncurses.h>

#include "app.h"

//not to include
#include "entities/constant.h"
//#include "gameEng.h"
#include "entities/entityMang.h"


int main (int argc, char** argv){

    std::cout<<"It works [main]\n";

    app *Application = app::getInstance();
    
    Application->start();
    
    //aggiungerlo nella applicazione
    entityMang * mng = entityMang::getInstance();

    mng->addEntity(BOARD);
    
    mng->update();
    
    Application->end();

    return 0;
}

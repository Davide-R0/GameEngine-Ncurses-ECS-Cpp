#include <iostream>
#include <ncurses.h>

#include "app.h"
#include "gameEng.h"

int main (int argc, char** argv){

    std::cout<<"It works [main]\n";

    app *Application = app::getInstance();
    
    Application->start();

    Application->end();

    return 0;
}

#include "app.h"

#include <iostream>
#include <ncurses.h>

/**********************************/
app *app::s_app = nullptr;

app *app::getInstance(){
    if (s_app == nullptr){
        s_app = new app();
        std::cout<<"Application Object created\n";
    }
    return s_app;
}
/**********************************/

void app::start() {
    initApp();
    loopApp();
}

//TODO: add check
bool app::initApp() {
    //init ncurses
    initscr();
    
    refresh();
    return true;
}

void app::loopApp() {
    getch();
}


void app::end() {
    endApp();
}

//TODO: add check
bool app::endApp() {
    //deallocate memori/end ncurses
    endwin();

    return true;
}

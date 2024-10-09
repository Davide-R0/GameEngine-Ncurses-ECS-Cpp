#include "app.h"
#include "core/logger.h"
#include "scenes/gameEngine.h"

//#include <iostream>
#include <ncurses.h>

/**********************************/
app *app::s_app = nullptr;

app *app::getInstance(){
    if (s_app == nullptr){
        s_app = new app();
        GTRACE("Application Constructor called");
    }
    return s_app;
}
/**********************************/

app::~app(){
    GTRACE("Application destructor called");
    delete m_game;
}

//TODO: add check
void app::start() {
    GINFO("Start Application");
    initApp();
    initGame();
}

//TODO: add check
bool app::initApp() {
    
    //logger test
    /*
    GFATAL("Fatal logger %f", 5.231);
    GERROR("Error logger %f", 5.231);
    GWARN("Warn logger %f", 5.231);
    GINFO("Info logger %f", 5.231);
    GDEBUG("Debug logger %f", 5.231);
    GTRACE("Trace logger %f", 5.231);
    */

    //(in case) init custom allocator

    //init ncurses
    initscr();
    //for more information see 'man cbreak'
    //cbreak(); nocbreak(); //no need end character 
              //^c wil exit the probram with error message
    raw();  //to make the getch() function an interrupt instead of a break in the program
            //getch() will not stop the probram until a character is pressed
    //noecho(); or echo(); //if the character is echoed to getch() (useful if want to not interact on certain window)
    noecho(); //will not print the character pressed on the screen

    nodelay(stdscr, true); //getch non bloacking call

    refresh();
    
    //get standard screen dimension
    getmaxyx(stdscr, m_yScr, m_xScr);
    GINFO("Start up terminal size (%d,%d)", m_xScr, m_yScr);

    return true;
}

//TODO: add check
bool app::initGame() {

    m_game = gameEngine::getInstance();
    m_game->run();

    return true;
}

//TODO: add check
void app::end() {
    GINFO("End Application");
    //deallocate memory
    
    //end ncurses
    endwin();
    endGame();

    //end logger
    end_logger();
}

//TODO: add check
bool app::endGame() {
    //end game
    //m_game->end();
    delete m_game;
    
    return true;
}

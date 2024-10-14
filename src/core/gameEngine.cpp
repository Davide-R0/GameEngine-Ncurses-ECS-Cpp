#include "gameEngine.h"
#include "../core/logger.h"

//wide character ncurses variant
#include <ncursesw/ncurses.h>
//#include <ncurses.h>

#include "../scenes/scene.h"
//#include "scPlay.h"
//#include "../scenes/sceneConstants.h"
#include "../actions/action.h"
#include <cstdlib> //size_t

//NOTE: is not efficient but it's a terminal game engine...
//#include <sys/time.h>
#include <chrono>
#include <thread>

/**********************************/
gameEngine* gameEngine::s_gameEngine = nullptr;

gameEngine* gameEngine::getInstance(){
    if (s_gameEngine == nullptr){
        s_gameEngine = new gameEngine();
        s_gameEngine->init();
        GTRACE("Game Engine constructor called");
    }
    return s_gameEngine;
}
/**********************************/

gameEngine::~gameEngine() {
    GTRACE("Game Engine destructor called");
    for(std::size_t i = 0; i<NUMBER_SCENE_TAG_DO_NOT_USE; i++) {
        delete m_scenes[i];
        m_scenes[i] = nullptr;
    }
}


void gameEngine::init() {
    //start with a scene
    GTRACE("Game engine init");

    }

void gameEngine::run() {
    //main loop
    GINFO("Game loop started");

    int ch;
    ACTION_NAME actionName;
    std::chrono::milliseconds previous = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    std::chrono::milliseconds current;
    std::chrono::milliseconds elapsed;
    std::chrono::milliseconds lag = std::chrono::milliseconds::zero();
    
    std::chrono::milliseconds msUpdate = std::chrono::milliseconds(1000/30);
    
    //bool test = true;

    //main game loop
    while (m_running) {
        /*test = !test;
        if (test) {
            mvwprintw(stdscr, 1, 1, " ");
        } else { 
            mvwprintw(stdscr, 1, 1, "O");
        }*/
        

        
        wrefresh(stdscr);

        //timesteps
        current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        elapsed = current - previous;
        previous = current;
        lag = lag + elapsed;
        
        //while (lag >= msUpdate){
        //first in main loop
            m_scenes[m_currentScene]->update();
            lag -= msUpdate;
        //}
        if (elapsed < msUpdate) {
            std::this_thread::sleep_for(msUpdate-elapsed);
        }

        ch = getch();
        
 
        if (ch != ERR){
            //printw("%d\n", ch);
            //GDEBUG("Pressed: %d", ch);
            
            actionName = currentScene()->getActionName(ch);
            
            if (actionName != 0) {   //0 means no action (see the enum ACTION_NAME)
                const ACTION_PHASE actionType = PRESS;  //ncurses do not distinguish press/release
                currentScene()->sDoAction(new action(actionName, actionType));
            }

            if (ch == 3) {  //termination process code ^C 
                m_running = false;
            }
        }
        
        /*
        //pause functonality for the entire game engine??
        if(!m_scenes[m_currentScene].isPaused()){
            //...
            //cosa eseguire se il gioco non è in pausa
            ////sCollisison()
            //sUserInput()
            //sRenderer()
        }
        */
    }

    GINFO("Game loop ended");
}

void gameEngine::changeScene(SCENE_TAG tag, scene* scene) {
    //TODO: controllare che non si stiano copiando dati inutilmente (specialmente che non si stia copiando l'intera "scene")
    //TODO: aggiungere controllia
    GDEBUG("Here");
    m_currentScene = tag;
    GDEBUG("Here");
    m_scenes[tag] = scene;
    GDEBUG("Here");
}

scene* gameEngine::currentScene() const {
    return m_scenes[m_currentScene];
}

//NOTE: in this case assets are loaded one (because light) and not per each scene
//otherwise this should have been in the sceneBase class
/*
assets& gameEngine::getAssets() {
    return m_assets;
}*/





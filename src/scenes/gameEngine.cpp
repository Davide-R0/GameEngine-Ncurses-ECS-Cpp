#include "gameEngine.h"
#include "../core/logger.h"
#include <ncurses.h>
#include "sceneBase.h"
#include "scPlay.h"
#include "sceneConstants.h"
#include "../actions/action.h"
#include <cstdlib> //size_t

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

    m_currentScene = PLAY;
    m_scenes[m_currentScene] = new scPlay();
}

void gameEngine::run() {
    //main loop
    GINFO("Game loop started");

    int ch;
    ACTION_NAME actionName;

    //main game loop
    while (m_running) {
        //first thing in main loop
        m_scenes[m_currentScene]->update();

        ch = getch();

        if (ch != ERR){
            printw("%d\n", ch);
            //GDEBUG("Pressed: %d", ch);
            
            actionName = currentScene()->getActionName(ch);
            printw("action name %d\n", actionName);
            if (actionName != 0) {   //0 means no action (see the enum ACTION_NAME)
                const ACTION_PHASE actionType = PRESS;
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

void gameEngine::changeScene(SCENE_TAG tag, sceneBase& scene) {
    //TODO: controllare che non si stiano copiando dati inutilmente (specialmente che non si stia copiando l'intera "scene"
    //TODO: aggiungere controlli
    m_currentScene = tag;
    m_scenes[tag] = &scene;
}

sceneBase* gameEngine::currentScene() {
    return m_scenes[m_currentScene];
}


/*
void gameEngine::sRender() {
    //clear window
    clear();

    for (auto e : m_entityMang->getEntities()){
        if (e->isToRender() && e->isAlive()){ 
            ncRendering(e);
        }
    }

    //display
}
*//*
void game::sNcCollide(std::shared_ptr<entity> a, std::shared_ptr<entity> b) {
    //a->cCollisionShapeNc->mask_layer ...
    //string della dimensione della board
    //per ogni elemento (a, b) controllare che le posizioni non escano dalla board
    //iterare lungo ogni nave e stamparla nella string controllando che la casella non sia già piena
}
*/
/*
void gameEngine::sCollision() {
    //colliison between ship 
    *//*
    for (auto e : m_entityMang->getEntities(SHIP)){
        //collion detection only if it have collision shape component
        if (e->cCollisionShapeNc != nullptr) {
            //e->cCollisionShapeNc->mask_layer ...
            //string della dimensione della board
            //per ogni elemento (a, b) controllare che le posizioni non escano dalla board
            //iterare lungo ogni nave e stamparla nella string controllando che la casella non sia già piena
            //fare il tutto per ogni board nel caso 

            //alternativa non giusta
            for (auto b : m_entityMang->getEntities(SHIP)) {
                if (b->cCollisionShapeNc != nullptr) {
                    //sNcCollide(e, b);
                }
            }
        }
    }
    //collision with board ????
    */
/*
}*/



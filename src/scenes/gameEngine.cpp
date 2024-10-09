#include "gameEngine.h"
#include "../core/logger.h"
//#include "../entities/constant.h"
//#include "../entities/entityMang.h"
#include <ncurses.h>
//#include "../entities/entity.h"
#include "sceneBase.h"
#include "scPlay.h"
#include "sceneConstants.h"
#include "../actions/action.h"

gameEngine::gameEngine() {
    GTRACE("Game object constructor called");
    init();
}

gameEngine::~gameEngine() {
    GTRACE("Game object destructor called");
    //TODO: liberare la memoria delle scene
    //for(int i = sizeof(m_scenes); i>=0; i--) {
    //    delete m_scenes[i];
    //}
    delete m_scenes[PLAY];
}

//#include "../components/Components.h"

void gameEngine::init() {
    //new//////////
    //start with a scene
    GTRACE("Game engine init");

    m_currentScene = PLAY;
    m_scenes[m_currentScene] = new scPlay();

    ///////////////////
}

#include "../actions/actionConstants.h"

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
            
            if (actionName != 0) {   //0 means no action (see the enum ACTION_NAME)
                const ACTION_PHASE actionType = PRESS;
                currentScene()->sDoAction(new action(actionName, actionType));
            }

            if (ch == 3) {  //termination process code ^C 
                m_running = false;
            }
        }
        
        /*
        //pause functonality
        if(!m_scenes[m_currentScene].isPaused()){
            //...
            //what to execute se il gioco non è in pausa
            ////sCollisison()
            //sUserInput()
            //sRenderer()
        }
        */
        //m_currentFrame++;
    }

    GINFO("Game loop ended");


}

void gameEngine::changeScene(SCENE_TAG tag, sceneBase& scene) {
    //TODO: aggiustare
    m_currentScene = tag;
    //if(se la scena è nuova aggoungerla al vettore){
    //m_scenes[m_currentScene].push_back(&scene);
    //}
}

sceneBase* gameEngine::currentScene() {
    return m_scenes[m_currentScene];
}

/*
void gameEngine::start() {
    GINFO("Start Game");
    mainLoop();
}
*/
/*
void gameEngine::mainLoop() {
    }*/
/*
void gameEngine::end() {
    GINFO("End Game");
    
}
*/



//...
//
/*
void gameEngine::sUserInput() {
    //only reading user input here, no implementation of input logic!!
    
    //add event object
    *//* esempio:
     se è premuto il pulsante "w" 
     then 
        m_player->cInput->up = true; //si modifica la variabile nel sistema di input 
    */
    
    //la logica dell'input è eseguita dalla funzione sMovement()
/*}
*//*
void gameEngine::sMovement() {
    //read the m_player->cInput and then change the component cTransform of the player entity
}
*//*
void gameEngine::ncRendering(std::shared_ptr<entity> a) {
    //...
    //change case if it is on board or not
    
}
*//*
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



#include "scPlay.h"
#include "../core/logger.h"


#include "../entities/entity.h"
#include "../entities/entityMang.h"
#include "../components/Components.h"
#include "../actions/action.h"
#include "../actions/actionConstants.h"
//#include "gameEngine.h"

scPlay::scPlay() {
    GTRACE("Scene play class constructor called");
    init();
}

scPlay::~scPlay() {
    GTRACE("Scene play class destructor called");
    //TODO: free memory
    delete m_entityMang;
    delete m_player;
    
    //do not delete m_game

}

void scPlay::update() {
    m_entityMang->update();
    
    if (!isPaused()) {
        //call systems ...
    }

    m_currentFrame++;
}

//#include <ncurses.h>

void scPlay::init() {
    ///////Initialization action map

    //dichiarare questa variabile oppure ricordarsi l'indice dell'enum...
    //i KEY_.. sono i valori di default di ncurses per i tasti 
    
    ACTION_NAME name;
    name = UP;
    registerAction((int)'w', name); //119 for the 'w? character
    name = DOWN;
    registerAction((int)'s', name);
    name = RIGHT;
    registerAction((int)'d', name);
    name = LEFT;
    registerAction(97, name);
    name = ENTER;
    registerAction(10, name);

    ////////general initialization
    //m_game = gameEngine::getInstance();
    m_entityMang = new entityMang();
    
    //setup window parameters

    //spawn initial scene
    m_entityMang->addEntity(BOARD);
    m_entityMang->update();
    
    //BUT if the component have a constructor with logic is necessary to call the constructor each time the new component is added, like this: (there is no other way to do this)
    m_entityMang->getEntities(BOARD)[0]->addComponent<CTransform>(new CTransform(10,10));
    m_entityMang->getEntities(BOARD)[0]->addComponent<CTransform>(new CTransform(10,10));
    //and to access che component:    
    GDEBUG("Component name %s", m_entityMang->getEntities(BOARD)[0]->getComponent<CTransform>()->name);
    
    //so if all the constructor of all components are empty (this mean that there must not be any private variable(?) or const value) you can let entity class create and destroy all components 
    
    //m_entityMang->getEntities(BOARD)[0]->~entity();
    
    m_player = new entity(PLAYER, -1);
    m_player->addComponent<CInput>(new CInput());
 
}

void scPlay::sRender() {
    
}

void scPlay::sDoAction(const action* act) {
    //NOTE: due modi per farlo: 
    //      1. metterci la logica delle azioni all'interno delle scene
    //      2. metterci la logica delle azioni nella classe action con classi derivate e base ecc...

    //if (act->getPhase() == 0) {    //0 for press in the enum
        if (act->getName() == 1) {   
            printw("w pressed\n");
        } else if (act->getName() == 2) {   
            printw("s pressed\n");
        } else if (act->getName() == 3) {   
            printw("d pressed\n");
        } else if (act->getName() == 4) {   
            printw("a pressed\n");
        } else if (act->getName() == 5) {   
            printw("Enter pressed\n");
        }
    //}

}

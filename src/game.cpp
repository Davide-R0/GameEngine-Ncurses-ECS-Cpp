#include "game.h"
#include "core/logger.h"
#include "entities/entityMang.h"
#include <ncurses.h>

game::game() {
    GINFO("Game object created");
    init();
}

void game::start() {
    
    GINFO("Start Game");

    GINFO("Game loop started");
    
    int ch;

    //main game loop
    while (m_running) {
        //first thing in main loop
        m_entityMang->update();
        
        ch = getch();
        if (ch != ERR){
            printw("%d\n", ch);
            GDEBUG("Pressed: %d", ch);
            
            if (ch == 3) {
                m_running = false;
            }
        }
        
        /*
        //pause functonality
        if(!m_paused){
            //...
            //what to execute se il gioco non è in pausa
            ////sCollisison()
            //sUserInput()
            //sRenderer()
        }
        */
        
        m_currentFrame++;
    }

    GINFO("Game loop ended");
}

void game::end() {
    GINFO("End Game");
    
}

void game::init() {
    m_entityMang = entityMang::getInstance();
    
    //...
    //setup window parameters

    //spawn initial scene
    m_entityMang->addEntity(BOARD);
    m_entityMang->update();

}

//...
//

void game::sUserInput() {
    //only reading user input here, no implementation of input logic!!
    
    //add event object
    /* esempio:
     se è premuto il pulsante "w" 
     then 
        m_player->cInput->up = true; //si modifica la variabile nel sistema di input 
    */
    
    //la logica dell'input è eseguita dalla funzione sMovement()
}

void game::sMovement() {
    //read the m_player->cInput and then change the component cTransform of the player entity
}

void game::ncRendering(std::shared_ptr<entity> a) {
    //...
    //change case if it is on board or not
    
}

void game::sRender() {
    //clear window
    clear();

    for (auto e : m_entityMang->getEntities()){
        if (e->isToRender() && e->isAlive()){ 
            ncRendering(e);
        }
    }

    //display
}
/*
void game::sNcCollide(std::shared_ptr<entity> a, std::shared_ptr<entity> b) {
    //a->cCollisionShapeNc->mask_layer ...
    //string della dimensione della board
    //per ogni elemento (a, b) controllare che le posizioni non escano dalla board
    //iterare lungo ogni nave e stamparla nella string controllando che la casella non sia già piena
}
*/

void game::sCollision() {
    //colliison between ship 
    /*
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

}



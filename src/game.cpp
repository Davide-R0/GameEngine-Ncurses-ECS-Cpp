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


void game::sRender() {
    //clear window
    
    //draw entities
    /*
    for (auto e : m_entityMang.getEntities()){
        if ( l'entità deve essere renderizzata){
            disegna l'entitàù
            m_window.draw(e);
        }
    }
    */

    //display
}

void game::sCollision() {
    //example:
    /*
    for (auto b : m_entities->getEntities(BULLET)) {
        for (auto e : m_entities->getEntities(ENEMY){
            //........
        }
    }
    */
}



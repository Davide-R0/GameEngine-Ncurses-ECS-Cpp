#include "game.h"

game::game() {
    init();
}

void game::start() {
    //pouse functionality

    //main game loop
    while (m_running) {
        //m_entities.update()
       
        /*
        if(!m_paused){
            //...
            //what to execute se il gioco non è in pausa
            ////sCollisison()
            //sUserInput()
            //sRenderer()
        }
        */

        
        
        //m_currentframe++;
    }
}

void game::end() {
    
}

void game::init() {
    //...
    //setup window parameters
    //spawn initial scene
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



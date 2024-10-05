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

    //
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



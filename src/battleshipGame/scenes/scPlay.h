#ifndef SCPLAY_H
#define SCPLAY_H

/*  Example of a scene in wich is being print the key number pressed and crated some entities
 *  must be declared:
 *  -update();
 *  -sRender();
 *  -sDoAction(action);
 */

#include "../../scenes/scene.h"
#include <cstdlib> //size_t

class entity;

//scene specific game example 
class scPlay : public virtual scene {
    public:
        scPlay();
        ~scPlay();
        
        //must always be implemented!
        void update();
        void sDoAction(const action* act);

    private:
        //ncurses utlity
        entity* m_focusWindow;

        entity* m_player;
        //player config
        //level path: string
        std::size_t m_currentFrame = 0; //like for last enemy spown time
        void init();

        //Serve???
        bool m_running = true;  //if game is running 

        //systems
        void sStaticNcRender(); //render called only at the begining of the scene
        void sRender(); //it must be always implemented!
        void sAnimation();
        void sMovement();
        void sEnemySpowner();
        void sCollision();
        void sDebug();

        //per le classi scene derivate:
        //assets m_assets;
        //render window
        //all config for the play
        //score
        /*

        //systems managing
        void sMovement();
        void sUserInput();
        void sCollision();
        //...

        //ncurses rendering
        void ncRendering(std::shared_ptr<entity> a);

        //system to check collision on a board
        void sNcCollide(std::shared_ptr<entity> a, std::shared_ptr<entity> b);
        
        void sRender();
        */
};

#endif 

#ifndef SCPLAY_H
#define SCPLAY_H

/*  Example of a scene in witch is being print the key number pressed and crated some entities
 *  must be declared:
 *  -update();
 *  -sRender();
 *  -sDoAction(action);
 */

#include "sceneBase.h"
class entity;
class action;

//scene specific game example 
class scPlay : public virtual sceneBase {
    public:
        scPlay();
        ~scPlay();
        
        //must always be implemented!
        void update();
        
        void sDoAction(const action* act);

    private:
        entity* m_player;
        //player config
        //level path: string

        int m_currentFrame = 0;

        void init();

        //systems
        
        //must always be implemented!
        void sRender();
        //void sDoAction(action);
        
        void sAnimation();
        void sMovement();
        void sEnemySpowner();
        void sCollision();
        void sDebug();
};

#endif 

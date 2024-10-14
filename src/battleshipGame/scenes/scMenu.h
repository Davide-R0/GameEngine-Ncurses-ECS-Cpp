#ifndef SCMENU_H
#define SCMENU_H

#include "../../scenes/scene.h"
#include <cstdlib>
#include "sMenu.h"
class entity;

//TODO: rinominare getAssets() to getAssetManager()

class scMenu : public virtual scene {
    public:
        scMenu();
        ~scMenu();

        //must always be implemented!
        void update();
        void sDoAction(const action* act);

    private:
        //ncurses utlity
        entity* m_focusWindow;
        
        menu* m_menu;

        //entity* m_player;
        //player config
        //level path: string
        std::size_t m_currentFrame = 0; //like for last enemy spown time
        void init();

        //Serve???
        bool m_running = true;  //if game is running 

        //systems
        void sStaticNcRender(); //render called only at the begining of the scene
        void sImageNcRender(entity* ent);
        void sRender(); //it must be always implemented!
        void sAnimation();
        void sMovement();
        void sEnemySpowner();
        void sCollision();
        void sDebug();
        

};

#endif 

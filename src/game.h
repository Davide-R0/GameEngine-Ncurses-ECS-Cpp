#ifndef GAME_H 
#define GAME_H 

#include "entities/entityMang.h"
#include "entities/entity.h"

#include <memory>


class game {
    
    public:
        //make a singleton????
        game();

        void start();

        void end();

    private:
        entityMang* m_entityMang;
        //font
        //text
        //render window
        //all config for the play
        //score
        //current frame
        std::size_t m_currentFrame = 0;
        //last enemy spown time
        bool m_paused = false;  //if update game logic
        bool m_running = true;  //if game is running

        std::shared_ptr<entity> m_player;
        
        void init();
        void setPouse(bool pouse);
        
        //systems managing
        void sMovement();
        void sUserInput();
        void sCollision();
        //...
        
        //spowning systems
        void sSpownPlayer();
        void sSpownEnemy();
        //...

        void sRender();
};


#endif 

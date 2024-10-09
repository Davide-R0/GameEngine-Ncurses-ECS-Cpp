#ifndef GAMEENGINE_H 
#define GAMEENGINE_H 

//#include "entities/entityMang.h"
//#include "entities/entity.h"
#include "sceneConstants.h"
//class entityMang;
//class entity;
class sceneBase;
//class assets;

#include <memory>
#include <vector>

class gameEngine {
    
    public:
        //make a singleton????
        
        //new /////////////////
        gameEngine();
        ~gameEngine();
        void run(); //main loop 
        void update();
        void quit();
        void changeScene(SCENE_TAG tag, sceneBase& scene);
        //assets& getAssets();
        //window& getWindow();
        void sUserInput();
        ////////////////////////

    private:
        
        //new////////////
        //std::vector<sceneBase*> m_scenes[sizeof(SCENE_TAG)];
        sceneBase* m_scenes[sizeof(SCENE_TAG)] = {};
        //window identifier
        //assets m_assets;
        SCENE_TAG m_currentScene;
        bool m_running = true;
        void init();
        sceneBase* currentScene();
        ////////////
        

        //font
        //text
        //render window
        //all config for the play
        //score
        //current frame
        /*
        std::size_t m_currentFrame = 0;
        //last enemy spown time
        bool m_paused = false;  //if update game logic
        //bool m_running = true;  //if game is running

        //void init();
        void setPouse(bool pouse);
        
        void mainLoop();

        //systems managing
        void sMovement();
        void sUserInput();
        void sCollision();
        //...

        //ncurses rendering
        void ncRendering(std::shared_ptr<entity> a);

        //system to check collision on a board
        void sNcCollide(std::shared_ptr<entity> a, std::shared_ptr<entity> b);
        
        //spowning systems
        void sSpownPlayer();
        void sSpownEnemy();
        //...

        void sRender();
        */
};


#endif 

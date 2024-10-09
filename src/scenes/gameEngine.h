#ifndef GAMEENGINE_H 
#define GAMEENGINE_H 

#include "sceneConstants.h"
class sceneBase;
//class assets;

class gameEngine {
    public:
        /**********************************/
        gameEngine(const gameEngine& other) = delete;
        void operator=(const gameEngine&) = delete;
        static gameEngine* getInstance();
        /**********************************/
        
        //new /////////////////
        ~gameEngine();
        void run();     //main loop 
        void update();
        void quit();
        void changeScene(SCENE_TAG tag, sceneBase& scene);
        //assets& getAssets();
        //window& getWindow();
        void sUserInput();
        ////////////////////////

    private:
        /**********************************/
        gameEngine() {}
        static gameEngine* s_gameEngine;
        /**********************************/


        //new////////////
        sceneBase* m_scenes[NUMBER_SCENE_TAG_DO_NOT_USE] = {};
        //window identifier
        SCENE_TAG m_currentScene;
        bool m_running = true;
        void init();
        sceneBase* currentScene();
        ////////////
        
        //per le classi scene derivate:
        //assets m_assets;
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

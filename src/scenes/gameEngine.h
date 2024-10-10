#ifndef GAMEENGINE_H 
#define GAMEENGINE_H 

#include "sceneConstants.h"
class sceneBase;
#include "../assets/assets.h"

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
        //window& getWindow();
        void sUserInput();

        //NOTE: in this case assets are loaded one (because light) and not per each scene
        //otherwise this should have been in the sceneBase class
        //assets& getAssets();
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
        sceneBase* currentScene() const;

        //NOTE: in this case assets are loaded one (because light) and not per each scene
        //otherwise this should have been in the sceneBase class
        //assets m_assets;
        ////////////
};


#endif 

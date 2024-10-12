#ifndef GAMEENGINE_H 
#define GAMEENGINE_H 

#include "../scenes/sceneConstants.h"
class scene;
#include "../assets/assets.h"

class gameEngine {
    public:
        /**********************************/
        gameEngine(const gameEngine& other) = delete;
        void operator=(const gameEngine&) = delete;
        static gameEngine* getInstance();
        /**********************************/
        
        ~gameEngine();
        void run();     //main loop 
        void update();
        //void quit();
        void changeScene(SCENE_TAG tag, scene* scene);
        void sUserInput();

        //NOTE: in this case assets are loaded one (because light) and not per each scene
        //otherwise this should have been in the sceneBase class
        //assets& getAssets();

    private:
        /**********************************/
        gameEngine() {}
        static gameEngine* s_gameEngine;
        /**********************************/
        
        void init();
        scene* currentScene() const;
        scene* m_scenes[NUMBER_SCENE_TAG_DO_NOT_USE] = {};
        SCENE_TAG m_currentScene;
        bool m_running = true;

        //NOTE: in this case assets are loaded one (because light) and not per each scene
        //otherwise this should have been in the sceneBase class
        //assets m_assets;
        ////////////
};


#endif 

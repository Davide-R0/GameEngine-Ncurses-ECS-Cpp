#include "gameEngine.h"
#include "../core/logger.h"

//wide character ncurses variant
#include <ncursesw/ncurses.h>
//#include <ncurses.h>

#include "../scenes/scene.h"
//#include "scPlay.h"
//#include "../scenes/sceneConstants.h"
#include "../actions/action.h"
#include <cstdlib> //size_t

//NOTE: is not efficient but it's a terminal game engine...
//#include <sys/time.h>
#include <chrono>
#include <thread>

/**********************************/
gameEngine* gameEngine::s_gameEngine = nullptr;

gameEngine* gameEngine::getInstance(){
    if (s_gameEngine == nullptr){
        s_gameEngine = new gameEngine();
        s_gameEngine->init();
        GTRACE("Game Engine constructor called");
    }
    return s_gameEngine;
}
/**********************************/

gameEngine::~gameEngine() {
    GTRACE("Game Engine destructor called");
    for(std::size_t i = 0; i<NUMBER_SCENE_TAG_DO_NOT_USE; i++) {
        delete m_scenes[i];
        m_scenes[i] = nullptr;
    }
}


void gameEngine::init() {
    //start with a scene
    GTRACE("Game engine init");

    }

void gameEngine::run() {
    //main loop
    GINFO("Game loop started");

    int ch;
    ACTION_NAME actionName;
    typedef std::chrono::milliseconds millsec;
    millsec previous = std::chrono::duration_cast<millsec>(std::chrono::system_clock::now().time_since_epoch());
    millsec current;
    millsec elapsed;
    millsec lag = millsec::zero();
    
    //frame per second
    millsec msUpdate = millsec(1000/30);
    
    //bool test = true;

    //main game loop
    while (m_running) {
        wrefresh(stdscr);

        //timesteps
        current = std::chrono::duration_cast<millsec>(std::chrono::system_clock::now().time_since_epoch());
        elapsed = current - previous;
        previous = current;

        lag = lag + elapsed;
        
        //if there is a lag of a multiple of the frame per second calculate the update of that scene that number of time (to not remain back in the calculation of physics, time, ecc... in the scene)
        //TODO: make a function inside of scene class that repeat the update a number of time (so we do not place a while loop here)
        while (lag >= msUpdate){
            currentScene()->update();
            lag -= msUpdate;
        }

        //limit the frame rate to the chosen one, so sleep if the time elapsed is less then the frame rate
        if (elapsed < msUpdate) {
            std::this_thread::sleep_for(msUpdate-elapsed);
        }
        
        //input detection
        ch = getch();
        //if input is not null
        if (ch != ERR){
            //GDEBUG("Pressed: %d", ch);
            actionName = currentScene()->getActionName(ch);
            
            if (actionName != 0) {   //0 means no action (see the enum ACTION_NAME)
                const ACTION_PHASE actionType = PRESS;  //ncurses do not distinguish press/release
                currentScene()->sDoAction(new action(actionName, actionType));  //inside here happen the change scene 
                GDEBUG("After sDoAction()!");
            }
            
            //termination process code ^C
            if (ch == 3) {   
                m_running = false;
            }
        }

        //change schene flag check
        //questo per creare una nuva scena da inizializzare, se volessi riprendere una scena gia inizializata??
        //uno è changeScene(), un'altra cosa è createScene()
        //
        //Da una qualsiasi scena posso creare altre scene o distruggerle o sostituirle con altre e posso anche cambiare scena in base al tag
        //serve uno scene manager che controlla, crea, distrugge, sostituisce le scene create da scene
        //così si avrebbe come membro un singleton (in entrambi le classi scene e gameEngine) che può essere chiamato sia da scene che gameEngine.
        //qui questo assomiglierebbe a qualcosa come: m_sceneManager->getCurrentScene() e (m_sceneManager->update() ???) ... senza dover organizzare la creazione, cambio o altro delle scene. Anzi gameEngine non avrebbe neanche più scene* m_scenes al suo interno, ma solo il sceneManager e si occuperebbe solo di chiamare m_sceneManager->getCurrentScene() quano gli serve.
        //
        //Nella classe scene, si avrebbe la stessa istanza di sceneManager e si utilizerebbe come:
        //  - m_sceneManager->createNewScene(scene* newScene) //crea una nuova scena e la sostituisce nell'array di scene, indipendentemente se ne esiste già una
        //  - m_sceneManager->changeSceneFlag(TAG)  //gli dice di flaggare una scena per poter essere attivata (nel prossimo update di sceneManager??? o subito??), controlla che la scena esista già, se non esiste return false e non fa niente
        //      
        //      Queste due funzioni servono nel caso si vogliano modificare prorpietà di altre scene all'interno della scena attuale
        //  - m_sceneManager->getScenes() //retrurn l'array di scene 
        //  - m_sceneManager->getScene(TAG) //return la scena con TAG
        //  
        //  - m_sceneManager->sceneExist(TAG)   //return true se la scena con TAG esiste già, altrimenti false
        //
        
        //if(currentScene()->getCreateScene()
        if(currentScene()->getChangeSceneFlag()) {
            changeScene(currentScene()->getNewScene()->getTag(), currentScene()->getNewScene());
        }

        //pause functonality for the entire game engine??
        if(!currentScene()->isPaused()){
            //...
            //cosa eseguire se il gioco non è in pausa
            //sUserInput()
            //sRenderer()
        }
    }

    GINFO("Game loop ended");
}

void gameEngine::changeScene(SCENE_TAG tag, scene* scene) {
    GDEBUG("Changing scene");
    m_currentScene = tag;   //BUG: addres not accessible
    m_scenes[tag] = scene;

}

scene* gameEngine::currentScene() const{
    return m_scenes[m_currentScene];
}

//NOTE: in this case assets are loaded one (because light) and not per each scene
//otherwise this should have been in the sceneBase class
/*
assets& gameEngine::getAssets() {
    return m_assets;
}*/





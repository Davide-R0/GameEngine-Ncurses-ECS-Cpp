#ifndef SCENE_H
#define SCENE_H

#include "../actions/actionConstants.h"
#include "sceneConstants.h"
//#include "../assets/assets.h"
//...
//???
//NOTE: includere tutte le classi da cui è composto??

//#include "gameEngine.h"
class gameEngine;
class entityMang;
class assets;
class action;

//#include <ncurses.h>


//use back reference for the scene and engine for the scene change
//oppure mettere engine come protected:
//
//INFO: to print a variable or clas name to the console:
//#include <typeinfo>
//std::cout << typeid(variableName).name();
//this print like 'float' or 'int'

//abstract class 
class scene {
    public:
        scene();
        virtual ~scene();

        virtual void update() = 0;
        virtual void sDoAction(const action* act) = 0;
        virtual void sRender() = 0;

        void simulate(int n);   //call derived class update() function a number n of times
        void registerAction(int ch, ACTION_NAME name); //ch the character number of ncurses 
        ACTION_NAME getActionName(int ch) const;
        
        //assets are modifieble during the game play???
        //if not declare constant and add initialization of assets in the init function of derived classes
        assets* getAssets(); //modifiable
        
        bool isPaused() const;
        
        SCENE_TAG getTag() const;

        //devono essere pubblico o privato???
        //can be private if initialized in the constructor in create a get function
        entityMang* m_entityMang;
        //gameEngine* m_game;     //dove lo prendo??? non è stato definito, o meglio è stato definito solo nella classe applicazione
                                //devo fare in modo che in scene io abbia questo??
                                //quindi o faccio in mdo di avere una referenza della classe application in questa scene o della classe m_game
                                //Difficilmente si vorrebbe modificare qualcosa della applicazione più generale all'interno di una scena, molto più probabile e normale voler modficare qualcosa del gioco in una scena
                                //Dare all'utente la possibilità di modificare la applicazione all'interno di una scena?
                                //Sicuramente deve poter modificare m_game per cambiare la scena, ma dargli l'accesso diretto a m_game? no dargli solo una chiamata di una funzione che fa tutto
                                //Quindi fare in modo di attivare una "flag" nella classe scene che indica la necessità del cambio di scena e poi lasciare il cambio di scena al gameEngine classe 
        //function called by gameEngine to check if a flag to change scene is being erased:
        bool getChangeSceneFlag() const;
        //function called by gameEngine in case m_changeSceneFlag == true
        scene* getNewScene() const;

        //function called in derived class to toggle change scene
        void setChangeSceneFlag();
        void setNewScene(scene* newScene);

        void setTag(SCENE_TAG tag);

        //for ncurses
        int xScr, yScr;
        
    private:
        //public or private??
        assets* m_assets;

        bool m_paused = false;
        bool m_hasEnded = false;

        //for changing scene 
        bool m_changeSceneFlag = false; //true if is necessary to change scene
        scene* m_sceneToChange = nullptr;   //non viene eliminata alla distruzione di questa scena? 

        //action map
        //map from the name given of ACTION_NAME to the int of ncurses (ncurses criptation of key name)
        //TODO: change this in a more dinamic way
        //      conviene un vettore statico rispetto ad una mappa std::map?? cosa è più veloce nella ricerca
        int m_actionMap[NUMBER_ACTION_NAME_DO_NOT_USE] = {};        //m_actionMap[action name] = action key of ncurses
                                                                    //NOTE: in this case ncurses have 93 possible key pressing
        
        SCENE_TAG m_sceneTag;    //to be set in the initialization
};

#endif 

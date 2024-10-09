#ifndef SCENEBASE_H
#define SCENEBASE_H

#include "../actions/actionConstants.h"
//#include "../assets/assets.h"
//...
//???
//NOTE: includere tutte le classi da cui è composto??

#include "gameEngine.h"
//class gameEngine;
class entityMang;
class assets;
class action;

//abstract class 
class sceneBase {
    public:
        sceneBase();
        virtual ~sceneBase();

        virtual void update() = 0;
        virtual void sDoAction(const action* act) = 0;
        virtual void sRender() = 0;

        void simulate(int n);   //call derived class update() function a number n of times
        void registerAction(int ch, ACTION_NAME name); //ch the character number of ncurses 
        ACTION_NAME getActionName(int ch);
        
        bool isPaused() const;

        //devono essere pubblico o privato???
        entityMang* m_entityMang;
        assets* m_assets;
        gameEngine* m_game;

    private:
                
        bool m_paused = false;
        bool m_hasEnded = false;
        
        //action map
        //map from the name given of ACTION_NAME to the int of ncurses (ncurses criptation of key name)
        //TODO: change this in a more dinamic way
        //      conviene un vettore statico rispetto ad una mappa std::map?? cosa è più veloce nella ricerca
        int m_actionMap[NUMBER_ACTION_NAME_DO_NOT_USE];     //m_actionMap[action name] = action key of ncurses
                                //NOTE: in this case ncurses have 93 possible key pressing

};

#endif 

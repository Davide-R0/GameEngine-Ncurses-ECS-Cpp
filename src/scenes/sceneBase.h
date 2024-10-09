#ifndef SCENEBASE_H
#define SCENEBASE_H

class gameEngine;
class entityMang;

#include "../assets/assets.h"
#include "../actions/actionConstants.h"
#include <vector>

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
        //void doAction(const action& act);
        void registerAction(int ch, ACTION_NAME name); //ch the character number of ncurses 
        //const ACTION_TAG* [len] getActionMap() const;
        //ACTION_NAME* getActionMap(ACTION_TYPE& type);
        ACTION_NAME getActionName(int ch);
        
        bool isPaused() const;

        //deve essere pubblico o privato???
        entityMang* m_entityMang;
        assets* m_assets;

    private:
        gameEngine* m_game;
        
        bool m_paused = false;
        bool m_hasEnded = false;
        
        //action map
        //map from the name given of ACTION_NAME to the int of ncurses (ncurses criptation of key name)
        //TODO: change this in a more dinamic way
        int m_actionMap[6];     //m_actionMap[action name] = action key of ncurses
                                //NOTE: in this case ncurses have 93 possible key pressing

};

#endif 

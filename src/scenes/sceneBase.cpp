#include "sceneBase.h"
#include "../core/logger.h"
#include <bits/stdc++.h>    //for std::find()

//momentaneamente
#include <ncurses.h>

sceneBase::sceneBase() {
    GTRACE("Scene base class constructor called");
}

sceneBase::~sceneBase() {
    GTRACE("Scene base class destructor called");
}

void sceneBase::registerAction(int ch, ACTION_NAME name) {
    m_actionMap[name] = ch;
}


ACTION_NAME sceneBase::getActionName(int ch) {
    //TODO: add checks ...
    
    for(std::size_t i = 0; i<sizeof(m_actionMap)/sizeof(int); i++) {
        if (m_actionMap[i] == ch) {    
            return (ACTION_NAME)i;
        }
    }
    return (ACTION_NAME)0;
}

bool sceneBase::isPaused() const {
    return m_paused;
}

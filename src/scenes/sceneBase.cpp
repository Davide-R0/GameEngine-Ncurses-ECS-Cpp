#include "sceneBase.h"
#include "../core/logger.h"
#include <cstdlib> //size_t

sceneBase::sceneBase() {
    GTRACE("Scene base class constructor called");
    m_assets = new assets();
}

sceneBase::~sceneBase() {
    GTRACE("Scene base class destructor called");
    delete m_assets;
    //do not delete m_game
}

void sceneBase::registerAction(int ch, ACTION_NAME name) {
    //TODO: add checks ...
    m_actionMap[name] = ch;
}


ACTION_NAME sceneBase::getActionName(int ch) const {
    //TODO: add checks ...

    for(std::size_t i = 0; i<NUMBER_ACTION_NAME_DO_NOT_USE; i++) {
        if (m_actionMap[i] == ch) return (ACTION_NAME)i;
    }
    return (ACTION_NAME)0;
}

bool sceneBase::isPaused() const {
    return m_paused;
}

assets* sceneBase::getAssets() {
    return m_assets;
}

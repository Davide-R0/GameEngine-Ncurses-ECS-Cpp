#include "scene.h"
#include "../core/gameEngine.h"
#include "../core/logger.h"
#include "sceneConstants.h"
#include <cstdlib> //size_t
//wide character ncurses varaint
#include <ncursesw/ncurses.h>

scene::scene() {
    GTRACE("Scene base class constructor called");
    m_assets = new assets();

    //get standard screen dimension
    getmaxyx(stdscr, yScr, xScr);
    GINFO("Start up terminal size (%d,%d)", xScr, yScr);
}

scene::~scene() {
    GTRACE("Scene base class destructor called");
    delete m_assets;
    //do not delete m_game
}

void scene::registerAction(int ch, ACTION_NAME name) {
    //TODO: add checks ...
    m_actionMap[name] = ch;
}


ACTION_NAME scene::getActionName(int ch) const {
    //TODO: add checks ...

    for(std::size_t i = 0; i<NUMBER_ACTION_NAME_DO_NOT_USE; i++) {
        if (m_actionMap[i] == ch) return (ACTION_NAME)i;
    }
    return (ACTION_NAME)0;
}

bool scene::isPaused() const {
    return m_paused;
}

assets* scene::getAssets() {
    return m_assets;
}

SCENE_TAG scene::getTag() const {
    return m_sceneTag;
}

void scene::setTag(SCENE_TAG tag){
    m_sceneTag = tag;
}

bool scene::getChangeSceneFlag() const {
    return m_changeSceneFlag;
}

scene* scene::getNewScene() const {
    return m_sceneToChange;
}

void scene::setChangeSceneFlag() {
    m_changeSceneFlag = true;
}

void scene::setNewScene(scene* newScene) {
    m_sceneToChange = newScene;
}

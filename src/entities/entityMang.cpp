#include "entityMang.h"
//#include "entityConstants.h" 
#include "../core/logger.h"
#include "entity.h"

#include <algorithm>

/**********************************/
/*entityMang *entityMang::s_entityMang = nullptr;

  entityMang *entityMang::getInstance(){
  if (s_entityMang == nullptr){
  s_entityMang = new entityMang();
  GTRACE("Entity Manager constructor called");
  }
  return s_entityMang;
  }*/
/**********************************/

entityMang::entityMang(){
    GTRACE("Entity Manager constructor called");
}

entityMang::~entityMang() {
    GTRACE("Entity Manager destructor called");

    //WARN: check the validity of this cleaning
    for (std::vector<entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it) {
        delete *it;
        *it = nullptr;  //this should be done by the .clear() ?
    }
    m_entities.clear();
}


entity* entityMang::addEntity (const ENTITY_TYPE& tag){
    entity* e = new entity(tag, m_totalEntities++);
    m_toAdd.push_back(e);

    //GDEBUG("Entity con tag %d e id %d aggiunto alla lista da aggiungere", (int)e->getTag(), (int)e->getId());

    return e;
}

void entityMang::removeEntity(const ENTITY_TYPE& tag, const std::size_t id){
    //WARN: sbagliato, bisogna iterare in base al tag e id per trovare l'effettiva entità da rimuovere
    for (auto& e : m_entityMap[tag]) {
        if (e->getId() == id) {
            e->destroy();
            m_removingQueue = true;
        }
    }
    GDEBUG("entityRemove called for tag %d and id %d", tag, id);
    //m_toRemove.push_back(m_entities[id]); //ricontrollare
}

const std::vector<entity*>& entityMang::getEntities() const{
    //GDEBUG("getEntities called");
    return m_entities;
}

const std::vector<entity*>& entityMang::getEntities(const ENTITY_TYPE& tag) const{
    //GDEBUG("getEntities called with tag");
    return m_entityMap[tag];
}

//called at the beggining of each game frame
void entityMang::update () {
    //GDEBUG("Update call");

    for (auto e : m_toAdd) {
        m_entities.push_back(e);
        m_entityMap[e->getTag()].push_back(e);

        //add error message

        //GDEBUG("Entity con tag %d e id %d aggiunto!", (int)e->getTag(), (int)e->getId());
    }
    /* is this needed? NO,becouse I delete the object that it points which is already pointed by m_entities etc..
       for (std::vector<entity*>::iterator it = m_toAdd.begin(); it != m_toAdd.end(); ++it) {
       delete *it;
     *it = nullptr;  //this should be done by the .clear() ?
     }*/
    m_toAdd.clear();

    // call this anly if there is a queue or remove entityes
    if (m_removingQueue) {
        //NOTE: add checks??
        removeDeadEntity();
        m_removingQueue = false;
    }


}

void entityMang::removeDeadEntity() {
    //GDEBUG("Remove dead entity called");
    //WARN: it works??
    for (auto entities : m_entityMap){
        entities.erase(std::remove_if(entities.begin(), entities.end(), [](entity* v)->bool{return !v->isAlive();}), entities.end());
    }
    //GDEBUG("lenght of entities before remove: %d", m_entities.size());
    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [](entity* v)->bool {
                    if (!v->isAlive()) {
                        delete v;       //NOTE: necessary to call the destructor otherwise is not called
                        //v = nullptr;  //free by erase() ??
                        return true;
                    }
                    return false;
                }), m_entities.end());
    //GDEBUG("lenght of entities after remove: %d", m_entities.size());
}

#include "entity.h"
#include "constant.h"
//#include "entityMang.h"
#include "../components/Components.h" 
#include "../core/logger.h"
#include <vector>

entity::entity(const ENTITY_TYPE tag, std::size_t id) : m_id(id), m_tag(tag){
    GTRACE("Entity with tag %d and id %d created", m_tag, m_id);
}

entity::~entity() {
    GTRACE("Entity destructor called for tag %d and id %d", m_tag, m_id);
    //vector of components should be deallocated as stack declared
    //not easy with raw pointers
    //WARN: controllare se funziona bene
    std::vector<Components*>::iterator i;
    for (i = m_components.begin(); i != m_components.end(); i++) {
        delete *i;
    }
}


const ENTITY_TYPE entity::getTag() const{
    return m_tag;
}

const std::size_t entity::getId() const{
    return m_id;
}

bool entity::isAlive() const{
    return m_alive;
}

bool entity::isToRender() const {
    return m_isToRender;
}

void entity::destroy() {
    m_alive = false;
}

void entity::toRender(bool toRender) {
    m_isToRender = toRender;
}

/*
   std::vector<Components*> getComponents() {
   return m_components;
   }*/

/*
   void entity::entityRemove(entityMang* manager) {
   m_alive = false;
//aggiungere controlli?
manager->removeEntity(m_tag, m_id);
//controllare se funziona
}
*/

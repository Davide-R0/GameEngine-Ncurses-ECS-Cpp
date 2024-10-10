#include "entity.h"
#include "constant.h"
#include "../components/Components.h" 
#include "../core/logger.h"
#include <vector>

entity::entity(const ENTITY_TYPE tag, std::size_t id) : m_id(id), m_tag(tag){
    GTRACE("Entity with tag %d and id %d created", m_tag, m_id);
}

entity::~entity() {
    GTRACE("Entity destructor called for tag %d and id %d", m_tag, m_id);
    
    //WARN: check the validity of this cleaning
    for (std::vector<Components*>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
        delete *it;
        *it = nullptr;  //this should be done by the .clear() ?
    }
    m_components.clear();
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


#include "entity.h"
#include "constant.h"
//#include "entityMang.h"

entity::entity(const ENTITY_TYPE tag, std::size_t id) : m_id(id), m_tag(tag){

}

ENTITY_TYPE entity::getTag() const{
    return m_tag;
}

std::size_t entity::getId() const{
    return m_id;
}

bool entity::isAlive() const{
    return m_alive;
}

void entity::destroy() {
    m_alive = false;
}

/*
void entity::entityRemove(entityMang* manager) {
    m_alive = false;
    //aggiungere controlli?
    manager->removeEntity(m_tag, m_id);
    //controllare se funziona
}

template <class T> void entity::addComponent(T c) {
    m_components.push_back(c);
}
*/

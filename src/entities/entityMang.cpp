#include "entityMang.h"
#include "constant.h"
#include "entity.h"

#include <iostream>
#include <memory>
#include <algorithm> //for find
//#include <string>

/**********************************/
entityMang *entityMang::s_entityMang = nullptr;

entityMang *entityMang::getInstance(){
    if (s_entityMang == nullptr){
        s_entityMang = new entityMang();
        std::cout<<"Entity Manager Object created\n";
    }
    return s_entityMang;
}
/**********************************/

std::shared_ptr<entity> entityMang::addEntity (const ENTITY_TYPE& tag){
    auto e = std::make_shared<entity>(tag, m_totalEntities ++);
    m_toAdd.push_back(e);

    std::cout << "Oggetto con tag " << e->getTag() << " e id " << e->getId() << " aggiunto" << std::endl;
    return e;
}

void entityMang::removeEntity(const ENTITY_TYPE& tag, const std::size_t id){
    m_toRemove.push_back(m_entities[id]); //ricontrollare
}

const entityVec& entityMang::getEntities() const{
    return m_entities;
}
const entityVec& entityMang::getEntities(const ENTITY_TYPE& tag) const{
    return m_entityMap[tag];
}

//called at the beggining of each game frame
void entityMang::update () {
    for (auto e : m_toAdd) {
        m_entities.push_back(e);
        m_entityMap[e->getTag()].push_back(e);
        //add error message
    }
    m_toAdd.clear();
    
    //???? to remove dead entities
    /*
    for (auto& [tag, m_entities] : m_entityMap){
        removeDeadEntity(entityVec);
    }*/
    /*
    for (auto e : m_toRemove) {
        //if (!e.isAlive()){
            //remove from vector
        //}
        //ricontorllare
        /*auto i = std::find(m_entities.begin(), m_entities.end(), [&e](std::shared_ptr<entity> * i) { return i && (*i == e); });

        if (i != m_entities.end()) {
            m_entities.erase(i);
        }*/
        
        //std::cout<< "Oggetto con tag " << e->getTag() << " e id " << e->getId() << " rimosso" << std::endl;
        //m_entities.erase(std::find(m_entities.begin(), m_entities.end(), e));
        /*
        m_entities.push_back(e);
        m_entityMap[e->getTag()].push_back(e);
        */
    //}
    m_toRemove.clear();

}

void entityMang::removeDeadEntity(entityVec& vec) {
    for (auto e : vec) {
        if (!e->isAlive()){
            //remove from vec
            //see std::remove_if()
        }
    }
}

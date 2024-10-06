#ifndef ENTITYMANG_H
#define ENTITYMANG_H

#include "constant.h"

/*Non è possibile aggiungere in entrambigli header file peciprocamente.
 * E' giusto dichiarare la classe nell'header file e includere l'altro hheader file solo nel .cpp file?
 */
//#include "entity.h"
class entity;

#include <vector>
#include <memory> //for shared ptr

//change shared pointer with something else
typedef std::vector<std::shared_ptr<entity>> entityVec;
typedef std::vector<entityVec> entityMap; //vector of entities indexed by the enum of the tag


class entityMang {
    public:
        /**********************************/
        entityMang(const entityMang &other) = delete;
        void operator=(const entityMang&) = delete;
        static entityMang *getInstance();
        /**********************************/
        
        void update();
        std::shared_ptr<entity> addEntity (const ENTITY_TYPE& tag);
        void removeEntity(const ENTITY_TYPE& tag, const std::size_t id);

        const entityVec& getEntities() const;
        const entityVec& getEntities(const ENTITY_TYPE& tag) const;
        
        void removeDeadEntity(entityVec& vec);

    private:
        /**********************************/
        entityMang() {}
        static entityMang* s_entityMang;
        /**********************************/
        
        entityVec m_entities;
        entityVec m_toAdd;
        entityVec m_toRemove;
        entityMap m_entityMap;

        std::size_t m_totalEntities = 0;

};


#endif

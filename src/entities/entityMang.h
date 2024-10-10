#ifndef ENTITYMANG_H
#define ENTITYMANG_H

#include "constant.h"

/*Non è possibile aggiungere in entrambigli header file peciprocamente.
 * E' giusto dichiarare la classe nell'header file e includere l'altro hheader file solo nel .cpp file?
 */
//#include "entity.h"
#include <vector>

class entity;

//#include <memory> //for shared ptr
//typedef std::vector<std::shared_ptr<entity>> entityVec;
//typedef entityVec entityMap[sizeof(ENTITY_TYPE)]; //vector of entities indexed by the enum of the tag

class entityMang {
    public:
        /**********************************/
        /*entityMang(const entityMang &other) = delete;
        void operator=(const entityMang&) = delete;
        static entityMang *getInstance();*/
        /**********************************/
        entityMang();
        ~entityMang();

        void update();
        entity* addEntity (const ENTITY_TYPE& tag);
        void removeEntity(const ENTITY_TYPE& tag, const std::size_t id);

        const std::vector<entity*>& getEntities() const;
        const std::vector<entity*>& getEntities(const ENTITY_TYPE& tag) const;
        
        
    private:
        /**********************************/
        /*entityMang() {}
        static entityMang* s_entityMang;*/
        /**********************************/
        
        std::vector<entity*> m_entities;
        std::vector<entity*> m_toAdd;
        //std::vector<entity*> m_toRemove;
        std::vector<entity*> m_entityMap[NUMBER_ENTITY_TYPE_DO_NOT_USE] = {};
        
        bool m_removingQueue = false;

        std::size_t m_totalEntities = 0;
        
        void removeDeadEntity();

};

#endif

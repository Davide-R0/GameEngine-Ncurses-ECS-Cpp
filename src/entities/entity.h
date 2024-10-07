#ifndef ENTITY_H
#define ENTITY_H

#include "constant.h"
#include "../core/logger.h"

//remove what not needed
#include <memory>

/*Non è possibile aggiungere in entrambigli header file reciprocamente.
 * E' giusto dichiarare la classe nell'header file e includere l'altro hheader file solo nel .cpp file?
 */
//#include "entityMang.h"
//class entityMang;
#include <ncurses.h>
#include <string>
#include <vector>

class Components;
//#include "../components/Components.h"

//NOTE: a template member function of a class decleration MUST be in the header file

class entity {
    public:
        entity(const ENTITY_TYPE tag, std::size_t id);
        ~entity();

        //here all shared_ptr of all the components 
        //std::shared_ptr<CWindow> cWindow;   //window on witch entity will be renered
        //std::shared_ptr<CTransform> cTransform; //position inside the window
        //std::shared_ptr<CSpriteNc> cSpriteNc;
        //std::shared_ptr<CCollisionShapeNc> cCollisionShapeNc;
        
        
        //possible to modify entoty tag in this way?
        ENTITY_TYPE getTag() const;
        std::size_t getId() const;
        
        bool isAlive() const;
        bool isToRender() const;

        void destroy();
        void toRender(bool toRender = false);
        
        template<typename T> 
        void addComponent(T* c);    //add componet
       
        
        template<typename T> 
        T* getComponent(){
            return reinterpret_cast<T*>(m_components[0]);
        }
        
        /*
        template <class T>
        void removeComponent (T c);    //remove component 
        */
        
        

    private:
        friend class entityMang;

        //should be private constructor
        //entity(const ENTITY_TYPE tag, std::size_t id);

        std::vector<Components*> m_components;

        const std::size_t m_id = 0;
        const ENTITY_TYPE m_tag = DEFAULT;
        bool m_alive = true;
        bool m_isToRender = true;
       
};

//Template function declaration
template<typename T> 
void entity::addComponent(T* c) {
    GDEBUG("Adding component %s to entity with tag %d and id %d", c->name, m_tag, m_id);

    m_components.emplace_back(c);
}
/*
template<typename T> 
T* getComponent() {
    return m_components[0];
}*/





#endif

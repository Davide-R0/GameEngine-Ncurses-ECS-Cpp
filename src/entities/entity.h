#ifndef ENTITY_H
#define ENTITY_H

#include "constant.h"
#include "../core/logger.h"

//remove what not needed
//#include <memory>

/*Non è possibile aggiungere in entrambigli header file reciprocamente.
 * E' giusto dichiarare la classe nell'header file e includere l'altro hheader file solo nel .cpp file?
 */
//#include "entityMang.h"
//class entityMang;
//wide character ncurses variant
//#define NCURSES_WIDECHAR 1
//#include <ncursesw/ncurses.h>

#include <string>
#include <vector>

class Components;

//NOTE: a template member function of a class decleration MUST be in the header file

class entity {
    public:
        entity(const ENTITY_TYPE tag, std::size_t id);
        ~entity();

        //here all shared_ptr of all the components (old way)
        //std::shared_ptr<CWindow> cWindow;   //window on witch entity will be renered
        //std::shared_ptr<CTransform> cTransform; //position inside the window
        //std::shared_ptr<CSpriteNc> cSpriteNc;
        //std::shared_ptr<CCollisionShapeNc> cCollisionShapeNc;
        
        const ENTITY_TYPE getTag() const;
        const std::size_t getId() const;
        
        bool isAlive() const;
        bool isToRender() const;

        void destroy();
        void toRender(bool toRender = false);
        
        template<typename T> 
        void addComponent(T* c);    //add componet
        
        template<typename T> 
        T* getComponent(){
            //GDEBUG("getComponent called");
            for (std::size_t i = 0; i<m_components.size(); i++) {
                if (dynamic_cast<T*>(m_components.at(i))){
                    //GDEBUG("Returned component with indeces %d", i);
                    return reinterpret_cast<T*>(m_components[i]);
                }
            }
            return nullptr;
        }
        
        /*
        template <class T>
        void removeComponent (T c);    //remove component 
        */

    private:
        //should be private constructor??? (note: in the scene class cannot create the m_player entity)
        //friend class entityMang;
        //entity(const ENTITY_TYPE tag, std::size_t id);

        std::vector<Components*> m_components;

        const std::size_t m_id = 0;
        const ENTITY_TYPE m_tag = DEFAULT;
        bool m_alive = true;
        bool m_isToRender = true;
       
};

template<typename T> 
void entity::addComponent(T* c) {
    //GDEBUG("Adding component %s to entity with tag %d and id %d", c->name, m_tag, m_id);
    if (getComponent<T>() == nullptr) {
        m_components.push_back(c);
    } else {
        //error or warn?
        GWARN("Tryng to declare a duplicate component type on the same entity with tag %d and id %d", m_tag, m_id); 
        //important because allocate the component class in heap memory without free it after:
        delete c;
        c = nullptr;
    }
}

#endif

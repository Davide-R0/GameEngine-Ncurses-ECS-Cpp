#ifndef ENTITY_H
#define ENTITY_H

#include "constant.h"
#include "../components/Components.h" 
#include <memory>

/*Non è possibile aggiungere in entrambigli header file reciprocamente.
 * E' giusto dichiarare la classe nell'header file e includere l'altro hheader file solo nel .cpp file?
 */
//#include "entityMang.h"
//class entityMang;
#include <ncurses.h>
#include <string>
#include <vector>

class entity {
    
    public:
        entity(const ENTITY_TYPE tag, std::size_t id);
              
        //void entityRemove(entityMang* manager); //set alive = false and add the entity to remove in the m_toRemove vector in the entityManger
        
        //here all shared_ptr of all the components 
        //std::shared_ptr<CWindow> cWindow;   //window on witch entity will be renered
        std::shared_ptr<CTransform> cTransform; //position inside the window
        //std::shared_ptr<CSpriteNc> cSpriteNc;
        //std::shared_ptr<CCollisionShapeNc> cCollisionShapeNc;
        

        ENTITY_TYPE getTag() const;
        std::size_t getId() const;
        bool isAlive() const;
        bool isToRender() const;

        void destroy();
        void toRender(bool toRender = false);

        //template <class T> 
        //void addComponent (T c);    //add componet
        
        //template <class T>
        //void getComponent ();    //remove component 
        
            
    private:
        friend class entityMang;

        //should be private constructor
        //entity(const ENTITY_TYPE tag, std::size_t id);

        const std::size_t m_id = 0;
        const ENTITY_TYPE m_tag = DEFAULT;
        bool m_alive = true;
        bool m_isToRender = true;
       
};

#endif

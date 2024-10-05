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

#include <string>
#include <vector>

class entity {
    
    public:
        
        //        //????????????        
        //void entityRemove(entityMang* manager); //set alive = false and add the entity to remove in the m_toRemove vector in the entityManger
        
        //here all shared_ptr of all the components
        std::shared_ptr<CTransform> cTransform;

        
        ENTITY_TYPE& getTag() const;
        std::size_t getId() const;
        bool isAlive() const;
        void destroy();

        //template <class T> 
        //void addComponent (T c);    //add componet
        
        //template <class T>
        //void getComponent ();    //remove component 
        
    
    private:
        friend class entityMang;

        //private constructor
        entity(const ENTITY_TYPE tag, std::size_t id);

        const std::size_t m_id = 0;
        const ENTITY_TYPE m_tag = DEFAULT;
        bool m_alive = true;
       
                
};

#endif
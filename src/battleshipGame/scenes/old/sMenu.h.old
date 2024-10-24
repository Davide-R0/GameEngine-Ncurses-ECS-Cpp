#ifndef SMENU_H
#define SMENU_H
#include <vector>
#include <string>
#include "../../entities/entity.h"
//#include "../../assets/assets.h"

//class only for vertical entry menu 
class menu {
    public:
        
        void addEntry(std::vector<std::string> content);

        void moveUp();
        void moveDown();
        void attachWindow(entity* window);
        void select() const;
        void renderMenu();


    private:
        //std::vector<std::string> m_entries;
        int m_activeIndex = 0;
        entity* m_window;
        
        std::vector<std::vector<std::string>> m_entries;
};

#endif 

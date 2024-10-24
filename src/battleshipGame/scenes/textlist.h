#ifndef TEXTLIST_H
#define TEXTLIST_H
#include "../../entities/entity.h"
#include "../../assets/assets.h"

struct text_list_info {
    //int nArgs;    can recave them after
    bool simpleText = true; //if the list i a simple text or a list of multiple line text 
    bool vertical = false;   //vertical list, otherwise horizontal
    int padding = 1;    //padding between vertical or horizontal entries
                        //NOTE: 0 means on a new line or consecutive text
    //...
    entity* window;   
};

//NOTE: by default vertical list are centered

class textlist {
    public:
        textlist(text_list_info info);
        ~textlist();

        //set list
        
        void addAssetEntries(std::vector<std::string> assetEntries);

        void moveNext();    //up if vertical list
                            //right if orrizontal list
        void movePrev();    //down if vertical list
                            //left if orrizontal list
        int getSelect() const;    //necessario??
        void sRenderMenu();
    
    private:
        text_list_info m_info;
        int m_activeIndex = 0;
        int nArgs = 0;  
        
        //for simple text 
        std::vector<std::string> m_textEntries;
        //for image list
        std::vector<std::vector<std::string>> m_assetEntries;    //WARN: momentaneo, cambiarlo con:
                                                            //assets* m_assetEntries;
};

#endif 

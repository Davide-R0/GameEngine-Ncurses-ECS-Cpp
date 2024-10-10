#ifndef ASSETS_H
#define ASSETS_H

#include <string>
#include <filesystem>
#include "assetsConstant.h"

class assets {
    public:
        assets();
        ~assets();
        
        //this functions should be called only on entity creation, not on every rendering frame

        //special ncurses drived function
        bool addNcTexture(TEXTURE_NAME name, std::filesystem::path path);

        //void addTexture(enum name, path);
        //...
        
        //THIS FUNCTION SHOULD BE CALLED ONLY ON ENTITY CREATION, NOT EVERY RENDERING FRAME

        //assetType& getTexture(enum name) const;
        //assetType& getSound(enum name) const;
        //...
        
    private:
        std::string m_texture[NUMBER_TEXTURE_NAME_DO_NOT_USE] = {};
        int nLine[NUMBER_TEXTURE_NAME_DO_NOT_USE];
        int lenLine[NUMBER_TEXTURE_NAME_DO_NOT_USE];

        //assetType* m_assetMap[enum name];

        //assetType* m_textures[...];
        //assetType* m_animations[...];
        //assetType* m_sounds[...];
        //assetType* m_fonts[...];
};


#endif

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "../entities/entityConstants.h"

//wide character ncurses variant
//#define NCURSES_WIDECHAR 1
#include <ncursesw/ncurses.h>
//#include <ncurses.h>


//#include <filesystem>   //non includerlo qui???
#include <vector>
//#include <string>
//#include "../core/logger.h"

//trasferire tutte queste classi in struct?

class Components {
    public:
       Components();
       virtual ~Components();
};

class CTransform : public virtual Components{
    public:
        CTransform(int X, int Y);
        CTransform();
        ~CTransform();

        int y = 0;
        int x = 0;
        
        const char name[11] = "CTransform";

    private:

};

class CInput : public virtual Components {
    public:
        CInput();
        ~CInput();

        bool up = false;
        bool down = false;
        bool right = false;
        bool left = false;
};

class CWindow : public virtual Components {
    public:
        //all the information needed for ncurses to render a window with or without a custom borde
        CWindow();
        ~CWindow();

        int x = 0;
        int y = 0;           //position of the top left corner
        int dimX = 0;
        int dimY = 0;     //dimensions of the window
        bool box = false;           //counturn of the window with 2 type character
        bool border = false;        //custom counturn of the window with 7 type of character
         
        cchar_t borderCh[8];
        cchar_t boxCh[2];

        WINDOW* win = nullptr;      //window referred to
                                    //if not set refer to std window
};

class CCursorPosition : public virtual Components {
    public:
        int x = 0, y = 0;
};

#include "../assets/assetsConstant.h"

class CTexture : public virtual Components {
    public:
        CTexture();
        CTexture(TEXTURE_NAME tag) : name(tag) {}
        
        TEXTURE_NAME name;
};

class CAnimation : public virtual Components {
    public:
};

//WARN: aggiustare!!
//forse meglio non trattare in questa componente la creazione della window, ma nel renderer. Così sarà possibile creare finestre virtuali che non verranno renderizzate
/*class CWindow {
    public:
        CWindow(int line_X = 0, int line_Y = 0, int X = 0, int Y = 0, WINDOW* parent_win = stdscr);
        ~CWindow();
        
        const WINDOW* getWin() const;
        
        //after changing this parameter is needed to update the window, how?????
        //lie number and position top left corner (of the parent window)
        int line_x = 0;
        int line_y = 0;
        int x = 0;
        int y = 0;

    private:
        const WINDOW* m_win;
        
};*/
/*
//sprite for ncurses rendering
class CSpriteNc {
    public:
        //TODO: trasferire il loading dei file alla scena, non farlo runtine, quindi in fututro timuovere questo costruttore
        CSpriteNc(std::filesystem::path filePath);  //read from a file the sprite and place in "sprite"
        
        CSpriteNc(char* sprite, int x, int y); 
        ~CSpriteNc();
        
        //use char* or std::vector????
        const char* getSprite() const;
        int getX() const;
        int getY() const;

    private:
        //WARN: const???
        const char* m_sprite;
        const int m_x, m_y;
};

//collision shape ncurses
//fare la classe collision shape derivata dalla classe shape??? simili
class CCollisionShapeNc {
    public:
        //TODO: trasferire il loading dei file alla scena, non farlo runtine, quindi in fututro timuovere questo costruttore
        CCollisionShapeNc(std::filesystem::path filePath);  //read from a file the sprite and place in "sprite"

        CCollisionShapeNc(char* sprite, int x, int y);
        ~CCollisionShapeNc();
        
        //use char* or std::vector????
        const char* getSprite() const;
        int getX() const;
        int getY() const;
        
        std::vector<MASK_LAYER> mask_layer;

    private:
        //WARN: const???
        const char* m_sprite;
        const int m_x, m_y;
};
*/
#endif 

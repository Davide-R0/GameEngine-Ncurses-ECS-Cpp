#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <ncurses.h>

class CTransform {
    public:
        void setXY(int X, int Y);
        int getX() const;
        int getY() const;
    private:
        int x = 0;
        int y = 0;
};

class CWindow {
    public:
        CWindow();
        ~CWindow();
    
        //no logic in components 
        //void refresh(); 
        //void box();
        
        void setXY();

        void getWin() const;
        void getX() const;
        void getY() const;
        
    private:
        const WINDOW* win;
        int x, y;
};

#endif 

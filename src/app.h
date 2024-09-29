#ifndef APP_H
#define APP_H

#include <iostream>
#include <ncurses.h>

class app {
    public:
        /**********************************/
        app(const app &other) = delete;
        void operator=(const app&) = delete;
        static app *getInstance();
        /**********************************/
       
        void start();

        void end();

    private:
        /**********************************/
        app() {}; //constructor
        static app* s_app;
        /**********************************/
        
        bool initApp();

        void loopApp();

        bool endApp();

};


#endif 
